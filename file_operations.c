#include "common.h"
#include "file.h"
#include "inode.h"
#include "block.h"

//struct V6_file curr_file;
extern struct V6_file curr_dir;
//extern struct inode curr_inode;
//extern uint curr_inode_num;

// add .. to the new created entry
int add_directory_to_directory(struct file_entry *file, struct V6_file *spec_dir) {

}


int make_root_directory() {
	struct inode root_inode;
	read_inode(1, &root_inode);
	allocate_inode(&root_inode);

	add_directory_to_inode("/", &root_inode);
	write_inode(1, &root_inode);
}

int add_directory_to_inode(struct file_entry *file, struct inode *dir_inode) {

	int full_blocks = dir_inode->size / BLOCKSIZE;
	if(full_blocks > 7)
		return -1;

	uint block_index = dir_inode->addr[full_blocks];
	struct block last_block;
	read_block(block_index, &last_block, BLOCKSIZE);
	int extra_entry = (dir_inode->size % BLOCKSIZE) / FILE_ENTRY_SIZE;
	
	if(extra_entry == (BLOCKSIZE / FILE_ENTRY_SIZE)))
		return -1;  // block is full of file entry

	memcpy((void *)&last_block + extra_entry * FILE_ENTRY_SIZE, file_entry, FILE_ENTRY_SIZE);

	write_block(block_index, &last_block, BLOCKSIZE);

	return 0;
}

// add . to the entry
inline int create_empty_directory_entry(char *filename, struct inode *dir_inode) {

}

uint make_directory_in_directory(char *filename, struct V6_file *spec_dir) {
	if(find_file_in_directory(filename, spec_dir) > 0)
		return -1; // Directory already exists

	struct inode dir_inode;
	struct file_entry new_entry;
	uint inode = get_free_inode();
	read_inode(inode, dir_inode);
	create_empty_directory_entry(filename, &new_entry);

	add_directory_to_inode(&new_entry, &dir_inode);
	write_inode(inode, &dir_inode);

	// not write spec_dir to disk, it may be completed by upper call
}

// 1 if already allocated
inline int check_allocation(struct inode *file_inode) {
	if(file_inode->flags & 0100000 == 0)
		return 1;
	return 0;
}

inline int allocate_inode_by_number(uint inode) {
	struct inode file_inode;
	read_inode(inode, &file_inode);
	return allocate_inode(&file_inode);
}

inline uint get_and_allocate_inode(struct inode *out_inode) {
	
	
	if(check_allocation(out_inode) == 1)
		return -1;

	allocate_inode(out_inode);
	return inode;
}

inline int allocate_inode(struct inode *file_inode) {
	if(check_allocation(file_inode) != 0)
		return -1;
	file_inode->flags |= 0100000;
	return 0;
}

int read_file_by_inode(struct inode *file_inode, byte* buf) {
	if(check_allocation(file_inode) == 0)
		return -1;

	struct inode inode;
    read_inode(curr_file.inumber, &inode);
    if(inode.flags & 0100000 == 0 ) {
       	ERROR("Interna: error: not a");
    }

    struct inode_data data;
	read_inode_data(file_inode, &data);

	int i;
	int num_full_block = file_inode->size / BLOCKSIZE;
	struct block tmp_block;
	for(i = 0; i < num_full_block; i++) {
		read_block(data.addr[i], &tmp_block, BLOCKSIZE);
		memcpy(buf + BLOCKSIZE * i, &tmp_block, BLOCKSIZE);
	}

	int extra_byte_in_block = file_inode->size - num_full_block * BLOCKSIZE;
	read_block(data.addr[num_full_block], &tmp_block, BLOCKSIZE);
	memcpy(buf + BLOCKSIZE * num_full_block, tmp_block.data, (int)extra_byte_in_block);

	return file_inode->size;
}

int write_file_by_inode(struct inode *file_inode, byte* buf, size_t count) {
	if(check_allocation(file_inode) != 0)
		return -1;
	allocate_inode(file_inode);

	struct inode_data data;
	read_inode_data(file_inode, &data);

	int i;
	int num_full_block = file_inode->size / BLOCKSIZE;
	struct block tmp_block;
	for(i = 0; i < num_full_block; i++) {
		memcpy(&tmp_block, buf + BLOCKSIZE * i, BLOCKSIZE);
		write_block(data.addr[i], &tmp_block, BLOCKSIZE);
	}

	int extra_byte_in_block = file_inode->size - num_full_block * BLOCKSIZE;
	memcpy(tmp_block.data, buf + BLOCKSIZE * num_full_block, (int)extra_byte_in_block);
	write_block(data.addr[num_full_block], &tmp_block, BLOCKSIZE);
}

inline uint filename_to_inode(char *filename, struct inode *file_inode) {
	int inode = find_file_in_directory(filename, curr_dir);
	struct inode file_inode;
	read_inode(inode, &file_inode);
	return inode;
}

size_t read_file(char *filename, void *buf) {
	struct inode file_inode;
	int inode = filename_to_inode(filename, &file_inode);
	if(inode <  0)
		return -1;

	return read_file_by_inode(&file_inode, buf);
}

size_t write_file(char *filename, void *buf, size_t count) {
	struct inode file_niode;
	//int inode = filename_to_inode(filename, &file_unode);
	int inode = get_free_inode();
	allocate_inode_by_number(inode);

	return write_file_by_inode(&file_inode, buf, count);
}

uint current_directory(const char *filename) {
	uint tmp_inode = find_file_in_current_directory(filename);
	if(tmp_inode < 1) {
		return -1;
	}
}

inline int read_inode_data(struct inode *file_inode, struct inode_data *data) {
	memcpy(data, file_inode->addr, sizeof(uint) * 20);
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

	return read_file_by_inode(dir_inode, *entries);
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

inline int is_directory(uint inode) {
	struct inode file_inode;
	read_inode(inode, &file_inode);
	if(inode.flags & 040000 == 0)
		return 0;
	return 1;
}

inline uint file_to_inode(struct V6_file* file) {
	return file->inumber;
}

// inline uint inode_to_file(uint inode, struct V6_file* file) {
// 	//struct inode inode_buf;
// 	//read_inode(inode, &inode_buf);
// 	//return
// }

uint find_directory_in_directory(const char *filename, struct V6_file *spec_dir) {
	uint inode = find_file_in_directory(filename, spec_dir);
	if(is_directory(inode) == 0)
		return -1;
	return inode;
}

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

int list_directory(char **all_filename, struct V6_file *spec_dir) {
	struct file_entry *entries; //allocated in read_directory, you need to free it after use
	int entry_num = 0;
	uint inode = spec_dir->inumber;
	struct inode dir_inode;
	read_inode(inode, &dir_inode);
	read_directory(&dir_inode, &entries, &entry_num);

	*count = entry_num;
	int i = 0;
	for(i = 0; i < entry_num; i++) {
		strcpy(all_filename[i], entries[i].filename, FILENAME_LENGTH);
	}

	return entry_num;
}
