/**
 * @file JogoDaVelha.hpp
 * @brief Declaração da classe JogoDaVelha, que implementa um jogo da velha
 * utilizando herança da classe JogoBase.
 *
 * Este arquivo contém a definição de uma classe para gerenciar o jogo da velha,
 * incluindo os métodos para cadastro de jogadores, execução do jogo e
 * manipulação do tabuleiro.
 */

#pragma once

#include <map>
#include <memory>

#include "JogoBase.hpp"

/**
 * @class JogoDaVelha
 * @brief Classe que representa o jogo da velha.
 *
 * A classe gerencia o tabuleiro do jogo, turnos dos jogadores, e verifica as
 * condições de vitória ou empate. Ela utiliza um mapa para associar os
 * jogadores aos seus respectivos símbolos ('X' ou 'O') e implementa os métodos
 * necessários para o funcionamento do jogo.
 */
class JogoDaVelha : public JogoBase {
public:
  /**
   * @brief Construtor da classe JogoDaVelha.
   * @param leaderboard Referência para a tabela de liderança onde serão
   * registrados os resultados.
   *
   * Inicializa o jogo e associa os jogadores à tabela de liderança fornecida.
   */
  JogoDaVelha(Leaderboard &leaderboard);

  /**
   * @brief Destrutor da classe JogoDaVelha.
   *
   * Libera os recursos alocados pela classe, caso necessário.
   */
  ~JogoDaVelha() override;

  /**
   * @brief Cadastra um jogador no jogo.
   * @param jogador Objeto que representa o jogador a ser cadastrado.
   * @return true se o cadastro for bem-sucedido, false caso contrário.
   *
   * Este método associa um jogador ao seu respectivo símbolo ('X' ou 'O') e
   * valida se o cadastro é possível.
   */
  bool cadastrarJogador(std::shared_ptr<Jogador>) override;

  /**
   * @brief Inicia o jogo.
   *
   * Gerencia o ciclo principal do jogo, incluindo a alternância de turnos entre
   * os jogadores, verificação de condições de vitória ou empate, e exibição do
   * tabuleiro.
   */
  void jogar() override;

  /**
   * @brief Verifica se uma jogada é válida.
   * @param x Coordenada x da jogada.
   * @param y Coordenada y da jogada.
   * @return true se a jogada for válida, false caso contrário.
   *
   * Uma jogada é considerada válida se as coordenadas estiverem dentro dos
   * limites do tabuleiro e a posição estiver livre.
   */
  bool jogadaValida(int x, int y) const override;

  /**
   * @brief Lê a jogada do jogador atual.
   *
   * Solicita ao jogador atual que informe as coordenadas da jogada. Caso a
   * jogada seja inválida, solicita novamente até que uma jogada válida seja
   * fornecida.
   */
  void lerJogada() override;

  /**
   * @brief Imprime o estado atual do tabuleiro.
   *
   * Exibe o tabuleiro no console, mostrando as posições ocupadas pelos
   * jogadores e as livres. O tabuleiro é representado em um formato amigável ao
   * usuário.
   */
  void imprimirTabuleiro() const override;

  bool verificarVitoria() const override;

private:
  /**
   * @brief Altera o jogador atual para o próximo jogador.
   *
   * Alterna entre os dois jogadores registrados no jogo. Essa função é chamada
   * após cada jogada válida.
   */
  void mudarJogadorAtual() override;

private:
  /**
   * @brief Mapeia os jogadores para os símbolos utilizados no jogo ('X' ou
   * 'O').
   *
   * Essa estrutura permite acessar rapidamente o símbolo associado a cada
   * jogador.
   */
  std::map<std::shared_ptr<Jogador>, char> mJogadorTipo;
};
