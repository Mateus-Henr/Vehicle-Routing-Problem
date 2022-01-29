#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <time.h>
#include <stdbool.h>

#include "cidade.h"
#include "combinacao.h"

// Varia conforme o sistema operacional.
#if defined WIN32 || defined _WIN32 || defined __CYGWIN__
#define PATH_ARQUIVO "..\\arquivos\\text.txt"
#else
#define PATH_ARQUIVO "../arquivos/text.txt" // Edite caso você estiver em outro plataforma que não seja Windows.
#endif

#define ERRO_ABRIR_ARQUIVO "\nErro ao tentar abrir o arquivo.\n"
#define ERRO (-1)
#define ZERO 0
#define UM 1
#define DOIS 2
#define POSICAO_ROTA 0
#define TOTAL_ROTA 1
#define NULO (-1)

// Protótipos de funções.

double inicializaClock(void);

double calculaTempo(double tempoInicial);


/*
 * A função principal. Tem como função a leitura de informações de um arquivo e manipulação dos dados.
 *
 * @return          0 se executado com sucesso, -1 se ocorrer algum erro.
 */
int main(void)
{
    // Inicializando o inicioClock.
    double inicioClock = inicializaClock();

    // Inicializando ponteiro do arquivo.
    FILE *pArquivo = NULL;

    // Abrindo arquivo.
    pArquivo = fopen(PATH_ARQUIVO, "r");

    // Lidando com caso que o arquivo não é encontrado.
    if (!pArquivo)
    {
        printf(ERRO_ABRIR_ARQUIVO);
        // Retornando caso não encontre o arquivo.
        return ERRO;
    }

    // Inicializando variáveis.
    int qtdCidades = 0;
    int cargaCaminhao = 0;
    int somatorioDemandas = 0;

    // Lendo a quantidade de cidades (N).
    fscanf(pArquivo, "%d", &qtdCidades);

    // Lendo a capacidade do caminhão (Qv).
    fscanf(pArquivo, "%d", &cargaCaminhao);

    // Definindo as estruturas baseado na quantidade de cidades do arquivo.
    struct Cidade cidades[qtdCidades];

    // Adicionando o depósito.
    int distanciaCidades[qtdCidades + 1][qtdCidades + 1];
    int locaisParaCombinar[qtdCidades];

    int totalCombinacoes = calculaQtdElementos(qtdCidades);
    int combinacoes[totalCombinacoes];

    // Lendo as demandas de cada cidade.
    for (int i = ZERO; i <= qtdCidades; i++)
    {
        struct Cidade cidade;
        fscanf(pArquivo, "%d ", &cidade.demanda);
        cidade.foiVisitada = false;

        cidades[i] = cidade;
        locaisParaCombinar[i] = (i + 1);
        somatorioDemandas += (int) cidade.demanda;
    }

    unsigned int qtdCaminhoes = somatorioDemandas / cargaCaminhao;

    printf("Printando matriz simetrica: \n");
    // Colocando valores em uma matriz simétrica (Ci para Cj).
    for (int i = ZERO; i <= qtdCidades; i++)
    {
        for (int j = ZERO; j <= qtdCidades; j++)
        {
            if (i == j)
            {
                distanciaCidades[i][j] = ZERO;
            }
            else if (i <= j)
            {
                if(fscanf(pArquivo, "%d", &distanciaCidades[i][j]) != EOF)
                {
                    distanciaCidades[j][i] = distanciaCidades[i][j];
                }
                else
                {
                    distanciaCidades[i][j] = NULO;
                    distanciaCidades[j][i] = NULO;
                }
            }

            printf("%02d ", distanciaCidades[i][j]);
        }

        printf("\n");
    }

    // Realiza todas as combinações possíveis.
    combinacao(locaisParaCombinar, combinacoes, qtdCidades);

    // Imprimindo combinações.
    printf("\nTodas as combinacoes possiveis: \n");
    for (int i = ZERO; i < totalCombinacoes; i++)
    {
        if (combinacoes[i] != SEPARADOR)
        {
            printf("%d ", combinacoes[i]);
        }
        else
        {
            printf("\n");
        }
    }

    printf("\nArray completo: \n");
    for (int i = ZERO; i < totalCombinacoes; i++)
    {
        if (combinacoes[i] == SEPARADOR)
        {
            printf("%c ", combinacoes[i]);
        }
        else
        {
            printf("%d ", combinacoes[i]);
        }
    }

    // -----------------------------------------------------------------------------------------------------------------

    int qtdItensCadaCombinacao[qtdCidades];

    for (int i = qtdCidades; i >= UM; i--)
    {
        qtdItensCadaCombinacao[qtdCidades - i] =
                calculaQtdCombinacoes(qtdCidades, i) * i + calculaQtdCombinacoes(qtdCidades, i);
    }

    printf("\n\nMELHORES CAMINHOS: \n");

    int demandaAtual = somatorioDemandas;

    int somaRota[DOIS] = {NULO, NULO};
    int tempRota[DOIS] = {NULO, NULO};

    int currLoop = ZERO;
    int currIndex = ZERO;

    while (currLoop < qtdCidades)
    {
        int i = ZERO;

        while (i < qtdItensCadaCombinacao[currLoop])
        {
            if (combinacoes[currIndex] == SEPARADOR)
            {
                if (somaRota[TOTAL_ROTA] < cargaCaminhao && somaRota[TOTAL_ROTA] < tempRota[TOTAL_ROTA] &&
                    somaRota[TOTAL_ROTA] <= demandaAtual || tempRota[TOTAL_ROTA] == NULO)
                {
                    tempRota[POSICAO_ROTA] = somaRota[POSICAO_ROTA];
                    tempRota[TOTAL_ROTA] = somaRota[TOTAL_ROTA];
                }

                somaRota[POSICAO_ROTA] = ZERO;
                somaRota[TOTAL_ROTA] = ZERO;
            }
            else
            {
                if (somaRota[POSICAO_ROTA] == NULO)
                {
                    somaRota[POSICAO_ROTA] = i;
                    somaRota[TOTAL_ROTA] = distanciaCidades[ZERO][combinacoes[currIndex]];
                }

                if (currIndex + 1 < qtdItensCadaCombinacao[currLoop])
                {
                    somaRota[TOTAL_ROTA] += distanciaCidades[combinacoes[currIndex]][combinacoes[currIndex + 1]];
                    int a = combinacoes[currIndex];
                    int b = combinacoes[currIndex + 1];
                    int c = a + b;
                }
            }

            i++;
            currIndex++;
        }

        if (tempRota[POSICAO_ROTA] != NULO)
        {
            i = ZERO;

            while (combinacoes[tempRota[POSICAO_ROTA] + i] != SEPARADOR)
            {
                printf("%d ", combinacoes[tempRota[POSICAO_ROTA] + i]);
                i++;
            }

            printf("\n");
            demandaAtual -= tempRota[TOTAL_ROTA];
        }

        currLoop++;
    }

    // -----------------------------------------------------------------------------------------------------------------


    fclose(pArquivo); // Fechando o arquivo.
    pArquivo = NULL; // Setando ponteiro como nulo.

    double tempoTotal = calculaTempo(inicioClock);

    printf("\nTempo total = %0.2lf segundos.\n", tempoTotal);


    return ZERO;
}


/*
 * Função usada para iniciar o clock.
 * Retorna valor de quando a função "clock()" é chamada.
 */
double inicializaClock(void)
{
    return (double) clock();
}


/*
 * Função usada para finalizar o clock e calcular o tempo total.
 *
 * @param    tempoInicial    valor da primeira vez que a função "clock()" foi chamada.
 * @return                   valor calculado referente ao tempo entre o tempo inicial e o tempo final.
 */
double calculaTempo(double tempoInicial)
{
    return (double) (clock() - tempoInicial) / CLOCKS_PER_SEC;
}

