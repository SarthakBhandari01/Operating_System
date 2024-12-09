#include<stdio.h>
#include<stdbool.h>
#include<math.h>

int fun(int req[],int diskSize,int head,int n){
    for(int i=0;i<n;i++){
        for(int j=0;j<n-i-1;j++){
            if(req[j]>req[j+1]){
                int temp=req[j];
                req[j]=req[j+1];
                req[j+1]=temp;
            }
        }
    }
   
    int ptr=0; 
    while( ptr<n && head>req[ptr]){
        ptr++;
    }
    printf("ptr %d\n",ptr);
    int res=0;
    for(int i=ptr;i<n;i++){
        res+=abs(head-req[i]);
        head=req[i];
    }
    res+=abs(diskSize-1-head);
    head=diskSize-1;

    for(int i=ptr-1;i>=0;i--){
        res+=abs(head-req[i]);
        head=req[i];
    }
    return res;
}
int main(){
    int diskSize=200;

    int n;
    printf("Enter number of disk requests: ");
    scanf("%d",&n);

    int request[100];
    for(int i=0;i<n;i++){
        scanf("%d",&request[i]);
    }

    int ipos;
    printf("Enter the initial position of the head: ");
    scanf("%d",&ipos);

    int totalSeek=fun(request,diskSize,ipos,n);

     printf("Total seek movement: %d\n", totalSeek);
    return 0;
}