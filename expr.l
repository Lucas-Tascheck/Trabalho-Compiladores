%option noyywrap

%{
#define YYSTYPE struct ExpressionValue
#include "expr.tab.h"
#include "ast.h"
#include <stdlib.h>
#include <string.h>

struct ExpressionValue {
    double num_value;
    char *str_value;
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
\n      {return TFIM;}

{num}   {yylval.num_value = atof(yytext); return TNUM;}
{id}    {yylval.str_value = strdup(yytext); return ID;}

. { fprintf(stderr, "Caractere inválido: %s\n", yytext); }

%%