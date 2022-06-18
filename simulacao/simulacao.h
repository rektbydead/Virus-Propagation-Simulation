
#ifndef simulacao_h
#define simulacao_h


pPerson TaxaDeDisseminacao(pPerson p, pRoom roomList, int total);

pPerson Recupercao(pPerson p);

pPerson DuracaoMaxima(pPerson p);

int Imunidade();

pPerson nextimaIteracao(pPerson p, pRoom roomList, int total);

#endif

