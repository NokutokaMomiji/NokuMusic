#include "Pages/AlbumPage.h"
#include "Components/InterfaceAlbum.h"
#include "Album.h"
#include "Song.h"
#include "SDL2/SDL_FontCache.h"

using namespace NokuMusic;

void AlbumPage::Init(Window* window, FC_Font* font) {
    InterfacePage::Init(window);
    this->window = window;

    int numOfAlbums = Album::GetNumOfAlbums();
    for (int i = 0; i < numOfAlbums; i++) {
        ((InterfaceAlbum*)AddComponent(new InterfaceAlbum(window)))->Init(Album::GetAlbum(i), font);
    }

    Dimensions.X = 1280;
    Dimensions.Y = 320;
}

void AlbumPage::Update() {

}

void AlbumPage::Draw() {
    Vector2D<int> itemPosition = { 8, 8 };
    InterfaceAlbum* currentAlbum = nullptr;
    Vector2D<int> componentDimensions;

    for (const auto& component : Components) {
        // Get current album component by casting it back to InterfaceAlbum.
        // We also get the component dimensions for position shenanigans.
        currentAlbum = reinterpret_cast<InterfaceAlbum*>(component);
        componentDimensions = currentAlbum->GetDimensions();

        // We draw the current album at the current calculated position and set the item position for the next component.
        currentAlbum->Draw(itemPosition.X, itemPosition.Y);
        itemPosition.X += componentDimensions.X;

        // We don't want the next component to get drawn off-screen or get cut in the middle
        // So, we check for that and break the line.
        if (itemPosition.X + componentDimensions.X > Dimensions.X) {
            itemPosition.X = 0;
            itemPosition.Y += componentDimensions.Y + 8;
        }
    }

    Dimensions.Y = itemPosition.Y;
}