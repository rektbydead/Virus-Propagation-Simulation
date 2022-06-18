// Trabalho Pratico Programacao - LEI
// DEIS-ISEC 2019-2020

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "utils.h"


void initRandom() {
    srand(time(NULL));
}

int intUniformRnd(int a, int b) {
    return a + rand() % (b - a + 1);
}

int probEvento(float prob) {
    return prob > ((float) rand() / RAND_MAX);
}

void limparecra() {
    for (int i = 0; i < 200; i++)
        printf("\n");
}



