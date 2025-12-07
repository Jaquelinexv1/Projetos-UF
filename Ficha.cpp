#include "Ficha.h"
#include <iostream>
#include <iomanip>

int Ficha::proximoId = 1;

// Construtor para novos cadastros
Ficha::Ficha(std::string nome) {
    this->nome = nome;
    this->id = proximoId++;
}

// Construtor para leitura de arquivo
Ficha::Ficha(int id, std::string nome) {
    this->id = id;
    this->nome = nome;
    
    // Se o ID lido for maior ou igual ao próximo, atualiza o contador
    if (id >= proximoId) {
        proximoId = id + 1;
    }
}

// Destrutor (não deletar exercícios, apenas limpar vector)
Ficha::~Ficha() {
    exercicios.clear(); // Apenas limpa o vetor, não deleta os ponteiros
}

// Adicionar exercício à ficha
void Ficha::adicionarExercicio(Exercicio* exercicio) {
    if (exercicio != nullptr) {
        exercicios.push_back(exercicio);
    }
}

// Exibir ficha completa com exercícios e totais
void Ficha::exibirFicha() const {
    std::cout << "\n========================================\n";
    std::cout << "           FICHA DE TREINO\n";
    std::cout << "========================================\n";
    std::cout << "ID: " << id << "\n";
    std::cout << "Nome da Ficha: " << nome << "\n";
    std::cout << "Total de Exercícios: " << exercicios.size() << "\n";
    std::cout << "----------------------------------------\n";
    
    if (exercicios.empty()) {
        std::cout << "Nenhum exercício adicionado.\n";
    } else {
        for (size_t i = 0; i < exercicios.size(); ++i) {
            std::cout << "\n[Exercício " << (i + 1) << "]\n";
            exercicios[i]->exibirDetalhes();
        }
    }
    
    std::cout << "----------------------------------------\n";
    std::cout << "RESUMO TOTAL:\n";
    std::cout << "  Tempo Total: " << std::fixed << std::setprecision(2) 
              << calcularTempoTotal() << " minutos\n";
    std::cout << "  Calorias Totais: " << std::fixed << std::setprecision(2) 
              << calcularCaloriasTotais() << " kcal\n";
    std::cout << "========================================\n\n";
}

// Calcular tempo total da ficha
double Ficha::calcularTempoTotal() const {
    double total = 0.0;
    for (const auto& exercicio : exercicios) {
        total += exercicio->calcularTempoEstimado();
    }
    return total;
}

// Calcular calorias totais da ficha
double Ficha::calcularCaloriasTotais() const {
    double total = 0.0;
    for (const auto& exercicio : exercicios) {
        total += exercicio->calcularCaloriasGastas();
    }
    return total;
}

// Getters
int Ficha::getId() const { 
    return id;
}

std::string Ficha::getNome() const { 
    return nome;
}

const std::vector<Exercicio*>& Ficha::getExercicios() const {
    return exercicios;
}

// Atualizar próximo ID
void Ficha::atualizarProximoId(int maiorId) {
    if (maiorId >= proximoId) {
        proximoId = maiorId + 1;
    }
}
