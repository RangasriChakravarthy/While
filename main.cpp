#include <stdio.h>
#include <cstring>
#include <iostream>
#include <iterator>
#include <map>
#include "while-parser.h"

int main() {

    string s = "";
    map<char*, int>::iterator i;
    map<char, string>::iterator j;
    char s1[100] = "";
    char *s0 = NULL, str_val[100];

    getline(cin, s);

    while_parse(s);

    for (i = state.begin(); i != state.end(); ++i) {
        char *ch = i->first;
        j=var.find(*ch);
        if(j != var.end()){
            sprintf(str_val, "%s", (j->second).c_str());
        }
        else{
            sprintf(str_val, "%s", i->first);
        }
        int val = i->second;
        if (s0 == NULL){
            sprintf(s1, "%s → %d", str_val, val);
            s0 = s1;
        }
        else {
            sprintf(s1, "%s, %s → %d", s0, str_val, val);
        }
    }
    cout << "{" << s1 << "}\n";
    return 0;
}
