//
//  init.c
//  CorewarVisualiser
//
//  Created by Edwy MANDRET on 10/5/18.
//  Copyright © 2018 Edwy MANDRET. All rights reserved.
//

#include "visualiser.h"

SDL_Window *g_window = NULL;
SDL_Renderer *g_renderer = NULL;

void cw_init(void)
{
    if (SDL_Init(SDL_INIT_VIDEO) == -1) {
        fprintf(stderr, "Could not initialize SDL: %s\n", SDL_GetError());
        exit(1);
    }

    if (TTF_Init() == -1) {
        fprintf(stderr, "Could not initialize SDL_ttf: %s\n", TTF_GetError());
        exit(1);
    }

    g_window = SDL_CreateWindow(WINDOW_TITLE,
                                SDL_WINDOWPOS_UNDEFINED,
                                SDL_WINDOWPOS_UNDEFINED,
                                WINDOW_WIDTH,
                                WINDOW_HEIGHT,
                                SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI);

    if (!g_window) {
        fprintf(stderr, "Could not create window: %s\n", SDL_GetError());
        exit(1);
    }

    g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);

    if (!g_renderer) {
        fprintf(stderr, "Could not create renderer: %s\n", SDL_GetError());
        exit(1);
    }
}

void cw_cleanup(void)
{
    SDL_DestroyRenderer(g_renderer);
    SDL_DestroyWindow(g_window);

    TTF_Quit();
    SDL_Quit();
}
