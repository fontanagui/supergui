#ifndef AUDIO_H
#define AUDIO_H

void init_audio();
void play_music();
void destroy_audio();

void toggle_music();            
void alterar_volume(float delta); 
void pausar_musica();
void retomar_musica();
void reiniciar_musica();

#endif