#ifndef NOKU_MUSIC_PLAYLIST_H
#define NOKU_MUSIC_PLAYLIST_H

#include <vector>

#include "SDL2/SDL.h"
#include "Song.h"

namespace NokuMusic {
    typedef struct {
        int Position;
        Song* song;
    } PlaylistData;
    
    
    class Playlist {
        public:
            void SetName(const char* name);
            void SetSubtitle(const char* subtitle);
            void SetArt(SDL_Texture* art);
            
            static void LoadAllPlaylists();
        private:
            const char* Name;
            const char* Subtitle;
            SDL_Texture* Art;

            std::vector<PlaylistData> Songs;
            
            static std::vector<Playlist*> allPlaylists;

    };
}

#endif