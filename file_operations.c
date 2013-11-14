#include "common.h"
#include "file.h"
#include "inode.h"
#include "block.h"

struct V6_file curr_dir;

int read_file_by_inode(struct inode *file_inode, byte* buf) {
    struct inode inode;
    read_inode(file_inode.inumber, &inode);
    if(inode.flags | 0100000 == 0 ) {
       	ERROR("Interna: error: not a");
    }
}

int write_file_by_inode(struct inode *file_inode, byte* buf, size_t count) {

}

uint current_directory(const char *filename) {
	uint tmp_inode = find_file_in_current_directory(filename);
	if(tmp_inode < 1) {
		return -1;
	}
}

inline int read_inode_data(struct inode *file_inode, struct inode_data *data) {
	memcpy(data, file_inode->addr, sizeof(uint) * 21);
}

//int read_inode_block(struct inode *file_inode, struct block *blocks) {
	//struct inode_data data;
	//read_inode_data(file_inode, data.addr);
//}

int read_directory(struct inode *dir_inode, struct file_entry **entries, int *entry_num) {
	if(*entries == NULL)
		return -1;

	int ENTRY_NUM = dir_inode->size / FILE_ENTRY_SIZE; 
	*entries = malloc(ENTRY_NUM * FILE_ENTRY_SIZE);
	*entry_num = ENTRY_NUM;

	struct inode_data data;
	read_inode_data(dir_inode, &data);

	int i;
	int num_full_block = dir_inode->size / BLOCKSIZE;
	struct block tmp_block;
	for(i = 0; i < num_full_block; i++) {
		read_block(data.addr[i], &tmp_block, BLOCKSIZE);
		memcpy((struct block *)entries[i], &tmp_block, BLOCKSIZE);
	}

	int byte_in_block = dir_inode->size - num_full_block * BLOCKSIZE;
	memcpy((struct block *)entries[num_full_block], data.addr[num_full_block], (int)byte_in_block);

	return 0;
}

// char *read_filename_from_inode(struct file_entry *file) {
// 	//return file_inode.filename;
// }

int is_this_file(struct file_entry *entry, const char* filename) {
	if(strcmp(entry->filename, filename) == 0)
		return 1;
	else 
		return 0;
}

inline uint file_to_inode(struct V6_file* file) {
	return file->inumber;
}

// inline uint inode_to_file(uint inode, struct V6_file* file) {
// 	//struct inode inode_buf;
// 	//read_inode(inode, &inode_buf);
// 	//return
// }

//return inode number 
uint find_file_in_directory(const char *filename, struct V6_file *spec_dir) {
	if(spec_dir.inumber != curr_inode_num) {
		curr_inode_num = spec_dir.inumber;
		read_inode(curr_inode_num, &curr_inode);
	}

	if(curr_inode.flags | 100000 == 0) {
		ERROR("Internal error: an existing file contains unallocated inode\n");
	}

	if(curr_inode.flags | 40000 == 0) {
		ERROR("Internal error: the current file is NOT directory\n");
	}

	struct file_entry *entries; //allocated in read_directory, you need to free it after use
	int entry_num = 0;
	read_directory(&curr_inode, &entries, &entry_num);

	int i = 0;
	for(i = 0; i < entry_num; i++) {
		if(is_this_file(&entries[i], filename)) {
			int ret = entries[i].inumber;
			free(entries);
			return ret;
		}
	}

	return -1;
}

//return inode number
uint find_file_in_current_directory(const char *filename) {
	return find_file_in_directory(filename, &curr_dir);
}
