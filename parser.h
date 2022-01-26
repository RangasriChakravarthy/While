//
// Created by Priyanka Dutta and Rangasri Chakravarthy.
//
#ifndef WHILE_HW2_PARSER_H
#define WHILE_HW2_PARSER_H

#include "ast.h"
#include "lexer.h"
typedef struct parser_struct {
    lexer_node* lexer;
    token_struct_node* curr_token;
} parser_node;

void parser_error();
ast_node* parser_expr(parser_node* parser);

parser_node* parser_create(lexer_node* lexer) {
    parser_node* parser = (parser_node*)malloc(sizeof(parser_node));
    parser->lexer = lexer;
    parser->curr_token = lexer_nexttoken(parser->lexer);
    return parser;
}

token_struct_node* parser_eat(parser_node* parser, int type) {
    token_struct_node* dummy;
    if (parser->curr_token->type == type) {
        token_struct_node *prev = parser->curr_token;
        parser->curr_token = lexer_nexttoken(parser->lexer);
        return prev;
    } else {
        parser_error();
        return dummy;
    }
}

ast_node* parser_factor(parser_node* parser) {
    ast_node* dummy_ast;
    token_struct_node* token = parser->curr_token;
    if (token->type == NUM) {
        parser_eat(parser, NUM);
        return ast_num_create(token);
    }
    else if (token->type == SUB) {
        parser_eat(parser, SUB);
        return ast_unary_create(token, parser_factor(parser));
    }
    else if (token->type == LPAREN) {
        parser_eat(parser, LPAREN);
        ast_node *node = parser_expr(parser);
        parser_eat(parser, RPAREN);
        return node;
    }
    else if (token->type == NOT) {
        parser_eat(parser, NOT);
        return ast_unary_create(token, parser_factor(parser));
    }
    return dummy_ast;
}

ast_node* parser_term(parser_node* parser) {
    token_struct_node* token;
    ast_node *node = parser_factor(parser);
    while (parser->curr_token->type == MUL || parser->curr_token->type == DIV || parser->curr_token->type == MOD ||
    (parser->curr_token->type == LESS) || (parser->curr_token->type == GREAT) ||(parser->curr_token->type == EQUAL)) {
        token = parser->curr_token;
        if (token->type == MUL) {
            parser_eat(parser, MUL);
        }
        else if (token->type == DIV) {
            parser_eat(parser, DIV);
        }
        else if (token->type == MOD) {
            parser_eat(parser, MOD);
        }
        else if (token->type == LESS) {
            parser_eat(parser, LESS);
        }
        else if (token->type == GREAT) {
            parser_eat(parser, GREAT);
        }
        else if (token->type == EQUAL) {
            parser_eat(parser, EQUAL);
        }
        node = ast_binary_create(node, token, parser_factor(parser));
    }
    return node;
}

ast_node* parser_expr(parser_node* parser) {
    token_struct_node *token;
    ast_node* node = parser_term(parser);
    while (parser->curr_token->type == ADD || parser->curr_token->type == SUB||
    (parser->curr_token->type == AND) || (parser->curr_token->type == OR)) {
        token = parser->curr_token;
        if (token->type == ADD) {
            parser_eat(parser, ADD);
        }
        else if (token->type == SUB) {
            parser_eat(parser, SUB);
        }
        else if (token->type == AND) {
            parser_eat(parser, AND);
        }
        else if (token->type == OR) {
            parser_eat(parser, OR);
        }
        node = ast_binary_create(node, token, parser_term(parser));

    }


    return node;
}
void parser_error() {
    printf("Parser error: not a valid parser character\n");
    exit(1);
}
void parser_destroy(parser_node* parser) {
    free(parser);
}

#endif //WHILE_HW2_PARSER_H
