#ifndef MENU_H
#define MENU_H
#include <allegro5/allegro_font.h>
void update_menu();
void draw_menu(ALLEGRO_FONT *fonte);
void draw_tela_gameover(ALLEGRO_FONT *fonte);
void menu_mover_cima();
void menu_mover_baixo();
int menu_get_opcao();
#endif  