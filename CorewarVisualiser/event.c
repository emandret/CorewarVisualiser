//
//  event.c
//  CorewarVisualiser
//
//  Created by Edwy MANDRET on 10/5/18.
//  Copyright © 2018 Edwy MANDRET. All rights reserved.
//

#include "visualiser.h"

void cw_handle_event(SDL_Event *event, _Bool *quit)
{
    SDL_WaitEvent(event);

    switch (event->type) {
        case SDL_QUIT:
            *quit = 1;
    }
}
