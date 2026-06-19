#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "agencia.h"

// Inclusão para detectar se a entrada vem do teclado ou de arquivo redirecionado
#ifdef _WIN32
#include <io.h>
#define IS_TERMINAL _isatty(_fileno(stdin))
#else
#include <unistd.h>
#define IS_TERMINAL isatty(fileno(stdin))
#endif

using namespace std;

void exibirMenu()
{
    cout << "\n=======================================================" << endl;
    cout << "           SISTEMA INTEGRADO DE TRÂNSITO          " << endl;
    cout << "=======================================================" << endl;
    cout << "  [1] Cadastrar Cidade" << endl;
    cout << "  [2] Cadastrar Trajeto" << endl;
    cout << "  [3] Cadastrar Transporte" << endl;
    cout << "  [4] Cadastrar Passageiro" << endl;
    cout << "  [5] Iniciar Viagem (Direta ou com Escalas)" << endl;
    cout << "  [6] Avançar Relógio (Simulação de Horas)" << endl;
    cout << "  [7] Relatar Estado Geral da Agência" << endl;
    cout << "  [8] Encerrar Programa (FIM)" << endl;
    cout << "-------------------------------------------------------" << endl;
    cout << " Selecione uma opção > ";
}

int main()
{
    controladorDeTransito controlador;
    string comando;

    // Carrega arquivo se existir
    ifstream arquivoSalvo("estado.txt");
    if (arquivoSalvo.is_open())
    {
        cout << "[Carregando] Estado anterior encontrado. Restaurando dados..." << endl;
        string cmdCarga;
        while (arquivoSalvo >> cmdCarga && cmdCarga != "FIM")
        {
            if (cmdCarga == "CADASTRAR_CIDADE")
            {
                string nomeCidade;
                getline(arquivoSalvo >> ws, nomeCidade);
                controlador.cadastrarCidade(nomeCidade);
            }
            else if (cmdCarga == "CADASTRAR_TRAJETO")
            {
                string origem, destino;
                char tipo;
                double distancia;
                getline(arquivoSalvo >> ws, origem);
                getline(arquivoSalvo >> ws, destino);
                arquivoSalvo >> tipo >> distancia;
                controlador.cadastrarTrajeto(origem, destino, tipo, distancia);
            }
            else if (cmdCarga == "CADASTRAR_TRANSPORTE")
            {
                string nomeTransp, nomeCidade;
                char tipo;
                int capacidade, velocidade, distDescanso, tempoDescanso;
                getline(arquivoSalvo >> ws, nomeTransp);
                arquivoSalvo >> tipo >> capacidade >> velocidade >> distDescanso >> tempoDescanso;
                getline(arquivoSalvo >> ws, nomeCidade);
                controlador.cadastrarTransporte(nomeTransp, tipo, capacidade, velocidade, distDescanso, tempoDescanso, nomeCidade);
            }
            else if (cmdCarga == "CADASTRAR_PASSAGEIRO")
            {
                string nomePassageiro, nomeCidade;
                getline(arquivoSalvo >> ws, nomePassageiro);
                getline(arquivoSalvo >> ws, nomeCidade);
                controlador.cadastrarPassageiro(nomePassageiro, nomeCidade);
            }
        }
        arquivoSalvo.close();
        cout << "[OK] Dados restaurados com sucesso!" << endl;
    }

    while (true)
    {
        if (IS_TERMINAL)
        {
            exibirMenu();
            string opcao;
            cin >> opcao;

            if (opcao == "1")
                comando = "CADASTRAR_CIDADE";
            else if (opcao == "2")
                comando = "CADASTRAR_TRAJETO";
            else if (opcao == "3")
                comando = "CADASTRAR_TRANSPORTE";
            else if (opcao == "4")
                comando = "CADASTRAR_PASSAGEIRO";
            else if (opcao == "5")
                comando = "CADASTRAR_VIAGEM";
            else if (opcao == "6")
                comando = "CADASTRAR_HORAS";
            else if (opcao == "7")
                comando = "RELATAR_ESTADO";
            else if (opcao == "8" || opcao == "FIM")
                comando = "FIM";
            else
            {
                cout << "\n Opção inválida! Escolha um número de 1 a 8." << endl;
                continue;
            }
        }
        else
        {
            // Se vier redirecionado de arquivo (< Agencia.txt), lê a string do comando diretamente
            if (!(cin >> comando))
                break;
        }
        if (comando == "FIM")
            break;

        if (comando == "CADASTRAR_CIDADE")
        {
            string nomeCidade;
            if (IS_TERMINAL)
                cout << "  -> Nome da Cidade: ";
            getline(cin >> ws, nomeCidade);
            controlador.cadastrarCidade(nomeCidade);
            if (IS_TERMINAL)
                cout << "  [OK] Cidade '" << nomeCidade << "' cadastrada com sucesso!" << endl;
        }

        else if (comando == "CADASTRAR_TRAJETO")
        {
            string origem, destino;
            char tipo;
            double distancia;

            if (IS_TERMINAL)
                cout << "  -> Cidade de Origem: ";
            getline(cin >> ws, origem);
            if (IS_TERMINAL)
                cout << "  -> Cidade de Destino: ";
            getline(cin >> ws, destino);
            if (IS_TERMINAL)
                cout << "  -> Tipo (T-Terrestre / A-Aquatico): ";
            cin >> tipo;
            if (IS_TERMINAL)
                cout << "  -> Distancia (km): ";
            cin >> distancia;

            if (controlador.cadastrarTrajeto(origem, destino, tipo, distancia))
                if (IS_TERMINAL)
                    cout << "  [OK] Trajeto cadastrado!" << endl;
        }

        else if (comando == "CADASTRAR_TRANSPORTE")
        {
            string nomeTransp, nomeCidadeInicial;
            char tipo;
            int capacidade, velocidade, distDescanso, tempoDescanso;

            if (IS_TERMINAL)
            {
                cout << "\n CADASTRO DE VEÍCULO" << endl;
                cout << " ---------------------------------------------------" << endl;
                cout << "  -> Nome do Transporte (ex: Busão 01): ";
                getline(cin >> ws, nomeTransp);

                cout << "  -> Tipo do Transporte [T - Terrestre / A - Aquático]: ";
                cin >> tipo;

                cout << "  -> Capacidade máxima de passageiros: ";
                cin >> capacidade;

                cout << "  -> Velocidade média operacional (km/h): ";
                cin >> velocidade;

                cout << "  -> Distância limite entre descansos (km): ";
                cin >> distDescanso;

                cout << "  -> Tempo de duração de cada descanso (horas): ";
                cin >> tempoDescanso;

                cin.ignore(1000, '\n');
                cout << "  -> Cidade onde o veículo iniciará estacionado: ";
                getline(cin >> ws, nomeCidadeInicial);
            }
            else
            {
                getline(cin >> ws, nomeTransp);
                cin >> tipo >> capacidade >> velocidade >> distDescanso >> tempoDescanso;
                cin >> ws;
                getline(cin >> ws, nomeCidadeInicial);
            }

            if (controlador.cadastrarTransporte(nomeTransp, tipo, capacidade, velocidade, distDescanso, tempoDescanso, nomeCidadeInicial))
                if (IS_TERMINAL)
                    cout << "\n [OK] Veículo '" << nomeTransp << "' integrado à frota com sucesso!" << endl;
        }

        else if (comando == "CADASTRAR_PASSAGEIRO")
        {
            string nomePassageiro, nomeCidadeInicial;
            if (IS_TERMINAL)
                cout << "  -> Nome do Passageiro: ";
            getline(cin >> ws, nomePassageiro);
            if (IS_TERMINAL)
                cout << "  -> Cidade Local Atual: ";
            getline(cin >> ws, nomeCidadeInicial);

            if (controlador.cadastrarPassageiro(nomePassageiro, nomeCidadeInicial))
                if (IS_TERMINAL)
                    cout << "  [OK] Passageiro registrado!" << endl;
        }

        else if (comando == "CADASTRAR_VIAGEM")
        {
            string nomeTransporte, origem, destino;
            int qtd;

            if (IS_TERMINAL)
                cout << "  -> Nome do Transporte: ";
            getline(cin >> ws, nomeTransporte);
            if (IS_TERMINAL)
                cout << "  -> Cidade de Origem: ";
            getline(cin >> ws, origem);
            if (IS_TERMINAL)
                cout << "  -> Cidade de Destino Final: ";
            getline(cin >> ws, destino);
            if (IS_TERMINAL)
                cout << "  -> Quantidade de Passageiros: ";
            cin >> qtd;

            vector<string> nomesPassageiros;
            for (int i = 0; i < qtd; i++)
            {
                string nome;
                if (IS_TERMINAL)
                    cout << "     - Nome do Passageiro " << i + 1 << ": ";
                getline(cin >> ws, nome);
                nomesPassageiros.push_back(nome);
            }
            controlador.iniciarViagem(nomeTransporte, nomesPassageiros, origem, destino);
        }

        else if (comando == "CADASTRAR_HORAS")
        {
            int horas;
            if (IS_TERMINAL)
                cout << "  -> Quantidade de horas a avancar: ";
            cin >> horas;

            controlador.avancarHoras(horas);
        }

        else if (comando == "RELATAR_ESTADO")
        {
            controlador.relatarEstado();
        }

        if (IS_TERMINAL)
            cout << "\nComando > ";
    }

    controlador.salvarEstado();
    if (IS_TERMINAL)
        cout << "\n[FIM] Programa encerrado. Memoria liberada!" << endl;
    controlador.limparMemoria();

    return 0;
}