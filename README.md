# Noku Music
## An open-source, C++ music player.

So, thus far, I haven't found a music player for PC that contains all the things I'd like to have from a nice music player.

In response, I had made a simple music player in GameMaker that allowed me to have the basic functionalities I wanted. After the change of the GameMaker runner from x86 to x64, that plan went sour due to the library I was using, so I decided to create a second music player, this time in C++ because I love suffering.

## Components:
- [SDL2](https://github.com/libsdl-org/SDL) (Contains released precompiled binaries and static libraries).
- [SDL_Mixer](https://github.com/libsdl-org/SDL_mixer) (You can get the necessary DLLs from the non-dev version).
- [SDL_ttf](https://github.com/libsdl-org/SDL_ttf)
- [SDL_FontCache](https://github.com/grimfang4/SDL_FontCache)
- [TagLib](https://taglib.org) (Requires to be built from scratch and it is a nightmare to interact with sometimes.)
- [FileWatch](https://github.com/ThomasMonkman/filewatch/tree/master)

## Structure:
The entire program UI is handled and drawn by the [Interface](src/Interface.cpp) class. The interface is made up of [Interface Pages](src/Pages/InterfacePages.cpp) containing [Interface Components](src/Components/InterfaceComponents.cpp).
I could have probably used a UI library but... yeah, no. Too many bad experiences and I like to torture myself.

Each [Song](src/Song.cpp) contains its own Metadata and Cover image data. Cover image data is always stored in a ``TagLib::ByteVector``. There are multiple ``Get...()`` functions to get the loaded data from a Song object. There are also static ``Get...()`` functions for getting general stored song objects. All Song objects on instantiation are added to a private std::vector, you can use the ``GetSong(int index)`` function to grab a song object from the list.

[Album](src/Album.cpp) objects contain an internal private ``std::vector<Song*>`` containing pointers to Song objects. The Album also contains its own metadata and album cover image data, which can either be derived from a Song object containing valid image data or it will scan the folder for a valid image file. The Album may also assign cover images to songs that do not possess a valid image data. Image data is always stored as a ``TagLib::ByteVector``, which can be used to create [Sprite](src/Utilities/Sprite.cpp) objects for drawing and stuff. 

Albums also have a few ``Get...()`` functions to get the Album data or get a song from the album. Songs are stored sorted by their album position, if there is one. The Songs that don't have an assigned number in the album are pushed to the end. Instanced Album objects are added to a private ``std::vector<Album*>`` containing all existing Album instances.

## Compiling
Compiling should theoretically be very straight forward. I have tried my best to include all necessary dependencies with the project so that there is no need for any external downloads or compilation (I already went though that and it sucks).
The project uses SDL2 primarily for graphics and audio playback, with TagLib for getting audio metadata. Other open-source things can be found in the files if you check.

The player also makes use of the ``<filesystem>`` library, so you'll need to be able to compile on C++17.

All you'll really need is a C++ compiler. I personally use g++, but you can try compiling using other compilers though I can't guarantee anything will work. The code has also only been tested in Windows thus far, so I am not sure whether it will compile on any other platform.

You can either use the included build scripts (build.sh hasn't been tested):
```bat
> ./build
```
or you can manually perform each needed step:
1. Compile the program.
```bat
> make
```
2. Copy all the files and folders from `datafiles` to `bin`. In Windows, I use
```bat
> xcopy datafiles bin /E/H/C/I/Y
```
3. Make sure that you ``cd`` to the ``bin`` directory (it should have been automatically created by the Makefile).
```bat
> cd bin
```
4. Open the program and have fun.
```bat
> ./nokuplayer
```
