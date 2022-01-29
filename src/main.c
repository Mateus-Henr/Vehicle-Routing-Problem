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

void imprimeCombinacoes(int *arrayCombinacoes, int totalCombinacoes);

int calculaDimensoesMatriz(int qtdElementos);


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

    // Definindo array da estrutura Cidade para armazenar as cidades.
    struct Cidade cidades[qtdCidades];

    // Definindo matriz para armazenar as distâncias entre as cidades/depósito. Adicionando um para o depósito.
    int distanciaCidades[qtdCidades + 1][qtdCidades + 1];

    // Array com os elementos para fazer combinações.
    int locaisParaCombinar[qtdCidades];

    // Calculando a quantidade de espaços que a matriz terá e definindo a matriz baseado nesse valor.
    int totalElementosNaMatriz = calculaQtdElementos(qtdCidades);
    int combinacoes[totalElementosNaMatriz];

    // Lendo as demandas de cada cidade.
    for (int i = ZERO; i < qtdCidades; i++)
    {
        struct Cidade cidade;
        fscanf(pArquivo, "%d ", &cidade.demanda);
        cidade.foiVisitada = false;

        cidades[i] = cidade;
        locaisParaCombinar[i] = (i + 1);
        somatorioDemandas += (int) cidade.demanda;
    }

    // Calculando a quantidade de caminhões.
    unsigned int qtdCaminhoes = somatorioDemandas / cargaCaminhao;
    printf("Quantidade caminhoes: %d\n", qtdCaminhoes);

    // Calculando dimensões para a matriz simétrica baseada na quantidade de elementos da mesma.
    int dimensaoMatriz = calculaDimensoesMatriz(qtdCidades);

    // Colocando valores do arquivo em uma matriz simétrica (Ci para Cj).
    printf("\nPrintando matriz simetrica: \n");
    for (int i = ZERO; i < dimensaoMatriz; i++)
    {
        for (int j = ZERO; j < dimensaoMatriz; j++)
        {
            if (i == j)
            {
                distanciaCidades[i][j] = ZERO;
            }
            else if (i <= j)
            {
                if (fscanf(pArquivo, "%d", &distanciaCidades[i][j]) != EOF)
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
    imprimeCombinacoes(combinacoes, totalElementosNaMatriz);


    // ----------------------- ESBOÇO CÓDIGO QUE CALCULA A MAIS OPTIMIZADA DISTÂNCIA -----------------------------------

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

                somaRota[POSICAO_ROTA] = NULO;
                somaRota[TOTAL_ROTA] = NULO;
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

    // Calculando tempo total de execução do programa.
    double tempoTotal = calculaTempo(inicioClock);

    printf("\nTempo total = %0.2lf segundos.\n", tempoTotal);


    return ZERO;
}


/*
 * Inicia o clock.
 * @return      valor de quando a função "clock()" é chamada.
 */
double inicializaClock(void)
{
    return (double) clock();
}


/*
 * Finaliza o clock e calcular o tempo total.
 *
 * @param    tempoInicial    valor da primeira vez que a função "clock()" foi chamada.
 * @return                   valor calculado referente ao tempo entre o tempo inicial e o tempo final.
 */
double calculaTempo(double tempoInicial)
{
    return (double) (clock() - tempoInicial) / CLOCKS_PER_SEC;
}


/*
 * Calcula a miníma dimensão para a matriz simétrica necessária para armazenar as distâncias.
 *
 * @param    qtdElementos    número de elementos.
 * @return                   dimensão para matriz simétrica.
 */
int calculaDimensoesMatriz(int qtdElementos)
{
    int dimensaoMatriz = UM;
    int sum = ZERO - UM;

    while (sum < qtdElementos)
    {
        sum += dimensaoMatriz++;
    }

    return dimensaoMatriz;
}


/*
 * TESTING PURPOSES.
 */
void imprimeCombinacoes(int *arrayCombinacoes, int totalCombinacoes)
{
    printf("\nTodas as combinacoes possiveis: \n");
    for (int i = ZERO; i < totalCombinacoes; i++)
    {
        if (arrayCombinacoes[i] != SEPARADOR)
        {
            printf("%d ", arrayCombinacoes[i]);
        }
        else
        {
            printf("\n");
        }
    }

    printf("\nArray completo: \n");
    for (int i = ZERO; i < totalCombinacoes; i++)
    {
        if (arrayCombinacoes[i] == SEPARADOR)
        {
            printf("%c ", arrayCombinacoes[i]);
        }
        else
        {
            printf("%d ", arrayCombinacoes[i]);
        }
    }
}