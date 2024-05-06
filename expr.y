%{
#define YYSTYPE double
#include <stdio.h>
#include <stdlib.h>

int yyerror(const char *);
int yylex();

%}
%define parse.error verbose

%token TADD TMUL TSUB TDIV TAPAR TFPAR TNUM TLESS TMORE TEQUAL TDIFF TFIM

%%
Linha :Expr TFIM {printf("Resultado:%lf\n", $1);exit(0);}
	| Rel TFIM { if ($1 != 0) printf("True"); else printf("False"); exit(0);}
	; 
Expr: Expr TADD Termo {$$ = $1 + $3;}
	| Expr TSUB Termo {$$ = $1 - $3;}
	| Termo
	;
Termo: Termo TMUL Fator {$$ = $1 * $3;}
	| Termo TDIV Fator {$$ = $1 / $3;}
	| Fator
	;
Fator: TNUM 
	| TAPAR Expr TFPAR {$$ = $2;}
	;
Rel: TNUM TMORE TNUM {}
	| TNUM TLESS TNUM {}
	| TNUM TEQUAL TEQUAL TNUM {}
	| TNUM TDIFF TEQUAL TNUM {}
%%

int yyerror (const char *str)
{
	fprintf(stderr, "%s\n", str);
	
} 		 

