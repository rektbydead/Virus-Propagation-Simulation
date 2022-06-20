
#ifndef opcoes_h
#define opcoes_h

#include "../room/room.h"
#include "../person/person.h"

void showStatistics(pPerson p, pRoom roomList, int total);

pPerson addSickPerson(pRoom roomList, int total, pPerson listaPersons);

pPerson transferPersons(pRoom roomList, int total, pPerson listaPersons);

pPerson goBack(pPerson *ArrayPersons, pPerson listaPersons);

void writeToFile(pPerson p, pRoom roomList, int total, int nIterations, int nStatistics, int nSickPerson, int nTransfer, int nGoBack);

#endif

