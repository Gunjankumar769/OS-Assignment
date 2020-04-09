   #include<stdio.h>
#include<stdlib.h>
typedef struct
{

    int arr_time,bur_time,que;
    int process_id;
}process;

int main()
{
    int size,quantum,done =0;//Number of processes
    int count = 0;
    int time,smallest,waiting_time[50],turnaround_time[50],completion[50],temp_burst[50];
    double average_waiting,average_turnaround;
    printf("\nEnter the number of processes:");
    scanf("%d",&size);
    process no[size];
    for(int i = 0; i < size; i++)
	{
		printf("\nProcess ID:\t");
		scanf("%d", &no[i].process_id);
		printf("Arrival Time:\t");
		scanf("%d", &no[i].arr_time);
		printf("Burst Time:\t");
		scanf("%d", &no[i].bur_time);
		printf("Queue1/Queue2(1/2):\t");
		scanf("%d", &no[i].que);
	}
	printf("\nEnter the time quantum for Round Robin:");
	scanf("%d",&quantum);
    for(int i=0;i<size;i++)
    {
        temp_burst[i] = no[i].bur_time;//storing the burst time in a array for  further use.
    }

    no[size+1].bur_time = 999;//  assign a max burst for comparison

    for(time=0;count!=size;time++) // shortest remaining time first scheduling
    {
         smallest = size+1;
         for(int i=0;i<size;i++)
         {
            if(no[i].arr_time<=time && no[i].bur_time<no[smallest].bur_time && no[i].bur_time>0 && no[i].que == 1)
            {
                smallest=i;
            }
         }

         if(count >= size/2) //round robin scheduling
          {
            while(1)
            {
              for(int j=0;j<size;j++)
              {
                  if(no[j].arr_time<=time && no[j].bur_time > quantum && no[j].que == 2 )
                  {
                      no[j].bur_time -= quantum;
                      smallest = j;
                  }
                  else if(no[j].arr_time<=time && no[j].bur_time < quantum && no[j].que == 2)
                  {
                      no[j].bur_time = 0;
                      smallest = j;
                      goto a;
                  }
              }
            }
          }

        no[smallest].bur_time--; //decrementing  the burst time

        a: if(no[smallest].bur_time == 0)
         {
            count++;
            completion[smallest] = time+1;
            turnaround_time[smallest] = completion[smallest] - no[smallest].arr_time;
            waiting_time[smallest] = turnaround_time[smallest] - temp_burst[smallest];
         }
    }
    printf("\n\nProcess Id\tArrival Time\t Burst Time\t Waiting Time\tTurnaround Time");
    for(int i=0;i<size;i++)
    {
        printf("\n   P%d   \t\t%d\t\t%d  \t\t%d\t\t%d",no[i].process_id,no[i].arr_time,temp_burst[i],waiting_time[i],turnaround_time[i]);
        average_waiting += waiting_time[i];
        average_turnaround += turnaround_time[i];
    }
    printf("\n\nAverage waiting time = %lf\n",average_waiting/size);
    printf("Average Turnaround time = %lf",average_turnaround/size);

}

