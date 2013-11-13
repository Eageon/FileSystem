#ifndef __FILES__FILESYSTEM_JUN__
#define __FILES__FILESYSTEM_JUN__

#include "common.h"

struct V6_file {
	uint inumber;
	byte filename[32 - sizeof(uint)];
};

typedef struct V6_file file_entry;

#define FILE_ENTRY_SIZE sizeof(struct V6_file)

ssize_t read_file(const char *filename, void *buf, size_t count);
int current_directory(const char *filename);
ssize_t read_directory(struct inode);    

#endif
