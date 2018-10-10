//
//  text.c
//  CorewarVisualiser
//
//  Created by Edwy MANDRET on 10/8/18.
//  Copyright © 2018 Edwy MANDRET. All rights reserved.
//

#include "visualiser.h"

static void render_legend_title(char *str)
{
    int text_w, text_h;

    // Initialize the surface
    SDL_Surface *surface = TTF_RenderText_Blended(g_font_title, str, g_white);

    // Create the texture from the surface and free it
    SDL_Texture *texture = SDL_CreateTextureFromSurface(g_renderer, surface);
    SDL_FreeSurface(surface);

    // Retrieve the texture dimensions and set the variables using pointers
    SDL_QueryTexture(texture, NULL, NULL, &text_w, &text_h);

    // Render a copy
    SDL_RenderCopy(g_renderer,
                   texture,
                   NULL,
                   &(SDL_Rect){(273 - text_w) / 2, 40, text_w, text_h});

    // Free the texture
    SDL_DestroyTexture(texture);
}

static void
render_legend_text(unsigned int pos_x, unsigned int pos_y, char *str)
{
    int text_w, text_h;

    // Initialize the surface and texture from an unicode text string
    SDL_Surface *surface = NULL;

    // Create the surface from wide string or normal string
    surface = TTF_RenderText_Blended(g_font_text, str, g_white);

    // Create the texture from the surface and free it
    SDL_Texture *texture = SDL_CreateTextureFromSurface(g_renderer, surface);
    SDL_FreeSurface(surface);

    // Retrieve the texture dimensions and set the variables using pointers
    SDL_QueryTexture(texture, NULL, NULL, &text_w, &text_h);

    // Render a copy
    SDL_RenderCopy(g_renderer,
                   texture,
                   NULL,
                   &(SDL_Rect){pos_x, pos_y, text_w, text_h});

    // Free the texture
    SDL_DestroyTexture(texture);
}

void cw_render_players_legend(void)
{
    // Render the legend title
    render_legend_title("Players");

    if (!MEMORY_SHARING) {
        return;
    }

    // Retrieve the shared memory address
    t_vm *vm = (t_vm *) g_shared.shmem;

    for (int i = 0; i < vm->players_amount; i++) {

        // Get the player color
        SDL_Color player_color = cw_player_color(i + 1);

        // Set color
        SDL_SetRenderDrawColor(g_renderer,
                               player_color.r,
                               player_color.g,
                               player_color.b,
                               player_color.a);

        // Draw the filled rectangle
        SDL_RenderFillRect(g_renderer,
                           &((SDL_Rect){.x = QUAD_OFFSET(1),
                                        .y = QUAD_OFFSET(i * 2) + 100,
                                        .w = QUAD_SIZE,
                                        .h = QUAD_SIZE}));

        // Print the player program name
        render_legend_text(QUAD_OFFSET(2.5),
                           QUAD_OFFSET(i * 2) + 100,
                           vm->players[i].header.prog_name);
    }

    if (vm->winner.id != NO_PLAYER) {
        cw_render_bg("Images/bg2.jpg");

        // Initialize the surface
        SDL_Surface *winner_info = TTF_RenderText_Blended(g_font_title,
                                                          "WINNER",
                                                          g_white);
        SDL_Surface *winner_name = TTF_RenderText_Blended(g_font_text,
                                                          vm->winner.header.prog_name,
                                                          cw_player_color(vm->winner.id +
                                                                          1));

        // Create the texture from the surface and free it
        SDL_Texture *texture_winner_info = SDL_CreateTextureFromSurface(g_renderer,
                                                                        winner_info);
        SDL_FreeSurface(winner_info);
        SDL_Texture *texture_winner_name = SDL_CreateTextureFromSurface(g_renderer,
                                                                        winner_name);
        SDL_FreeSurface(winner_name);

        int text_h, text_w;

        // Retrieve the texture dimensions and set the variables using pointers
        SDL_QueryTexture(texture_winner_info, NULL, NULL, &text_w, &text_h);

        // Render a copy
        SDL_RenderCopy(g_renderer,
                       texture_winner_info,
                       NULL,
                       &(SDL_Rect){(1440 - text_w) / 2,
                                   (900 - text_h) / 2 - text_h,
                                   text_w,
                                   text_h});

        // Retrieve the texture dimensions and set the variables using pointers
        SDL_QueryTexture(texture_winner_name, NULL, NULL, &text_w, &text_h);

        // Render a copy
        SDL_RenderCopy(g_renderer,
                       texture_winner_name,
                       NULL,
                       &(SDL_Rect){(1440 - text_w) / 2,
                                   (900 - text_h) / 2 + text_h,
                                   text_w,
                                   text_h});

        // Free the texture
        SDL_DestroyTexture(texture_winner_info);
        SDL_DestroyTexture(texture_winner_name);
    }
}
