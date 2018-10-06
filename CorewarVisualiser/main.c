//
//  main.c
//  CorewarVisualiser
//
//  Created by Edwy MANDRET on 10/5/18.
//  Copyright © 2018 Edwy MANDRET. All rights reserved.
//

#include "visualiser.h"

int main(void)
{
    _Bool quit = 0;
    SDL_Event event;

    // Initialize global variables
    cw_init();

    // Clear screen
    SDL_SetRenderDrawColor(g_renderer, 0, 0, 0, 255);
    SDL_RenderClear(g_renderer);

    while (!quit) {

        // Handle event and update quit condition if necessary
        cw_handle_event(&event, &quit);

        // Initialize the grid
        t_frameset frameset = {10, 10, 0, 0};
        unsigned char grid[GRID_SIZE][GRID_SIZE];

        // Modify it
        grid[32][32] = PLAYER_2;

        // Print it
        cw_render_grid(&frameset, grid);
    }

    cw_cleanup();
    return 0;
}
