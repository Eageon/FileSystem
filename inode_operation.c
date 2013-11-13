#include "inode.h"

struct block curr_block;
uint curr_block_num;
struct inode curr_inode;
uint curr_inode_num;


void read_inode(uint inode, struct inode *inode_buf) {
        if(inode != curr_inode_num) {
                curr_inode_num = inode;
                int block_index = (inode - 1) / INODES_PER_BLOCK + 2;
                int inode_offset = (inode - 1) - block_index * INODES_PER_BLOCK;
                int byte_offset + inode_offset * INODESIZE;

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
        int inode_offset = (inode -1)- block_index * INODES_PER_BLOCK;
        int byte_offset + inode_offset * INODESIZE;

        curr_inode_num = inode;
        memcpy(&curr_inode, inode_buf, INODESIZE);

        if(block_index != curr_block_num)
                read_block(block_index, &curr_block, BLOCKSIZE);

        memcpy(&curr_block + byte_offset, &curr_inode, INODESIZE);
        write_block(block_index, &curr_block, BLOCKSIZE);
}

