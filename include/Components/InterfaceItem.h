#ifndef NOKU_MUSIC_INTERFACE_ITEM_H
#define NOKU_MUSIC_INTERFACE_ITEM_H

#include <functional>

#include "InterfaceComponent.h"
#include "Utilities/Sprite.h"

namespace NokuMusic {
    class InterfaceItem : public InterfaceComponent {
        public:
            InterfaceItem(Window* window);
            void Init(const char* text, Sprite* sprite, std::function<void()> callback);
            void Update(int x, int y) override;
            void Draw(int x, int y) override;
        private:
            const char* Text;
            Sprite* sprite;
            std::function<void()> Callback;
    };
}

#endif