#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

char *PadronizaLista(char *vetor[])
{
    int i, tamanho;
    char *buffer[MAX], vetorFinal[MAX];
    /*Começa acrescentando os 0's e o NULL ao fim da lista*/
    tamanho = qtdCidades;
    for (i = 0; i < tamanho; i++)
    {
        const char *str2 = "0";
        const char *str1 = (char *) *vetor;
        strcat(strcpy((char *) buffer, (const char *) str1), (const char *) str2);
        vetor = buffer;
    }
    strcat(strcpy((char *) vetorFinal, (const char *) vetor), NULL);
    return (char *) vetorFinal;
}

char *vetor[] = {"1", "2", "3"};

/* Funcao que retorna verdadeiro se
 * `num' nao contem algarismos repetidos
 * e zero caso contrario. */
char eh_sem_repeticao(int *num, int r)
{
    int i, j;

    for (i = 0; i < r; i++)
    {
        for (j = 0; j < r && i != j; j++)
        {
            if (num[i] == num[j])
            {
                return 0;
            }
        }
    }

    return 1;
}

int main(int argc, char **argv)
{
    /* vetor que representara cada permutacao. */
    int *num;
    /* quantidade de elementos do vetor. */
    int n;
    /* tamanho de cada permutacao. */
    int r;
    /* controle de loop. */
    int i, j;
    /* Obtem a quantidade de elementos do vetor. */
    n = 0;
    while (vetor[n] != NULL) n++;

    /* Testa parametros da linha de comando. */
    if (argc > 1)
    {
        r = atoi(argv[1]);
    }
    else
    {
        r = n;
    }

    /* Sai do programa se r > n. */
    if (r > n)
    {
        printf("Nao faz sentido r > n.\n");
        return -1;
    }

    /* Aloca espaco para o vetor num. Lembre-se
     * que o vetor `num' representa um numero
     * na base n com r algarismos. */
    num = (int *) calloc(r + 1, sizeof(int));
    if (num == NULL)
    {
        perror("malloc");
        return -1;
    }

    /* Inicio do algoritmo. */
    while (num[r] == 0)
    {
        for (i = 0; i < n; i++)
        {
            /* Mostra a permutacao na tela se
             * e somente se `num' nao contem
             * algarismos repetidos. */
            if (eh_sem_repeticao(num, r))
            {
                for (j = 0; j < r; j++)
                {
                    printf("%s ", vetor[num[j]]);
                }
                putchar('\n');
            }

            /* incrementa o algarismo menos
             * significativo. */
            num[0]++;
        }

        /* distribui os vai-uns. */
        for (i = 0; i < r; i++)
        {
            if (num[i] == n)
            {
                num[i] = 0;
                num[i + 1]++;
            }
        }
    }
    PadronizaLista(*vetor);
    free(num);

    return 0;
}