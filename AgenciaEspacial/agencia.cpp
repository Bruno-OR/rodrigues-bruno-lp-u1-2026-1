#include <iostream>
#include <string>
#include <vector>
#include "agencia.h"
using namespace std;


int main(int argc, char const *argv[])
{

    vector<Astronauta> astronautas;
    vector<Voo> voos;

    string comando;

    while (cin >> comando)
    {
        if (comando == "FIM")
        {
            break;
        }
        if (comando == "CADASTRAR_ASTRONAUTA")
        {
            bool jaExiste = false;
            string cpfDigitado, nomeDigitado;
            int idadeDigitado;

            cin >> cpfDigitado >> idadeDigitado;
            getline(cin >> ws, nomeDigitado);

            for (int i = 0; i < astronautas.size(); i++)
            {

                if (astronautas[i].cpf == cpfDigitado)
                {
                    jaExiste = true;

                    break;
                }
            }

            if (!jaExiste)
            {
                Astronauta novoAstro(cpfDigitado, nomeDigitado, idadeDigitado);
                astronautas.push_back(novoAstro);
            }

            else
            {
                cout << "O astronauta já está cadastrado!" << endl;
            }
        }

        if (comando == "CADASTRAR_VOO")
        {
            bool jaExiste = false;
            int codDigitado;

            cin >> codDigitado;

            for (int i = 0; i < voos.size(); i++)
            {

                if (voos[i].codigo == codDigitado)
                {
                    jaExiste = true;

                    break;
                }
            }

            if (!jaExiste)
            {
                Voo novoVoo(codDigitado);
                voos.push_back(novoVoo);
            }

            else
            {
                cout << "Voo já cadastrado!" << endl;
            }
        }

        if (comando == "ADICIONAR_ASTRONAUTA")
        {
            string cpfDigitado;
            int codDigitado;
            int indiceAstronauta = -1;
            int indiceVoo = -1;

            cin >> cpfDigitado >> codDigitado;

            for (int i = 0; i < astronautas.size(); i++)
            {
                if (astronautas[i].cpf == cpfDigitado)
                {
                    indiceAstronauta = i;
                    break;
                }
            }

            if (indiceAstronauta != -1)
            {
                if (astronautas[indiceAstronauta].vivo == false)
                {
                    cout << "Erro: Astronauta morto!" << endl;
                }

                else
                {
                    for (int i = 0; i < voos.size(); i++)
                    {
                        if (voos[i].codigo == codDigitado)
                        {
                            indiceVoo = i;
                            break;
                        }
                    }

                    if (indiceVoo != -1)
                    {
                        if (voos[indiceVoo].estado != "Planejado")
                        {
                            cout << "Erro: Voo nao planejado!" << endl;
                        }
                        else
                        {
                            bool jaEstaNoVoo = false;
                            for (int i = 0; i < voos[indiceVoo].cpfsPassageiros.size(); i++)
                            {
                                if (voos[indiceVoo].cpfsPassageiros[i] == cpfDigitado)
                                {
                                    jaEstaNoVoo = true;
                                    break;
                                }
                            }

                            if (!jaEstaNoVoo)
                            {
                                voos[indiceVoo].cpfsPassageiros.push_back(cpfDigitado);
                                astronautas[indiceAstronauta].disponivel = false;
                                cout << "Astronauta adicionado com sucesso!" << endl;
                            }
                            else
                            {
                                cout << "Erro: Astronauta ja esta neste voo!" << endl;
                            }
                        }
                    }
                    else
                    {
                        cout << "Erro: Voo nao encontrado!" << endl;
                    }
                }
            }
            else
            {
                cout << "Erro: CPF nao encontrado!" << endl;
            }
        };

        if (comando == "REMOVER_ASTRONAUTA")
        {
            string cpfDigitado;
            int codDigitado;
            int indiceAstronauta = -1;
            int indiceVoo = -1;

            cin >> cpfDigitado >> codDigitado;

            // BUSCANDO O INDICE DO ASTRONAUTA PARA MUDAR O STATUS DELE DE INDISPONIVEL PARA DISPONIVEL DEPOIS CASO ELE ESTEJA NO VOO
            for (int i = 0; i < astronautas.size(); i++)
            {
                if (astronautas[i].cpf == cpfDigitado)
                {
                    indiceAstronauta = i;
                    break;
                }
            }
            if (indiceAstronauta == -1)
            {
                cout << "ERRO: Astronauta não cadastrado!" << endl;
            }
            else
            {

                // BUSCANDO VOO
                for (int i = 0; i < voos.size(); i++)
                {
                    if (voos[i].codigo == codDigitado)
                    {
                        indiceVoo = i;
                        break;
                    }
                }
                // SAÍ DO LAÇO E AGORA VERIFICO SE O VOO É PLANEJADO OU NÃO
                if (indiceVoo != -1)
                {
                    if (voos[indiceVoo].estado != "Planejado")
                    {
                        cout << "Erro: Voo nao planejado!" << endl;
                    }

                    else
                    {
                        for (int i = 0; i < voos[indiceVoo].cpfsPassageiros.size(); i++)
                        {
                            if (voos[indiceVoo].cpfsPassageiros[i] == cpfDigitado)
                            {
                                voos[indiceVoo].cpfsPassageiros.erase(voos[indiceVoo].cpfsPassageiros.begin() + i);

                                if (astronautas[indiceAstronauta].vivo == true)
                                {
                                    astronautas[indiceAstronauta].disponivel = true;
                                }
                                cout << "Astronauta removido com sucesso!" << endl;
                                break;
                            }
                        }
                    }
                }
                else
                {
                    cout << "ERRO: Voo não existe!" << endl;
                }
            };
        };

        if (comando == "LANCAR_VOO")
        {
            int codDigitado;
            int indiceVoo = -1;
            bool todosVivos = true;

            cin >> codDigitado;

            for (int i = 0; i < voos.size(); i++)
            {
                if (voos[i].codigo == codDigitado)
                {
                    indiceVoo = i;
                    break;
                }
            }
            if (indiceVoo != -1)
            {
                if (voos[indiceVoo].estado == "Planejado")
                {
                    if (voos[indiceVoo].cpfsPassageiros.empty())
                    {

                        cout << "ERRO: Voo sem passageiros" << endl;
                    }
                    else

                    {
                        for (int i = 0; i < voos[indiceVoo].cpfsPassageiros.size(); i++)
                        {
                            string checarCpf = voos[indiceVoo].cpfsPassageiros[i];
                            int indiceGlobal = -1;

                            for (int j = 0; j < astronautas.size(); j++)
                            {
                                if (astronautas[j].cpf == checarCpf)
                                {
                                    indiceGlobal = j;
                                    break;
                                }
                            }

                            if (indiceGlobal != -1 && astronautas[indiceGlobal].vivo == false)
                            {
                                todosVivos = false;
                                break;
                            }
                        }
                        if (todosVivos)
                        {
                            voos[indiceVoo].estado = "Em curso";
                            cout << "Voo lançado com sucesso" << endl;
                        }
                        else
                        {
                            cout << "ERRO: O voo possui astronautas mortos!" << endl;
                        }
                    }
                }
                else
                {
                    cout << "ERRO: Voo não planejado!" << endl;
                }
            }
            else
            {
                cout << "ERRO: Voo não existe!" << endl;
            }
        }

        if (comando == "EXPLODIR_VOO")
        {
            int codDigitado;
            int indiceVoo = -1;

            cin >> codDigitado;

            for (int i = 0; i < voos.size(); i++)
            {
                if (voos[i].codigo == codDigitado)
                {
                    indiceVoo = i;
                    break;
                }
            }
            if (indiceVoo != -1)
            {
                if (voos[indiceVoo].estado == "Em curso")
                {
                    voos[indiceVoo].estado = "Finalizado com explosão";

                    for (int i = 0; i < voos[indiceVoo].cpfsPassageiros.size(); i++)
                    {
                        string checarCpf = voos[indiceVoo].cpfsPassageiros[i];
                        int indiceGlobal = -1;

                        for (int j = 0; j < astronautas.size(); j++)
                        {
                            if (astronautas[j].cpf == checarCpf)
                            {
                                indiceGlobal = j;
                                break;
                            }
                        }

                        if (indiceGlobal != -1)
                        {
                            astronautas[indiceGlobal].vivo = false;
                            astronautas[indiceGlobal].disponivel = false;
                        }
                    }
                }
                else
                {
                    cout << "ERRO: Voo não está em curso!" << endl;
                }
            }
            else
            {
                cout << "ERRO: Voo não existe!" << endl;
            }
        }

        if (comando == "FINALIZAR_VOO")
        {
            int codDigitado;
            int indiceVoo = -1;

            cin >> codDigitado;

            for (int i = 0; i < voos.size(); i++)
            {
                if (voos[i].codigo == codDigitado)
                {
                    indiceVoo = i;
                    break;
                }
            }
            if (indiceVoo != -1)
            {
                if (voos[indiceVoo].estado == "Em curso")
                {
                    voos[indiceVoo].estado = "Finalizado com sucesso";

                    for (int i = 0; i < voos[indiceVoo].cpfsPassageiros.size(); i++)
                    {
                        string checarCpf = voos[indiceVoo].cpfsPassageiros[i];
                        int indiceGlobal = -1;

                        for (int j = 0; j < astronautas.size(); j++)
                        {
                            if (astronautas[j].cpf == checarCpf)
                            {
                                indiceGlobal = j;
                                break;
                            }
                        }

                        if (indiceGlobal != -1)
                        {
                            astronautas[indiceGlobal].vivo = true;
                            astronautas[indiceGlobal].disponivel = true;
                        }
                    }
                }
                else
                {
                    cout << "ERRO: Voo não está em curso!" << endl;
                }
            }
            else
            {
                cout << "ERRO: Voo não existe!" << endl;
            }
        }

        if (comando == "LISTAR_VOOS")
        {
            for (int i = 0; i < voos.size(); i++)
            {
                cout << "--------------------------------" << endl;
                cout << "VOO: " << voos[i].codigo << " | STATUS: " << voos[i].estado << endl;
                cout << "PASSAGEIROS:" << endl;

                for (int j = 0; j < voos[i].cpfsPassageiros.size(); j++)
                {
                    string checarCpf = voos[i].cpfsPassageiros[j];

                    for (int k = 0; k < astronautas.size(); k++)
                    {
                        if (astronautas[k].cpf == checarCpf)
                        {
                            cout << "\t- CPF: " << astronautas[k].cpf << " | NOME: " << astronautas[k].nome << endl;
                        }
                    }
                }
            }
        }
        if (comando == "LISTAR_MORTOS")
        {

            for (int i = 0; i < astronautas.size(); i++)
            {

                if (astronautas[i].vivo == false)
                {
                    cout << "--------------------------------" << endl;
                    cout << "NOME: " << astronautas[i].nome << endl;
                    cout << "CPF: " << astronautas[i].cpf << endl;
                    cout << "VOOS PARTICIPADOS: ";

                    for (int j = 0; j < voos.size(); j++)
                    {

                        if (voos[j].estado != "Planejado")
                        {

                            for (int k = 0; k < voos[j].cpfsPassageiros.size(); k++)
                            {

                                if (voos[j].cpfsPassageiros[k] == astronautas[i].cpf)
                                {

                                    cout << voos[j].codigo << " ";
                                }
                            }
                        }
                    }
                    cout << endl;
                }
            }
        }
        
    }

    return 0;
}
