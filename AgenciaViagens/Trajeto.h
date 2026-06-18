#ifndef TRAJETO_H
#define TRAJETO_H

#include <iostream>
#include "Cidade.h"

using namespace std;

// Classe para ligar duas cidades e definir a distancia entre elas
class Trajeto
{
private:
    Cidade *origem;
    Cidade *destino;
    char tipo; // A - Aquatico, T - Terrestre
    double distancia;

public:
    // Construtor recebendo as cidades ja cadastradas por ponteiro
    Trajeto(Cidade *cidadeOrigem, Cidade *cidadeDestino, char tipoTrajeto, double distanciaKm)
    {
        origem = cidadeOrigem;
        destino = cidadeDestino;
        tipo = tipoTrajeto;
        distancia = distanciaKm;
    }

    Cidade *getOrigem() { return origem; }
    Cidade *getDestino() { return destino; }
    char getTipo() { return tipo; }
    double getDistancia() { return distancia; }
};

#endif