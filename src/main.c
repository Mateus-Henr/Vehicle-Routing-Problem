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

int calculaQtdElementosMatriz(int n);

void imprimeCombinacoes(int **arrayCombinacoes, int totalCombinacoes, int *qtdItens, int *qtdCombItem);


/*
 * A função principal. Tem como função a leitura de informações de um arquivo e manipulação dos dados.
 *
 * @return          0 se executado com sucesso, -1 se ocorrer algum erro.
 */
int main(void)
{
    // Inicializando o inicioClock.
    double inicioClock = inicializaClock();


    /// ------------------------------------------- OPERAÇÕES NO ARQUIVO -----------------------------------------------

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

    int qtdCombinacoes = calculaQtdCombinacoesTotal(qtdCidades);
    int *combinacoes[qtdCombinacoes];

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

    int qtdElementos = calculaQtdElementosMatriz(qtdCidades);

    // Colocando valores do arquivo em uma matriz simétrica (Ci para Cj).
    for (int k = UM; k <= qtdElementos; k++)
    {
        int i = ZERO;
        int j = ZERO;

        fscanf(pArquivo, "%d", &i);
        fscanf(pArquivo, "%d", &j);
        fscanf(pArquivo, "%d", &distanciaCidades[i][j]);
        distanciaCidades[j][i] = distanciaCidades[i][j];
    }

    // Imprime a matriz
    for (int i = ZERO; i < qtdCidades; i++)
    {
        for (int j = ZERO; j < qtdCidades; i++)
        {
            printf("%d ", distanciaCidades[i][j]);
        }

        printf("\n");
    }

    // Fim das operações no arquivo.
    fclose(pArquivo); // Fechando o arquivo.
    pArquivo = NULL; // Setando ponteiro como nulo.

    /// -------------------------------------- FIM DE OPERAÇÕES NO ARQUIVO ---------------------------------------------



    /// ----------------------------------------- PROCESSAMENTO DOS DADOS ----------------------------------------------

    // Array para armazenar quantidade de combinações para cada quantidade de elementos.
    int qtdItensCadaCombinacao[qtdCidades];
    int qtdCombinacoesItem[qtdCidades];

    for (int i = qtdCidades; i >= UM; i--)
    {
        qtdItensCadaCombinacao[qtdCidades - i] = i + DOIS;
        // Colocando a quantidade de combinações para cada quantidade de elementos.
        qtdCombinacoesItem[qtdCidades - i] = calculaQtdCombinacoes(qtdCidades, i);
    }


    // Realiza todas as combinações possíveis.
    combinacao(locaisParaCombinar, combinacoes, qtdCidades);

    // Imprimindo combinações.
    // imprimeCombinacoes(combinacoes, qtdCombinacoes, qtdItensCadaCombinacao, qtdCombinacoesItem);



    /// ---------------------------- ESBOÇO CÓDIGO QUE CALCULA A ROTA MAIS OPTIMIZADA ----------------------------------

    int *melhoresRotas[qtdCombinacoes];
    int qtdDigitosCadaComb[qtdCidades];
    int qtdCombsDeCadaDigito[qtdCidades];
    int rotasEncontradas = ZERO;
    int indexAtual = ZERO;

    int posIndexCadaDigito = ZERO;

    for (int qtdDigitosAtual = ZERO; qtdDigitosAtual < qtdCidades; qtdDigitosAtual++)
    {
        bool encontrou = false;
        int qtdEncontradas = ZERO;

        for (int qtdCombsDeUmDigito = ZERO; qtdCombsDeUmDigito < qtdCombinacoesItem[qtdDigitosAtual]; qtdCombsDeUmDigito++)
        {
            int *combinacaoAtual = combinacoes[indexAtual++];
            int demandaRota = ZERO;

            // Ignorando 0s, esse é o motivo de estarmos começando de 1 e terminando em qtd algarismos menos 1.
            for (int qtdDigitosDaComb = UM; qtdDigitosDaComb < qtdItensCadaCombinacao[qtdDigitosAtual] - 1; qtdDigitosDaComb++)
            {
                demandaRota += (int) cidades[combinacaoAtual[qtdDigitosDaComb] - 1].demanda;
            }

            if (demandaRota <= cargaCaminhao)
            {
                qtdCombsDeCadaDigito[posIndexCadaDigito] = ++qtdEncontradas;
                qtdDigitosCadaComb[posIndexCadaDigito] = qtdItensCadaCombinacao[qtdDigitosAtual];

                melhoresRotas[rotasEncontradas++] = combinacaoAtual;
                encontrou = true;
            }
        }

        if (encontrou)
        {
            posIndexCadaDigito++;
        }
    }

    indexAtual = ZERO;
    int tamanhoArrayFinal = ZERO;
    int *rotaFinal[qtdCombinacoes];
    int indexRotaFinal = ZERO;
    int melhorDistanciaValor = ZERO;
    int *melhorDistancia = NULL;
    int digitoAtual = ZERO;
    int posicoesArray[qtdCidades];

    for (int qtdDigitosAtual = ZERO; qtdDigitosAtual < posIndexCadaDigito; qtdDigitosAtual++)
    {
        for (int multiploNoMsmDigito = ZERO; multiploNoMsmDigito < qtdCombsDeCadaDigito[qtdDigitosAtual]; multiploNoMsmDigito++)
        {
            bool cidadeJaVisitada = false;
            bool encontrou = false;

            for (int qtdCombsDeUmDigito = digitoAtual; qtdCombsDeUmDigito < qtdCombsDeCadaDigito[qtdDigitosAtual] + digitoAtual; qtdCombsDeUmDigito++)
            {
                int distanciaRota = ZERO;
                cidadeJaVisitada = false;

                for (int qtdDigitosDaComb = ZERO; qtdDigitosDaComb < qtdDigitosCadaComb[qtdDigitosAtual] - 1; qtdDigitosDaComb++)
                {
                    if (melhoresRotas[qtdCombsDeUmDigito][qtdDigitosDaComb] != ZERO)
                    {
                        if (cidades[melhoresRotas[qtdCombsDeUmDigito][qtdDigitosDaComb] - 1].foiVisitada)
                        {
                            cidadeJaVisitada = true;
                        }
                    }

                    distanciaRota +=
                            distanciaCidades[melhoresRotas[qtdCombsDeUmDigito][qtdDigitosDaComb]]
                            [melhoresRotas[qtdCombsDeUmDigito][qtdDigitosDaComb + UM]];
                }

                if (distanciaRota < melhorDistanciaValor && !cidadeJaVisitada || melhorDistancia == NULL && !cidadeJaVisitada)
                {
                    melhorDistanciaValor = distanciaRota;
                    melhorDistancia = melhoresRotas[qtdCombsDeUmDigito];
                    encontrou = true;
                }
            }

            if (encontrou)
            {
                posicoesArray[indexRotaFinal] = qtdDigitosCadaComb[qtdDigitosAtual];
                tamanhoArrayFinal += qtdDigitosCadaComb[qtdDigitosAtual];
                rotaFinal[indexRotaFinal++] = melhorDistancia;

                for (int i = ZERO; i < indexRotaFinal; i++)
                {
                    for (int j = ZERO; j < qtdDigitosCadaComb[qtdDigitosAtual]; j++)
                    {
                        if (rotaFinal[i][j] != ZERO)
                        {
                            cidades[rotaFinal[i][j] - 1].foiVisitada = true;
                        }
                    }
                }

                melhorDistanciaValor = ZERO;
                melhorDistancia = NULL;
            }
        }

        digitoAtual += qtdCombsDeCadaDigito[qtdDigitosAtual];
    }

    int oCaminho[tamanhoArrayFinal];
    int index = ZERO;

    for (int i = ZERO; i < indexRotaFinal; i++)
    {
        for (int j = ZERO; j < posicoesArray[i]; j++)
        {
            oCaminho[index++] = rotaFinal[i][j];
        }
    }

    printf("\nTHE FUCKING FINAL ROUTE: \n");
    for (int i = ZERO; i < tamanhoArrayFinal; i++)
    {
        printf("%d ", oCaminho[i]);
    }


    /// ------------------------- FIM DO ESBOÇO CÓDIGO QUE CALCULA A ROTA MAIS OPTIMIZADA ------------------------------


    /// ------------------------------------- FIM DO PROCESSAMENTO DOS DADOS -------------------------------------------


    // Calculando tempo total de execução do programa.
    double tempoTotal = calculaTempo(inicioClock);

    printf("\n\nTempo total = %0.2lf segundos.\n", tempoTotal);


    return ZERO;
}


