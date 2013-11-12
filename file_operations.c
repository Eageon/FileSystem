#include "file.h"
#include "inode.h"
#include "block.h"

extern struct V6_file curr_file;

ssize_t read_file(const char *filename, void *buf, size_t count) {
        struct inode inode;
        get_inode(curr_file.inumber, &inode);
        // if(inode.flags | 040000 != 0 )
        //      read_directory(&inode, )
}

int current_directory(const char *filename) {

}

ssize_t read_directory(struct inode) {

}
