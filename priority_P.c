#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<stdbool.h>
#define and &&
#define or ||
typedef struct Process{
    int pid;
    int at;
    int bt;
    int ct;
    int tat;
    int wt;
    int rt;
    int st;
    int priority;
    int bt_remaining;
}Process;

int findMin(int a,int b){
    return (a<b)?a:b; 
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
        scanf("%d %d %d",&p[i].at,&p[i].bt,&p[i].priority);
        p[i].bt_remaining=p[i].bt;
    }

    int completed=0;
    int cur_time=0;
    bool isCompleted[100]={false},isFirstProcess=true;
    int totleIdleTime=0,prev=0;
    while(completed!=n){
        int max=-1;
        int maxIdx=-1;
        for(int i=0;i<n;i++){
            if(isCompleted[i]==false and p[i].at<=cur_time){
                if(max<p[i].priority){
                    max=p[i].priority;
                    maxIdx=i;
                }
                if(max==p[i].priority){
                   if(p[i].at<p[maxIdx].at){
                        max=p[i].priority;
                        maxIdx=i;
                   }
                }
            }
        }
        if(maxIdx==-1){
            cur_time++;
        }else{
            if(p[maxIdx].bt==p[maxIdx].bt_remaining){
                p[maxIdx].st=cur_time;
                totleIdleTime+=(isFirstProcess==true)?0:(p[maxIdx].st-prev);
                isFirstProcess=false;
            }
            
            p[maxIdx].bt_remaining--;
            cur_time++;
            prev=cur_time;
            
            if(p[maxIdx].bt_remaining==0){
                p[maxIdx].ct=cur_time;
                p[maxIdx].tat = p[maxIdx].ct - p[maxIdx].at;
                p[maxIdx].wt = p[maxIdx].tat - p[maxIdx].bt;
                p[maxIdx].rt = p[maxIdx].st - p[maxIdx].at;

                srt += p[maxIdx].rt;
                swt += p[maxIdx].wt;
                stat += p[maxIdx].tat;

                completed++;
                isCompleted[maxIdx]=true;
            }
        }   
    }
    
  //calculating length of process completion cycle
  int max_completion_time=INT_MIN;
  int max_arr_time=INT_MAX;
  for(int i=0;i<n;i++){
    max_completion_time=findMax(max_completion_time,p[i].ct);
    max_arr_time=findMin(max_arr_time,p[i].at);
  }
  int lenCyc=max_completion_time-max_arr_time;
  cu=(float)(lenCyc-totleIdleTime)/lenCyc;
  throughPut=(float)n/lenCyc;

    printf("\nprocesss No.\tAT\tBT\tST\tCT\tTAT\tRT \twt\n");
    for(int i=0;i<n;i++){
        printf("  %d\t\t%d\t%d\t%d\t%d\t%d\t%d\t%d \n",p[i].pid,p[i].at,p[i].bt,p[i].st,p[i].ct,p[i].tat,p[i].rt,p[i].wt);
    }
    printf("\n average turn around time : %f",(float)stat/n);
    printf("\n average waiting time: %f",(float)swt/n);
    printf("\n average response time : %f",(float)srt/n);
    printf("\n Throughput : %f",throughPut);
    printf("\n cpu utilization : %f %",cu*100);
    return 0;
}