#include "common.h"
#include "block.h"

extern int curr_fd;
extern struct super_block curr_superblock;

inline void write_superblock() {
        int bytes = 0;
        if((bytes = write(curr_fd, &curr_superblock, sizeof(struct super_block)) < 0 ) {
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
