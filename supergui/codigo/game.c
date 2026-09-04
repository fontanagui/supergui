#include "../includes/game.h"
#include "../includes/constants.h"
#include "../includes/jogador.h"
#include "../includes/menu.h"
#include "../includes/inimigos.h"
#include "../includes/engine.h"
#include  "../includes/colisao.h"
#include "../includes/ui.h"
#include "../includes/audio.h"

// Ponteiros para as texturas 
ALLEGRO_BITMAP *sprite_fundo = NULL;
ALLEGRO_BITMAP *sprite_jogador = NULL;
ALLEGRO_BITMAP *sprite_jogador_agachado = NULL;
ALLEGRO_BITMAP *sprite_espinho = NULL;
ALLEGRO_BITMAP *sprite_inimigo = NULL;
ALLEGRO_BITMAP *sprite_jogador_andando = NULL;
ALLEGRO_BITMAP *sprite_final = NULL;
ALLEGRO_BITMAP *sprite_jogador_pulo = NULL;
ALLEGRO_BITMAP *sprite_aranha = NULL;
ALLEGRO_DISPLAY *display = NULL;
ALLEGRO_FONT *fonte_jogo = NULL; // Ponteiro para a fonte 

// Começa no menu
GameState current_state = MENU; 

float camera_x = 0; // Posição da câmera no eixo X
int invencivel_timer = 0; // Contagem de frames em que o jogador fica imune após levar dano

int init_game()
{
    if(!al_init())
        return 0;

    al_install_keyboard();
    al_init_primitives_addon();
    al_init_font_addon(); // Inicializa o addon de fontes
    if (!al_init_image_addon())
        return 0;

    // Carrega as texturas
    sprite_fundo = al_load_bitmap("images/fundo.png");
    sprite_jogador = al_load_bitmap("images/player_idle.png");
    sprite_jogador_agachado = al_load_bitmap("images/player_crouch.png");
    sprite_espinho = al_load_bitmap("images/espinho.png");
    sprite_inimigo = al_load_bitmap("images/inimigo.png");
    sprite_jogador_andando = al_load_bitmap("images/player_walk.png");
    sprite_final = al_load_bitmap("images/final.png");
    sprite_jogador_pulo = al_load_bitmap("images/player_jump.png");                        
    sprite_fundo = al_load_bitmap("images/fundo.png");
    sprite_aranha = al_load_bitmap("images/aranha.png");


    display = al_create_display(SCREEN_W, SCREEN_H); 
    if(!display)
        return 0;

    // Cria a fonte padrão 
    fonte_jogo = al_create_builtin_font();
    if(!fonte_jogo)
        return 0;

    init_jogador(); // Inicializa o jogador
    init_obstaculos(); // Inicializa os obstáculos
    init_audio();
    play_music(); // Já começa a tocar a trilha sonora

    return 1;
}

void update_camera()
{
    // Centraliza a câmera nojogador
    camera_x = player.x - (SCREEN_W / 2);

    // Trava a câmera na esquerda do mapa
    if(camera_x < 0)
    {
        camera_x = 0;
    }

    // Trava a câmera na direita do mapa
    if(camera_x > LARGURA_MAPA - SCREEN_W)
    {
        camera_x = LARGURA_MAPA - SCREEN_W;
    }
}


void checar_perigos()
{
    
    // Como o chão é em 600, se o Y do jogador passar de 680, ele caiu 
  
    if (player.y > 680)
    {
        player.hp = 0;
        current_state = GAMEOVER;
        return; // Sai da função imediatamente
    }

    // Se o jogador estiver invencível (após levar dano de monstro/espinho)
    if (invencivel_timer > 0)
    {
        invencivel_timer--;
        
        if (invencivel_timer < 10 && player.vx < 0)
        {
            player.vx = 0; 
        }
        return; // Sai da função, ignorando novas colisões 
    }

    // Varre todos os obstáculos da fase 
    for (int i = 0; i < QTD_OBSTACULOS; i++)
    {
        if (check_collision(player.x, player.y, (float)player.width, (float)player.height,
                            lista_obstaculos[i].x, lista_obstaculos[i].y, 
                            (float)lista_obstaculos[i].width, (float)lista_obstaculos[i].height)) 
        {
            // moeda - final
            if (lista_obstaculos[i].moving == 3)
            {
                current_state = VICTORY; 
                break; 
            }
            // obstaculos normais
            else
            {
                player.hp -= lista_obstaculos[i].damage;  
                
                invencivel_timer = 20; // 20 frames de imunidade

                // knockback 
                player.vx = -10; // empurrar para trás
                player.vy = -6;  // pra cima
                player.grounded = 0; 

                if (player.hp <= 0)
                {
                    player.hp = 0;
                    current_state = GAMEOVER; 
                }
                
                break; 
            }
        }
    }
}

