#pragma once

#include <map>
#include <memory>
#include <vector>
#include <iostream>
#include <stdexcept>
#include "JogoBase.hpp"

class Lig4 : public JogoBase {
public:
    static const int ROWS = 6;
    static const int COLS = 7;

    Lig4(Leaderboard &leaderboard);
    ~Lig4() override;

    bool cadastrarJogador(std::shared_ptr<Jogador> jogador) override;
    void mudarJogadorAtual() override;
    bool jogadaValida(int col) const override;
    void lerJogada() override;
    bool verificarVitoria() const override;
    void imprimirTabuleiro() const override;
    void jogar() override;

private:
    bool isTabuleiroCheio() const;

private:
    std::map<std::shared_ptr<Jogador>, char> mJogadorTipo;
    std::vector<std::vector<char>> mTabuleiro;
    std::shared_ptr<Jogador> mJogadorAtual;
};
