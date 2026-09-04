#include "../includes/engine.h"
#include "../includes/game.h"
#include "../includes/constants.h"
#include "../includes/jogador.h"
#include "../includes/menu.h" 
#include "../includes/audio.h"

extern Jogador player;
bool teclas[3] = { false, false, false };

int main(void)
{
    if(!init_game())
        return 1;

    bool rodando = true;
    bool redesenhar = true;

    ALLEGRO_EVENT_QUEUE *fila = al_create_event_queue();
    ALLEGRO_TIMER *timer = al_create_timer(1.0 / FPS);

    al_register_event_source(fila, al_get_display_event_source(display));
    al_register_event_source(fila, al_get_timer_event_source(timer));
    al_register_event_source(fila, al_get_keyboard_event_source());

    al_start_timer(timer);

    while(rodando)
    {
        ALLEGRO_EVENT ev;
        al_wait_for_event(fila, &ev);

        // PRESSIONA TECLA
        if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            //controle de audio
            switch(ev.keyboard.keycode)
            {
                case ALLEGRO_KEY_M:
                    toggle_music(); 
                    break;
                case ALLEGRO_KEY_O: 
                    alterar_volume(0.1f);  
                    break;
                case ALLEGRO_KEY_I: 
                    alterar_volume(-0.1f); 
                    break;
            }

            //controle de jogo
            switch(current_state)
            {
                case MENU:
                    if(ev.keyboard.keycode == ALLEGRO_KEY_UP || ev.keyboard.keycode == ALLEGRO_KEY_W)
                    {
                        menu_mover_cima();
                    }
                    else if(ev.keyboard.keycode == ALLEGRO_KEY_DOWN || ev.keyboard.keycode == ALLEGRO_KEY_S)
                    {
                        menu_mover_baixo();
                    }
                    else if(ev.keyboard.keycode == ALLEGRO_KEY_ENTER || ev.keyboard.keycode == ALLEGRO_KEY_SPACE)
                    {
                        if(menu_get_opcao() == 0)
                        {
                            // limpa as teclas
                            teclas[0] = false; 
                            teclas[1] = false;
                            teclas[2] = false;

                            current_state = PLAYING; 
                            
                        }
                        else
                        {
                            rodando = false; 
                        }
                    }
                    break;

                case PLAYING:
                    switch(ev.keyboard.keycode)
                    {
                        case ALLEGRO_KEY_A:
                            teclas[0] = true; //esquerda
                            break;

                        case ALLEGRO_KEY_D:
                            teclas[1] = true; //direita
                            break;

                        case ALLEGRO_KEY_SPACE:
                        case ALLEGRO_KEY_W:
                            if(player.grounded)
                            {
                                player.vy = -12;
                                player.grounded = 0; //pula 
                            }
                            break;
                        
                        case ALLEGRO_KEY_S:
                            if (player.grounded)
                            {
                                teclas[2] = true;
                                player.state = CROUCH; 
                            }
                            break;

                        case ALLEGRO_KEY_P:
                            current_state = PAUSED; // Pausa o jogo
                            player.vx = 0; 
                            pausar_musica();        // Muta a música no pause
                            break;
                    }
                    break;

                case PAUSED:
                    if(ev.keyboard.keycode == ALLEGRO_KEY_P)
                    {
                        current_state = PLAYING; // Volta a jogar   
                        retomar_musica();        // Despausa a música
                    }
                    else if(ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
                    {
                        current_state = MENU;    // Volta para o menu
                        reiniciar_musica();
                    }
                    break;

                case GAMEOVER:
                    if (ev.keyboard.keycode == ALLEGRO_KEY_SPACE)
                    {
                        // LIMPA AS TECLAS 
                        teclas[0] = false;
                        teclas[1] = false;
                        teclas[2] = false;

                        init_jogador(); 
                        camera_x = 0; 
                        extern int invencivel_timer;
                        invencivel_timer = 0; 
                        
                        current_state = PLAYING; 
                        reiniciar_musica(); 
                    }
                    else if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
                    {
                        current_state = MENU; 
                        reiniciar_musica();  
                    }
                    break;

               case VICTORY:
                if(ev.keyboard.keycode == ALLEGRO_KEY_SPACE)
                {
                    // LIMPA AS TECLAS
                    teclas[0] = false;
                    teclas[1] = false;
                    teclas[2] = false;

                    init_jogador(); 
                    current_state = PLAYING;
                    reiniciar_musica(); 
                }
                else if(ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
                {
                    current_state = MENU;
                    reiniciar_musica();
    }
    break;
            }
        }
        
        // SOLTA A TECLA
        else if(ev.type == ALLEGRO_EVENT_KEY_UP)
        {
            if(current_state == PLAYING)
            {
                switch(ev.keyboard.keycode)
                {
                    case ALLEGRO_KEY_A:
                        teclas[0] = false;
                        break;

                    case ALLEGRO_KEY_D:
                        teclas[1] = false;
                        break;

                    case ALLEGRO_KEY_S:
                        teclas[2] = false;
                        if (player.state == CROUCH)
                        {
                            player.state = IDLE; 
                        }
                        break;
                }
            }
        }

        // SISTEMA
        else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            rodando = false;
        }

        else if(ev.type == ALLEGRO_EVENT_TIMER)
        {
            // Guarda o estado antes da atualização 
            int estado_anterior = current_state; 
            
            update_game();
            
            // Se o update_game mudou o estado para GAMEOVER ou VICTORY via colisão, para a música
            if (estado_anterior == PLAYING && (current_state == GAMEOVER || current_state == VICTORY))
            {
                pausar_musica();
            }

            redesenhar = true;
        }

        // RENDERIZA
        if(redesenhar && al_is_event_queue_empty(fila))
        {
            redesenhar = false;
            draw_game();
        }
    }

    al_destroy_timer(timer);
    al_destroy_event_queue(fila);
    destroy_game();

    return 0;
}