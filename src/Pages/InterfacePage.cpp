#include "Pages/InterfacePage.h"

using namespace NokuMusic;

void InterfacePage::Init(Window* window) {
    Components = std::vector<InterfaceComponent*>();
    this->window = window;
}

void InterfacePage::Update() {

}

void InterfacePage::Draw() {

}

void InterfacePage::SetDimensions(int x, int y) {

}

InterfaceComponent* InterfacePage::AddComponent(InterfaceComponent* component) {
    Components.push_back(component);
    return component;
}

bool InterfacePage::RemoveComponent(InterfaceComponent* component) {

}