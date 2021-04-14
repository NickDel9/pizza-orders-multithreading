#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>



unsigned int seed;
int mutex,mutex1,mutex2,mutex3,condition1,condition2 , condition3;
double max = 0;
double maxKriwmatos = 0;
double avg;
double avgKriwmatos;
int Ncook = 2;
int Noven = 5;
int Ndeliverer = 10;
int Torderlow = 1;
int Torderhigh = 5;
int Norderlow = 1;
int Norderhigh = 5;
int Tprep = 1;
int Tbake = 10;
int 	Tlow = 5;
int Thigh = 15;
int  tNums;
int rc;

