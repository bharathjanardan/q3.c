#include<stdio.h>
#include<conio.h>

int rd_que[20];

struct Process_Structure
{
	int arr_time;   //arrival time
	int burst_time;   //burst time
	int flag;	  //flag to see whther the process is terminated or not; 1=not processed, 0= processed
	int pid;
	int comp_time;   //completion time
};

void swap(struct Process_Structure proc[], int k, int l) //To swap all the process elements
{
	int temp;
		
	temp = proc[k].pid; 
	proc[k].pid = proc[l].pid;
	proc[l].pid = temp;
	
	temp = proc[k].burst_time; 
	proc[k].burst_time = proc[l].burst_time;
	proc[l].burst_time = temp;
	
	temp = proc[k].arr_time; 
	proc[k].arr_time = proc[l].arr_time;
	proc[l].arr_time = temp;
	
	temp = proc[k].comp_time; 
	proc[k].comp_time = proc[l].comp_time;
	proc[l].comp_time = temp;
	
	temp = proc[k].flag;
	proc[k].flag = proc[l].flag;
	proc[l].flag = temp;
} //end of function

void sort_burst(struct Process_Structure proc[], int n) //To sort the processes accordin to burst time
{	
	int i, j, min;
	for(i = 0; i < n; i++)
	{
		min = proc[i].burst_time;
		for(j = i+1; j < n; j++)
		{
			if(proc[j].burst_time <= min)
			{
				min = proc[j].burst_time;
				swap(proc, i, j);
			}		
		}
		rd_que[i] = proc[i].pid;		
	}
} //end of function

void sort_comp(struct Process_Structure proc[], int n) //To sort processes according to completion time
{	
	int i, j, min;
	for(i = 0; i < n; i++)
	{
		min = proc[i].comp_time;
		for(j = i+1; j < n; j++)
		{
			if(proc[j].comp_time <= min)
			{
				min = proc[j].comp_time;
				swap(proc, i, j);
			}		
		}
		rd_que[i] = proc[i].pid;		
	}
} //end of function


int main()
{
	int time = 0, checker = 0, Tot_TAT = 0 , Tot_Wait = 0;
	int i, j, k = 1, n, min, temp, wait_time, TAT_time, burst_rep[20],len=0;
	struct Process_Structure P[20],Q[20];
	printf("\nEnter the number of processes : ");
	scanf("%d",&n);
	for(i=0;i<n;i++)
	{
		printf("\nEnter the arrival time of P[%d] : ",i);
		scanf("%d",&P[i].arr_time);
		printf("\nEnter the burst time of P[%d] : ",i);
		scanf("%d",&P[i].burst_time);
		P[i].pid=i;		
		P[i].flag=1;
		P[i].comp_time=0;
	}
	j=0;
	
	for(i = 0;i<n;i++)
	{
		if(P[i].arr_time == 0)
		{
			printf("\nArrival Time is 0, so element discarded");
			P[i].arr_time = -1;
			len++;
		}
		else
		{	
			Q[j].arr_time = P[i].arr_time;
			Q[j].burst_time = P[i].burst_time;
			Q[j].pid = P[i].pid;
			Q[j].comp_time = P[i].comp_time;
			Q[j].flag = P[i].flag;
			burst_rep[j] = P[i].burst_time;
			checker++;
			rd_que[j] = P[i].pid;
			j++;
		}
	}
	
	n = n-len;
	
	for(i =0;i<n; i++)
	{
		min = Q[i].arr_time;
		for(j=i+1; j<n; j++)
		{
			if(Q[j].arr_time <= min)
			{
				min = Q[j].arr_time;
				swap(Q,i,j);
			}
		}
		rd_que[i] = Q[i].pid;
	}
	
	while(checker != 0)
	{
		for(j = 0; j < n; j++)
		{		
			if(j==0)	
			{
				time = time + Q[j].burst_time;
			}
			else
			{
				time = time + Q[j].burst_time;
			}
			Q[j].burst_time -= Q[j].burst_time;
			if(Q[j].burst_time == 0)
			{
				Q[j].comp_time = time;
				time += 2;
				--checker;
			}
			sort_burst(Q,n);
		}
	}
	
	if(checker == 0)
	{
		sort_comp(Q,n);
		printf("\n\n\t!!! The Processes have Completed their Execution !!!\n\n");
	}
	
	printf("\n\t==============================================================================\n");
	printf("\t Process \t Completion Time \t Turn Around Time \t Waiting Time");
	printf("\n\t==============================================================================\n");
	for(i = 0; i < n; i++)
	{
		TAT_time = Q[i].comp_time - Q[i].arr_time;
		if(TAT_time >= 0)
		Tot_TAT += TAT_time;
		wait_time = TAT_time - burst_rep[(rd_que[i])];
		if(wait_time >= 0)
		Tot_Wait += wait_time;
		printf("\t    %d \t\t      %d \t\t       %d \t%\t     %d",rd_que[i],Q[i].comp_time,TAT_time,wait_time);
		printf("\n\n");
	}
	
	printf("\n\tAverage Turn around Time is : %.2f",((float)Tot_TAT/n));
	printf("\n\tAverage Waiting Time is     : %.2f",((float)Tot_Wait/n));
	
	return 0;	
}
