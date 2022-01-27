//
// Created by Priyanka Dutta and Rangasri Chakravarthy
//

#ifndef WHILE_HW2_WHILE_PARSER_H
#define WHILE_HW2_WHILE_PARSER_H
//#include <stdlib.h>
//#include <stdio.h>
//#include <ctype.h>
//#include <string.h>
#include <cstring>
#include <iostream>
#include <iterator>
#include <map>
#include "ast.h"
#include "lexer.h"
#include "parser.h"
#include "interpreter.h"

using namespace std;
std::map<char*, int,std::less<std::string> > state;
std::map<char, string>var;

int evaluate(char *txt_copy);
int execute_condition(char *cond);
void if_helper(string s, int res);
void while_helper(string s, char b[], int res);

int iterate(char *str){
    map<char *, int>::iterator itr;
    for (itr = state.begin(); itr != state.end(); ++itr)
    {
        if (itr->first[0] == str[0]){
            return itr->second;
        }
    }
    return 0;
}

char* seq_statement(char* text_copy){
    char* dummy;
    int result;
    char *token1, *token2, *token3, ch, s3[10], a[80];
    char* token4 = (char *)malloc(sizeof(text_copy));
    strcpy(token4, text_copy);
    int val;
    for(token1 = strtok_r(token4, ";", &token4); token1 != NULL; token1 = strtok_r(NULL, ";", &token4)){
        token3 = token1;
        token2 = strtok_r(token3, ":=", &token3);
        string s1, s2;
        s2+=token3;
        s2.erase(0, 1);
        for(int i = 0; i < s2.size(); i++){
            if (isalpha(s2[i])){
                ch = s2[i];
                val = iterate(&ch);
                sprintf(s3, "%d", val);
                s1.clear();
                s1+=s3;
                int len=s1.size();
                s2.erase(i, 1);
                s2.insert(i, s1);
                i+=len-1;
                s1.clear();
            }
        }
        strcpy(a, s2.c_str());
        result = evaluate(a);
        state[token1]=result;
    }
    return dummy;
}

void if_statement(string s)
{
    if (s == ""){
        return ;
    }
    int result;
    char a[100];
    unsigned if_pos = s.find("if") + 2;
    unsigned then_pos1 = s.find("then");
    string condition1 = s.substr (if_pos, then_pos1 - if_pos);
    strcpy(a, condition1.c_str());
    result = execute_condition(a);
    if_helper(s, result);
}

void if_helper(string s, int res){
    char b[100];
    if (res){
        unsigned then_pos2 = s.find("then") + 4;
        unsigned else_pos1 = s.find("else");
        string condition2 = s.substr (then_pos2, else_pos1 - then_pos2);
        strcpy(b, condition2.c_str());
        seq_statement(b);
    }
    else {
        unsigned else_pos2 = s.find("else") + 4;
        unsigned end_pos = s.find("\0");
        string condition3 = s.substr (else_pos2, end_pos - else_pos2);
        if (s.find('{') != std::string::npos) {
            unsigned open_pos = condition3.find("{") + 1;
            unsigned close_pos = condition3.find("}");
            string condition4 = condition3.substr (open_pos, close_pos - open_pos);
            strcpy(b, condition4.c_str());
            seq_statement(b);
        }
        else {
            strcpy(b, condition3.c_str());
            seq_statement(b);
        }
    }
}

void while_statement(string s){
    if (s == ""){
        return ;
    }
    char a[100],b[100];
    int result;
    unsigned while_pos = s.find("while") + 5;
    unsigned do_pos = s.find("do");
    string condition1 = s.substr (while_pos, do_pos - while_pos);
    // strcpy(a, condition1.c_str());
    strcpy(b, condition1.c_str());
    result = execute_condition(b);
    string cond_if;
    while_helper(s, b, result);
}
void while_helper(string s, char b[], int res){
    char c[100], d[100];
    if(res){
        unsigned do_pos2 = s.find("do") + 2;
        unsigned end_pos = s.find("\0");
        string condition2 = s.substr (do_pos2, end_pos - do_pos2);
        if (s.find('{') != std::string::npos) {
            unsigned open_pos = condition2.find("{") + 1;
            unsigned close_pos = condition2.find("}");

            if(s.find("if") != std::string::npos){
                unsigned if_pos = s.find("if");
                string cond_if = s.substr (if_pos, close_pos - 1);
                strcpy(c, cond_if.c_str());
                if_statement(cond_if);
            }
            else{
                string condition3 = condition2.substr (open_pos, close_pos - open_pos);
                strcpy(d, condition3.c_str());
                seq_statement(d);
            }
        }
        else if(s.find("if") != std::string::npos) {
            unsigned if_pos = s.find("if");
            unsigned end_if = s.size();
            string cond_if = s.substr (if_pos, end_if);
            if_statement(cond_if);
        }
        else {
            strcpy(d, condition2.c_str());
            seq_statement(d);
        }
        res = execute_condition(b);
        while(res){
            if(s.find("if") != std::string::npos){
                string s1;
                s1+=c;
                if_statement(s1);
            }
            else {
                seq_statement(d);
            }
            res = execute_condition(b);
        }
    }
}

int execute_condition(char *cond){
    int result;
    char s3[10];
    char ch;
    char* cond_copy = (char *)malloc(sizeof(cond));
    strcpy(cond_copy,cond);
    string s1,s2;
    s1+=cond_copy;
    for(int i = 0; i < s1.size(); i++){
        ch = s1[i];
        s2.clear();
        if (isalpha(ch)){
            int val = iterate(&ch);
            sprintf(s3, "%d", val);
            s2+=s3;
            int len=s2.size();
            s1.erase(i, 1);
            s1.insert(i, s2);
            i+=len-1;
            cond_copy[i] = s3[0];
            continue;
        }
    }
    char* temp = (char *)malloc(sizeof(s1.c_str()));
    strcpy(temp, s1.c_str());
    result = evaluate(temp);
    return result;
}

