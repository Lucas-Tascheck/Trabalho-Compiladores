#include "ast.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

int contador = 0;

ListaParam *initParam(char *tipo, char *id) {
    ListaParam *l = (ListaParam*)malloc(sizeof(ListaParam));
    l->tipo = tipo;
    l->id = id;
    l->prox = NULL;
    return l;
}

ListaParam *createParam(ListaParam *left, ListaParam *right) {
    ListaParam *p = left;
    while(p->prox != NULL) {
        p = p->prox;
    }
    p->prox = right;
    return left;
}

ListaDeFunc *initListaDeFunc(char *nodetype, char *tipo, char *id, ListaParam *lista, BlocoPrincipal *blocoPrincipal) {
    ListaDeFunc *l = (ListaDeFunc*)malloc(sizeof(ListaDeFunc));
    l->nodeType = nodetype;
    l->tipo = tipo;
    l->id = id;
    l->listaParam = lista;
    l->blocoPrincipal = blocoPrincipal;
    l->prox = NULL;
    return l;
}

ListaDeFunc *createFunc(ListaDeFunc *left, ListaDeFunc *right) {
    ListaDeFunc *p = left;
    while(p->prox != NULL) {
        p = p->prox;
    }
    p->prox = right;
    return left;
}

Declaracoes *initDeclaracoes(char *tipo, ListaId *listaId) {
    Declaracoes *declaracao = (Declaracoes*)malloc(sizeof(Declaracoes));
    declaracao->tipo = tipo;
    declaracao->listaId = listaId;
    declaracao->prox = NULL;
    return declaracao;
}

Declaracoes *addDeclaracoes(Declaracoes *left, Declaracoes *right) {
    Declaracoes *p = left;
    while(p->prox != NULL) {
        p = p->prox;
    }
    p->prox = right;
    return left;
}

BlocoPrincipal *initBlocoPrincipal(Declaracoes *declaracoes, Comando *listaDeCmd) {
    BlocoPrincipal *blocoPrincipal = (BlocoPrincipal*)malloc(sizeof(BlocoPrincipal));
    blocoPrincipal->listaDeDeclaracoes = declaracoes;
    blocoPrincipal->listaDeCmd = listaDeCmd;
    return blocoPrincipal;
}

Programa *initPrograma(ListaDeFunc *listaDeFunc, BlocoPrincipal *blocoPrincipal) {
    Programa *programa = (Programa*)malloc(sizeof(Programa));
    programa->listaDeFunc = listaDeFunc;
    programa->blocoPrincipal = blocoPrincipal;
    return programa;
}

ListaId *initListaId(char *id) {
    ListaId *listaId = (ListaId*)malloc(sizeof(ListaId));
    listaId->nodetype = "ListaId";
    listaId->id = id;
    listaId->index = contador++;
    listaId->prox = NULL;
    return listaId;
}

ListaId *addListaId(ListaId *left, char *right) {
    ListaId *p = left;
    ListaId *IdRight = initListaId(right);
    while(p->prox != NULL) {
        p = p->prox;
    }
    p->prox = IdRight;
    return left;
}

Rel *initRel(char *op, char *value, Rel *left, Rel *right) {
    Rel *rel = (Rel*)malloc(sizeof(Rel));
    rel->op = op;
    rel->value = value;
    rel->left = left;
    rel->right = right;
    return rel;
}

Expr *initExpr(char *op, char *value, ChamaFunc *chamaFunc, Expr *left, Expr *right) {
    Expr *expr = (Expr*)malloc(sizeof(Expr));
    expr->op = op;
    expr->value = value;
    expr->chamafunc = chamaFunc;
    expr->left = left;
    expr->right = right;
    return expr;
}

ListaParamChamafunc *initListaParamChamafunc(char *id, Expr *expr) {
    ListaParamChamafunc *listaParamChamafunc = (ListaParamChamafunc*)malloc(sizeof(ListaParamChamafunc));
    listaParamChamafunc->id = id;
    listaParamChamafunc->expr = expr;
    listaParamChamafunc->prox = NULL;
    return listaParamChamafunc;
}

