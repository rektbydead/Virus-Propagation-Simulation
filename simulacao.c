
#include <stdio.h>
#include "simulacao.h"
#include "utils.h"

ppessoa ProximaIteracao(ppessoa p, local *locais, int total) {
    p = TaxaDeDisseminacao(p, locais, total);
    p = Recupercao(p);
    p = DuracaoMaxima(p);
    return p;
}

ppessoa TaxaDeDisseminacao(ppessoa p, local *locais, int total) {
    ppessoa devolver = NULL;

    for (int b = 0; b < total; b++) {
        ppessoa aux = p;
        int ContadorPessoasSala = 0;
        int ContadorDoentesSala = 0;
        while (aux != NULL) {
            if (aux->localID == locais[b].id) {
                if (aux->estado == 'D')
                    ContadorDoentesSala++;
                ContadorPessoasSala++;
            }
            aux = aux->prox;
        }

        int QuantasPessoasUmDoenteVaiContaminar = (int) (ContadorPessoasSala * 0.05);
        int QuantasPessoasVaoFicarDoentes = QuantasPessoasUmDoenteVaiContaminar * ContadorDoentesSala;

        int lista[QuantasPessoasVaoFicarDoentes];
        for (int i = 0; i < QuantasPessoasVaoFicarDoentes; i++) {
            lista[i] = intUniformRnd(0, ContadorPessoasSala);
        }

        aux = p;
        int lugar = 0;
        while (aux != NULL) {
            if (aux->localID != locais[b].id) {
                aux = aux->prox;
                continue;
            }

            if (aux->estado == 'D')
                aux->DiasDoente = aux->DiasDoente + 1;

            for (int i = 0; i < QuantasPessoasVaoFicarDoentes; i++) { //loop para por as pessoas doentes
                if (lista[i] != lugar) //se o lugar da pessoa nao for o valor que esta em lista[i], ve o proximo valor de lista[i]
                    continue;

                if (aux->estado == 'D' || aux->estado == 'I') // se ele for doente ou imune passa para o proximo valor de lista[i]
                    continue;

                //põe  a pessoa a doente e seta os dias doente a 1
                aux->estado = 'D';
                aux->DiasDoente = 1;
                break;
            }

            ppessoa adicionar = malloc(sizeof(pessoa)); //define a var adicionar e aloca espaço
            if (adicionar == NULL) { //se nao houver espaço da erro
                printf("Erro ao alocar espaço na memoria (TaxaDeDisseminacao)");
                return p;
            }

            //copia os valores de aux para adicionar e seta o prox em NULL
            strcpy(adicionar->nome, aux->nome);
            adicionar->idade = aux->idade;
            adicionar->estado = aux->estado;
            adicionar->DiasDoente = aux->DiasDoente;
            adicionar->localID = aux->localID;
            adicionar->prox = NULL;
            devolver = inserirPessoa(devolver, adicionar); //chama funcao de inserir pessoa e retorna a lista

            aux = aux->prox;
            lugar++;
        }
    }
    return devolver;
}

ppessoa Recupercao(ppessoa p) {
    ppessoa devolver = NULL;

    while (p != NULL) {
        ppessoa  adicionar = malloc(sizeof(pessoa));//define a var adicionar e aloca espaço
        if (adicionar == NULL) { //se nao houver espaço da erro
            printf("Erro ao alocar espaço na memoria (Recupercao)");
            return p;
        }

        //copia os valores de aux para adicionar e seta o prox em NULL
        strcpy(adicionar->nome, p->nome);
        adicionar->idade = p->idade;
        adicionar->localID = p->localID;
        adicionar->prox = NULL;
        adicionar->estado = p->estado;
        adicionar->DiasDoente = p->DiasDoente;

        int verificar = probEvento((1 / adicionar->idade)); //Vê se a probabilidade da certo.
        if (verificar == 1) { //se der certo, seta os dias doentes a 0
            adicionar->DiasDoente = 0;
            if (Imunidade() == 0) //ve a funcao Imunidade() retornar 0, põe a pessoa saudavel
                adicionar->estado = 'S';
            else //senao ela fica imune
                adicionar->estado = 'I';
        }


        devolver = inserirPessoa(devolver, adicionar);  //chama funcao de inserir pessoa e retorna a lista
        p = p->prox;
    }
    return devolver;
}

ppessoa DuracaoMaxima(ppessoa p) {
    ppessoa devolver = NULL;

    while (p != NULL) {
        int duracaomaxima = (int) 5 + p->idade / 10; //ve qual é o maximo de tempo que a doença vai durar, formula: 5+(idade/10)

        ppessoa adicionar = malloc(sizeof(pessoa)); //define a var adicionar e aloca espaço
        if (adicionar == NULL) { //se nao houver espaço da erro
            printf("Erro ao alocar espaço na memoria (DuracaoMaxima)");
            return p;
        }

        //copia os valores de aux para adicionar e seta o prox em NULL
        strcpy(adicionar->nome, p->nome);
        adicionar->idade = p->idade;
        adicionar->localID = p->localID;
        adicionar->prox = NULL;
        adicionar->estado = p->estado;
        adicionar->DiasDoente = p->DiasDoente;

        if (p->DiasDoente >= duracaomaxima) { //verificar se os dias são maiores que a duracao maxima
            adicionar->DiasDoente = 0; //se der certo, seta os dias doentes a 0
            if (Imunidade() == 0) //ve a funcao Imunidade() retornar 0, põe a pessoa saudavel
                adicionar->estado = 'S';
            else //senao ela fica imune
                adicionar->estado = 'I';
        }

        devolver = inserirPessoa(devolver, adicionar);  //chama funcao de inserir pessoa e retorna a lista
        p = p->prox;
    }
    return devolver;
}

int Imunidade() {
    int valor = intUniformRnd(1, 100); //gera um valor entre 1 e 100
    if (valor < 20) //se o valor gerado for maior que 20, devolve um o que significa que a pessoa fica imune
        return 1;
    return 0;
}
