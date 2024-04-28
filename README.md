# Sistema de Gerenciamento de Artistas

Este é um sistema simples de gerenciamento de artistas, onde você pode adicionar, remover, editar, buscar e listar informações sobre artistas e seus álbuns.

## Funcionalidades

- **Inserção Ordenada de Artistas:** Permite adicionar novos artistas de forma ordenada por nome.
- **Remoção de Artistas:** Remove um artista existente da lista.
- **Edição de Artistas:** Permite editar informações de um artista já existente.
- **Busca Binária por Artistas:** Busca um artista na lista utilizando busca binária.
- **Busca Sequencial por Álbum:** Busca um álbum específico na lista de artistas.
- **Listagem de Artistas:** Lista todos os artistas cadastrados no sistema.

## Como Compilar e Executar

Certifique-se de ter um compilador de C instalado em seu sistema. Para compilar os arquivos fonte, utilize o seguinte comando:
```
gcc main.c artistas.c -o gerenciador
```
Para executar o programa compilado, utilize:
```
./gerenciador
```

## Arquivos

- **main.c:** Contém a função `main()` onde o programa é iniciado e o menu principal é exibido.
- **artistas.c:** Contém as implementações das funções relacionadas à manipulação de artistas.
- **artistas.h:** Arquivo de cabeçalho contendo os protótipos das funções e as definições de estruturas utilizadas.

## Estrutura de Dados

O sistema utiliza as seguintes estruturas de dados:

- `Artista`: Estrutura que armazena informações sobre um artista, incluindo nome, gênero musical, local de nascimento e álbuns.
- `ListaArtistas`: Estrutura que mantém uma lista de artistas, juntamente com o número total de artistas.

## Arquivo de Dados

O programa utiliza o arquivo `artistas.txt` para armazenar os dados dos artistas. Cada registro de artista é armazenado com o seguinte formato:
```
Nome do Artista
Gênero Musical
Local de Nascimento
Nome dos Álbuns
==========
```

## Contribuindo
Se encontrar algum problema ou tiver sugestões de melhorias, sinta-se à vontade para abrir uma issue ou enviar um pull request.

