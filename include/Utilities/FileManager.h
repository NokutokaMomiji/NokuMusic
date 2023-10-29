#ifndef NOKU_MUSIC_FILE_MANAGER_H
#define NOKU_MUSIC_FILE_MANAGER_H

#include <vector>

#define TAGLIB_STATIC
#include "taglib/fileref.h"
#include "taglib/tbytevector.h"

namespace NokuMusic {
    class FileManager {
	public:
	    FileManager();

		static bool Exists(const char* path);
		static bool ScanPath(const char* path);
		static const char* PathFilename(const char* path);
		static const char* PathDirectory(const char* path);
		static TagLib::ByteVector ScanForAlbumCover(const char* path);

	private:
	    std::vector<const char*> musicPaths;
	    static FileManager* Manager;

    };
}

#endif
