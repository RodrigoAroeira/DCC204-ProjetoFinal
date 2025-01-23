#pragma once

#include <memory>
#include <string>
#include <vector>

#include "Jogador.hpp"

/**
 * @class Leaderboard
 * @brief Classe que representa e gerencia o placar dos jogos
 *
 * Esta classe gerencia um placar de jogadores, permitindo adicionar,
 * atualizar e recuperar jogadores, bem como salvar e ler os dados de um arquivo
 * CSV.
 */
class Leaderboard {
public:
  /**
   * @brief Construtor da classe Leaderboard.
   *
   * @param arquivo Nome do arquivo CSV onde os dados dos jogadores serão
   */
  Leaderboard(const std::string &arquivo);

  /**
   * @brief Destrutor da classe Leaderboard.
   *
   * Salva o leaderboard no arquivo CSV antes de destruir o objeto.
   */
  ~Leaderboard();

  /**
   * @brief Adiciona um jogador não existente no leaderboard.
   *
   * @param jogador Ponteiro para o objeto Jogador a ser adicionado.
   *
   * Lança uma exceção caso o jogador já esteja presente no leaderboard.
   */
  void addJogador(const std::shared_ptr<Jogador> jogador);

  /**
   * @brief Atualiza a pontuação de um jogador existente no leaderboard.
   *
   * @param jogador Ponteiro para o objeto Jogador a ser atualizado
   *
   * Lança uma exceção caso o jogador não esteja presente no leaderboard.
   */
  void updateJogador(const std::shared_ptr<Jogador> jogador);

  /**
   * @brief Retorna um jogador pelo nome
   *
   * @param nome Nome do jogador a ser retornado
   */
  const std::shared_ptr<Jogador> getJogador(const std::string &nome) const;

private:
  /**
   * @brief Verifica se um jogador já está presente no leaderboard.
   *
   * @param jogador Ponteiro para o objeto Jogador a ser verificado
   */
  bool jogadorExiste(const std::shared_ptr<Jogador> jogador) const;

  /**
   * @brief Tenta ler os dados do arquivo CSV e atualiza o objeto leaderboard.
   */
  void read();

  /**
   * @brief Salva os dados do leaderboard no arquivo CSV.
   */
  void save();

private:
  std::string mArquivo;
  std::vector<std::shared_ptr<Jogador>> mJogadores;
};
