#ifndef NOKU_MUSIC_SONG_H
#define NOKU_MUSIC_SONG_H

#define TAGLIB_STATIC

#include "SDL2/SDL_mixer.h"
#include "taglib/tag.h"
#include "taglib/fileref.h"
#include "taglib/tstring.h"
#include "taglib/tbytevector.h"

#include "Utilities/Sprite.h"

namespace NokuMusic {
    class Album;

    class Song {
        public:
            Song(const char* path, bool load = false);
			
            bool Load();
			bool LoadMetadata();
            bool LoadArt(); 
			bool IsLoaded();

            const char* GetPath();
            Mix_Music* GetMusic();
            TagLib::ByteVector GetArt();
            const char* GetTitle();
            const char* GetArtist();
            const char* GetAlbum();
            const char* GetGenre();
            int GetTrack();
            int GetDurationMS();
            const char* GetTrackNumber();
            const char* GetDuration();
            int GetYear();

            void SetAlbumObject(NokuMusic::Album* album);

            static Song* GetSong(int index);

			void PrintData();
        private:
            const char* Path = NULL;

            const char* Title = NULL;
            const char* Artist = NULL;
            const char* Album = NULL;
            const char* Genre = NULL;
			int Track = -1;
            int Duration = 0;
            int Bitrate = -1;
            int Year = 0;
            int Disc = 0;

            Mix_Music* Music = NULL;
            NokuMusic::Album* album;
            TagLib::ByteVector Art;

            static std::vector<Song*> Songs;
    };
}

#endif
