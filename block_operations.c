#include "common.h"
#include "block.h"

extern int curr_fd;
extern struct super_block curr_superblock;

inline void write_superblock() {
        int bytes = 0;
        if((bytes = write(curr_fd, curr_superblock, sizeof(struct super_block)) < 0 ) {
                fprintf(stderr, "Error in write th superblock errno = %d\n", -bytes);
                exit(errno);
        }
}


ssize_t read_block(int block, void* buf, size_t count) {
        if(count > BLOCKSIZE)
                return -1;
        int offset = block * BLOCKSIZE;

        int offs = 0;
        if((offs = lseek(curr_fd, offset, SEEK_SET)) < 0) {
                printf(stderr, "Error in seek block %d\n", block);
                exit(errno);
        }

        int bytes = 0;
        if((bytes = read(curr_fd, buf, count)) < 0) {
                printf(stderr, "Error in read block %d\n", block);
                exit(errno);
        }

        return bytes;
}

ssize_t write_block(int block, void *buf, size_t count) {
        if(count > BLOCKSIZE)
                return -1;
        int offset = block * BLOCKSIZE;

        int offs = 0;
        if((offs = lseek(curr_fd, offset, SEEK_SET)) < 0) {
                printf(stderr, "Error in seek block %d\n", block);
                exit(errno);
        }

        int bytes = 0;
        if((bytes = write(curr_fd, buf, count)) < 0) {
                printf(stderr, "Error in read block %d\n", block);
                exit(errno);
        }

        return bytes;
}

void free_block(uint free_block) {
    if(curr_superblock.nfree ==  MAX_SIZE) {
        struct head_free_block w;
        int i;
        w.nfr = curr_superblock.nfree;
        memcpy(w.fr, curr_superblock.free, curr_superblock.nfree * sizeof(uint));
        write_block(free_block, (void*)&w, (curr_superblock.nfree + 1) * sizeof(uint)); //write nfree and free array into block i;
        curr_superblock.nfree = 0;
    }
    curr_superblock.free[curr_superblock.nfree++] = free_block;    
}


uint allocate_block() {
    curr_superblock.nfree--;
    uint block_id = curr_superblock.free[curr_superblock.nfree];
    if(block_id == 0) {
        fprintf(stderr, "Error: the data blocks are full, allocation failure\n");
        exit(-1);
    }
    if(curr_superblock.nfree == 0) {
        struct head_free_block w;
        int i;
        read_block(block_id, (void*)&w, curr_superblock.nfree * sizeof(uint));
        curr_superblock.nfree = w.nfr;
        memcpy(curr_superblock.free, w.fr, (curr_superblock.nfree + 1) * sizeof(uint));
    }
    return block_id;
}
