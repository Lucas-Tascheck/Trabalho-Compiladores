all: main

expr.tab.c expr.tab.h: expr.y ast.h
	bison -d expr.y

lex.yy.c: expr.l
	flex expr.l

main: lex.yy.c expr.tab.c ast.c exprMain.c ast.h
	gcc -o expr lex.yy.c expr.tab.c exprMain.c ast.c -lfl

clean: 
	rm -f lex.yy.c expr.tab.c expr.tab.h expr
