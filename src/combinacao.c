#include <stdlib.h>
#include "combinacao.h"

#define ZERO 0
#define UM 1
#define ERRO (-1)
#define DOIS 2

// Protótipos de funções.

void calculaPetala(int *arr, int *data, int **arrFinal, int *pIdxArr, int inicio, int fim, int idx, int r);

int fatorial(int numero);


/*
 *  Calcula todas as possibilidades de combinações de um dado array de inteiros para todas as variações de quantidade
 *  de itens.
 *
 *  @param   array          ponteiro para o array que possui os itens.
 *  @param   arrayFinal     ponteiro para o array que armazenará todas as possibilidades.
 *  @param   n              número de possibilidades para começar (o número de itens).
 */
void combinacao(int *array, int **arrayFinal, int n)
{
    int combinacaoAtual[n];
    int indexArray = ZERO;
    int *pIndexArray = &indexArray;

    for (int i = n; i >= UM; i--)
    {
        calculaPetala(array, combinacaoAtual, arrayFinal, pIndexArray, ZERO, n - UM, ZERO, i);
    }
}


/*
 * Calcula todas as possibilidades de combinações de um dado array de inteiros com uma quantidade de itens específica.
 * Utiliza recursão para tal cálculo.
 *
 * @param   arr             ponteiro para o array que possui os itens.
 * @param   data            ponteiro para o array que irá armazenar uma possibilidade por vez.
 * @param   arrFinal        ponteiro para o array que armazenará todas as possibilidades.
 * @param   pIdxArr         ponteiro de um inteiro usado para controlar o index do array com todas as possibilidades.
 * @param   inicio          index do início do array que armazena uma possibilidade por vez.
 * @param   fim             index do fim do array que armazena uma possibilidade por vez.
 * @param   idx             index atual do array que armazena uma possibilidade por vez.
 * @param   r               número de itens sendo escolhido.
 */
void calculaPetala(int *arr, int *data, int **arrFinal, int *pIdxArr, int inicio, int fim, int idx, int r)
{
    if (idx == r)
    {
        int *combinacaoAtual = (int *) malloc((r + DOIS) * sizeof(int));

        int j = ZERO;

        combinacaoAtual[j] = ZERO;

        for (j = ZERO; j < r; j++)
        {
            combinacaoAtual[j + UM] = data[j];
        }

        combinacaoAtual[j + UM] = ZERO;

        arrFinal[*pIdxArr] = combinacaoAtual;
        *pIdxArr = *pIdxArr + UM;

        return;
    }

    for (int i = inicio; i <= fim && fim - i + UM >= r - idx; i++)
    {
        data[idx] = arr[i];
        calculaPetala(arr, data, arrFinal, pIdxArr, i + UM, fim, idx + UM, r);
    }
}


/*
 * Calcula a quantidade de elementos que contém em todas as possibilidades de combinações possíveis.
 *
 * @param    n    número de possibilidades para começar.
 * @return        quantidade de combinação para os dados parâmetros. Em caso de valores inválidos, -1.
 */
int calculaQtdCombinacoesTotal(int n)
{
    if (n < ZERO)
    {
        return ERRO;
    }

    int soma = ZERO;

    for (int i = n; i >= UM; i--)
    {
        soma += calculaQtdCombinacoes(n, i);
    }

    return soma;
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
    int sum = UM;

    for (int i = UM; i <= numero; i++)
    {
        sum *= i;
    }

    return sum;
}