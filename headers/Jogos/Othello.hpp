#pragma once

#include "JogoBase.hpp"

/**
 * @file Othello.hpp
 * @brief Declaração da classe Othello, derivada de JogoBase.
 */

/**
 * @class Othello
 * @brief Classe que implementa o jogo de tabuleiro Othello (ou Reversi).
 *
 * A classe Othello é responsável por implementar as regras específicas do jogo,
 * gerenciar o estado do tabuleiro e as interações dos jogadores.
 */
class Othello : public JogoBase {
private:
  /**
   * @brief Estado inicial do tabuleiro de Othello.
   *
   * Um vetor bidimensional representando o tabuleiro na configuração inicial.
   */
  static std::vector<std::vector<char>> tabuleiroInicial;

public:
  /**
   * @brief Construtor da classe Othello.
   *
   * @param leaderboard Referência ao objeto Leaderboard para gerenciamento de
   * pontuações.
   */
  Othello(Leaderboard &leaderboard);

  /**
   * @brief Destrutor da classe Othello.
   */
  ~Othello() override;

  /**
   * @brief Inicializa o tabuleiro com a configuração padrão do jogo Othello.
   *
   * Configura as peças iniciais (duas brancas e duas pretas no centro do
   * tabuleiro).
   */
  static void inicializarTabuleiro();

  /**
   * @brief Registra um jogador no jogo.
   *
   * Sobrescreve o comportamento padrão para associar um tipo de peça ('X' ou
   * 'O') ao jogador.
   *
   * @param jogador Um ponteiro compartilhado para o objeto Jogador a ser
   * registrado.
   * @return true se o jogador foi registrado com sucesso; false se já estava
   * registrado.
   */
  bool cadastrarJogador(std::shared_ptr<Jogador> jogador) override;

  /**
   * @brief Verifica se uma jogada é válida.
   *
   * Implementa as regras de Othello para determinar se uma jogada é permitida.
   *
   * @param x Coordenada X no tabuleiro.
   * @param y Coordenada Y no tabuleiro.
   * @return true se a jogada for válida; caso contrário, false.
   */
  bool jogadaValida(int x, int y) const override;

  /**
   * @brief Lê a jogada de um jogador.
   *
   * Captura a entrada do jogador atual e valida a jogada antes de executá-la.
   */
  void lerJogada() override;

  /**
   * @brief Imprime o estado atual do tabuleiro.
   *
   * Exibe o tabuleiro no terminal, indicando as posições ocupadas e
   * disponíveis.
   */
  void imprimirTabuleiro() const override;

  /**
   * @brief Verifica se há uma condição de vitória.
   *
   * Determina se o jogo terminou e calcula o vencedor com base nas condições de
   *vitoria: caso não haja jogada possível a fazer para ambos os jogadores,
   *vence o jogador com mais peças no tabuleiro. Isso incluí o caso onde um
   *jogador não possui mais peças para jogo.
   *
   * @return true se o jogo terminou; caso contrário, false.
   */
  bool verificarVitoria() const override;

  /**
   * @brief Exibe o número de execuções válidas no tabuleiro.
   *
   * Determina e retorna as possibilidades de jogadas válidas disponíveis para o
   * jogador atual.
   *
   * @return Número de execuções válidas.
   */
  int mostrarExecucaoValida() const;

  /**
   * @brief Inicia o loop principal do jogo.
   *
   * Implementa a lógica para alternar turnos, capturar jogadas e verificar
   * condições de vitória.
   */
  void jogar() override;

private:
  /**
   * @brief Alterna para o próximo jogador.
   *
   * Muda o jogador atual para o próximo na sequência.
   */
  void mudarJogadorAtual() override;

private:
  /**
   * @brief Mapa que associa cada jogador ao tipo de peça que controla.
   *
   * '1' para um jogador e '2' para o outro.
   */
  std::map<std::shared_ptr<Jogador>, char> mJogadorTipo;
};
