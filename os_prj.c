 #include <stdlib.h>
 #include <stdio.h>
 #include <pthread.h>
 #include <semaphore.h>

int available[20];
int max1[20][20];
int all[20][20];
int need[20][20];
pthread_mutex_t lock;

  void *customerMethod(void *no_cus1){

      int customer = *(int*)no_cus1;
      bool res_used = false;
     int req [res];
     while(1){
            for(int i = 0; i < res; i++){

                req[i] = rand() % (max1[customer][i] + 1);
                        }
          pthread_mutex_lock(&lock);
        res_used = req_res(customer,req);
            pthread_mutex_unlock(&lock);
            if(res_used){
    printf("This is a safe state\nCustomer: %d got the resources it wanted! The customer will return some in at most 5 seconds.\n\n", customer);
    sleep((int)rand() % 5 + 1);
            res_used = false;
               pthread_mutex_lock(&lock);
             release_res(customer,req);
             pthread_mutex_unlock(&lock);
             //simulate the customer has finished its task.
             if(rand() % 2 == 0){
                    printf("\nCustomer : %d is finished\n", customer);
             for(int i = 0; i < res; i++){
                            need[customer][i] = 0;
             max1[customer][i] = 0;
                          }
            printf("max Needs After the Customer Finished\n");
                for(int i = 0; i < no_cus; i++){
                        for(int j = 0; j < res; j++){
                                printf("%3d ",max1[i][j]);
                        }
                         puts("");
                    }
                            sleep(2);
                            break;
                    }
                }
                sleep(1);
        }
        return 0;
        }

 bool safe(){

     int work[res];
       for(int i = 0; i < res; i++){
                    work[i] = available[i];
       }
    bool finish [no_cus];
            for(int i = 0; i < no_cus; i++){
                    finish[i] = false;
            }

int count = 0;
    int indexFinish = -1;
          int prevFinishIndex = -1;
          bool finishCustomer = true;

       while (count < no_cus){
                prevFinishIndex = indexFinish;

    for(int i = 0; i < no_cus; i++){
        if(!finish[i]){
        for(int j = 0; j < res; j++){
                if (need[i][j] > work[j])
                        finishCustomer = false;
               }
    if(finishCustomer){
           indexFinish = i;
        for(int j = 0; j < res; j++){
                work[j] += all[i][j];

            }
                finish[i] = true;
                count++;
        finishCustomer = true;
        break;
        }
            }
                }

        for(int i = 0; i < no_cus; i++){
        if(!finish[i])
        break;
              }
    if(prevFinishIndex == indexFinish)
         return false;
    }
      return true;
       }

        bool req_res(int n_customer, int req[]){

             printf("\nCustomer: %d reqing Resources\n",n_customer);
                for(int i = 0; i < res; i++){
                printf("%d ",req[i]);
        }
            puts("");

     printf("Available Resources Before\n");
     for(int i = 0; i < res; i++){
                printf("%d ",available[i]);
     }
      puts("");
       for(int i = 0; i < res; i++){
                    if(req[i] <= need[n_customer][i]){
                        if(req[i] > available[i]){
                printf("The system is NOT safe with this req\n\n");
       sleep(1); //used for readability
         return false;
           }
           else{
                printf("testing taking resources\n");
           for(int k = 0; k < res; k++){
                            all[n_customer][k] += req[k];
           available[k] -= req[k];
            need[n_customer][k] -= req[k];
            }
      if(safe()){
        printf("The system is safe with this req\nResources granted\n");
      printf("Available Resources After\n");
          for(int i = 0; i < res; i++){
                printf("%d ",available[i]);
          }
           puts("\n");
        sleep(2);
        return true;
        }
        else{
        printf("The system is not safe with this req\nResources are not granted\n");
        for(int k = 0; k < res; k++){
        available[k] += req[k];
        need[n_customer][k] += req[k];
        all[n_customer][k] -= req[k];
        }
           return false;
                     }
                }
            }
            else{
            printf("Customer: %d is NEEDY\n",n_customer);
            sleep(1);//used for readability
            return false;
            }


     }         return true;  }

 bool release_res(int n_customer, int release[])  {
     printf("\nCustomer: %d Releasing Resources\n", n_customer);
     for(int i = 0; i < res; i++){
    printf("%d ",release[i]);
    available[i] += release[i];
        need[n_customer][i] += release[i];
    all[n_customer][i] -= release[i];
    }

     puts("");
     printf("Available Resources After\n");
     for(int i = 0; i < res; i++){
            printf("%d ",available[i]);
     }
     puts("");
           sleep(2);
                return true;
                 }

int main()  {

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
       for(int i = 0; i < no_cus; i++){
            int *c_num = malloc(sizeof(*c_num));
       if(c_num ==NULL){
            printf("couldn't make customer number");
       exit(1);
         }
         *c_num = i;
         pthread_create(&threads[i],NULL,&customerMethod, c_num);
         }
         for(int i = 0; i < no_cus; i++){
                pthread_join(threads[i],0);
         }
         printf("DONE ALL CUSTOMERS\n");
             pthread_mutex_destroy(&lock);
                       return EXIT_SUCCESS;
 }
