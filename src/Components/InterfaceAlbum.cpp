#include "Components/InterfaceAlbum.h"
#include "Utilities/Utilities.h"
#include "Interface.h"

using namespace NokuMusic;

InterfaceAlbum::InterfaceAlbum(Window* window) {
    this->window = window;
    this->renderer = window->GetSDLRenderer();
}

void InterfaceAlbum::Init(Album* album, FC_Font* font) {
    this->album = album;

    printf((album == nullptr) ? "ALBUM IS NULLPTR INSIDE INIT!\n" : "fine?\n");

    albumTitle = Utilities::ShortenTo(album->GetTitle(), 32);
    albumArtist = Utilities::ShortenTo(album->GetArtist(), 20);
    albumArt = new Sprite(window, album->GetArt());
    textFont = font;

    printf("> %s\n", albumTitle);
    printf("> %s | %d %s\n", albumArtist, album->GetNumOfSongs(), (album->GetNumOfSongs() == 1) ? "track" : "tracks");

    Dimensions.X = 176; // 160 + 16 for padding.
    Dimensions.Y = 224; // 160 + 32 + 16 + 16 for padding;

    printf("> Width: %d | Height: %d\n", Dimensions.X, Dimensions.Y);
}

void InterfaceAlbum::Update(int x, int y) {

}

void InterfaceAlbum::Draw(int x, int y) {
    /*
        test->Draw(128, 128, 128 + 32, 128 + 32);
        FC_DrawAlign(internalManager->GetFont("default"), mainWindow->GetSDLRenderer(), 128 + ((128 + 32) / 2), 256 + 32 + 8, FC_ALIGN_CENTER, tempTitle);
        FC_DrawAlign(internalManager->GetFont("default"), mainWindow->GetSDLRenderer(), 128 + ((128 + 32) / 2), 256 + 32 + 8 + 16, FC_ALIGN_CENTER, tempArtist);
    */
    int numOfSongs = album->GetNumOfSongs();
    albumArt->Draw(x, y, 160, 160);
    FC_DrawAlign(textFont, window->GetSDLRenderer(), x + 80, y + 160 + 8, FC_ALIGN_CENTER, albumTitle);
    FC_DrawAlign(textFont, window->GetSDLRenderer(), x + 80, y + 160 + 8 + 16, FC_ALIGN_CENTER, "%s | %d %s", albumArtist, numOfSongs, (numOfSongs == 1) ? "track" : "tracks");   
}