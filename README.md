# IDJ-ZUMBI

Este é um projeto de jogo desenvolvido para a disciplina de Introdução ao Desenvolvimento de Jogos (IDJ). O jogo utiliza a biblioteca SDL2 para renderização, áudio e entrada.

## Pré-requisitos

Antes de rodar o projeto, certifique-se de que você possui os seguintes itens instalados no seu sistema:

- **g++** (compilador C++)
- **Make** (ferramenta de build)
- **SDL2** e suas extensões:
    - SDL2
    - SDL2_image
    - SDL2_mixer
    - SDL2_ttf

### Instalando as dependências no Linux (Ubuntu/Debian)

Execute o seguinte comando no terminal para instalar as dependências:

```bash
sudo apt-get update
sudo apt-get install g++ make libsdl2-dev libsdl2-image-dev libsdl2-mixer-dev libsdl2-ttf-dev
```

### Como rodar o jogo

Siga os passos abaixo para rodar o jogo:

1. **Clone o repositório** (se ainda não tiver feito isso):
     ```bash
     git clone <URL_DO_REPOSITORIO>
     cd IDJ-ZUMBI
     ```

2. **Compile o projeto**:
     Execute o comando `make` no diretório raiz do projeto:
     ```bash
     make run
     ```

3. **Divirta-se**:
     O jogo será iniciado. Aproveite!

Se precisar limpar os arquivos gerados pela compilação, utilize:
```bash
make clean
```