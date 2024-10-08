#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<stdbool.h>

#define and &&
#define or ||

typedef struct Process {
    int pid;
    int at;
    int bt;
    int ct;
    int tat;
    int wt;
    int rt;
    int st;
    int bt_remaining;
  }
Process;

int findMin(int a, int b) {
  return (a < b) ? a : b;
}

int findMax(int a, int b) {
  return (a > b) ? a : b;
}

int main() {
  int n;
  printf("Enter number of processes : ");
  scanf("%d", & n);
  float swt = 0, stat = 0;
  float cu = 0, throughPut = 0;
  int srt = 0;
  int sbt = 0;
  Process p[100];

  for (int i = 0; i < n; i++) {
    printf("Process id : %d\t", i);
    p[i].pid = i;
    printf("Enter the value of AT and BT : ");
    scanf("%d %d", & p[i].at, & p[i].bt);
    p[i].bt_remaining=p[i].bt;
  }

  int completed = 0, cur_time = 0;
  bool isCompleted[100] = {false}, is_first_process = true;
  int prev = 0;
  int totalIdleTime = 0;
  while (completed != n) {
    int minIdx = -1;
    int min = INT_MAX;
    
    for (int i = 0; i < n; i++) {
      if (cur_time >= p[i].at and isCompleted[i] == false) {
        if (min > p[i].bt_remaining) {
          min = p[i].bt_remaining;
          minIdx = i;
        }
        if (min == p[i].bt_remaining) {
          if (p[i].at < p[minIdx].at) {
            minIdx = i;
            min = p[i].bt_remaining;
          }
        }
      }
    }
    if (minIdx == -1) {
      cur_time++;
    } else {
      if (p[minIdx].bt_remaining == p[minIdx].bt) {
        p[minIdx].st = cur_time;
        totalIdleTime += (is_first_process == true) ? 0 : (p[minIdx].st - prev);
        is_first_process = false;
      }
      p[minIdx].bt_remaining-=1;
      cur_time+=1;
      prev = cur_time;
      if (p[minIdx].bt_remaining == 0) {
        p[minIdx].ct = cur_time;
        p[minIdx].tat = p[minIdx].ct - p[minIdx].at;
        p[minIdx].wt = p[minIdx].tat - p[minIdx].bt;
        p[minIdx].rt = p[minIdx].st - p[minIdx].at;

        srt += p[minIdx].rt;
        swt += p[minIdx].wt;
        stat += p[minIdx].tat;

        completed++;
        isCompleted[minIdx] = true;
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
  cu=(float)(lenCyc-totalIdleTime)/lenCyc;
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