void update_game()
{
    switch(current_state)
    {
        case MENU:
            update_menu(); // Atualiza o menu 
            break;

        case PLAYING:
            update_jogador( invencivel_timer, current_state); // Atualiza o jogador
            update_obstaculos(); // Atualiza os obstáculos
            checar_perigos(); // Verifica colisões e aplica danos
            update_camera();  // Atualiza a posição da câmera
            break;

        case PAUSED:
            break;

        case GAMEOVER:
            break;

        case VICTORY:
            break;
    }
}


void draw_game()
{
    al_clear_to_color(al_map_rgb(0,0,0)); // Limpa a tela com preto
    
    switch(current_state)    // desenha a tela de acordo com o estado atual do jogo
    {
        case MENU:
            draw_menu(fonte_jogo); // desenha o menu 
            break;

        case PLAYING:
            if (sprite_fundo) 
            {
                //fundo
                al_draw_bitmap(sprite_fundo, 0 - camera_x, 0, 0);
                al_draw_bitmap(sprite_fundo, 1700 - camera_x, 0, 0);

                al_draw_bitmap(sprite_fundo, 3000 - camera_x, 0, 0);
                
                al_draw_bitmap(sprite_fundo, 4700 - camera_x, 0, 0); 
            }
            else 
            {
                al_clear_to_color(al_map_rgb(100, 149, 237)); 
            }

            //buraco
            float altura_do_chao = 600.0; 
            float fim_da_tela_y = 1000.0;  

            //retangulo marrom no buraco
            al_draw_filled_rectangle(
                1600 - camera_x, altura_do_chao, 
                1800 - camera_x, fim_da_tela_y, 
                al_map_rgb(101, 67, 33) 
            );

        
            // Grama 
            al_draw_filled_rectangle(0 - camera_x, altura_do_chao, 1600 - camera_x, fim_da_tela_y, al_map_rgb(34, 139, 34));
            al_draw_filled_rectangle(1800 - camera_x, altura_do_chao, 5200 - camera_x, fim_da_tela_y, al_map_rgb(34, 139, 34));


            draw_jogador(camera_x, sprite_jogador, sprite_jogador_agachado, sprite_jogador_andando, sprite_jogador_pulo); // Desenha o jogador
            draw_obstaculos(camera_x, sprite_espinho, sprite_inimigo, sprite_aranha, sprite_final); // Desenha os obstáculos
            draw_ui(player.hp); // Desenha a barra de vida por cima de tudo
    break;

        case PAUSED:
            // tela de pausa
            al_draw_text(fonte_jogo, al_map_rgb(255, 255, 0), SCREEN_W / 2, SCREEN_H / 2, ALLEGRO_ALIGN_CENTER, "PAUSADO");
            al_draw_text(fonte_jogo, al_map_rgb(255, 255, 255), SCREEN_W / 2, (SCREEN_H / 2) + 50, ALLEGRO_ALIGN_CENTER, "Pressione P para continuar ou ESC para sair");
            break;

        case GAMEOVER:
            // tela de game over
            draw_tela_gameover(fonte_jogo);
            break;

        case VICTORY:
            // tela de vitória
            al_draw_text(fonte_jogo, al_map_rgb(0, 255, 0), SCREEN_W / 2, SCREEN_H / 2, ALLEGRO_ALIGN_CENTER, "VOCE VENCEU!");
            al_draw_text(fonte_jogo, al_map_rgb(255, 255, 255), SCREEN_W / 2, (SCREEN_H / 2) + 50, ALLEGRO_ALIGN_CENTER, "Pressione ESPACO para reiniciar");
            break;
    }
    
    al_flip_display(); // Atualiza a tela com o que foi desenhado
}

void destroy_game()
{
    if(fonte_jogo)
        al_destroy_font(fonte_jogo); // Limpa a memória da fonte
        
    al_destroy_display(display);
    destroy_audio(); // Limpa a memória dos recursos de áudio
}