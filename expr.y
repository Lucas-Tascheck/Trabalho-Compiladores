%{
#include "ast.h"
int yyerror(const char *);
int yylex();

#define YYSTYPE struct Types

struct Types {
      double doubleNum;
      char *stringVal;
      Programa *programa;
      ListaDeFunc *listaDeFunc;
      ListaParam *listaParam;
      Declaracoes *declaracoes;
      ListaDeCmd *listaDeCmd;
};
%}


%define parse.error verbose
%token STRING
%token INT FLOAT VOID
%token IF ELSE WHILE PRINT READ RETURN
%token SEMICOLON COMMA LBRACE RBRACE
%token TADD TMUL TSUB TDIV EQ TAPAR TFPAR TNUM TLESS TMORE TEQUAL TDIFF TAND TOR TFIM ID

%type <yylval.stringVal> STRING
%type <yylval.stringVal> INT
%type <yylval.stringVal> FLOAT
%type <yylval.stringVal> VOID
%type <yylval.doubleNum> IF
%type <yylval.doubleNum> ELSE
%type <yylval.doubleNum> WHILE
%type <yylval.doubleNum> PRINT
%type <yylval.doubleNum> READ
%type <yylval.doubleNum> RETURN
%type <yylval.doubleNum> SEMICOLON
%type <yylval.doubleNum> COMMA
%type <yylval.doubleNum> TADD
%type <yylval.doubleNum> TMUL
%type <yylval.doubleNum> TSUB
%type <yylval.doubleNum> TDIV
%type <yylval.doubleNum> EQ
%type <yylval.doubleNum> TAPAR
%type <yylval.doubleNum> TFPAR
%type <yylval.doubleNum> TNUM
%type <yylval.doubleNum> TLESS
%type <yylval.doubleNum> TMORE
%type <yylval.doubleNum> TEQUAL
%type <yylval.doubleNum> TAND
%type <yylval.doubleNum> TOR
%type <yylval.doubleNum> TFIM
%type <yylval.stringVal> ID
%type <yylval.listaDeFunc> Programa
%type <yylval.listaDeFunc> Linha
%type <yylval.listaDeFunc> ListaFuncoes
%type <yylval.listaDeFunc> Funcao
%type <yylval.listaParam> DeclParametros 
%type <yylval.listaParam> Parametro
%type <yylval.doubleNum> Termo
%type <yylval.doubleNum> Fator
%type <yylval.stringVal> TipoRetorno
%type <yylval.stringVal> Tipo


%%

Linha : Programa {printf("%s", $1->id);}
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


Programa : ListaFuncoes { $$ = $1; }
         ;

ListaFuncoes : ListaFuncoes Funcao {$$ = createFunc($1, $2);}
             | Funcao {$$ = $1;}
             ;

Funcao : TipoRetorno ID TAPAR DeclParametros TFPAR BlocoPrincipal {$$ = initListaDeFunc("Func", $1, $2, $4);}
       | TipoRetorno ID TAPAR TFPAR BlocoPrincipal {$$ = initListaDeFunc("Func", $1, $2, NULL);}
       ;

TipoRetorno : Tipo
            | VOID
            ;

DeclParametros : DeclParametros COMMA Parametro {$$ = createParam($1, $3);}
               | Parametro {$$ = $1;}
               ;

Parametro : Tipo ID {$$ = initParam($1, $2);}
          ;

BlocoPrincipal : LBRACE Declaracoes ListaCmd RBRACE
               | LBRACE ListaCmd RBRACE
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
