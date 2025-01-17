#include "JogoBase.hpp"

#include <iostream>

JogoBase::JogoBase(Leaderboard &leaderboard)
    : mJogadoresPontuacao{}, mJogadorAtual{nullptr},
      mLeaderboard(leaderboard) {};

bool JogoBase::cadastrarJogador(const Jogador &jogador) {
  if (mJogadoresPontuacao.find(jogador) != mJogadoresPontuacao.end()) {
    std::cerr << "Jogador " << jogador.getNome() << " já está registrado"
              << std::endl;
    return false;
  }

  mJogadoresPontuacao[jogador] = 0;
  return true;
}
