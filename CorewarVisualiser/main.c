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

    // Initialize the grid
    unsigned char grid[GRID_SIZE][GRID_SIZE];

    while (!quit) {
        // Handle event and update quit condition if necessary
        cw_handle_event(&event, &quit);

        // Render background
        cw_render_bg("Images/bg.jpg");

        // Fill the grid
        cw_fill_grid(grid);

        // Display it
        cw_render_grid(273, 3, grid);
        cw_render_players_legend();

        // Render on screen
        SDL_RenderPresent(g_renderer);
    }

    cw_cleanup();
    return 0;
}
