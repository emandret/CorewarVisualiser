//
//  grid.c
//  CorewarVisualiser
//
//  Created by Edwy MANDRET on 10/5/18.
//  Copyright © 2018 Edwy MANDRET. All rights reserved.
//

#include "visualiser.h"

/*
 * Compute the quad offset related to the index in the grid
 */
#define QUAD_OFFSET(i) ((i + 1) * (QUAD_SIZE + QUAD_SIZE / 6))

/*
 * Private color variables
 */
static const SDL_Color gray = {50, 50, 50, 125};
static const SDL_Color red = {255, 0, 75, 225};
static const SDL_Color green = {0, 255, 100, 225};
static const SDL_Color blue = {50, 225, 255, 225};
static const SDL_Color yellow = {255, 255, 0, 225};
static const SDL_Color purple = {255, 0, 255, 225};
static const SDL_Color orange = {255, 100, 0, 225};

/*
 * Return the color associated to a player
 */
SDL_Color cw_player_color(unsigned char player_id)
{
    switch (player_id) {
        case NO_PLAYER:
            return gray;
        case PLAYER_1:
            return red;
        case PLAYER_2:
            return green;
        case PLAYER_3:
            return blue;
        case PLAYER_4:
            return yellow;
        case PLAYER_5:
            return purple;
        case PLAYER_6:
            return orange;
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
void cw_render_grid(t_frameset *set, unsigned char grid[][GRID_SIZE])
{
    t_position player_pos = {set->pos.x, set->pos.y};

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

            // Set color
            SDL_SetRenderDrawColor(g_renderer,
                                   player_color.r,
                                   player_color.g,
                                   player_color.b,
                                   player_color.a);

            // Draw the filled rectangle
            SDL_RenderFillRect(g_renderer,
                               &((SDL_Rect){.x = player_pos.x,
                                            .y = player_pos.y,
                                            .w = QUAD_SIZE,
                                            .h = QUAD_SIZE}));

            player_pos.x = set->pos.x + QUAD_OFFSET(x);
        }
        player_pos.x = set->pos.x;
        player_pos.y = set->pos.y + QUAD_OFFSET(y);
    }

    set->w = set->pos.x + QUAD_OFFSET(GRID_SIZE - 1);
    set->h = set->pos.y + QUAD_OFFSET(GRID_SIZE - 1);

    // Render the grid
    SDL_RenderPresent(g_renderer);
}
