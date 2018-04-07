 #include <stdlib.h>
 #include <stdio.h>
 #include <pthread.h>
 #include <semaphore.h>
#define res 10
#define no_cus 10
int available[20];
int max1[20][20];
int all[20][20];
int need[20][20];
pthread_mutex_t lock;

  void *customerMethod(void *no_cus1){

      int customer = *(int*)no_cus1;
      int i,j;
      int res_used = 0;
     int req [res];
     while(1){
            for(i = 0; i < res; i++){

                req[i] = rand() % (max1[customer][i] + 1);
                        }
          pthread_mutex_lock(&lock);
        res_used = req_res(customer,req);
            pthread_mutex_unlock(&lock);
            if(res_used){
    printf("This is a safe state\nCustomer: %d got the resources it wanted! The customer will return some in at most 5 seconds.\n\n", customer);
    //((int)rand() % 5 + 1);
            res_used = 0;
               pthread_mutex_lock(&lock);
             release_res(customer,req);
             pthread_mutex_unlock(&lock);
             //simulate the customer has finished its task.
             if(rand() % 2 == 0){
                    printf("\nCustomer : %d is finished\n", customer);
             for(i = 0; i < res; i++){
                            need[customer][i] = 0;
             max1[customer][i] = 0;
                          }
            printf("max Needs After the Customer Finished\n");
                for(i = 0; i < no_cus; i++){
                        for(j = 0; j < res; j++){
                                printf("%3d ",max1[i][j]);
                        }
                         puts("");
                    }
                            //sleep(2);
                            break;
                    }
                }
                //sleep(1);
        }
        return 0;
        }

 int safe(){

     int work[res],i,j;
       for(i = 0; i < res; i++){
                    work[i] = available[i];
       }
    int finish [no_cus];
            for(i = 0; i < no_cus; i++){
                    finish[i] = 0;
            }

int count = 0;
    int indexFinish = -1;
          int prevFinishIndex = -1;
          int finishCustomer = 1;

       while (count < no_cus){
                prevFinishIndex = indexFinish;

    for(i = 0; i < no_cus; i++){
        if(!finish[i]){
        for(j = 0; j < res; j++){
                if (need[i][j] > work[j])
                        finishCustomer = 0;
               }
    if(finishCustomer){
           indexFinish = i;
        for(j = 0; j < res; j++){
                work[j] += all[i][j];

            }
                finish[i] = 1;
                count++;
        finishCustomer = 1;
        break;
        }
            }
                }

        for(i = 0; i < no_cus; i++){
        if(!finish[i])
        break;
              }
    if(prevFinishIndex == indexFinish)
         return 0;
    }
      return 1;
       }

int req_res(int n_customer, int req[]){
int i,k;
             printf("\nCustomer: %d reqing Resources\n",n_customer);
                for( i = 0; i < res; i++){
                printf("%d ",req[i]);
        }
            puts("");

     printf("Available Resources Before\n");

     for(i = 0; i < res; i++){
                printf("%d ",available[i]);
     }
      puts("");
       for(i = 0; i < res; i++){
                    if(req[i] <= need[n_customer][i]){
                        if(req[i] > available[i]){
                printf("The system is NOT safe with this req\n\n");
       //sleep(1);
         return 0;
           }
           else{
                printf("testing taking resources\n");
           for(k = 0; k < res; k++){
                            all[n_customer][k] += req[k];
           available[k] -= req[k];
            need[n_customer][k] -= req[k];
            }
      if(safe()){
        printf("The system is safe with this req\nResources granted\n");
      printf("Available Resources After\n");
          for(i = 0; i < res; i++){
                printf("%d ",available[i]);
          }
           puts("\n");
        //sleep(2);
        return 1;
        }
        else{
        printf("The system is not safe with this req\nResources are not granted\n");
        for(k = 0; k < res; k++){
        available[k] += req[k];
        need[n_customer][k] += req[k];
        all[n_customer][k] -= req[k];
        }
           return 0;
                     }
                }
            }
            else{
            printf("Customer: %d is NEEDY\n",n_customer);
            //sleep(1);
                   return 0;
            }


     }         return 1;  }

 int release_res(int n_customer, int release[])  {
     int i;
     printf("\nCustomer: %d Releasing Resources\n", n_customer);
     for(i = 0; i < res; i++){
    printf("%d ",release[i]);
    available[i] += release[i];
        need[n_customer][i] += release[i];
    all[n_customer][i] -= release[i];
    }

     puts("");
     printf("Available Resources After\n");
     for( i = 0; i < res; i++){
            printf("%d ",available[i]);
     }
     puts("");
           //sleep(2);
                return 1;
                 }

int main()  {
int i,j,n,m;
    printf("Enter size of matrix n x m:");
scanf("%d %d",&n,&m);
printf("\n");
printf("Enter values for allocation matrix:");
for(i=0;i<n;i++)
    for(j=0;j<m;j++)
        scanf("%d",&all[i][j]);
        printf("\n");
  printf("Enter values for max demand matrix:");
for(i=0;i<n;i++)
    for(j=0;j<m;j++)
        scanf("%d",&max1[i][j]);
       printf("\n");

     pthread_t threads[no_cus];
     pthread_mutex_init(&lock, NULL);
      srand(time(NULL));
       //make all the customers
       int *c_num = malloc(sizeof(int)*no_cus);
       for(i = 0; i < no_cus; i++){

         *(c_num+i) = i;
         pthread_create(&threads[i],NULL,&customerMethod,(void *)(c_num+i));
         }
         for(i = 0; i < no_cus; i++){
                pthread_join(threads[i],0);
         }
         printf("DONE ALL CUSTOMERS\n");
             pthread_mutex_destroy(&lock);
                       return EXIT_SUCCESS;
 }
