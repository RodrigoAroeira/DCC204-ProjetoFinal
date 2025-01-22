#pragma once

#include "JogoBase.hpp"

class Othello : public JogoBase {
private:
  static std::vector<std::vector<char>> tabuleiroInicial;

public:
  Othello(Leaderboard &leaderboard);
  ~Othello() override;

  static void inicializarTabuleiro();
  bool cadastrarJogador(std::shared_ptr<Jogador> jogador) override;
  bool jogadaValida(int x, int y) const override;
  void lerJogada() override;
  void imprimirTabuleiro() const override;
  bool verificarVitoria() const override;
  int mostrarExecucaoValida() const;
  void jogar() override;

private:
  void mudarJogadorAtual() override;

private:
  std::map<std::shared_ptr<Jogador>, char> mJogadorTipo;
};
