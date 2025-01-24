# TabEngine

## Participantes

- André Luís Barbosa de Sá
- Igor Maia Mendes Ribeiro
- Isabel Gomes Queiroz Mendes Vieira
- Júlio César Barbosa Machado
- Matheus Antonio Barbosa Santos
- Rodrigo Oliveira Leite Aroeira de Assis

## Introdução

Este projeto tem como objetivo desenvolver um sistema de jogos de tabuleiro utilizando o paradigma de orientação a objetos em C++. O sistema é composto por três partes principais:

### Hierarquia de Classes para Jogos

- Implementação de uma classe abstrata que representa jogos de tabuleiro, com métodos básicos como validação de jogadas, verificação de condições de vitória e impressão do tabuleiro.
- Além disso, são criadas classes específicas para os seguintes jogos:
  - **Reversi (Othello)**
  - **Lig 4**
  - **Jogo da Velha**

### Cadastro de Jogadores

Um módulo dedicado ao gerenciamento de jogadores, incluindo:

- Cadastro e remoção de jogadores
- Registro de estatísticas de vitórias e derrotas por jogo
- Persistência dos dados em arquivo para uso em execuções futuras

### Execução de Partidas

Sistema para execução de partidas entre dois jogadores, que inclui:

- Leitura e validação de jogadas
- Atualização do estado do tabuleiro
- Determinação de condições de vitória
- Atualização das estatísticas dos jogadores

O sistema utiliza técnicas de programação orientada a objetos, modularidade e programação defensiva, garantindo a confiabilidade e manutenção do código.

Durante as partidas, o sistema solicitará jogadas no formato apropriado para cada jogo e informará mensagens de erro caso a entrada seja inválida.

## Estrutura do Projeto

- `headers/`: Arquivos de cabeçalho (.hpp)
- `src/`: Código-fonte principal
- `tests/`: Testes unitários com a biblioteca doctest

## Modo de Uso

### Compilação

Para compilar o projeto, execute os seguintes comandos no diretório do projeto:

```bash
mkdir build && cd build

cmake ..

make
```

### Execução

Na pasta build, execute o comando para rodar o programa:

```bash
./TabEngine
```

### Documentação

O projeto foi documentado utilizando Doxygen para detalhar a estrutura de dados, métodos e funcionalidades.

Para gerar a documentação, execute o comando no diretório do projeto:

```bash
doxygen
```
