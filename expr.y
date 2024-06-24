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
      BlocoPrincipal *blocoPrincipal;
      ListaId *listaId;
      ListaParamChamafunc *listaParamChamafunc;
      ChamaFunc *chamaFunc;
      Escrita *escrita;
      Leitura *leitura;
      Atrib *atrib;
      Return *returnn;
      Comando *comando;
      Ifstruct *ifStruct;
      Whilestruct *whilestruct;
      Bloco *bloco;
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
%type <escrita> CmdEscrita
%type <leitura> CmdLeitura
%type <atrib> CmdAtrib
%type <returnn> Retorno
%type <comando> Comando
%type <comando> ListaCmd
%type <ifStruct> CmdSe
%type <whilestruct> CmdEnquanto
%type <bloco> Bloco
%%

Linha : Programa {imprimeArvore($1);}
      ; 

Expr  : Expr TADD Termo {$$ = initExpr("+", "", NULL, $1, $3);}
      | Expr TSUB Termo {$$ = initExpr("-", "", NULL, $1, $3);}
      | Termo {$$ = $1;}
      ;


Termo : Termo TMUL Fator {$$ = initExpr("*", "", NULL, $1, $3);}
      | Termo TDIV Fator {$$ = initExpr("/", "", NULL, $1, $3);}
      | Fator {$$ = $1;}
      | ChamaFuncao {$$ = initExpr("", "", $1, NULL, NULL);}
      ;

Fator : TNUM {$$ = initExpr("", $1, NULL, NULL, NULL);}
      | ID {$$ = initExpr("", $1, NULL, NULL, NULL);}
      | TAPAR Expr TFPAR {$$ = $2;}
      ;

Rel   : Rel TAND OpLog {$$ = initRel("&&", "", $1, $3);}
	  | Rel TOR OpLog {$$ = initRel("||", "", $1, $3);}
	  | OpLog {$$ = $1;}
      ;

OpLog : FatorLog TMORE FatorLog {$$ = initRel(">", "", $1, $3);}
      | FatorLog TLESS FatorLog {$$ = initRel("<", "", $1, $3);} 
      | FatorLog TEQUAL FatorLog {$$ = initRel("==", "", $1, $3);}
      | FatorLog TDIFF FatorLog {$$ = initRel("!=", "", $1, $3);}
      | FatorLog {$$ = $1;}
      ;

FatorLog: TNUM {$$ = initRel("", $1, NULL, NULL);}
        | ID {$$ = initRel("", $1, NULL, NULL);}

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

BlocoPrincipal : LBRACE Declaracoes ListaCmd RBRACE {$$ = initBlocoPrincipal($2, $3);}
               | LBRACE ListaCmd RBRACE {$$ = initBlocoPrincipal(NULL, $2);}
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

Bloco : LBRACE ListaCmd RBRACE {$$ = initBloco("Bloco", $2);}
      ;

ListaCmd : ListaCmd Comando {$$ = addComando($1, $2);}
         | Comando {$$ = $1;}
         ;

Comando : CmdSe {$$ = initComando("If", $1, NULL, NULL, NULL, NULL, NULL, NULL); }
        | CmdEnquanto {$$ = initComando("While", NULL, $1, NULL, NULL, NULL, NULL, NULL); }
        | CmdAtrib {$$ = initComando("Atrib", NULL, NULL, $1, NULL, NULL, NULL, NULL); }
        | CmdEscrita {$$ = initComando("Escrita", NULL, NULL, NULL, $1, NULL, NULL, NULL); }
        | CmdLeitura {$$ = initComando("Leitura", NULL, NULL, NULL, NULL, $1, NULL, NULL); }
        | ChamadaProc {$$ = initComando("ChamaFunc", NULL, NULL, NULL, NULL, NULL, $1, NULL); }
        | Retorno {$$ = initComando("Return", NULL, NULL, NULL, NULL, NULL, NULL, $1); }
        ;

Retorno : RETURN Expr SEMICOLON {$$ = initReturn("Return", "", $2);}
        | RETURN ID SEMICOLON {$$ = initReturn("Return", $2, NULL);}
        | RETURN SEMICOLON {$$ = initReturn("Return", "", NULL);}
        ;


CmdSe : IF TAPAR Rel TFPAR Bloco {$$ = initIf("If", $3, $5, NULL);}
      | IF TAPAR Rel TFPAR Bloco ELSE Bloco {$$ = initIf("If", $3, $5, $7);}
      ;

CmdEnquanto : WHILE TAPAR Rel TFPAR Bloco {$$ = initWhile("While", $3, $5);}
            ;

CmdAtrib : ID EQ Expr SEMICOLON {$$ = initAtrib($1, "", $3);}
         | ID EQ ID SEMICOLON {$$ = initAtrib($1, $3, NULL);}
         ;


CmdEscrita : PRINT TAPAR Expr TFPAR SEMICOLON {$$ = initEscrita("Escrita", "", $3);}
           | PRINT TAPAR ID TFPAR SEMICOLON {$$ = initEscrita("Escrita", $3, NULL);}
           ;

CmdLeitura : READ TAPAR ID TFPAR SEMICOLON {$$ = initLeitura("Leitura", $3);}
           ;

ChamadaProc : ChamaFuncao SEMICOLON {$$ = $1;}
            ;
ChamaFuncao : ID TAPAR ListaParametros TFPAR {$$ = initChamaFunc($1, $3);}
            | ID TAPAR TFPAR {$$ = initChamaFunc($1, NULL);}
            ;
ListaParametros : ListaParametros COMMA Expr {$$ = addListaParamChamafunc($1, NULL, $3);}
                | Expr {$$ = initListaParamChamafunc(NULL, $1);}
                ;
%%

int yyerror(const char *str)
{
    fprintf(stderr, "%s\n", str);
    return 0; // Adicione um retorno para evitar warnings
}

