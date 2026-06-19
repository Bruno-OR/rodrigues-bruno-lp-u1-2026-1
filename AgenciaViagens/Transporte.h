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
    int velocidade;
    int distancia_entre_descansos;
    int tempo_de_descanso_atual;     // Tempo total que deve descansar
    int horas_restantes_de_descanso; // Contador regressivo de horas parado
    int km_acumulados;               // Controla quantos km andou desde a ultima parada
    Cidade *localAtual;              // Aponta para onde o veículo está ou nullptr se estiver viajando

public:
    Transporte(string nomeTransp, char tipoTransp, int cap, int vel, int distDesc, int tempoDesc, Cidade *cidadeInicial)
    {
        nome = nomeTransp;
        tipo = tipoTransp;
        capacidade = cap;
        velocidade = vel;
        distancia_entre_descansos = distDesc;
        tempo_de_descanso_atual = tempoDesc;
        horas_restantes_de_descanso = 0; // Comeca zerado, pois não comeca cansado
        km_acumulados = 0;               // Comeca sem km rodados
        localAtual = cidadeInicial;
    }

    string getNome() { return nome; }
    char getTipo() { return tipo; } // Retorna 'T' ou 'A'
    int getCapacidade() { return capacidade; }
    int getVelocidade() { return velocidade; }
    int getDistanciaEntreDescansos() { return distancia_entre_descansos; }
    int getTempoDescansoAtual() { return tempo_de_descanso_atual; }
    Cidade *getLocalAtual() { return localAtual; }

    int getHorasRestantesDeDescanso() { return horas_restantes_de_descanso; }
    int getKmAcumulados() { return km_acumulados; }

    void setLocalAtual(Cidade *novaCidade) { localAtual = novaCidade; }

    // Força o motorista a entrar em modo de descanso
    void iniciarDescanso()
    {
        horas_restantes_de_descanso = tempo_de_descanso_atual;
        km_acumulados = 0; // Zera os km para continuar ate a proxima parada
    }

    // Reduz uma hora de descanso
    void reduzirHoraDescanso()
    {
        if (horas_restantes_de_descanso > 0)
        {
            horas_restantes_de_descanso--;
        }
    }

    // Acumula os km rodados na hora atual
    void adicionarKm(int km)
    {
        km_acumulados += km;
    }
};

#endif
