#include "Forca.h"
#include <iostream>

// Construtor para novos cadastros
Forca::Forca(std::string nome, double carga, int series, int repeticoes, int tempoDescanso)
    : Exercicio(nome) {
    this->carga = carga;
    this->series = series;
    this->repeticoes = repeticoes;
    this->tempoDescanso = tempoDescanso;
}

// Construtor para leitura de arquivo
Forca::Forca(int id, std::string nome, bool ativo, double carga, int series, int repeticoes, int tempoDescanso)
    : Exercicio(id, nome, ativo) {
    this->carga = carga;
    this->series = series;
    this->repeticoes = repeticoes;
    this->tempoDescanso = tempoDescanso;
}

// Exibir detalhes do exercício
void Forca::exibirDetalhes() const {
    std::cout << "=== EXERCÍCIO DE FORÇA ===\n";
    std::cout << "ID: " << id << "\n";
    std::cout << "Nome: " << nome << "\n";
    std::cout << "Status: " << (ativo ? "Ativo" : "Inativo") << "\n";
    std::cout << "Carga: " << carga << " kg\n";
    std::cout << "Séries: " << series << "\n";
    std::cout << "Repetições: " << repeticoes << "\n";
    std::cout << "Tempo de descanso: " << tempoDescanso << " segundos\n";
    std::cout << "Tempo estimado: " << calcularTempoEstimado() << " minutos\n";
    std::cout << "Calorias gastas (estimado): " << calcularCaloriasGastas() << "\n";
    std::cout << "===========================\n";
}

// Calcular tempo estimado (em minutos)
double Forca::calcularTempoEstimado() const {
    // Tempo = (séries * (repeticoes + descanso entre repetições)) + (descanso entre séries)
    // Aproximadamente: tempo por série = 30 segundos + tempo de descanso
    double tempoSerieSegundos = (repeticoes * 2) + tempoDescanso; // 2 segundos por repetição
    double tempoTotalSegundos = (series * tempoSerieSegundos);
    return tempoTotalSegundos / 60.0; // Converter para minutos
}

// Calcular calorias gastas
double Forca::calcularCaloriasGastas() const {
    // Estimativa: 0.05 calorias por kg de carga por repetição
    double caloriasBase = carga * repeticoes * series * 0.05;
    return caloriasBase;
}

// Retornar tipo do exercício (2 = Força)
int Forca::getTipo() const {
    return 2;
}

// Getters
double Forca::getCarga() const { 
    return carga;
}

int Forca::getSeries() const { 
    return series;
}

int Forca::getRepeticoes() const { 
    return repeticoes;
}

int Forca::getTempoDescanso() const { 
    return tempoDescanso;
}
