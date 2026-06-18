#ifndef PASSAGEIRO_H
#define PASSAGEIRO_H

#include <string>
#include "Cidade.h"

using namespace std;

// Classe para guardar os dados de cada pessoa do sistema
class Passageiro
{
private:
    string nome;
    Cidade *localAtual; // Cidade onde a pessoa esta ou nullptr se estiver viajando

public:
    Passageiro(string nomePassageiro, Cidade *cidadeInicial)
    {
        nome = nomePassageiro;
        localAtual = cidadeInicial;
    }

    string getNome() { return nome; }
    Cidade *getLocalAtual() { return localAtual; }

    void setLocalAtual(Cidade *novaCidade)
    {
        localAtual = novaCidade;
    }
};

#endif