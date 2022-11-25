#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
struct rr
{
    int pid , at , bt , st , ct , tat , wt , rt , rem_bt ;
};
int com(const void *p,const void *q){
    int l=((struct rr*)p)->at;
    int r=((struct rr*)q)->at;
    return (l-r) ;
}
int findMax(int a,int b)
{
    return a>b?a:b;
}
int main()
{
    int n , i , q ;
    printf("Enter No. of Process : ");
    scanf("%d",&n) ;
    struct rr p[n] ;
    printf("Enter Pid AT BT \n");
    for(i=0;i<n;i++)
    {
        scanf("%d%d%d",&p[i].pid,&p[i].at,&p[i].bt);
        p[i].rem_bt = p[i].bt ;
    }
    printf("Enter Time Quanta : ");
    scanf("%d",&q) ;
    int queue[100] ;
    int front , rear ;
    int visited[100] = {0} ;
    front = rear = 0 ;
    qsort(p,n,sizeof(p[0]),com) ;
    printf("\n");
    int curr_time = 0 , completed = 0 ;
    queue[rear] = 0 ;
    visited[0] = 1;
    int ind ;
    while(completed!=n)
    {
        
        ind = queue[front] ;  
        front++ ;
        if(p[ind].rem_bt == p[ind].bt)
        {
            p[ind].st = findMax(curr_time,p[ind].at) ;
            curr_time = p[ind].st ;
        }
        if(p[ind].rem_bt - q >0)
        {
            p[ind].rem_bt -= q ;
            curr_time += q ;
        }
        else
        {
            int t = p[ind].rem_bt ;
            p[ind].rem_bt -= t ;
            curr_time += t ;
            completed ++ ;
            p[ind].ct = curr_time ; 
            p[ind].tat = p[ind].ct - p[ind].at ; 
            p[ind].wt  = p[ind].tat - p[ind].bt ; 
            p[ind].rt  = p[ind].st - p[ind].at ;
        }
        for(i=1;i<n;i++)
        {
            if(p[i].rem_bt>0 && p[i].at<=curr_time && visited[i]==0)
            {
                queue[++rear] = i ;
                visited[i] = 1 ;
            }
        }
        if(p[ind].rem_bt>0) // if not finished push it to queue 
        {
            queue[++rear] = ind ;
        }
        if(front>rear) // if queue is Empty
        {
            for(i=1;i<n;i++)
            {
                if(p[i].rem_bt>0)
                {
                    queue[++rear] = i ;
                    visited[i] = 1 ;
                    break ;
                }
            }
        }
    }
    printf("Pid\tAT\tBT\tCT\tTAT\tWT\tRT\n");
    int avgtat=0,avgwt=0,avgrt=0;
    for(i=0;i<n;i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",p[i].pid,p[i].at,p[i].bt,p[i].ct,p[i].tat,p[i].wt,p[i].rt) ;
        avgtat+=p[i].tat;
        avgwt+=p[i].wt;
        avgrt+=p[i].rt;
    }
    printf("\nAvg tat : %f ",(float)avgtat/n);
    printf("\nAvg wt : %f ",(float)avgwt/n);
    printf("\nAvg rt : %f ",(float)avgrt/n);
    printf("\ncycle time : %f",curr_time-p[0].at);
    printf("\nthroughtput : %.2f ",(float)n/curr_time);
    return 0 ;
}