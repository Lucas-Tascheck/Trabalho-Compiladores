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
      Expr *expr;
      Rel *rel;
}

%define parse.error verbose
%token STRING
%token INT FLOAT VOID
%token IF ELSE WHILE PRINT READ RETURN
%token SEMICOLON COMMA LBRACE RBRACE
%token TADD TMUL TSUB TDIV EQ TAPAR TFPAR TNUM TLESS TMORE TEQUAL TDIFF TAND TOR TFIM ID
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
%type <Expr> Expr 
%type <Rel> Rel 
%type <listaId> ListaId
%%

Linha : Programa {printf("%s", $1->listaDeFunc->tipo);}
      ; 

Expr  : Expr TADD Termo
      | Expr TSUB Termo
      | Termo
      ;


Termo : Termo TMUL Fator
      | Termo TDIV Fator
      | Fator
      | ChamaFuncao
      ;

Fator : TNUM 
      | TAPAR Expr TFPAR 
      ;

Rel   : Rel TAND OpLog
	  | Rel TOR OpLog
	  | OpLog
      ;

OpLog : FatorLog TMORE FatorLog
      | FatorLog TLESS FatorLog
      | FatorLog TEQUAL FatorLog
      | FatorLog TDIFF FatorLog
      | FatorLog
      ;

FatorLog: TNUM
        | ID

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

