#include <memory>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <cstdio>
#include <fstream>

#include "Jogador.hpp"
#include "Leaderboard.hpp"
#include "doctest.h"
#include "helpers.hpp"

const char *csv = "teste.csv";
extern const char *CSV_HEADER;

TEST_CASE("addJogador") {

  Leaderboard lb(csv);

  auto j = std::make_shared<Jogador>("P1");

  lb.addJogador(j);
  // Se j foi adicionado com sucesso, proxima linha passa teste
  CHECK_THROWS(lb.addJogador(j));
}

TEST_CASE("updateJogador") {
  Leaderboard lb(csv);
  const char *nome = "P2";
  auto j = std::make_shared<Jogador>(nome);
  CHECK_THROWS(lb.updateJogador(j));

  lb.addJogador(j);
  j->setJV(5);
  lb.updateJogador(j);
  auto orig = spoofInput(nome);

  CHECK_EQ(Jogador::fromLeaderboard(lb)->getJV(), 10);
  std::cin.rdbuf(orig);
}

TEST_CASE("Ler CSV valido") {
  const char *nome = "Jonas";
  int JV = 5, Lig4 = 3, Othello = 2;
  {
    std::ofstream arq(csv);
    arq << CSV_HEADER << "\n";
    arq << nome << "," << JV << "," << Lig4 << "," << Othello << "\n";
  }
  Leaderboard lb(csv);

  // Simular input de usuário
  auto orig = spoofInput(nome);

  auto j = Jogador::fromLeaderboard(lb);
  CHECK_EQ(j->getNome(), nome);
  CHECK_EQ(j->getJV(), JV);
  CHECK_EQ(j->getLig4(), Lig4);
  CHECK_EQ(j->getOthello(), Othello);
  CHECK_EQ(j->getPontosTot(), JV + Lig4 + Othello);

  std::cin.rdbuf(orig);
}

TEST_CASE("Ler CSV Inválido") {
  const char *nome = "Jonas";
  int JV = 5, Lig4 = 3, Othello = 2;

  // Caso 1: Header Invalido
  {
    std::ofstream arq(csv);
    arq << "HEADER INVALIDO" << "\n";
    arq << nome << "," << JV << "," << Lig4 << "," << Othello << "\n";
  }
  CHECK_THROWS(Leaderboard(csv));

  // Caso 2: Header Valido, mas dados invalidos
  {
    std::ofstream arq(csv);
    arq << CSV_HEADER << "\n";

    // Menos de 4 itens na linha
    arq << nome << "," << JV << "," << Lig4 << "," << "\n";
  }
  CHECK_THROWS(Leaderboard(csv));
}

TEST_CASE("deletar arquivo teste") { CHECK_EQ(remove(csv), 0); }
