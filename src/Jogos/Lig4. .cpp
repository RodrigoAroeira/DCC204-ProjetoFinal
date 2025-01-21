/**
 * @file Lig4.cpp
 * @brief Implementação do jogo Connect Four (Lig4) com documentação detalhada.
 * 
 * Este arquivo contém a implementação do jogo "Connect Four", também conhecido como Lig4.
 * O jogo é implementado através das classes: `Jogador`, `JogoLig4` e outras definições auxiliares.
 */

#include "Lig4.hpp"
#include <iostream>
#include <vector>
#include <map>
#include <memory>
#include <limits>
#include <stdexcept>
#include <string>

/**
 * @enum JogadorTipo
 * @brief Enumeração que define o tipo de jogador no jogo.
 * 
 * Define os tipos de jogadores com base nos símbolos usados no tabuleiro.
 * - P1 representa o jogador 1 (simbolizado por 'o')
 * - P2 representa o jogador 2 (simbolizado por 'x')
 * - INVALID é utilizado para indicar um jogador inválido.
 */
enum class JogadorTipo {
    P1 = 'o', /**< Jogador 1 */
    P2 = 'x', /**< Jogador 2 */
    INVALID  /**< Jogador inválido */
};

/**
 * @class Jogador
 * @brief Classe que representa um jogador no jogo.
 * 
 * A classe `Jogador` é responsável por armazenar as informações do jogador, como nome e tipo.
 */
class Jogador {
public:
    /**
     * @brief Construtor da classe Jogador.
     * 
     * Inicializa o jogador com um tipo específico (P1 ou P2).
     * @param t Tipo do jogador (P1 ou P2).
     */
    Jogador(JogadorTipo t) : tipo(t) {}

    /**
     * @brief Construtor padrão da classe Jogador.
     */
    Jogador() = default;

    /**
     * @brief Cria um jogador a partir da entrada do usuário.
     * 
     * Lê o nome do jogador e retorna um objeto Jogador com o nome fornecido.
     * @return Jogador O objeto Jogador criado com o nome informado.
     */
    static Jogador fromInput() {
        std::cout << "Digite o nome do jogador: ";
        Jogador j;
        std::string nome;
        std::getline(std::cin, nome);
        j.mNome = nome;
        return j;
    }

    /**
     * @brief Obtém o nome do jogador.
     * @return O nome do jogador.
     */
    const std::string &getNome() const {
        return mNome;
    }

    JogadorTipo tipo = JogadorTipo::INVALID; /**< Tipo do jogador (P1 ou P2). */

private:
    std::string mNome; /**< Nome do jogador. */
};

/**
 * @class JogoLig4
 * @brief Classe que representa o jogo Lig4 (Connect Four).
 * 
 * A classe `JogoLig4` contém a lógica do jogo, como o tabuleiro, os jogadores e as regras de vitória.
 */
class JogoLig4 {
public:
    static const int ROWS = 6; /**< Número de linhas do tabuleiro. */
    static const int COLS = 7; /**< Número de colunas do tabuleiro. */

    /**
     * @brief Construtor da classe JogoLig4.
     * 
     * Inicializa o tabuleiro e define o jogador atual como `nullptr`.
     */
    JogoLig4()
        : mTabuleiro(ROWS, std::vector<char>(COLS, ' ')),
          mJogadorAtual(nullptr) {}

    /**
     * @brief Cadastra um jogador no jogo.
     * 
     * Verifica se o nome do jogador já foi cadastrado e, caso não, o adiciona ao mapa de jogadores.
     * @param jogador O jogador a ser cadastrado.
     * @return true se o jogador foi cadastrado com sucesso, false se o nome já existir.
     */
    bool cadastrarJogador(const Jogador &jogador) {
        auto ptr = std::make_shared<Jogador>(jogador);

        // Verifica se já existe jogador com o mesmo nome 
        for(const auto &par : mJogadoresPontuacao) {
            if(par.first->getNome() == jogador.getNome()) {
                return false;
            }
        }
        // Insere jogador
        mJogadoresPontuacao[ptr] = 0;

        // Se for o primeiro jogador cadastrado, já define como atual
        if (!mJogadorAtual) {
            mJogadorAtual = ptr;
        }
        return true;
    }

    /**
     * @brief Alterna a vez entre os jogadores.
     * 
     * Caso o jogador atual seja o primeiro, muda para o segundo, e vice-versa.
     */
    void mudarJogadorAtual() {
        auto it = mJogadoresPontuacao.find(mJogadorAtual);
        if(it != mJogadoresPontuacao.end()) {
            auto nextIt = it;
            ++nextIt;
            if(nextIt == mJogadoresPontuacao.end()) {
                nextIt = mJogadoresPontuacao.begin();
            }
            mJogadorAtual = nextIt->first;
        }
    }

    /**
     * @brief Verifica se a jogada na coluna é válida.
     * 
     * Verifica se a coluna está dentro dos limites e se não está cheia.
     * @param col A coluna onde a jogada será realizada.
     * @return true se a jogada for válida, false caso contrário.
     */
    bool jogadaValida(int col) const {
        if (col < 0 || col >= COLS) {
            return false;
        }
        return (mTabuleiro[0][col] == ' ');
    }

