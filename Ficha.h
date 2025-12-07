#ifndef FICHA_H
#define FICHA_H

#include <string>
#include <vector>
#include "Exercicio.h"

class Ficha {
private:
    int id;
    std::string nome;
    std::vector<Exercicio*> exercicios; // Polimorfismo: guarda ponteiros para base
    
    static int proximoId;

public:
    // Construtores
    Ficha(std::string nome);
    Ficha(int id, std::string nome); // Para arquivo

    ~Ficha();

    void adicionarExercicio(Exercicio* exercicio);
    void exibirFicha() const;
    
    double calcularTempoTotal() const;
    double calcularCaloriasTotais() const;
    
    int getId() const;
    std::string getNome() const;
    const std::vector<Exercicio*>& getExercicios() const;
    
    static void atualizarProximoId(int maiorId);
};

#endif

