#ifndef JOGADOR_H
#define JOGADOR_H

#include "engine.h"
#include "constants.h"
typedef enum
{
    IDLE,
    WALK,
    JUMP,
    CROUCH
} Estado;

typedef struct
{
    float x, y;
    float vx, vy;

    int width;
    int height;
    int altura_original;
    int grounded;
    int hp;

    Estado state;

    ALLEGRO_BITMAP *sprite;

} Jogador;

extern Jogador player;


void init_jogador();

void update_jogador(int invencivel_timer, GameState current_state);

void draw_jogador(float cam_X, ALLEGRO_BITMAP *sprite_jogador, 
                  ALLEGRO_BITMAP *sprite_jogador_agachado, 
                  ALLEGRO_BITMAP *sprite_jogador_andando, 
                  ALLEGRO_BITMAP *sprite_jogador_pulo);
#endif