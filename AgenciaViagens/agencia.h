#ifndef AGENCIA_H
#define AGENCIA_H
#include <iostream>
#include <string>
#include <vector>
#include "Cidade.h"
#include "Trajeto.h"
#include "Transporte.h"
#include "Passageiro.h"
#include "Viagem.h"

using namespace std;

class controladorDeTransito
{
private:
    vector<Cidade *> cidades;
    vector<Trajeto *> trajetos;
    vector<Transporte *> transportes;
    vector<Passageiro *> passageiros;
    vector<Viagem *> viagens;

public:
    controladorDeTransito() {}

    // --- FUNÇÕES DE CADASTRO ---

    void cadastrarCidade(string nome)
    {
        // Criar uma nova cidade
        Cidade *novaCidade = new Cidade(nome);
        cidades.push_back(novaCidade);
    };

    void cadastrarTrajeto(string nomeOrigem, string nomeDestino, char tipo, double distancia)
    {

        Cidade *cidadeOrigem = nullptr;
        Cidade *cidadeDestino = nullptr;

        for (int i = 0; i < cidades.size(); i++)
        {
            if (cidades[i]->getNome() == nomeOrigem)
            {
                cidadeOrigem = cidades[i];
            }
            if (cidades[i]->getNome() == nomeDestino)
            {
                cidadeDestino = cidades[i];
            }
        }

        if (cidadeOrigem != nullptr && cidadeDestino != nullptr)
        {
            Trajeto *novoTrajeto = new Trajeto(cidadeOrigem, cidadeDestino, tipo, distancia);
            trajetos.push_back(novoTrajeto);
        }
        else
        {
            cout << "Erro: Uma das cidades não foi encontrada para criar o trajeto" << endl;
        }
    };

    void cadastrarTransporte(string nome, char tipo, int capacidade, int velocidade, int distancia_entre_descansos, int tempo_de_descanso, string localAtual)
    {

        Cidade *cidadeInicial = nullptr;

        for (int i = 0; i < cidades.size(); i++)
        {
            if (cidades[i]->getNome() == localAtual)
            {
                cidadeInicial = cidades[i];
                break;
            }
        }

        if (cidadeInicial != nullptr)
        {

            Transporte *novoTransporte = new Transporte(nome, tipo, capacidade, velocidade, distancia_entre_descansos, tempo_de_descanso, cidadeInicial);
            transportes.push_back(novoTransporte);
        }
        else
        {
            cout << "Erro: A cidade inicial '" << localAtual << "' não foi encontrada para cadastrar o transporte!" << endl;
        }
    };

    void cadastrarPassageiro(string nome, string localAtual)
    {

        Cidade *cidadeInicial = nullptr;

        for (int i = 0; i < cidades.size(); i++)
        {
            if (cidades[i]->getNome() == localAtual)
            {
                cidadeInicial = cidades[i];
                break;
            }
        }

        if (cidadeInicial != nullptr)
        {
            Passageiro *novoPassageiro = new Passageiro(nome, cidadeInicial);
            passageiros.push_back(novoPassageiro);
        }
        else
        {
            cout << "Erro: A cidade inicial '" << localAtual << "' não foi encontrada para cadastrar o passageiro!" << endl;
        }
    };

    // --- FUNÇÕES DE SIMULAÇÃO ---

