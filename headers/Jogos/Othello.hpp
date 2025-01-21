#pragma once

#include "JogoBase.hpp"

class Othello : public JogoBase {
private:
  static std::vector<std::vector<char>> mTabuleiro;
  static const int cTamanho = 8;

public:
  Othello();

  static int getTamanho() { return cTamanho; }
  static std::vector<std::vector<char>> getTabuleiro() {
    return std::vector<std::vector<char>>(cTamanho,
                                          std::vector<char>(cTamanho, 'x'));
  }
  void iniciarTabuleiro();
  void imprimirTabuleiro() const override;
  bool jogadaValida(int x, int y) const override;
  bool verificarVitoria() const override;
  bool mostrarExecucaoValida();
  void lerJogada() = 0;
  bool cadastrarJogador();
  void jogar();

private:
  std::map<std::shared_ptr<Jogador>, float> mJogadoresPontuacao;
  std::vector<std::vector<char>> mTabuleiro;
  std::shared_ptr<Jogador> mJogadorAtual;
};
