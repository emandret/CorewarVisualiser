//
//  event.c
//  CorewarVisualiser
//
//  Created by Edwy MANDRET on 10/5/18.
//  Copyright © 2018 Edwy MANDRET. All rights reserved.
//

#include "visualiser.h"

/*
 * Set the quit variable to 1 (true) if the SDL_QUIT event is triggered
 */
void cw_handle_event(SDL_Event *event, _Bool *quit)
{
    SDL_PollEvent(event);

    switch (event->type) {
        case SDL_QUIT:
            *quit = 1;
    }
}
