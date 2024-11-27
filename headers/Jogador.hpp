#pragma once

#include <string>

class Jogador {
public:
  Jogador(const std::string &mNome, const std::string &mApelido);

private:
  std::string mNome, mApelido;
  int mPontos;
};
