#pragma once

#include <map>
#include <memory>

#include "JogoBase.hpp"

class JogoDaVelha : public JogoBase {
public:
  JogoDaVelha(Leaderboard &leaderboard);
  ~JogoDaVelha() override;

  bool cadastrarJogador(std::shared_ptr<Jogador> jogador) override;

  bool jogadaValida(int x, int y) const override;
  void lerJogada() override;
  void imprimirTabuleiro() const override;
  bool verificarVitoria() const override;
  void jogar() override;

private:
  void mudarJogadorAtual() override;

private:
  std::map<std::shared_ptr<Jogador>, char> mJogadorTipo;
};
