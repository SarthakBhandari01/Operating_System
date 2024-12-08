#include<stdio.h>
#include<stdbool.h>

#define and &&
#define or ||
#define max 100000

typedef struct pageTable{
    int frame_no;
    bool valid;
    int last_access_time;
}pageTable;

bool isPagePresent(pageTable pt[],int page){
    if(pt[page].valid){
        return true;
    }else{
        return false;
    }
}

void printFrame(int frame[],int nof){
    for(int i=0;i<nof;i++)
    printf("%d ",frame[i]);
    printf("\n");
}

void findLruPageIndex(pageTable pt[],int frame[],int nof,int * lru){
    int min=max;
    for(int i=0;i<nof;i++){
        if(min > pt[frame[i]].last_access_time){
            min= pt[frame[i]].last_access_time;
            *lru=i;
        }
    }
    return ;
}
int updatePageTable(pageTable pt[],int page,int fr_no,int last_access_time,bool status){
    pt[page].valid=status;
    if(status){
        pt[page].frame_no=fr_no;
        pt[page].last_access_time=last_access_time;
    }
}


int main(){
    int n;
    printf("Enter Number Of Pages  : ");
    scanf("%d",&n);
    int pages[n];
    printf("\n Enter the reference string(different page numbers) : ");
    for(int i=0;i<n;i++){
        scanf("%d",&pages[i]);
    }
    
    int nof;
    printf("Enter Number Of frame  : ");
    scanf("%d",&nof);
    int frame[nof];
    for(int i=0;i<nof;i++){
        frame[i]=-1;
    }

    pageTable pt[50];
    for(int i=0;i<50;i++){
        pt[i].valid=false;
    }

    int pageFault=0;
    int current=0;
    bool full=false;
    for(int i=0;i<n;i++){
        int page=pages[i];
        if (!isPagePresent(pt,page)){
            pageFault++;
            if(full and current<nof){
                updatePageTable(pt,page,current,i,true);
                frame[current]=page;
                printFrame(frame,nof);
                current++;
                if(current==nof){
                    full=true;
                }
            }else{
                int lruPageIndex=-1;
                findLruPageIndex(pt,frame,nof,&lruPageIndex);
                updatePageTable(pt,frame[lruPageIndex],-1,i,false);

                frame[lruPageIndex]=page;
                printFrame(frame,nof);

                //update page table
                updatePageTable(pt,page,lruPageIndex,i,true);
            }
        }
        pt[page].last_access_time=i;
    }
    printf("\nTotal No. of Page Faults = %d\n",pageFault);
    printf("\nPage Fault ratio = %.2f\n",(float)pageFault/n);
    printf("\nPage Hit Ratio = %.2f\n",(float)(n- pageFault)/n);
    return 0;
}