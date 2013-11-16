#ifndef __FILES__FILESYSTEM_JUN__
#define __FILES__FILESYSTEM_JUN__

#include "common.h"
#include "inode.h"
#include "block.h"

#define FILENAME_LENGTH (32 - sizeof(uint))

struct V6_file {
	uint inumber;
	byte filename[FILENAME_LENGTH];
};


//typedef struct V6_file ;
#define file_entry V6_file


#define FILE_ENTRY_SIZE (sizeof(struct V6_file))

int read_file_by_inode(struct inode *file_inode, byte* buf);
int write_file_by_inode(struct inode *file_inode, byte* buf, size_t count);
int read_directory(struct inode *dir_inode, struct file_entry **entries, int *entry_num);

uint find_file_in_directory(const char *filename, struct V6_file *spec_dir);
//uint find_file_in_current_directory(const char *filename);
uint find_directory_in_directory(const char *filename, struct V6_file *spec_dir);
uint make_directory_in_directory(char *filename, struct V6_file *spec_dir);
int add_directory_to_inode(struct file_entry *file, struct inode *dir_inode);

int list_directory(char **);
int make_root_directory();

//int current_directory(const char *filename);
//extern int read_directory(struct inode *dir_inode, struct file_entry *entries, int *entry_num);

#endif
