//
// Created by Priyanka Dutta and Rangasri Chakravarthy.
//

#ifndef WHILE_HW2_LEXER_H
#define WHILE_HW2_LEXER_H
enum operations{
    NUM,
    ADD,
    SUB,
    MUL,
    DIV,
    MOD,
    LPAREN,
    RPAREN,
    LESS,
    GREAT,
    EQUAL,
    AND,
    OR,
    NOT,
    END
};

typedef struct token_val {
    int   int_val;
    char *ch;
} token_val_node;

typedef struct token_struct {
    int type;
    token_val_node value;
} token_struct_node;

typedef struct lexer_struct {
    unsigned int curr_pos;
    char curr_char;
    char *arith_exp;
    unsigned int exp_len;
} lexer_node;

void lexer_move(lexer_node* lexer);
void lexer_error();

token_struct_node* token_create_int(int type, int value) {
    token_struct_node* token = (token_struct_node*)malloc(sizeof(token_struct_node));
    token->type = type;
    token->value.int_val = value;
    return token;
}

token_struct_node* token_create_char(int type, const char* ch, int ch_length) {
    token_struct_node* token = (token_struct_node*) malloc(sizeof(token_struct_node));
    token->type   = type;
    token->value.ch = (char*) malloc(sizeof(char));
    strcpy(token->value.ch, ch);
    return token;
}

lexer_node* lexer_create(char* arith_expr, unsigned int exp_len) {
    lexer_node *lexer = (lexer_node*)malloc(sizeof(lexer));
    lexer->arith_exp = arith_expr;
    lexer->exp_len = exp_len;
    lexer->curr_pos = 0;
    lexer->curr_char = lexer->arith_exp[lexer->curr_pos];
    return lexer;
}
void lexer_omitspaces(lexer_node* lexer) {
    while (lexer->curr_char && lexer->curr_char == ' '){
        lexer_move(lexer);
    }
}

int lexer_num(lexer_node* lexer) {
    char int_str[20];
    int int_value;
    unsigned int i = 0;
    while (lexer->curr_char && isdigit(lexer->curr_char)) {

        int_str[i] = lexer->curr_char;
        lexer_move(lexer);
        i++;

    }
    int_str[i]='\0';
    int_value = atoi(int_str);
    return (int_value);
}

void lexer_move(lexer_node* lexer) {
    lexer->curr_pos = lexer->curr_pos + 1;
    if (lexer->curr_pos > (lexer->exp_len - 1)) {
        lexer->curr_char = '\0';
    } else {
        lexer->curr_char = lexer->arith_exp[lexer->curr_pos];
    }
}

token_struct_node* lexer_nexttoken(lexer_node* lexer) {
    token_struct_node *token;
    while (lexer->curr_char) {
        if (lexer->curr_char == ' ') {
            lexer_omitspaces(lexer);
            continue;
        }

        if (isdigit(lexer->curr_char)) {
            token = token_create_int(NUM, lexer_num(lexer));
            return token;
        }

        if (lexer->curr_char == '+') {
            lexer_move(lexer);
            token = token_create_char(ADD, "+", 1);
            free(token->value.ch);
            return token;
        }

        if (lexer->curr_char == '-') {
            lexer_move(lexer);
            token = token_create_char(SUB, "-", 1);
            return token;
        }

        if (lexer->curr_char == '*') {
            lexer_move(lexer);
            token = token_create_char(MUL, "*", 1);
            free(token->value.ch);
            return token;
        }

        if (lexer->curr_char == '/') {
            lexer_move(lexer);
            token = token_create_char(DIV, "/", 1);
            free(token->value.ch);
            return token;
        }

        if (lexer->curr_char == '%') {
            lexer_move(lexer);
            token = token_create_char(MOD, "%", 1);
            free(token->value.ch);
            return token;
        }

        if (lexer->curr_char == '(') {
            lexer_move(lexer);
            token = token_create_char(LPAREN, "(", 1);
            free(token->value.ch);
            return token;
        }

        if (lexer->curr_char == ')') {
            lexer_move(lexer);
            token = token_create_char(RPAREN, ")", 1);
            free(token->value.ch);
            return token;
        }

        if (lexer->curr_char == '<') {
            lexer_move(lexer);
            token = token_create_char(LESS, "<", 1);
            free(token->value.ch);
            return token;
        }
        if (lexer->curr_char == '>') {
            lexer_move(lexer);
            token = token_create_char(GREAT, ">", 1);
            free(token->value.ch);
            return token;
        }
        if (lexer->curr_char == '=') {
            lexer_move(lexer);
            token = token_create_char(EQUAL, "=", 1);
            free(token->value.ch);
            return token;
        }
        if (lexer->curr_char == '$') {
            lexer_move(lexer);
            token = token_create_char(AND, "$", 1);
            free(token->value.ch);
            return token;
        }
        if (lexer->curr_char == '|') {
            lexer_move(lexer);
            token = token_create_char(OR, "|", 1);
            free(token->value.ch);
            return token;
        }
        if (lexer->curr_char == '!') {
            lexer_move(lexer);
            token = token_create_char(NOT, "!", 1);
            free(token->value.ch);
            return token;
        }

        lexer_error();
    }

    token = token_create_char(END, "", 1);
    return token;
}

void lexer_error() {
    printf("Lexer error: not a valid lexer character\n");
    exit(1);
}

void lexer_destroy(lexer_node* lexer) {
    free(lexer);
}

#endif //WHILE_HW2_LEXER_H
