#include <stdio.h>
#include <stdlib.h> 
#include <string.h>

#include "options.h"
#include "../utils/utils.h"
#include "../person/person.h"
#include "../room/room.h"
#include "../verificar/verificar.h"

void showStatistics(pPerson p, pRoom roomList, int total) {

    for (int i = 0; i < total; i++) {
        pPerson aux = p;
        int personsTotal = 0;
        int totalPeopleSick = 0;
        int totalPeopleImmune = 0;
        int totalPeopleHealthy = 0;

        while (aux != NULL) {
            if (aux->placeID != roomList[i].id) {
                aux = aux->next;
                continue;
            }

            personsTotal++;

            switch(aux->status) {
                case SICK:
                    totalPeopleSick++;
                    break;
                 case HEALTHY:
                    totalPeopleHealthy++;
                    break;
                case IMMUNE:
                    totalPeopleImmune++;
                    break;
            }

            aux = aux->next;
        }

        float percentageSick = (float) totalPeopleSick / personsTotal * 100;
        float percentageHealthy = (float) totalPeopleHealthy / personsTotal * 100;
        float percentageImmune = (float) totalPeopleImmune / personsTotal * 100;

        printf("\n\n\nSala: %d", roomList[i].id);
        printf("\nTotal de Persons na sala: %d", personsTotal);
        printf("\nTotal de doentes na sala: %d, Taxa de doentes: %.1f%%", totalPeopleSick, percentageSick);
        printf("\nTotal de saudaveis na sala: %d, Taxa de saudaveis: %.1f%%", totalPeopleHealthy, percentageHealthy); 
        printf("\nTotal de imunes na sala: %d, Taxa de imunes: %.1f%%", totalPeopleImmune, percentageImmune); 
    }
}


pPerson addSickPerson(pRoom roomList, int total, pPerson p) {
    char name[100];
    int age;
    int nSickDays;
    int placeID;

    for (int i = 0; i < total; i++)
        printRoom(roomList[i]); 

    printf("\nID do Local: ");
    scanf("%d", &placeID);

    if (verifyFreeSpace(roomList, total, placeID) == 0) { 
        printf("\nname: ");
        scanf("%99s", name);
        printf("\nIdade: ");
        scanf("%d", &age);
        printf("\nDias Doente: ");
        scanf("%d", &nSickDays);

        if (verifyInputValues(age, name, nSickDays, p) == 1)
            return p;

        pPerson aux = malloc(sizeof(person));
        if (aux == NULL) {
            printf("\nErro na alocacao de memoria!");
            return p;
        }

        strcpy(aux->name, name);
        aux->status = SICK;
        aux->age = age;
        aux->nSickDays = nSickDays;
        aux->placeID = placeID;
        aux->next = NULL;

        p = addPerson(p, aux); 
        printf("\nDoente introduzido com sucesso.");
    }

    return p;
}

pPerson transferPersons(pRoom roomList, int total, pPerson p) {
    int nPersons = 0;
    int fromID = 0;
    int toID = 0;

    for (int i = 0; i < total; i++)
        printRoom(roomList[i]); 

    printf("\nNumero de Persons:");
    scanf("%d", &nPersons);

    printf("Local de Origem:");
    scanf("%d", &fromID);
    
    printf("Local de Destino:");
    scanf("%d", &toID);

    p = verifyRoomChange(nPersons, fromID, toID, p, roomList, total);
    printf("\nAs Persons foram transferidas com sucesso");

    return p;
}

// To be refactored
pPerson goBack(pPerson *arrayPersons, pPerson p) {
    int counter = 0;
    int back = 0;

    if (arrayPersons == NULL) {
        printf("\narrayPersons ta nulo.");
        return p;
    }

    for (int i = 0; i < 3; ++i)
        if (arrayPersons[i] != NULL)
            counter++;

    if (counter == 0) {
        printf("\nVoce ainda nao percorrer um numero suficiente de iteracoes.");
        return p;
    }

    printf("Deseja voltar quantos passos atras? (%d)", counter);
    scanf("\n%d", &back);
    if (back > counter || back < 1) {
        printf("\nVoce nao pode mandar mais que %d passo/s para tras.", counter);
        return p;
    }

    p = arrayPersons[back - 1];

    if (back == 1) {
        arrayPersons[0] = arrayPersons[1];
        arrayPersons[1] = arrayPersons[2];
    } else if (back == 2) {
        arrayPersons[0] = arrayPersons[2];
    }

    for (int i = counter; i > counter - back; i--) {
        arrayPersons[i - 1] = NULL;
    }

    printf("\nVoce voltou atras com sucesso");

    return p;
}

void writeToFile(pPerson p, pRoom roomList, int total, int nIterations, int nStatistics, int nSickPerson, int nTransfer, int nGoBack) {
    FILE *f = fopen("report.txt", "wt");

    int nPersons = 0;
    pPerson aux = p;
    while (aux != NULL) {
        nPersons++;
        aux = aux->next;
    }

    fprintf(f, "Iterou %d vezes", nIterations);
    fprintf(f, "\nApresentou a estatistica %d vezes.", nStatistics);
    fprintf(f, "\nAdicionou doentes %d vezes", nSickPerson);
    fprintf(f, "\nTransferio Persons %d vezes", nTransfer);
    fprintf(f, "\nVoltou atras %d vezes", nGoBack);


    fprintf(f, "\n\nTOTAL DE PersonS: %d", nPersons);

    for (int i = 0; i < total; i++) {
        aux = p;
        int totalPeople = 0;

        int totalPeopleSick = 0;
        int totalPeopleImmune = 0;
        int totalPeopleHealthy = 0;
        while (aux != NULL) {
            if (aux->placeID != roomList[i].id) {
                aux = aux->next;
                continue;
            }

            totalPeople++;

             switch(aux->status) {
                case SICK:
                    totalPeopleSick++;
                    break;
                 case HEALTHY:
                    totalPeopleHealthy++;
                    break;
                case IMMUNE:
                    totalPeopleImmune++;
                    break;
            }

            aux = aux->next;
        }


        float percentageSick = (float) totalPeopleSick / totalPeople * 100;
        float percentageHealthy = (float) totalPeopleHealthy / totalPeople * 100;
        float percentageImmune = (float) totalPeopleImmune / totalPeople * 100;

        fprintf(f, "\nSala: %d", roomList[i].id);
        fprintf(f, "\nTotal de Persons na sala: %d", totalPeople);
        fprintf(f, "\nTotal de doentes na sala: %d, Taxa de doentes: %.1f%%", totalPeopleSick, percentageSick); 
        fprintf(f, "\nTotal de saudaveis na sala: %d, Taxa de saudaveis: %.1f%%", totalPeopleHealthy, percentageHealthy);
        fprintf(f, "\nTotal de imunes na sala: %d, Taxa de imunes: %.1f%%", totalPeopleImmune, percentageImmune); 
    }

    fclose(f);

    char name[100];
    printf("name do ficheiro para guardar as pessoas:");
    scanf("%s", name);

    f = fopen(name, "wt");
    aux = p;
    while (aux != NULL) {
        showPerson(aux);
        
        aux = aux->next;
    }

    fclose(f);
    printf("\nPersons guardadas com sucesso no ficheiro %s", name);
}