    void iniciarViagem(string nomeTransporte, vector<string> nomesPassageiros, string nomeOrigem, string nomeDestino)
    {
        // Encontrar o ponteiro do Transporte
        Transporte *transpEscolhido = nullptr;
        for (int i = 0; i < transportes.size(); i++)
        {
            if (transportes[i]->getNome() == nomeTransporte)
            {
                transpEscolhido = transportes[i];
                break;
            }
        }
        // Encontrar os ponteiros das Cidades de Origem e Destino
        Cidade *cidOrigem = nullptr;
        Cidade *cidDestino = nullptr;
        for (int i = 0; i < cidades.size(); i++)
        {
            if (cidades[i]->getNome() == nomeOrigem)
            {
                cidOrigem = cidades[i];
            }
            if (cidades[i]->getNome() == nomeDestino)
            {
                cidDestino = cidades[i];
            }
        }
        // Encontrar os ponteiros de cada Passageiro da lista
        vector<Passageiro *> passageirosEncontrados;
        for (int i = 0; i < nomesPassageiros.size(); i++)
        {
            for (int j = 0; j < passageiros.size(); j++)
            {
                if (passageiros[j]->getNome() == nomesPassageiros[i])
                {
                    passageirosEncontrados.push_back(passageiros[j]);
                    break;
                }
            };
        };

        // Validação para garantir que o transporte ou cidade existem
        if (transpEscolhido == nullptr || cidOrigem == nullptr || cidDestino == nullptr)
        {
            cout << "Erro: Transporte, Origem ou Destino não encontrados no sistema!" << endl;
            return;
        }

        // Validação para verificar se o transporte comporta o numero de passageiros
        if (passageirosEncontrados.size() > transpEscolhido->getCapacidade())
        {
            cout << "Erro: O transporte '" << transpEscolhido->getNome() << "' não tem capacidade para tantos passageiros!" << endl;
            return;
        }

        // Verificaçao para saber se o veiculo está na cidade de origem
        if (transpEscolhido->getLocalAtual() != cidOrigem)
        {
            cout << "Erro: O transporte '" << transpEscolhido->getNome() << "' não esta na cidade de origem (" << cidOrigem->getNome() << ")!" << endl;
            return;
        }

        // Verificação para saber se todos os passageiros estão na cidade de origem
        for (int i = 0; i < passageirosEncontrados.size(); i++)
        {
            if (passageirosEncontrados[i]->getLocalAtual() != cidOrigem)
            {
                cout << "Erro: O passageiro '" << passageirosEncontrados[i]->getNome() << "' não esta na cidade de origem para embarcar!" << endl;
                return;
            }
        };

        Trajeto *trajetoDireto = nullptr;
        // procura o trajeto direto
        for (int i = 0; i < trajetos.size(); i++)
        {
            if (trajetos[i]->getOrigem() == cidOrigem && trajetos[i]->getDestino() == cidDestino)
            {
                trajetoDireto = trajetos[i];
                break;
            }
        }

        // Tentar iniciar a viagem
        if (trajetoDireto != nullptr)
        {
            // Verifica se o tipo do transporte bate com o tipo do trajeto
            if (transpEscolhido->getTipo() != trajetoDireto->getTipo())
            {
                cout << "Erro: O transporte '" << transpEscolhido->getNome() << "' não é compativel com o tipo de trajeto!" << endl;
                return;
            }

            Viagem *novaViagem = new Viagem(transpEscolhido, passageirosEncontrados, cidOrigem, cidDestino);
            novaViagem->setEmAndamento(true);
            viagens.push_back(novaViagem);

            // Transporte em transito
            transpEscolhido->setLocalAtual(nullptr);
            // Passageiros em transito
            for (int i = 0; i < passageirosEncontrados.size(); i++)
            {
                passageirosEncontrados[i]->setLocalAtual(nullptr);
            }

            cout << "Viagem direta iniciada com sucesso!" << endl;
        }
        else
        {
            // --- ESCALAS ---
            Cidade *cidConexao = nullptr;

            // Busca uma cidade intermediária varrendo os trajetos existentes
            for (int i = 0; i < trajetos.size(); i++)
            {
                if (trajetos[i]->getOrigem() == cidOrigem && trajetos[i]->getTipo() == transpEscolhido->getTipo())
                {
                    Cidade *possivelConexao = trajetos[i]->getDestino();

                    // Verifica se essa cidade conecta com o destino final
                    for (int j = 0; j < trajetos.size(); j++)
                    {
                        if (trajetos[j]->getOrigem() == possivelConexao && trajetos[j]->getDestino() == cidDestino && trajetos[j]->getTipo() == transpEscolhido->getTipo())
                        {
                            cidConexao = possivelConexao;
                            break;
                        }
                    }
                    if (cidConexao != nullptr)
                        break;
                }
            }

            if (cidConexao == nullptr)
            {
                cout << "Alerta: Não foi possível encontrar rotas diretas ou conexões válidas com esse tipo de transporte." << endl;
                return;
            }

            // Cria o trecho 2 (Da Conexão até o Destino Final) - Começa pausado (false)
            Viagem *viagemTrecho2 = new Viagem(transpEscolhido, passageirosEncontrados, cidConexao, cidDestino);
            viagemTrecho2->setEmAndamento(false);

            // Cria o trecho 1 (Da Origem até a Conexão) - Começa em andamento (true)
            Viagem *viagemTrecho1 = new Viagem(transpEscolhido, passageirosEncontrados, cidOrigem, cidConexao);
            viagemTrecho1->setEmAndamento(true);

            // Encadeia as duas
            viagemTrecho1->setProxima(viagemTrecho2);

            // Cadastra ambas no vetor de viagens
            viagens.push_back(viagemTrecho1);
            viagens.push_back(viagemTrecho2);

            // Define transporte e passageiros em trânsito
            transpEscolhido->setLocalAtual(nullptr);
            for (int i = 0; i < passageirosEncontrados.size(); i++)
            {
                passageirosEncontrados[i]->setLocalAtual(nullptr);
            }

            cout << "Viagem com conexao via " << cidConexao->getNome() << " iniciada com sucesso!" << endl;
        }
    };

