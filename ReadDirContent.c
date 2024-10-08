#include<stdio.h>
#include<stdlib.h>
#include<dirent.h>
int main(){
    DIR *d;
    d=opendir(".");
    struct dirent * entry;
    if(d){
        while((entry=readdir(d))!=NULL){
            printf("\n%s",entry->d_name);
        }
    }else{
        perror("opendir");
    }
    return 0;
}