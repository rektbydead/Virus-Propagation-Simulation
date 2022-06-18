
#include <stdio.h>
#include "opcoes.h"
#include "utils.h"
#include "../person/person.h"
#include "../room/room.h"
#include "../verificar/verificar.h"

void ApresentarEstatistica(pPerson p, pRoom roomList, int total) {

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
        printf("\nNome: ");
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

pPerson TransferirPersons(pRoom roomList, int total, pPerson listaPersons) {
    int NPersons = 0;
    int LocalOrigem = 0;
    int LocalDestino = 0;
    for (int i = 0; i < total; i++)
        printRoom(roomList[i]); //Ficheiro sala.c
    printf("\nNumero de Persons:");
    scanf("%d", &NPersons);
    printf("Local de Origem:");
    scanf("%d", &LocalOrigem);
    printf("Local de Destino:");
    scanf("%d", &LocalDestino);
    listaPersons = verifyRoomChange(NPersons, LocalDestino, LocalOrigem, listaPersons, roomList, total);
    printf("\nAs Persons foram transferidas com sucesso");
    return listaPersons;
}

pPerson VoltarAtras(pPerson *ArrayPersons, pPerson listaPersons) {
    int Contador = 0;
    int Voltar = 0;
    for (int i = 0; i < 3; ++i)
        if (ArrayPersons[i] != NULL)
            Contador++;

    if (Contador == 0) {
        printf("\nVoce ainda nao percorrer um numero suficiente de iteracoes.");
        return listaPersons;
    }

    printf("Deseja voltar quantos passos atras? (%d)", Contador);
    scanf("\n%d", &Voltar);
    if (Voltar > Contador || Voltar < 1) {
        printf("\nVoce nao pode mandar mais que %d passo/s para tras.", Contador);
        return listaPersons;
    }

    listaPersons = ArrayPersons[Voltar - 1];

    if (Voltar == 1) {
        ArrayPersons[0] = ArrayPersons[1];
        ArrayPersons[1] = ArrayPersons[2];
    } else if (Voltar == 2) {
        ArrayPersons[0] = ArrayPersons[2];
    }
    for (int i = Contador; i > Contador - Voltar; i--) { //ta a funcionar, so seta em NULL
        ArrayPersons[i - 1] = NULL;
    }
    printf("\nVoce voltou atras com sucesso");
    return listaPersons;
}

void EscreverNoFicheiro(pPerson listaPersons, pRoom roomList, int total, int IteracoesVezes,
                        int ApresentarEstatisticaVezes, int addSickPersonVezes, int TransferirPersonVezes,
                        int VoltarAtrasVezes) {
    FILE *f;
    f = fopen("report.txt", "wt");


    int TotalPersons = 0;
    pPerson aux = listaPersons;
    while (aux != NULL) {
        TotalPersons++;
        aux = aux->next;
    }
    fprintf(f, "Iterou %d vezes", IteracoesVezes);
    fprintf(f, "\nApresentou a estatistica %d vezes.", ApresentarEstatisticaVezes);
    fprintf(f, "\nAdicionou doentes %d vezes", addSickPersonVezes);
    fprintf(f, "\nTransferio Persons %d vezes", TransferirPersonVezes);
    fprintf(f, "\nVoltou atras %d vezes", VoltarAtrasVezes);


    fprintf(f, "\n\nTOTAL DE PersonS: %d", TotalPersons);

    for (int i = 0; i < total; i++) {
        aux = listaPersons;
        int PersonsTotalSala = 0;
        int PersonsDoentesSala = 0;
        int PersonsImunesSala = 0;
        int PersonsSaudaveisSala = 0;
        while (aux != NULL) {
            if (aux->placeID != roomList[i].id) {
                aux = aux->next;
                continue;
            }

            PersonsTotalSala++;
            if (aux->status == 'D')
                PersonsDoentesSala++;
            if (aux->status == 'S')
                PersonsSaudaveisSala++;
            if (aux->status == 'I')
                PersonsImunesSala++;
            aux = aux->next;
        }


        float TaxaDoentes = (float) PersonsDoentesSala / PersonsTotalSala * 100;
        float TaxaSaudaveis = (float) PersonsSaudaveisSala / PersonsTotalSala * 100;
        float TaxaImunes = (float) PersonsImunesSala / PersonsTotalSala * 100;

        fprintf(f, "\nSala: %d", roomList[i].id);
        fprintf(f, "\nTotal de Persons na sala: %d", PersonsTotalSala);
        fprintf(f, "\nTotal de doentes na sala: %d, Taxa de doentes: %.1f%%", PersonsDoentesSala,
                TaxaDoentes); //o %% da print so a um '%'
        fprintf(f, "\nTotal de saudaveis na sala: %d, Taxa de saudaveis: %.1f%%", PersonsSaudaveisSala,
                TaxaSaudaveis); // tambem se pode usar , %c e depois '%'
        fprintf(f, "\nTotal de imunes na sala: %d, Taxa de imunes: %.1f%%", PersonsImunesSala,
                TaxaImunes); // exemplo printf("%c", '%');
    }
    fclose(f);

    char name[100];
    printf("Nome do ficheiro para guardar as Persons:");
    scanf("%s", name);
    f = fopen(name, "wt");
    aux = listaPersons;
    while (aux != NULL) {
        fprintf(f, "%s\t %d\t %c\t %d\n", aux->name, aux->age, aux->status, aux->nSickDays);
        aux = aux->next;
    }
    fclose(f);
    printf("\nPersons guardadas com sucesso no ficheiro %s", name);
}