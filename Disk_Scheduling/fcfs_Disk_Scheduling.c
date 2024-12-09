#include<stdio.h>
#include<stdbool.h>
#include<math.h>

int main(){
    int n;
    printf("\n Enter the no. of cylinders in Request queue: ");
    scanf("%d",&n);

    int request_queue[50];
    printf("\n Enter the cylinders no. in Request queue :\n");
    for(int i=0;i<n;i++){
        scanf("%d",&request_queue[i]);
    }
    
    int ipos;
    printf("\n Enter the initial Position of RW head: ");
    scanf("%d",&ipos);

    int totalHeadMovement=0;
    for(int i=0;i<n;i++){
        totalHeadMovement+=abs(ipos-request_queue[i]);
        ipos=request_queue[i];
    }
    
    printf("\nTotal No. of Head Movements = %d\n",totalHeadMovement);
    printf("\nAverage head movements = %.2f\n",(float)totalHeadMovement/n);
    return 0;
}