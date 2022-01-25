#include <stdio.h>
#include <stddef.h>
#include <time.h>

#define PATH_ARQUIVO "..//arquivos//text.txt" // Varia conforme o sistema operacional.
#define ERRO_ABRIR_ARQUIVO "Erro ao tentar abrir o arquivo.\n"
#define ERRO (-1)
#define ZERO 0

// Protótipos de funções.

double inicializaClock(void);

double finalizaClock(double tempoInicial);


int main()
{
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

    // Lendo a quantidade de cidades (N).
    fscanf(pArquivo, "%d", &qtdCidades);

    // Lendo a capacidade do caminhão (Qv).
    fscanf(pArquivo, "%d", &cargaCaminhao);

    // Definindo as estruturas baseado na quantidade de cidades do arquivo.
    int demandaCidades[qtdCidades];
    int distanciaCidades[qtdCidades][qtdCidades];

    // Lendo as demandas de cada cidade.
    for (int i = ZERO; i < qtdCidades; i++)
    {
        fscanf(pArquivo, "%d ", &demandaCidades[i]);
    }

    // Colocando valores em uma matriz simétrica (Ci para Cj).
    for (int i = ZERO, k = ZERO; i < qtdCidades; i++)
    {
        for (int j = ZERO; j < qtdCidades; j++)
        {
            if (i == j)
            {
                distanciaCidades[i][j] = ZERO;
            }
            else if (i < j)
            {
                fscanf(pArquivo, "%d", &distanciaCidades[i][j]);
                distanciaCidades[j][i] = distanciaCidades[i][j];
            }
        }
    }

    fclose(pArquivo); // Fechando o arquivo.
    pArquivo = NULL; // Setando ponteiro como nulo.

    return ZERO;
}


/*
 * Função usada para iniciar o clock.
 */
double inicializaClock(void)
{
    return (double) clock();
}


/*
 * Função usada para finalizar o clock e calcular o tempo total.
 */
double finalizaClock(double tempoInicial)
{
    return (double) (clock() - tempoInicial) / CLOCKS_PER_SEC;
}

