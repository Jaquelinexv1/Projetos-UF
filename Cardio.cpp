#include "Cardio.h"
#include <iostream>

// Construtor para novos cadastros
Cardio::Cardio(std::string nome, int duracao, double caloriasPorMinuto) 
    : Exercicio(nome) {
    this->duracao = duracao;
    this->caloriasPorMinuto = caloriasPorMinuto;
}

// Construtor para leitura de arquivo
Cardio::Cardio(int id, std::string nome, bool ativo, int duracao, double caloriasPorMinuto)
    : Exercicio(id, nome, ativo) {
    this->duracao = duracao;
    this->caloriasPorMinuto = caloriasPorMinuto;
}

// Exibir detalhes do exercício
void Cardio::exibirDetalhes() const {
    std::cout << "=== EXERCÍCIO CARDIO ===\n";
    std::cout << "ID: " << id << "\n";
    std::cout << "Nome: " << nome << "\n";
    std::cout << "Status: " << (ativo ? "Ativo" : "Inativo") << "\n";
    std::cout << "Duração: " << duracao << " minutos\n";
    std::cout << "Calorias por minuto: " << caloriasPorMinuto << "\n";
    std::cout << "Total de calorias: " << calcularCaloriasGastas() << "\n";
    std::cout << "========================\n";
}

// Calcular tempo estimado (duração em minutos)
double Cardio::calcularTempoEstimado() const {
    return duracao;
}

// Calcular calorias gastas
double Cardio::calcularCaloriasGastas() const {
    return duracao * caloriasPorMinuto;
}

// Retornar tipo do exercício (1 = Cardio)
int Cardio::getTipo() const {
    return 1;
}

// Getter de duração
int Cardio::getDuracao() const {
    return duracao;
}

// Getter de calorias por minuto
double Cardio::getCaloriasPorMinuto() const {
    return caloriasPorMinuto;
}
