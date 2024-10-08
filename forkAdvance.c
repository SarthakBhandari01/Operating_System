#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

int main(){
    pid_t pid1,pid2;
    pid1=fork();
    if(pid1==0){
        //this block is executed by child process
        printf("child :Listing file in current directory");
        execlp("ls","ls",NULL);
        perror("execlp");
        exit(EXIT_FAILURE);
    }else if(pid1>1){
        //this block is executed by parent process
        pid2=fork();
        if(pid2==0){
            printf("child2 sleeping..");
            sleep(5);
            printf("child2 : sleep complete");
        }else if(pid2>0){
            printf("parent: waiting  for child 1 to finish ..");
            waitpid(pid1,NULL,0);
            printf("child1 is completed");

            printf("parent: waiting  for child 2 to finish ..");
            waitpid(pid2,NULL,0);
            printf("child2 is completed");
        }
    }else{
        perror("fork")
    }
}