#ifndef SISTEMA_H
#define SISTEMA_H

#include <vector>
#include "Exercicio.h"
#include "Ficha.h"
#include "Historico.h"

class Sistema {
private:
    std::vector<Exercicio*> exercicios;
    std::vector<Ficha*> fichas;
    Historico historico;

    // Métodos auxiliares privados
    Exercicio* buscarExercicioPorId(int id);
    Ficha* buscarFichaPorId(int id);

public:
    Sistema();
    ~Sistema();

    // Gerenciamento de Dados
    void carregarDados();
    void salvarDados();

    // Funcionalidades de Exercícios
    void cadastrarExercicio();
    void listarExercicios();
    void excluirExercicio(); // Lógico

    // Funcionalidades de Fichas
    void criarFicha();
    void adicionarExercicioFicha();
    void listarFichas();

    // Execução
    void registrarTreino();
    void exibirHistorico();
};

#endif

