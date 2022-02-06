#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "permutacao.h"

#define ZERO 0
#define UM 1
#define DOIS 2


// Variáveis globais.

bool foiInicializado = false;
int cargaCaminhao = ZERO;
struct Cidade *cidades = NULL;
int **distanciaCidades = NULL;


// Protótipos de funções.

void calculaPetala(int *arr, int *data, int inicio, int fim, int idx, int r, int *pMelhorDist, int *melhorDistValor);

void fazPermutacoes(int *data, int tamanho, int n, int *pMelhorDist, int *melhorDistValor);

void troca(int *a, int *b);

int fatorial(int numero);

void liberaMemoria(int numCidades);



/*
 * Inicializa variáveis globais para serem usadas em outras funções.
 *
 * @param    arrayCidades       ponteiro para array que contém as estruturas cidades.
 * @param    numCidades         a quantidade de cidades.
 * @param    matrizDistancias   ponteiro para a matriz de distâncias entre as cidades.
 * @param    caminhao           a capacidade do caminhão.
 */
void inicializa(struct Cidade *arrayCidades, int numCidades, int **matrizDistancias, int caminhao)
{
    distanciaCidades = (int **) malloc(numCidades * sizeof(int *));

    for (int i = ZERO; i < numCidades; i++)
    {
        distanciaCidades[i] = (int *) malloc(numCidades * sizeof(int));

        for (int j = ZERO; j < numCidades; j++)
        {
            distanciaCidades[i][j] = matrizDistancias[i][j];
        }
    }

    cidades = (struct Cidade *) malloc(numCidades * sizeof(struct Cidade));

    for (int i = ZERO; i < numCidades; i++)
    {
        cidades[i] = arrayCidades[i];
    }

    cargaCaminhao = caminhao;
    foiInicializado = true;
}


/*
 *  Calcula todas as possibilidades de combinações de um dado itens de inteiros para todas as variações de quantidade
 *  de itens.
 *
 *  @param   itens          ponteiro para o array que possui os itens.
 *  @param   rotaFinal      ponteiro para o array que armazenará a rota final (a melhor rota encontrada).
 *  @param   qtdItens       número de possibilidades para começar (o número de itens).
 */
void fazCombinacoes(int *itens, int *rotaFinal, int *pIndexArr, int qtdItens)
{
    // Retorna caso as variáveis globais não foram inicializadas.
    if (!foiInicializado)
    {
        return;
    }

    int combinacaoAtual[qtdItens];

    int melhorDistancia = ZERO;
    int *melhorV = &melhorDistancia;

    int melhor[qtdItens];
    int qtdDigitosAtual = qtdItens;

    while (qtdDigitosAtual)
    {
        calculaPetala(itens, combinacaoAtual, ZERO, qtdItens - UM, ZERO, qtdDigitosAtual, melhor, melhorV);

        // Se encontrar cidade que passe nas condições.
        if (melhorDistancia != ZERO)
        {
            // Seta para zero novamente para checar se outra permutação passa nas condições.
            melhorDistancia = ZERO;

            // Adiciona zero no início da permutação.
            rotaFinal[(*pIndexArr)++] = ZERO;

            // Adiciona cidades encontrados no itens final.
            for (int i = ZERO; i < qtdDigitosAtual; i++)
            {
                rotaFinal[(*pIndexArr)++] = melhor[i];
                cidades[melhor[i]].foiVisitada = true;
            }

            // Adiciona zero no final da permutação.
            rotaFinal[(*pIndexArr)++] = ZERO;

            // Checa a mesmo digito novamente. Não optimizado.
            continue;
        }

        qtdDigitosAtual--;
    }

    liberaMemoria(qtdItens);
}


/*
 * Calcula todas as possibilidades de combinações de um dado array de inteiros com uma quantidade de itens específica.
 * Utiliza recursão para tal cálculo.
 *
 * @param    arr                 ponteiro para o array que possui os itens.
 * @param    data                ponteiro para o array que irá armazenar uma possibilidade por vez.
 * @param    inicio              index do início do array que armazena uma possibilidade por vez.
 * @param    fim                 index do fim do array que armazena uma possibilidade por vez.
 * @param    idx                 index atual do array que armazena uma possibilidade por vez.
 * @param    r                   número de itens sendo escolhido.
 * @param    pMelhorDist         ponteiro para array que contém melhor permutação encontrada até então.
 * @param    melhorDistValor     ponteiro para valor da distância total da melhor permutação encontrada até então.
 */
