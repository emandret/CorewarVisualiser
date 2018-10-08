//
//  visualiser.h
//  CorewarVisualiser
//
//  Created by Edwy MANDRET on 10/5/18.
//  Copyright © 2018 Edwy MANDRET. All rights reserved.
//

#ifndef VISUALISER_H
#define VISUALISER_H

#include "corewar.h"
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>

#define MEMORY_SHARING 1
#define WINDOW_TITLE "Corewar Visualiser"
#define WINDOW_WIDTH 1440
#define WINDOW_HEIGHT 900
#define QUAD_SIZE 12
#define GRID_SIZE 64

typedef struct s_shared {
    void *shmem;
    int shmid;
} t_shared;

typedef enum e_player_id {
    NO_PLAYER,
    PLAYER_1,
    PLAYER_2,
    PLAYER_3,
    PLAYER_4,
    PLAYER_5,
    PLAYER_6
} t_player_id;

typedef struct s_position {
    unsigned int x;
    unsigned int y;
} t_position;

typedef struct s_frameset {
    t_position pos;
    unsigned int w;
    unsigned int h;
} t_frameset;

typedef struct s_text {
    t_position pos;
    SDL_Color color;
    TTF_Font *font;
    char *value;
} t_text;

/*
 * Global variable declarations for memory sharing and windowing context
 */
extern t_shared g_shared;
extern SDL_Window *g_window;
extern SDL_Renderer *g_renderer;

/*
 * Initialization and cleanup
 */
void cw_init(void);
void cw_cleanup(void);

/*
 * Event handling
 */
void cw_handle_event(SDL_Event *, _Bool *);

/*
 * Grid functions
 */
SDL_Color cw_player_color(unsigned char);
void cw_fill_grid(unsigned char (*)[GRID_SIZE]);
void cw_render_grid(t_frameset *, unsigned char (*)[GRID_SIZE]);

/*
 * Memory sharing functions
 */
void cw_start_shared_mem(t_shared *);
void cw_clean_shared_mem(t_shared *);

/*
 * Background functions
 */
void cw_render_bg(const char *);

/*
 * Utility functions
 */
SDL_Color cw_lighten_color(SDL_Color, double);

#endif
