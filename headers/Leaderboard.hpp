#pragma once

#include <memory>
#include <string>
#include <vector>

#include "Jogador.hpp"

class Leaderboard {
public:
  Leaderboard(const std::string &arquivo);
  ~Leaderboard();
  void addJogador(const std::shared_ptr<Jogador> jogador);
  void updateJogador(const std::shared_ptr<Jogador> jogador);

  const std::shared_ptr<Jogador> getJogador(const std::string &nome) const;

private:
  bool jogadorExiste(const std::shared_ptr<Jogador> jogador) const;
  void read();
  void save();

private:
  std::string mArquivo;
  std::vector<std::shared_ptr<Jogador>> mJogadores;
};
