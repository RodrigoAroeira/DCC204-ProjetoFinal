#include "Othello.hpp"

#include <iostream>

/// Define o tipo de jogador
enum class JogadorTipo { P1 = '1', P2 = '2', INVALID };

/// Classe que representa um jogador
class Jogador {
public:
  Jogador(JogadorTipo t) : tipo(t) {}
  Jogador() = default;

  static Jogador fromInput() {
    std::cout << "Digite o nome do jogador: ";
    Jogador j;
    std::string nome;
    std::getline(std::cin, nome);
    j.mNome = nome;
    return j;
  }

  const std::string &getNome() const { return mNome; }

  JogadorTipo tipo = JogadorTipo::INVALID;

private:
  std::string mNome;
};

class Othello {
private:
  int mTamanho;
  std::vector<std::vector<char>> mTabuleiro;

public:
  // Inicialização do membro estático mTabuleiro
  std::vector<std::vector<char>> Othello::mTabuleiro = Othello::getTabuleiro();

  Othello::Othello() : mTamanho(getTamanho()), { iniciarTabuleiro(); }

  int Othello::getTamanho() { return mTamanho; }

  std::vector<std::vector<char>> Othello::getTabuleiro() {
    return std::vector<std::vector<char>>(mTamanho,
                                          std::vector<char>(mTamanho, 'x'));
  }

  void iniciarTabuleiro() {

    int mid = mTamanho / 2;
    mTabuleiro[mid - 1][mid - 1] = static_cast<char>(JogadorTipo::P1);
    mTabuleiro[mid][mid] = static_cast<char>(JogadorTipo::P1);
    mTabuleiro[mid - 1][mid] = static_cast<char>(JogadorTipo::P2);
    mTabuleiro[mid][mid - 1] = static_cast<char>(JogadorTipo::P2);
  }

  void imprimirTabuleiro() const {
    for (const auto &row : mTabuleiro) {
      for (const auto &cell : row) {
        std::cout << cell << " ";
      }
      std::cout << std::endl;
    }
  }

  bool jogadaValida(int x, int y, JogadorTipo tipoJogador) const {
    if (x < 0 || y < 0 || x > mTamanho || y > mTamanho)
      return false;

    if (!(mTabuleiro[x][y] == 'x'))
      return false;

    char jogador = static_cast<char>(tipoJogador);
    char adversario = (tipoJogador == JogadorTipo::P1) ? '2' : '1';

    const int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    const int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};

    for (int dir = 0; dir < 8; ++dir) {
      int nx = x + dx[dir], ny = y + dy[dir];
      bool encontrouAdversario = false;

      while (nx >= 0 && nx < mTamanho && ny >= 0 && ny < mTamanho) {
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

  bool mostrarExecucaoValida() {
    for (int i = 0; i < mTamanho; i++) {
      for (int j = 0; j < mTamanho; j++) {
        if (jogadaValida(i, j)) {
          std::cout << "Eh Valida:"
                    << "[" << i << "][" << j << "]" << std::endl;
        }
      }
    }
    return 0;
  }

  bool verificarVitoria() const {
    if (!jogadaValida)
      return true;
    return false;
  }

  void jogar(Jogador *j1, Jogador *j2) {}

  bool cadastrarJogador(const Jogador &j) {}
};

int main() {
  try {
    Othello jogo;

    std::cout << "Cadastro do primeiro jogador:\n";
    Jogador j1 = Jogador::fromInput();
    j1.tipo = JogadorTipo::P1;
    jogo.cadastrarJogador(j1);

    std::cout << "Cadastro do segundo jogador:\n";
    Jogador j2 = Jogador::fromInput();
    j2.tipo = JogadorTipo::P2;
    jogo.cadastrarJogador(j2);

    // Inicia a partida
    jogo.jogar(&j1, &j2);
  } catch (const std::exception &ex) {
    std::cerr << "Erro: " << ex.what() << "\n";
  }
  return 0;
}
