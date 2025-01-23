#include "Lig4.hpp"

#include <iostream>
#include <limits>
#include <stdexcept>

#include "helpers.hpp"

std::vector<std::vector<char>> tabuleiroInicialLig4(6,
                                                    std::vector<char>(7, ' '));

Lig4::Lig4(Leaderboard &leaderboard) : JogoBase(leaderboard) {
  mTabuleiro = tabuleiroInicialLig4;
}

Lig4::~Lig4() {
  for (const auto &[jogador, _] : mJogadoresPontuacao) {
    int pontos = mJogadoresPontuacao.at(jogador);
    jogador->aumentarJV(pontos);
    try {
      mLeaderboard.addJogador(jogador);
    } catch (const std::exception &) {
      mLeaderboard.updateJogador(jogador);
    }
  }
}

bool Lig4::cadastrarJogador(std::shared_ptr<Jogador> jogador) {
  if (!JogoBase::cadastrarJogador(jogador)) {
    return false;
  }

  char tipo = mJogadorTipo.empty() ? 'o' : 'x';
  mJogadorTipo[jogador] = tipo;
  return true;
}

void Lig4::mudarJogadorAtual() {
  for (const auto &[jogador, _] : mJogadorTipo) {
    if (jogador != mJogadorAtual) {
      mJogadorAtual = jogador;
      return;
    }
  }
}

bool Lig4::jogadaValida(int col, int /*ignored*/) const {
  return col >= 0 && col < COLS && mTabuleiro[0][col] == ' ';
}

void Lig4::lerJogada() {
  int col;
  while (true) {
    std::cout << "Jogador " << mJogadorAtual->getNome() << " ("
              << mJogadorTipo[mJogadorAtual] << "), escolha uma coluna (0-6): ";
    std::cin >> col;

    if (!std::cin || !jogadaValida(col, 0)) {
      std::cout << "Entrada inválida! Tente novamente.\n";
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      continue;
    }

    for (int row = ROWS - 1; row >= 0; --row) {
      if (mTabuleiro[row][col] == ' ') {
        mTabuleiro[row][col] = mJogadorTipo[mJogadorAtual];
        return;
      }
    }
  }
}

void Lig4::imprimirTabuleiro() const {
  std::cout << " 0 1 2 3 4 5 6\n";
  for (int row = 0; row < ROWS; ++row) {
    for (int col = 0; col < COLS; ++col) {
      std::cout << "|" << mTabuleiro[row][col];
    }
    std::cout << "|\n";
  }
}

bool Lig4::verificarVitoria() const {
  char jogadorChar = mJogadorTipo.at(mJogadorAtual);

  // Verifica linhas
  for (int row = 0; row < ROWS; ++row) {
    for (int col = 0; col < COLS - 3; ++col) {
      if (mTabuleiro[row][col] == jogadorChar &&
          mTabuleiro[row][col + 1] == jogadorChar &&
          mTabuleiro[row][col + 2] == jogadorChar &&
          mTabuleiro[row][col + 3] == jogadorChar) {
        return true;
      }
    }
  }

  // Verifica colunas
  for (int col = 0; col < COLS; ++col) {
    for (int row = 0; row < ROWS - 3; ++row) {
      if (mTabuleiro[row][col] == jogadorChar &&
          mTabuleiro[row + 1][col] == jogadorChar &&
          mTabuleiro[row + 2][col] == jogadorChar &&
          mTabuleiro[row + 3][col] == jogadorChar) {
        return true;
      }
    }
  }

  // Verifica diagonais
  for (int row = 0; row < ROWS - 3; ++row) {
    for (int col = 0; col < COLS - 3; ++col) {
      if (mTabuleiro[row][col] == jogadorChar &&
          mTabuleiro[row + 1][col + 1] == jogadorChar &&
          mTabuleiro[row + 2][col + 2] == jogadorChar &&
          mTabuleiro[row + 3][col + 3] == jogadorChar) {
        return true;
      }
    }
  }

  for (int row = 0; row < ROWS - 3; ++row) {
    for (int col = 3; col < COLS; ++col) {
      if (mTabuleiro[row][col] == jogadorChar &&
          mTabuleiro[row + 1][col - 1] == jogadorChar &&
          mTabuleiro[row + 2][col - 2] == jogadorChar &&
          mTabuleiro[row + 3][col - 3] == jogadorChar) {
        return true;
      }
    }
  }

  return false;
}

bool Lig4::isTabuleiroCheio() const {
  for (int col = 0; col < COLS; ++col) {
    if (mTabuleiro[0][col] == ' ') {
      return false;
    }
  }
  return true;
}

void Lig4::jogar() {
  if (mJogadorTipo.size() != 2) {
    throw std::runtime_error("Lig4 requer 2 jogadores.");
  }

  mudarJogadorAtual();
  std::cout << mJogadorAtual->getNome() << " começa!\n";

  while (true) {
    limparTela();
    imprimirTabuleiro();
    lerJogada();

    if (verificarVitoria()) {
      limparTela();
      imprimirTabuleiro();
      std::cout << mJogadorAtual->getNome() << " venceu!\n";
      mJogadoresPontuacao[mJogadorAtual] += 1;
      break;
    }

    if (isTabuleiroCheio()) {
      limparTela();
      imprimirTabuleiro();
      std::cout << "Empate! Deseja jogar novamente (y/n)? ";
      char resposta;
      std::cin >> resposta;
      if (tolower(resposta) == 'y') {
        mTabuleiro = tabuleiroInicialLig4;
        continue;
      } else {
        break;
      }
    }

    mudarJogadorAtual();
  }
}
