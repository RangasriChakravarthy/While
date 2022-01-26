//
// Created by Priyanka Dutta and Rangasri Chakravarthy.
//

#ifndef WHILE_HW2_AST_H
#define WHILE_HW2_AST_H

#include "lexer.h"

enum node_type {
    number,
    unary_op,
    binary_op
};

struct ast_node {
    int type;
    union {
        struct integer_node *num;
        struct unary_node *unaryop;
        struct binary_node *binop;
    } data;
};

struct integer_node {
    token_val_node value;
};
struct unary_node {
    ast_node  *expr;
    token_struct_node *op;
};
struct binary_node {
    ast_node *left;
    ast_node *right;
    token_struct_node *op;
};


ast_node* ast_num_create(token_struct_node* token) {
    ast_node* node = (ast_node*)malloc(sizeof(ast_node));
    node->type = number;
    node->data.num = (integer_node*)malloc(sizeof(integer_node));
    node->data.num->value = token->value;
    return node;
}

void ast_num_destroy(ast_node* num) {
    free(num);
}



ast_node* ast_unary_create(token_struct_node *op, ast_node *expr) {
    ast_node* node = (ast_node*)malloc(sizeof(ast_node));
    node->type = unary_op;
    node->data.unaryop = (unary_node*)malloc(sizeof(unary_node));
    node->data.unaryop->op = op;
    node->data.unaryop->expr = expr;
    return node;
}

void ast_unary_destroy(ast_node* unaryop) {
    free(unaryop);
}

ast_node* ast_binary_create(ast_node* left, token_struct_node* op, ast_node* right) {
    ast_node* node = (ast_node*)malloc(sizeof(ast_node));
    node->type = binary_op;
    node->data.binop = (binary_node*)malloc(sizeof(binary_node));
    node->data.binop->left = left;
    node->data.binop->right = right;
    node->data.binop->op = op;
    return node;
}

void ast_binary_destroy(ast_node* binaryop) {
    free(binaryop);
}

#endif //WHILE_HW2_AST_H
