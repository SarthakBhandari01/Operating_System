#include<stdio.h>
#include<limits.h>
#include<stdbool.h>
#include<stdlib.h>
#define and &&
#define or ||
typedef struct process_struct{
    int pid;
    int at;
    int bt;
    int ct,wt,tat,rt,st;
    int bt_remaining;
}process;

int comp(const void * p1,const void *p2){
    int a=((process *)p1)->at;
    int b=((process *)p2)->at;
    if(a<b){
        return -1; //no sorting 
    }else{
        return 1; //sorting 
    }
}

int comp2(const void * p1,const void* p2){
    int a=((process *)p1)->pid;
    int b=((process *)p2)->pid;
    if(a<b){
        return -1;
    }else{
        return 1;
    }
}

int findmax(int a,int b){
    return (a>b)?a:b;    
}

int main(){
    int n;
    printf("Enter number of processes : ");
    scanf("%d",&n);
    float swt=0,stat=0;
    float cu=0,throughPut=0;
    int srt=0;
    process p[100];

    for(int i=0;i<n;i++){
        printf("Process id : %d\t",i);
        p[i].pid=i;
        printf("Enter the value of AT and BT : ");
        scanf("%d %d",&p[i].at,&p[i].bt);
        p[i].bt_remaining=p[i].bt;
    }

    int completed=0;
    int tq=0;
    printf("Enter time qunta : ");
    scanf("%d",&tq);
    //sort structure on the basis of arrival time in ascending order.
    qsort((void *)p,n,sizeof(process),comp);

    int queue[100],f=-1,r=-1;
    bool visited[100]={false},is_first_process=true;

    int index=0;
    int cur_time=0;
    f=r=0;
    queue[r]=0;
    visited[0]=true;
    int totleIdleTime=0;
    while(completed!=n){
        index=queue[f];
        f++;

        if(p[index].bt==p[index].bt_remaining){
            p[index].st=findmax(cur_time,p[index].at);
            totleIdleTime+=(is_first_process==true)?0:p[index].st-cur_time;
            cur_time=p[index].st;
            is_first_process=false;
        }

        if(p[index].bt_remaining-tq>0){
            cur_time+=tq;
            p[index].bt_remaining-=tq;
        }else{
            cur_time+=p[index].bt_remaining;
            p[index].bt_remaining=0;
            completed++;

            p[index].ct=cur_time;
            p[index].rt=p[index].st-p[index].at;
            p[index].tat=p[index].ct-p[index].at;
            p[index].wt=p[index].tat-p[index].bt;
            stat+=p[index].tat;
            swt+=p[index].wt;
            srt+=p[index].rt;
        }

        //check which new process needed to be pushed into queue
        for(int i=1;i<n;i++){
            if(p[i].bt_remaining>0 and p[i].at<=cur_time and visited[i]==false){
                queue[++r]=i;
                visited[i]=true;
            }
        }
        //check if Process on cpu needs to be pushed to ready queue
        if(p[index].bt_remaining>0){
            queue[++r]=index;
        }
        //if queue is empty,just add one process from list whose remaining burst time > 0
        if(f>r){
            for(int i=1;i<n;i++){
                if(p[i].bt_remaining>0){
                    queue[++r]=i;
                    visited[i]=true;
                    break;
                }
            }
        }
    }
    
    int max_completion_time=INT_MIN;
    for(int i=0;i<n;i++){
        max_completion_time=findmax(max_completion_time,p[i].ct);
    }
    int lenCyc=max_completion_time-p[0].at;
    cu=(float)(lenCyc-totleIdleTime)/lenCyc;
    
    //sort so that process comes in original order
    qsort((void *)p,n,sizeof(process),comp2);

    printf("\nprocesss No.\tAT\tBT\tST\tCT\tTAT\tRT \twt\n");
    for(int i=0;i<n;i++){
        printf("  %d\t\t%d\t%d\t%d\t%d\t%d\t%d\t%d \n",p[i].pid,p[i].at,p[i].bt,p[i].st,p[i].ct,p[i].tat,p[i].rt,p[i].wt);
    }
    printf("\n average turn around time : %f",(float)stat/n);
    printf("\n average waiting time: %f",(float)swt/n);
    printf("\n average response time : %f",(float)srt/n);
    printf("\n Throughput : %2f",n/(float)lenCyc);
    printf("\n cpu utilization : %2f",cu*100);
    return 0;
}