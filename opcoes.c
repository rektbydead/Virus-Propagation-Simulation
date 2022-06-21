
#include <stdio.h>
#include "opcoes.h"
#include "utils.h"

void ApresentarEstatistica(ppessoa p, local *locais, int total) {

    for (int i = 0; i < total; i++) {
        ppessoa aux = p;
        int PessoasTotalSala = 0;
        int PessoasDoentesSala = 0;
        int PessoasImunesSala = 0;
        int PessoasSaudaveisSala = 0;
        while (aux != NULL) {
            if (aux->localID != locais[i].id) {
                aux = aux->prox;
                continue;
            }

            PessoasTotalSala++;
            if (aux->estado == 'D')
                PessoasDoentesSala++;
            if (aux->estado == 'S')
                PessoasSaudaveisSala++;
            if (aux->estado == 'I')
                PessoasImunesSala++;
            aux = aux->prox;
        }


        float TaxaDoentes = (float) PessoasDoentesSala / PessoasTotalSala * 100;
        float TaxaSaudaveis = (float) PessoasSaudaveisSala / PessoasTotalSala * 100;
        float TaxaImunes = (float) PessoasImunesSala / PessoasTotalSala * 100;

        printf("\n\n\nSala: %d", locais[i].id);
        printf("\nTotal de pessoas na sala: %d", PessoasTotalSala);
        printf("\nTotal de doentes na sala: %d, Taxa de doentes: %.1f%%", PessoasDoentesSala,
               TaxaDoentes); //o %% da print so a um '%'
        printf("\nTotal de saudaveis na sala: %d, Taxa de saudaveis: %.1f%%", PessoasSaudaveisSala,
               TaxaSaudaveis); // tambem se pode usar , %c e depois '%'
        printf("\nTotal de imunes na sala: %d, Taxa de imunes: %.1f%%", PessoasImunesSala,
               TaxaImunes); // exemplo printf("%c", '%');
    }
}


ppessoa AdicionarDoente(local *listaSalas, int total, ppessoa listaPessoas) {
    char nome[100];
    int idade = 0, DiasDoente, localID;
    for (int i = 0; i < total; i++)
        escreverLocal(listaSalas[i]); //Ficheiro sala.c
    printf("\nID do Local: ");
    scanf("%d", &localID);
    if (VerificarSeTemEspacoLivre(listaSalas, total, localID, listaPessoas) == 0) { //Ficheiro verificar.c
        printf("\nNome: ");
        scanf("%99s", nome);
        printf("\nIdade: ");
        scanf("%d", &idade);
        printf("\nDias Doente: ");
        scanf("%d", &DiasDoente);

        if (VerificarValores(idade, nome, DiasDoente, listaPessoas) == 1)
            return listaPessoas;
//
        ppessoa aux = malloc(sizeof(pessoa));
        if (aux == NULL) {
            printf("\nErro na alocacao de memoria!");
            return listaPessoas;
        }
        strcpy(aux->nome, nome);
        aux->estado = 'D';
        aux->idade = idade;
        aux->DiasDoente = DiasDoente;
        aux->localID = localID;
        aux->prox = NULL;
        listaPessoas = inserirPessoa(listaPessoas, aux); //Ficheiro jog.c
        printf("\nDoente introduzido com sucesso.");
    }
    return listaPessoas;
}

ppessoa TransferirPessoas(local *listaSalas, int total, ppessoa listaPessoas) {
    int NPessoas = 0;
    int LocalOrigem = 0;
    int LocalDestino = 0;
    for (int i = 0; i < total; i++)
        escreverLocal(listaSalas[i]); //Ficheiro sala.c
    printf("\nNumero de pessoas:");
    scanf("%d", &NPessoas);
    printf("Local de Origem:");
    scanf("%d", &LocalOrigem);
    printf("Local de Destino:");
    scanf("%d", &LocalDestino);
    listaPessoas = VerificarTrocarLocais(NPessoas, LocalDestino, LocalOrigem, listaPessoas, listaSalas, total);
    printf("\nAs pessoas foram transferidas com sucesso");
    return listaPessoas;
}

