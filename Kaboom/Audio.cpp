#include "Audio.h"

Audio::Audio(string path, bool loop)
{
    this->path = path;
    this->loop = loop;
    all.push_back(this);
}

void Audio::Setup()
{
    ma_engine_init(NULL, &engine);
    for (Audio * audio : all)
    {
        ma_sound_init_from_file(&engine, audio->path.c_str(), 0, NULL, NULL, &audio->sound);
        ma_sound_set_looping(&audio->sound, audio->loop ? MA_TRUE : MA_FALSE);
    }
}

void Audio::Play()
{
    ma_sound_seek_to_pcm_frame(&sound, 0);
    ma_sound_start(&sound);
}
