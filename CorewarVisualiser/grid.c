//
//  grid.c
//  CorewarVisualiser
//
//  Created by Edwy MANDRET on 10/5/18.
//  Copyright © 2018 Edwy MANDRET. All rights reserved.
//

#include "visualiser.h"

/*
 * Private color variables
 */
static const SDL_Color white = {255, 255, 255, 255};
static const SDL_Color red = {255, 0, 0, 255};
static const SDL_Color green = {0, 255, 0, 255};
static const SDL_Color blue = {0, 0, 255, 255};
static const SDL_Color yellow = {255, 255, 0, 255};
static const SDL_Color purple = {255, 0, 255, 255};
static const SDL_Color orange = {255, 155, 0, 255};

/*
 * Return the color associated to a player
 */
SDL_Color cw_player_color(unsigned char player_id)
{
    switch (player_id) {
        case NO_PLAYER:
            return white;
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
 * Render the player grid
 */
void cw_render_grid(t_frameset *frameset, unsigned char grid[][GRID_SIZE])
{
    t_position player_pos = {frameset->pos.x, frameset->pos.y};

    /*
     * Static variables are initialized to zero on first function call
     */
    static _Bool first_call;

    /*
     * At the very first call, the values of the grid are set to NO_PLAYER
     */
    if (!first_call) {
        memset(grid, 8, sizeof(grid[0][0]) * GRID_SIZE * GRID_SIZE);
        first_call = 1;
    }

    for (int y = 0; y < GRID_SIZE; y++) {
        for (int x = 0; x < GRID_SIZE; x++) {

            SDL_Color player_color = cw_player_color(grid[y][x]);
            SDL_SetRenderDrawColor(g_renderer,
                                   player_color.r,
                                   player_color.g,
                                   player_color.b,
                                   player_color.a);

            SDL_RenderFillRect(g_renderer,
                               &((SDL_Rect){.x = player_pos.x,
                                            .y = player_pos.y,
                                            .w = QUAD_SIZE,
                                            .h = QUAD_SIZE}));

            player_pos.x = x * QUAD_SIZE;
        }
        player_pos.x = frameset->pos.x;
        player_pos.y = y * QUAD_SIZE;
    }

    frameset->h = player_pos.x + QUAD_SIZE;
    frameset->w = player_pos.y + QUAD_SIZE;

    SDL_RenderPresent(g_renderer);
}
