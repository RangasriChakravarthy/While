//
// Created by Priyanka Dutta and Rangasri Chakravarthy.
//

#ifndef WHILE_HW2_INTERPRETER_H
#define WHILE_HW2_INTERPRETER_H

#include "ast.h"
#include "lexer.h"
#include "parser.h"
#include "while-parser.h"

typedef struct interpreter_struct {
    parser_node* parser;
} interpreter_node;

using namespace std;


int interpreter_move(interpreter_node* interpreter, ast_node* node);

interpreter_node* interpreter_create(parser_node* parser) {
    interpreter_node* interpreter = (interpreter_node*)malloc(sizeof(interpreter_node));
    interpreter->parser = parser;
    return interpreter;
}

int interpreter_num(ast_node* node) {
    return node->data.num->value.int_val;
}
int interpreter_unary(interpreter_node* interpreter, ast_node* node) {
    if (node->data.unaryop->op->type == SUB)
        return (-1)*interpreter_move(interpreter, node->data.unaryop->expr);
    if (node->data.unaryop->op->type == ADD) {
        return interpreter_move(interpreter, node->data.unaryop->expr);
    }
    if (node->data.unaryop->op->type == NOT) {
        return !(interpreter_move(interpreter, node->data.unaryop->expr));
    }
    return 0;
}

int interpreter_binary(interpreter_node* interpreter, ast_node* node) {
    if (node->data.binop->op->type == ADD) {
        return interpreter_move(interpreter, node->data.binop->left) + interpreter_move(interpreter, node->data.binop->right);
    }
    else if (node->data.binop->op->type == SUB) {
        return interpreter_move(interpreter, node->data.binop->left) - interpreter_move(interpreter, node->data.binop->right);
    }
    else if (node->data.binop->op->type == MUL) {
        return interpreter_move(interpreter, node->data.binop->left) * interpreter_move(interpreter, node->data.binop->right);
    }
    else if (node->data.binop->op->type == DIV) {
        return interpreter_move(interpreter, node->data.binop->left) / interpreter_move(interpreter, node->data.binop->right);
    }
    else if (node->data.binop->op->type == MOD) {
        return interpreter_move(interpreter, node->data.binop->left) % interpreter_move(interpreter, node->data.binop->right);
    }
    else if (node->data.binop->op->type == LESS) {
        return interpreter_move(interpreter, node->data.binop->left) < interpreter_move(interpreter, node->data.binop->right);
    }
    else if (node->data.binop->op->type == GREAT) {
        return interpreter_move(interpreter, node->data.binop->left) > interpreter_move(interpreter, node->data.binop->right);
    }
    else if (node->data.binop->op->type == EQUAL) {
        return interpreter_move(interpreter, node->data.binop->left) == interpreter_move(interpreter, node->data.binop->right);
    }
    else if (node->data.binop->op->type == AND) {
        return interpreter_move(interpreter, node->data.binop->left) & interpreter_move(interpreter, node->data.binop->right);
    }
    else if (node->data.binop->op->type == OR) {
        return interpreter_move(interpreter, node->data.binop->left) | interpreter_move(interpreter, node->data.binop->right);
    }
    return 0;
}
int interpreter_move(interpreter_node* interpreter, ast_node* node) {
    int val;
    if (node->type == number) {
        val = interpreter_num(node);
        ast_num_destroy(node);
    }

    else if (node->type == unary_op) {
        val = interpreter_unary(interpreter, node);
        ast_unary_destroy(node);
    }

    else if (node->type == binary_op) {
        val = interpreter_binary(interpreter, node);
        ast_binary_destroy(node);
    }
    return val;
}


int eval(interpreter_node* interpreter) {
    ast_node* tree = parser_expr(interpreter->parser);
    return interpreter_move(interpreter, tree);
}

void interpreter_destroy(interpreter_node* interpreter) {
    free(interpreter);
}

#endif //WHILE_HW2_INTERPRETER_H
