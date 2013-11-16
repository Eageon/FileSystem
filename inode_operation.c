#include "inode.h"
#include "block.h"


//extern int curr_fd;
extern struct super_block curr_superblock;
struct block curr_block;
uint curr_block_num;
//struct inode curr_inode;
//uint curr_inode_num;


void read_inode(uint inode, struct inode *inode_buf) {
    //error: inode_offset may be negative
    //error: curr_inode and curr_block are not updated;
    int block_index = (inode - 1) / INODES_PER_BLOCK + 2;
    int inode_offset = (inode - 1) % INODES_PER_BLOCK;
    int byte_offset = inode_offset * INODESIZE;

    if(block_index != curr_block_num) {
        curr_block_num = block_index;
        read_block(block_index, &curr_block, BLOCKSIZE);
    }
    if(inode == 2) {
        DEBUG("This is it\n");
    }
    memcpy((void *)&curr_inode, (void *)&curr_block + byte_offset, INODESIZE);
}

void write_inode(uint inode, struct inode *inode_buf) {
    int block_index = (inode - 1) / INODES_PER_BLOCK + 2;
    int inode_offset = (inode -1) % INODES_PER_BLOCK;
    int byte_offset = inode_offset * INODESIZE;

    //memcpy(&curr_inode, inode_buf, INODESIZE);

    if(block_index != curr_block_num) {
        curr_block_num = block_index;
        read_block(block_index, &curr_block, BLOCKSIZE);
    }
    memcpy((void *)&curr_block + byte_offset, (void *)inode_buf, INODESIZE);
    write_block(block_index, &curr_block, BLOCKSIZE);
}

int free_inode(uint free_inode) {
    if(curr_superblock.ninode == MAX_SIZE)
        return -1;
    curr_superblock.inode[curr_superblock.ninode] = free_inode;
    curr_superblock.ninode++;
    write_superblock();
    return 0; 
}

uint get_free_inode() {
    if(curr_superblock.ninode == 0) 
        return -1;
    curr_superblock.ninode--;
    uint inode_id = curr_superblock.inode[curr_superblock.ninode];
    write_superblock();
    return inode_id; 
           
}

int is_free_inode(struct inode* ino) {
    return ino->flags >> 15;
}
