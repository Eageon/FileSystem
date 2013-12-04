/*
* Name: Renkai Ji 
* CS4348.HON
*/

I. Purpose
(1)Redesin the file system to remove the file size limitation of Unix V6 file system. You can also redesign superblock, inode, and directory entries.
(2)Design and develp a program called fsaccess which will allow a Unix user access to the modified Unix V6 file system. 


II. File list

inode.c
inode.h
block.c
block.h
file.c
file.h
v6util.c
v6util.h
common.h
fsaccess.c
fsaccess*
Makefile
readme.txt
test-file-in

III.Compiling and Executing on command line

Run on cs1.utdallas.edu or cs2.utdallas.edu Linux System

To compile, run:
make

To execute, run:
./fsaccess

Thereafter, you will go into my file server command line mode. 
This version of File System only support cpin, cpout, makdir together with extra feature ls(buy 3 get 1 free)

To use my file system, input the following command:

(a)initfs diskname number_of_blocks number_of_inode_block
//Initialize the disk by setting all the of the data blocks to free, and set all inode blocks as unallocated. 

(b)cpin external_file_name v6-file
//Create a new file called v6-file in the current directory of the file system 
//and fill the contents of the newly created file with the contents of the external file.

(c)cpout v6-file external_file_name
//If the v6-file exists, create external file and make the external file's contents equal to v6-file.

(d)mkdir v6-dir
// if v6-dir does not exists in the current directory of the file system, create the directory 
// and set its first two entries . and .. 

(e)ls
//list all files and directories in current directory.

(f)q
//save all changes and quit.

IV. Sample output

>>>initfs ./disk 1000 300
>>>ls
.       ..
>>>cpin test-file-in v6-file
>>>ls
.       ..      v6-file
>>>cpout v6-file test-file-out
>>>ls
.       ..      v6-file
>>>mkdir v6-dir
>>>ls
.       ..      v6-file v6-dir
>>>q

After quit this program, you will see that an external file named "test-file-out" was created,
and its contents are equal to v6-file and hence equal to the file "test-file-in".

