#include "../includes/inimigos.h"
#include "../includes/engine.h"
#include "../includes/constants.h"
#include <math.h>



obstaculo lista_obstaculos[QTD_OBSTACULOS];


void init_obstaculos()
{
   //loop para inicializar os obstáculos (espinhos)
    float x_espinhos[5] = {400, 1350, 1900, 3200, 4500};
    
    for(int i = 0; i < 5; i++)
    {
        lista_obstaculos[i].x = x_espinhos[i];
        lista_obstaculos[i].y = 600 - 40; 
        lista_obstaculos[i].moving = 0;
        lista_obstaculos[i].speed = 0;
        lista_obstaculos[i].damage = 15;
        lista_obstaculos[i].width = 40;
        lista_obstaculos[i].height = 40;
        lista_obstaculos[i].cor = al_map_rgb(255, 0, 0);
    }

    //loop para inicializar os inimigos (robôs)
    float x_robos[3] = {800, 2400, 4100};
    float v_robos[3] = {5, -6, 4}; 
    
    for(int i = 0; i < 3; i++)
    {
        int idx = 5 + i;
        
        lista_obstaculos[idx].x = x_robos[i];
        lista_obstaculos[idx].y = 600 - 45; 
        lista_obstaculos[idx].moving = 1;
        lista_obstaculos[idx].speed = v_robos[i];
        lista_obstaculos[idx].damage = (i == 2) ? 25 : 20; 
        lista_obstaculos[idx].width = 40;
        lista_obstaculos[idx].height = 40;
        lista_obstaculos[idx].cor = al_map_rgb(255, 0, 0);
    }

    //loop para inicializar os inimigos (aranhas)
    float x_aranhas[5] = {1100, 2150, 2800, 3600, 4650}; 
    float y_aranhas[5] = {300,  250,  200,  200,  250};    
    float v_aranhas[5] = {7,    8,    3,    7,    10};          
    
   
    for(int i = 0; i < 5; i++)
    {
        int idx = 8 + i; 
        
        lista_obstaculos[idx].x = x_aranhas[i];
        lista_obstaculos[idx].y = y_aranhas[i];
        lista_obstaculos[idx].moving = 2;
        lista_obstaculos[idx].speed = v_aranhas[i];
        lista_obstaculos[idx].damage = (i == 4) ? 20 : 15;
        lista_obstaculos[idx].width = 40;
        lista_obstaculos[idx].height = 50; 
        lista_obstaculos[idx].cor = al_map_rgb(255, 0, 0);
    }
    
    // Inicializa a moeda final (moving == 3)
    lista_obstaculos[13].x = 4800;          // final do mapa
    lista_obstaculos[13].y = 600 - 80;      // Flutuando um pouco acima do chão
    lista_obstaculos[13].width = 40;
    lista_obstaculos[13].height = 40;
    lista_obstaculos[13].moving = 3;        
    lista_obstaculos[13].speed = 0;
    lista_obstaculos[13].damage = 0;         
    lista_obstaculos[13].cor = al_map_rgb(255, 215, 0); // amarelo ouro
}
void draw_obstaculos(float cam_X,  ALLEGRO_BITMAP *sprite_espinho,  ALLEGRO_BITMAP *sprite_inimigo, ALLEGRO_BITMAP *sprite_aranha, ALLEGRO_BITMAP *sprite_final)
{
  

    for(int i = 0; i < QTD_OBSTACULOS; i++)
    {
        //robo
        if (lista_obstaculos[i].moving == 1 && sprite_inimigo) 
        {
            // flip imagem
            int flip = 0; // direita

            // esquerda
            if (lista_obstaculos[i].speed < 0) 
            {
                flip = ALLEGRO_FLIP_HORIZONTAL; // Espelha a imagem
            }

            // Desenha com o flip 
            al_draw_bitmap(
                sprite_inimigo, 
                lista_obstaculos[i].x - cam_X, 
                lista_obstaculos[i].y, 
                flip 
            );
        }
        
        // aranha
        else if (lista_obstaculos[i].moving == 2 && sprite_aranha) 
        {
            al_draw_bitmap(
                sprite_aranha, 
                lista_obstaculos[i].x - cam_X, 
                lista_obstaculos[i].y, 
                0 
            );
        }
        
        // espinho
        else if (lista_obstaculos[i].moving == 0 && sprite_espinho) 
        {
            al_draw_bitmap(
                sprite_espinho, 
                lista_obstaculos[i].x - cam_X, 
                lista_obstaculos[i].y, 
                0 
            );
        }

      
        // final (moeda)
        else if (lista_obstaculos[i].moving == 3 && sprite_final) 
        {
            al_draw_bitmap(
                sprite_final, 
                lista_obstaculos[i].x - cam_X, 
                lista_obstaculos[i].y, 
                0 
            );
        }
        
        // fallback
        else 
        {
            al_draw_filled_rectangle(
                lista_obstaculos[i].x - cam_X,
                lista_obstaculos[i].y,
                lista_obstaculos[i].x + lista_obstaculos[i].width - cam_X,
                lista_obstaculos[i].y + lista_obstaculos[i].height,
                lista_obstaculos[i].cor
            );
        }
    }
}

void update_obstaculos()
{
    for(int i = 0; i < QTD_OBSTACULOS; i++)
    {
        // robo
        if (lista_obstaculos[i].moving == 1)
        {
            // Move no eixo X
            lista_obstaculos[i].x += lista_obstaculos[i].speed;

            // limites
            float limite_esquerda = 0;
            float limite_direita = 5200;

            // setor
            if (i == 5) // R1
            {
                limite_esquerda = 450;
                limite_direita  = 1200; 
            }
            else if (i == 6) // R2
            {
                limite_esquerda = 1900; 
                limite_direita  = 2900;
            }
            else if (i == 7) // R3
            {
                limite_esquerda = 3400;
                limite_direita  = 4800;
            }

            
            // vira a direcao do robo se ele atingir os limites
            if (lista_obstaculos[i].x < limite_esquerda && lista_obstaculos[i].speed < 0) 
            {
                lista_obstaculos[i].speed *= -1;
            }
            if (lista_obstaculos[i].x > limite_direita && lista_obstaculos[i].speed > 0) 
            {
                lista_obstaculos[i].speed *= -1;
            }
        }

        // aranha
        else if (lista_obstaculos[i].moving == 2)
        {
            lista_obstaculos[i].y += lista_obstaculos[i].speed;

            // Se a aranha descer demais, sobe
            if (lista_obstaculos[i].y > 500 && lista_obstaculos[i].speed > 0)
            {
                lista_obstaculos[i].speed *= -1;
            }
            // Se a aranha subir demais, desce
            if (lista_obstaculos[i].y < 100 && lista_obstaculos[i].speed < 0)
            {
                lista_obstaculos[i].speed *= -1;
            }
        }
    }
}