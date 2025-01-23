#pragma once

#include <memory>
#include <string>

class Leaderboard;

/**
 * @class Jogador
 * @brief Representa um jogador no jogo.
 */
class Jogador {
  friend class Leaderboard;

public:
  /**
   * @brief Constrói um objeto Jogador com o nome dado.
   * @param nome O nome do jogador.
   */
  Jogador(const std::string &nome);

  /**
   * @brief Cria um objeto Jogador a partir da entrada do usuário.
   * @return Um ponteiro compartilhado para o objeto Jogador criado.
   */
  static std::shared_ptr<Jogador> fromInput();

  /**
   * @brief Cria um objeto Jogador a partir de um leaderboard.
   * @param lb O leaderboard para criar o Jogador.
   * @return Um ponteiro compartilhado para o objeto Jogador criado.
   */
  static std::shared_ptr<Jogador> fromLeaderboard(const Leaderboard &lb);

  /**
   * @brief Retorna os dados do jogador em formato CSV.
   * @return Uma string contendo os dados do jogador em formato CSV.
   */
  std::string linhaCSV() const;

  /**
   * @brief Obtém o nome do jogador.
   * @return O nome do jogador.
   */
  const std::string &getNome() const { return mNome; }

  /**
   * @brief Obtém o número de jogos de Jogo Da Velha ganhos pelo jogador.
   * @return O número de jogos de Jogo Da Velha ganhos.
   */
  int getJV() const;

  /**
   * @brief Obtém o número de jogos de Lig4 ganhos pelo jogador.
   * @return O número de jogos de Lig4 ganhos.
   */
  int getLig4() const;

  /**
   * @brief Obtém o número de jogos de Othello ganhos pelo jogador.
   * @return O número de jogos de Othello ganhos.
   */
  int getOthello() const;

  /**
   * @brief Obtém o total de pontos do jogador.
   * @return O total de pontos do jogador.
   */
  int getPontosTot() const;

  /**
   * @brief Define o número de jogos de Jogo Da Velha ganhos pelo jogador.
   * @param jv O número de jogos de Jogo Da Velha ganhos.
   */
  void setJV(int jv);

  /**
   * @brief Define o número de jogos de Lig4 ganhos pelo jogador.
   * @param lig4 O número de jogos de Lig4 ganhos.
   */
  void setLig4(int lig4);

  /**
   * @brief Define o número de jogos de Othello ganhos pelo jogador.
   * @param othello O número de jogos de Othello ganhos.
   */
  void setOthello(int othello);

  /**
   * @brief Define o total de pontos do jogador.
   * @param pontosTot O total de pontos do jogador.
   */
  void setPontosTot(int pontosTot);

  /**
   * @brief Aumenta o número de jogos de Jogo Da Velha ganhos pelo jogador.
   * @param quant A quantidade a aumentar.
   */
  void aumentarJV(int quant);

  /**
   * @brief Aumenta o número de jogos de Lig4 ganhos pelo jogador.
   * @param quant A quantidade a aumentar.
   */
  void aumentarLig4(int quant);

  /**
   * @brief Aumenta o número de jogos de Othello ganhos pelo jogador.
   * @param quant A quantidade a aumentar.
   */
  void aumentarOthello(int quant);

  /**
   * @brief Compara dois objetos Jogador para igualdade.
   * @param j O outro objeto Jogador para comparar.
   * @return Verdadeiro se os objetos forem iguais, falso caso contrário.
   */
  bool operator==(const Jogador &j) const;

  /**
   * @brief Compara dois objetos Jogador para desigualdade.
   * @param j O outro objeto Jogador para comparar.
   * @return Verdadeiro se os objetos não forem iguais, falso caso contrário.
   */
  bool operator!=(const Jogador &j) const;

private:
  std::string mNome; ///< O nome do jogador.
  int mJogoDaVelha;  ///< O número de jogos de Jogo Da Velha ganhos.
  int mLig4;         ///< O número de jogos de Lig4 ganhos.
  int mOthello;      ///< O número de jogos de Othello ganhos.
  int mPontosTot;    ///< O total de pontos do jogador.
};
