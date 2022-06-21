
#ifndef sala_h
#define sala_h

typedef struct local local, *plocal;
struct local {
    int id; // id numérico do local
    int capacidade; // capacidade máxima
    int liga[3]; // id das ligações (-1 nos casos não usados)
};

typedef struct localAS localAS, *plocalAS; //AJUDA NA VERIFICAÇÃO DA CAPACIDADE DAS SALAS
struct localAS {
    int id; // id numérico do local
    int capacidade; // capacidade máxima
};

local *listarFicheiroLocal(char *nomeFich, int *total);

void escreverLocal(local c);

int verificarLocais(local *locais, int total);

#endif

