#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<stdlib.h>
#define MaxP 10
#define MaxT 10

void *watch_count(void *r);
int Available[10];
int all[20][20];
int max[20][20];
int need[20][20];

pthread_mutex_t mutex;


int main(){
    //All decleration.
    int n,m;
printf("Enter size of matrix n x m:");
scanf("%d %d",&n,&m);
printf("\n");
printf("Enter values for allocation matrix:");
int i,j;
for(i=0;i<n;i++)
    for(j=0;j<m;j++)
        scanf("%d",&all[i][j]);
        printf("\n");
  printf("Enter values for max demand matrix:");
for(i=0;i<n;i++)
    for(j=0;j<m;j++)
        scanf("%d",&max[i][j]);
       printf("\n");



}