void calculaPetala(int *arr, int *data, int inicio, int fim, int idx, int r, int *pMelhorDist, int *melhorDistValor)
{
    // Entra nessa condição quando tiver uma combinação pronta.
    if (idx == r)
    {
        // Criando outro array, pois em C não existe "pass by value" quando usando arrays. Em outras palavras, criando array para ser
        // modificado.
        int novoData[r];

        for (int i = ZERO; i < r; i++)
        {
            novoData[i] = data[i];
        }

        // Realizando permutações a partir da combinação encontrada.
        fazPermutacoes(novoData, r, r, pMelhorDist, melhorDistValor);

        return;
    }

    for (int i = inicio; i <= fim && fim - i + UM >= r - idx; i++)
    {
        data[idx] = arr[i];
        calculaPetala(arr, data, i + UM, fim, idx + UM, r, pMelhorDist, melhorDistValor);
    }
}


/*
 * Usa a permutação de Heap para gerar todas as permutações.
 *
 * @param    data                array para ser permutado.
 * @param    tamanho             tamanho do array (será mudado).
 * @param    n                   tamanho do array.
 * @param    pMelhorDist         ponteiro para array que contém melhor permutação encontrada até então.
 * @param    melhorDistValor     ponteiro para valor da distância total da melhor permutação encontrada até então.
 */
void fazPermutacoes(int *data, int tamanho, int n, int *pMelhorDist, int *melhorDistValor)
{
    // Entra nessa condição se tiver uma permutação pronta.
    if (tamanho == UM)
    {
        unsigned int demandaTotal = ZERO;

        for (int i = ZERO; i < n; i++)
        {
            // Associando com index em cidades.
            int cidadeAtual = data[i];

            if (cidades[cidadeAtual].foiVisitada)
            {
                return;
            }

            demandaTotal += cidades[cidadeAtual].demanda;
        }

        bool otimizaRota = (demandaTotal <= cargaCaminhao);

        if ((demandaTotal % cargaCaminhao) == ZERO)
        {
            otimizaRota = (demandaTotal == cargaCaminhao);
        }

        if (otimizaRota)
        {
            int totalDistance = ZERO;

            totalDistance = distanciaCidades[ZERO][data[ZERO]];
            for (int i = ZERO; i < n - UM; i++)
            {
                totalDistance += distanciaCidades[data[i]][data[i + UM]];
            }
            totalDistance += distanciaCidades[ZERO][data[n - UM]];


            if (totalDistance < *melhorDistValor || *melhorDistValor == ZERO)
            {
                *melhorDistValor = totalDistance;

                for (int i = ZERO; i < n; i++)
                {
                    pMelhorDist[i] = data[i];
                }
            }
        }

        return;
    }

    for (int i = ZERO; i < tamanho; i++)
    {
        fazPermutacoes(data, tamanho - UM, n, pMelhorDist, melhorDistValor);

        if (tamanho % DOIS == UM)
        {
            troca(data, data + (tamanho - UM));
        }
        else
        {
            troca(data + i, data + (tamanho - UM));
        }
    }
}


/*
 * Troca valores dos elementos dados na memória.
 *
 * @param    a    primeiro valor.
 * @param    b    segundo valor.
 */
void troca(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}


/*
 * Calcula a quantidade de combinações possíveis usando a seguinte fórmula:
 *  n! / (r! (n - r)!)
 *
 * @param    n    número de possibilidades para começar (o número de itens).
 * @param    r    número de itens sendo escolhido.
 * @return        número de combinações possíveis pelos dados parâmetros.
 */
int calculaQtdCombinacoes(int n, int r)
{
    return fatorial(n) / (fatorial(r) * fatorial(n - r));
}


/*
 * Calcula o fatorial de um número.
 *
 * @param   numero   o número para ser calculado o fatorial.
 * @return           o fatorial do número dado.
 */
int fatorial(int numero)
{
    int soma = UM;

    for (int i = UM; i <= numero; i++)
    {
        soma *= i;
    }

    return soma;
}


void liberaMemoria(int numCidades)
{
    // Retorna caso as variáveis globais não foram inicializadas.
    if (!foiInicializado)
    {
        return;
    }

    for (int i = ZERO; i < numCidades; i++)
    {
        free(distanciaCidades[i]);
    }

    free(distanciaCidades);
    free(cidades);
}