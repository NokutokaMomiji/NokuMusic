#ifndef NOKU_MUSIC_INTERFACE_COMPONENT_H
#define NOKU_MUSIC_INTERFACE_COMPONENT_H

#include "./Utilities/Vector.h"
#include "./Utilities/Window.h"


namespace NokuMusic {
	class InterfacePage;

    class InterfaceComponent {
        public:
            InterfaceComponent();
            virtual void Init();
            virtual void Update(int x, int y);
            virtual void Draw(int x, int y);

            virtual Vector2D<int> GetDimensions(); 
            virtual void SetPage(InterfacePage* page);
            virtual InterfacePage* GetPage(); 
        protected:
            Window* window;
            Vector2D<int> Dimensions;
            InterfacePage* parentPage = nullptr;

    };
}

#endif
