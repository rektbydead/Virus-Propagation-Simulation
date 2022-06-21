
#ifndef simulacao_h
#define simulacao_h


ppessoa TaxaDeDisseminacao(ppessoa p, local *locais, int total);

ppessoa Recupercao(ppessoa p);

ppessoa DuracaoMaxima(ppessoa p);

int Imunidade();

ppessoa ProximaIteracao(ppessoa p, local *locais, int total);

#endif

