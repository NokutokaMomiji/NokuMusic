#ifndef NOKU_MUSIC_ALBUM_H
#define NOKU_MUSIC_ALBUM_H

#define TAGLIB_STATIC

#include <vector>

#include "taglib/tbytevector.h"

#include "Song.h"

namespace NokuMusic {
    class Album {
		public:
			Album(const char* title);

			Song* GetSong(int index);
			void AddSong(Song* song);
			bool RemoveSong(Song* song);

			void FindArtIfNone();

			const char* GetTitle();
			const char* GetArtist();
			int GetYear();
			TagLib::ByteVector GetArt();

			void SortSongs();
			void PrintSongs();
			int GetNumOfSongs();

			static bool Exists(const char* title);
			static Album* GetAlbum(const char* title);
			static Album* GetAlbum(int index);
			static int GetNumOfAlbums();
			
		private:
			const char* Title;
			const char* Artist;
			int Year;
			TagLib::ByteVector albumArt;

			int numOfSongs = 0;
			int Duration = 0;
			std::vector<Song*> Songs;
			static std::vector<Album*> Albums;
    };
}

#endif
