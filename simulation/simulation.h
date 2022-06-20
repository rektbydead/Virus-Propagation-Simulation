
#ifndef simulation_h
#define simulation_h

#include "../room/room.h"
#include "../person/person.h"

pPerson spreadRate(pPerson p, pRoom roomList, int total);

pPerson recovery(pPerson p);

pPerson maxDuration(pPerson p);

int immunity();

pPerson nextIteration(pPerson p, pRoom roomList, int total);

#endif

