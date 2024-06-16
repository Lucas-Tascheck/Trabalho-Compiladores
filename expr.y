%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ast.h"


int yyerror(const char *);
int yylex();

%}
%union {
      double doubleNum;
      char *stringVal;
      ListaParam *listaParam;
      ListaDeFunc *listaDeFunc;
}
%define parse.error verbose
%token STRING
%token INT FLOAT VOID
%token IF ELSE WHILE PRINT READ RETURN
%token SEMICOLON COMMA LBRACE RBRACE
%token TADD TMUL TSUB TDIV EQ TAPAR TFPAR TNUM TLESS TMORE TEQUAL TDIFF TAND TOR TFIM ID

%type <stringVal> STRING
%type <doubleNum> INT
%type <doubleNum> FLOAT
%type <doubleNum> VOID
%type <doubleNum> IF
%type <doubleNum> ELSE
%type <doubleNum> WHILE
%type <doubleNum> PRINT
%type <doubleNum> READ
%type <doubleNum> RETURN
%type <doubleNum> SEMICOLON
%type <doubleNum> COMMA
%type <doubleNum> LBRACE
%type <doubleNum> RBRACE
%type <doubleNum> TADD
%type <doubleNum> TMUL
%type <doubleNum> TSUB
%type <doubleNum> TDIV
%type <doubleNum> EQ
%type <doubleNum> TAPAR
%type <doubleNum> TFPAR
%type <doubleNum> TNUM
%type <doubleNum> TLESS
%type <doubleNum> TMORE
%type <doubleNum> TEQUAL
%type <doubleNum> TEDIFF
%type <doubleNum> TAND
%type <doubleNum> TOR
%type <doubleNum> TFIM
%type <doubleNum> ID
%type <listaDeFunc> Programa
%type <listaDeFunc> Linha
%type <listaDeFunc> ListaFuncoes
%type <listaDeFunc> Funcao
%type <listaParam> DeclParametros 
%type <listaParam> Parametro
%type <doubleNum> Expr
%type <doubleNum> Termo
%type <doubleNum> Fator
%type <doubleNum> Rel
%type <doubleNum> OpLog
%type <doubleNum> FatorLog


%%

Linha : Programa {printf("%s", $1->id);}
      ; 
Expr  : Expr TADD Termo { $$ = $1 + $3; }
      | Expr TSUB Termo { $$ = $1 - $3; }
      | Termo
      ;


Termo : Termo TMUL Fator { $$ = $1 * $3; }
      | Termo TDIV Fator { $$ = $1 / $3; }
      | Fator
      | ChamaFuncao
      ;

Fator : TNUM 
      | TAPAR Expr TFPAR 
      ;

ExprSTR  : ExprSTR TADD Termo2 
      | ExprSTR TSUB Termo2 
      | Termo2
      ;


Termo2 : Termo2 TMUL Fator2
      | Termo2 TDIV Fator2 
      | Fator2
      | ChamaFuncao
      ;

Fator2 : ID 
      | TNUM
      | TAPAR ExprSTR TFPAR 
      ;

Rel   : Rel TAND OpLog { $$ = $1 && $3; }
	  | Rel TOR OpLog { $$ = $1 || $3; }
	  | OpLog
      ;

OpLog : FatorLog TMORE FatorLog { $$ = $1 > $3; }
      | FatorLog TLESS FatorLog { $$ = $1 < $3; }
      | FatorLog TEQUAL FatorLog { $$ = $1 == $3; }
      | FatorLog TDIFF FatorLog { $$ = $1 != $3; }
      | FatorLog { $$ = $1; }
      ;

FatorLog: TNUM
        | ID


Programa : ListaFuncoes BlocoPrincipal { $$ = $1; }
         | BlocoPrincipal { $$ = $1; }
         ;

ListaFuncoes : ListaFuncoes Funcao {$$ = createFunc($1, $2)}
             | Funcao {$$ = $1}
             ;

Funcao : TipoRetorno ID TAPAR DeclParametros TFPAR BlocoPrincipal {$$ = initListaDeFunc(char "Func", $1, $2, $4)}
       | TipoRetorno ID TAPAR TFPAR BlocoPrincipal {$$ = initListaDeFunc(char "Func", $1, $2, NULL)}
       ;

TipoRetorno : Tipo
            | VOID
            ;

DeclParametros : DeclParametros COMMA Parametro {$$ = createParam($1, $3)}
               | Parametro {$$ = $1}
               ;

Parametro : Tipo ID {$$ = initParam($1, $2)}
          ;

BlocoPrincipal : LBRACE Declaracoes ListaCmd RBRACE { $$ = $3; }
               | LBRACE ListaCmd RBRACE { $$ = $2; }
               ;

Declaracoes : Declaracoes Declaracao
            | Declaracao
            ;

Declaracao : Tipo ListaId SEMICOLON
           ;

Tipo : INT
     | STRING
     | FLOAT
     ;

ListaId : ListaId COMMA ID
        | ID
        ;

Bloco : LBRACE ListaCmd RBRACE { $$ = $2; }
      ;

ListaCmd : ListaCmd Comando { $$ = $2; }
         | Comando { $$ = $1; }
         ;

Comando : CmdSe { $$ = $1; } 
        | CmdEnquanto { $$ = $1; }
        | CmdAtrib { $$ = $1; }
        | CmdEscrita { $$ = $1; }
        | CmdLeitura { $$ = $1; }
        | ChamadaProc { $$ = $1; }
        | Retorno { $$ = $1; }
        ;

Retorno : RETURN Expr SEMICOLON { $$ = $2; }
        | RETURN ID SEMICOLON { $$ = 1; }
        | RETURN SEMICOLON { $$ = 1; }
        ;

CmdSe : IF TAPAR Rel TFPAR Bloco { $$ = $5; }
      | IF TAPAR Rel TFPAR Bloco ELSE Bloco { if($3) $$ = $5; else $$ = 7; }
      ;

CmdEnquanto : WHILE TAPAR Rel TFPAR Bloco
            ;

CmdAtrib : ID EQ Expr SEMICOLON
         | ID EQ ExprSTR SEMICOLON
         | ID EQ ID SEMICOLON
         ;

CmdEscrita : PRINT TAPAR Expr TFPAR SEMICOLON
           | PRINT TAPAR ID TFPAR SEMICOLON
           ;

CmdLeitura : READ TAPAR ID TFPAR SEMICOLON
           ;

ChamadaProc : ChamaFuncao SEMICOLON
            ;

ChamaFuncao : ID TAPAR ListaParametros TFPAR
            | ID TAPAR TFPAR
            ;

ListaParametros : ListaParametros COMMA Expr
                | ListaParametros COMMA ID
                | Expr
                | ID
                ;
%%

int yyerror(const char *str)
{
    fprintf(stderr, "%s\n", str);
    return 0; // Adicione um retorno para evitar warnings
}
