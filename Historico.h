#ifndef HISTORICO_H
#define HISTORICO_H

#include <string>
#include <vector>

struct RegistroTreino {
    std::string dataHora;
    int idFicha;
    std::string nomeFicha;
    double tempoTotal;
    double caloriasTotal;
};

class Historico {
private:
    std::vector<RegistroTreino> registros;

public:
    void adicionarRegistro(const RegistroTreino& registro);
    void exibirHistorico() const;
    const std::vector<RegistroTreino>& getRegistros() const;
    
    // Métodos para persistência
    void carregarDeArquivo();
    void salvarEmArquivo() const;
};

#endif

