#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pessoas.h"
#include "utils.c"


ppessoa inserirPessoa(ppessoa p, ppessoa pPessoa) {
    ppessoa aux;

    if (p == NULL) {
        p = pPessoa;
    } else {
        aux = p;
        while (aux->prox != NULL)
            aux = aux->prox;
        aux->prox = pPessoa;
    }
    return p;
}

void escreverPessoa(ppessoa c) {
    printf("\n%s\t%d\t%c\t%d\t%d", c->nome, c->idade, c->estado, c->DiasDoente, c->localID);
}

void mostraTudo(ppessoa c) {
    if (c == NULL)
        printf("Lista vazia\n");
    else {
        while (c != NULL) {
            escreverPessoa(c);
            c = c->prox;
        }
    }
}

void liberarpessoas(ppessoa c) {
    ppessoa aux;
    while (c != NULL) {
        aux = c;
        c = c->prox;
        free(aux);
    }
}


ppessoa lerFicheiroPessoa(char *fnome, ppessoa p) {
    FILE *f;
    f = fopen(fnome, "rt"); //abrir ficheiro pessoas
    if (f == NULL) { //verificar se houve erro no alocamento de mmeoria
        printf("O ficheiro que le os locais não existe");
        return NULL;
    }

    ppessoa aux;
    int idade = 0, diasdoente = 0;
    char nome[100];
    char estado;

    while (fscanf(f, "%s %d %c %d", nome, &idade, &estado, &diasdoente) != EOF) { //le ate o final do fciheiro
        aux = malloc(sizeof(pessoa));
        if (aux == NULL) { //ve se o alocamente da erro
            printf("\nErro na alocacao de memoria! (Leitura das pessoas)");
            return NULL;
        }

        if (idade < 1 ||  idade > 150) { //verificar se a tidade é menor que 1
            printf("\nFoi encontrado uma pessoa com idade menor que um ou superior a 150!");
            return NULL;
        }

        if (diasdoente < 1 && estado == 'D') { //verificar se os dias doentes e o estado é igual a 'D'
            printf("\nFoi encontrado uma doente, doente a um numero de dias inválido!");
            return NULL;
        }

        if (estado != 'I' && estado != 'S' && estado != 'D') { //verificar todos os estados posiveis
            printf("\nFoi encontrado uma pessoa com estado invalido!");
            return NULL;
        }

        ppessoa verificador = p;
        while (verificador != NULL) { //loop
            if (strcmp(verificador->nome, nome) == 0) { //verifica se ha 2 pessoas com o mesmo nome
                printf("\nFoi encontrado duas pessoas com o mesmo nome!");
                return NULL;
            }
            verificador = verificador->prox;
        }


        if (estado != 'D') //se nao for doente, seta a var diasdoente a 0
            diasdoente = 0;

        strcpy(aux->nome, nome);
        aux->estado = estado;
        aux->idade = idade;
        aux->DiasDoente = diasdoente;
        aux->localID = -1;
        aux->prox = NULL;

        p = inserirPessoa(p, aux);
    }
    fclose(f); //fechar fichieor
    return p;
}

ppessoa atribuirLocais(ppessoa p, local *s, int total) {
    localAS lista[total];
    for (int i = 0; i < total; i++) {
        lista[i].id = s[i].id;
        lista[i].capacidade = 0;
    }


    ppessoa devolver = NULL, adicionar;
    while (p != NULL) {
        int verificar = 0;
        int aleatorio = 0;

        do {
            verificar = 0;
            aleatorio = intUniformRnd(0, total - 1);

            for (int a = 0; a < total; a++) {
                if (lista[a].capacidade == s[a].capacidade) {
                    verificar++;
                }
            }

            if (verificar == total) {
                printf("\nTodos os lugares foram preenchidos, porem sobraram pessoas sem local.");
                return devolver;
            }

            if (lista[aleatorio].capacidade == s[aleatorio].capacidade)
                continue;


            lista[aleatorio].capacidade = lista[aleatorio].capacidade + 1;
            break;
        } while (1);


        adicionar = malloc(sizeof(pessoa));
        if (adicionar == NULL) {
            printf("\nErro ao alocar espaço na memoria");
            return NULL;
        }
        strcpy(adicionar->nome, p->nome);
        adicionar->idade = p->idade;
        adicionar->estado = p->estado;
        adicionar->DiasDoente = p->DiasDoente;
        adicionar->localID = lista[aleatorio].id;
        adicionar->prox = NULL;
        devolver = inserirPessoa(devolver, adicionar);
        p = p->prox;
    }
    return devolver;
}

