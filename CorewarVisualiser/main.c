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

    // Grid frameset
    t_frameset frameset = {{0, 0}, 0, 0};

    while (!quit) {

        // Handle event and update quit condition if necessary
        cw_handle_event(&event, &quit);

        // Initialize the grid
        unsigned char grid[GRID_SIZE][GRID_SIZE];

        // Modify it
        grid[0][0] = PLAYER_2;
        grid[10][10] = PLAYER_1;
        grid[25][25] = PLAYER_6;

        // Print it
        cw_render_grid(&frameset, grid);
    }

    // Grid dimensions updated in frameset structure
    printf("grid width = %d, grid height = %d\n", frameset.w, frameset.h);

    cw_cleanup();
    return 0;
}