ListaParamChamafunc *addListaParamChamafunc(ListaParamChamafunc *left, char *id, Expr *expr) {
    ListaParamChamafunc *p = left;
    ListaParamChamafunc *IdRight;
    IdRight = initListaParamChamafunc(NULL, expr);
    while(p->prox != NULL) {
        p = p->prox;
    }
    p->prox = IdRight;
    return left;
}

ChamaFunc *initChamaFunc(char *id, ListaParamChamafunc *listaParamChamafunc) {
    ChamaFunc *chamaFunc = (ChamaFunc*)malloc(sizeof(ChamaFunc));
    chamaFunc->id = id;
    chamaFunc->listaParamChamafunc = listaParamChamafunc;
    return chamaFunc;
}

Escrita *initEscrita(char *nodeType, char *id, Expr *expr) {
    Escrita *escrita = (Escrita*)malloc(sizeof(Escrita));
    escrita->nodeType = nodeType;
    escrita->id = id;
    escrita->expr = expr;
    return escrita;
}

Leitura *initLeitura(char *nodeType, char *id) {
    Leitura *leitura = (Leitura*)malloc(sizeof(Leitura));
    leitura->nodeType = nodeType;
    leitura->id = id;
    return leitura;
}

Atrib *initAtrib(char *id, char *id2, Expr *expr) {
    Atrib *atrib = (Atrib*)malloc(sizeof(Atrib));
    atrib->id = id;
    atrib->id2 = id2;
    atrib->expr = expr;
    return atrib;
}

Return *initReturn(char *nodeType, char *id, Expr *expr) {
    Return *returnn = (Return*)malloc(sizeof(Return));
    returnn->nodeType = nodeType;
    returnn->id = id;
    returnn->expr = expr;
    return returnn;
}

