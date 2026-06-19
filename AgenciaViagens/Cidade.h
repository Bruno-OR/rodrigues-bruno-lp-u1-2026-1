#ifndef CIDADE_H
#define CIDADE_H

#include <string>

using namespace std;

// Guarda as informações básicas de uma cidade
class Cidade
{
private:
    string nome;
    int visitas;

public:
    // Construtor para criar a cidade com o nome
    Cidade(string nomeCidade)
    {
        nome = nomeCidade;
        visitas = 0;
    }

    string getNome()
    {
        return nome;
    }

    int getVisitas() { return visitas; }

    void registrarVisita() { visitas++; }
};

#endif