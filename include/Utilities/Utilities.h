#ifndef NOKU_MUSIC_UTILITIES_H
#define NOKU_MUSIC_UTILITIES_H

#include <string>

namespace NokuMusic {
    class Utilities {
        public:
            static const char* ShortenTo(const char* text, int length);
            static const char* WCharToChar(std::wstring s);
            static bool BeginsWith(const char* string, const char* substring);
    };
}

#endif