    void avancarHoras(int horas)
    {
        for (int h = 0; h < horas; h++)
        {
            for (int i = 0; i < viagens.size(); i++)
            {
                Viagem *v = viagens[i];

                if (v->isEmAndamento())
                {
                    Transporte *t = v->getTransporte();
                    Cidade *dest = v->getDestino();

                    // Verificação de descanso
                    if (t->getHorasRestantesDeDescanso() > 0)
                    {
                        t->reduzirHoraDescanso();
                        continue; // Se o motorista está descansando, pula essa hora
                    }

                    v->adicionarHora();

                    // Busca do trajeto para saber a distancia total do trecho atual
                    double distanciaTotal = 0;
                    for (int j = 0; j < trajetos.size(); j++)
                    {
                        if (trajetos[j]->getOrigem() == v->getOrigem() && trajetos[j]->getDestino() == dest)
                        {
                            distanciaTotal = trajetos[j]->getDistancia();
                            break;
                        }
                    }

                    // Cálculo da distância percorrida e acumulação de descanso
                    double distanciaPercorrida = t->getVelocidade() * v->getHorasEmTransito();
                    t->adicionarKm(t->getVelocidade());

                    // Verificação de fadiga
                    if (t->getKmAcumulados() >= t->getDistanciaEntreDescansos())
                    {
                        t->iniciarDescanso();
                        cout << "[Descanso] O transporte '" << t->getNome() << "' atingiu o limite de conducao e parou para descansar por " << t->getTempoDescansoAtual() << " horas." << endl;
                    }

                    // Verificação de chegada no destino do trecho
                    if (distanciaPercorrida >= distanciaTotal)
                    {
                        v->setEmAndamento(false);

                        // Se houver uma viagem de conexão na sequência
                        if (v->getProxima() != nullptr)
                        {
                            cout << "O transporte '" << t->getNome() << "' chegou a cidade de conexao: " << dest->getNome() << ". Iniciando proximo trecho da viagem..." << endl;

                            // Ativa a próxima viagem para começar a rodar na próxima hora
                            v->getProxima()->setEmAndamento(true);
                        }
                        else
                        {
                            // Se não houver conexão, então é o destino final
                            t->setLocalAtual(dest);

                            vector<Passageiro *> passageirosABordo = v->getPassageiros();
                            for (int p = 0; p < passageirosABordo.size(); p++)
                            {
                                passageirosABordo[p]->setLocalAtual(dest);
                            }

                            // Reseta o descanso ao finalizar a viagem
                            t->iniciarDescanso();
                            t->reduzirHoraDescanso();

                            cout << "A viagem chegou ao destino final! O transporte '" << t->getNome() << "' e seus passageiros desembarcaram em " << dest->getNome() << "." << endl;
                        }
                    }
                }
            }
        }
    };

    void relatarEstado()
    {

        cout << "\n==============================================" << endl;
        cout << "         RELATÓRIO DE ESTADO DA AGÊNCIA       " << endl;
        cout << "==============================================" << endl;

        // Relatório de cidades
        cout << "\n--- CIDADES CADASTRADAS ---" << endl;
        if (cidades.empty())
        {
            cout << "Nenhuma cidade cadastrada." << endl;
        }
        else
        {
            for (int i = 0; i < cidades.size(); i++)
            {
                cout << "- " << cidades[i]->getNome() << endl;
            }
        }

        // Relatorio de transportes
        cout << "\n--- STATUS DOS TRANSPORTES ---" << endl;
        if (transportes.empty())
        {
            cout << "Nenhum transporte cadastrado." << endl;
        }
        else
        {
            for (int i = 0; i < transportes.size(); i++)
            {
                Transporte *t = transportes[i];
                cout << "- " << t->getNome() << " [Tipo: " << t->getTipo() << "] -> ";

                // Se o local atual for diferente de nullptr, ele está estacionado na cidade
                if (t->getLocalAtual() != nullptr)
                {
                    cout << "Estacionado em: " << t->getLocalAtual()->getNome() << endl;
                }
                else
                {
                    // Se for nullptr, ele está na estrada. Verifica se está andando ou dormindo:
                    if (t->getHorasRestantesDeDescanso() > 0)
                    {
                        cout << "Em trânsito (PARADO PARA DESCANSO - Faltam "
                             << t->getHorasRestantesDeDescanso() << "h)" << endl;
                    }
                    else
                    {
                        cout << "Em trânsito (viajando)..." << endl;
                    }
                }
            }
        }
        // Relatorio de passageiros
        cout << "\n--- LOCALIZAÇÃO DOS PASSAGEIROS ---" << endl;
        if (passageiros.empty())
        {
            cout << "Nenhum passageiro cadastrado." << endl;
        }
        else
        {
            for (int i = 0; i < passageiros.size(); i++)
            {
                Passageiro *p = passageiros[i];
                cout << "- " << p->getNome() << " -> ";

                if (p->getLocalAtual() != nullptr)
                {
                    cout << "Na cidade de: " << p->getLocalAtual()->getNome() << endl;
                }
                else
                {
                    cout << "Em viagem)..." << endl;
                }
            }
        }
        cout << "==============================================\n"
             << endl;
    };

    void limparMemoria()
    {
        for (int i = 0; i < cidades.size(); i++)
            delete cidades[i];
        for (int i = 0; i < trajetos.size(); i++)
            delete trajetos[i];
        for (int i = 0; i < transportes.size(); i++)
            delete transportes[i];
        for (int i = 0; i < passageiros.size(); i++)
            delete passageiros[i];
        for (int i = 0; i < viagens.size(); i++)
            delete viagens[i];
    }
};

#endif