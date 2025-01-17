#pragma once

#include <map>
#include <vector>

#include "Jogador.hpp"
#include "Leaderboard.hpp"

class JogoBase {
public:
  JogoBase(Leaderboard &leaderboard);
  virtual ~JogoBase() = default;

  virtual bool cadastrarJogador(const Jogador &jogador);
  virtual void mudarJogadorAtual();

  virtual void jogar() = 0;
  virtual void lerJogada() = 0;
  virtual bool jogadaValida(int x, int y) const = 0;
  virtual bool verificarVitoria() const = 0;
  virtual void imprimirTabuleiro() const = 0;

protected:
  std::map<Jogador, float> mJogadoresPontuacao;
  std::vector<std::vector<char>> mTabuleiro;
  Jogador *mJogadorAtual; // Ponteiros de stack
  Leaderboard &mLeaderboard;
};
