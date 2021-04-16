
#include "Header-pizza2.h"

void *Construction (void *var);

pthread_mutex_t lock_kataskevastwn;
pthread_mutex_t lock_fournwn;
pthread_mutex_t lock_arxikis_othonis;
pthread_cond_t cond1;
pthread_cond_t cond2;
pthread_cond_t cond3;
pthread_mutex_t lock_dianomewn;


void *Construction (void *var)
{
      int pitses , dianomi ;
      struct timespec start;
      struct timespec finish;
      struct timespec startKriwmatos;
      struct timespec finishKriwmatos;
      double xronos_paragelias , xronos_kriwmatos;
      int id = *(int*) var;
     
      pitses = rand_r(&seed)%Norderhigh + Norderlow;

      rc = pthread_mutex_lock (&lock_kataskevastwn); // lock kataskevastwn
      if (rc!=0){
            printf("Error on mutex .");
        }

      clock_gettime(CLOCK_REALTIME,&start); // arxi metrisis xronou oloklirwsis
           
      printf ("---------------H paragelia me arithmo %d kataxorithike\n", id);
      while (Ncook == 0)
 	  {
	    printf("H paragelia me arithmo %d einai se anamoni mexri na vrethei diathesimos paraskevastis. . . .\n",id);
        rc = pthread_cond_wait(&cond1,&lock_kataskevastwn);
        if (rc!=0){
            printf("Error on condition wait .");
        }
	  }
	  printf("H paraggelia me arithmo %d paraskevazetai apo ton paraskevasti %d. Pitses = %d\n",id,Ncook,pitses);
      Ncook--;

      pthread_mutex_unlock(&lock_kataskevastwn); // unlock kataskevastwn
      
      sleep(Tprep*pitses); // xronos proetimasias
     
      rc = pthread_mutex_lock(&lock_fournwn);// lock fournwn
      if (rc!=0){
            printf("Error on mutex .");
        }      

      while (Noven == 0)
      {
           printf("H paraggelia me arithmo %d einai se anamoni mexri na vrethei diathesimos fournos. . . .\n",id);
           rc = pthread_cond_wait(&cond2,&lock_fournwn);
           if (rc!=0){
            printf("Error on condition wait .");
        }
       }
      printf("H paragelia me arithmo %d bike sto fourno...%d\n",id,Noven);
      Noven--;
      pthread_mutex_unlock(&lock_fournwn); // unlock fournwn
      
      rc = pthread_mutex_lock(&lock_kataskevastwn);
      if (rc!=0){
            printf("Error on mutex .");
        }
      Ncook++; 				// apeleftherwsi kataskevasti
      pthread_cond_signal(&cond1);
      pthread_mutex_unlock(&lock_kataskevastwn);  

      sleep(Tbake); // xronos psisimatos
	
      clock_gettime(CLOCK_REALTIME,&startKriwmatos); // arxi metrisis xronou kriwmatos
     
      rc = pthread_mutex_lock(&lock_dianomewn);// lock dianomewn
      if (rc!=0){
            printf("Error on mutex .");
        }      

      while (Ndeliverer == 0)
      {
           printf("H paraggelia me arithmo %d einai se anamoni mexri na vrethei diathesimos dianomeas. . . .\n",id);
           rc = pthread_cond_wait(&cond3,&lock_dianomewn);
           if (rc!=0){
            printf("Error on condition wait .");
        }
       }
      printf("H paragelia me arithmo %d einai sto dromo... me ton dianomea %d\n",id , Ndeliverer);
      Ndeliverer--;
      pthread_mutex_unlock(&lock_dianomewn); // unlock dianomewn   

      rc = pthread_mutex_lock(&lock_fournwn);
      if (rc!=0){
            printf("Error on mutex .");
        }
      Noven++;				// apeleftherwsi fournou
      pthread_cond_signal(&cond2);
      pthread_mutex_unlock(&lock_fournwn);   
      
      dianomi = rand_r(&seed)%Thigh + Tlow;
      
      sleep(dianomi);	// xronos dianomis paragelias sto pelati   

      clock_gettime(CLOCK_REALTIME,&finishKriwmatos); // telos metrisis xronou kriwmatos

      clock_gettime(CLOCK_REALTIME,&finish); // telos metrisis xronou oloklirwsis   
 
      sleep(dianomi); // xronos epistrofis dianomea

      rc = pthread_mutex_lock(&lock_dianomewn);
      if (rc!=0){
            printf("Error on mutex .");
        }

      Ndeliverer++; // apeleftherwsi dianomea

      printf("o dianomeas %d epestrepse \n", Ndeliverer);   
   
      pthread_cond_signal(&cond3);
      pthread_mutex_unlock(&lock_dianomewn);

      

      rc = pthread_mutex_lock(&lock_arxikis_othonis);// lock arxikis othonis
      if (rc!=0){
            printf("Error on mutex .");
        }
      xronos_paragelias = finish.tv_sec - start.tv_sec; ;
      avg += xronos_paragelias;    // ypologismos mesou orou oloklirwsis

      xronos_kriwmatos = finishKriwmatos.tv_sec - startKriwmatos.tv_sec;
      avgKriwmatos += xronos_kriwmatos;

      if (xronos_paragelias > max)
      {
      	max = xronos_paragelias;  // ypologismos megistou xronou oloklirwsis 
      }
      
      if (xronos_kriwmatos > maxKriwmatos)
      {
      	maxKriwmatos = xronos_kriwmatos;  // ypologismos megistou xronou oloklirwsis 
      }

      printf("      ********* H paragelia %d oloklirotike epitixws...me xrono %f lepta kai kriwne gia %f lepta .\n",id,xronos_paragelias,xronos_kriwmatos); // ektypwsi apotelesmatwn paragelias

      pthread_mutex_unlock(&lock_arxikis_othonis); // unlock arxikis othonis

      pthread_exit (NULL);
  
}



