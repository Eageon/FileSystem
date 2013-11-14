#include "common.h" 
#include "block.h" 
#include "inode.h"

extern int curr_fd;
extern struct super_block curr_superblock;
void initiate_inode_list();
void print_superblock();
void initiate_super_block(int fd, int total_block_number, int inode_block_number);
void initiate_inode_list();
void print_superblock();
int initfs(int argc, char** argv);
