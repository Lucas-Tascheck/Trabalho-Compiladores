%option noyywrap

%{
#define YYSTYPE char*
#include "ast.h"
#include "expr.tab.h"

struct ExpressionValue {
    double num_value;
    char* str_value;
};
%}

delim	[ \t\n]
ws	{delim}+
digito	[0-9]
num	{digito}+(\.{digito}*(E[+-]?{digito}+)?)?
id	[a-zA-Z][a-zA-Z0-9]*

%%

{ws}	{}      

"+"     {return TADD;}
"-"     {return TSUB;}
"*"     {return TMUL;}
"/"     {return TDIV;}
"="     {return EQ;}
"("     {return TAPAR;}
")"     {return TFPAR;}
"<"     {return TLESS;}
">"     {return TMORE;}
"=="    {return TEQUAL;}
"!="    {return TDIFF;}
"&&"    {return TAND;}
"||"    {return TOR;}
"int"   {return INT;}
"float" {return FLOAT;}
"string" {return STRING;}
"void"  {return VOID;}
"if"    {return IF;}
"else"  {return ELSE;}
"while" {return WHILE;}
"print" {return PRINT;}
"read"  {return READ;}
"return"    {return RETURN;}
";"     {return SEMICOLON;}
","     {return COMMA;}
"{"     {return LBRACE;}
"}"     {return RBRACE;}

{num}   {yylval = strdup(yytext); return TNUM;}
{id}    {yylval = strdup(yytext); return ID;}

. { fprintf(stderr, "Caractere inválido: %s\n", yytext); }

%%