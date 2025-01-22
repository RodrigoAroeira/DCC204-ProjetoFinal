#include "Othello.hpp"

#include <iostream>
#include <vector>

#include "JogoBase.hpp"

void limparTela() {
#ifdef _WIN32
  return (void)system("cls");
#else
  return (void)system("clear");
#endif
}

std::vector<std::vector<char>> Othello::tabuleiroInicial{
    {'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x'},
    {'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x'},
    {'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x'},
    {'x', 'x', 'x', '1', '2', 'x', 'x', 'x'},
    {'x', 'x', 'x', '2', '1', 'x', 'x', 'x'},
    {'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x'},
    {'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x'},
    {'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x'},
};

void Othello::inicializarTabuleiro() {
  // Você pode usar esse método para redefinir o tabuleiro, se necessário
  tabuleiroInicial = {{'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x'},
                      {'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x'},
                      {'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x'},
                      {'x', 'x', 'x', '1', '2', 'x', 'x', 'x'},
                      {'x', 'x', 'x', '2', '1', 'x', 'x', 'x'},
                      {'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x'},
                      {'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x'},
                      {'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x'}};
}

Othello::Othello(Leaderboard &leaderboard) : JogoBase(leaderboard) {
  mTabuleiro = tabuleiroInicial;
}

Othello::~Othello() {
  //
}

bool Othello::cadastrarJogador(std::shared_ptr<Jogador> jogador) {
  bool resultado = JogoBase::cadastrarJogador(jogador);
  if (!resultado)
    return false;

  char tipo;
  if (mJogadorTipo.empty()) {
    tipo = '1';
  } else {
    tipo = '2';
  }

  mJogadorTipo[jogador] = tipo;
  return true;
}

void Othello::mudarJogadorAtual() {
  auto it = mJogadorTipo.find(mJogadorAtual);
  if (it != mJogadorTipo.end()) {
    // Alternar entre os jogadores
    if (it == mJogadorTipo.begin()) {
      mJogadorAtual = std::next(mJogadorTipo.begin())->first;
    } else {
      mJogadorAtual = mJogadorTipo.begin()->first;
    }
    std::cout << "Alterando para: " << mJogadorAtual->getNome() << std::endl;
  } else {
    throw std::runtime_error("Jogador atual não encontrado em mJogadorTipo!");
  }
}

bool Othello::jogadaValida(int x, int y) const {
  if (x < 0 || x >= 8 || y < 0 || y >= 8)
    return false;

  if (!(mTabuleiro[x][y] == 'x'))
    return false;

  auto it = mJogadorTipo.find(mJogadorAtual);
  if (it == mJogadorTipo.end()) {
    throw std::runtime_error("Jogador atual não encontrado no mapa!");
  }

  char jogador = it->second;
  char adversario = (jogador == '1') ? '2' : '1';

  const int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
  const int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};

  for (int dir = 0; dir < 8; ++dir) {
    int nx = x + dx[dir], ny = y + dy[dir];
    bool encontrouAdversario = false;

    while (nx >= 0 && nx < 8 && ny >= 0 && ny < 8) {
      if (mTabuleiro[nx][ny] == adversario) {
        encontrouAdversario = true;
      } else if (mTabuleiro[nx][ny] == jogador) {
        if (encontrouAdversario)
          return true;
        break;
      } else
        break;

      nx += dx[dir];
      ny += dy[dir];
    }
  }
  return false;
}

int Othello::mostrarExecucaoValida() const {
  int contagemExecucoesValidas = 0;
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      if (jogadaValida(i, j)) {
        contagemExecucoesValidas++;
        std::cout << "São válidas as seguintes coordenadas:"
                  << "[" << i << "][" << j << "]" << std::endl;
      }
    }
  }
  return contagemExecucoesValidas;
}

void Othello::lerJogada() {
  int x, y;
  while (true) {
    std::cout << "Digite a coordenada x: ";
    std::cin >> x;

    std::cout << "Digite a coordenada y: ";
    std::cin >> y;
    if (jogadaValida(x, y))
      break;

    std::cout << "Jogada inválida!\n";
  }

  char pChar = mJogadorTipo[mJogadorAtual];

  mTabuleiro[x][y] = pChar;
}

void Othello::imprimirTabuleiro() const {
  for (const auto &row : mTabuleiro) {
    for (const auto &cell : row) {
      std::cout << cell << " ";
    }
    std::cout << std::endl;
  }
}

bool Othello::verificarVitoria() const {
  int contagemJogador = 0;
  int contagemAdversario = 0;
  int contagemExecucoesValidas = mostrarExecucaoValida();

  if (contagemExecucoesValidas == 0) {

    for (int i = 0; i < 8; i++) {
      for (int j = 0; j < 8; j++) {
        if (mTabuleiro[i][j] == '1') {
          contagemJogador++;
        } else if (mTabuleiro[i][j] == '2') {
          contagemAdversario++;
        }
      }
    }
    if ((contagemJogador > contagemAdversario) ||
        (contagemAdversario > contagemJogador)) {
      return true;
    }
  }

  return false;
}

void Othello::jogar() {
  if (mJogadorTipo.size() != 2) {
    throw std::runtime_error("Reversi requer 2 jogadores.");
  }
  mJogadorAtual = mJogadorTipo.begin()->first;
  std::cout << mJogadorAtual->getNome() << " começa!\n";
  while (true) {
    imprimirTabuleiro();

    int jogadasValidas = mostrarExecucaoValida();

    if (jogadasValidas == 0) {
      mudarJogadorAtual();
      if (mostrarExecucaoValida() == 0) {
        limparTela();
        imprimirTabuleiro();
        verificarVitoria();
        break;
      }
      std::cout << mJogadorAtual->getNome()
                << " não possui jogadas válidas. Passando turno!\n";
      continue;
    }

    std::cout << "[" << mJogadorAtual->getNome() << "]" << std::endl;
    lerJogada();

    if (verificarVitoria()) {
      imprimirTabuleiro();
      std::cout << mJogadorAtual->getNome() << " venceu!\n";
      mJogadoresPontuacao[mJogadorAtual]++;
      std::cout << "Deseja jogar novamente (y/n)? ";
      char resposta;
      std::cin >> resposta;
      if (tolower(resposta) == 'y') {
        mTabuleiro = tabuleiroInicial;
        continue;
      } else {
        mudarJogadorAtual();
        break;
      }
    }
    limparTela();
    mudarJogadorAtual();
  }
}