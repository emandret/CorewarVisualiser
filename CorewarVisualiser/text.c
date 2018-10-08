//
//  text.c
//  CorewarVisualiser
//
//  Created by Edwy MANDRET on 10/8/18.
//  Copyright © 2018 Edwy MANDRET. All rights reserved.
//

#include "visualiser.h"

void cw_render_text(unsigned int pos_x, unsigned int pos_y, t_text text)
{
    int text_w, text_h;

    // Initialize the surface and texture
    SDL_Surface *surface = TTF_RenderText_Blended(text.font,
                                                  text.body,
                                                  text.color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(g_renderer, surface);

    // Free the surface
    SDL_FreeSurface(surface);

    // Retrieve the texture size and update the text_w and text_h variables
    // using pointers
    SDL_QueryTexture(texture, NULL, NULL, &text_w, &text_h);

    // Render a copy
    SDL_RenderCopy(g_renderer,
                   texture,
                   NULL,
                   &(SDL_Rect){pos_x, pos_y, text_w, text_h});

    // Free the texture
    SDL_DestroyTexture(texture);
}
