#include "../includes/menu.h"
#include "../includes/constants.h"
#include "../includes/engine.h"

// 0 = Iniciar Jogo, 1 = Sair
int opcao_selecionada = 0; 

// Controla um efeito simples de fade/piscar para o texto de instrução
float timer_pisca = 0;
int mostrar_texto_instrucao = 1;

void update_menu()
{
    timer_pisca += 1.0 / FPS;
    if(timer_pisca >= 0.5) // Inverte a cada meio segundo
    {
        mostrar_texto_instrucao = !mostrar_texto_instrucao;
        timer_pisca = 0;
    }
}

void draw_menu(ALLEGRO_FONT *fonte)
{
    
    ALLEGRO_COLOR cor_iniciar = al_map_rgb(150, 150, 150);
    ALLEGRO_COLOR cor_sair = al_map_rgb(150, 150, 150);
    
    
    if (opcao_selecionada == 0)
        cor_iniciar = al_map_rgb(255, 255, 255);
    else
        cor_sair = al_map_rgb(255, 255, 255);

    // TITULO
    al_draw_text(fonte, al_map_rgb(255, 215, 0), SCREEN_W / 2, 150, ALLEGRO_ALIGN_CENTER, "SUPERGUI ADVENTURE");

    // MENU
    al_draw_text(fonte, cor_iniciar, SCREEN_W / 2, 300, ALLEGRO_ALIGN_CENTER, "JOGAR");
    al_draw_text(fonte, cor_sair, SCREEN_W / 2, 350, ALLEGRO_ALIGN_CENTER, "SAIR");

    // seta
    float seta_y = (opcao_selecionada == 0) ? 300 : 350;
    al_draw_filled_triangle(
        (SCREEN_W / 2) - 80, seta_y + 2,
        (SCREEN_W / 2) - 80, seta_y + 12,
        (SCREEN_W / 2) - 70, seta_y + 7,
        al_map_rgb(255, 215, 0)
    );

    // instrrucao
    if(mostrar_texto_instrucao)
    {
        al_draw_text(fonte, al_map_rgb(100, 100, 100), SCREEN_W / 2, 500, ALLEGRO_ALIGN_CENTER, 
            "Use as SETAS para navegar e ENTER para selecionar");
    }
}

// Funções auxiliares para mover
void menu_mover_cima()
{
    opcao_selecionada = 0;
}

void menu_mover_baixo()
{
    opcao_selecionada = 1;
}

int menu_get_opcao()
{
    return opcao_selecionada;
}

void draw_tela_gameover(ALLEGRO_FONT *fonte)
{
    al_draw_text(fonte, al_map_rgb(255, 0, 0), SCREEN_W / 2, 250, ALLEGRO_ALIGN_CENTER, "GAME OVER");
    al_draw_text(fonte, al_map_rgb(255, 255, 255), SCREEN_W / 2, 350, ALLEGRO_ALIGN_CENTER, "Pressione ESPAÇO para Tentar Novamente");
}