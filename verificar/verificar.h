
#ifndef verificar_h
#define verificar_h

#include "../room/room.h"
#include "../person/person.h"

int verifyFreeSpace(pRoom roomList, int total, int placeID);

int verifyInputValues(int age, char name[100], int DiasDoente, pPerson p);

pPerson verifyRoomChange(int N, int fromID, int toID, pPerson p, pRoom roomList, int total);

#endif

