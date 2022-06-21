
#include <stdio.h>
#include "room.h"
#include <stdlib.h>
#include <string.h>


void printRoom(room r) {
    printf("\nID:%d\tCapacidade:%d\tLigacao1: %d\tLigacao2: %d\tLigacao1: %d", r.id, r.maxCapacity, r.connections[0], r.connections[1],
           r.connections[2]);
}

// Read rooms file - 
pRoom readRoomsFile(char *fileName, int *total) {
    FILE *f = fopen(fileName, "rb");
    if (f == NULL) { 
        printf("\nO ficheiro que lê os locais não existe (readRoomsFile)");
        return NULL;
    }

    *total = 0;

    pRoom roomList = NULL; 
    room r; 
    
    // it takes the size of an int, (quick fix... the binary files have the old structure saved which has less 1 int variable)
    while (fread(&r, sizeof(room) - sizeof(int), 1, f) == 1) { 
        printf("%d - %d %d %d \n", r.id, r.connections[0],r.connections[1],r.connections[2]);

        roomList = realloc(roomList, sizeof(room) * (*total + 1)); 
        if (roomList == NULL) {
            printf("\nErro no alocamente de memoria! (Leitura dos Ficheiros)");
            return NULL;
        }

        r.capacity = 0;
        roomList[(*total)++] = r; 
    }

    fclose(f);
    return roomList;
}

int verifyRooms(pRoom roomList, int total) {
    for (int i = 0; i < total; i++) { 
        room room = roomList[i];

        if (room.id < 1) { 
            printf("\nFoi encontrado um ID negativo entao a opercacao foi cancelada!");
            return 1;
        }
        
        if (room.maxCapacity < 0) {
            printf("\nFoi encontrada uma sala com capacidade negativa entao a operacao foi cancelada!");
            return 1;
        }

        for (int j = i + 1; j < total; j++) { 
            if (room.id == roomList[j].id) {
                printf("\nForam encontradas dois Locais com o mesmo ID entao a operacacao foi cancelada!");
                return 1;
            }
        }

        for (int j = 0; j < MAX_CONNECTION; j++) { 
            int connection = room.connections[j];
            if (connection == NO_CONNECTION) continue;

            // verify if it exists
            for (int k = 0; k < total; k++) { 
                // leaves if it exists
                if (connection == roomList[k].id) break;

                // continues if its not the last one
                if (k != total - 1) continue;    
                
                printf("\nUm local tem uma ligacao a um local que nao existe");
                return 1;
            }

            // verify if both have the connection
            for (int k = 0; k < total; k++) {
                // get connection room
                if (roomList[k].id != connection) 
                    continue;


                for (int b = 0; b < MAX_CONNECTION; b++) {
                    if (roomList[k].connections[b] == room.id) break;

                    // continues if its not the last one
                    if (b != total - 1) continue;

                    printf("\nFoi encontrado um erro nas ligacoes entre as salas.");
                    return 1;
                }
                
                break;
            }
        }
    }

    return 0;
}
