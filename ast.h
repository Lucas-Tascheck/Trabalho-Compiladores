#ifndef __AST_H__
#define __AST_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct ListaDeCmd ListaDeCmd;
typedef struct Declaracoes Declaracoes;
typedef struct ListaParam ListaParam;
typedef struct ListaDeFunc ListaDeFunc;
typedef struct BlocoPrincipal BlocoPrincipal;
typedef struct ListaId ListaId;
typedef struct ListaParamChamafunc ListaParamChamafunc;
typedef struct Rel Rel;
typedef struct Expr Expr;

typedef enum Tag {If, While, Atrib, Escrita, Leitura} Tag;

typedef struct Bloco {
    char *nodeType;
    ListaDeCmd *listaDeCmd;
} Bloco;

struct ListaParamChamafunc {
    char *id;
    Expr *expr;
    ListaParamChamafunc *prox;
};

struct ChamaFunc {
    char *id;
    ListaParamChamafunc *listaParamChamafunc;
}ChamaFunc;

typedef struct Ifstruct {
    char *nodeType;
    Rel *rel;
    Bloco *blocoIf;
    Bloco *blocoElse;
}Ifstruct;

typedef struct Whilestruct {
    char *nodeType;
    Rel *rel;
    Bloco *blocoWhile;
}Whilestruct;

typedef struct CmdAtrib {
    char *nodeType;
    char *id;

}CmdAtrib;

typedef union Union {
  Ifstruct *If;
  Whilestruct *While;
} Union;

struct Rel {
    char *op;
    char *value;
    Rel *left;
    Rel *right;
};

struct Expr {
    char *op;
    char *value;
    Expr *left;
    Expr *right;
};

struct ListaDeCmd {
    Tag tag;
    Union value;
    ListaDeCmd *prox;
};

struct Declaracoes {
    char *nodeType;
    char *tipo;
    ListaId *listaId;
    Declaracoes *prox;
};

struct ListaParam {
    char *tipo;
    char *id;
    ListaParam *prox;
};

struct ListaDeFunc {
    char *nodeType;
    char *tipo;
    char *id;
    ListaParam *listaParam;
    BlocoPrincipal *blocoPrincipal;
    ListaDeFunc *prox;
};

struct ListaId {
    char *nodetype;
    char *id;
    ListaId *prox;
};

typedef struct BlocoPrincipal {
    char *nodeType;
    Declaracoes *listaDeDeclaracoes;
    ListaDeCmd *listaDeCmd;
} BlocoPrincipal;


typedef struct Programa {
    char *nodeType;
    ListaDeFunc *listaDeFunc;
    BlocoPrincipal *blocoPrincipal;
} Programa;

Programa *initPrograma(ListaDeFunc *listaDeFunc, BlocoPrincipal *blocoPrincipal);
ListaParam *initParam(char *tipo, char *id);
ListaParam *createParam(ListaParam *left, ListaParam *right);
ListaDeFunc *initListaDeFunc(char *nodetype, char *tipo, char *id, ListaParam *lista, BlocoPrincipal *blocoPrincipal);
ListaDeFunc *createFunc(ListaDeFunc *left, ListaDeFunc *right);
Declaracoes *initDeclaracoes(char *tipo, ListaId *listaId);
Declaracoes *addDeclaracoes(Declaracoes *left, Declaracoes *right);
BlocoPrincipal *initBlocoPrincipal(Declaracoes *declaracoes, ListaDeCmd *listaDeCmd);
Programa *initPrograma(ListaDeFunc *listaDeFunc, BlocoPrincipal *blocoPrincipal);
ListaId *initListaId(char *id);
ListaId *addListaId(ListaId *left, char *right);
Rel *initRel(char *op, char *value, Rel *left, Rel *right);
Expr *initExpr(char *op, char *value, Expr *left, Expr *right);
ListaParamChamafunc *initListaParamChamafunc(char *id, Expr *expr);
ListaParamChamafunc *addListaParamChamafunc(ListaParamChamafunc *left, char *id, Expr *expr);
ChamaFunc *initChamaFunc(char *id, ListaParamChamafunc *listaParamChamafunc);

#endif