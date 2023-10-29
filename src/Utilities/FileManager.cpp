#include <filesystem>
#include <iostream>
#include <stdlib.h>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include "Utilities/FileManager.h"
#include "Song.h"
#include "Album.h"
#include "Utilities/Utilities.h"

using namespace NokuMusic;

FileManager* FileManager::Manager = nullptr;

FileManager::FileManager() {
    if (Manager == nullptr)
		Manager = this;
}

bool FileManager::Exists(const char* path) {
    return std::filesystem::exists(path);
}

bool CheckIfValidExtension(std::filesystem::path path) {
    if (path == ".mp3")
        return true;
    if (path == ".flac")
        return true;
    if (path == ".ogg")
        return true;
    if (path == ".wav")
        return true;
    if (path == ".wave")
        return true;
    if (path == ".m4a")
        return true;

    return false;
}

bool FileManager::ScanPath(const char* path) {
    if (!Exists(path))
        return false;

    printf("> [FileManager]: Scanning path \"%s\"\n", path);

    for (const auto& dirEntry : std::filesystem::recursive_directory_iterator(path)) {
        //std::cout << "Test: " << Utilities::WCharToChar(dirEntry.path().wstring()) << std::endl;

        if (dirEntry.is_regular_file() && dirEntry.path().has_extension() && CheckIfValidExtension(dirEntry.path().extension())) {
            Song* song = new Song(Utilities::WCharToChar(dirEntry.path().wstring()));

            if (song->GetPath() == NULL) {
                delete song;
                continue;
            }

            Album* songAlbum = Album::GetAlbum(song->GetAlbum());

            if (songAlbum == nullptr)
                songAlbum = new Album(song->GetAlbum());

            songAlbum->AddSong(song);
            songAlbum->SortSongs();
            songAlbum->FindArtIfNone();
        }
    }

    return true;
}

const char* FileManager::PathFilename(const char* path) {
    std::filesystem::path tempPath(path);

    return tempPath.filename().string().c_str();
}

const char* FileManager::PathDirectory(const char* path) {
    std::filesystem::path tempPath(path);

    return tempPath.parent_path().filename().string().c_str();
}

static bool CheckIfValidImage(std::filesystem::path path) {
    if (path == ".png")
        return true;
    if (path == ".jpg")
        return true;
    if (path == ".jpeg")
        return true;
    if (path == ".bmp")
        return true;
    if (path == ".raw")
        return true;
    
    return false;
}

static bool HasAlbumCoverName(std::filesystem::path path) {
    //printf("> in has album cover name: %s\n", path.string().c_str());
    const char* cPath = path.string().c_str();
    if (Utilities::BeginsWith(cPath, "album"))
        return true;
    if (Utilities::BeginsWith(cPath, "cover"))
        return true;
    if (Utilities::BeginsWith(cPath, "thumb"))
        return true;
    if (Utilities::BeginsWith(cPath, "folder"))
        return true;
    return false;
}

static TagLib::ByteVector CoverDataToVector(const char* path) {
    //printf("> Testing %s.\n", path);

    SDL_RWops* imageFile = SDL_RWFromFile(path, "rb");

    if (imageFile == NULL) {
        printf("> [FileManager]: Failed to load file \"%s\".", path);
        printf("> [FileManager]: Error: %s\n", SDL_GetError());
        return TagLib::ByteVector();
    }

    Sint64 fileSize = SDL_RWsize(imageFile);
    if (fileSize < 0) {
        printf("> [FileManager]: Cannot read file size from data.\n");
        printf("> [FileManager]: Error: %s\n", SDL_GetError());
        return TagLib::ByteVector();
    }

    void* imageData = malloc(fileSize);

    SDL_RWread(imageFile, imageData, 1, fileSize);

    TagLib::ByteVector byteVector(static_cast<const char*>(imageData), static_cast<unsigned int>(fileSize));

    SDL_RWclose(imageFile);
    free(imageData);

    return byteVector;
} 

TagLib::ByteVector FileManager::ScanForAlbumCover(const char* path) {
    std::filesystem::path tempPath(path);
    std::filesystem::path previousPath(tempPath.parent_path().parent_path());
    const char* finalPath = NULL;

    for (const auto& dirEntry : std::filesystem::directory_iterator(tempPath.parent_path())) {
        if (dirEntry.is_regular_file() && dirEntry.path().has_extension() && CheckIfValidImage(dirEntry.path().extension())) {
            //printf("> checking file: %s\n", dirEntry.path().string().c_str());
            if (HasAlbumCoverName(dirEntry.path().filename()))
                return CoverDataToVector(dirEntry.path().string().c_str());
        }
    }

    for (const auto& dirEntry : std::filesystem::directory_iterator(tempPath.parent_path())) {
        if (dirEntry.is_regular_file() && dirEntry.path().has_extension() && CheckIfValidImage(dirEntry.path().extension())) {
            if (HasAlbumCoverName(dirEntry.path().filename()))
                return CoverDataToVector(dirEntry.path().string().c_str());
        }
    }

    return TagLib::ByteVector();

}