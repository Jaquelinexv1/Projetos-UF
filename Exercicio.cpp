#include "Exercicio.h"

// Inicialização da variável estática
int Exercicio::proximoId = 1;

// Construtor para novos cadastros
Exercicio::Exercicio(std::string nome) {
    this->nome = nome;
    this->ativo = true;
    this->id = proximoId++;
}

// Construtor para leitura de arquivo
Exercicio::Exercicio(int id, std::string nome, bool ativo) {
    this->id = id;
    this->nome = nome;
    this->ativo = ativo;
    
    // Se o ID lido do arquivo for maior ou igual ao próximo,
    // atualizamos o contador para evitar colisões no futuro
    if (id >= proximoId) {
        proximoId = id + 1;
    }
}

Exercicio::~Exercicio() {}

int Exercicio::getId() const {
    return id;
}

std::string Exercicio::getNome() const {
    return nome;
}

bool Exercicio::isAtivo() const {
    return ativo;
}

void Exercicio::desativar() {
    ativo = false;
}

void Exercicio::atualizarProximoId(int maiorId) {
    if (maiorId >= proximoId) {
        proximoId = maiorId + 1;
    }
}

