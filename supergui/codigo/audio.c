#include "../includes/engine.h"
#include "../includes/audio.h"

// Variável estática: só este arquivo consegue enxergar ou mexer na música
static ALLEGRO_AUDIO_STREAM *audio_fundo = NULL;

void init_audio()
{
    
    if (!al_install_audio()) 
    {
        printf("ERRO: Nao foi possivel inicializar o sistema de audio.\n");
        return;
    }

    // 2. Inicializa os codecs (para o jogo entender arquivos .ogg ou .wav)
    if (!al_init_acodec_addon()) 
    {
        return;
    }

    
    
    if (!al_reserve_samples(1)) 
    {
        printf("ERRO: Nao foi possivel reservar canais de audio.\n");
        return;
    }
}

void play_music()
{
    audio_fundo = al_load_audio_stream("images/audio.ogg", 4, 2048);
    
    if (!audio_fundo) 
    {
        printf("ERRO: Nao foi possivel carregar images/audio.ogg\n");
        return;
    }

    // Configura a música para tocar em LOOP infinito
    al_set_audio_stream_playmode(audio_fundo, ALLEGRO_PLAYMODE_LOOP);

    // Conecta a música ao mixer padrão da Allegro (faz o som sair nas caixas de som)
    al_attach_audio_stream_to_mixer(audio_fundo, al_get_default_mixer());
}

void destroy_audio()
{
    // Se a música estiver carregada, limpa ela da memória
    if (audio_fundo) 
    {
        al_destroy_audio_stream(audio_fundo);
        audio_fundo = NULL;
    }
}
void toggle_music()
{
    if (audio_fundo)
    {
        // Descobre se a música está tocando no momento (true ou false)
        bool tocando = al_get_audio_stream_playing(audio_fundo);
        
        // Inverte o estado atual
        al_set_audio_stream_playing(audio_fundo, !tocando);
    }
}

void alterar_volume(float delta)
{
    if (audio_fundo)
    {
        // Pega o volume atual da música (vai de 0.0 a 1.0)
        float volume_atual = al_get_audio_stream_gain(audio_fundo);
        
        // Aplica a mudança (ex: volume_atual + 0.1)
        float novo_volume = volume_atual + delta;
        
        // Trava o volume para não sair dos limites da Allegro (0.0 a 1.0)
        if (novo_volume < 0.0f) novo_volume = 0.0f;
        if (novo_volume > 1.0f) novo_volume = 1.0f;
        
        // Aplica o novo volume na música
        al_set_audio_stream_gain(audio_fundo, novo_volume);
    }
}

void pausar_musica()
{
    if (audio_fundo) {
        al_set_audio_stream_playing(audio_fundo, false);
    }
}

void retomar_musica()
{
    if (audio_fundo) {
        al_set_audio_stream_playing(audio_fundo, true);
    }
}

void reiniciar_musica()
{
    if (audio_fundo)
    {
        // Rebobina o áudio para o início (0.0 segundos)
        al_seek_audio_stream_secs(audio_fundo, 0.0);
        // Garante que ela vai começar a tocar
        al_set_audio_stream_playing(audio_fundo, true);
    }
}