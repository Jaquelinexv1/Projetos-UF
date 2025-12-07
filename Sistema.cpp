#include "Sistema.h"
#include "Cardio.h"
#include "Forca.h"
#include "Utils.h"
#include <iostream>
#include <fstream>
#include <limits>
#include <sstream>

Sistema::Sistema() {
    carregarDados();
}

Sistema::~Sistema() {
    salvarDados();
    for (auto ex : exercicios) {
        delete ex;
    }
    exercicios.clear();
    
    for (auto ficha : fichas) {
        delete ficha;
    }
    fichas.clear();
}

void Sistema::carregarDados() {
    std::ifstream arquivoEx("exercicios.txt");
    if (arquivoEx.is_open()) {
        std::string linha;
        while (std::getline(arquivoEx, linha)) {
            if (linha.empty()) continue;
            
            std::istringstream iss(linha);
            std::string tipoStr, idStr, nome, statusStr;
            
            if (std::getline(iss, tipoStr, ';') &&
                std::getline(iss, idStr, ';') &&
                std::getline(iss, nome, ';')) {
                
                try {
                    int tipo = std::stoi(tipoStr);
                    int id = std::stoi(idStr);
                    
                    if (tipo == 1) {
                        std::string durStr, calorStr;
                        if (std::getline(iss, durStr, ';') &&
                            std::getline(iss, calorStr, ';') &&
                            std::getline(iss, statusStr, ';')) {
                            int duracao = std::stoi(durStr);
                            double calorias = std::stod(calorStr);
                            bool ativo = (std::stoi(statusStr) == 1);
                            exercicios.push_back(new Cardio(id, nome, ativo, duracao, calorias));
                            Exercicio::atualizarProximoId(id);
                        }
                    } else if (tipo == 2) {
                        std::string cargaStr, seriesStr, repStr, tempoStr;
                        if (std::getline(iss, cargaStr, ';') &&
                            std::getline(iss, seriesStr, ';') &&
                            std::getline(iss, repStr, ';') &&
                            std::getline(iss, tempoStr, ';') &&
                            std::getline(iss, statusStr, ';')) {
                            double carga = std::stod(cargaStr);
                            int series = std::stoi(seriesStr);
                            int repeticoes = std::stoi(repStr);
                            int tempo = std::stoi(tempoStr);
                            bool ativo = (std::stoi(statusStr) == 1);
                            exercicios.push_back(new Forca(id, nome, ativo, carga, series, repeticoes, tempo));
                            Exercicio::atualizarProximoId(id);
                        }
                    }
                } catch (...) {
                    std::cerr << "Erro ao carregar exercício.\n";
                }
            }
        }
        arquivoEx.close();
    }
    
    std::ifstream arquivoFicha("fichas.txt");
    if (arquivoFicha.is_open()) {
        std::string linha;
        while (std::getline(arquivoFicha, linha)) {
            if (linha.empty()) continue;
            
            std::istringstream iss(linha);
            std::string idStr, nome, totalStr;
            
            if (std::getline(iss, idStr, ';') &&
                std::getline(iss, nome, ';') &&
                std::getline(iss, totalStr, ';')) {
                
                try {
                    int id = std::stoi(idStr);
                    int total = std::stoi(totalStr);
                    Ficha* ficha = new Ficha(id, nome);
                    Ficha::atualizarProximoId(id);
                    
                    std::string exIdStr;
                    for (int i = 0; i < total && std::getline(iss, exIdStr, ';'); ++i) {
                        int exId = std::stoi(exIdStr);
                        Exercicio* ex = buscarExercicioPorId(exId);
                        if (ex) ficha->adicionarExercicio(ex);
                    }
                    fichas.push_back(ficha);
                } catch (...) {
                    std::cerr << "Erro ao carregar ficha.\n";
                }
            }
        }
        arquivoFicha.close();
    }
    
    historico.carregarDeArquivo();
}

