#include<stdio.h>
#include<string.h>
#include <stdbool.h>

#define and &&
#define or ||

typedef struct pageTable{
    int frame_no;
    bool valid;
}pageTable;

void updatePageTable(pageTable pt[],int page,int f_no,int status){
    pt[page].valid=status; 
    pt[page].frame_no=f_no; 
}

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

int main(){
    int n;
    printf("Enter Number Of Pages  : ");
    scanf("%d",&n);
    int refrence_string[n];
    printf("\n Enter the reference string(different page numbers) :\n");
    for(int i=0;i<n;i++){
        scanf("%d",&refrence_string[i]);
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
        int page=refrence_string[i];
        if(!isPagePresent(pt,page)){ //if not present 
            pageFault++;
            if(full and current<nof){

                frame[current]=page;
                printFrame(frame,nof);
                updatePageTable(pt,page,current,true);
                current++;

                if(current==nof){
                    current=0;
                    full=true;
                }
            }else{ // frame is full ,apply fifo
                updatePageTable(pt,frame[current],-1,false);
                frame[current]=page;
                printFrame(frame,nof);
                updatePageTable(pt,page,current,true);
                current=(current+1)%nof;
            }
        }
    }
    printf("\nTotal No. of Page Faults = %d\n",pageFault);
    printf("\nPage Fault ratio = %.2f\n",(float)pageFault/n);
    printf("\nPage Hit Ratio = %.2f\n",(float)(n- pageFault)/n);
    return 0;
}