
#include <stdio.h>
#include <string.h>
#include <stdlib.h> 

#include "../utils/utils.h"
#include "../verificar/verificar.h"
#include "../person/person.h"
#include "../room/room.h"


int verifyFreeSpace(pRoom roomList, int total, int placeID) {
    for (int i = 0; i < total; i++) { 
        if (roomList[i].id != placeID)
            continue;

        if (roomList[i].capacity == roomList[i].maxCapacity) { 
            printf("\nEsse local nao tem espaco suficiente, entao a operacao foi cancelada.");
            return 1;
        }

        return 0;
    }

    printf("\nO local escolhido nao existe, entao a operacao foi cancelada.");
    return 1;
}

int verifyInputValues(int age, char name[100], int nSickDays, pPerson p) {
    pPerson aux = p;
    while (aux != NULL) { 
        if (strcmp(name, aux->name) == 0) {
            printf("\nJa existe uma Person com esse name, entao a operacao foi cancelada.");
            return 1;
        }

        aux = aux->next;
    }

    if (age < 1) {
        printf("\nA idade introduzida e negativa ou zero, entao a operacao foi cancelada.");
        return 1;
    }

    if (nSickDays < 1) { 
        printf("\nOs 'dias doente' tem de ser maior que 0, entao a operacao foi cancelada.");
        return 1;
    }

    return 0;
}

pPerson verifyRoomChange(int N, int fromID, int toID, pPerson p, pRoom roomList, int total) {
    if (fromID == toID) { 
        printf("\nO local de destino e de origem sao iguais.");
        return p;
    }

    if (N < 0) { 
        printf("\nO numero de Persons tem de ser positivo.");
        return p;
    }

    int toIndex = -1; 
    int fromIndex = -1; 

    for (int i = 0; i < total; i++) { 
        if (fromID == roomList[i].id) {
            toIndex = i; 
        }

        if (toID == roomList[i].id) {
            fromIndex = i;
        }
    }

    if (fromIndex == -1) { 
        printf("\nO Local de Origem com o ID: %d, nao existe.", toID);
        return p;
    }

    if (toIndex == -1) {
        printf("\nO Local de Destino com o ID: %d, nao existe.", fromID);
        return p;
    }

    int checkConnectionExists = 0;
    for (int a = 0; a < 3; a++)
        if (roomList[fromIndex].connections[a] == fromID)
            checkConnectionExists = 1;

    if (checkConnectionExists == 0) {
        printf("\nOs locais selecionados nao estao interligados.");
        return p;
    }

    int fromCapacity = roomList[fromID].capacity;
    int toCapacity = roomList[toID].capacity;

    if (fromCapacity < N) {
        printf("\nO Local de origem nao possui %d Persons, a sala so possui %d.", N, fromCapacity);
        return p;
    }

    if (roomList[toID].maxCapacity - toCapacity < N) {
        printf("\nO local nao tem capacidade suficiente para serem transportados tantas Persons.");
        return p;
    }

    int *list = malloc(sizeof(int) * N);
    for (int i = 0; i < N; i++)
        list[i] = intUniformRnd(0, fromCapacity - 1);


    int index = -1;
    while (p != NULL) {
        index++;
            
        if (p->placeID != toID) {
            p = p->next;
            continue;
        }

        for (int i = 0; i < N; i++) {
            if (list[i] != index)
                continue;
                
            p->placeID = toID;
            break;
        }

        p = p->next;
    }

    free(list);
    return p;

}