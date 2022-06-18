#include <stdio.h>
#include <stdlib.h>
#include "sala.c"
#include "Persons.c"
#include "simulacao.c"
#include "verificar.c"
#include "opcoes.c"


int main() {
    initRandom();
    pRoom roomList = NULL;
    pPerson ArrayPersons[3];
    for (int i = 0; i < 3; i++)
        ArrayPersons[i] = NULL;

    char nomeP[100];
    char nomeL[100];
    int total = 0;

    printf("Ficheiro de Persons:");
    scanf(" %99s", nomeP);
    printf("\nFicheiro de Local:");
    scanf(" %99s", nomeL);


    roomList = readRoomsFile(nomeL, &total); //Ficheiro sala.c
    if (roomList == NULL)
        return 0;

    if (verifyRooms(roomList, total) == 1) //Ficheiro sala.c
        return 0;

    printf("\nLeitura e verificacao dos locais executada com sucesso.");

    for (int i = 0; i < total; i++) //dar print a todas as salas
        printRoom(roomList[i]); //Ficheiro sala.c

    pPerson listaPersons = NULL;
    listaPersons = readPersonFile(nomeP, listaPersons); //Ficheiro jog.c
    if (listaPersons == NULL)
        return 0;

    listaPersons = atribuirLocais(listaPersons, roomList, total); //Ficheiro jog.c
    if (listaPersons == NULL)
        return 0;

    printf("\n\nLeitura e verificacao das Persons executada com sucesso.");
    printf("\nLocais atribuidos com sucesso.");


    fflush(stdin);
    printf("\n\nClique enter tecla para avancar!");
    getchar();
    limparecra(); //Ficheiro utils.c


    int IteracoesVezes = 0;
    int ApresentarEstatisticaVezes = 0;
    int addSickPersonVezes = 0;
    int TransferirPersonVezes = 0;
    int VoltarAtrasVezes = 0;
    int opcao = 0;
    do {
        fflush(stdin);
        printf("\n");
        printf("\n* Iteracao numero: %d", IteracoesVezes);
        printf("\n* 1. Avancar 1 iteracao na simulacao (Fica organizado pelo o ID dos locais!)");
        printf("\n* 2. Apresentar estatistica");
        printf("\n* 3. Adicionar doente");
        printf("\n* 4. Transferir Persons");
        printf("\n* 5. Voltar atras");
        printf("\n* 6. Terminar Simulacao");
        printf("\n");
        printf("\nOpcao:");
        scanf("%d", &opcao);
        switch (opcao) {
            case 1:
                IteracoesVezes++;
                ArrayPersons[2] = ArrayPersons[1];
                ArrayPersons[1] = ArrayPersons[0];
                ArrayPersons[0] = listaPersons;
                listaPersons = nextimaIteracao(listaPersons, roomList, total);
                printf("\nVoce avancou de iteracao com sucesso");
                break;
            case 2:
                ApresentarEstatisticaVezes++;
                ApresentarEstatistica(listaPersons, roomList, total);
                break;
            case 3:
                addSickPersonVezes++;
                listaPersons = addSickPerson(roomList, total, listaPersons);
                break;
            case 4:
                TransferirPersonVezes++;
                listaPersons = TransferirPersons(roomList, total, listaPersons);
                break;
            case 5:
                VoltarAtrasVezes++;
                listaPersons = VoltarAtras(ArrayPersons, listaPersons);
                break;
        }
    } while (opcao != 6);

    EscreverNoFicheiro(listaPersons, roomList, total, IteracoesVezes,
                       ApresentarEstatisticaVezes, addSickPersonVezes, TransferirPersonVezes, VoltarAtrasVezes);

    free(roomList);
    freePersons(listaPersons);
    return 0;
}
