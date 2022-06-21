
#ifndef pessoas_h
#define pessoas_h

typedef struct pessoa pessoa, *ppessoa;
struct pessoa {
    char nome[100];
    int idade;
    char estado;
    int DiasDoente; //0 se não estiver doente
    int localID;
    ppessoa prox;
};

ppessoa lerFicheiroPessoa(char *nomeFich, ppessoa p);

void escreverPessoa(ppessoa c);

void liberarpessoas(ppessoa c);

ppessoa inserirPessoa(ppessoa p, ppessoa pPessoa);

void mostraTudo(ppessoa c);

ppessoa atribuirLocais(ppessoa p, local *s, int total);

#endif

