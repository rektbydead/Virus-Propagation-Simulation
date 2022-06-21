#include <stdio.h>
#include <stdlib.h>
#include "./person/person.h"
#include "./room/room.h"
#include "./simulation/simulation.h"
#include "./options/options.h"
#include "./verificar/verificar.h"
#include "./utils/utils.h"


int main() {
    initRandom();
    pRoom roomList = NULL;
    pPerson personsList[3];
    for (int i = 0; i < 3; i++)
        personsList[i] = NULL;

    char nameP[100];
    char nameL[100];
    int total = 0;

    printf("\nFicheiro de Local:");
    scanf(" %99s", nameL);

    roomList = readRoomsFile(nameL, &total);
    if (roomList == NULL)
        return 0;

    if (verifyRooms(roomList, total) == 1)
        return 0;

    printf("\nLeitura e verificacao dos locais executada com sucesso.");

    for (int i = 0; i < total; i++) 
        printRoom(roomList[i]);

    printf("Ficheiro de Persons:");
    scanf(" %99s", nameP);

    pPerson p = NULL;
    p = readPersonFile(nameP, p); 
    if (p == NULL) {
        printf("Leave on readPersonFile");
        return 0;
    }

    p = assignRooms(p, roomList, total); 
    if (p == NULL) {
        printf("Leave on assignRooms");
        return 0;
    }

    printf("\n\nLeitura e verificacao das Persons executada com sucesso.");
    printf("\nLocais atribuidos com sucesso.");


    fflush(stdin);
    printf("\n\nClique enter tecla para avancar!");
    getchar();
    cleanScreen();


    int nIteration = 0;
    int nShowStatistics = 0;
    int nAddSickPerson = 0;
    int nTransferPeople = 0;
    int nGoBack = 0;
    int option = 0;
    do {
        fflush(stdin);
        printf("\n");
        printf("\n* Iteracao numero: %d", nIteration);
        printf("\n* 1. Avancar 1 iteracao na simulation (Fica organizado pelo o ID dos locais!)");
        printf("\n* 2. Apresentar estatistica");
        printf("\n* 3. Adicionar doente");
        printf("\n* 4. Transferir Persons");
        printf("\n* 5. Voltar atras");
        printf("\n* 6. Terminar simulation");
        printf("\n");

        printf("\nopcao:");
        scanf("%d", &option);

        switch (option) {
            case 1:
                nIteration++;
                personsList[2] = personsList[1];
                personsList[1] = personsList[0];
                personsList[0] = p;
                p = nextIteration(p, roomList, total);
                printf("\nVoce avancou de iteracao com sucesso");
                break;
            case 2:
                nShowStatistics++;
                showStatistics(p, roomList, total);
                break;
            case 3:
                nAddSickPerson++;
                p = addSickPerson(roomList, total, p);
                break;
            case 4:
                nTransferPeople++;
                p = transferPersons(roomList, total, p);
                break;
            case 5:
                nGoBack++;
                p = goBack(personsList, p);
                break;
        }
    } while (option != 6);

    writeToFile(p, roomList, total, nIteration,
                       nShowStatistics, nAddSickPerson, nTransferPeople, nGoBack);

    free(roomList);
    freePersons(p);
    return 0;
}
