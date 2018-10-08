//
//  main.c
//  CorewarVisualiser
//
//  Created by Edwy MANDRET on 10/5/18.
//  Copyright © 2018 Edwy MANDRET. All rights reserved.
//

#include "visualiser.h"

/*
 * Entrypoint that provides the main event loop
 */
int main(void)
{
    _Bool quit = 0;
    SDL_Event event;

    // Initialize global variables
    cw_init();

    // Grid frameset
    t_frameset frameset = {{273, 3}, 0, 0};

    // Initialize the grid
    unsigned char grid[GRID_SIZE][GRID_SIZE];

    while (!quit) {
        // Handle event and update quit condition if necessary
        cw_handle_event(&event, &quit);

        // Render background
        cw_render_bg("Images/bg.jpeg");

        // Fill the grid
        cw_fill_grid(grid);

        // Display it
        cw_render_grid(&frameset, grid);
    }

    // Grid dimensions updated in frameset structure
    printf("grid width = %d, grid height = %d\n", frameset.w, frameset.h);

    cw_cleanup();
    return 0;
}
