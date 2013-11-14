#include "V6stdio.h"
int cpin(int argc, char** argv) {
    int src_fd, n, err;
    unsigned char buffer[2048];
    char * src_path, dst_path;
    
    // Assume that the program takes two arguments the source path followed
    // by destination file name.
    if(argc != 3) {
         printf("Usage: cpin external_file_name v6_file\n");
         exit(-1);
    }

    if (curr_fd == -1) {
         perror("disk doesn't exist!\n");
         exit(-1);
    }

    uint curr_inode_number = find_file_in_current_directory(argv[2]);
    if (curr_inode_number != -1) {
        printf("Filename %s exists! Can't override an existing file", argv[2]);
        return -1;
    } 

    src_path = argv[1];
    dst_path = argv[2];

    src_fd = open(src_path, O_RDONLY);
    //dst_fd = open(dst_path, O_CREAT | O_WRONLY);


    while (1) {
        err = read(src_fd, buffer, 2048);
        if (err == -1) {
            perror("Error reading file.\n");
            exit(1);
        }
        n = err;

        if (n == 0) break;

        err = write_file(dst_path, buffer, n);
        if (err == -1) {
            perror("Error writing to file.\n");
            exit(1);
        }
    }
    close(src_fd);
    //close(dst_fd);
}

int cpout(int argc, char** argv) {
    int src_fd, n, err;
    unsigned char buffer[4096];
    char* src_path, dst_path;
    
    // Assume that the program takes two arguments the source path followed
    // by destination file name.
    if(argc != 3) {
         printf("Usage: cpin v6_file external_file_name\n");
         exit(-1);
    }

    if (curr_fd == -1) {
         perror("disk doesn't exist!\n");
         exit(-1);
    }
    uint curr_inode_number = find_file_in_current_directory(argv[2]);
    if (curr_inode_number != -1) {
        printf("filename %s exists! Can't override an existing file", argv[2]);
        return -1;
    } 

    src_path = argv[1];
    dst_path = argv[2];

   // src_fd = open(src_path, O_RDONLY);
    dst_fd = open(dst_path, O_CREAT | O_WRONLY);
    
    while (1) {
        err = read_file(src_path, buffer, 2048);
        if (err == -1) {
            perror("Error reading file.\n");
            exit(1);
        }
        n = err;

        if (n == 0) break;

        err = write(dst_fd, buffer, n);
        if (err == -1) {
            perror("Error writing to file.\n");
            exit(1);
        }
    }
    //close(src_fd);
    close(dst_fd);
}


   /* int infile = open(argv[1], 0400);
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
    */
int mkdir (int argc, char** argv) {
    char* dir_name;
    if(argc != 2) {
         printf("Usage: mkdir V6-directory\n");
         exit(-1);
    }

    if (curr_fd == -1) {
         perror("disk doesn't exist!\n");
         exit(-1);
    }

    uint curr_inode_number = find_directory_in_current_directory(argv[2]);
    if (curr_inode_number != -1) {
        printf("Diretory %s exists! Can't override an existing file", argv[2]);
        return -1;
    }
    dir_name =  argv[1];
    mkdir(dir_name);
}

int ls(int argc, char** argv) {
    char* all_files_in_curr_diretory[64];
    if(argc != 1) {
         printf("Usage: ls\n");
         exit(-1);
    }

    if (curr_fd == -1) {
         perror("disk doesn't exist!\n");
         exit(-1);
    }
    int file_count;
    list_current_directory(all_files_in_curr_diretory,&file_count);
    int i;
    for(i = 0; i < file_count; i++) {
        printf("%d.%s",i+1,all_files_in_curr_diretory[i]);
    }
}


