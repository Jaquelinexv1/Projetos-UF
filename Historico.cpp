#include "Historico.h"
#include "Utils.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>

// Adicionar registro ao historico
void Historico::adicionarRegistro(const RegistroTreino& registro) {
    registros.push_back(registro);
}

// Exibir historico completo
void Historico::exibirHistorico() const {
    std::cout << "\n========================================\n";
    std::cout << "        HISTORICO DE TREINOS\n";
    std::cout << "========================================\n";
    
    if (registros.empty()) {
        std::cout << "Nenhum treino registrado.\n";
    } else {
        std::cout << std::left << std::setw(20) << "Data/Hora"
                  << std::setw(15) << "ID Ficha"
                  << std::setw(20) << "Nome Ficha"
                  << std::setw(12) << "Tempo (min)"
                  << std::setw(12) << "Calorias\n";
        std::cout << "----------------------------------------"
                  << "----------------------------------------\n";
        
        for (size_t i = 0; i < registros.size(); ++i) {
            std::cout << std::left << std::setw(20) << registros[i].dataHora
                      << std::setw(15) << registros[i].idFicha
                      << std::setw(20) << registros[i].nomeFicha
                      << std::fixed << std::setprecision(2)
                      << std::setw(12) << registros[i].tempoTotal
                      << std::setw(12) << registros[i].caloriasTotal << "\n";
        }
    }
    std::cout << "========================================\n\n";
}

// Getter de registros
const std::vector<RegistroTreino>& Historico::getRegistros() const {
    return registros;
}

// Carregar historico do arquivo
void Historico::carregarDeArquivo() {
    std::ifstream arquivo("historico.txt");
    if (!arquivo.is_open()) {
        // Arquivo nao existe, comeca vazio (nao e erro)
        return;
    }
    std::string linha;
    while (std::getline(arquivo, linha)) {
        if (linha.empty()) continue; // Pula linhas vazias
        // Formato esperado: DATA;ID_FICHA;NOME_FICHA;TEMPO_TOTAL;CALORIAS_TOTAL
        std::istringstream iss(linha);
        std::string dataHora, idStr, nomeFicha, tempoStr, caloriasStr;
        if (std::getline(iss, dataHora, ';') &&
            std::getline(iss, idStr, ';') &&
            std::getline(iss, nomeFicha, ';') &&
            std::getline(iss, tempoStr, ';') &&
            std::getline(iss, caloriasStr, ';')) {
            try {
                RegistroTreino registro;
                registro.dataHora = dataHora;
                registro.idFicha = std::stoi(idStr);
                registro.nomeFicha = nomeFicha;
                registro.tempoTotal = std::stod(tempoStr);
                registro.caloriasTotal = std::stod(caloriasStr);
                registros.push_back(registro);
            } catch (...) {
                std::cerr << "Aviso: Erro ao carregar registro do arquivo.\n";
            }
        }
    }
    arquivo.close();
}

// Salvar historico no arquivo
void Historico::salvarEmArquivo() const {
    std::ofstream arquivo("historico.txt");
    if (!arquivo.is_open()) {
        std::cerr << "Erro ao abrir arquivo historico para escrita.\n";
        return;
    }
    for (const auto& registro : registros) {
        arquivo << registro.dataHora << ";"
                << registro.idFicha << ";"
                << registro.nomeFicha << ";"
                << std::fixed << std::setprecision(2) << registro.tempoTotal << ";"
                << std::fixed << std::setprecision(2) << registro.caloriasTotal << "\n";
    }
    arquivo.close();
}
