#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct process{
    int maximum[10];
    int allocated[10];
    int need[10];
}process;

int processNum,resourceNum;

//take the input
void input(process p[processNum],int available[resourceNum]){
    for(int i=0;i<processNum;i++){
        printf("Enter Process[%d] Info",i);
        printf("Enter Maximum need : ");
        for(int j=0;j<resourceNum;j++){
            scanf("%d",&p[i].maximum[j]);
        }
        printf("Enter Number of process allocated for this process ");
        for(int j=0;j<resourceNum;j++){
            scanf("%d",&p[i].allocated[j]);
        }
        for(int j=0;j<resourceNum;j++){
            p[i].need[j]=p[i].maximum[j]-p[i].allocated[j];
        }  
    }
    printf("Enter available resources ");
        for(int j=0;j<resourceNum;j++){
            scanf("%d",&available[j]);
        }
}

bool applySafetyAlgo(process p[processNum],int available[resourceNum],int safeSeq[processNum]){
    bool finish[processNum]={false};
    int work[resourceNum];
    for(int i=0;i<resourceNum;i++){
        work[i]=available[i];
    }
    int k=0;
    bool proceed=true;
    while(proceed){
        proceed=false;
        for(int i=0;i<processNum;i++){
            bool flag=true;
            if(finish[i]==false){
                for(int j=0;j<resourceNum;j++){
                    //need<=work
                    if(work[j]<p[i].need[j]){
                        flag=false;
                        break;
                    }
                }
                if(flag==false){
                    continue;
                }
                //update work
                for(int j=0;j<resourceNum;j++){
                    work[j]+=p[i].allocated[j];
                }
                finish[i]=true;
                safeSeq[k++]=i;
                proceed=true;
            }
        }
    }
    int i=0;
    for(i=0;i<processNum && finish[i]==true ;i++){}
    if(i==processNum)return true;
    else return false;
}

int main(){
    printf("Enter Number of processes : ");
    scanf("%d",&processNum);
    printf("Enter Number of resources : ");
    scanf("%d",&resourceNum);
    int available[resourceNum];
    process p[processNum];
    int safeSeq[processNum];

    printf("Enter details of processes : ");
    
    input(p,available);

    if(applySafetyAlgo(p,available,safeSeq)){
        printf("system is safe");
        for(int i=0;i<processNum;i++){
            printf("%d  ",safeSeq[i]);
        }
        printf("true");
    }else{
        printf("false")
    }
    
    return 0;
}