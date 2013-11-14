#ifndef __INODE__FILESYSTEM_JUN__
#define __INODE__FILESYSTEM_JUN__

#include "common.h"

struct inode {
    ushort flags;
    char nlinks;
    char uid;
    char gid;
    char padding[3];
    uint size;
    uint addr[21];
    long actime[2];
    long modtime[2];
};

struct inode_data {
	uint addr[21];
};

#define INODESIZE sizeof(struct inode)
#define INODES_PER_BLOCK (BLOCKSIZE/INODESIZE)
void read_inode(uint inode, struct inode *inode_buf);
void write_inode(uint inode, struct inode *inode_buf);
int free_inode(uint free_inode);
uint get_free_inode();  //replace allocate_inode()
int is_free_inode(struct inode* ino);
size_t read_file(char *filename, void *buf);
size_t write_file(char *filename, void *buf, size_t count);

#endif
