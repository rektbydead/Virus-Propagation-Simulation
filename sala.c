
#include<stdio.h>
#include "sala.h"
#include <stdlib.h>
#include <string.h>


void escreverLocal(local c) {
    printf("\nID:%d\tCapacidade:%d\tLigacao1: %d\tLigacao2: %d\tLigacao1: %d", c.id, c.capacidade, c.liga[0], c.liga[1],
           c.liga[2]);
}


local *listarFicheiroLocal(char *nome, int *total) {
    FILE *f;
    local c;
    f = fopen(nome, "rb");
    if (f == NULL) { //verifica se a erro no alocamento de memoria
        printf("\nO ficheiro que lê os locais não existe (listarFicheiroLocal)");
        return NULL;
    }
    int i = 1; //index
    local *array; //cria o ponteiro
    array = malloc(sizeof(local)); //aloca espaço

    while (fread(&c, sizeof(local), 1, f) == 1) { //le ate o fread devovler o valor 0
        if (i != 1)
            array = realloc(array, sizeof(local) * i); //realoca memoria quando o index for diferente de 1.
        if (array == NULL) {//verifica se a erro no alocamento de memoria
            printf("\nErro no alocamente de memoria! (Leitura dos Ficheiros)");
            return NULL;
        }
        array[i - 1] = c; //seta o struc no array no index (i-1)
        i++; //incrementa o index
    }

    fclose(f); //fechar ficheiroi
    *total = i - 1; //total
    return array;
}

int verificarLocais(local *locais, int total) {
    int *p = malloc(sizeof(int) * total);
    if (p == NULL) { //ve se da erro na alocacao de memoria
        printf("\nErro no alocamente de memoria! (Verificacao de Locais)");
        return 1;
    }
    for (int i = 0; i < total; i++) { //loop entre todos os locais
        if (locais[i].id < 1) { //verifica se o id do local é negativo ou 0
            printf("\nFoi encontrado um ID negativo entao a opercacao foi cancelada!");
            return 1;
        }
        if (locais[i].capacidade < 0) {//verifica se a capacidade é negativa
            printf("\nFoi encontrada uma sala com capacidade negativa entao a operacao foi cancelada!");
            return 1;
        }

        p[i] = locais[i].id;
        for (int q = i; q < i; q++) { //loop entro os locais
            if (p[q] == p[i]) { //verifica se ha duas salas com o mesmo id
                printf("\nForam encontradas dois Locais com o mesmo ID entao a operacacao foi cancelada!");
                return 1;
            }
        }

        for (int h = 0; h < 3; h++) { //loop entre as ligações do local i
            if (locais[i].liga[h] == -1) //se a ligação for -1, vai para o proxima ligação
                continue;

            int verificador = 0;
            for (int h2 = 0; h2 < total; h2++) { //loop entre todos os locais
                if (locais[i].liga[h] == locais[h2].id) //verificar se a ligacao ao local existe
                    verificador = 1; // se exitir seta a var verificador a 1
            }
            if (verificador == 0){ //se nao exitir, entao verificador vai ser igual a 0
                printf("\nUm local tem uma ligacao a um local que nao existe");
                return 1;
            }

            for (int a = 0; a < total; a++) { //loop entre todas os locais novamente
                if (locais[i].liga[h] != locais[a].id) //se o id da ligacao for diferente ao do local, vai para a proximo local
                    continue;

                int cont = 0;
                for (int b = 0; b < 3; b++) {//contador de  0 a 2 para ver se a ligacao existe
                    if (locais[a].liga[b] == locais[i].id) { //se existir incrementa
                        cont++;
                    }
                }
                if (cont != 1) { //se ha ligacao nao existir ou se houver a ligacao mais que uma vez da erro.
                    printf("\nFoi encontrado um erro nas ligacoes entre as salas.");
                    return 1;
                }
                break;
            }
        }
    }
    return 0;
}
