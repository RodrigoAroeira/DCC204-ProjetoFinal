/**
 * @brief Arquivo com funções helper que podem ser reutilizadas em vários
 * arquivos
 *
 */

#include <streambuf>

/**
 * @brief Limpa a tela do terminal.
 *
 * Utiliza diferentes comandos dependendo do sistema operacional (Windows ou
 * Unix-like).
 */
void limparTela();

/**
 * @brief Simula input de usuário
 *
 * @param txt Texto com o conteúdo a ser simulado
 *
 * Retorna o ponteiro do buffer original do std::cin. Preferivelmente deve ser
 * restaurado dentro do mesmo escopo
 */
[[nodiscard]] std::streambuf *spoofInput(const std::string &txt);
