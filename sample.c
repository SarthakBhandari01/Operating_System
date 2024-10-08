#include<stdio.h>
#include<stdlib.h>
#include<dirent.h>
int main(){
    struct dirent * dir;
    DIR *d;
    d=opendir(".");
    if(d){
        printf("content of directory : ");
        while((dir=readdir(d))!=NULL){
            printf("\n%s",dir->d_name);
        }
    }else{
        perror("opendir");
    }
    closedir(d);
    return 0;
}