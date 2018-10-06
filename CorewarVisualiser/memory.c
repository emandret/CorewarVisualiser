//
//  memory.c
//  CorewarVisualiser
//
//  Created by Edwy MANDRET on 10/6/18.
//  Copyright © 2018 Edwy MANDRET. All rights reserved.
//

#include "visualiser.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define BUF_SHMID 1024

/*
 * Start System V IPC memory sharing
 */
void cw_start_shared_mem(t_shared *shared)
{
    char buf[BUF_SHMID];

    // Retrieve the shmid
    shared->shmid = atoi(fgets(buf, BUF_SHMID, stdin));

    // Attach to shared memory
    shared->shmem = shmat(shared->shmid, NULL, 0);

    // shmat return (void *) -1 in case of error
    if (shared->shmem == (void *) -1) {
        fprintf(stderr, "shmat error: %s\n", strerror(errno));
        exit(1);
    }
}

/*
 * Stop memory sharing
 */
void cw_clean_shared_mem(t_shared *shared)
{
    // Detach from shared memory
    shmdt(shared->shmem);

    // Destroy the shared memory
    shmctl(shared->shmid, IPC_RMID, NULL);

    // Erase the structure
    memcpy(shared, &(t_shared){0}, sizeof(t_shared));
}