int main (int argc , char *argv[])
{
  
  int i;  
  int paragelia;

  if (argc!=3){
	printf("Wrong input , please try again .\n");
	exit(0);
  }

  tNums = atoi(argv[1]);
  seed = atoi(argv[2]);

  int *id;
  pthread_t *ThreadArray;

  id = (int *)malloc(sizeof(int)*tNums); // desmefsi mnimis gia ton pinaka id

  if (!id)
    {
      printf ("Wrong malloc execution\n");
      exit (0);
    }

  ThreadArray = (pthread_t*)malloc(sizeof (pthread_t) * tNums); // desmefsi mnimis gia ton pinaka ThreadArray

  if (!ThreadArray)
    {
      printf ("Wrong malloc execution\n");
      exit (0);
    }

  	// inits 
  mutex = pthread_mutex_init (&lock_fournwn, NULL);
  condition1 = pthread_cond_init(&cond1, NULL);
  mutex1 = pthread_mutex_init (&lock_kataskevastwn, NULL);
  condition2 = pthread_cond_init(&cond2, NULL);
  mutex2 = pthread_mutex_init (&lock_arxikis_othonis, NULL);
  mutex3 = pthread_mutex_init (&lock_dianomewn, NULL);
  condition3 = pthread_cond_init(&cond2, NULL);
  
  if (mutex != 0 || mutex1!=0 || mutex2!=0 || condition1!=0 || condition2!=0|| mutex3!=0 || condition3!=0)
    {
      printf ("Mutex or condition init has failed .");
      return 1;
    }
  for (i = 0; i < tNums; ++i)
    {

      id[i] = i + 1 ;

      if (i>0){
          paragelia = rand_r(&seed)%Torderhigh + Torderlow;
          sleep(paragelia);
      }

      rc = pthread_create (&(*(ThreadArray + i)), NULL, Construction,(void*)&(id[i]));
      
      if (rc != 0)
	{
	  printf ("ERROR code from pthread_create() is %d\n", rc);
	  exit(0);

	}
    }

    for (i=0;i<tNums;++i){
        pthread_join (*(ThreadArray + i), NULL);
    }


    printf("--Mesos oros xronwn : %f lepta .\n",avg/tNums); //ektipwsi mesou orou
    printf("--Megistos xronos paragelias : %f lepta .\n",max); // ektipwsi max xronou
     
    printf("--Mesos oros xronwn kriwmatos : %f lepta .\n",avgKriwmatos/tNums); //ektipwsi mesou orou kriwmatos
    printf("--Megistos xronos kriwmatos : %f lepta .\n",maxKriwmatos); // ektipwsi max xronou kriwmatos

	// apodesmefsi dinamikis mnimis
    free(ThreadArray);
    free(id);
    pthread_mutex_destroy (&lock_fournwn);
    pthread_cond_destroy(&cond2);
    pthread_mutex_destroy (&lock_kataskevastwn);
    pthread_cond_destroy(&cond1);
    pthread_mutex_destroy (&lock_arxikis_othonis);
     
   char a;
   printf("Press any key and enter to continue \n");
   scanf("%s",&a);

  return 0;


}



