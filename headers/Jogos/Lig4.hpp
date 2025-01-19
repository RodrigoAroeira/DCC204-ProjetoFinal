#pragma once

#include "JogoBase.hpp"
#include <vector>
#include <map>
#include <memory>
#include <string>
#include <iostream>
#include <stdexcept>

class Lig4 : public JogoBase {
public:
    static const int ROWS = 6;
    static const int COLS = 7;

    Lig4();

    bool cadastrarJogador(const Jogador &jogador) override;
    void mudarJogadorAtual() override;
    bool jogadaValida(int col) const;
    void lerJogada() override;
    bool verificarVitoria() const override;
    void imprimirTabuleiro() const override;
    void jogar() override;

    friend std::ostream &operator<<(std::ostream &os, const Lig4 &j);

private:
    bool isTabuleiroCheio() const;

private:
    std::map<std::shared_ptr<Jogador>, float> mJogadoresPontuacao;
    std::vector<std::vector<char>> mTabuleiro;
    std::shared_ptr<Jogador> mJogadorAtual;
};
