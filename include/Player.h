#ifndef NOKU_MUSIC_PLAYER_H
#define NOKU_MUSIC_PLAYER_H

#include "SDL2/SDL_mixer.h"

#include "Song.h"

#define MAX_VOLUME 128
#define DEFAULT_FORMAT AUDIO_F32LSB
#define DEFAULT_CHANNELS 2
#define DEFAULT_FREQUENCY 48000
#define DEFAULT_CHUNK_SIZE 2048

namespace NokuMusic {
    class Player {
        public:
            static bool Init();
            static void CleanUp();

            static void Play(Song* song);

        private:
            Player();
            static Player* player;
            static void LoadConfig();

            bool Initialized = false;
            int Volume = 128;
            int Channels = DEFAULT_CHANNELS;
            Uint16 Frequency = DEFAULT_FREQUENCY;
            int chunkSize = DEFAULT_CHUNK_SIZE;
    };
}

#endif
