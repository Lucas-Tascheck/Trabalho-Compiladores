#include <stdio.h>
#include <stdlib.h>
#include "expr.tab.h"


extern FILE *yyin;

int main()
{
	yyin = fopen("./codigo.txt", "r");
	yyparse();
	return 0;
}

