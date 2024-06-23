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

BlocoPrincipal *initBlocoPrincipal(Declaracoes *declaracoes, Comando *listaDeCmd){
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

Rel *initRel(char *op, char *value, Rel *left, Rel *right){
    Rel *rel = (Rel*)malloc(sizeof(Rel));
    rel->op = op;
    rel->value = value;
    rel->left = left;
    rel->right = right;
    return rel;
}

Expr *initExpr(char *op, char *value, ChamaFunc *chamaFunc, Expr *left, Expr *right){
    Expr *expr = (Expr*)malloc(sizeof(Expr));
    expr->op = op;
    expr->value = value;
    expr->chamafunc = chamaFunc;
    expr->left = left;
    expr->right = right;
    return expr;
}

ListaParamChamafunc *initListaParamChamafunc(char *id, Expr *expr){
    ListaParamChamafunc *listaParamChamafunc = (ListaParamChamafunc*)malloc(sizeof(ListaParamChamafunc));
    listaParamChamafunc->id = id;
    listaParamChamafunc->expr = expr;
    listaParamChamafunc->prox = NULL;
    return listaParamChamafunc;
}

ListaParamChamafunc *addListaParamChamafunc(ListaParamChamafunc *left, char *id, Expr *expr){
    ListaParamChamafunc *p = left;
    ListaParamChamafunc *IdRight;
    if(id == ""){
        IdRight = initListaParamChamafunc(NULL, expr);
    }else{
        IdRight = initListaParamChamafunc(id, NULL);
    }
    while(p->prox != NULL){
        p = p->prox;
    }
    p->prox = IdRight;
    return left;
}

ChamaFunc *initChamaFunc(char *id, ListaParamChamafunc *listaParamChamafunc){
    ChamaFunc *chamaFunc = (ChamaFunc*)malloc(sizeof(ChamaFunc));
    chamaFunc->id = id;
    chamaFunc->listaParamChamafunc = listaParamChamafunc;
    return chamaFunc;
}

Escrita *initEscrita(char *nodeType, char *id, Expr *expr){
    Escrita *escrita = (Escrita*)malloc(sizeof(Escrita));
    escrita->nodeType = nodeType;
    escrita->id = id;
    escrita->expr = expr;
}

Leitura *initLeitura(char *nodeType, char *id){
    Leitura *leitura = (Leitura*)malloc(sizeof(Leitura));
    leitura->nodeType = nodeType;
    leitura->id = id;
}

Atrib *initAtrib(char *id, char *id2, Expr *expr){
    Atrib *atrib = (Atrib*)malloc(sizeof(Atrib));
    atrib->id = id;
    if(id2 != ""){
        atrib->id2 = id2;
    }
    atrib->expr = expr;
    return atrib;
}

Return *initReturn(char *nodeType, char *id, Expr *expr){
    Return *returnn = (Return*)malloc(sizeof(Return));
    returnn->nodeType = nodeType;
    returnn->id = id;
    returnn->expr = expr;
}

Comando *initComando(char *op, Ifstruct *ifstruct, Whilestruct *whilestruct, Atrib *atrib, Escrita *escrita, Leitura *leitura, ChamaFunc *chamaFunc, Return *returnn){
    Comando *comando = (Comando*)malloc(sizeof(Comando));
    comando->atrib = atrib;
    comando->chamaFunc = chamaFunc;
    comando->escrita = escrita;
    comando->leitura = leitura;
    comando->ifstruct = ifstruct;
    comando->returnn = returnn;
    comando->whilestruct = whilestruct;
    comando->prox = NULL;
    return comando;
}

Comando *addComando(Comando *left, Comando *right){
    Comando *c = left;
    while(c->prox != NULL){
        c = c->prox;
    }
    c->prox = right;
    return left;
}

Ifstruct *initIf(char *nodeType, Rel *rel, Bloco *blocoIf, Bloco *blocoElse){
    Ifstruct *ifstruct = (Ifstruct*)malloc(sizeof(Ifstruct));
    ifstruct->nodeType = nodeType;
    ifstruct->rel = rel;
    ifstruct->blocoIf = blocoIf;
    ifstruct->blocoElse = blocoElse;
    return ifstruct;
}

Whilestruct *initWhile(char *nodeType, Rel *rel, Bloco *blocoWhile){
    Whilestruct *whileStruct = (Whilestruct*)malloc(sizeof(Whilestruct));
    whileStruct->nodeType = nodeType;
    whileStruct->rel = rel;
    whileStruct->blocoWhile = blocoWhile;
}

Bloco *initBloco(char *nodeType, Comando *listaDeCmd){
    Bloco *bloco = (Bloco*)malloc(sizeof(Bloco));
    bloco->nodeType = nodeType;
    bloco->listaDeCmd = listaDeCmd;
    return bloco;
}