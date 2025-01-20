#pragma once

#include <map>

#include "JogoBase.hpp"

class JogoDaVelha : public JogoBase {
public:
  JogoDaVelha(Leaderboard &leaderboard);
  ~JogoDaVelha() override;

  bool cadastrarJogador(std::shared_ptr<Jogador> jogador) override;

  void jogar() override;
  bool jogadaValida(int x, int y) const override;
  void lerJogada() override;
  void imprimirTabuleiro() const override;

private:
  void mudarJogadorAtual() override;

private:
  std::map<std::shared_ptr<Jogador>, char> mJogadorTipo;
};
