#include <stdbool.h>

#include "cidade.h"

void setID(struct Cidade cidade, unsigned int novoID)
{
    cidade.ID = novoID;
}

void setDemanda(struct Cidade cidade, unsigned int novaDemanda)
{
    cidade.demanda = novaDemanda;
}

void setFoiVisitada(struct Cidade cidade, bool foiVisitada)
{
    cidade.foiVisitada = foiVisitada;
}

unsigned int getID(struct Cidade cidade)
{
    return cidade.ID;
}

unsigned int getDemanda(struct Cidade cidade)
{
    return cidade.demanda;
}

bool foiVisitada(struct Cidade cidade)
{
    return cidade.foiVisitada;
}