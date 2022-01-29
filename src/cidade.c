#include "cidade.h"

bool foiVisitada(struct Cidade cidade)
{
    return cidade.foiVisitada;
}

unsigned int getDemanda(struct Cidade cidade)
{
    return cidade.demanda;
}

void setDemanda(struct Cidade cidade, unsigned int novaDemanda)
{
    cidade.demanda = novaDemanda;
}

void setFoiVisitada(struct Cidade cidade, bool foiVisitada)
{
    cidade.foiVisitada = foiVisitada;
}