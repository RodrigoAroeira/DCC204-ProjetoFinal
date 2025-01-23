#include <iostream>

#include "Jogador.hpp"
#include "JogoBase.hpp"
#include "JogoDaVelha.hpp"
#include "Leaderboard.hpp"
#include "Lig4.hpp"
#include "Othello.hpp"

int main() {
  Leaderboard lb("Leaderboard.csv");

  std::cout << "Bem vindos! Digite quantos de vocês já jogaram antes por esse "
               "programa(0, 1, ou 2): ";

  int opt;
  std::cin >> opt;
  std::vector<std::shared_ptr<Jogador>> jogadores;
  switch (opt) {
  case 0: {
    for (int i{}; i < 2; ++i) {
      auto jogador = Jogador::fromInput();
      jogadores.push_back(jogador);
      jogadores.push_back(jogador);
    }
  } break;
  case 1: {
    auto jogador1 = Jogador::fromLeaderboard(lb);
    auto jogador2 = Jogador::fromInput();
    lb.addJogador(jogador2);
    jogadores.push_back(jogador1);
    jogadores.push_back(jogador2);
  } break;
  case 2: {
    for (int i{}; i < 2; ++i) {
      auto jogador = Jogador::fromLeaderboard(lb);
      jogadores.push_back(jogador);
    }
  } break;
  default:
    std::cerr << "Valor " << opt << " inválido. Digite 0, 1, ou 2.\n";
    exit(1);
  }

  std::cout << "Temos 3 jogos disponíveis: Jogo Da Velha, Lig4 e Othello.\n";
  bool running = true;
  while (running) {
    std::cout << "Qual jogo vocês querem jogar?\n"
              << "0 - Sair\n"
              << "1 - Jogo Da Velha\n"
              << "2 - Lig4\n"
              << "3 - Othello\n"
              << "Digite o número correspondente: ";

    std::cin >> opt;
    std::unique_ptr<JogoBase> jogo;
    switch (opt) {
    case 0:
      return 0;
    case 1:
      jogo = std::make_unique<JogoDaVelha>(lb);
      break;
    case 2:
      jogo = std::make_unique<Lig4>(lb);
      break;
    case 3:
      jogo = std::make_unique<Othello>(lb);
      break;
    default:
      std::cerr << "Opção inválida." << std::endl;
      break;
    }

    for (auto &jogador : jogadores) {
      jogo->cadastrarJogador(jogador);
    }

    jogo->jogar();

    char replay;
    std::cout << "Deseja jogar novamente? (y/n): ";
    std::cin >> replay;

    if (std::tolower(replay) == 'n') {
      running = false;
    }
  }
}
