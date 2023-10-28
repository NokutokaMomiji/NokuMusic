#include "Components/InterfaceComponent.h"

using namespace NokuMusic;

InterfaceComponent::InterfaceComponent() {
}

void InterfaceComponent::Init() {

}

void InterfaceComponent::Update(int x, int y) {
    return;
}

void InterfaceComponent::Draw(int x, int y) {
    return;
}

Vector2D<int> InterfaceComponent::GetDimensions() {
    return Dimensions;
}

void InterfaceComponent::SetPage(InterfacePage* page) {
    if (parentPage != nullptr)
        return;

    parentPage = page;
}

InterfacePage* InterfaceComponent::GetPage() {
    return parentPage;
}