#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
typedef struct Process{
    int pid;
    int at;
    int bt;
    int ct;
    int tat;
    int wt;
    int rt;
    int st;
}Process;

int compare(const void* p1,const void* p2){
    int a=((Process *)p1)->at;
    int b=((Process *)p2)->at;
    if(a<b){
        return -1; //no sorting 
    }else{
        return 1; //sorting
    }
}
int findMax(int a,int b){
    return (a>b)?a:b;
}

int main(){
    int n;
    printf("Enter number of processes : ");
    scanf("%d",&n);
    float swt=0,stat=0;
    float cu=0,throughPut=0;
    int srt=0;
    int sbt=0;
    Process p[100];

    for(int i=0;i<n;i++){
        printf("Process id : %d\t",i);
        p[i].pid=i;
        printf("Enter the value of AT and BT : ");
        scanf("%d %d",&p[i].at,&p[i].bt);
    }
    qsort((void *)p,n,sizeof(Process),compare);

    for(int i=0;i<n;i++){
        if(i==0){
            p[i].ct=p[i].at+p[i].bt;
        }else if(p[i].at>=p[i-1].ct){
            p[i].ct=p[i].at+p[i].bt;
        }else{ // p[i].at<p[i-1].ct
            p[i].ct=p[i].bt+p[i-1].ct;
        }
        p[i].tat=p[i].ct-p[i].at;
        p[i].wt=p[i].tat-p[i].bt;
        p[i].rt=p[i].wt;
        p[i].st=p[i].rt+p[i].at;
        swt+=p[i].wt;
        stat+=p[i].tat;
        sbt+=p[i].bt;
        srt+=p[i].rt;
    }
    //totalTime = max completion time
    int maxCompletionTime=INT_MIN;
    for(int i=0;i<n;i++){
        maxCompletionTime=findMax(maxCompletionTime,p[i].ct);
    }
    cu=((float)sbt/maxCompletionTime)*100;
    throughPut=(float)n/maxCompletionTime;

    printf("\nprocesss No.\tAT\tBT\tST\tCT\tTAT\tRT \twt\n");
    for(int i=0;i<n;i++){
        printf("  %d\t\t%d\t%d\t%d\t%d\t%d\t%d\t%d \n",p[i].pid,p[i].at,p[i].bt,p[i].st,p[i].ct,p[i].tat,p[i].rt,p[i].wt);
    }
    printf("\n average turn around time : %f",(float)stat/n);
    printf("\n average waiting time: %f",(float)swt/n);
    printf("\n average response time : %f",(float)srt/n);
    printf("\n Throughput : %f",throughPut);
    printf("\n cpu utilization : %f %",cu);
    return 0;
}