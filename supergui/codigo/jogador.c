#include "../includes/jogador.h"
#include "../includes/constants.h"
extern Jogador player;
extern bool teclas[3]; // A (0), D (1), S (2)

Jogador player;




void init_jogador()
{
    player.x = 100;
    player.y = 100;

    player.vx = 0;
    player.vy = 0;

    player.width = 40;
    player.height = 60;
    player.altura_original = 60;

    player.grounded = 0;

    player.hp = 100;

    player.state = IDLE;
}




void update_jogador(int invencivel_timer, GameState current_state)
{
   
    
    
    // knockback
    if (invencivel_timer <= 10)
    {
        player.vx = 0; // Reseta a velocidade 

        if(teclas[0]) // Tecla A (Esquerda)
        {
            player.vx = -5;
        }
        else if(teclas[1]) // Tecla D (Direita)
        {
            player.vx = 5;
        }

        // andar ou parado
        if (player.grounded && player.state != CROUCH)
        {
            if (teclas[0] || teclas[1]) player.state = WALK;
            else player.state = IDLE;
        }
    }
    

    //agachamento
    if (player.state == CROUCH)
    {
        if (player.height == player.altura_original)
        {
            player.height = player.altura_original / 2; // Corta colisão pela metade
            player.y += player.height;                  // Mantém os pés no chão
        }
        player.vx *= 0.5; // Reduz a velocidade pela metade se andar agachado
    }
    else 
    {
        // mudou de estado
        if (player.height < player.altura_original)
        {
            player.y -= (player.altura_original - player.height); // Devolve o Y para o topo
            player.height = player.altura_original;               // Restaura a altura normal
        }
    }

    // gravidade 
    player.vy += 0.5; // gravidade 

    player.x += player.vx; // Aplica deslocamento horizontal
    player.y += player.vy; // Aplica deslocamento vertical

    // chao 
    // buraco
    if (player.x > 1600 && (player.x + player.width) < 1800)
    {
        // caiu no buraco, então não tem chão
        player.grounded = 0;
    }
    else
    {
        // Fora do buraco, 
        if (player.y + player.height >= 600)
        {
            player.y = 600 - player.height; // Fixa perfeitamente os pés na linha do chão
            player.vy = 0;                  // Para a aceleração da gravidade
            player.grounded = 1;            // pode pular novamente
        }
        else
        {
            player.grounded = 0; // Está caindo ou pulando fora do buraco
        }
    }

    // game over se cair no buraco 
    if (player.y > 700) 
    {
        player.hp = 0;
        current_state = GAMEOVER;
    }

    //limites do mapa
    if(player.x < 0)
    {
        player.x = 0;
    }

    // Se o jogador alcançar a linha final do mapa, aciona a vitória
    if(current_state == PLAYING && player.x >= LARGURA_MAPA - (player.width + 100))
    {
        current_state = VICTORY; 
    }
}

void draw_jogador(float cam_X, ALLEGRO_BITMAP *sprite_jogador, 
                  ALLEGRO_BITMAP *sprite_jogador_agachado, 
                  ALLEGRO_BITMAP *sprite_jogador_andando, 
                  ALLEGRO_BITMAP *sprite_jogador_pulo)
{
 
    // flip
    int flip = 0; //direita

    // esquerda
    if (teclas[0]) 
    {
        // Define a flag de rotação horizontal
        flip = ALLEGRO_FLIP_HORIZONTAL;
    }
  


    
    float offset_agachado = -50.0; 


    

    // agachado
    if (player.state == CROUCH && sprite_jogador_agachado) 
    {
        
        al_draw_bitmap(
            sprite_jogador_agachado, 
            player.x - cam_X, 
            player.y + offset_agachado, 
            flip 
        );
    }
    // andando
    else if (player.grounded && (teclas[0] || teclas[1]) && sprite_jogador_andando)
    {
        //
        al_draw_bitmap(
            sprite_jogador_andando, 
            player.x - cam_X, 
            player.y, 
            flip 
        );
    }
    // pulando
    else if (player.grounded == 0 && sprite_jogador_pulo) 
    {
        
        al_draw_bitmap(
            sprite_jogador_pulo, 
            player.x - cam_X, 
            player.y, 
            flip //
        );
    }
    // parado
    else if (sprite_jogador)
    {
        
        al_draw_bitmap(
            sprite_jogador, 
            player.x - cam_X, 
            player.y, 
            flip //
        );
    }
    // retangulo
    else 
    {
        al_draw_filled_rectangle(
            player.x - cam_X, 
            player.y, 
            player.x + player.width - cam_X, 
            player.y + player.height, 
            al_map_rgb(0, 0, 255) // Azul
        );
    }
}