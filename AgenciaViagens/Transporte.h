#ifndef TRANSPORTE_H
#define TRANSPORTE_H

#include <string>
#include "Cidade.h"

using namespace std;

// Guarda as regras e dados de cada veículo
class Transporte
{
private:
    string nome;
    char tipo; // 'A' para aquático ou 'T' para terrestre
    int capacidade;
    int velocidad;
    int distancia_entre_descansos;
    int tempo_de_descanso_atual;
    Cidade *localAtual; // Aponta para onde o veículo está ou nullptr se estiver viajando

public:
    Transporte(string nomeTransp, char tipoTransp, int cap, int vel, int distDesc, int tempoDesc, Cidade *cidadeInicial)
    {
        nome = nomeTransp;
        tipo = tipoTransp;
        capacidade = cap;
        velocidad = vel;
        distancia_entre_descansos = distDesc;
        tempo_de_descanso_atual = tempoDesc;
        localAtual = cidadeInicial;
    }

    string getNome() { return nome; }
    char getTipo() { return tipo; } // Retorna 'T' ou 'A'
    int getCapacidade() { return capacidade; }
    int getVelocidade() { return velocidad; }
    int getDistanciaEntreDescansos() { return distancia_entre_descansos; }
    int getTempoDescansoAtual() { return tempo_de_descanso_atual; }
    Cidade *getLocalAtual() { return localAtual; }

    void setLocalAtual(Cidade *novaCidade) { localAtual = novaCidade; }
};

#endif