#include "ast.h"
#include <stdio.h>
#include <stdlib.h>

Programa *initPrograma(){
    Programa *p = (Programa*)malloc(sizeof(Programa));
    p->bloco = NULL;
    p->listaDeFunc = NULL;
    p->nodeType = "Programa";
    return p;
}

ListaParam *initParam(char *tipo, char *id){
    ListaParam *l = (ListaParam*)malloc(sizeof(ListaParam));
    l->tipo = tipo;
    l->id = id;
    l->prox = NULL;
    return l;
}

ListaParam *createParam(ListaParam *left, ListaParam *right){
    right->prox = left;
    return right;
}

ListaDeFunc *initListaDeFunc(char *nodetype, char *tipo, char *id, ListaParam *lista){
    ListaDeFunc *l = (ListaDeFunc*)malloc(sizeof(ListaDeFunc));
    l->nodeType = nodetype;
    l->tipo = tipo;
    l->id = id;
    l->listaParam = lista;
    l->prox = NULL;
    return l;
}

ListaDeFunc *createFunc(ListaDeFunc *left, ListaDeFunc *right){
    right->prox = left;
    return right;
}

Programa *addListaDeFunc(ListaDeFunc *nodo){

}