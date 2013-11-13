#ifndef __FILES__FILESYSTEM_JUN__
#define __FILES__FILESYSTEM_JUN__

#include "common.h"
#include "inode.h"

struct V6_file {
	uint inumber;
	byte filename[32 - sizeof(uint)];
};

//typedef struct V6_file ;
#define file_entry V6_file


#define FILE_ENTRY_SIZE sizeof(struct V6_file)

extern ssize_t read_file(const char *filename, void *buf, size_t count);
extern ssize_t write_file(char *filename, const void *buf, size_t count);
//int current_directory(const char *filename);
//extern int read_directory(struct inode *dir_inode, struct file_entry *entries, int *entry_num);

#endif
