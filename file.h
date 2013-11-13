#ifndef __FILES__FILESYSTEM_JUN__
#define __FILES__FILESYSTEM_JUN__

#include "common.h"

struct V6_file {
	ushort inumber;
	ushort filename[7];
};

typedef struct V6_file file_entry;

ssize_t read_file(const char *filename, void *buf, size_t count);
ssize_t write_file(char *filename, const void *buf, size_t count);
int current_directory(const char *filename);
ssize_t read_directory(struct inode);    

#endif
