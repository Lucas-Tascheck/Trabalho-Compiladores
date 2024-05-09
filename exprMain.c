#include <stdio.h>
#include <stdlib.h>
#include "expr.tab.h"


extern FILE *yyin;

int main()
{
	FILE *input_file = fopen("./codigo.txt", "r");
    FILE *output_file = fopen("./input.txt", "w");

    if (input_file == NULL || output_file == NULL) {
        fprintf(stderr, "Erro ao abrir os arquivos.\n");
        return 1;
    }

    int c;
    while ((c = fgetc(input_file)) != EOF) {
        if (c != '\n') {
            fputc(c, output_file); // Escreve o caractere no arquivo de saída, exceto se for uma quebra de linha
        }
    }

    fclose(input_file);
    fclose(output_file);
	yyin = fopen("./input.txt", "r");
	yyparse();
	return 0;
}

