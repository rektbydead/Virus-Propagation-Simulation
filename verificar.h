
#ifndef verificar_h
#define verificar_h


int VerificarSeTemEspacoLivre(local *listaSalas, int total, int localID, ppessoa p);

int VerificarValores(int idade, char nome[100], int DiasDoente, ppessoa p);

ppessoa VerificarTrocarLocais(int N, int DestinoID, int OrigemID, ppessoa p, local *listaSalas, int total);

#endif

