//
//  init.c
//  CorewarVisualiser
//
//  Created by Edwy MANDRET on 10/5/18.
//  Copyright © 2018 Edwy MANDRET. All rights reserved.
//

#include "visualiser.h"

/*
 * Static storage duration objects are initialized to zero but it is always
 * better to explicitly initialize variables
 */
t_shared g_shared = {0};
SDL_Window *g_window = NULL;
SDL_Renderer *g_renderer = NULL;

/*
 * Initializiation
 */
void cw_init(void)
{
    // Start memory sharing
    if (MEMORY_SHARING) {
        cw_start_shared_mem(&g_shared);
    }

    if (SDL_Init(SDL_INIT_VIDEO) == -1) {
        fprintf(stderr, "Could not initialize SDL: %s\n", SDL_GetError());
        exit(1);
    }

    if (TTF_Init() == -1) {
        fprintf(stderr, "Could not initialize SDL_ttf: %s\n", TTF_GetError());
        exit(1);
    }

    // Create the window context
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

    // Create the renderer for the created window
    g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);

    if (!g_renderer) {
        fprintf(stderr, "Could not create renderer: %s\n", SDL_GetError());
        exit(1);
    }
}

/*
 * Must be called before program termination
 */
void cw_cleanup(void)
{
    // Stop memory sharing
    if (MEMORY_SHARING) {
        cw_clean_shared_mem(&g_shared);
    }

    // Destroy windowing context
    SDL_DestroyRenderer(g_renderer);
    SDL_DestroyWindow(g_window);

    // Quit libraries
    TTF_Quit();
    SDL_Quit();
}
