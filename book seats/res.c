
#include "res.h"

void *book_seats(void *var);

int check_seats(int **zone , int n , int seats , int id);



int check_seats(int **zone , int n , int seats , int id){

    
   
        for (int i = 0; i < n; i++){
            int check_available_seats = 0;
            for (int j = 0; j < 10; j++){
                if (zone[i][j] == 0){
                    ++check_available_seats;
                    if (check_available_seats == seats){
                        int count = 0;
                        row = i+1;
                        for (int a = j; a > j - seats ; a--){
                            
                            zone[i][a] = id;
                            
                          //  booked_seats[count] = a;
                           
                            
                            count++;
                            
                        }
                    
                        printf("\n");
                        
                        return 1;
                        
                    }
                }
            }
        }
        
        return 0;
}


void *book_seats(void *var){
    int seats;
    bool canceled = false;
    struct timespec start_anamonis;
    struct timespec finish_anamonis;

    struct timespec start_eksipiretisis;
    struct timespec finish_eksipiretisis;

    double xronos_eksipiretisis , xronos_anamonis;

    int id = *(int*) var;
    int cost;


    rc = pthread_mutex_lock(&lock_tel);
    if (rc!=0){
        printf("Error on mutex .");
    }

    clock_gettime(CLOCK_REALTIME,&start_anamonis);


    printf ("---------------H kratisi me arithmo %d kataxorithike\n", id);

    while (tel == 0){
        printf("H kratisi me arithmo %d einai se anamoni mexri na vrethei diathesimos tilefonitis. . . .\n",id);
        rc = pthread_cond_wait(&lock_cond1,&lock_tel);
        if (rc!=0){
            printf("Error on condition wait .");
        }    
    }
    tel--;

    clock_gettime(CLOCK_REALTIME,&start_eksipiretisis);

    pthread_mutex_unlock(&lock_tel);

    int epilogi_zonis = rand_r(&seed)%100; // epilogi zonis

    seats = rand_r(&seed)%Nseathigh + Nseatlow;// epilogi thesewn

    int time = rand_r(&seed)%Tseathigh + Tseatlow;

    sleep(time); // anazitisi eisitiriwn

    
    if (epilogi_zonis <= 30){
        
        printf("-------epilexthike i zoni A . arithmos thesewn : %d id : %d\n" , seats , id);

        selected_zone = zoneA;
        cost = seats * CzoneA; 
        

        pthread_mutex_lock(&lock_thesewn_zoneA);

        int s = check_seats(zoneAseats , 10 , seats , id);
        

        pthread_mutex_unlock(&lock_thesewn_zoneA);
       
        if (s == 0){
            
            rc = pthread_mutex_lock(&lock_tel);
            if (rc!=0){
                printf("Error on mutex .");
            }

             // zone A
            for (int i = 0; i < zoneA; i++){
                for (int j = 10-1; j >= 0; j--){
                    if (zoneAseats[i][j] == id){
                        zoneAseats[i][j] = 0;
                    }
                }
            }
            

            pthread_mutex_lock(&lock_statistics);
            apotiximenes_kratiseis++;
            pthread_mutex_unlock(&lock_statistics);

            printf("-------den iparxoun diathesimes thesis stin zoni A . arithmos thesewn : %d id : %d\n" , seats,id);
            tel++;
            pthread_mutex_unlock(&lock_tel);

            canceled = true;
        }
      
    }
    else{
        
        printf("-------epilexthike i zoni B . arithmos thesewn : %d id : %d\n" , seats ,id);  

        selected_zone = zoneB;
        cost = seats * CzoneB; 
        
        pthread_mutex_lock(&lock_thesewn_zoneB);

        int s = check_seats(zoneBseats , 20 , seats , id);

        pthread_mutex_unlock(&lock_thesewn_zoneB);
        
        if (s == 0){
            
            rc = pthread_mutex_lock(&lock_tel);
            if (rc!=0){
                printf("Error on mutex .");
            }

            
            // zone B
            for (int i = 0; i < zoneB; i++){
                for (int j = 10-1; j >= 0; j--){
                    if (zoneBseats[i][j] == id){
                        zoneBseats[i][j] = 0;
                    }
                }
            }
            
            pthread_mutex_lock(&lock_statistics);
            apotiximenes_kratiseis++;
            pthread_mutex_unlock(&lock_statistics);
            printf("-------den iparxoun diathesimes thesis stin zoni B . arithmos thesewn : %d id : %d\n" , seats,id);
            tel++;
            pthread_mutex_unlock(&lock_tel);

            canceled = true;
        }    
       
    }
    
    clock_gettime(CLOCK_REALTIME,&finish_anamonis);

    if (!canceled){

        rc = pthread_mutex_lock(&lock_cash);
        if (rc!=0){
            printf("Error on mutex .");
        }

        while (cash == 0)
        {
            printf("H kratisi me arithmo %d einai se anamoni mexri na vrethei diathesimos tamias. . . .\n",id);
            rc = pthread_cond_wait(&lock_cond2,&lock_cash);
            if (rc!=0){
                printf("Error on condition wait .");
            } 
        }
        cash--;

        pthread_mutex_unlock(&lock_cash);

        rc = pthread_mutex_lock(&lock_tel);
        if (rc!=0){
            printf("Error on mutex .");
        }
        tel++;
        pthread_cond_signal(&lock_cond1);
        pthread_mutex_unlock(&lock_tel);

        int time1 = rand_r(&seed)%Tcashhigh + Tcashlow;// diadikasia pliromis
        sleep(time1);

        int ra = rand_r(&seed)%100;

        rc = pthread_mutex_lock(&lock_screen);

        if (cost / seats == 30){
            selected_zone = zoneA;
        }
        else{
            selected_zone = zoneB;
        }

        if (ra <= 90){

            sum += cost;

            char z;
            int booked_seats[seats];
            int row = 0;

            if (cost / seats == 30){
                z = 'A';

                for (int i = 0; i < zoneA; i++){
                    for (int j = 0; j < 10; j++){
                        if (zoneAseats[i][j] == id){
                            row = i+1;
                            break;
                        }      
                    }  
                    if (row > 0)
                        break;
                        
                }   
                
                int count = 0;
                for (int j = 0; j < 10; j++){
                    if (zoneAseats[row-1][j] == id){
                        booked_seats[count] = j;
                        count++;
                    }      
                }  
            }
            else{
                z = 'B';

                for (int i = 0; i < zoneB; i++){
                    for (int j = 0; j < 10; j++){
                        if (zoneBseats[i][j] == id){
                            row = i+1;
                            break;
                        }      
                    }  
                    if (row > 0)
                        break;
                        
                }  

                int count = 0;
                for (int j = 0; j < 10; j++){
                    if (zoneBseats[row-1][j] == id){
                        booked_seats[count] = j;
                        count++;
                    }      
                }
        
            }
            
            printf("-------- I kratisi oloklirothike epitixws id: %d. Oi theseis sas einai stin zoni %c , seira : %d , theseis : ",id,z , row);
            
            for (int i = 0; i < seats; i++){
                printf("%d ",booked_seats[i]);
            }
            printf(" poso : %d\n" , cost);
        }
        else{
            

            if(selected_zone == 10){ // zone A
                for (int i = 0; i < selected_zone; i++){
                    for (int j = 10-1; j >= 0; j--){
                        if (zoneAseats[i][j] == id){
                            zoneAseats[i][j] = 0;
                        }
                    }
                }
            }
            else{// zone B
                for (int i = 0; i < selected_zone; i++){
                    for (int j = 10-1; j >= 0; j--){
                        if (zoneBseats[i][j] == id){
                            zoneBseats[i][j] = 0;
                        }
                    }
                }
            }
            pthread_mutex_lock(&lock_statistics);
            apotiximenes_kratiseis++;
            pthread_mutex_unlock(&lock_statistics);
                    
            printf("------ Apotixia pliromis id: %d\n" ,id);

            pthread_mutex_lock(&lock_cash);
            if (rc!=0){
                printf("Error on mutex .");
            }
            cash++;

            pthread_mutex_unlock(&lock_cash);

            
        }

        clock_gettime(CLOCK_REALTIME,&finish_eksipiretisis);

    }

    pthread_mutex_lock(&lock_statistics);
    xronos_eksipiretisis = finish_eksipiretisis.tv_sec - start_eksipiretisis.tv_sec;
    avg_ekspipiretisis += xronos_eksipiretisis;

    xronos_anamonis = finish_anamonis.tv_sec - start_anamonis.tv_sec;
    avg += xronos_anamonis;
    pthread_mutex_unlock(&lock_statistics);

    pthread_mutex_unlock(&lock_screen);

    

    rc = pthread_mutex_lock(&lock_cash);
    if (rc!=0){
        printf("Error on mutex .");
    }

    cash++;
    pthread_cond_signal(&lock_cond2);
    pthread_mutex_unlock(&lock_cash);

    pthread_exit (NULL);
}   


