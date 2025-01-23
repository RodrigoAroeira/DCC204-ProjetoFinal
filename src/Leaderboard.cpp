#include "Leaderboard.hpp"

#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <memory>
#include <sstream>
#include <stdexcept>

#include "Jogador.hpp"

const char *CSV_HEADER = "Nome,JogoDaVelha,Lig4,Othello";

Leaderboard::Leaderboard(const std::string &arquivo) : mArquivo(arquivo) {
  read();
}

Leaderboard::~Leaderboard() { save(); }

void Leaderboard::addJogador(std::shared_ptr<Jogador> jogador) {

  if (jogadorExiste(jogador))
    throw std::runtime_error("Jogador presente já presente no leaderboard.");

  mJogadores.push_back(jogador);
}

void Leaderboard::updateJogador(std::shared_ptr<Jogador> jogador) {
  if (!jogadorExiste(jogador)) {
    throw std::runtime_error("Jogador não está presente no leaderboard");
  }

  for (auto &j : mJogadores) {
    if (j->mNome == jogador->mNome) {
      j->aumentarJV(jogador->getJV());
      j->aumentarLig4(jogador->getLig4());
      j->aumentarOthello(jogador->getLig4());
      return;
    }
  }
}

const std::shared_ptr<Jogador>
Leaderboard::getJogador(const std::string &nome) const {
  for (auto &jogador : mJogadores) {
    if (jogador->mNome == nome) {
      return jogador;
    }
  }
  std::cout << "Jogador não encontrado. Criando novo jogador." << std::endl;
  return std::make_shared<Jogador>(nome);
}

void Leaderboard::save() {
  std::ofstream arquivo(mArquivo);
  if (!arquivo.is_open()) {
    std::stringstream ss;
    ss << "Impossível abrir arquivo " << std::quoted(mArquivo);
    throw std::runtime_error(ss.str());
  }

  arquivo << CSV_HEADER << "\n";
  std::sort(mJogadores.begin(), mJogadores.end(),
            [](std::shared_ptr<Jogador> a, std::shared_ptr<Jogador> b) {
              return a->mPontosTot >= b->mPontosTot;
            });

  for (const auto &jogador : mJogadores) {
    arquivo << jogador->linhaCSV() << '\n';
  }
}

bool Leaderboard::jogadorExiste(std::shared_ptr<Jogador> jogador) const {
  for (const auto &other : mJogadores) {
    if (other->mNome == jogador->mNome) {
      return true;
    }
  }
  return false;
}

void Leaderboard::read() {
  // Ter certeza que quando o programa terminar, os nomes antigos vão
  // permanecer.
  //
  std::ifstream f(mArquivo);
  if (!f.is_open()) {
    std::cerr << "Arquivo " << std::quoted(mArquivo, '`') << " não encontrado."
              << std::endl;

    return;
  }

  std::string line;
  std::getline(f, line);
  if (line != CSV_HEADER)
    throw std::runtime_error(
        "Arquivo de leaderboard segue estrutura diferente do esperado.");

  while (std::getline(f, line)) {
    std::istringstream iss(line);
    std::string token;
    std::vector<std::string> tokens;

    while (std::getline(iss, token, ',')) {
      tokens.push_back(token);
    }

    if (tokens.size() != 4) {
      throw std::runtime_error("Linha do arquivo CSV inválida");
    }

    auto j = std::make_shared<Jogador>(tokens[0]);
    j->mJogoDaVelha = std::stoi(tokens[1]);
    j->mLig4 = std::stoi(tokens[2]);
    j->mOthello = std::stoi(tokens[3]);
    j->mPontosTot = j->mJogoDaVelha + j->mLig4 + j->mOthello;
    mJogadores.push_back(j);
  }
}
