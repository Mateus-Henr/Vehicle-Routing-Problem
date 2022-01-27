#include <stdio.h>

#include "permutacao.h"

#define ZERO 0
#define UM 1
#define ERRO (-1)

// Imprime array (temporário)
void imprimeArray(int *array, int tamanho)
{
    for (int i = ZERO; i < tamanho; i++)
    {
        printf("%d ", array[i]);
    }

    printf("\n");
}


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
 * Realiza todas as permutações possíveis de um array de forma recursiva.
 *
 * @param    array    ponteiro para o array.
 * @param    inicio   posição inicial do array.
 * @param    fim      posição final do array.
 */
void permutacao(int *array, int inicio, int fim)
{
    if (inicio == fim)
    {
        imprimeArray(array, fim + UM);
        return;
    }

    for (int i = inicio; i <= fim; i++)
    {
        // Mudando posições dos números.
        mudarPosicao((array + i), (array + inicio));

        // Arrumando primeiro digito e chamando a função "permutacao()" no resto dos digitos.
        permutacao(array, inicio + UM, fim);
        mudarPosicao((array + i), (array + inicio));
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
    int sum;

    if (numero < ZERO)
    {
        return ERRO;
    }

    for (int i = UM; i < numero; i++)
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
//    permutacao(arr, 0, size - 1);
//
//    return 0;
//}