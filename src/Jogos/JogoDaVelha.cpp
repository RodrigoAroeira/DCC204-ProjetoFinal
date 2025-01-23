#include "JogoDaVelha.hpp"

#include <iostream>
#include <stdexcept>

#include "JogoBase.hpp"
#include "helpers.hpp"

/**
 * @brief Verifica se o tabuleiro está cheio.
 * @param tabuleiro Tabuleiro atual.
 * @return true se o tabuleiro estiver cheio, false caso contrário.
 */
bool isTabuleiroCheio(const std::vector<std::vector<char>> &tabuleiro) {
  for (const auto &row : tabuleiro)
    for (const auto cell : row)
      if (cell == ' ')
        return false;

  return true;
}

/**
 * @brief Tabuleiro inicial do jogo, representado por uma matriz 3x3 vazia.
 */
std::vector<std::vector<char>> tabuleiroInicial{
    {' ', ' ', ' '},
    {' ', ' ', ' '},
    {' ', ' ', ' '},
};

JogoDaVelha::JogoDaVelha(Leaderboard &leaderboard) : JogoBase(leaderboard) {
  mTabuleiro = tabuleiroInicial;
}

JogoDaVelha::~JogoDaVelha() {
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

bool JogoDaVelha::cadastrarJogador(const std::shared_ptr<Jogador> jogador) {
  bool resultado = JogoBase::cadastrarJogador(jogador);
  if (!resultado)
    return false;

  char tipo;
  if (mJogadorTipo.empty()) {
    tipo = 'x';
  } else {
    tipo = 'o';
  }

  mJogadorTipo[jogador] = tipo;
  return true;
}

void JogoDaVelha::mudarJogadorAtual() {
  for (const auto &[jogador, _] : mJogadorTipo) {
    if (jogador != mJogadorAtual) {
      mJogadorAtual = jogador;
      return;
    }
  }
}

bool JogoDaVelha::jogadaValida(int x, int y) const {
  const short rows = mTabuleiro.size();
  const short cols = mTabuleiro[0].size();

  if (x < 0 || x >= rows || y < 0 || y >= cols)
    return false;

  for (const char invalid : {'|', '-', 'x', 'o'}) {
    if (mTabuleiro[x][y] == invalid)
      return false;
  }

  return true;
}

void JogoDaVelha::lerJogada() {
  int x, y;

  while (true) {
    std::cout << "Digite as coordenadas de onde quer jogar: ";
    std::cin >> x >> y;

    if (jogadaValida(x, y))
      break;

    std::cout << "Jogada inválida!\n";
  }

  char pChar = mJogadorTipo[mJogadorAtual];

  mTabuleiro[x][y] = pChar;
}

void JogoDaVelha::imprimirTabuleiro() const {

  const std::vector<char> sep = {'-', '|', '-', '|', '-', '|', '-'};
  std::vector<std::vector<char>> tabuleiro = {
      {'0', '|', mTabuleiro[0][0], '|', mTabuleiro[0][1], '|', mTabuleiro[0][2]},
      sep,
      {'1', '|', mTabuleiro[1][0], '|', mTabuleiro[1][1], '|', mTabuleiro[1][2]},
      sep,
      {'2', '|', mTabuleiro[2][0], '|', mTabuleiro[2][1], '|', mTabuleiro[2][2]},
  };
  std::cout << "_|0 1 2\n";
  for (const auto &row : tabuleiro) {
    for (const auto &cell : row) {
      std::cout << cell;
    }
    std::cout << '\n';
  }
}

bool JogoDaVelha::verificarVitoria() const {
  char jogadorChar = mJogadorTipo.at(mJogadorAtual);
  // Verifica linhas e colunas
  for (int i = 0; i < 3; ++i) {
    if ((mTabuleiro[i][0] == jogadorChar && mTabuleiro[i][1] == jogadorChar &&
         mTabuleiro[i][2] == jogadorChar) ||
        (mTabuleiro[0][i] == jogadorChar && mTabuleiro[1][i] == jogadorChar &&
         mTabuleiro[2][i] == jogadorChar)) {
      return true;
    }
  }
  // Verifica diagonais
  if ((mTabuleiro[0][0] == jogadorChar && mTabuleiro[1][1] == jogadorChar &&
       mTabuleiro[2][2] == jogadorChar) ||
      (mTabuleiro[0][2] == jogadorChar && mTabuleiro[1][1] == jogadorChar &&
       mTabuleiro[2][0] == jogadorChar)) {
    return true;
  }
  return false;
}

void JogoDaVelha::jogar() {
  if (mJogadorTipo.size() != 2) {
    throw std::runtime_error("Jogo da velha requer 2 jogadores.");
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

    if (isTabuleiroCheio(mTabuleiro)) {
      limparTela();
      imprimirTabuleiro();
      std::cout << "Empate! Deseja jogar novamente (y/n)? ";
      char resposta;
      std::cin >> resposta;
      if (tolower(resposta) == 'y') {
        mTabuleiro = tabuleiroInicial;
        continue;
      } else {
        break;
      }
    }

    mudarJogadorAtual();
  }
}
