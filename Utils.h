#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <limits>

// Função auxiliar para limpar a tela independente do SO
inline void limparTela() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Função auxiliar para pausar e esperar ENTER
inline void pausar() {
    std::cout << "\nPressione ENTER para continuar...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

// Função que retorna a data e hora atual formatada
inline std::string getDataHoraAtual() {
    std::time_t t = std::time(nullptr);
    char buffer[100];
    if (std::strftime(buffer, sizeof(buffer), "%d/%m/%Y %H:%M:%S", std::localtime(&t))) {
        return std::string(buffer);
    }
    return "Data Indisponivel";
}

#endif

