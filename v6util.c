#include "v6util.h"
#include "block.h" 
#include "inode.h"
#include "file.h"

struct V6_file root2;


int initfs(int argc, char** argv) {
    if(argc < 4) {
         printf("Usage: initfs file_name(representing disk) n1(total number of blocks) n2(total number of blocks containing inodes)\n");
         return -1;
    }

    curr_fd = open(argv[1], O_CREAT | O_RDWR, 0600);
    if (curr_fd == -1) {
        perror("Disk cannot be allocated");
        exit(-1);
    }
    int n1 = atoi(argv[2]);
    int n2 = atoi(argv[3]);
    lseek(curr_fd, n1 * 2048, SEEK_SET);
    write(curr_fd," ",1);
    initiate_super_block(curr_fd, n1, n2);
    make_root_directory(&root2); 
 //   print_superblock();
 /*   int allocated_block;
    while(allocated_block = allocate_block())
        printf("allocated block: %d\n", allocated_block);
    int i;
    for(i = n2+2; i<n1; i++) {
        free_block(i);
    }
    print_superblock();
    */
    
    return 0;
}


int cpin(int argc, char** argv) {
    //int n, err;
    int src_fd;
   // unsigned char buffer[2048];
    char * src_path, *dst_path;
    
    // Assume that the program takes two arguments the source path followed
    // by destination file name.
    if(argc != 3) {
         printf("Usage: cpin external_file_name v6_file\n");
         return 1;
    }

    if (curr_fd == -1) {
         perror("disk doesn't exist!\n");
         exit(-1);
    }

    uint curr_inode_number = find_file_in_directory(argv[2], &root2);
    if (curr_inode_number != -1) {
         printf("Filename %s exists! You are not allowed to override an existing file. Please change to another filename\n", argv[2]);
         return -1;
    } 

    src_path = argv[1];
    dst_path = argv[2];


    struct stat statbuf; 
    src_fd = open(src_path, O_RDONLY);
    if (fstat(src_fd, &statbuf) == -1) {
    /* check the value of errno */
    }
    int filelength = statbuf.st_size;

    //printf("file size %ld", statbuf.st_size);
    //dst_fd = open(dst_path, O_CREAT | O_WRONLY);
    // fseek(src_fd, 0L, SEEK_END);
    // int filelength = ftell(src_fd);
    // fseek(src_fd, 0L, SEEK_SET);

    /*while (1) {
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
    */
    char *buf;
    buf = malloc(filelength);
    if (buf == 0)
    {
        printf("ERROR: Out of memory\n");
        return -1;
    }
    int size = read(src_fd, buf, filelength);
    write_file(dst_path, buf, size);
    free(buf);
    //close(dst_fd);
    return 0;
}

int cpout(int argc, char** argv) {
    int dst_fd;//, n, err;
    //unsigned char buffer[4096];
    char* src_path, *dst_path;
    
    // Assume that the program takes two arguments the source path followed
    // by destination file name.
    if(argc != 3) {
         printf("Usage: cpin v6_file external_file_name\n");
         return 1; 
    }

    if (curr_fd == -1) {
         perror("disk doesn't exist!\n");
         exit(-1);
    }
    uint curr_inode_number = find_file_in_directory(argv[2], &root2);
    if (curr_inode_number != -1) {
        printf("filename %s doesn't exists! Please check your typing\n", argv[2]);
        return -1;
    } 

    src_path = argv[1];
    dst_path = argv[2];

   // src_fd = open(src_path, O_RDONLY);
    dst_fd = open(dst_path, O_CREAT | O_WRONLY, 0600);
    /*
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
    }*/
    char *buf;
    int filelength = get_file_size(src_path);
    buf = malloc(filelength);
    if (buf == 0)
    {
        printf("ERROR: Out of memory\n");
        return -1;
    }
 
    read_file(src_path, buf, filelength);
    write(dst_fd, buf, filelength);
    free(buf);
    //close(dst_fd);
    return 0;
    //close(src_fd);
    close(dst_fd);
    return 0;
}


int mkdir1 (int argc, char** argv) {
    char* dir_name;
    if(argc != 2) {
         printf("Usage: mkdir V6-directory\n");
         exit(-1);
    }

    if (curr_fd == -1) {
         perror("disk doesn't exist!\n");
         exit(-1);
    }

    int curr_inode_number = find_directory_in_directory(argv[1], &root2);
    if (curr_inode_number != -1) {
        printf("Diretory %s exists! Can't override an existing file\n", argv[1]);
        return -1;
    }
    dir_name =  argv[1];
    make_directory_in_directory(dir_name, &root2);
    return 0;
}

int ls(int argc, char** argv) {
    char** all_files_in_curr_diretory;
    if(argc != 1) {
         printf("Usage: ls\n");
         exit(-1);
    }

    if (curr_fd == -1) {
         perror("disk doesn't exist!\n");
         exit(-1);
    }
    int file_count = list_directory(&all_files_in_curr_diretory,&root2);
    int i;
    for(i = 0; i < file_count; i++) {
        printf("%s\t",all_files_in_curr_diretory[i]);
    }
    printf("\n");
    for (i = 0; i < file_count; ++i)
    {
        free(all_files_in_curr_diretory[i]);
    }
    free(all_files_in_curr_diretory);
    return 0;
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

