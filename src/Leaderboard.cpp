#include "Leaderboard.hpp"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>

#include "Jogador.hpp"

const char *CSV_HEADER = "Nome,JogoDaVelha,Lig4,Othello";

// std::quoted existe apenas a partir de c++14
std::string quoted(const std::string &str, char c = '"') { return c + str + c; }

Leaderboard::Leaderboard(const std::string &arquivo) : mArquivo(arquivo) {
  read();
}
Leaderboard::~Leaderboard() { save(); }

void Leaderboard::addJogador(const Jogador &jogador) {

  if (jogadorExiste(jogador))
    throw std::runtime_error("Jogador presente já presente no leaderboard.");

  mJogadores.push_back(jogador);
}

void Leaderboard::updateJogador(const Jogador &jogador) {
  if (!jogadorExiste(jogador)) {
    throw std::runtime_error("Jogador não está presente no leaderboard");
  }

  for (auto &j : mJogadores) {
    if (j.mNome == jogador.mNome) {
      j.aumentarJV(jogador.getJV());
      j.aumentarLig4(jogador.getLig4());
      j.aumentarOthello(jogador.getLig4());
      return;
    }
  }
}

const Jogador Leaderboard::getJogador(const std::string &nome) const {
  for (auto &jogador : mJogadores) {
    if (jogador.mNome == nome) {
      return jogador;
    }
  }
  std::cout << "Jogador não encontrado. Retornando novo jogador." << std::endl;
  return Jogador(nome);
}

void Leaderboard::save() {
  std::ofstream arquivo(mArquivo);
  if (!arquivo.is_open()) {
    std::string err = "Impossível abrir arquivo " + quoted(mArquivo);
    throw std::runtime_error(err);
  }

  arquivo << CSV_HEADER << "\n";
  std::sort(mJogadores.begin(), mJogadores.end(),
            [](const Jogador &a, const Jogador &b) {
              return a.mPontosTot >= b.mPontosTot;
            });

  for (const auto &jogador : mJogadores) {
    arquivo << jogador.linhaCSV() << '\n';
  }
}

bool Leaderboard::jogadorExiste(const Jogador &jogador) const {
  return std::find(mJogadores.begin(), mJogadores.end(), jogador) !=
         mJogadores.end();
}

void Leaderboard::read() {
  // Ter certeza que quando o programa terminar, os nomes antigos vão
  // permanecer.
  //
  std::ifstream f(mArquivo);
  if (!f.is_open()) {
    std::cerr << "Arquivo " << quoted(mArquivo, '`')
              << " não encontrado. Criando um novo." << std::endl;

    if (!std::ofstream(mArquivo).is_open())
      throw std::runtime_error(
          "Impossível ler ou criar arquivo de leaderboard.");

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

    Jogador j(tokens[0]);
    j.mJogoDaVelha = std::stoi(tokens[1]);
    j.mLig4 = std::stoi(tokens[2]);
    j.mOthello = std::stoi(tokens[3]);
    j.mPontosTot = j.mJogoDaVelha + j.mLig4 + j.mOthello;
    mJogadores.push_back(j);
  }
}
