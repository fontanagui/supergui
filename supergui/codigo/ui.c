#include "../includes/engine.h"
#include "../includes/ui.h"

void draw_ui(int hp)
{
    // posição e tamanho da barra de vida
    float x = 20.0;
    float y = 20.0;
    float altura_barra = 24.0;
    
    // cada 1 ponto de HP vai valer 2 pixels de largura.

    float largura_maxima = 200.0;
    float largura_atual = hp * 2.0;

    // limites
    if (largura_atual < 0) largura_atual = 0;
    if (largura_atual > largura_maxima) largura_atual = largura_maxima;

    //fundo da barra
    al_draw_filled_rectangle(
        x, y, 
        x + largura_maxima, y + altura_barra, 
        al_map_rgb(60, 60, 60)
    );

    //cor da barra de vida
    ALLEGRO_COLOR cor_vida;
    
    if (hp > 40) 
    {
        cor_vida = al_map_rgb(46, 204, 113); // Verde  se bem
    } 
    else 
    {
        cor_vida = al_map_rgb(231, 76, 60);  // Vermelho se estiver crítico
    }

    // desenha a barra de vida atual por cima do fundo 
    if (largura_atual > 0)
    {
        al_draw_filled_rectangle(
            x, y, 
            x + largura_atual, y + altura_barra, 
            cor_vida
        );
    }

    //borda
    al_draw_rectangle(
        x, y, 
        x + largura_maxima, y + altura_barra, 
        al_map_rgb(0, 0, 0), 
        2.5 // Espessura da borda
    );
}