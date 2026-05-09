#ifndef AGENCIA_H
#define AGENCIA_H

#include <string>
#include <vector>

using namespace std;

class Astronauta {
public:
    string cpf;
    string nome;
    int idade;
    bool vivo;
    bool disponivel;

    Astronauta(string c, string n, int i) {
        cpf = c;
        nome = n;
        idade = i;
        vivo = true;
        disponivel = true;
    }
};

class Voo {
public:
    int codigo;
    vector<string> cpfsPassageiros;
    string estado;

    Voo(int cod) {
        codigo = cod;
        estado = "Planejado";
    }
};

#endif