/*
 * Calcula quantos elementos o usuário pode adicionar na matriz simétrica.
 *
 * @param    n    quantidade de linhas da matriz.
 * @return        quantidade de elementos que o usuário pode adicionar na matriz simétrica
 */
int calculaQtdElementosMatriz(int n)
{
    int soma = ZERO;

    for (int i = n; i >= UM; i--)
    {
        soma += i;
    }

    return soma;
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
 * Finaliza o clock e calcula o tempo total.
 *
 * @param    tempoInicial    valor da primeira vez que a função "clock()" foi chamada.
 * @return                   valor calculado referente ao tempo entre o tempo inicial e o tempo final.
 */
double calculaTempo(double tempoInicial)
{
    return (double) (clock() - tempoInicial) / CLOCKS_PER_SEC;
}


/*
 * TESTING PURPOSES.
 */
void imprimeCombinacoes(int **arrayCombinacoes, int totalCombinacoes, int *qtdItens, int *qtdCombItem)
{
    printf("\nTodas as combinacoes possiveis: \n");
    int soma = qtdCombItem[ZERO];
    int indexAtual = ZERO;

    for (int i = ZERO; i < totalCombinacoes; i++)
    {
        if (i == soma)
        {
            soma += qtdCombItem[++indexAtual];
        }

        int *combinacaoAtual = arrayCombinacoes[i];

        for (int j = ZERO; j < qtdItens[indexAtual]; j++)
        {
            printf("%d ", combinacaoAtual[j]);
        }

        printf("\n");
    }
}