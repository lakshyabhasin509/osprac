#include<stdio.h>
#include <stdlib.h>
struct pr{
	int pid;
	int at;
	int bt;
	int st;
	int ct;
	int tat;
	int wt;
	int rt;
};
int com(const void *p, const void *q)
{
	int l = ((struct pr *)p)->at;
	int r = ((struct pr *)q)->at;
	return (l - r);
}
int main(){
	int n;
	float cycle_time,ideal_time=0;
	printf("enter total process : ");
	scanf("%d",&n);
	struct pr a[n];
	printf("\n enter at and bt :\n");
	for(int i=0;i<n;i++){
		scanf("%d%d",&a[i].at,&a[i].bt);
		a[i].pid=i+1;
	}
	qsort((void*)a, n, sizeof(a[0]), com);
	a[0].ct=a[0].bt;
	a[0].tat=a[0].bt;
	a[0].wt=0;
	a[0].rt=0;
	a[0].st=a[0].at;
	for(int i=1;i<n;i++){
		if(a[i].at<=a[i-1].ct){
			a[i].ct=a[i-1].ct+a[i].bt;
		}
		else{
		     ideal_time = ideal_time + a[i].at-a[i-1].ct;
			a[i].ct=a[i].bt+a[i].at;
		}
		a[i].tat=a[i].ct-a[i].at;
		a[i].st=a[i].ct-a[i].bt;
		a[i].wt=a[i].tat-a[i].bt;
		a[i].rt=a[i].st-a[i].at;	
	}
	float avgwt=0,avgtat=0,avgrt=0;
	printf("pid| at | bt | ct | tat | st | wt | rt |\n");
	for(int i=0;i<n;i++){
		avgwt=avgwt+a[i].wt;
		avgtat=avgtat+a[i].tat;
		avgrt=avgrt+a[i].rt;
		printf("%d | %d | %d | %d | %d | %d | %d | %d |\n",a[i].pid,a[i].at,a[i].bt,a[i].ct,a[i].tat,a[i].st,a[i].wt,a[i].rt);
	}
	cycle_time=a[n-1].ct-a[0].st;
	printf("average waiting time : %f \n average turn around time : %f \n average response time =%f \n ",avgwt/n,avgtat/n,avgrt/n);
	printf(" \nideal time = %f",ideal_time);
	printf(" \nlength cycle = %f",cycle_time);
	float cpu=(cycle_time-ideal_time)/cycle_time * 100;
	printf(" \ncpu utilisation = %f",cpu);
return 0;	
}