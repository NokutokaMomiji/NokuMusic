#ifndef NOKU_MUSIC_SIDE_BAR_PAGE_H
#define NOKU_MUSIC_SIDE_BAR_PAGE_H

#include "InterfacePage.h"

namespace NokuMusic {
    class SideBarPage : public InterfacePage {
        public:
            void Init(Window* window) override;
            void Update() override;
            void Draw() override;
    };
}

#endif