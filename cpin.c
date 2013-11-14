#include "cpin.h"
int cpin(int argc, char** argv) {
    if(argc < 3) {
         printf("Usage: cpin external_file_name v6_file\n");
    }

    if (curr_fd == -1) {
         perror("disk doesn't exist!\n");
         exit(-1);
    }
    int infile = open(argv[1], 0400);
    uint curr_inode_number = find_file_in_current_directory(argv[2]);
    if (curr_inode_number != -1) {
        printf("File %s exists! Can't override an existing file", argv[2]);
        return -1;
    } 
    else {
        char *buf;
        buf = malloc(filelength);
        if (buf == 0)
        {
            printf("ERROR: Out of memory\n");
            return -1;
        }
        int size = read(infile, &buf,filelength);
        write_file(argv[2], &buf, size);
        free(buf);
    }
}
off_t fsize(const char *filename) {
    struct stat st;

    if (stat(filename, &st) == 0)
        return st.st_size;

    fprintf(stderr, "Cannot determine size of %s: %s\n",
            filename, strerror(errno));

    return -1;
}