Comando *initComando(char *op, Ifstruct *ifstruct, Whilestruct *whilestruct, Atrib *atrib, Escrita *escrita, Leitura *leitura, ChamaFunc *chamaFunc, Return *returnn) {
    Comando *comando = (Comando*)malloc(sizeof(Comando));
    comando->op = op;
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

Comando *addComando(Comando *left, Comando *right) {
    Comando *c = left;
    while(c->prox != NULL) {
        c = c->prox;
    }
    c->prox = right;
    return left;
}

Ifstruct *initIf(char *nodeType, Rel *rel, Bloco *blocoIf, Bloco *blocoElse) {
    Ifstruct *ifstruct = (Ifstruct*)malloc(sizeof(Ifstruct));
    ifstruct->nodeType = nodeType;
    ifstruct->rel = rel;
    ifstruct->blocoIf = blocoIf;
    ifstruct->blocoElse = blocoElse;
    return ifstruct;
}

Whilestruct *initWhile(char *nodeType, Rel *rel, Bloco *blocoWhile) {
    Whilestruct *whileStruct = (Whilestruct*)malloc(sizeof(Whilestruct));
    whileStruct->nodeType = nodeType;
    whileStruct->rel = rel;
    whileStruct->blocoWhile = blocoWhile;
    return whileStruct;
}

Bloco *initBloco(char *nodeType, Comando *listaDeCmd) {
    Bloco *bloco = (Bloco*)malloc(sizeof(Bloco));
    bloco->nodeType = nodeType;
    bloco->listaDeCmd = listaDeCmd;
    return bloco;
}

FILE *outputFile;

void abrirArquivoJ(char *nomeArquivo) {
    outputFile = fopen(nomeArquivo, "w");
    if (outputFile == NULL) {
        perror("Erro ao abrir o arquivo .j");
        exit(1);
    }
}

void fecharArquivoJ() {
    fclose(outputFile);
}

void escreverNoArquivo(char *formato, ...) {
    va_list args;
    va_start(args, formato);
    vfprintf(outputFile, formato, args);
    va_end(args);
}

int evaluateExpr(Expr *expr) {
    if (expr == NULL) return 0;

    if (expr->op == NULL || strcmp(expr->op, "") == 0) {
        return atoi(expr->value);
    }

    int leftValue = evaluateExpr(expr->left);
    int rightValue = evaluateExpr(expr->right);

    if (strcmp(expr->op, "+") == 0) {
        return leftValue + rightValue;
    } else if (strcmp(expr->op, "-") == 0) {
        return leftValue - rightValue;
    } else if (strcmp(expr->op, "") == 0) {
        return leftValue * rightValue;
    } else if (strcmp(expr->op, "/") == 0) {
        return leftValue / rightValue;
    } else {
        return 0;
    }
}

void imprimeExpr(Expr *expr) {
    int result = evaluateExpr(expr);
    escreverNoArquivo("%d", result);
}

int avaliaRel(Rel *rel) {
    if (rel == NULL) {
        return 0;
    }

    if (rel->op == NULL || strcmp(rel->op, "") == 0) {
        return atoi(rel->value);
    }

    int left = avaliaRel(rel->left);
    int right = avaliaRel(rel->right);

    if (strcmp(rel->op, "&&") == 0) {
        return left && right;
    } else if (strcmp(rel->op, "||") == 0) {
        return left || right;
    } else if (strcmp(rel->op, "==") == 0) {
        return left == right;
    } else if (strcmp(rel->op, "!=") == 0) {
        return left != right;
    } else if (strcmp(rel->op, "<") == 0) {
        return left < right;
    } else if (strcmp(rel->op, "<=") == 0) {
        return left <= right;
    } else if (strcmp(rel->op, ">") == 0) {
        return left > right;
    } else if (strcmp(rel->op, ">=") == 0) {
        return left >= right;
    }

    return 0;
}

void imprimeRel(Rel *rel) {
    if (rel != NULL) {
        int resultado = avaliaRel(rel);
        escreverNoArquivo("%d", resultado);
    }
}

int encontraIndex(Declaracoes *l, char *var) {
    Declaracoes *decl = l;
    while(decl!=NULL){
        ListaId *p = decl->listaId;
        while(p != NULL) {
            if (strcmp(p->id, var) == 0) {
                return p->index;
            }
            p = p->prox;
        }
        decl = decl->prox;
    }
    printf("Variavel %s nao declarada\n", var);
    return -1;
}

ListaDeFunc *encontraFunc(ListaDeFunc *l, char *id){
    ListaDeFunc *p = l;
    while(p != NULL){
        if (strcmp(p->id, id) == 0) {
            return p;
        }
        p = p->prox;
    }
    p = NULL;
    return p;
}

int contadorDeIf = 0;
int contadorDeWhile = 0;

void imprimeListaCmd(Comando *listaDeCmd, Declaracoes *listaDeDeclaracoes, Programa *raiz) {
    if (listaDeCmd == NULL) {
        return;
    }
    if (strcmp(listaDeCmd->op, "If") == 0) {
        char labelIf[50] = "LabelEndIf";
        char labelElse[50] = "LabelElse";
        char labelEndElse[50] = "LabelEndElse";
        char contIf[10];
        sprintf(contIf, "%d", contadorDeIf);
        strcat(labelIf, contIf);
        strcat(labelElse, contIf);
        strcat(labelEndElse, contIf);
        if (!avaliaRel(listaDeCmd->ifstruct->rel)) {
            escreverNoArquivo("\ticonst_0\n");
        } else {
            escreverNoArquivo("\ticonst_1\n");
        }
        if (listaDeCmd->ifstruct->blocoElse != NULL) {
            escreverNoArquivo("\tifeq %s\n", labelElse);
            imprimeListaCmd(listaDeCmd->ifstruct->blocoIf->listaDeCmd, raiz->blocoPrincipal->listaDeDeclaracoes, raiz);
            escreverNoArquivo("\tgoto %s\n", labelEndElse);
            escreverNoArquivo("%s:\n", labelElse);
            imprimeListaCmd(listaDeCmd->ifstruct->blocoElse->listaDeCmd, raiz->blocoPrincipal->listaDeDeclaracoes, raiz);
            escreverNoArquivo("%s:\n", labelEndElse);
        }
        if (listaDeCmd->ifstruct->blocoElse == NULL) {
            escreverNoArquivo("\tifeq %s\n", labelIf);
            imprimeListaCmd(listaDeCmd->ifstruct->blocoIf->listaDeCmd, raiz->blocoPrincipal->listaDeDeclaracoes, raiz);
            escreverNoArquivo("%s:\n", labelIf);
        }
        contadorDeIf++;
    }

    if (strcmp(listaDeCmd->op, "While") == 0) {
        char labelWhile[50] = "LabelWhile";
        char labelEndWhile[50] = "LabelEndWhile";
        char contWhile[10];
        sprintf(contWhile, "%d", contadorDeWhile);
        strcat(labelWhile, contWhile);
        strcat(labelEndWhile, contWhile);
        escreverNoArquivo("%s:\n", labelWhile);
        int var1 = encontraIndex(raiz->blocoPrincipal->listaDeDeclaracoes, listaDeCmd->whilestruct->rel->left->value);
        int var2 = encontraIndex(raiz->blocoPrincipal->listaDeDeclaracoes, listaDeCmd->whilestruct->rel->right->value);
        if(var1 == -1){
            var1 = atoi(listaDeCmd->whilestruct->rel->left->value);
            escreverNoArquivo("\tbipush %d\n", var1);
        } else{
            escreverNoArquivo("\tiload %d\n", var1);
        }
        if(var2 == -1){
            var2 = atoi(listaDeCmd->whilestruct->rel->right->value);
            escreverNoArquivo("\tbipush %d\n", var2);
        } else{
            escreverNoArquivo("\tiload %d\n", var2);
        }
        if(strcmp(listaDeCmd->whilestruct->rel->op, ">") == 0){
            escreverNoArquivo("\tif_icmple %s\n", labelEndWhile);
        }
        if(strcmp(listaDeCmd->whilestruct->rel->op, ">=") == 0){
            escreverNoArquivo("\tif_icmplt %s\n", labelEndWhile);
        }
        if(strcmp(listaDeCmd->whilestruct->rel->op, "<") == 0){
            escreverNoArquivo("\tif_icmpge %s\n", labelEndWhile);
        }
        if(strcmp(listaDeCmd->whilestruct->rel->op, "<=") == 0){
            escreverNoArquivo("\tif_icmpgt %s\n", labelEndWhile);
        }
        imprimeListaCmd(listaDeCmd->whilestruct->blocoWhile->listaDeCmd, raiz->blocoPrincipal->listaDeDeclaracoes, raiz);
        if(strcmp(listaDeCmd->whilestruct->rel->op, ">") == 0 || strcmp(listaDeCmd->whilestruct->rel->op, ">=") == 0){
            escreverNoArquivo("\tiload %d\n", var1);
            escreverNoArquivo("\ticonst_1\n");
            escreverNoArquivo("\tisub\n");
            escreverNoArquivo("\tistore %d\n", var1);
        }else{
            escreverNoArquivo("\tiload %d\n", var1);
            escreverNoArquivo("\ticonst_1\n");
            escreverNoArquivo("\tiadd\n");
            escreverNoArquivo("\tistore %d\n", var1);
        }
        escreverNoArquivo("\tgoto %s\n", labelWhile);
        escreverNoArquivo("%s:\n\n", labelEndWhile);
        contadorDeWhile++;
    }
    if (strcmp(listaDeCmd->op, "Atrib") == 0) {
        if (strcmp(listaDeCmd->atrib->id2, "") != 0) {
            escreverNoArquivo("%s;\n", listaDeCmd->atrib->id2);
        }
        if (listaDeCmd->atrib->expr != NULL) {
            escreverNoArquivo("\tldc ");
            imprimeExpr(listaDeCmd->atrib->expr);
            escreverNoArquivo("\n\tistore %d\n\n", encontraIndex(raiz->blocoPrincipal->listaDeDeclaracoes, listaDeCmd->atrib->id));
        }
    }
    if (strcmp(listaDeCmd->op, "Escrita") == 0) {
        escreverNoArquivo("\tgetstatic java/lang/System/out Ljava/io/PrintStream;\n");
        escreverNoArquivo("\tiload %d\n", encontraIndex(raiz->blocoPrincipal->listaDeDeclaracoes, listaDeCmd->escrita->expr->value));
        escreverNoArquivo("\tinvokevirtual java/io/PrintStream/println(I)V\n\n");
    }
    if (strcmp(listaDeCmd->op, "Leitura") == 0) {
        escreverNoArquivo("\tread(%s);\n", listaDeCmd->leitura->id);
    }
    if (strcmp(listaDeCmd->op, "ChamaFunc") == 0) {
        ListaParamChamafunc *l = listaDeCmd->chamaFunc->listaParamChamafunc;
        while (l != NULL) {
            escreverNoArquivo("\tiload %d\n", encontraIndex(raiz->blocoPrincipal->listaDeDeclaracoes, l->expr->value));
            l = l->prox;
        }
        l = listaDeCmd->chamaFunc->listaParamChamafunc;
        escreverNoArquivo("\tinvokestatic Main/%s(", listaDeCmd->chamaFunc->id);
        while (l != NULL) {
            escreverNoArquivo("I");
            l = l->prox;
        }
        ListaDeFunc *f = encontraFunc(raiz->listaDeFunc, listaDeCmd->chamaFunc->id);
        if(strcmp(f->tipo, "int") == 0){
            escreverNoArquivo(")I\n");
        }
        if(strcmp(f->tipo, "void") == 0){
            escreverNoArquivo(")V\n");
        }
    }
    if (strcmp(listaDeCmd->op, "Return") == 0) {
        escreverNoArquivo("\tldc ");
        imprimeExpr(listaDeCmd->returnn->expr);
        escreverNoArquivo("\n\tireturn\n");
    }

    imprimeListaCmd(listaDeCmd->prox, raiz->blocoPrincipal->listaDeDeclaracoes, raiz);
}

void imprimeBlocoPrincipal(BlocoPrincipal *blocoPrincipal, Programa *raiz) {
    escreverNoArquivo("\t.limit stack 3\n\t.limit locals 8\n\n");
    Declaracoes *declaracoes = blocoPrincipal->listaDeDeclaracoes;
    ListaId *listaId = declaracoes->listaId;
    ListaId *listaId2 = declaracoes->listaId;
    while (declaracoes != NULL) {
        while (listaId->prox != NULL) {
            listaId = listaId->prox;
        }
        declaracoes = declaracoes->prox;
    }
    imprimeListaCmd(blocoPrincipal->listaDeCmd, raiz->blocoPrincipal->listaDeDeclaracoes, raiz);
}

void imprimeArvore(Programa *raiz) {
    abrirArquivoJ("output.j");
    escreverNoArquivo(".class public Main\n.super java/lang/Object\n\n.method public <init>()V\n\taload_0\n\tinvokespecial java/lang/Object/<init>()V\n\treturn\n.end method\n\n");

    ListaDeFunc *listaDeFunc = raiz->listaDeFunc;
    ListaParam *listaDeParam;
    while (listaDeFunc != NULL) {
        //escreverNoArquivo("%s %s(", listaDeFunc->tipo, listaDeFunc->id);
        escreverNoArquivo(".method public static %s(", listaDeFunc->id);
        listaDeParam = listaDeFunc->listaParam;
        if (listaDeParam == NULL) {
            escreverNoArquivo(")");
        } 
        else {
            while (listaDeParam != NULL) {
                if(strcmp(listaDeParam->tipo, "int") == 0){
                    escreverNoArquivo("I");
                }
                listaDeParam = listaDeParam->prox;
            }
            if(strcmp(listaDeFunc->tipo, "int") == 0){
                escreverNoArquivo(")I\n");
            }
            if(strcmp(listaDeFunc->tipo, "void") == 0){
                escreverNoArquivo(")V\n");
            }
        }
        BlocoPrincipal *blocoPrincipal = listaDeFunc->blocoPrincipal;
        imprimeBlocoPrincipal(blocoPrincipal, raiz);
        listaDeFunc = listaDeFunc->prox;
        escreverNoArquivo(".end method\n\n");
    }
    BlocoPrincipal *main = raiz->blocoPrincipal;
    escreverNoArquivo(".method public static main([Ljava/lang/String;)V\n");
    imprimeBlocoPrincipal(main, raiz);
    escreverNoArquivo("\treturn\n");
    escreverNoArquivo(".end method");
    fecharArquivoJ();
}