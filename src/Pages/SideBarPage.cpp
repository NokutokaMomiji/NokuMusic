#include "Pages/SideBarPage.h"
#include "Components/InterfaceItem.h"

using namespace NokuMusic;

static void Test() {

}

void SideBarPage::Init(Window* window) {
    InterfacePage::Init(window);

    auto first = new InterfaceItem(window);
    auto icon = new Sprite(window, "Textures/list.svg");
    
    ((InterfaceItem*)AddComponent(first))->Init("Text", icon, Test);
}

void SideBarPage::Update() {
    InterfacePage::Update();
}

void SideBarPage::Draw() {
    InterfacePage::Draw();
}