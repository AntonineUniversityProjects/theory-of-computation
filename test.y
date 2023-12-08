%{
#include <stdio.h>

int yylex();
int yyerror(char *s);

%}

%token STRING NUM OTHER SEMICOLON

%type <name> STRING
%type <number> NUM

%union {
    char name[20];
    int number;
}

%%

prog: stmts
;

stmts: | stmt SEMICOLON stmts
;

stmt: STRING {
    // Do something with the string, for example, print it
    printf("String: %s\n", $1);
}
| NUM {
    // Do something with the number, for example, print it
    printf("Number: %d\n", $1);
}
| OTHER
;

%%

int yyerror(char *s)
{
    printf("Syntax Error on line %s\n", s);
    return 0;
}

int main()
{
    yyparse();

    return 0;
}