ppessoa VoltarAtras(ppessoa *ArrayPessoas, ppessoa listaPessoas) {
    int Contador = 0;
    int Voltar = 0;
    for (int i = 0; i < 3; ++i)
        if (ArrayPessoas[i] != NULL)
            Contador++;

    if (Contador == 0) {
        printf("\nVoce ainda nao percorrer um numero suficiente de iteracoes.");
        return listaPessoas;
    }

    printf("Deseja voltar quantos passos atras? (%d)", Contador);
    scanf("\n%d", &Voltar);
    if (Voltar > Contador || Voltar < 1) {
        printf("\nVoce nao pode mandar mais que %d passo/s para tras.", Contador);
        return listaPessoas;
    }

    listaPessoas = ArrayPessoas[Voltar - 1];

    if (Voltar == 1) {
        ArrayPessoas[0] = ArrayPessoas[1];
        ArrayPessoas[1] = ArrayPessoas[2];
    } else if (Voltar == 2) {
        ArrayPessoas[0] = ArrayPessoas[2];
    }
    for (int i = Contador; i > Contador - Voltar; i--) { //ta a funcionar, so seta em NULL
        ArrayPessoas[i - 1] = NULL;
    }
    printf("\nVoce voltou atras com sucesso");
    return listaPessoas;
}

void EscreverNoFicheiro(ppessoa listaPessoas, local *listaSalas, int total, int IteracoesVezes,
                        int ApresentarEstatisticaVezes, int AdicionarDoenteVezes, int TransferirPessoaVezes,
                        int VoltarAtrasVezes) {
    FILE *f;
    f = fopen("report.txt", "wt");


    int TotalPessoas = 0;
    ppessoa aux = listaPessoas;
    while (aux != NULL) {
        TotalPessoas++;
        aux = aux->prox;
    }
    fprintf(f, "Iterou %d vezes", IteracoesVezes);
    fprintf(f, "\nApresentou a estatistica %d vezes.", ApresentarEstatisticaVezes);
    fprintf(f, "\nAdicionou doentes %d vezes", AdicionarDoenteVezes);
    fprintf(f, "\nTransferio pessoas %d vezes", TransferirPessoaVezes);
    fprintf(f, "\nVoltou atras %d vezes", VoltarAtrasVezes);


    fprintf(f, "\n\nTOTAL DE PESSOAS: %d", TotalPessoas);

    for (int i = 0; i < total; i++) {
        aux = listaPessoas;
        int PessoasTotalSala = 0;
        int PessoasDoentesSala = 0;
        int PessoasImunesSala = 0;
        int PessoasSaudaveisSala = 0;
        while (aux != NULL) {
            if (aux->localID != listaSalas[i].id) {
                aux = aux->prox;
                continue;
            }

            PessoasTotalSala++;
            if (aux->estado == 'D')
                PessoasDoentesSala++;
            if (aux->estado == 'S')
                PessoasSaudaveisSala++;
            if (aux->estado == 'I')
                PessoasImunesSala++;
            aux = aux->prox;
        }


        float TaxaDoentes = (float) PessoasDoentesSala / PessoasTotalSala * 100;
        float TaxaSaudaveis = (float) PessoasSaudaveisSala / PessoasTotalSala * 100;
        float TaxaImunes = (float) PessoasImunesSala / PessoasTotalSala * 100;

        fprintf(f, "\nSala: %d", listaSalas[i].id);
        fprintf(f, "\nTotal de pessoas na sala: %d", PessoasTotalSala);
        fprintf(f, "\nTotal de doentes na sala: %d, Taxa de doentes: %.1f%%", PessoasDoentesSala,
                TaxaDoentes); //o %% da print so a um '%'
        fprintf(f, "\nTotal de saudaveis na sala: %d, Taxa de saudaveis: %.1f%%", PessoasSaudaveisSala,
                TaxaSaudaveis); // tambem se pode usar , %c e depois '%'
        fprintf(f, "\nTotal de imunes na sala: %d, Taxa de imunes: %.1f%%", PessoasImunesSala,
                TaxaImunes); // exemplo printf("%c", '%');
    }
    fclose(f);

    char nome[100];
    printf("Nome do ficheiro para guardar as pessoas:");
    scanf("%s", nome);
    f = fopen(nome, "wt");
    aux = listaPessoas;
    while (aux != NULL) {
        fprintf(f, "%s\t %d\t %c\t %d\n", aux->nome, aux->idade, aux->estado, aux->DiasDoente);
        aux = aux->prox;
    }
    fclose(f);
    printf("\nPessoas guardadas com sucesso no ficheiro %s", nome);
}