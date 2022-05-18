#define _POSIX_C_SOURCE 200809L

#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>

unsigned int seed , rc;
int mutex , mutex1 , mutex2, mutex3 , cond1 , cond2;
int **zoneAseats;
int **zoneBseats;
int * booked_seats;
int row;
int selected_zone;

//statistics
int sum = 0; // sinolika esoda
int apotiximenes_kratiseis = 0;

double avg = 0; // mesos xronos anamonis 
double avg_ekspipiretisis = 0; // mesos xronos ekspipiretisis 
 

// count

int tel = 3;
int cash = 2;
int seat = 10;
int zoneA = 10;
int zoneB = 20;

//possibility
double PzoneA = 0.3;
double PzoneB = 0.7;
double Pcardsuccess = 0.9;

//amount 
double CzoneA = 30;
double CzoneB = 20;

//seats
int Nseatlow = 1;
int Nseathigh = 5;

//Time
int Treslow = 1;
int Treshigh = 5;
int Tseatlow = 5;
int Tseathigh = 13;
int Tcashlow = 4;
int Tcashhigh = 8;

// mutexes
pthread_mutex_t lock_tel;
pthread_mutex_t lock_cash;
pthread_mutex_t lock_thesewn_zoneA;
pthread_mutex_t lock_thesewn_zoneB;
pthread_mutex_t lock_statistics;
pthread_mutex_t lock_desmefmenwn_thesewn;
pthread_mutex_t lock_screen;

//conditions
pthread_cond_t lock_cond1 , lock_cond2 , lock_cond3;

//thread array
pthread_t *threads;



