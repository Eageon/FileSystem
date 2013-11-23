#include "common.h"
#include "v6util.h"
#define MAX 100


void tokenize(char *string, char *token_list[], int *argc);
//void fork_execute(const char *path, char *const argv[]);
//int status;

char seps[] = " ,\t\n";

int main() {
    while(1) {
        char string[MAX];
        fgets(string, MAX, stdin);
        int length = strlen(string) - 1;
        string[length] = '\0';
        if(strcmp(string, "q") == 0){
           break; 
        }
        char* argv[5];
        int argc;
        tokenize(string, argv, &argc);
        if(argv[0] != '\0') { 
            if(strcmp(argv[0], "cpin") == 0)
                cpin(argc, argv);
            else if(strcmp(argv[0], "initfs") == 0)
                initfs(argc,argv);
            else if(strcmp(argv[0], "cpout") == 0)
                cpout(argc,argv);
            else if(strcmp(argv[0], "mkdir") == 0)
                mkdir1(argc,argv);
            else if(strcmp(argv[0], "ls") == 0)
                ls(argc,argv);
            else {
                printf("Error: unsupported operations!\nThis File System only support cpin, cpout, makdir and ls\n");
            }
        }
     }
     close(curr_fd);
     return 0;
}


void tokenize(char *string, char *token_list[], int *argc)
{
    
    /* Establish string and get the first token: */
    char * token;
    *argc = 0;
    token = strtok(string, seps );
    while( token != NULL )
    {
        /* While there are tokens in "string" */
        token_list[*argc] = token;
        (*argc)++;
        /* Get next token: */
        token = strtok( NULL, seps );
    }
    token_list[(*argc)] = (char*)0; 
}



/*
void fork_execute(const char *path, char *const argv[]){
    int child_pid; 
    if((child_pid = fork()) < 0 )
    {
        perror("fork failure");
        exit(-1);
    }    
    if (child_pid == 0 ) {
        if(execvp(path, argv) != 0) {
            printf("%s faulure\n", argv[0] );
        }
        exit(0);
    }
    else {
        printf("%s are executed!\n", argv[0] );
        if (wait(&status) == -1)
            perror("wait error");                
    }
}
*/
