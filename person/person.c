#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Person.h"
#include "../room/room.h"
#include "../verificar/verificar.h"


pPerson addPerson(pPerson p, pPerson add) {
    pPerson aux;

    if (p == NULL) {
        return add;
    }

    aux = p;
    while (aux->next != NULL)
        aux = aux->next;

    aux->next = add;

    return p;
}

void mostraTudo(pPerson p) {  
    while (p != NULL) {
        printf("\n%s\t%d\t%c\t%d\t%d", p->name, p->age, p->status, p->nSickDays, p->placeID);

        p = p->next;
    }
}

void freePersons(pPerson c) {
    while (c != NULL) {
        pPerson aux = c;
        c = c->next;

        free(aux);
    }
}


pPerson readPersonFile(char *fileName, pPerson p) {
    FILE *f = fopen(fileName, "rt");

    if (f == NULL) {
        printf("O ficheiro que le os locais não existe");
        return NULL;
    }

    char name[100];
    int age;
    char status;
    int nSickDays;

    while (fscanf(f, "%s %d %c %d", name, &age, &status, &nSickDays) != EOF) {
        pPerson temp = malloc(sizeof(pPerson));

        if (temp == NULL) {
            printf("\nErro na alocacao de memoria! (Leitura das Persons)");
            return NULL;
        }

        if (verifyInputValues(age, name, nSickDays, p) == 1) return NULL;

        if (status == SICK && nSickDays == 0) { 
            printf("\nFoi encontrado uma doente, doente a um numero de dias inválido!");
            return NULL;
        }

        if (status != SICK && nSickDays != 0) {
            printf("\nFoi encontrado uma pessoa nao doente, com dias doente setados");
            return NULL;
        }

        if (status != IMMUNE && status != HEALTHY && status != SICK) {
            printf("\nFoi encontrado uma Person com status invalido!");
            return NULL;
        }


        strcpy(temp->name, name);
        temp->status = status;
        temp->age = age;
        temp->nSickDays = nSickDays;
        temp->placeID = NO_ROOM;
        temp->next = NULL;

        p = addPerson(p, temp);
    }

    fclose(f); 
    return p;
}

pPerson atribuirLocais(pPerson p, pRoom r, int nRooms) {
    while (p != NULL) {
        int nFullPlaces = getNumberOfFullPlaces(readPersonFile, nRooms);

        if (nFullPlaces == nRooms) {
            printf("\nTodos os lugares foram preenchidos, porem sobraram Persons sem local.");

            return p;
        }           

        int index;
        do {
            index = intUniformRnd(0, nRooms - 1);
        } while (r[index].capacity == r[index].maxCapacity);

        r[index].capacity++;
        
        p->placeID = r[index].id;
        p = p->next;
    }
    
    return p;
}


int getNumberOfFullPlaces(pRoom r, int nRooms) {
    int nFullPlaces = 0;

    for (int i = 0; i < nRooms; i++) {
        if (r[i].capacity != r[i].maxCapacity) continue;

        nFullPlaces++;
    }

    return nFullPlaces;
}
