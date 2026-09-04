#ifndef CONSTANTS_H
#define CONSTANTS_H

#define SCREEN_W 1280
#define SCREEN_H 720
#define LARGURA_MAPA 4900 // O tamanho total do cenário (5 telas de largura)
#define FPS 60.0
#define QTD_OBSTACULOS 14


// Estados do Jogo
typedef enum
{
    MENU,
    PLAYING,
    PAUSED,
    GAMEOVER,
    VICTORY
} GameState;
#endif