# WHILE interpreter

-------------------------------------------------------------------
HW2- WHILE: lexer.h, parser.h, ast.h, interpreter.h, while-parser.h, main.cpp, Makefile

Authors: Rangasri Chakravarthy & Priyanka Dutta

On this homework, we worked together for 12 hours,

Rangasri worked independently for 2 hours,
Priyanka worked independently for 2 hours.
--------------------------------------------------------------------
This project was implemented in c++. (same as HW1)

Steps to compile:
- run 'make'

Steps to run:
- ./while

Steps to run the tests:
- ./test.sh

While operations implemented:

Aexp {+ (ADD), - (SUB), * (MUL), / (DIV)}, Bexp {Boolean statements}, Sequential commands, if & while statements

Extra features added:

% (MOD) operation, skipping extra spaces (even if there is more than 1 space between numbers and operands), evaluating parenthesis and braces.

Extra test cases:

7 extra test cases have been added to support the extra features and are under 'self.bats'


References:

•  https://ruslanspivak.com/lsbasi-part7/

•  Our Arith code from HW1


# While