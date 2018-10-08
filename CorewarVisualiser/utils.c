//
//  utils.c
//  CorewarVisualiser
//
//  Created by Edwy MANDRET on 10/8/18.
//  Copyright © 2018 Edwy MANDRET. All rights reserved.
//

#include "visualiser.h"
#include <math.h>

SDL_Color cw_lighten_color(SDL_Color color, double amount)
{
    color.r = (unsigned int) fmin(255, color.r + 255 * amount);
    color.g = (unsigned int) fmin(255, color.g + 255 * amount);
    color.b = (unsigned int) fmin(255, color.b + 255 * amount);

    return color;
}
