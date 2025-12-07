#include "Sistema.h"
#include "Utils.h"
#include <iostream>
#include <limits>

int main() {
    Sistema sistema;
    int opcao;

    do {
        limparTela();
        std::cout << "=== SISTEMA DE GESTAO DE TREINOS ===" << std::endl;
        std::cout << "1. Gerenciar Exercicios" << std::endl;
        std::cout << "2. Gerenciar Fichas" << std::endl;
        std::cout << "3. Registrar Treino (Historico)" << std::endl;
        std::cout << "4. Consultar Historico" << std::endl;
        std::cout << "0. Sair" << std::endl;
        std::cout << "Opcao: ";
        
        if (!(std::cin >> opcao)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            opcao = -1;
        }

        switch (opcao) {
            case 1: {
                int subOpcao;
                limparTela();
                std::cout << "--- EXERCICIOS ---" << std::endl;
                std::cout << "1. Cadastrar Novo" << std::endl;
                std::cout << "2. Listar Disponiveis" << std::endl;
                std::cout << "3. Excluir (Desativar)" << std::endl;
                std::cout << "Opcao: ";
                std::cin >> subOpcao;

                if (subOpcao == 1) sistema.cadastrarExercicio();
                else if (subOpcao == 2) sistema.listarExercicios();
                else if (subOpcao == 3) sistema.excluirExercicio();
                break;
            }
            case 2: {
                int subOpcao;
                limparTela();
                std::cout << "--- FICHAS DE TREINO ---" << std::endl;
                std::cout << "1. Criar Nova Ficha" << std::endl;
                std::cout << "2. Adicionar Exercicio na Ficha" << std::endl;
                std::cout << "3. Visualizar Fichas" << std::endl;
                std::cout << "Opcao: ";
                std::cin >> subOpcao;

                if (subOpcao == 1) sistema.criarFicha();
                else if (subOpcao == 2) sistema.adicionarExercicioFicha();
                else if (subOpcao == 3) sistema.listarFichas();
                break;
            }
            case 3:
                sistema.registrarTreino();
                break;
            case 4:
                sistema.exibirHistorico();
                break;
            case 0:
                std::cout << "Saindo e salvando dados..." << std::endl;
                break;
            default:
                std::cout << "Opcao invalida!" << std::endl;
                pausar();
        }

    } while (opcao != 0);

    return 0;
}

