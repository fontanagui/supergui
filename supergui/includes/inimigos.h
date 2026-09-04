#ifndef INIMIGOS_H
#define INIMIGOS_H
#include "engine.h"
#include "constants.h"

typedef struct
{
    float x, y;

    int width;
    int height;

    int damage;

    int moving;

    float speed;
    float limite_min;
    float limite_max;


    ALLEGRO_COLOR cor;

} obstaculo;


extern obstaculo lista_obstaculos[QTD_OBSTACULOS];


void init_obstaculos();
void update_obstaculos();
void draw_obstaculos(float cam_X,  ALLEGRO_BITMAP *sprite_espinho,  
                    ALLEGRO_BITMAP *sprite_inimigo, 
                    ALLEGRO_BITMAP *sprite_aranha, 
                    ALLEGRO_BITMAP *sprite_final);

#endif