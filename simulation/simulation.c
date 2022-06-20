
#include <stdio.h>
#include <stdlib.h>

#include "../utils/utils.h"
#include "../person/person.h"
#include "../room/room.h"
#include "../simulation/simulation.h"
#include "../options/options.h"

pPerson nextIteration(pPerson p, pRoom roomList, int total) {
    p = spreadRate(p, roomList, total);
    p = recovery(p);
    p = maxDuration(p);
    return p;
}

pPerson spreadRate(pPerson p, pRoom roomList, int total) {
    for (int i = 0; i < total; i++) {
        pPerson aux = p;

        int counterPeople = 0;
        int counterSickPeople = 0;
        while (aux != NULL) {
            if (aux->placeID == roomList[i].id) {
                if (aux->status == SICK) {
                    counterSickPeople++;
                }

                counterPeople++;
            }

            aux = aux->next;
        }

        int nPeopleToContaminate = (int) (counterPeople * 0.05) * counterSickPeople;

        int *contaminateList = malloc(sizeof(int) * nPeopleToContaminate) ;
        for (int i = 0; i < nPeopleToContaminate; i++) {
            contaminateList[i] = intUniformRnd(0, nPeopleToContaminate);
        }

        int counter = 0;
        
        // To be redone? after 2 years idk how this is supposed to work (no patience now)
        aux = p;
        while (aux != NULL) {
            if (aux->placeID != roomList[i].id) {
                aux = aux->next;
                continue;
            }

            if (aux->status == SICK)
                aux->nSickDays++;

            for (int i = 0; i < nPeopleToContaminate; i++) { 
                if (contaminateList[i] != counter) 
                    continue;

                if (aux->status == SICK || aux->status == IMMUNE) 
                    continue;

                aux->status = SICK;
                aux->nSickDays = 1;
                break;
            }

            aux = aux->next;
            counter++;
        }

        free(contaminateList);
    }

    return p;
}

pPerson recovery(pPerson p) {
    pPerson aux = p;

    while (aux != NULL) {
        int probability = probEvento(1 / aux->age); 

        if (probability == 1) { 
            aux->nSickDays = 0;
            aux->status = immunity() == 0 ? HEALTHY : IMMUNE;
        }

        aux = aux->next;
    }

    return p;
}

pPerson maxDuration(pPerson p) {  
    pPerson aux = p;

    while (aux != NULL) {
        int maxSickDuration = (int) 5 + p->age / 10; 

        if (aux->nSickDays >= maxSickDuration) { 
            aux->nSickDays = 0;
            aux->status = immunity() == 0 ? HEALTHY : IMMUNE;
        }

        aux = aux->next;
    }

    return p;
}

int immunity() {
    return intUniformRnd(1, 100) < 20 ? 1 : 0;
}
