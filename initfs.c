#include "common.h" 
#include "block.h" 
#include "inode.h"

int curr_fd;
extern struct inode curr_inode;
extern struct data_block curr_block;

void initiate_super_block(int fd, int total_block_number, int inode_block_number) {
    struct super_block s_block;
    int i;
    curr_fd = fd;
    s_block.isize = inode_block_number;
    s_block.fsize = total_block_number;
    s_block.nfree = 0;
    s_block.ninode = 0;
    free_block(&super_block, 0);
    u_int max_inode_block = 1 + inode_block_number;
    for(i = fsize - 1; i > max_data_block; i--) {
        free_block(&super_block, i);
    }
    initiate_inode_list(&super_block, inode_block_number);
    u_int root = 1;
    
    write_superblock((void*)&s_block);

}

void initiate_inode_list(struct super_block* s_super) {

    u_int inode_number = s_super->isize * INODE_PER_BLOCK;
    int i;
    for(i = 2; i < inode_number; i++) {
        if(s_super->ninode == MAX_SIZE) 
            break;
        struct inode ino;
        read_inode(i, &ino);
        if(is_free_inode(&ino)
            free_inode(s_super, i);    
    }
    if(s_super->ninode == 0){ 
        fprintf(stderr,"Error: the inode blocks are full, allocation falure!");
        exit(-1);
    }
}
void free_inode(struct super_block* s_super, u_int free_inode) {
    int i;
    if(s_super->ninode == MAX_SIZE) 
        return;
    s_super->inode[s_super->ninode] = i;
    s_super->ninode++; 
}

u_int allocate_inode(struct super_block* s_super) {
    if(s_super->ninode == 0) 
        initiate_inode_list(s_super);
    s_super->ninode--;
    u_int inode_id = s_super->inode[s_super->ninode];
    return inode_id; 
           
}
void free_block(struct super_block* s_super, u_int free_block) {
    if(s_block.nfree ==  MAX_SIZE) {
        struct head_free_block w;
        int i;
        w.nfr = s_block->nfree;
        memcpy(w.fr, s_super->free, s_super->nfree * sizeof(u_int));
        write_block(free_block, (void*)&w, (s_block->nfree + 1) * sizeof(u_int)); //write nfree and free array into block i;
        s_block.nfree = 0;
    }
    s_block.free[s_block.nfree++] = free_block;    
}


u_int allocate_block(struct super_block* s_super) {
    s_super->nfree--;
    u_int block_id = s_super->free[s_super->nfree];
    if(block_id == 0) {
        fprintf(stderr, "Error: the data blocks are full, allocation failure\n");
        exit(-1);
    }
    if(s_super->nfree == 0) {
        struct head_free_block w;
        int i;
        read_block(block_id, (void*)&w, s_super->nfree * sizeof(u_int));
        s_super->nfree = w.nfr;
        memcpy(s_super->free, w.fr, (s_block->nfree + 1) * sizeof(u_int));
    }
    return block_id;
}



int main(int argc, char** argv) {
    if(argc < 4) {
         printf("Usage: initfs file_name(representing disk) n1(total number of blocks) n2(total number of blocks containing inodes)\n");
    }

    fd = open(argv[1], O_CREAT | O_RDWR);
    if (fd == -1) {
        perror("File cannot be opened");
        return EXIT_FAILURE;
    }
                                }
    printf("Size: %d\n", sizeof(struct super_block));
    printf("Size: %d\n", sizeof(long long));
    close(fd);
    return 0;
}


