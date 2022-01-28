#include <stdio.h>
#include <stddef.h>
#include <time.h>
#include <stdbool.h>

#include "cidade.h"
#include "combinacao.h"

// Varia conforme o sistema operacional.
#if defined WIN32 || defined _WIN32 || defined __CYGWIN__
#define PATH_ARQUIVO "..\\arquivos\\text.txt"
#else
#define PATH_ARQUIVO "../arquivos/text.txt" // Edite caso você estiver em outro plataforma que não seja Windows.
#endif

#define ERRO_ABRIR_ARQUIVO "Erro ao tentar abrir o arquivo.\n"
#define ERRO (-1)
#define ZERO 0
#define UM 1

// Protótipos de funções.

double inicializaClock(void);

double calculaTempo(double tempoInicial);


/*
 * A função principal. Tem como função a leitura de informações de um arquivo e manipulação dos dados.
 *
 * @return          0 se executado com sucesso, -1 se ocorrer algum erro.
 */
int main(void)
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
    unsigned int somatorioDemandas = 0;

    // Lendo a quantidade de cidades (N).
    fscanf(pArquivo, "%d", &qtdCidades);

    // Lendo a capacidade do caminhão (Qv).
    fscanf(pArquivo, "%d", &cargaCaminhao);

    // Definindo as estruturas baseado na quantidade de cidades do arquivo.
    struct Cidade cidades[qtdCidades];

    int distanciaCidades[qtdCidades + 1][qtdCidades + 1];
    int locaisParaCombinar[qtdCidades];

    int totalCombinacoes = fatorial(qtdCidades) * qtdCidades;
    int combinacoes[totalCombinacoes];

    // Lendo as demandas de cada cidade.
    for (int i = ZERO; i < qtdCidades; i++)
    {
        struct Cidade cidade;
        fscanf(pArquivo, "%d ", &cidade.demanda);
        cidade.foiVisitada = false;

        cidades[i] = cidade;
        locaisParaCombinar[i] = (i + 1);
        somatorioDemandas += cidade.demanda;
    }

    unsigned int qtdCaminhoes = somatorioDemandas / cargaCaminhao;

    // Colocando valores em uma matriz simétrica (Ci para Cj).
    for (int i = ZERO; i < qtdCidades; i++)
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

    // Realiza todas as combinações possíveis.
    combinaPetalas(locaisParaCombinar);

    // Imprimindo permutações.
    for (int i = ZERO; i < totalCombinacoes; i++)
    {
        if ((i % qtdCidades) == ZERO && i != 0)
        {
            printf("\n");
        }

        printf("%d ", combinacoes[i]);
    }

    fclose(pArquivo); // Fechando o arquivo.
    pArquivo = NULL; // Setando ponteiro como nulo.


    return ZERO;
}


/*
 * Função usada para iniciar o clock.
 * Retorna valor de quando a função "clock()" é chamada.
 */
double inicializaClock(void)
{
    return (double) clock();
}


/*
 * Função usada para finalizar o clock e calcular o tempo total.
 *
 * @param    tempoInicial    valor da primeira vez que a função "clock()" foi chamada.
 * @return                   valor calculado referente ao tempo entre o tempo inicial e o tempo final.
 */
double calculaTempo(double tempoInicial)
{
    return (double) (clock() - tempoInicial) / CLOCKS_PER_SEC;
}

