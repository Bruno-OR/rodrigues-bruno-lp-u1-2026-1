#ifndef CIDADE_H
#define CIDADE_H

#include <string>

using namespace std;

// Guarda as informações básicas de uma cidade
class Cidade
{
private:
    string nome;

public:
    // Construtor para criar a cidade com o nome
    Cidade(string nomeCidade)
    {
        nome = nomeCidade;
    }

    string getNome()
    {
        return nome;
    }
};

#endif