#ifndef __BLOCK_FILESYSTEM__
#define __BLOCK_FILESYSTEM__
#include "common.h"
#define MAX_SIZE 251
struct super_block {
    uint isize;
    uint fsize;
    uint nfree;
    uint ninode;
    uint free[MAX_SIZE];
    uint inode[MAX_SIZE];
    char flock;
    char ilock;
    char fmod;
    char padding;
    long time[2];
};
#define BLOCKSIZE sizeof(struct super_block)
//for the head of free array
struct head_free_block {
    uint nfr;
    uint fr[MAX_SIZE];
    uint padding[512 - MAX_SIZE - 1];
};

struct data_block {
    int data[512];
};
#endif

