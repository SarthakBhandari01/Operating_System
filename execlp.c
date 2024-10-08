#include<stdio.h>
#include<unistd.h>

int main(){
    execlp("readDirContent","readDirContent",NULL);
    perror("execlp failed");
}