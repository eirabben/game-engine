#include <iostream>
#include <SDL2/SDL.h>

int main(int argc, char* args[]) {
    bool quit {false};
    SDL_Window* window {nullptr};
    const int width {800};
    const int height {600};

    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("OpenGL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);

    SDL_SetRelativeMouseMode(SDL_TRUE);

    SDL_Event e;

    while (!quit) {
        while (SDL_PollEvent(&e)) {
            switch (e.type) {
                case SDL_QUIT:
                    quit = true;
                    break;
                case SDL_MOUSEMOTION:
                    std::cout << "Mouse moved\n";
                    break;
                default:
                    break;
            }
        }
    }

    SDL_DestroyWindow(window);
    window = nullptr;
    SDL_Quit();

    return 0;
}
