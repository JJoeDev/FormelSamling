#include <iostream>
#include <SDL2/SDL.h>

int main(){
    if(SDL_InitSubSystem(SDL_INIT_VIDEO) < 0){
        std::cerr << "[ ERROR ] SDL2 failed initialization\n";
        return -1;
    }

    SDL_Window* window = SDL_CreateWindow("SDL2 Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 680, 480, SDL_WINDOW_SHOWN);
    if(!window){
        std::cerr << "[ ERROR ] SDL2 window error: " << SDL_GetError() << '\n';
        return -1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(!renderer){
        std::cerr << "[ ERROR ] SDL2 Render error: " << SDL_GetError() << '\n';
        return -1;
    }

    SDL_SetRenderDrawColor(renderer, 20, 20, 20, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

    bool running = true;
    SDL_Event e;
    while(running){
        while(SDL_PollEvent(&e)){
            if(e.type == SDL_QUIT) running = false;
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}