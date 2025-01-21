#include "JogoBase.hpp"

#include <iostream>
#include <memory>

JogoBase::JogoBase(Leaderboard &leaderboard)
    : mJogadoresPontuacao{}, mJogadorAtual{nullptr},
      mLeaderboard(leaderboard) {};

bool JogoBase::cadastrarJogador(const std::shared_ptr<Jogador> jogador) {
  if (mJogadoresPontuacao.find(jogador) != mJogadoresPontuacao.end()) {
    std::cerr << "Jogador " << jogador->getNome() << " já está registrado"
              << std::endl;
    return false;
  }

  mJogadoresPontuacao[jogador] = 0;
  return true;
}

// void JogoBase::mudarJogadorAtual() {
//   for (auto pair : mJogadoresPontuacao) {
//     auto jogador = pair.first;
//     if (jogador != mJogadorAtual) {
//       mJogadorAtual = jogador;
//       return;
//     }
//   }
// }
