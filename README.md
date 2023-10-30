# Noku Music
## An open-source, C++ music player.

So, thus far, I haven't found a music player for PC that contains all the things I'd like to have from a nice music player.

In response, I had made a simple music player in GameMaker that allowed me to have the basic functionalities I wanted. After the change of the GameMaker runner from x86 to x64, that plan went sour due to the library I was using, so I decided to create a second music player, this time in C++ because I love suffering.

## Components:
- [https://github.com/libsdl-org/SDL](SDL2) (Contains released precompiled binaries and static libraries).
- [https://github.com/libsdl-org/SDL_mixer](SDL_Mixer) (You can get the necessary DLLs from the non-dev version).
- [https://github.com/libsdl-org/SDL_ttf](SDL_ttf)
- [https://github.com/grimfang4/SDL_FontCache](SDL_FontCache)
- [https://taglib.org](Taglib) (Requires to be built from scratch and it is a nightmare to interact with sometimes.)
- [https://github.com/ThomasMonkman/filewatch/tree/master] (Filewatch)

# Structure:
The entire program UI is handled and drawn by the [src/Interface.cpp](Interface) class. The interface is made up of [src/Pages/InterfacePages.cpp](Interface Pages) containing [src/Components/InterfaceComponents.cpp](Inteface Components).
I could have probably used a UI library but... yeah, no. Too many bad experiences and I like to torture myself.

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
