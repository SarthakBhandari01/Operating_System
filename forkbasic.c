#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>

//The getppid function in C returns the parent process ID of the calling process
int main(){
    int pid=fork();
    if(pid>0){
        //this block is executed by the parent process
        printf("process id of parent process %d that creates a child process %d",getpid(),pid);
    }else if(pid==0){
        //this block is executed by the child process
        printf("child process pid %d",getpid());
    }else{ 
        perror("fork failed");
        return 1;
    }
    return 0;
}