int main (int argc , char *argv[])
{

    if (argc != 3){
        printf("Wrong input , try again!");
        exit(0);
    }
    
    mutex = pthread_mutex_init (&lock_tel , NULL);
    cond1 = pthread_cond_init (&lock_cond1 , NULL);
    mutex1 = pthread_mutex_init (&lock_cash , NULL);
    cond2 = pthread_cond_init (&lock_cond2 , NULL);
    mutex2 = pthread_mutex_init (&lock_screen, NULL);


    int Ncust = atoi(argv[1]);
    seed = atoi(argv[2]);

    int *id; 
    
    
    printf("%d",Ncust);

    zoneAseats = (int **)malloc(sizeof(int*)*10);
    zoneBseats = (int **)malloc(sizeof(int*)*20);

    for (int i=0; i < zoneA; i++){
        *(zoneAseats + i) = (int *)malloc(sizeof(int)*10);
        for (int j = 0; j < 10; j++){
            zoneAseats[i][j] = 0;
        }
    }

    for (int i=0; i < zoneB; i++){
        *(zoneBseats + i) = (int *)malloc(sizeof(int)*10);
        for (int j = 0; j < 10; j++){
            zoneBseats[i][j] = 0;
        }
    }

    id = (int *)malloc(sizeof(int)*Ncust);
    
    if (!id){
        printf("malloc failure");
        exit(0);
    }

    threads = (pthread_t*)malloc(sizeof (pthread_t) * Ncust);

    if (!threads){
        printf("malloc failure");
        exit(0);
    }

    for (int i = 0; i < Ncust; ++i){
        id[i] = i + 1;

        if (i > 0){
            int time = rand_r(&seed)%Treshigh + Treslow;
            sleep(time);
        }

        rc = pthread_create(&(threads[i]) , NULL ,book_seats , (void*)&(id[i]));
       // printf("thread created id : %d\n",id[i]);

        if (rc != 0){
            printf("error on pthread_create");
            exit(0);
        }
    }

    for (int i = 0; i < Ncust; i++){
        pthread_join(threads[i] , NULL);
    }

    printf("--sinolika esoda : %d $ .\n",sum); 
    printf("--Mesos oros xronwn anamonis : %.2f lepta .\n",avg/(double)Ncust); 
    printf("--Mesos oros xronwn ekspipiretisis : %.2f lepta .\n",avg_ekspipiretisis/(double)Ncust); 
    printf("--apotiximenes kratiseis : %d  .\n",apotiximenes_kratiseis); 
    printf("--pososto epitiximenwn kratisewn : %.2f  .\n",(double)(Ncust-apotiximenes_kratiseis)/(double)Ncust); 

    //plano thesewn 

    // ZONE A
    printf("zoneA \n");
    for (int i=0; i < zoneA; i++){
        for (int j = 0; j < 10; j++){
            printf("%d " , zoneAseats[i][j]);
        }
        printf("\n");
    }

    // ZONE B
    printf("\nzoneB \n");
    for (int i=0; i < zoneB; i++){
        for (int j = 0; j < 10; j++){
            printf("%d " , zoneBseats[i][j]);
        }
        printf("\n");
    }

    free(threads);
    free(id);
    free(booked_seats);
    for (int i = 0; i < 10; i++){
        free(*(zoneAseats + i));
    }
    for (int i = 0; i < 20; i++){
        free(*(zoneBseats + i));
    }
    pthread_mutex_destroy (&lock_tel);
    pthread_cond_destroy(&lock_cond2);
    pthread_mutex_destroy (&lock_cash);
    pthread_mutex_destroy (&lock_thesewn_zoneA);
    pthread_mutex_destroy (&lock_thesewn_zoneB);
    pthread_mutex_destroy(&lock_statistics);
    pthread_mutex_destroy(&lock_desmefmenwn_thesewn);
    pthread_cond_destroy(&lock_cond1);
    pthread_mutex_destroy (&lock_screen);


    char a;
    printf("Press any key and enter to continue \n");
    scanf("%s",&a);

    return 0;

}