#pragma once

#include <string>

class Leaderboard;

class Jogador {
  friend class Leaderboard;

public:
  Jogador(const std::string &nome);

  static Jogador fromInput();
  static Jogador fromLeaderboard(const Leaderboard &lb);

  std::string linhaCSV() const;

  const std::string &getNome() const { return mNome; }

  int getJV() const;
  int getLig4() const;
  int getOthello() const;
  int getPontosTot() const;

  void setJV(int jv);
  void setLig4(int lig4);
  void setOthello(int othello);
  void setPontosTot(int pontosTot);

  void aumentarJV(int quant);

  void aumentarLig4(int quant);

  void aumentarOthello(int quant);

  bool operator==(const Jogador &j) const;

private:
  std::string mNome;
  int mJogoDaVelha;
  int mLig4;
  int mOthello;
  int mPontosTot;
};