void Sistema::salvarDados() {
    std::ofstream arquivoEx("exercicios.txt");
    for (const auto& ex : exercicios) {
        if (ex->getTipo() == 1) {
            Cardio* c = dynamic_cast<Cardio*>(ex);
            arquivoEx << "1;" << ex->getId() << ";" << ex->getNome() << ";"
                      << c->getDuracao() << ";" << c->getCaloriasPorMinuto() << ";"
                      << (ex->isAtivo() ? "1" : "0") << "\n";
        } else if (ex->getTipo() == 2) {
            Forca* f = dynamic_cast<Forca*>(ex);
            arquivoEx << "2;" << ex->getId() << ";" << ex->getNome() << ";"
                      << f->getCarga() << ";" << f->getSeries() << ";"
                      << f->getRepeticoes() << ";" << f->getTempoDescanso() << ";"
                      << (ex->isAtivo() ? "1" : "0") << "\n";
        }
    }
    arquivoEx.close();
    
    std::ofstream arquivoFicha("fichas.txt");
    for (const auto& ficha : fichas) {
        const auto& exercs = ficha->getExercicios();
        arquivoFicha << ficha->getId() << ";" << ficha->getNome() << ";" << exercs.size() << ";";
        for (size_t i = 0; i < exercs.size(); ++i) {
            if (i > 0) arquivoFicha << ";";
            arquivoFicha << exercs[i]->getId();
        }
        arquivoFicha << "\n";
    }
    arquivoFicha.close();
    
    historico.salvarEmArquivo();
}

Exercicio* Sistema::buscarExercicioPorId(int id) {
    for (auto ex : exercicios) {
        if (ex->getId() == id) {
            return ex;
        }
    }
    return nullptr;
}

Ficha* Sistema::buscarFichaPorId(int id) {
    for (auto ficha : fichas) {
        if (ficha->getId() == id) {
            return ficha;
        }
    }
    return nullptr;
}

void Sistema::cadastrarExercicio() {
    std::cout << "\n=== CADASTRAR EXERCÍCIO ===\n";
    std::cout << "Tipo de exercício:\n";
    std::cout << "1. Cardio\n";
    std::cout << "2. Força\n";
    std::cout << "Opção: ";
    
    int opcao;
    std::cin >> opcao;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    std::cout << "Nome do exercício: ";
    std::string nome;
    std::getline(std::cin, nome);
    
    if (opcao == 1) {
        std::cout << "Duração (minutos): ";
        int duracao;
        std::cin >> duracao;
        std::cout << "Calorias por minuto: ";
        double calorias;
        std::cin >> calorias;
        std::cin.ignore();
        
        exercicios.push_back(new Cardio(nome, duracao, calorias));
        std::cout << "Exercício Cardio cadastrado com sucesso!\n";
    } else if (opcao == 2) {
        std::cout << "Carga (kg): ";
        double carga;
        std::cin >> carga;
        std::cout << "Séries: ";
        int series;
        std::cin >> series;
        std::cout << "Repetições: ";
        int repeticoes;
        std::cin >> repeticoes;
        std::cout << "Tempo de descanso (segundos): ";
        int tempo;
        std::cin >> tempo;
        std::cin.ignore();
        
        exercicios.push_back(new Forca(nome, carga, series, repeticoes, tempo));
        std::cout << "Exercício de Força cadastrado com sucesso!\n";
    } else {
        std::cout << "Opção inválida.\n";
    }
}

void Sistema::listarExercicios() {
    std::cout << "\n=== EXERCÍCIOS CADASTRADOS ===\n";
    
    if (exercicios.empty()) {
        std::cout << "Nenhum exercício cadastrado.\n";
        return;
    }
    
    for (size_t i = 0; i < exercicios.size(); ++i) {
        std::cout << "\n[" << (i + 1) << "] ";
        exercicios[i]->exibirDetalhes();
    }
}

void Sistema::excluirExercicio() {
    std::cout << "\n=== EXCLUIR EXERCÍCIO ===\n";
    
    if (exercicios.empty()) {
        std::cout << "Nenhum exercício cadastrado.\n";
        return;
    }
    
    listarExercicios();
    
    std::cout << "\nID do exercício a excluir: ";
    int id;
    std::cin >> id;
    std::cin.ignore();
    
    Exercicio* ex = buscarExercicioPorId(id);
    if (ex) {
        ex->desativar();
        std::cout << "Exercício desativado com sucesso.\n";
    } else {
        std::cout << "Exercício não encontrado.\n";
    }
}