    /**
     * @brief Lê a jogada do jogador e atualiza o tabuleiro.
     * 
     * Solicita a coluna onde o jogador deseja jogar, valida a jogada e atualiza o tabuleiro.
     */
    void lerJogada() {
        int col;
        while (true) {
            std::cout << "Jogador " << mJogadorAtual->getNome() << " ("
                      << static_cast<char>(mJogadorAtual->tipo)
                      << "), escolha uma coluna (0-" << COLS - 1 << "): ";
            std::cin >> col;

            if(!std::cin) {
                std::cout << "Entrada inválida! Tente novamente.\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }

            if (jogadaValida(col)) {
                for(int row = ROWS - 1; row >= 0; --row) {
                    if(mTabuleiro[row][col] == ' ') {
                        mTabuleiro[row][col] = static_cast<char>(mJogadorAtual->tipo);
                        break;
                    }
                }
                break;
            } else {
                std::cout << "Jogada inválida! Coluna cheia ou fora do limite.\n";
            }
        }
    }

    /**
     * @brief Verifica se algum jogador venceu o jogo.
     * 
     * Verifica as linhas, colunas e diagonais para ver se existe uma sequência de 4 peças do mesmo jogador.
     * @return true se alguém venceu, false caso contrário.
     */
    bool verificarVitoria() const {
        for(int row = 0; row < ROWS; ++row) {
            for(int col = 0; col < COLS - 3; ++col) {
                char c = mTabuleiro[row][col];
                if(c != ' ' &&
                   c == mTabuleiro[row][col+1] &&
                   c == mTabuleiro[row][col+2] &&
                   c == mTabuleiro[row][col+3]) {
                    return true;
                }
            }
        }
        for(int col = 0; col < COLS; ++col) {
            for(int row = 0; row < ROWS - 3; ++row) {
                char c = mTabuleiro[row][col];
                if(c != ' ' &&
                   c == mTabuleiro[row+1][col] &&
                   c == mTabuleiro[row+2][col] &&
                   c == mTabuleiro[row+3][col]) {
                    return true;
                }
            }
        }
        for(int row = 0; row < ROWS - 3; ++row) {
            for(int col = 0; col < COLS - 3; ++col) {
                char c = mTabuleiro[row][col];
                if(c != ' ' &&
                   c == mTabuleiro[row+1][col+1] &&
                   c == mTabuleiro[row+2][col+2] &&
                   c == mTabuleiro[row+3][col+3]) {
                    return true;
                }
            }
        }
        for(int row = 0; row < ROWS - 3; ++row) {
            for(int col = 3; col < COLS; ++col) {
                char c = mTabuleiro[row][col];
                if(c != ' ' &&
                   c == mTabuleiro[row+1][col-1] &&
                   c == mTabuleiro[row+2][col-2] &&
                   c == mTabuleiro[row+3][col-3]) {
                    return true;
                }
            }
        }
        return false;
    }

    /**
     * @brief Imprime o estado atual do tabuleiro.
     */
    void imprimirTabuleiro() const {
        std::cout << *this << "\n";
    }

    /**
     * @brief Sobrecarga do operador de inserção para imprimir o tabuleiro de forma formatada.
     * @param os O fluxo de saída.
     * @param j O objeto JogoLig4 a ser impresso.
     * @return O fluxo de saída com o tabuleiro impresso.
     */
    friend std::ostream &operator<<(std::ostream &os, const JogoLig4 &j) {
        for(int row = 0; row < ROWS; ++row) {
            for(int col = 0; col < COLS; ++col) {
                os << "|" << j.mTabuleiro[row][col];
            }
            os << "|\n";
        }
        for(int col = 0; col < COLS; ++col) {
            os << " " << col;
        }
        os << "\n";
        return os;
    }

    /**
     * @brief Inicia o loop principal do jogo.
     * 
     * Gerencia o fluxo de jogo, alternando entre jogadores e verificando as condições de vitória ou empate.
     */
    void jogar() {
        if (mJogadoresPontuacao.size() < 2) {
            throw std::runtime_error("Jogadores insuficientes para começar o jogo!");
        }

        while(true) {
            imprimirTabuleiro();
            lerJogada();
            
            if(verificarVitoria()) {
                imprimirTabuleiro();
                std::cout << "Jogador " << mJogadorAtual->getNome()
                          << " venceu!\n";
                return;
            }
            if(isTabuleiroCheio()) {
                imprimirTabuleiro();
                std::cout << "Empate! O tabuleiro está cheio.\n";
                return;
            }
            mudarJogadorAtual();
        }
    }

private:
    /**
     * @brief Verifica se o tabuleiro está cheio.
     * 
     * Verifica se todas as células do tabuleiro foram preenchidas.
     * @return true se o tabuleiro estiver cheio, false caso contrário.
     */
    bool isTabuleiroCheio() const {
        for(int row = 0; row < ROWS; ++row) {
            for(int col = 0; col < COLS; ++col) {
                if(mTabuleiro[row][col] == ' ') {
                    return false;
                }
            }
        }
        return true;
    }

private:
    std::map<std::shared_ptr<Jogador>, float> mJogadoresPontuacao; /**< Mapa de jogadores e suas pontuações. */
    std::vector<std::vector<char>> mTabuleiro; /**< Tabuleiro do jogo. */
    std::shared_ptr<Jogador> mJogadorAtual; /**< Jogador atual da vez. */
};

/**
 * @brief Função principal para rodar o jogo.
 */
int main() {
    try {
        JogoLig4 jogo;

        std::cout << "Cadastro do primeiro jogador:\n";
        Jogador j1 = Jogador::fromInput();
        j1.tipo = JogadorTipo::P1;
        jogo.cadastrarJogador(j1);

        std::cout << "Cadastro do segundo jogador:\n";
        Jogador j2 = Jogador::fromInput();
        j2.tipo = JogadorTipo::P2;
        jogo.cadastrarJogador(j2);

        jogo.jogar();
    } 
    catch(const std::exception &ex) {
        std::cerr << "Erro: " << ex.what() << "\n";
    }
    return 0;
}
