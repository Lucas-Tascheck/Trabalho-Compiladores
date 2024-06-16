typedef struct Ifstruct Ifstruct;
typedef struct Whilestruct Whilestruct;
typedef struct ListaDeCmd ListaDeCmd;
typedef struct Declaracoes Declaracoes;
typedef struct ListaParam ListaParam;

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

typedef struct ListaDeFunc {
    char *nodeType;
    char *tipo;
    char *id;
    ListaParam *listaParam;
    ListaDeFunc *prox;
} ListaDeFunc;

typedef struct Bloco {
    char *nodeType;
} Bloco;

typedef struct Programa {
    char *nodeType;
    ListaDeFunc *listaDeFunc;
    Bloco *bloco;
} Programa;