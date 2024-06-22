#ifndef __AST_H__
#define __AST_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Ifstruct Ifstruct;
typedef struct Whilestruct Whilestruct;
typedef struct ListaDeCmd ListaDeCmd;
typedef struct Declaracoes Declaracoes;
typedef struct ListaParam ListaParam;
typedef struct ListaDeFunc ListaDeFunc;
typedef struct BlocoPrincipal BlocoPrincipal;

typedef enum Tag {If, While, Atrib, Escrita, Leitura, ChamaFunc} Tag;

struct Ifstruct {
    char *nodeType;
    char op;
    Ifstruct *esq;
    Ifstruct *dir;
};

struct Whilestruct {
    char op;
    Whilestruct *esq;
    Whilestruct *dir;
};

typedef union Union {
  Ifstruct *If;
  Whilestruct *While;
} Union;

struct ListaDeCmd {
    Tag tag;
    Union value;
    ListaDeCmd *prox;
};

struct Declaracoes {
    char *nodeType;
    char *tipo;
    char *id;
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

Programa *initPrograma();
ListaParam *initParam(char *tipo, char *id);
Programa *addListaDeFunc(ListaDeFunc *nodo);
ListaParam *createParam(ListaParam *left, ListaParam *right);
ListaDeFunc *initListaDeFunc(char *nodetype, char *tipo, char *id, ListaParam *lista, BlocoPrincipal *blocoPrincipal);
ListaDeFunc *createFunc(ListaDeFunc *left, ListaDeFunc *right);
Declaracoes *initDeclaracoes(char *tipo, char *id);
Declaracoes *addDeclaracoes(Declaracoes *left, Declaracoes *right);
BlocoPrincipal *initBlocoPrincipal(Declaracoes *declaracoes, ListaDeCmd *listaDeCmd);
Programa *initPrograma(ListaDeFunc *listaDeFunc, BlocoPrincipal *blocoPrincipal);

#endif