#include <algorithm>
#include <string.h>
#include "Album.h"

using namespace NokuMusic;

std::vector<Album*> Album::Albums = std::vector<Album*>(); 

Album::Album(const char* title) {
    //printf("> created album\n");
    //printf("> title: %s\n", (title == NULL) ? "title is null." : title);
    Title = title;
    Artist = NULL;
    Year = 0;
    Songs = std::vector<Song*>();
    Albums.push_back(this);
}

Song* Album::GetSong(int index) {
    if (index >= numOfSongs)
        return nullptr;
    
    if (index < 0)
        index = numOfSongs + index;

    if (index < 0)
        return nullptr;

    return Songs[index];
}

void Album::AddSong(Song* song) {
    Songs.push_back(song);
    numOfSongs++;
    song->SetAlbumObject(this);

    if (Artist == NULL)
        Artist = song->GetArtist();
    else if (Artist != song->GetArtist())
        Artist = "Various Artists";

    if (Year == NULL)
        Year = song->GetYear();
    
    if (albumArt.isEmpty())
        albumArt = song->GetArt();

}

bool Album::RemoveSong(Song* song) {
    return false;
}

const char* Album::GetTitle() {
    return Title;
}

const char* Album::GetArtist() {
    return Artist;
}

int Album::GetYear() {
    return Year;
}

TagLib::ByteVector Album::GetArt() {
    return albumArt;
}

void Album::SortSongs() {
    std::sort(Songs.begin(), Songs.end(), [](Song* first, Song* second){
        if (first->GetTrack() == -1)
            return false;

        if (second->GetTrack() == -1)
            return true;
        
        return (first->GetTrack() < second->GetTrack());
    });
}

void Album::PrintSongs() {
    if (numOfSongs == 0) {
        printf("> [Album]: Album \"%s\" has no songs.\n", Title);
        return;
    }

    printf("> [================[%s]================]\n", Title);
    printf("> [==============[%s | %d]=============]\n", Artist, Year);

    for (const auto& song : Songs) {
        song->PrintData();
    }
}

int Album::GetNumOfSongs() {
    return numOfSongs;
}

bool Album::Exists(const char* title) {
    for (std::vector<Album*>::iterator it = Albums.begin(); it != Albums.end(); it++) {
        if (strcmp((*it)->Title, title) == 0) {
            return true;
        }
    }
    return false;
}

Album* Album::GetAlbum(const char* title) {
    for (const auto& albumRef : Albums) {
        if (strcmp(albumRef->Title, title) == 0)
            return albumRef;
    }

    return nullptr;
}

Album* Album::GetAlbum(int index) {
    int size = Albums.size();
    if (index > size)
        return nullptr;

    if (index < 0)
        index = size + index;

    if (index < 0)
        return nullptr;

    return Albums[index];
}

int Album::GetNumOfAlbums() {
    return Albums.size();
}