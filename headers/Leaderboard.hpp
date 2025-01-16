#pragma once

#include <string>
#include <vector>

#include "Jogador.hpp"

class Leaderboard {
public:
  Leaderboard(const std::string &arquivo);
  ~Leaderboard();
  void addJogador(const Jogador &jogador);
  void updateJogador(const Jogador &jogador);

  const Jogador getJogador(const std::string &nome) const;

private:
  bool jogadorExiste(const Jogador &jogador) const;
  void read();
  void save();

private:
  std::string mArquivo;
  std::vector<Jogador> mJogadores;
};