void Sistema::criarFicha() {
    std::cout << "\n=== CRIAR FICHA ===\n";
    std::cout << "Nome da ficha: ";
    std::string nome;
    std::getline(std::cin, nome);
    
    fichas.push_back(new Ficha(nome));
    std::cout << "Ficha criada com sucesso!\n";
}

void Sistema::adicionarExercicioFicha() {
    std::cout << "\n=== ADICIONAR EXERCÍCIO À FICHA ===\n";
    
    if (fichas.empty()) {
        std::cout << "Nenhuma ficha cadastrada.\n";
        return;
    }
    
    std::cout << "\nFichas disponíveis:\n";
    for (size_t i = 0; i < fichas.size(); ++i) {
        std::cout << "[" << (i + 1) << "] ID: " << fichas[i]->getId() 
                  << " - " << fichas[i]->getNome() << "\n";
    }
    
    std::cout << "\nID da ficha: ";
    int idFicha;
    std::cin >> idFicha;
    std::cin.ignore();
    
    Ficha* ficha = buscarFichaPorId(idFicha);
    if (!ficha) {
        std::cout << "Ficha não encontrada.\n";
        return;
    }
    
    if (exercicios.empty()) {
        std::cout << "Nenhum exercício cadastrado.\n";
        return;
    }
    
    std::cout << "\nExercícios disponíveis:\n";
    for (size_t i = 0; i < exercicios.size(); ++i) {
        std::cout << "[" << (i + 1) << "] ID: " << exercicios[i]->getId() 
                  << " - " << exercicios[i]->getNome() << "\n";
    }
    
    std::cout << "\nID do exercício: ";
    int idExercicio;
    std::cin >> idExercicio;
    std::cin.ignore();
    
    Exercicio* ex = buscarExercicioPorId(idExercicio);
    if (ex) {
        ficha->adicionarExercicio(ex);
        std::cout << "Exercício adicionado à ficha com sucesso!\n";
    } else {
        std::cout << "Exercício não encontrado.\n";
    }
}

void Sistema::listarFichas() {
    std::cout << "\n=== FICHAS CADASTRADAS ===\n";
    
    if (fichas.empty()) {
        std::cout << "Nenhuma ficha cadastrada.\n";
        return;
    }
    
    for (size_t i = 0; i < fichas.size(); ++i) {
        std::cout << "\n[" << (i + 1) << "] ";
        fichas[i]->exibirFicha();
    }
}

void Sistema::registrarTreino() {
    std::cout << "\n=== REGISTRAR TREINO ===\n";
    
    if (fichas.empty()) {
        std::cout << "Nenhuma ficha cadastrada.\n";
        return;
    }
    
    std::cout << "Fichas disponíveis:\n";
    for (size_t i = 0; i < fichas.size(); ++i) {
        std::cout << "[" << (i + 1) << "] ID: " << fichas[i]->getId() 
                  << " - " << fichas[i]->getNome() << "\n";
    }
    
    std::cout << "\nID da ficha de treino: ";
    int idFicha;
    std::cin >> idFicha;
    std::cin.ignore();
    
    Ficha* ficha = buscarFichaPorId(idFicha);
    if (!ficha) {
        std::cout << "Ficha não encontrada.\n";
        return;
    }
    
    if (ficha->getExercicios().empty()) {
        std::cout << "Ficha sem exercícios. Adicione exercícios antes de registrar.\n";
        return;
    }
    
    RegistroTreino registro;
    registro.dataHora = getDataHoraAtual();
    registro.idFicha = ficha->getId();
    registro.nomeFicha = ficha->getNome();
    registro.tempoTotal = ficha->calcularTempoTotal();
    registro.caloriasTotal = ficha->calcularCaloriasTotais();
    
    historico.adicionarRegistro(registro);
    std::cout << "Treino registrado com sucesso!\n";
    std::cout << "Tempo: " << registro.tempoTotal << " minutos\n";
    std::cout << "Calorias: " << registro.caloriasTotal << " kcal\n";
}

void Sistema::exibirHistorico() {
    historico.exibirHistorico();
}
