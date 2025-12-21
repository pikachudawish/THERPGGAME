#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#define W_TITLE "The RPG Game"

void intro_game(SDL_Renderer* r) {
    SDL_SetRenderDrawColor(r, 0, 0, 0, 255);
    SDL_RenderClear(r);
    SDL_RenderPresent(r);

    SDL_Delay(3000);
    
    return;
}

int gameloop() {
    if(SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr, "SDL_ERROR: %s\n", SDL_GetError());
        return 0;
    }

    SDL_Window* w = SDL_CreateWindow(W_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP);
    if(!w) {
        fprintf(stderr, "SDL_ERROR: %s\n", SDL_GetError());
        SDL_Quit();
        return 0;
    }

    SDL_Renderer* r = SDL_CreateRenderer(w, -1, 0); 
    if(!r) {
        fprintf(stderr, "SDL_ERROR: %s\n", SDL_GetError());
        SDL_DestroyWindow(w); SDL_Quit();
        return 0;
    }

    intro_game(r);

    int gl = 1; SDL_Event e;
    while(gl) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        gl = 0; 
                        break;
                }
            }
        }

        SDL_SetRenderDrawColor(r, 255, 0, 0, 255);
        SDL_RenderClear(r);
        SDL_RenderPresent(r);
        
        SDL_Delay(16);
    }

    SDL_DestroyRenderer(r);
    SDL_DestroyWindow(w);
    SDL_Quit();

    return 1;
}
