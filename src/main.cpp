#include <iostream>
#include "SDL2/SDL.h"

#include "Interface.h"

int main(int argc, char* argv[]) {
    std::cout << "Hello world!" << std::endl;
    
    NokuMusic::Interface::Initialize();

    NokuMusic::Interface* mainInterface = new NokuMusic::Interface();
    mainInterface->Run();

    return 0;
}