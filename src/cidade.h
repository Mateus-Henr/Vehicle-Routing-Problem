#include <stdbool.h>

typedef struct Cidade
{
    unsigned int demanda;
    bool foiVisitada;
} Cidade;

bool foiVisitada(struct Cidade cidade);

// Getters e Setters

unsigned int getDemanda(struct Cidade cidade);

void setDemanda(struct Cidade cidade, unsigned int novaDemanda);

void setFoiVisitada(struct Cidade cidade, bool foiVisitada);
