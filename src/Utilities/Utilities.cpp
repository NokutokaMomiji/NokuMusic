#include <string.h>
#include <cstdlib>

#include "Utilities/Utilities.h"

using namespace NokuMusic;

const char* Utilities::ShortenTo(const char* text, int length) {
    int textLength = strlen(text);
    if (length > textLength)
        return text;

    char* result = new char[length];

    for (int i = 0; i < length; i++) {
        result[i] = text[i];
    }

    result[length] = '\0';
    result[length - 1] = '.';
    result[length - 2] = '.';
    result[length - 3] = '.';

    return result;
}

const char* Utilities::WCharToChar(std::wstring s) {
    const wchar_t* wct = s.c_str();

    size_t size = (wcslen(wct) + 1) * sizeof(wchar_t);
    char* buffer = new char[size];

    std::wcstombs(buffer, wct, size);

    return buffer;
}

bool Utilities::BeginsWith(const char* string, const char* substring) {
    return (strncmp(string, substring, strlen(substring)) == 0);
}