#include <iostream>
#include <string>
#include <vector>
#include "agencia.h"

using namespace std;

int main()
{

    controladorDeTransito controlador;

    string comando;
    while (cin >> comando && comando != "FIM")
    {
        if (comando == "CADASTRAR_CIDADE") // CADASTRAR NOME DA CIDADE
        {
            string nomeCidade;
            getline(cin >> ws, nomeCidade);
            controlador.cadastrarCidade(nomeCidade);
        }

        else if (comando == "CADASTRAR_TRAJETO") // DADOS DO TRAJETO
        {
            string origem, destino;
            char tipo;
            double distancia;

            getline(cin >> ws, origem);
            getline(cin >> ws, destino);

            cin >> tipo >> distancia;

            controlador.cadastrarTrajeto(origem, destino, tipo, distancia);
        }

        else if (comando == "CADASTRAR_TRANSPORTE") // DADOS DO TRANSPORTE
        {
            string nomeTransp, nomeCidadeInicial;
            char tipo;
            int capacidade, velocidade, distDescanso, tempoDescanso;

            getline(cin >> ws, nomeTransp);

            cin >> tipo >> capacidade >> velocidade >> distDescanso >> tempoDescanso;
            cin >> ws;

            getline(cin >> ws, nomeCidadeInicial);

            controlador.cadastrarTransporte(nomeTransp, tipo, capacidade, velocidade, distDescanso, tempoDescanso, nomeCidadeInicial);
        }

        else if (comando == "CADASTRAR_PASSAGEIRO") // DADOS DO PASSAGEIRO
        {
            string nomePassageiro, nomeCidadeInicial;

            getline(cin >> ws, nomePassageiro);

            getline(cin >> ws, nomeCidadeInicial);

            controlador.cadastrarPassageiro(nomePassageiro, nomeCidadeInicial);
        }

        else if (comando == "CADASTRAR_VIAGEM") // DADOS DA VIAGEM
        {
            string nomeTransporte, origem, destino;
            int qtd;

            getline(cin >> ws, nomeTransporte);
            getline(cin >> ws, origem);
            getline(cin >> ws, destino);
            cin >> qtd;

            vector<string> nomesPassageiros;
            for (int i = 0; i < qtd; i++)
            {
                string nome;
                getline(cin >> ws, nome);
                nomesPassageiros.push_back(nome);
            }
            controlador.iniciarViagem(nomeTransporte, nomesPassageiros, origem, destino);
        }

        else if (comando == "CADASTRAR_HORAS") // QTDE HORAS
        {
            int horas;

            cin >> horas;

            controlador.avancarHoras(horas);
        }

        else if (comando == "RELATAR_ESTADO") // RELATORIO
        {
            controlador.relatarEstado();
        }
    }

    return 0;
}