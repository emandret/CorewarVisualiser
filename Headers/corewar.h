//
//  corewar.h
//  CorewarVisualiser
//
//  Created by Edwy MANDRET on 10/5/18.
//  Copyright © 2018 Edwy MANDRET. All rights reserved.
//

#ifndef COREWAR_H
#define COREWAR_H

#include <stddef.h>

#define MAX_PLAYERS 4
#define PROG_NAME_LENGTH 128
#define COMMENT_LENGTH 2048
#define MEM_SIZE (4 * 1024)
#define CHAMP_MAX_SIZE (MEM_SIZE / 6)
#define CYCLE_TO_PRINT 200
#define FLAG_START 16

typedef struct s_list {
    void *content;
    size_t content_size;
    struct s_list *next;
} t_list;

typedef struct s_header {
    unsigned int magic;
    char prog_name[PROG_NAME_LENGTH + 1];
    unsigned int prog_size;
    char comment[COMMENT_LENGTH + 1];
} t_header;

typedef struct s_player {
    t_header header;
    int id;
    unsigned char code[CHAMP_MAX_SIZE];
    unsigned int lives_amount;
    unsigned int last_live_ts;
} t_player;

typedef struct s_vm {
    t_player players[MAX_PLAYERS];
    unsigned int players_amount;
    unsigned int flags;
    unsigned int verbose_flags;
    unsigned int dump_cycle;
    t_list *processes;
    unsigned char mem[MEM_SIZE];
    unsigned char mem_owner[MEM_SIZE];
    unsigned int mem_cycles[MEM_SIZE];
    unsigned int cycle;
    unsigned int cycle_to_die;
    int cycle_to_die_delta;
    unsigned int skip_cycles;
    unsigned int checks_left;
    unsigned int lives_amount;
    unsigned int next_process_id;
    unsigned int last_player;
} t_vm;

#endif
