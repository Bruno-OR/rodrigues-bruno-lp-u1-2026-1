#ifndef VIAGEM_H
#define VIAGEM_H

#include <vector>
#include "Transporte.h"
#include "Passageiro.h"
#include "Cidade.h"

using namespace std;

// Classe que junta o transporte e a lista de passageiros em transito
class Viagem
{
private:
    Transporte *transporte;
    vector<Passageiro *> passageiros;
    Cidade *origem;
    Cidade *destino;
    Viagem *proxima; // Ponteiro para conexao de viagens
    int horasEmTransito;
    bool emAndamento;
    double kmPercorridos;

public:
    Viagem(Transporte *t, vector<Passageiro *> p, Cidade *o, Cidade *d)
    {
        transporte = t;
        passageiros = p;
        origem = o;
        destino = d;
        proxima = nullptr; // Comeca sem conexao definida
        horasEmTransito = 0;
        emAndamento = false;
        kmPercorridos = 0;

    }

    Transporte *getTransporte() { return transporte; }
    vector<Passageiro *> getPassageiros() { return passageiros; }
    Cidade *getOrigem() { return origem; }
    Cidade *getDestino() { return destino; }
    Viagem *getProxima() { return proxima; }
    int getHorasEmTransito() { return horasEmTransito; }
    bool isEmAndamento() { return emAndamento; }

    void setProxima(Viagem *prox) { proxima = prox; }
    void setEmAndamento(bool status) { emAndamento = status; }
    void adicionarHora() { horasEmTransito++; }
    void adicionarKm(double km) { kmPercorridos += km; }
    double getKmPercorridos() { return kmPercorridos; }
};
#endif