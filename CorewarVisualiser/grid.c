//
//  grid.c
//  CorewarVisualiser
//
//  Created by Edwy MANDRET on 10/5/18.
//  Copyright © 2018 Edwy MANDRET. All rights reserved.
//

#include "visualiser.h"

/*
 * Global color variables
 */
const SDL_Color g_gray = {50, 50, 50, 125};
const SDL_Color g_white = {255, 255, 255, 225};
const SDL_Color g_red = {255, 0, 75, 225};
const SDL_Color g_green = {0, 255, 100, 225};
const SDL_Color g_blue = {50, 225, 255, 225};
const SDL_Color g_yellow = {255, 255, 0, 225};
const SDL_Color g_purple = {255, 0, 255, 225};
const SDL_Color g_orange = {255, 100, 0, 225};

/*
 * Return the color associated to a player
 */
SDL_Color cw_player_color(unsigned char player_id)
{
    switch (player_id) {
        case NO_PLAYER:
            return g_gray;
        case PLAYER_1:
            return g_red;
        case PLAYER_2:
            return g_green;
        case PLAYER_3:
            return g_blue;
        case PLAYER_4:
            return g_yellow;
        case PLAYER_5:
            return g_purple;
        case PLAYER_6:
            return g_orange;
        default:
            return (SDL_Color){0};
    }
}

/*
 * Fill the player grid with the shared memory values
 */
void cw_fill_grid(unsigned char grid[][GRID_SIZE])
{
    if (!MEMORY_SHARING) {
        return;
    }

    // Retrieve the shared memory address
    t_vm *vm = (t_vm *) g_shared.shmem;

    vm->flags |= FLAG_START;
    for (int y = 0; y < GRID_SIZE; y++) {
        for (int x = 0; x < GRID_SIZE; x++) {
            grid[y][x] = vm->mem_owner[y * GRID_SIZE + x];
        }
    }
}

/*
 * Render the player grid
 */
void cw_render_grid(unsigned int pos_x,
                    unsigned int pos_y,
                    unsigned char grid[][GRID_SIZE])
{
    // Position of each box
    unsigned int player_pos_x = pos_x, player_pos_y = pos_y;

    // Static variables are initialized to zero on first function call
    static _Bool first_call;

    // At the very first call, the values of the grid are set to NO_PLAYER
    if (!first_call) {
        memset(grid, NO_PLAYER, sizeof(grid[0][0]) * GRID_SIZE * GRID_SIZE);
        first_call = 1;
    }

    for (int y = 0; y < GRID_SIZE; y++) {
        for (int x = 0; x < GRID_SIZE; x++) {
            // Set alpha channel
            SDL_SetRenderDrawBlendMode(g_renderer, SDL_BLENDMODE_BLEND);

            // Get the player color
            SDL_Color player_color = cw_player_color(grid[y][x]);

            // Lighten the cursor color for the current cycle printing
            if (MEMORY_SHARING &&
                ((t_vm *) g_shared.shmem)->mem_cycles[y * GRID_SIZE + x] >
                ((t_vm *) g_shared.shmem)->cycle - CYCLE_TO_PRINT) {
                player_color = cw_lighten_color(player_color, .5);
            }

            // Set color
            SDL_SetRenderDrawColor(g_renderer,
                                   player_color.r,
                                   player_color.g,
                                   player_color.b,
                                   player_color.a);

            // Draw the filled rectangle
            SDL_RenderFillRect(g_renderer,
                               &((SDL_Rect){.x = player_pos_x,
                                            .y = player_pos_y,
                                            .w = QUAD_SIZE,
                                            .h = QUAD_SIZE}));

            player_pos_x = pos_x + QUAD_OFFSET(x);
        }
        player_pos_x = pos_x;
        player_pos_y = pos_y + QUAD_OFFSET(y);
    }
}
