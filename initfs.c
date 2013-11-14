#include "common.h" 
#include "block.h" 
#include "inode.h"

int curr_fd;
struct super_block curr_superblock;
void initiate_inode_list();
void print_superblock();
void initiate_super_block(int fd, int total_block_number, int inode_block_number) {
    int i;
    curr_fd = fd;
    curr_superblock.isize = inode_block_number;
    curr_superblock.fsize = total_block_number;
    curr_superblock.nfree = 0;
    curr_superblock.ninode = 0;
    //free_block(&curr_superblock, 0);
    uint max_inode_block = 1 + inode_block_number;
    for(i = curr_superblock.fsize - 1; i > max_inode_block; i--) {
        free_block(i);
    }
    int arr[512];
    memset(arr,0 ,sizeof(arr));
    for(i = 2; i <= max_inode_block; i++)
        write_block(i, arr, sizeof(arr)); 
    initiate_inode_list();
     
    write_superblock();

}

void initiate_inode_list() {

    uint inode_number = curr_superblock.isize * INODES_PER_BLOCK;
    int i;
    for(i = 2; i < inode_number; i++) {
        if(curr_superblock.ninode == MAX_SIZE) 
            break;
        struct inode ino;
        read_inode(i, &ino);
        if(is_free_inode(&ino))
            if(curr_superblock.ninode == MAX_SIZE) 
                break; 
            free_inode(i);    
    }
    if(curr_superblock.ninode == 0){ 
        fprintf(stderr,"Error: the inode blocks are full, allocation falure!");
        exit(-1);
    }
}

void print_superblock() {
    printf("isize: %d\n",curr_superblock.isize);
    printf("fsize: %d\n",curr_superblock.fsize);
    printf("nfree: %d\n",curr_superblock.nfree);
    int i;
    for(i = 0; i<curr_superblock.nfree; i++){
        printf("free %d: %d  ",i, curr_superblock.free[i]);
    }
    printf("\n");
    printf("ninode: %d\n",curr_superblock.ninode);
    for(i = 0; i<curr_superblock.nfree; i++){
        printf("free %d: %d  ",i, curr_superblock.inode[i]);
    }
}
int main(int argc, char** argv) {
    if(argc < 4) {
         printf("Usage: initfs file_name(representing disk) n1(total number of blocks) n2(total number of blocks containing inodes)\n");
    }

    curr_fd = open(argv[1], O_CREAT | O_RDWR, 0600);
    if (curr_fd == -1) {
        perror("File cannot be opened");
        exit(-1);
    }
    int n1 = atoi(argv[2]);
    int n2 = atoi(argv[3]);
    lseek(curr_fd, n1 * 2048, SEEK_SET);
    write(curr_fd," ",1);
    initiate_super_block(curr_fd, n1, n2);
    print_superblock();
    while(1)
        printf("allocated block: %d\n", allocate_block());
    int i;
    for(i = n2+2; i<n1; i++) {
        free_block(i);
    }
    print_superblock();
    close(curr_fd);
    return 0;
}


