#ifndef GAME_H
#define GAME_H

#include "engine.h"
#include "constants.h"

// Dentro do seu arquivo .h (ex: game.h):
extern float camera_x; // O "extern" diz: essa variável existe e está em outro lugar, apenas use-a.




extern ALLEGRO_DISPLAY *display;
extern GameState current_state;
int init_game();

void update_game();

void draw_game();
void update_camera();
void destroy_game();
void checar_perigos();
#endif