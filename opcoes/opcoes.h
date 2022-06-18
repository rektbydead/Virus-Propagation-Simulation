
#ifndef opcoes_h
#define opcoes_h


void ApresentarEstatistica(pPerson p, pRoom roomList, int total);

pPerson addSickPerson(pRoom roomList, int total, pPerson listaPersons);

pPerson TransferirPersons(pRoom roomList, int total, pPerson listaPersons);

pPerson VoltarAtras(pPerson *ArrayPersons, pPerson listaPersons);

void EscreverNoFicheiro(pPerson listaPersons, pRoom roomList, int total,int IteracoesVezes,
                        int ApresentarEstatisticaVezes,int addSickPersonVezes,int TransferirPersonVezes, int VoltarAtrasVezes);

#endif

