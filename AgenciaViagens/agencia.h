#ifndef AGENCIA_H
#define AGENCIA_H
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
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
        // Verifica se a cidade já existe
        for (int i = 0; i < cidades.size(); i++)
        {
            if (cidades[i]->getNome() == nome)
            {
                cout << "Erro: A cidade '" << nome << "' já está cadastrada no sistema!" << endl;
                return;
            }
        }
        // Criar uma nova cidade
        Cidade *novaCidade = new Cidade(nome);
        cidades.push_back(novaCidade);
    };

    bool cadastrarTrajeto(string nomeOrigem, string nomeDestino, char tipo, double distancia)
    {
        if (tipo != 'T' && tipo != 'A')
        {
            cout << "Erro: Tipo de trajeto inválido! Use 'T' para Terrestre ou 'A' para Aquático." << endl;
            return false;
        }
        if (distancia <= 0)
        {
            cout << "Erro: A distância do trajeto deve ser maior que zero!" << endl;
            return false;
        }

        Cidade *cidadeOrigem = nullptr;
        Cidade *cidadeDestino = nullptr;

        for (int i = 0; i < cidades.size(); i++)
        {
            if (cidades[i]->getNome() == nomeOrigem)
                cidadeOrigem = cidades[i];
            if (cidades[i]->getNome() == nomeDestino)
                cidadeDestino = cidades[i];
        }

        if (cidadeOrigem != nullptr && cidadeDestino != nullptr)
        {
            Trajeto *novoTrajeto = new Trajeto(cidadeOrigem, cidadeDestino, tipo, distancia);
            trajetos.push_back(novoTrajeto);
            return true;
        }
        else
        {
            cout << "Erro: Uma das cidades não foi encontrada para criar o trajeto" << endl;
            return false;
        }
    };

    bool cadastrarTransporte(string nome, char tipo, int capacidade, int velocidade, int distancia_entre_descansos, int tempo_de_descanso, string localAtual)
    {
        if (tipo != 'T' && tipo != 'A')
        {
            cout << "Erro: Tipo de transporte inválido! Use 'T' para Terrestre ou 'A' para Aquático." << endl;
            return false;
        }

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
            return true;
        }
        else
        {
            cout << "Erro: A cidade inicial '" << localAtual << "' não foi encontrada para cadastrar o transporte!" << endl;
            return false;
        }
    };

    bool cadastrarPassageiro(string nome, string localAtual)
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
            return true;
        }
        else
        {
            cout << "Erro: A cidade inicial '" << localAtual << "' não foi encontrada para cadastrar o passageiro!" << endl;
            return false;
        }
    };

    // --- FUNÇÕES DE SIMULAÇÃO ---

    // Busca o caminho entre duas cidades
    // Retorna a sequência de cidades do caminho ou vetor vazio se não encontrar
    vector<Cidade *> buscarCaminho(Cidade *origem, Cidade *destino, char tipo)
    {
        vector<vector<Cidade *>> fila;
        vector<Cidade *> caminhoInicial;
        caminhoInicial.push_back(origem);
        fila.push_back(caminhoInicial);

        // Guarda as cidades já visitadas
        vector<Cidade *> visitados;
        visitados.push_back(origem);

        while (!fila.empty())
        {
            // Pega o primeiro caminho da fila
            vector<Cidade *> caminhoAtual = fila[0];
            fila.erase(fila.begin());

            // Última cidade do caminho atual
            Cidade *ultimaCidade = caminhoAtual[caminhoAtual.size() - 1];

            // Se chegou no destino, retorna o caminho
            if (ultimaCidade == destino)
                return caminhoAtual;

            // Procura trajetos que saem da última cidade
            for (int i = 0; i < trajetos.size(); i++)
            {
                if (trajetos[i]->getOrigem() == ultimaCidade && trajetos[i]->getTipo() == tipo)
                {
                    Cidade *proxima = trajetos[i]->getDestino();

                    // Verifica se essa cidade já foi visitada
                    bool jaVisitado = false;
                    for (int j = 0; j < visitados.size(); j++)
                    {
                        if (visitados[j] == proxima)
                        {
                            jaVisitado = true;
                            break;
                        }
                    }

                    if (!jaVisitado)
                    {
                        visitados.push_back(proxima);
                        vector<Cidade *> novoCaminho = caminhoAtual;
                        novoCaminho.push_back(proxima);
                        fila.push_back(novoCaminho);
                    }
                }
            }
        }

        // Se saiu do loop sem encontrar, retorna vazio
        vector<Cidade *> vazio;
        return vazio;
    }

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
            bool encontrado = false;
            for (int j = 0; j < passageiros.size(); j++)
            {
                if (passageiros[j]->getNome() == nomesPassageiros[i])
                {
                    passageirosEncontrados.push_back(passageiros[j]);
                    encontrado = true;
                    break;
                }
            }
            if (!encontrado)
            {
                cout << "Aviso: Passageiro '" << nomesPassageiros[i] << "' não encontrado no sistema e será ignorado." << endl;
            }
        }

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
            vector<Cidade *> caminho = buscarCaminho(cidOrigem, cidDestino, transpEscolhido->getTipo());

            if (caminho.empty() || caminho.size() < 2)
            {
                cout << "Alerta: Não foi possível encontrar rotas diretas ou conexões válidas com esse tipo de transporte." << endl;
                return;
            }

            // Cria os trechos de tras pra frente: [A, X, Y, B] → trecho3(Y->B), trecho2(X->Y), trecho1(A->X)
            Viagem *proximoTrecho = nullptr;
            for (int i = caminho.size() - 1; i > 0; i--)
            {
                Viagem *trecho = new Viagem(transpEscolhido, passageirosEncontrados, caminho[i - 1], caminho[i]);
                trecho->setEmAndamento(false);
                trecho->setProxima(proximoTrecho);
                proximoTrecho = trecho;
                viagens.push_back(trecho);
            }

            // Ativa só o primeiro trecho
            proximoTrecho->setEmAndamento(true);

            // Define transporte e passageiros em trânsito
            transpEscolhido->setLocalAtual(nullptr);
            for (int i = 0; i < passageirosEncontrados.size(); i++)
            {
                passageirosEncontrados[i]->setLocalAtual(nullptr);
            }

            string conexoes = "";
            for (int i = 1; i < (int)caminho.size() - 1; i++)
            {
                conexoes += caminho[i]->getNome();
                if (i < (int)caminho.size() - 2)
                    conexoes += ", ";
            }
            cout << "Viagem com conexao via " << conexoes << " iniciada com sucesso!" << endl;
        }
    };

    void avancarHoras(int horas)
    {
        if (horas <= 0)
        {
            cout << "Erro: A quantidade de horas deve ser maior que zero!" << endl;
            return;
        }
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
                    v->adicionarHora();
                    v->adicionarKm(t->getVelocidade());

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
                        cout << "[Descanso] O transporte '" << t->getNome() << "' atingiu o limite de condução e parou para descansar por " << t->getTempoDescansoAtual() << (t->getTempoDescansoAtual() == 1 ? " hora." : " horas.") << endl;
                    }
                    double distanciaPercorrida = (double)v->getHorasEmTransito() * t->getVelocidade();

                    // Verificação de chegada no destino do trecho
                    if (v->getKmPercorridos() >= distanciaTotal)
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
                            dest->registrarVisita();
                            vector<Passageiro *> passageirosABordo = v->getPassageiros();
                            for (int p = 0; p < passageirosABordo.size(); p++)
                            {
                                passageirosABordo[p]->setLocalAtual(dest);
                            }

                            // Reseta o descanso ao finalizar a viagem
                            t->resetarKm();

                            cout << "A viagem chegou ao destino final! O transporte '" << t->getNome() << "' e seus passageiros desembarcaram em " << dest->getNome() << "." << endl;
                        }
                    }
                }
            }
        }
    };

    void relatarEstado()
    {

        cout << "\n=======================================================" << endl;
        cout << "           RELATÓRIO DE ESTADO DA AGÊNCIA              " << endl;
        cout << "=======================================================" << endl;

        // Relatório de cidades
        cout << "\n CIDADES CADASTRADAS" << endl;
        cout << " ---------------------------------------------------" << endl;
        if (cidades.empty())
        {
            cout << "   (Nenhuma cidade cadastrada no sistema)" << endl;
        }
        else
        {
            for (size_t i = 0; i < cidades.size(); i++)
            {
                cout << "   • " << cidades[i]->getNome() << endl;
            }
        }

        // Relatorio de transportes
        cout << "\n STATUS DA FROTA (TRANSPORTES)" << endl;
        cout << " ---------------------------------------------------" << endl;
        if (transportes.empty())
        {
            cout << "   (Nenhum veiculo cadastrado no sistema)" << endl;
        }
        else
        {
            for (int i = 0; i < transportes.size(); i++)
            {
                Transporte *t = transportes[i];
                cout << "   • [" << t->getTipo() << "] " << t->getNome() << "\n     └─ Status: ";

                // Se o local atual for diferente de nullptr, ele está estacionado na cidade
                if (t->getLocalAtual() != nullptr)
                {
                    cout << "Estacionado em " << t->getLocalAtual()->getNome() << endl;
                }
                else
                {
                    // Se for nullptr, ele está na estrada. Verifica se está andando ou dormindo:
                    if (t->getHorasRestantesDeDescanso() > 0)
                    {
                        cout << " PARADO PARA DESCANSO (Faltam " << t->getHorasRestantesDeDescanso() << "h)" << endl;
                    }
                    else
                    {
                        cout << " Em transito (Viajando...)" << endl;
                    }
                }
            }
        }
        // Relatorio de passageiros
        cout << "\n LOCALIZAÇÃO DOS PASSAGEIROS" << endl;
        if (passageiros.empty())
        {
            cout << "   (Nenhum passageiro cadastrado no sistema)" << endl;
        }
        else
        {
            for (int i = 0; i < passageiros.size(); i++)
            {
                Passageiro *p = passageiros[i];
                cout << "   • " << p->getNome() << " \n     └─ Local: ";

                if (p->getLocalAtual() != nullptr)
                {
                    cout << "Na cidade de " << p->getLocalAtual()->getNome() << endl;
                }
                else
                {
                    // Busca a viagem em andamento que contém esse passageiro
                    bool viagemEncontrada = false;
                    for (int j = 0; j < viagens.size(); j++)
                    {
                        if (!viagens[j]->isEmAndamento())
                            continue;

                        vector<Passageiro *> abordo = viagens[j]->getPassageiros();
                        for (int k = 0; k < abordo.size(); k++)
                        {
                            if (abordo[k] == p)
                            {
                                cout << "Em viagem: " << viagens[j]->getOrigem()->getNome()
                                     << " -> " << viagens[j]->getDestino()->getNome()
                                     << " | Transporte: " << viagens[j]->getTransporte()->getNome() << endl;
                                viagemEncontrada = true;
                                break;
                            }
                        }
                        if (viagemEncontrada)
                            break;
                    }
                    if (!viagemEncontrada)
                        cout << "Em viagem..." << endl;
                }
            }
        }

        cout << "\n CIDADES MAIS VISITADAS" << endl;
        cout << " ---------------------------------------------------" << endl;
        if (cidades.empty())
        {
            cout << "   (Nenhuma cidade cadastrada no sistema)" << endl;
        }
        else
        {
            // Ordena uma cópia do vetor por visitas (mais visitada primeiro)
            vector<Cidade *> cidadesOrdenadas = cidades;
            for (int i = 0; i < cidadesOrdenadas.size(); i++)
            {
                for (int j = i + 1; j < cidadesOrdenadas.size(); j++)
                {
                    if (cidadesOrdenadas[j]->getVisitas() > cidadesOrdenadas[i]->getVisitas())
                    {
                        Cidade *temp = cidadesOrdenadas[i];
                        cidadesOrdenadas[i] = cidadesOrdenadas[j];
                        cidadesOrdenadas[j] = temp;
                    }
                }
            }
            for (int i = 0; i < cidadesOrdenadas.size(); i++)
            {
                cout << "   • " << cidadesOrdenadas[i]->getNome()
                     << " — " << cidadesOrdenadas[i]->getVisitas() << " visita(s)" << endl;
            }
        }

        cout << "\n VIAGENS EM ANDAMENTO" << endl;
        cout << " ---------------------------------------------------" << endl;

        bool temViagem = false;
        for (int i = 0; i < viagens.size(); i++)
        {
            if (viagens[i]->isEmAndamento())
            {
                Viagem *v = viagens[i];
                cout << "   • " << v->getTransporte()->getNome()
                     << ": " << v->getOrigem()->getNome()
                     << " -> " << v->getDestino()->getNome()
                     << " | " << v->getHorasEmTransito() << "h em trânsito" << endl;
                temViagem = true;
            }
        }
        if (!temViagem)
        {
            cout << "   (Nenhuma viagem em andamento no momento)" << endl;
        }
        cout << "=======================================================\n"
             << endl;
    };

    void salvarEstado()
    {
        ofstream arquivo("estado.txt");
        if (!arquivo.is_open())
        {
            cout << "Erro: Não foi possível salvar o estado do sistema!" << endl;
            return;
        }

        // Para salvar as cidades
        for (int i = 0; i < cidades.size(); i++)
        {
            arquivo << "CADASTRAR_CIDADE\n";
            arquivo << cidades[i]->getNome() << "\n";
        }

        // Para salvar os trajetos
        for (int i = 0; i < trajetos.size(); i++)
        {
            arquivo << "CADASTRAR_TRAJETO\n";
            arquivo << trajetos[i]->getOrigem()->getNome() << "\n";
            arquivo << trajetos[i]->getDestino()->getNome() << "\n";
            arquivo << trajetos[i]->getTipo() << "\n";
            arquivo << trajetos[i]->getDistancia() << "\n";
        }

        // Para salvar os transportes que não estão em trânsito
        for (int i = 0; i < transportes.size(); i++)
        {
            if (transportes[i]->getLocalAtual() != nullptr)
            {
                arquivo << "CADASTRAR_TRANSPORTE\n";
                arquivo << transportes[i]->getNome() << "\n";
                arquivo << transportes[i]->getTipo() << "\n";
                arquivo << transportes[i]->getCapacidade() << "\n";
                arquivo << transportes[i]->getVelocidade() << "\n";
                arquivo << transportes[i]->getDistanciaEntreDescansos() << "\n";
                arquivo << transportes[i]->getTempoDescansoAtual() << "\n";
                arquivo << transportes[i]->getLocalAtual()->getNome() << "\n";
            }
        }

        // Para salvar os passageiros que não estão em trânsito
        for (int i = 0; i < passageiros.size(); i++)
        {
            if (passageiros[i]->getLocalAtual() != nullptr)
            {
                arquivo << "CADASTRAR_PASSAGEIRO\n";
                arquivo << passageiros[i]->getNome() << "\n";
                arquivo << passageiros[i]->getLocalAtual()->getNome() << "\n";
            }
        }

        arquivo << "FIM\n";
        arquivo.close();
        cout << "[Salvo] Estado do sistema gravado em 'estado.txt'." << endl;
    }

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