#include <filesystem>
#include <iostream>

#define TAGLIB_STATIC
#include "taglib/fileref.h"

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
