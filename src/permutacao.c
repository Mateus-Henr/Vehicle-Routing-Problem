#include <stdio.h>

#include "permutacao.h"

#define ZERO 0
#define UM 1
#define DOIS 2
#define ERRO (-1)


/*
 * Muda os valores do vetor na memória.
 *
 * @param    a   valor para ser trocado.
 * @param    b   valor para ser trocado.
 */
void mudarPosicao(int *a, int *b)
{
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}


/*
 * Realiza todas as combinações possíveis de elementos de um array e coloca os resultados em outro array.
 *
 * @param    arrayParaPermutar    ponteiro para o array.
 * @param    arrayPermutacoes     ponteiro para o array em que serão armazenados as permutações.
 * @param    inicio               posição inicial do array.
 * @param    fim                  posição final do array.
 */
void combination(int *arrayParaPermutar, int *arrayPermutacoes, int qtdElementos)
{
    int c[qtdElementos], j = ZERO;

    for (int i = ZERO; i < qtdElementos; i++, j++)
    {
        c[i] = ZERO;
        arrayPermutacoes[j] = arrayParaPermutar[i];
    }

    int i = ZERO;
    while (i < qtdElementos)
    {
        if (c[i] < i)
        {
            if (i % DOIS == ZERO)
            {
                mudarPosicao(arrayParaPermutar, arrayParaPermutar + i);
            }
            else
            {
                mudarPosicao(arrayParaPermutar + c[i], arrayParaPermutar + i);
            }

            for (int k = ZERO; k < qtdElementos; k++, j++)
            {
                arrayPermutacoes[j] = arrayParaPermutar[k];
            }

            c[i] += 1;
            i = 0;
        }
        else
        {
            c[i++] = 0;
        }
    }
}


/*
 * Calcula fatorial de um número.
 *
 * @param   numero   um numero.
 * @return           o fatorial do número caso exista, caso não exista -1.
 */
int fatorial(int numero)
{
    int sum = UM;

    if (numero < ZERO)
    {
        return ERRO;
    }

    for (int i = UM; i <= numero; i++)
    {
        sum *= i;
    }

    return sum;
}


// Testing purposes
//int main()
//{
//    int size = 0;
//
//    printf("Enter the size of array:\n");
//    scanf("%d", &size);
//
//    int arr[size];
//
//    for (int i = 0; i < size; i++)
//    {
//        printf("%d: \n", (i + 1));
//        scanf("%d", &arr[i]);
//    }
//
//    combination(arr, 0, size - 1);
//
//    return 0;
//}