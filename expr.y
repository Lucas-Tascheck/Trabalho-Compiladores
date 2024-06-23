%{ 
#include <stdio.h>
#include <stdlib.h>

int yyerror(const char *);
int yylex();
%}

%code requires {#include "ast.h"}

%union {
      char *str;
      Programa *programa;
      ListaDeFunc *listaDeFunc;
      ListaParam *listaParam;
      Declaracoes *declaracoes;
      ListaDeCmd *listaDeCmd;
      BlocoPrincipal *blocoPrincipal;
      ListaId *listaId;
      ListaParamChamafunc *listaParamChamafunc;
      ChamaFunc *chamaFunc;
      Escrita *escrita;
      Expr *expr;
      Rel *rel;
}

%define parse.error verbose
%token STRING
%token INT FLOAT VOID
%token IF ELSE WHILE PRINT READ RETURN
%token SEMICOLON COMMA LBRACE RBRACE
%token TADD TMUL TSUB TDIV EQ TAPAR TFPAR TNUM TLESS TMORE TEQUAL TDIFF TAND TOR TFIM ID

%type <str> TADD
%type <str> TMUL
%type <str> TSUB
%type <str> TDIV
%type <str> EQ
%type <str> TAPAR
%type <str> TFPAR
%type <str> TLESS
%type <str> TMORE
%type <str> TEQUAL
%type <str> TDIFF
%type <str> TAND
%type <str> TOR
%type <programa> Programa
%type <listaDeFunc> Linha
%type <listaDeFunc> ListaFuncoes
%type <listaDeFunc> Funcao
%type <listaParam> DeclParametros 
%type <listaParam> Parametro
%type <blocoPrincipal> BlocoPrincipal
%type <declaracoes> Declaracao
%type <declaracoes> Declaracoes
%type <str> TipoRetorno
%type <str> Tipo
%type <str> ID 
%type <str> TNUM 
%type <expr> Expr 
%type <expr> Fator
%type <expr> Termo
%type <rel> Rel 
%type <rel> OpLog
%type <rel> FatorLog
%type <listaId> ListaId
%type <listaParamChamafunc> ListaParametros
%type <chamaFunc> ChamaFuncao
%type <chamaFunc> ChamadaProc
%type <escrita> Escrita
%%

Linha : Programa {printf("%s", $1->listaDeFunc->tipo);}
      ; 

Expr  : Expr TADD Termo {$$ = initExpr($2, "", NULL, $1, $3);}
      | Expr TSUB Termo {$$ = initExpr($2, "", NULL, $1, $3);}
      | Termo {$$ = $1;}
      ;


Termo : Termo TMUL Fator {$$ = initExpr($2, "", NULL, $1, $3);}
      | Termo TDIV Fator {$$ = initExpr($2, "", NULL, $1, $3);}
      | Fator {$$ = $1;}
      | ChamaFuncao {$$ = initExpr("", "", $1, NULL, NULL);}
      ;

Fator : TNUM {$$ = initExpr("", $1, NULL, NULL, NULL);}
      | TAPAR Expr TFPAR {$$ = $2;}
      ;

Rel   : Rel TAND OpLog {$$ = initRel($2, NULL, $1, $3);}
	  | Rel TOR OpLog {$$ = initRel($2, NULL, $1, $3);}
	  | OpLog {$$ = $1;}
      ;

OpLog : FatorLog TMORE FatorLog {$$ = initRel($2, NULL, $1, $3);}
      | FatorLog TLESS FatorLog {$$ = initRel($2, NULL, $1, $3);} 
      | FatorLog TEQUAL FatorLog {$$ = initRel($2, NULL, $1, $3);}
      | FatorLog TDIFF FatorLog {$$ = initRel($2, NULL, $1, $3);}
      | FatorLog {$$ = $1;}
      ;

FatorLog: TNUM {$$ = initRel(NULL, $1, NULL, NULL);}
        | ID {$$ = initRel(NULL, $1, NULL, NULL);}

Programa : ListaFuncoes BlocoPrincipal {$$ = initPrograma($1, $2);}
         | BlocoPrincipal {$$ = initPrograma(NULL, $1);}
         ;

ListaFuncoes : ListaFuncoes Funcao {$$ = createFunc($1, $2);}
             | Funcao {$$ = $1;}
             ;

Funcao : TipoRetorno ID TAPAR DeclParametros TFPAR BlocoPrincipal {$$ = initListaDeFunc("Func", $1, $2, $4, $6);}
       | TipoRetorno ID TAPAR TFPAR BlocoPrincipal {$$ = initListaDeFunc("Func", $1, $2, NULL, $5);}
       ;

TipoRetorno : Tipo {$$ = $1;}
            | VOID {$$ = "void";}
            ;

DeclParametros : DeclParametros COMMA Parametro {$$ = createParam($1, $3);}
               | Parametro {$$ = $1;}
               ;

Parametro : Tipo ID {$$ = initParam($1, $2);}
          ;

BlocoPrincipal : LBRACE Declaracoes ListaCmd RBRACE {$$ = initBlocoPrincipal($2, NULL);}
               | LBRACE ListaCmd RBRACE {$$ = initBlocoPrincipal(NULL, NULL);}
               ;

Declaracoes : Declaracoes Declaracao {$$ = addDeclaracoes($1, $2);}
            | Declaracao {$$ = $1;}
            ;

Declaracao : Tipo ListaId SEMICOLON {$$ = initDeclaracoes($1, $2);}
           ;

Tipo : INT {$$ = "int";}
     | STRING {$$ = "string";}
     | FLOAT {$$ = "float";}
     ;


ListaId : ListaId COMMA ID {$$ = addListaId($1, $3);}
        | ID {$$ = initListaId($1);}
        ;

Bloco : LBRACE ListaCmd RBRACE
      ;

ListaCmd : ListaCmd Comando
         | Comando
         ;

Comando : CmdSe
        | CmdEnquanto
        | CmdAtrib
        | CmdEscrita
        | CmdLeitura
        | ChamadaProc
        | Retorno
        ;

Retorno : RETURN Expr SEMICOLON
        | RETURN ID SEMICOLON
        | RETURN SEMICOLON
        ;


CmdSe : IF TAPAR Rel TFPAR Bloco
      | IF TAPAR Rel TFPAR Bloco ELSE Bloco
      ;

CmdEnquanto : WHILE TAPAR Rel TFPAR Bloco
            ;

CmdAtrib : ID EQ Expr SEMICOLON
         | ID EQ ID SEMICOLON
         ;


CmdEscrita : PRINT TAPAR Expr TFPAR SEMICOLON {$$ = initEscrita("Escrita", "", $3);}
           | PRINT TAPAR ID TFPAR SEMICOLON {$$ = initEscrita("Escrita", $3, NULL);}
           ;

CmdLeitura : READ TAPAR ID TFPAR SEMICOLON
           ;

ChamadaProc : ChamaFuncao SEMICOLON {$$ = $1;}
            ;
ChamaFuncao : ID TAPAR ListaParametros TFPAR {$$ = initChamaFunc($1, $3);}
            | ID TAPAR TFPAR {$$ = initChamaFunc($1, NULL);}
            ;
ListaParametros : ListaParametros COMMA Expr {$$ = addListaParamChamafunc($1, NULL, $3);}
                | ListaParametros COMMA ID {$$ = addListaParamChamafunc($1, $3, NULL);}
                | Expr {$$ = initListaParamChamafunc(NULL, $1);}
                | ID {$$ = initListaParamChamafunc($1, NULL);}
                ;
%%

int yyerror(const char *str)
{
    fprintf(stderr, "%s\n", str);
    return 0; // Adicione um retorno para evitar warnings
}

