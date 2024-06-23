#include "ast.h"
#include <stdio.h>
#include <stdlib.h>

ListaParam *initParam(char *tipo, char *id){
    ListaParam *l = (ListaParam*)malloc(sizeof(ListaParam));
    l->tipo = tipo;
    l->id = id;
    l->prox = NULL;
    return l;
}

ListaParam *createParam(ListaParam *left, ListaParam *right){
    ListaParam *p = left;
    while(p->prox != NULL){
        p = p->prox;
    }
    p->prox = right;
    return left;
}

ListaDeFunc *initListaDeFunc(char *nodetype, char *tipo, char *id, ListaParam *lista, BlocoPrincipal *blocoPrincipal){
    ListaDeFunc *l = (ListaDeFunc*)malloc(sizeof(ListaDeFunc));
    l->nodeType = nodetype;
    l->tipo = tipo;
    l->id = id;
    l->listaParam = lista;
    l->blocoPrincipal = blocoPrincipal;
    l->prox = NULL;
    return l;
}

ListaDeFunc *createFunc(ListaDeFunc *left, ListaDeFunc *right){
    ListaDeFunc *p = left;
    while(p->prox != NULL){
        p = p->prox;
    }
    p->prox = right;
    return left;
}

Declaracoes *initDeclaracoes(char *tipo, ListaId *listaId){
    Declaracoes *declaracao = (Declaracoes*)malloc(sizeof(Declaracoes));
    declaracao->tipo = tipo;
    declaracao->listaId = listaId;
    declaracao->prox = NULL;
    return declaracao;
}

Declaracoes *addDeclaracoes(Declaracoes *left, Declaracoes *right){
    Declaracoes *p = left;
    while(p->prox != NULL){
        p = p->prox;
    }
    p->prox = right;
    return left;
}

BlocoPrincipal *initBlocoPrincipal(Declaracoes *declaracoes, ListaDeCmd *listaDeCmd){
    BlocoPrincipal *blocoPrincipal = (BlocoPrincipal*)malloc(sizeof(BlocoPrincipal));
    blocoPrincipal->listaDeDeclaracoes = declaracoes;
    blocoPrincipal->listaDeCmd = listaDeCmd;
    return blocoPrincipal;
}

Programa *initPrograma(ListaDeFunc *listaDeFunc, BlocoPrincipal *blocoPrincipal){
    Programa *programa = (Programa*)malloc(sizeof(Programa));
    programa->listaDeFunc = listaDeFunc;
    programa->blocoPrincipal = blocoPrincipal;
    return programa;
}

ListaId *initListaId(char *id){
    ListaId *listaId = (ListaId*)malloc(sizeof(ListaId));
    listaId->nodetype = "ListaId";
    listaId->id = id;
    listaId->prox = NULL;
}

ListaId *addListaId(ListaId *left, char *right){
    ListaId *p = left;
    ListaId *IdRight = initListaId(right);
    while(p->prox != NULL){
        p = p->prox;
    }
    p->prox = IdRight;
    return left;
}