#include <stdio.h>
#include <string.h>
#include <iostream>

#define TAGLIB_STATIC

#include "taglib/mpegfile.h"
#include "taglib/flacfile.h"
#include "taglib/oggfile.h"
#include "taglib/id3v2tag.h"
#include "taglib/id3v2.h"
#include "taglib/id3v2frame.h"
#include "taglib/attachedpictureframe.h"
#include "taglib/tpropertymap.h"
#include "taglib/mp4file.h"
#include "taglib/mp4item.h"
#include "taglib/mp4coverart.h"

#include "Song.h"
#include "Album.h"
#include "Utilities/FileManager.h"

using namespace NokuMusic;

std::vector<Song*> Song::Songs = std::vector<Song*>();

Song::Song(const char* path, bool load) {
	//printf("> [Song]: Created song instance with path \"%s\".\n", path);
	if (!FileManager::Exists(path)) {
		Path = NULL;
		return;
	}

	Path = path;
	if (load)
		Load();

    LoadMetadata();
	LoadArt();

	Songs.push_back(this);
}

bool Song::Load() {
	if (Path == NULL) {
		printf("> [Song]: Song item has no path.\n");
		return false;
	}

	if (!FileManager::Exists(Path)) {
		printf("> [Song]: File \"%s\" does not exist.\n", Path);
		Path = NULL;
		return false;
	}

	Music = Mix_LoadMUS(Path);

	if (Music == NULL) {
		printf("> [Song]: File %s could not be loaded.\n", Path);
		printf("> [Song]: Error: \"%s\".\n", SDL_GetError());
		return false;
	}

	return true;
}

bool Song::LoadMetadata() {
	if (Path == NULL) {
		printf("> [Song]: Song item has no path.\n");
		return false;
	}

	if (!FileManager::Exists(Path)) {
		printf("> [Song]: File \"%s\" does not exist.\n", Path);
		Path = NULL;
		return false;
	}

	TagLib::FileRef* musicFile = new TagLib::FileRef(Path);

	if (musicFile->isNull()) {
		delete musicFile;
		return false;
	}

	TagLib::String _title = musicFile->tag()->title();
	TagLib::String _artist = musicFile->tag()->artist();
	TagLib::String _album = musicFile->tag()->album();
	TagLib::String _genre = musicFile->tag()->genre();

	Title = (_title != TagLib::String::null) ? strdup(_title.to8Bit().c_str()) : strdup(FileManager::PathFilename(Path));
	Artist = strdup(_artist.to8Bit().c_str());
	Album = (_artist != TagLib::String::null) ? strdup(_album.to8Bit().c_str()) : strdup(FileManager::PathDirectory(Path));
	Genre = strdup(_genre.to8Bit().c_str());
	int tempTrackNum = musicFile->tag()->track();
	Track = (tempTrackNum == 0) ? -1 : tempTrackNum;
	Duration = musicFile->audioProperties()->lengthInMilliseconds();
	Bitrate = musicFile->audioProperties()->bitrate();
	Year = musicFile->tag()->year();

	//std::cout << musicFile->tag()->properties().toString() << std::endl;
	delete musicFile;

	return true;
}

bool Song::LoadArt() {
	if (Path == NULL) {
		printf("> [Song]: Song item has no path.\n");
		return false;
	}

	if (!FileManager::Exists(Path)) {
		printf("> [Song]: File \"%s\" does not exist.\n", Path);
		Path = NULL;
		return false;
	}

	TagLib::FileRef* musicFile = new TagLib::FileRef(Path);

	if (musicFile->isNull()) {
		printf("> [Song]: Failed to create file reference.\n");
		delete musicFile;
		return false;
	}
	if (TagLib::MPEG::File* mpegFile = dynamic_cast<TagLib::MPEG::File*>(musicFile->file())) {
		if (mpegFile->hasID3v2Tag()) {
			TagLib::ID3v2::Tag* mpegTag = mpegFile->ID3v2Tag();
			if (mpegTag) {
				TagLib::ID3v2::FrameList frames = mpegTag->frameList();
				for (auto it = frames.begin(); it != frames.end(); ++it) {
					TagLib::ID3v2::AttachedPictureFrame* frame = dynamic_cast<TagLib::ID3v2::AttachedPictureFrame*>(*it);
					if (frame) {
						Art = frame->picture();
					}
				}
			}
		}
	}
	else if (TagLib::MP4::File* mp4File = dynamic_cast<TagLib::MP4::File*>(musicFile->file())) {
		if (mp4File->hasMP4Tag()) {
			TagLib::MP4::Tag* mp4Tag = mp4File->tag();
			if (mp4Tag) {
				TagLib::MP4::ItemMap mp4Map = mp4Tag->itemMap();
				for (auto it = mp4Map.begin(); it != mp4Map.end(); ++it) {
					TagLib::MP4::CoverArtList art = it->second.toCoverArtList();
					if (!art.isEmpty()) {
						Art = art[0].data();
					}
				}
			}
		}
	}



	/*
	if (Art.isEmpty()) {
		Art = FileManager::ScanForAlbumCover(Path);
	}*/

	return true;
}

bool Song::IsLoaded() {
	return (Music != NULL);
}

const char* Song::GetPath() {
	return Path;
}

Mix_Music* Song::GetMusic() {
	return Music;
}

TagLib::ByteVector Song::GetArt() {
	return Art;
}

const char* Song::GetTitle() {
	return Title;
}

const char* Song::GetArtist() {
	return (Artist == NULL) ? "Unknown Artist" : Artist;
}

const char* Song::GetAlbum() {
	return (Album == NULL) ? "No Album" : Album;
}

const char* Song::GetGenre() {
	return (Genre == NULL) ? "No Genre" : Genre;
}

int Song::GetTrack() {
	return Track;
}

int Song::GetDurationMS() {
	return Duration;
}

const char* Song::GetTrackNumber() {
	char* buffer = new char[64];
	sprintf(buffer, "%d", Track);
	return buffer;
}

const char* Song::GetDuration() {
	char* buffer = new char[64];
	sprintf(buffer, "%d", Duration);
	return buffer;
}

int Song::GetYear() {
	return Year;
}

void Song::SetAlbumObject(NokuMusic::Album* album) {
	if (this->album != nullptr)
		return;

	this->album = album;
}

Song* Song::GetSong(int index) {
	int size = Songs.size();
	if (index > size)
		return nullptr;
	
	if (index < 0)
		index = size + index;

	if (index < 0)
		return nullptr;

	return Songs[index];
}

void Song::PrintData() {
	if (Path == NULL)
		return;

	if (Title == NULL || Album == NULL || Artist == NULL)
		return;

	printf("> [Song]: %2d. \"%s\" (from \"%s\") by \"%s\"\n", Track,
													   (Title[0] == '\0')  ? "No Title" : Title,
													   (Album[0] == '\0')  ? "-" 	    : Album,
													   (Artist[0] == '\0') ? "Unknown Artist": Artist);
}