void statement_parser(string *s){
    int result;
    char a[100], b[100];
    string condition1;
    unsigned delete_pos;
    while(!s->empty()){

        unsigned if_pos = s->find("if");
        unsigned while_pos = s->find("while");

        if (if_pos == 0){
            condition1.erase();
            string condition2 = s->substr (s->find("if") + 2, (s->find("then")) - (s->find("if") + 2));
            strcpy(b, condition2.c_str());
            result = execute_condition(b);
            string else_cond = s->substr (s->find("else"), s->size());
            string condition3 = s->substr(s->find("else") + 4, s->size() );

            if (s->find('{') != std::string::npos) {
                delete_pos = s->find("}");
            }
            else if((condition3.find("if") != std::string::npos && (condition3.find("if") == 0 )) || (condition3.find("while") != std::string::npos && (condition3.find("while") == 0 ))){
                delete_pos = s->size();
            }
            else {

                if (else_cond.find(";") != std::string::npos){
                    condition1+=s->substr (if_pos,s->find("else"));
                    condition1+=else_cond.substr (0, else_cond.find(";"));
                    delete_pos = s->find("else") + else_cond.find(";") + 1;
                }
                else {
                    condition1 = s->substr (if_pos, s->size());
                    delete_pos = s->size();
                }
            }

            if_statement(condition1);
            s->erase(0, delete_pos);
        }

        else if (while_pos == 0){
            condition1.erase();
            string else_cond = s->substr (s->find("do"), s->size());
            string condition2 = s->substr(s->find("do") + 2, s->size() );
            if (s->find('{') != std::string::npos) {
                if(condition2.find("if") != std::string::npos && (condition2.find("if") == 1 )) {
                    condition1 = s->substr(while_pos, s->find("}") + 1);
                }
                else {
                    condition1 = s->substr (while_pos, s->find("}") + 1);
                }
                delete_pos = s->find("}") + 1;
            }
            else if(condition2.find("if") != std::string::npos && (condition2.find("if") == 0 )){
                condition1 = s->substr(while_pos + 1, s->size() - 1);
                delete_pos = s->size();

            }
            else if (condition2.find("while") != std::string::npos && ( condition2.find("while") == 0 )){
                delete_pos = s->size();
            }
            else {

                if (else_cond.find(";") != std::string::npos){
                    condition1+=s->substr(while_pos,s->find("do"));
                    delete_pos = s->find("do") + else_cond.find(";") + 1;
                    condition1+=else_cond.substr (0, else_cond.find(";"));
                }
                else {
                    condition1 = s->substr (while_pos, s->size());
                    delete_pos = s->size();
                }
            }
            while_statement(condition1);
            s->erase(0, delete_pos);
        }
        else {
            unsigned end_pos;
            if (s->find(";") != std::string::npos){
                end_pos = s->find(";") + 1;
            } else {
                end_pos = s->size();
            }
            string condition2 = s->substr (0, end_pos);
            delete_pos = end_pos;
            strcpy(a, condition2.c_str());
            seq_statement(a);
            s->erase(0, delete_pos);
        }
    }
}

void while_parse(string s){

    if (s.find("skip") != std::string::npos){
        s.replace(s.find("skip"),sizeof("skip")-1, "");
    }
    if (s.find("∧") != std::string::npos){
        s.replace(s.find("∧"),sizeof("∧")-1, "$");
    }
    if (s.find("∨") != std::string::npos){
        s.replace(s.find("∨"),sizeof("∨")-1, "|");
    }

    if (s.find("¬") != std::string::npos){
        s.replace(s.find("¬"),sizeof("¬")-1, "!");
    }
    std::string true_val = "1";
    std::string false_val = "0";
    size_t pos;
    while ((pos = s.find("true")) != std::string::npos) {
        s.replace(pos, 4, true_val);
    }
    while ((pos = s.find("false")) != std::string::npos) {
        s.replace(pos, 5, false_val);
    }

    string s2;
    s2+=s;
    char *token;

    char* temp = (char *)malloc(s2.size() * sizeof(char*));
    strcpy(temp, s2.c_str());

    for(token = strtok_r(temp, " ", &temp); token != NULL; token = strtok_r(NULL, " ", &temp)){
        if (isalpha(token[0]) && (strlen(token) > 1)){
            if ((strcmp(token,"if")!=0) && (strcmp(token,"then")!=0) &&
                (strcmp(token,"while")!=0) && (strcmp(token,"skip")!=0) &&
                (strcmp(token,"do")!=0)  && (strcmp(token,"else")!=0)){
                var[token[0]]=token;
                size_t pos = s.find(token);
                string s3;
                s3+=token[0];
                s.replace(pos, strlen(token), s3);
            }
        }
    }
    s.erase(std::remove_if(s.begin(), s.end(), ::isspace), s.end());

    statement_parser(&s);
}
int evaluate(char *txt_copy){
    int len= strlen(txt_copy);
    lexer_node *lexer = lexer_create(txt_copy,len);
    parser_node *parser = parser_create(lexer);
    interpreter_node *interpreter = interpreter_create(parser);
    int result = eval(interpreter);
    lexer_destroy(lexer);
    parser_destroy(parser);
    interpreter_destroy(interpreter);
    return result;
}

#endif //WHILE_HW2_WHILE_PARSER_H
