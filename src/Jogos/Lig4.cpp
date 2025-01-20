#include "Lig4.hpp"
#include <iostream>
#include <vector>
#include <map>
#include <memory>
#include <limits>
#include <stdexcept>
#include <string>

/// Define o tipo de jogador 
enum class JogadorTipo {
    P1 = 'o',
    P2 = 'x',
    INVALID
};

/// Classe que representa um jogador
class Jogador {
public:
    Jogador(JogadorTipo t) : tipo(t) {}
    Jogador() = default;

    static Jogador fromInput() {
        std::cout << "Digite o nome do jogador: ";
        Jogador j;
        std::string nome;
        std::getline(std::cin, nome);
        j.mNome = nome;
        return j;
    }

    const std::string &getNome() const {
        return mNome;
    }

    JogadorTipo tipo = JogadorTipo::INVALID;

private:
    std::string mNome;
};

/// Classe que representa o jogo Lig4
class JogoLig4 {
public:
    static const int ROWS = 6;  // Número de linhas do tabuleiro
    static const int COLS = 7;  // Número de colunas do tabuleiro

    JogoLig4()
        : mTabuleiro(ROWS, std::vector<char>(COLS, ' ')),
          mJogadorAtual(nullptr) {}

    /// Cadastra um jogador no map 
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

    /// Alterna para o próximo jogador
    void mudarJogadorAtual() {
        // Tenta encontrar o jogador atual no map
        auto it = mJogadoresPontuacao.find(mJogadorAtual);
        if(it != mJogadoresPontuacao.end()) {
            // Avança o iterador para o próximo
            auto nextIt = it;
            ++nextIt;
            // Se chegou ao fim, volta para o primeiro
            if(nextIt == mJogadoresPontuacao.end()) {
                nextIt = mJogadoresPontuacao.begin();
            }
            mJogadorAtual = nextIt->first;
        }
    }

    /// Verifica se a jogada é válida 
    bool jogadaValida(int col) const {
        if (col < 0 || col >= COLS) {
            return false;
        }
        // Se a linha do topo (0) já estiver ocupada, coluna está cheia
        return (mTabuleiro[0][col] == ' ');
    }

    /// Lê a jogada (coluna), verifica validade e “solta” a peça na linha apropriada
    void lerJogada() {
        int col;
        while (true) {
            std::cout << "Jogador " << mJogadorAtual->getNome() << " ("
                      << static_cast<char>(mJogadorAtual->tipo)
                      << "), escolha uma coluna (0-" << COLS - 1 << "): ";
            std::cin >> col;

            // Trata possíveis erros de stream 
            if(!std::cin) {
                std::cout << "Entrada inválida! Tente novamente.\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }

            if (jogadaValida(col)) {
                // Acha a linha mais baixa disponível nessa coluna
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
