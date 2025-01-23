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
  /// Verifica se alguém venceu (4 em linha horizontal, vertical ou diagonal)
    bool verificarVitoria() const {
        // Checa horizontais
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

        // Checa verticais
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

        // Checa diagonais “↘”
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

        // Checa diagonais “↙”
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

    /// Imprime o tabuleiro no console
    void imprimirTabuleiro() const {
        std::cout << *this << "\n";
    }

    /// Sobrecarga do operador << para exibir o tabuleiro formatado
    friend std::ostream &operator<<(std::ostream &os, const JogoLig4 &j) {
        for(int row = 0; row < ROWS; ++row) {
            for(int col = 0; col < COLS; ++col) {
                os << "|" << j.mTabuleiro[row][col];
            }
            os << "|\n";
        }
        // Imprime índices das colunas
        for(int col = 0; col < COLS; ++col) {
            os << " " << col;
        }
        os << "\n";
        return os;
    }

    /// Inicia o loop principal do jogo
    void jogar() {
        // Verifica se há ao menos 2 jogadores
        if (mJogadoresPontuacao.size() < 2) {
            throw std::runtime_error("Jogadores insuficientes para começar o jogo!");
        }

        while(true) {
            imprimirTabuleiro();
            lerJogada();
            
            // Verifica se a jogada atual gerou uma vitória
            if(verificarVitoria()) {
                imprimirTabuleiro();
                std::cout << "Jogador " << mJogadorAtual->getNome()
                          << " venceu!\n";
                return;
            }
            // Verifica se o tabuleiro encheu (empate)
            if(isTabuleiroCheio()) {
                imprimirTabuleiro();
                std::cout << "Empate! O tabuleiro está cheio.\n";
                return;
            }
            // Passa a vez para o próximo jogador
            mudarJogadorAtual();
        }
    }

private:
    /// Verifica se o tabuleiro está cheio 
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
    std::map<std::shared_ptr<Jogador>, float> mJogadoresPontuacao;
    std::vector<std::vector<char>> mTabuleiro;
    std::shared_ptr<Jogador> mJogadorAtual;
};

/// Função principal para rodar o jogo
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

        // Inicia a partida
        jogo.jogar();
    } 
    catch(const std::exception &ex) {
        std::cerr << "Erro: " << ex.what() << "\n";
    }
    return 0;
}
