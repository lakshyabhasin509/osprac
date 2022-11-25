#include<stdio.h>
#include<stdlib.h>
struct srtf{
	int pid;
	int at;
	int bt;
	int rbt;
	int ct;
	int tat;
	int wt;
	int rt;
	int st;
};
int com(const void *p, const void *q)
{
	int l = ((struct srtf *)p)->at;
	int r = ((struct srtf *)q)->at;
	return (l - r);
}
int main(){
	printf("Jay Upadhyay\n");
	int p;
	int total_idle_time = 0,prev=0;
	float avgwt=0,avgtat=0,avgrt=0;
	printf("enter total process :\n");
	scanf("%d",&p);
	printf("\nenter at and bt: \n");
	struct srtf a[p];
	for(int i=0;i<p;i++){
		a[i].pid=i+1;
		scanf("%d%d",&a[i].at,&a[i].bt);
		a[i].rbt=a[i].bt;
	}
	qsort((void*)a, p, sizeof(a[0]), com);
	int pc=0,i=0;
	while(i<p){
		int k=-1;
		int min=9999999;
		for(int j=0;j<p;j++){
			if(a[j].at<=pc&&a[j].rbt!=0){
			 if(a[j].rbt<min){
				min=a[j].rbt;
				k=j;
			}
			if(a[j].rbt==min){
				if(a[i].at<a[k].at){
				min=a[j].rbt;
				k=j;}
			} 
			}
			}
		if(k!=-1){
			if(a[k].rbt == a[k].bt) {
                a[k].st = pc;
                total_idle_time += a[k].st - prev;
            }
            a[k].rbt -= 1;
            pc++;
            prev = pc;
		 if(a[k].rbt==0){
			a[k].ct=pc;
			i++;
			a[k].tat=a[k].ct-a[k].at;
		    a[k].wt=a[k].tat-a[k].bt;
		    a[k].rt=a[k].st-a[k].at;
		    avgwt=avgwt+a[k].wt;
		    avgrt=avgrt+a[k].rt;
		    avgtat=avgtat+a[k].tat;
		}
	}
	  else{
	  	pc++;
	  }
	}
	printf("pid\tat\tbt\tst\tct\ttat\twt\trt \n");
    for(i=0;i<p;i++){
    	printf("\n%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d",a[i].pid,a[i].at,a[i].bt,a[i].st,a[i].ct,a[i].tat,a[i].wt,a[i].rt);
	}
	printf("\n average waiting time : %f \n average response time : %f \n average tat : %f \n cpu ideal time : %d \n",avgwt/p,avgrt/p,avgtat/p,total_idle_time);
	
	float length_cycle=pc-a[0].at;
	float cpu=(length_cycle-total_idle_time)/length_cycle*100;
	printf("\nlength cycle : %f\n Cpu utilisation: %f\n throughput : %f ",length_cycle,cpu,(float)(p)/(length_cycle));
}