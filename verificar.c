
#include <stdio.h>
#include "utils.h"
#include "verificar.h"

int VerificarSeTemEspacoLivre(local *listaSalas, int total, int localID, ppessoa p) {
    for (int i = 0; i < total; i++) { //percorre todos os locais
        if (listaSalas[i].id != localID) //verifica quando o id da sala indicada é igual
            continue;

        int contador = 0; //contador de pessoas na sala
        ppessoa aux = p;
        while (aux != NULL) {
            if (aux->localID == localID) //se a pessoa tiver o mesmo LocalID adiciona incrementa o contador
                contador++;
            aux = aux->prox;
        }

        if (contador >= listaSalas[i].capacidade) { //se o contador for igual a capacidade do local, cancela
            printf("\nEsse local nao tem espaco suficiente, entao a operacao foi cancelada.");
            return 1;
        }
        return 0;
    }

    //se chegar aqui não existe lugar
    printf("\nO local escolhido nao existe, entao a operacao foi cancelada.");
    return 1;
}

int VerificarValores(int idade, char nome[100], int DiasDoente, ppessoa p) { //verifica os valores introduzidos
    while (p->prox != NULL) { //faz um loop entre todas as pessoas e verifica se ha alguma pessoa com o nome que esta na string nome
        if (strcmp(nome, p->nome) == 0) {
            printf("\nJa existe uma pessoa com esse nome, entao a operacao foi cancelada.");
            return 1;
        }
        p = p->prox;
    }

    if (idade < 1) { //verifica se a idade é menor que 0
        printf("\nA idade introduzida e negativa ou zero, entao a operacao foi cancelada.");
        return 1;
    }

    if (DiasDoente < 1) { //verificar se os dias doente é menor que 0
        printf("\nOs 'dias doente' tem de ser maior que 0, entao a operacao foi cancelada.");
        return 1;
    }
    return 0;
}

ppessoa VerificarTrocarLocais(int N, int DestinoID, int OrigemID, ppessoa p, local *listaSalas, int total) {
    if (DestinoID == OrigemID) { //verificar se o id de origim e de destino sao iguais
        printf("\nO local de destino e de origem sao iguais.");
        return p;
    }

    if (N < 0) { //ve se o numero der pessoas e´posiotivos
        printf("\nO numero de pessoas tem de ser positivo.");
        return p;
    }

    int DestinoExiste = 0; //verifica se existe
    int OrigemExiste = 0;//verifica se existe
    int DestinoIndex = 0; //guardar em que lugar do array esta a destino
    int OrigemIndex = 0; //guardar em que lugar do array esta a origem

    for (int i = 0; i < total; i++) { //loop entre as locais
        if (DestinoID == listaSalas[i].id) {
            DestinoExiste = 1; //se exitir poe a 1
            DestinoIndex = i; //e guarda o index
        }
        if (OrigemID == listaSalas[i].id) {
            OrigemExiste = 1; //se existir poe a 1
            OrigemIndex = i; //e guarda o index
        }
    }

    if (OrigemExiste == 0) { //verifica se exisste
        printf("\nO Local de Origem com o ID: %d, nao existe.", OrigemID);
        return p;
    }

    if (DestinoExiste == 0) {//verifica se exisste
        printf("\nO Local de Destino com o ID: %d, nao existe.", DestinoID);
        return p;
    }

    int VerSeTemLigacao = 0;
    for (int a = 0; a < 3; a++)
        if (listaSalas[OrigemIndex].liga[a] == DestinoID)
            VerSeTemLigacao = 1;

    if (VerSeTemLigacao == 0) {
        printf("\nOs locais selecionados nao estao interligados.");
        return p;
    }

    ppessoa aux = p;
    int contadorPessoas = 0;
    int PessoasNoDestino = 0;
    while (aux != NULL) {
        if (aux->localID == OrigemID)
            contadorPessoas++;
        if (aux->localID == DestinoID)
            PessoasNoDestino++;
        aux = aux->prox;
    }

    if (contadorPessoas < N) {
        printf("\nO Local de origem nao possui %d pessoas, a sala so possui %d.", N, contadorPessoas);
        return p;
    }

    if (listaSalas[DestinoIndex].capacidade - PessoasNoDestino < N) { //verifica se a capacidade é suficiente
        printf("\nO local nao tem capacidade suficiente para serem transportados tantas pessoas.");
        return p;
    }

    int lista[N];
    for (int i = 0; i < N; i++) //gera o total de infetados
        lista[i] = intUniformRnd(0, contadorPessoas - 1);


    ppessoa devolver = NULL, adicionar;
    int index = -1;
    while (p != NULL) {
        index++;
        adicionar = malloc(sizeof(pessoa));
        if (adicionar == NULL) {
            printf("\nErro ao alocar espaço na memoria. (VerificarTrocarLocais)");
            return p;
        }
        strcpy(adicionar->nome, p->nome);
        adicionar->idade = p->idade;
        adicionar->estado = p->estado;
        adicionar->DiasDoente = p->DiasDoente;
        adicionar->localID = p->localID;
        if (p->localID == OrigemID)  //se for diferença passa
            for (int i = 0; i < N; i++)
                if (lista[i] == index)
                    adicionar->localID = DestinoID;
        adicionar->prox = NULL;
        devolver = inserirPessoa(devolver, adicionar);
        p = p->prox;
    }
    return devolver;

}