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

struct block {
    uint data[512];
};

struct data_block {
    uint data[512];
};
inline void write_superblock();
ssize_t read_block(int block, void* buf, size_t count);
ssize_t write_block(int block, void *buf, size_t count);
void free_block(uint free_block); //add a freed block number to free array;
uint allocate_block();   //return a freed block number
    
#endif

