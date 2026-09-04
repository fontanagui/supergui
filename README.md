# SUPERGUI ADVENTURE

Jogo de plataforma 2D em **C** utilizando a biblioteca **Allegro 5**, com sistema de câmera lateral, inimigos com padrões de movimento distintos, colisão, HUD de vida e trilha sonora.

## 🎮 Sobre o jogo

O jogador controla um personagem que precisa atravessar um mapa cheio de obstáculos (espinhos), inimigos terrestres (robôs) e inimigos voadores (aranhas), até alcançar o objetivo final (uma moeda) para vencer a fase. O jogo possui menu inicial, pausa, tela de game over e tela de vitória.

## ✨ Funcionalidades

- **Máquina de estados** do jogo: `MENU`, `PLAYING`, `PAUSED`, `GAMEOVER`, `VICTORY`
- **Movimentação do jogador**: andar, pular, agachar (com ajuste de hitbox), gravidade e knockback ao levar dano
- **Câmera lateral** que acompanha o jogador e é travada nos limites do mapa
- **Sistema de colisão** por AABB (bounding box) reutilizável (`colisao.c`)
- **Inimigos variados**:
  - Espinhos fixos
  - Robôs que patrulham em faixas horizontais delimitadas
  - Aranhas que se movem verticalmente
  - Item final (moeda) que aciona a vitória
- **Buraco no mapa** que causa queda e game over
- **Timer de invencibilidade** após tomar dano
- **HUD de vida** com barra colorida (verde/vermelha conforme o HP)
- **Áudio**: música de fundo em loop, controle de volume, pausar/retomar/reiniciar
- **Menu navegável** com seleção de "Jogar" / "Sair" e texto piscante de instrução

## 🎹 Controles

| Tecla | Ação |
|---|---|
| `A` / `D` | Mover para esquerda / direita |
| `W` ou `Espaço` | Pular |
| `S` | Agachar |
| `P` | Pausar / despausar o jogo |
| `Enter` / `Espaço` | Confirmar no menu / reiniciar após game over ou vitória |
| `Esc` | Voltar ao menu (na pausa, game over ou vitória) |
| `M` | Ligar/desligar a música |
| `O` | Aumentar volume |
| `I` | Diminuir volume |

## 📁 Estrutura do projeto

O código faz referência a headers em `../includes/` e a assets em `images/`, então a estrutura esperada do repositório é:

```
supergui-adventure/
├── codigo/
│   ├── main.c          # Loop principal, eventos e input
│   ├── game.c           # Inicialização, update e draw geral do jogo
│   ├── jogador.c         # Lógica e desenho do jogador
│   ├── inimigos.c        # Obstáculos, inimigos e a moeda final
│   ├── colisao.c         # Função de detecção de colisão (AABB)
│   ├── menu.c            # Menu inicial e tela de game over
│   ├── ui.c              # HUD (barra de vida)
│   └── audio.c           # Sistema de áudio (música, volume, play/pause)
├── includes/
│   ├── engine.h
│   ├── constants.h
│   ├── game.h
│   ├── jogador.h
│   ├── inimigos.h
│   ├── colisao.h
│   ├── menu.h
│   ├── ui.h
│   └── audio.h
└── images/
    ├── fundo.png
    ├── player_idle.png
    ├── player_crouch.png
    ├── player_walk.png
    ├── player_jump.png
    ├── espinho.png
    ├── inimigo.png
    ├── aranha.png
    ├── final.png
    └── audio.ogg
```

> **Nota:** os arquivos `.h` da pasta `includes/` não foram enviados nesta análise — os nomes acima foram inferidos a partir dos `#include` presentes nos `.c`. Ajuste conforme sua estrutura real.

## 🔧 Requisitos

- Compilador C (GCC ou similar)
- [Allegro 5](https://liballeg.org/) instalado, com os seguintes addons:
  - `allegro_image`
  - `allegro_font`
  - `allegro_primitives`
  - `allegro_audio`
  - `allegro_acodec`

### Instalando o Allegro 5 (Ubuntu/Debian)

```bash
sudo apt update
sudo apt install liballegro5-dev liballegro-image5-dev liballegro-font5-dev \
                  liballegro-primitives5-dev liballegro-audio5-dev liballegro-acodec5-dev
```

## 🛠️ Compilando

A partir da pasta `codigo/`:

```bash
gcc *.c -o supergui_adventure \
    $(pkg-config --cflags --libs allegro-5 allegro_image-5 allegro_font-5 \
      allegro_primitives-5 allegro_audio-5 allegro_acodec-5)
```

## ▶️ Executando

O executável precisa ser rodado a partir da raiz do projeto (onde a pasta `images/` está localizada), já que os assets são carregados com caminhos relativos como `images/fundo.png`:

```bash
./codigo/supergui_adventure
```

## 🧩 Detalhes técnicos

- **`camera_x`**: controla o deslocamento da câmera, travado entre `0` e `LARGURA_MAPA - SCREEN_W`.
- **Obstáculos** (`inimigos.c`): usam o campo `moving` para diferenciar comportamento:
  - `0` → espinho (parado)
  - `1` → robô (patrulha horizontal com limites por índice)
  - `2` → aranha (movimento vertical entre altura mínima e máxima)
  - `3` → moeda final (aciona `VICTORY`)
- **Buraco no mapa**: região fixa entre `x = 1600` e `x = 1800`; se o jogador cair nela, `player.y > 700` aciona game over.
- **Agachar**: reduz a altura da hitbox pela metade e ajusta a posição `y` para manter os pés no chão.

## 📌 Possíveis melhorias futuras

- Externalizar posições e parâmetros dos obstáculos para um arquivo de configuração/fase
- Adicionar mais fases além do mapa único atual
- Sistema de pontuação
- Efeitos sonoros (SFX) além da música de fundo
