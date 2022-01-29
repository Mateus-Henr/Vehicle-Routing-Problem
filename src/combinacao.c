#include "combinacao.h"

#define ZERO 0
#define UM 1
#define ERRO (-1)

// Protótipos de funções.

void calculaPetala(int *array, int *data, int *arrayFinal, int *pIndexArray, int inicio, int fim, int index, int r);


/*
 *  Calcula todas as possibilidades de combinações de um dado array de inteiros para todas as variações de quantidade
 *  de itens.
 *
 *  @param   array          ponteiro para o array que possui os itens.
 *  @param   arrayFinal     ponteiro para o array que armazenará todas as possibilidades.
 *  @param   n              número de possibilidades para começar (o número de itens).
 */
void combinacao(int *array, int *arrayFinal, int n)
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
 * @param   array           ponteiro para o array que possui os itens.
 * @param   data            ponteiro para o array que irá armazenar uma possibilidade por vez.
 * @param   arrayFinal      ponteiro para o array que armazenará todas as possibilidades.
 * @param   pIndexArray     ponteiro de um inteiro usado para controlar o index do array com todas as possibilidades.
 * @param   inicio          index do início do array que armazena uma possibilidade por vez.
 * @param   fim             index do fim do array que armazena uma possibilidade por vez.
 * @param   index           index atual do array que armazena uma possibilidade por vez.
 * @param    r              número de itens sendo escolhido.
 */
void calculaPetala(int *array, int *data, int *arrayFinal, int *pIndexArray, int inicio, int fim, int index, int r)
{
    if (index == r)
    {
        for (int j = ZERO; j < r; j++)
        {
            arrayFinal[*pIndexArray] = data[j];
            *pIndexArray = *pIndexArray + 1;
        }

        // JUST FOR TESTING
        arrayFinal[*pIndexArray] = SEPARADOR;
        *pIndexArray = *pIndexArray + UM;

        return;
    }

    for (int i = inicio; i <= fim && fim - i + UM >= r - index; i++)
    {
        data[index] = array[i];
        calculaPetala(array, data, arrayFinal, pIndexArray, i + UM, fim, index + UM, r);
    }
}


/*
 * Calcula a quantidade de elementos que contém em todas as possibilidades de combinações possíveis.
 *
 * @param    n    número de possibilidades para começar.
 * @return        quantidade de combinação para os dados parâmetros. Em caso de valores inválidos, -1.
 */
int calculaQtdElementos(int n)
{
    if (n < ZERO)
    {
        return ERRO;
    }

    int soma = ZERO;

    for (int i = n; i >= UM; i--)
    {
        soma += calculaQtdCombinacoes(n, i) * i + calculaQtdCombinacoes(n, i);
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