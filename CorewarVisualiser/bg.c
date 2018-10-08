//
//  bg.c
//  CorewarVisualiser
//
//  Created by Edwy MANDRET on 10/6/18.
//  Copyright © 2018 Edwy MANDRET. All rights reserved.
//

#include "visualiser.h"

/*
 * Render background image
 */
void cw_render_bg(const char *path)
{
    SDL_Surface *background;

    if (!(background = IMG_Load(path))) {
        fprintf(stderr, "Img not found: %s\n", IMG_GetError());
        exit(1);
    }

    // Clear screen to black
    SDL_SetRenderDrawColor(g_renderer, 0, 0, 0, 255);
    SDL_RenderClear(g_renderer);

    // Create texture from background surface
    SDL_Texture *texture = SDL_CreateTextureFromSurface(g_renderer, background);
    SDL_FreeSurface(background);

    // Render it
    SDL_RenderCopy(g_renderer, texture, NULL, NULL);
    SDL_DestroyTexture(texture);
}
