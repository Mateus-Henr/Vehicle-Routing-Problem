#include <stddef.h>

#include "combinacao.h"

#define ZERO 0
#define UM 1
#define ERRO (-1)

void cadaCombinacao(int *array, int *data, int *arrayFinal, int *pIndexArrayFinal, int inicio, int fim, int index, int r)
{
    if (index == r)
    {
        for (int j = ZERO; j < r; j++)
        {
            arrayFinal[*pIndexArrayFinal] = data[j];
        }

        return;
    }

    for (int i = inicio; i <= fim && fim - i + UM >= r - index; i++)
    {
        data[index] = array[i];
        cadaCombinacao(array, data, arrayFinal, pIndexArrayFinal + UM, i + UM, fim, index + UM, r);
    }
}

void combinacao(int *array, int *arrayFinal, int n)
{
    int data[n];
    int indexArrayFinal = ZERO;
    int *pIndexArrayFinal = &indexArrayFinal;

    for (int i = n; i >= UM; i--)
    {
        cadaCombinacao(array, data, arrayFinal, pIndexArrayFinal, ZERO, n - UM, ZERO, i);
    }
}


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

    int sum = ZERO;

    for (int i = n; i >= UM; i--)
    {
        sum += fatorial(n) / (fatorial(i) * fatorial(n - i));
    }

    return sum;
}