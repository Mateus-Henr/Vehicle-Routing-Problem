#include <stdio.h>
#include <stddef.h>

#include "combinacao.h"

#define ZERO 0
#define UM 1
#define ERRO (-1)

/*
 * Calcula fatorial de um número.
 *
 * @param   numero   um numero.
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

int qtdCombinacoes(int n, int r)
{
    return fatorial(n) / (fatorial(r) * fatorial(n - r));
}

void cadaCombinacao(int *array, int *data, int *arrayFinal, int *pIndexArray, int inicio, int fim, int index, int r)
{
    if (index == r)
    {
        for (int j = ZERO; j < r; j++)
        {
            arrayFinal[*pIndexArray] = data[j];
            *pIndexArray = *pIndexArray + 1;
        }

        // JUST FOR TESTING
        arrayFinal[*pIndexArray] = ZERO;
        *pIndexArray = *pIndexArray + UM;

        return;
    }

    for (int i = inicio; i <= fim && fim - i + UM >= r - index; i++)
    {
        data[index] = array[i];
        cadaCombinacao(array, data, arrayFinal, pIndexArray, i + UM, fim, index + UM, r);
    }
}

void combinacao(int *array, int *arrayFinal, int n)
{
    int data[n];
    int indexArray = ZERO;
    int *pIndexArray = &indexArray;

    for (int i = n; i >= UM; i--)
    {
        cadaCombinacao(array, data, arrayFinal, pIndexArray, ZERO, n - UM, ZERO, i);
    }
}

/*
 * Calcula a quantidade de combinações possíveis para uma quantidade de elementos.
 *
 * @param    n    número de possibilidades para começar.
 * @return        quantidade de combinação para os dados parâmetros. Em caso de valores inválidos, -1.
 */
int qtdTotalCombinacoes(int n)
{
    if (n < ZERO)
    {
        return ERRO;
    }

    int soma = ZERO;

    for (int i = n; i >= UM; i--)
    {
        soma += qtdCombinacoes(n, i) * i + qtdCombinacoes(n, i); // ADICIONANDO UM PARA TESTE
    }

    return soma;
}