
#ifndef opcoes_h
#define opcoes_h


void ApresentarEstatistica(ppessoa p, local *locais, int total);

ppessoa AdicionarDoente(local *listaSalas, int total, ppessoa listaPessoas);

ppessoa TransferirPessoas(local *listaSalas, int total, ppessoa listaPessoas);

ppessoa VoltarAtras(ppessoa *ArrayPessoas, ppessoa listaPessoas);

void EscreverNoFicheiro(ppessoa listaPessoas, local *listaSalas, int total,int IteracoesVezes,
                        int ApresentarEstatisticaVezes,int AdicionarDoenteVezes,int TransferirPessoaVezes, int VoltarAtrasVezes);

#endif

