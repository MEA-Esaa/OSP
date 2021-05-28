#include <stdio.h>
#include <stdlib.h>
void print_table(char **pn,int at[],int et[],int p[],int totaltm,int totaltime,int n)
{
    int i;

    puts("+-----+------------+--------------+-----------------+-----------------+-----------------+");
    puts("| PID | arrival time  | execution time | priority Time | waiting time |total time");
    puts("+-----+------------+--------------+-----------------+-----------------+-----------------+");

    for(i=0; i<n; i++) {
        printf("| %2s  |     %2d     |      %2d      |        %2d       |     %2d     |     %2d     |\n"
               , pn+i*10, at[i], et[i], p[i],totaltm,totaltime);
        puts("+-----+------------+--------------+-----------------+-----------------+-----------------+");
    }

}

void print_gantt_chart(char **pn,int et[], int n)
{
    int i, j,k=0;
    // print top bar
    printf(" ");
    for(i=0; i<n; i++) {
        for(j=0; j<et[i] -1; j++) printf("--");
        printf(" ");
    }
    printf("\n|");

    // printing process id in the middle
    for(i=0; i<n; i++) {
        for(j=0; j<et[i] - 1; j++) printf(" ");
        printf("%s", pn+i*10);
        for(j=0; j<et[i] - 1; j++) printf(" ");
        printf("|");
    }
    printf("\n ");
    // printing bottom bar
    for(i=0; i<n; i++) {
        for(j=0; j<et[i]; j++) printf("--");
        printf(" ");
    }
    printf("\n");

    // printing the time line
    printf("0");
    for(i=0; i<n; i++) {
            k=k+et[i];
        for(j=0; j<et[i]; j++) printf("  ");

        if(et[i] > 9) printf("\b"); // backspace : remove 1 space
        printf("%d", k);

    }
    printf("\n");

}
int main()
{
    int et[20],at[10],n,i,j,temp,p[10],st[10],ft[10],wt[10],ta[10];
    int totwt=0,totta=0;
    float awt,ata;
    char *pn[10][10],t[10];

    printf("Enter the number of process:");
    scanf("%d",&n);
    for(i=0; i<n; i++)
    {
        printf("Enter process name,arrival time,burst time & priority:");

        scanf("%s%d%d%d",pn[i],&at[i],&et[i],&p[i]);
    }
    for(i=0; i<n; i++)
        for(j=0; j<n; j++)
        {
            if(p[i]<p[j])
            {
                temp=p[i];
                p[i]=p[j];
                p[j]=temp;
                temp=at[i];
                at[i]=at[j];
                at[j]=temp;
                temp=et[i];
                et[i]=et[j];
                et[j]=temp;
                strcpy(t,pn[i]);
                strcpy(pn[i],pn[j]);
                strcpy(pn[j],t);
            }
        }
    for(i=0; i<n; i++)

    {

        if(i==0)
        {
            st[i]=at[i];
            wt[i]=st[i]-at[i];
            ft[i]=st[i]+et[i];
            ta[i]=ft[i]-at[i];
        }
        else
        {
            st[i]=ft[i-1];
            wt[i]=st[i]-at[i];
            ft[i]=st[i]+et[i];
            ta[i]=ft[i]-at[i];
        }
        totwt+=wt[i];
        totta+=ta[i];
    }

    awt=(float)totwt/n;
    ata=(float)totta/n;
    printf("\nPname\tarrival time\texecution time\tpriority\twaiting time\ttatime");
    for(i=0; i<n; i++)
        printf("\n%s\t%5d\t\t%5d\t\t%5d\t\t%5d\t\t%5d",pn[i],at[i],et[i],p[i],wt[i],ta[i]);
    printf("\nAverage waiting time is:%f",awt);
    printf("\nAverage turnaroundtime is:%f\n",ata);
    print_table(pn,at,et,p,totwt,totta,n);
    printf("\n");




    print_gantt_chart(pn,et,n);



    return 0;
}
