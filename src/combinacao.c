#include <stdio.h>

#include "combinacao.h"

#define ZERO 0
#define UM 1
#define DOIS 2
#define ERRO (-1)


///*
// * Muda os valores do vetor na memória.
// *
// * @param    a   valor para ser trocado.
// * @param    b   valor para ser trocado.
// */
//void mudarPosicao(int *a, int *b)
//{
//    int temp;
//    temp = *a;
//    *a = *b;
//    *b = temp;
//}
//
//
///*
// * Realiza todas as combinações possíveis de elementos de um array e coloca os resultados em outro array.
// *
// * @param    arrayParaPermutar    ponteiro para o array.
// * @param    arrayPermutacoes     ponteiro para o array em que serão armazenados as permutações.
// * @param    inicio               posição inicial do array.
// * @param    fim                  posição final do array.
// */
//void combination(int *arrayParaPermutar, int *arrayPermutacoes, int qtdElementos)
//{
//    int c[qtdElementos], j = ZERO;
//
//    for (int i = ZERO; i < qtdElementos; i++, j++)
//    {
//        c[i] = ZERO;
//        arrayPermutacoes[j] = arrayParaPermutar[i];
//    }
//
//    int i = ZERO;
//    while (i < qtdElementos)
//    {
//        if (c[i] < i)
//        {
//            if (i % DOIS == ZERO)
//            {
//                mudarPosicao(arrayParaPermutar, arrayParaPermutar + i);
//            }
//            else
//            {
//                mudarPosicao(arrayParaPermutar + c[i], arrayParaPermutar + i);
//            }
//
//            for (int k = ZERO; k < qtdElementos; k++, j++)
//            {
//                arrayPermutacoes[j] = arrayParaPermutar[k];
//            }
//
//            c[i] += 1;
//            i = 0;
//        }
//        else
//        {
//            c[i++] = 0;
//        }
//    }
//}
//
//
///*
// * Calcula fatorial de um número.
// *
// * @param   numero   um numero.
// * @return           o fatorial do número caso exista, caso não exista -1.
// */
//int fatorial(int numero)
//{
//    int sum = UM;
//
//    if (numero < ZERO)
//    {
//        return ERRO;
//    }
//
//    for (int i = UM; i <= numero; i++)
//    {
//        sum *= i;
//    }
//
//    return sum;
//}


/*
 * [comb.c]
 * Programa que gera todas as combinações dos caracteres
 * de uma string de entrada.
 *
 * [Autor]
 * Marcos Paulo Ferreir (Daemonio)
 * undefinido gmail com
 * https://daemoniolabs.wordpress.com/
 *
 * [Uso]
 * $ gcc -o comb comb.c
 * $ echo 'abcd' | ./comb
 *
 * Versão 1.0 by daemonio @ Thu Feb 17 08:17:31 BRST 2011
 *
 */
#include <stdio.h>
#include <string.h>

/* Tamanho máximo da entrada */
#define MAX_INPUT 31

void combinaPetalas(int *locaisParaCombinar)
{
    unsigned MAX, MASK, NUM;
    int i, j;
    /* Armazena a string de entrada. */
    /* Armazena cada combinação. */
    char str[MAX_INPUT];


    /* Manda o bit 1 para a n-ésima posição.
     * Os bits são invertidos para que a posição n
     * esteja com o bit zero, a fim de marcar
     * o final do processo.
     */
    MAX = ~(1 << strlen(locaisParaCombinar));

    /* Primeiro número é o 1. */
    NUM = 1;

    putchar('\n');

    /* Quando o número alcançar MAX, o loop
     * será encerrado.
     */
    while (MAX & NUM)
    {
        MASK = 1;
        i = j = 0;

        while (MAX & MASK)
        {
            /* Verdadeiro se NUM tem um bit 1
             * na posição indicada por MASK. */
            if (NUM & MASK)
            {
                /* Gera a combinação em str. */
                str[i] = locaisParaCombinar[j];
                i++;
            }
            j++;
            /* Desloca a máscara */
            MASK = MASK << 1;
        }

        str[i] = 0;
        printf("%s\n", str);

        NUM++;
    }
}

int fatorial(int n)
{
    if (n > 0)
    {
        return n * fatorial(n - 1);
    }
    else
    {
        return 1;
    }
}

int arranjo(int numero, int posicoes)
{
    if (posicoes > 1)
    {
        return numero * arranjo(numero - 1, posicoes - 1);
    }
    else
    {
        return numero;
    }
}

int combinacao(int numero, int posicoes)
{
    return arranjo(numero, posicoes) / fatorial(posicoes);
}