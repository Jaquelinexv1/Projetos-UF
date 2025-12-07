#ifndef CARDIO_H
#define CARDIO_H

#include "Exercicio.h"

class Cardio : public Exercicio {
private:
    int duracao; // em minutos
    double caloriasPorMinuto;

public:
    // Construtor novo
    Cardio(std::string nome, int duracao, double caloriasPorMinuto);

    // Construtor arquivo
    Cardio(int id, std::string nome, bool ativo, int duracao, double caloriasPorMinuto);

    // Implementação dos métodos virtuais
    void exibirDetalhes() const override;
    double calcularTempoEstimado() const override;
    double calcularCaloriasGastas() const override;
    int getTipo() const override;

    // Getters específicos
    int getDuracao() const;
    double getCaloriasPorMinuto() const;
};

#endif

