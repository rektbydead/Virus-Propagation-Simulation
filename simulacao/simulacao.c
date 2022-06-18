
#include <stdio.h>
#include "simulacao.h"
#include "utils.h"

pPerson nextimaIteracao(pPerson p, pRoom roomList, int total) {
    p = TaxaDeDisseminacao(p, locais, total);
    p = Recupercao(p);
    p = DuracaoMaxima(p);
    return p;
}

pPerson TaxaDeDisseminacao(pPerson p, pRoom roomList, int total) {
    pPerson devolver = NULL;

    for (int b = 0; b < total; b++) {
        pPerson aux = p;
        int ContadorPersonsSala = 0;
        int ContadorDoentesSala = 0;
        while (aux != NULL) {
            if (aux->placeID == roomList[b].id) {
                if (aux->status == 'D')
                    ContadorDoentesSala++;
                ContadorPersonsSala++;
            }
            aux = aux->next;
        }

        int QuantasPersonsUmDoenteVaiContaminar = (int) (ContadorPersonsSala * 0.05);
        int QuantasPersonsVaoFicarDoentes = QuantasPersonsUmDoenteVaiContaminar * ContadorDoentesSala;

        int lista[QuantasPersonsVaoFicarDoentes];
        for (int i = 0; i < QuantasPersonsVaoFicarDoentes; i++) {
            lista[i] = intUniformRnd(0, ContadorPersonsSala);
        }

        aux = p;
        int lugar = 0;
        while (aux != NULL) {
            if (aux->placeID != roomList[b].id) {
                aux = aux->next;
                continue;
            }

            if (aux->status == 'D')
                aux->DiasDoente = aux->DiasDoente + 1;

            for (int i = 0; i < QuantasPersonsVaoFicarDoentes; i++) { //loop para por as Persons doentes
                if (lista[i] != lugar) //se o lugar da Person nao for o valor que esta em lista[i], ve o nextimo valor de lista[i]
                    continue;

                if (aux->status == 'D' || aux->status == 'I') // se ele for doente ou imune passa para o nextimo valor de lista[i]
                    continue;

                //põe  a Person a doente e seta os dias doente a 1
                aux->status = 'D';
                aux->DiasDoente = 1;
                break;
            }

            pPerson adicionar = malloc(sizeof(Person)); //define a var adicionar e aloca espaço
            if (adicionar == NULL) { //se nao houver espaço da erro
                printf("Erro ao alocar espaço na memoria (TaxaDeDisseminacao)");
                return p;
            }

            //copia os valores de aux para adicionar e seta o next em NULL
            strcpy(adicionar->name, aux->nome);
            adicionar->idade = aux->idade;
            adicionar->status = aux->status;
            adicionar->DiasDoente = aux->DiasDoente;
            adicionar->placeID = aux->placeID;
            adicionar->next = NULL;
            devolver = addPerson(devolver, adicionar); //chama funcao de inserir Person e retorna a lista

            aux = aux->next;
            lugar++;
        }
    }
    return devolver;
}

pPerson Recupercao(pPerson p) {
    pPerson devolver = NULL;

    while (p != NULL) {
        pPerson  adicionar = malloc(sizeof(Person));//define a var adicionar e aloca espaço
        if (adicionar == NULL) { //se nao houver espaço da erro
            printf("Erro ao alocar espaço na memoria (Recupercao)");
            return p;
        }

        //copia os valores de aux para adicionar e seta o next em NULL
        strcpy(adicionar->name, p->nome);
        adicionar->idade = p->idade;
        adicionar->placeID = p->placeID;
        adicionar->next = NULL;
        adicionar->status = p->status;
        adicionar->DiasDoente = p->DiasDoente;

        int verificar = probEvento((1 / adicionar->age); //Vê se a probabilidade da certo.
        if (verificar == 1) { //se der certo, seta os dias doentes a 0
            adicionar->DiasDoente = 0;
            if (Imunidade() == 0) //ve a funcao Imunidade() retornar 0, põe a Person saudavel
                adicionar->status = 'S';
            else //senao ela fica imune
                adicionar->status = 'I';
        }


        devolver = addPerson(devolver, adicionar);  //chama funcao de inserir Person e retorna a lista
        p = p->next;
    }
    return devolver;
}

pPerson DuracaoMaxima(pPerson p) {
    pPerson devolver = NULL;

    while (p != NULL) {
        int duracaomaxima = (int) 5 + p->idade / 10; //ve qual é o maximo de tempo que a doença vai durar, formula: 5+(idade/10)

        pPerson adicionar = malloc(sizeof(Person)); //define a var adicionar e aloca espaço
        if (adicionar == NULL) { //se nao houver espaço da erro
            printf("Erro ao alocar espaço na memoria (DuracaoMaxima)");
            return p;
        }

        //copia os valores de aux para adicionar e seta o next em NULL
        strcpy(adicionar->name, p->nome);
        adicionar->idade = p->idade;
        adicionar->placeID = p->placeID;
        adicionar->next = NULL;
        adicionar->status = p->status;
        adicionar->DiasDoente = p->DiasDoente;

        if (p->DiasDoente >= duracaomaxima) { //verificar se os dias são maiores que a duracao maxima
            adicionar->DiasDoente = 0; //se der certo, seta os dias doentes a 0
            if (Imunidade() == 0) //ve a funcao Imunidade() retornar 0, põe a Person saudavel
                adicionar->status = 'S';
            else //senao ela fica imune
                adicionar->status = 'I';
        }

        devolver = addPerson(devolver, adicionar);  //chama funcao de inserir Person e retorna a lista
        p = p->next;
    }
    return devolver;
}

int Imunidade() {
    int valor = intUniformRnd(1, 100); //gera um valor entre 1 e 100
    if (valor < 20) //se o valor gerado for maior que 20, devolve um o que significa que a Person fica imune
        return 1;
    return 0;
}
