#include "SDL2/SDL_FontCache.h"
#include "Components/InterfaceItem.h"


using namespace NokuMusic;

InterfaceItem::InterfaceItem(Window* window) {
    this->window = window;
}

void InterfaceItem::Init(const char* text, Sprite* sprite, std::function<void()> callback) {
    this->Text = text;
    this->sprite = sprite;
    this->Callback = callback;
}

void InterfaceItem::Update(int x, int y) {

}

void InterfaceItem::Draw(int x, int y) {
    sprite->Draw(x, y, 32, 32);
}