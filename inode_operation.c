#include "inode.h"

extern int curr_fd;
extern struct super_block curr_superblock;
struct block curr_block;
uint curr_block_num;
struct inode curr_inode;
uint curr_inode_num;


void read_inode(uint inode, struct inode *inode_buf) {
    //error: inode_offset may be negative
    //error: curr_inode and curr_block are not updated;
    if(inode != curr_inode) {
        curr_inode_num = inode;
        int block_index = (inode - 1) / INODES_PER_BLOCK + 2;
        int inode_offset = (inode - 1) % INODES_PER_BLOCK;
        int byte_offset = inode_offset * INODESIZE;

        if(block_index != curr_block_num) {
            curr_block_num = block_index;
            read_block(block_index, &curr_block, BLOCKSIZE);
        }
        memcpy(&curr_inode, &curr_block + byte_offset, INODESIZE);
    }
    inode_buf = &curr_inode;
}

void write_inode(uint inode, struct inode *inode_buf) {
    int block_index = (inode - 1) / INODES_PER_BLOCK + 2;
    int inode_offset = (inode -1) % INODES_PER_BLOCK;
    int byte_offset = inode_offset * INODESIZE;

    curr_inode_num = inode;
    memcpy(&curr_inode, inode_buf, INODESIZE);

    if(block_index != curr_block_num) {
        curr_block_num = block_index;
        read_block(block_index, &curr_block, BLOCKSIZE);
    }
    memcpy(&curr_block + byte_offset, &curr_inode, INODESIZE);
    write_block(block_index, &curr_block, BLOCKSIZE);
}

void free_inode(uint free_inode) {
    int i;
    if(s_super.ninode == MAX_SIZE) 
        return;
    s_super.inode[s_super.ninode] = i;
    s_super.ninode++; 
}

uint allocate_inode() {
    if(s_super.ninode == 0) 
        initiate_inode_list(s_super);
    s_super.ninode--;
    uint inode_id = s_super.inode[s_super.ninode];
    return inode_id; 
           
}

bool is_free_inode(struct inode* ino) {
    return ino->flags >> 15;
}
