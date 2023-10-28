#ifndef NOKU_MUSIC_FILE_MANAGER_H
#define NOKU_MUSIC_FILE_MANAGER_H

#include <vector>

namespace NokuMusic {
    class FileManager {
	public:
	    FileManager();

		static bool Exists(const char* path);
		static bool ScanPath(const char* path);
		static const char* PathFilename(const char* path);
		static const char* PathDirectory(const char* path);

	private:
	    std::vector<const char*> musicPaths;
	    static FileManager* Manager;

    };
}

#endif
