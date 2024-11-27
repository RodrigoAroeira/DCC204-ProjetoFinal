#pragma once

#include "Jogador.hpp"

#include <map>
#include <memory>
#include <vector>

class JogoBase {
public:
  JogoBase() : mJogadoresPontuacao{}, mJogadorAtual{nullptr} {};
  virtual ~JogoBase() = default;

  bool cadastrarJogador(const Jogador &jogador);
  void mudarJogadorAtual();

  virtual void lerJogada() = 0;
  virtual bool jogadaValida(int x, int y) const = 0;
  virtual bool verificarVitoria() const = 0;
  virtual void imprimirTabuleiro() const = 0;

protected:
  std::map<Jogador, float> mJogadoresPontuacao;
  std::vector<std::vector<char>> mTabuleiro;
  std::unique_ptr<Jogador> mJogadorAtual;
};
