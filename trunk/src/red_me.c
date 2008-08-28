/* 
   Simple generic RED gateway simulator
     by Mehmet A. Suzen
     January 2005, Famagusta, Cyprus
     October 2005,  Minor Modifications
     June 2007,  Modified for Master Equation Computation
     Famagusta, Cyprus
     (c) 2005-2006-2007
     General Public License 
      GPL  
#    Copyright (C) 2006  Mehmet Suzen <mehmet.suzen@physics.org>
#
#    This program is free software; you can redistribute it and/or modify
#    it under the terms of the GNU General Public License as published by
#    the Free Software Foundation; either version 2 of the License, or
#    any later version.
#
#    This program is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU General Public License for more details.
#
#    You should have received a copy of the GNU General Public License
#    along with this program; if not, write to the Free Software
#    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
#

 */
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

/* Prototypes                        */
/*************************************/
int main();
void get_randoms(int *numbers, int upper);
void get_bin_randoms(int *numbers2, int upper);
int read_network(int *hostrate);
void drandom_init_memo();
double forward_euler(double delta,double aposb ,double ppos,double anegf,double pneg,double anowf ,double anowb,double pnow);
double get_PQ(int q,double avg,int buffer_size,double delta);
/*************************************/

double *PQ; /* probability of finding q number of packets at time t*/
double *forward_rate; /* forward rate of state q */
double *backward_rate; /* forward rate of state q */

int main()
{
   FILE *fp1,*fp2,*fp3;
   int i,j,q,numhost,count,minth,maxth,time,simtime,m,qtime,*q_time;
   int *nran,*nran2,*hostrate,**hostdrops,zero,rcount,buffer_size;
   char line1[100];
   double wq,avg,maxp,pa,pb,*avg_time,prob;  
   double real_time,delta_time=0.01;
      drandom_init_memo();
    zero=0;
    numhost=0;
    simtime=10000;
    wq=0.002;
    minth=5;
    maxth=15;
    maxp=0.02;
    buffer_size=500; /* this is actually buffer size -1 if it doesn't include zero size queue state*/
    printf(" \n"); 
    printf("          Simple genericRED gateway simulator \n"); 
    printf("                      Master Equation Approach\n"); 
    printf("                      M. Suzen (c) 2005 -2007 \n"); 
    printf(" \n"); 
    printf(" \n"); 
    printf(" \n"); 
    printf(" \n"); 
    printf(" \n"); 
    hostrate=(int *) malloc(1000*sizeof(int));
    printf("  allocated hostrate \n"); 
    numhost=read_network(hostrate);
    printf("  read network file !\n"); 
     avg_time=(double *) malloc(simtime*sizeof(double));
     q_time=(int *) malloc(simtime*sizeof(int));
     nran=(int *) malloc((simtime+1)*(numhost+1)*sizeof(int));
     nran2=(int *) malloc((numhost+1)*sizeof(int));
     hostdrops=(int **) malloc((simtime+3)*sizeof(int));
     for(i=0;i<=simtime;i++) { 
      hostdrops[i]=(int *) malloc((numhost+3)*sizeof(int));
     }
    printf("  allocated other stuff !! !\n"); 
   for(i=0;i<numhost;i++) {
     printf("%d th hostrate = %d  packets/unit time\n",i,hostrate[i]);
    }


   
     /* initilize hostdrops and avg_time */
      for(time=0; time < simtime; time++) {
           avg_time[time]=0;
         for(i=0;i<numhost;i++) {
           hostdrops[time][i]=0;
          }
       }
    /* Master Equation Stuff */
     PQ=(double *) malloc(buffer_size*sizeof(double));
     forward_rate=(double *) malloc(buffer_size*sizeof(double));
     backward_rate=(double *) malloc(buffer_size*sizeof(double));
    /* initilize ME stuff with random number drand48 */
      for(i=0;i<buffer_size;i++) {
	 PQ[i]=drand48();
	 forward_rate[i]=drand48();
	 backward_rate[i]=drand48();
      }

     /* core RED algorithm */
          avg=0;
          count=-1;
          qtime=0;
       fp3=fopen("traffic_master.ntw","w");
           /* Find current queue size or hosts sending packet */
       rcount=0;
           /* randomly pick which hosts are sending packets*/
            get_bin_randoms(nran,(numhost+1)*(simtime+1)); 
	     printf("core RED Algorithm \n");
      for(time=0;time<simtime; time++) {
	     printf("core RED Algorithm step =%d \r",time); 
            q=0;
	       real_time=delta_time*time;
              sprintf(line1,"%f ",real_time);
            for(i=0;i<numhost;i++) {
                   nran2[i]=nran[rcount];
                    /* printf("count nran2=%d\n",nran2[i]); */
               if(nran[rcount] == 1) {
                  q=q+hostrate[i];
                  sprintf(line1,"%s%d ",line1,hostrate[i]);
                 } else {
                  sprintf(line1,"%s%d ",line1,zero);
               }
                rcount++;
            }
              fprintf(fp3,"%s\n",line1);
               q_time[time]=q;
               /* printf("Current time = %d QUEUE q=%d\n",time,q); */
             /* loop over each host sending packet */
            for(i=0;i<numhost;i++) {
               /* printf("here nran2=%d\n",nran2[i]); */
               if(nran2[i] == 1) {
                    for(j=0;j<hostrate[i];j++) {
                          if(q != 0) {
			     prob=get_PQ(q,avg,buffer_size,delta_time); /* compute average via Master Equation */
                             // avg=fabs(q*prob+(q-avg));
                             // avg=q*prob;
                             avg=(q-avg)*prob+avg*prob;
                             avg_time[time]=avg;
                             if(prob > 1.0) {  printf("EVER avg=%f prob=%f \n",avg,prob); }
                        /*   printf("ZERO q= %d time=%d avg_time=%f\n",q,time,avg_time[time]);  */
                            } else {
                             m=time-qtime; /* s is 1 here time-qtime/s */
			     prob=get_PQ(m,avg,buffer_size,delta_time); /* compute average via Master Equation */
                             avg=pow((1-prob),m)*avg;
                             avg_time[time]=avg;
                         /*printf("time=%d avg_time=%f\n",time,avg_time[time]); */
                           }
                          /*printf("time=%d avg_time=%f\n",time,avg_time[time]); */
                          //if(q >= buffer_size) { hostdrops[time][i]++;  }
                          if(minth <= avg && avg < maxth ) {
                             count++; 
                      /* printf("maxp=%f avg=%f minth=%d maxth=%d\n",maxp,avg,minth,maxth); */
                             pb=maxp*(avg-minth)/(maxth-minth);
                             pa=pb/(1-count*pb);
                                   /* printf("count=%d pb=%f pa=%f \n",count,pb,pa); */
                              if(pa >= 0.015) { 
                               hostdrops[time][i]++; 
                               /* printf("PA dropping: i %d time %d value %d \n",i,time,hostdrops[time][i]); */
                               count=0;
                              }
                           }
                           if(maxth <= avg) {
                               hostdrops[time][i]++; 
                              /* printf("dropping: i %d time %d value %d \n",i,time,hostdrops[time][i]); */
                               count=0;
                             } else {
                               count=-1;
                           } 
                           if(q ==0) {
                              qtime=time;
                           }
                     }
                }  
             }
        }
    fclose(fp3);
    /* Report Host Drops  */
    fp1=fopen("hostdrops_master.ntw","w");
      for(time=0; time < simtime; time++) {
           sprintf(line1,"%5d",time);
         for(i=0;i<numhost;i++) {
                /* printf("hostdrop=%d \n",hostdrops[time][i]); */
           sprintf(line1,"%s %5d",line1,hostdrops[time][i]);
          }
                /* printf("C line1=%s \n",line1); */
           fprintf(fp1,"%s\n",line1);
       } 
    fclose(fp1);
    /* Report average and current queue size */
    fp2=fopen("queues_master.ntw","w");
      for(time=0; time < simtime; time++) {
        real_time=delta_time*time;
        fprintf(fp2,"%f  %f  %d\n",real_time,avg_time[time],q_time[time]);
       /* printf("time=%d avg_time=%f\n",time,avg_time[time]);  */
      }
    fclose(fp2);
    /* Free Dynamic Arrays */
   free(nran);
   free(hostrate);
   free(hostdrops);
   free(avg_time);
   free(q_time);
	     printf("\n \n  _ _ _ RED Algorithm  finished \n"); 
    exit(0);
}
 /**********************************************************
    RED simulator  Functions                                     
  **********************************************************/
/* Get random squence over upper*/
void get_randoms(int *numbers, int upper) {
   int i;
   /*srand( (unsigned int) time( NULL ) );*/
      for(i =upper-1; i > 0; i -= 1 ){
        numbers[i] = drand48() * i;
        /* printf("numbers=%d i=%d \n",numbers[i],i);*/
       }
}
/* Get random squence of 1s and 0s of uppers*/
void get_bin_randoms(int *numbers2, int upper) {
   int i,where;
   /*srand( (unsigned int)time( NULL ) );*/
      for(i =0; i < upper; i++ ){
        where=drand48()*100;  
            /* printf("where = %d\n",where) */; 
        numbers2[i] = where % 2;
       }
}
/* Read Network Data */
/* First line number of hosts */
/* other lines packets/sec perline */ 
int read_network(int *hostrate) {
    FILE *fp;
    int i,j,numhost=0;
    char line[100];

     i=0; 
     j=0; 
    printf(" network file \n");
     /* while(feof(fp) == 0) {*/
    fp=fopen("network.ntw","r");
     while( fgets(line,10,fp) != NULL) { 
            /* printf(" \n *** hell line is =%s \n",line); */
        if(i == 0) {
           /* realloc(hostrate,2*sizeof(int));  */
           /* printf(" network hostrate realloc\n"); */
           sscanf(line,"%3d",&numhost); 
           /* printf("numhost=%d \n",numhost);  */
          } else {
           /* printf("other then that =%s \n",line); */
           /*realloc(hostrate,2*sizeof(int)+(i+1)*sizeof(int));  */
           sscanf(line,"%3d",&hostrate[j]);
	   j++;
           /* printf("hostrate i=%d rate=%d\n",i,hostrate[i]);  */
        }
           i++;
            /* printf("line increment i=%d numhost=%d \n",i,numhost);   */
      }
            /* printf("line out\n");  */
       if(numhost != (i-1)) {
          printf("missing host in network.ntw ; numhost=%d total lines=%d   \n",numhost,i); 
          exit(0);
        }
   fclose(fp);
        printf(" network file read completed \n");
  return numhost;
}
/* update Master Equation : transition rates and probabilities */
double get_PQ(int q,double avg,int buffer_size,double delta) {
   int i;
    /* Compute new transition rates */
    for(i=0;i<buffer_size-1;i++) {
      forward_rate[i]=exp(-fabs(i+1+avg)); /* forward rate of state q */
    }
    for(i=1;i<buffer_size;i++) {
      backward_rate[i]=exp(-fabs(i-1+avg));
    }
   /* Compute new probability values */
      backward_rate[0]=0.0;
      forward_rate[buffer_size-1]=0.0;
    for(i=1;i<buffer_size-1;i++) {
	    double tempo=PQ[i];
      PQ[i]=forward_euler(delta, backward_rate[i+1],PQ[i+1],forward_rate[i-1],PQ[i-1],forward_rate[i], backward_rate[i],PQ[i]);
       if(PQ[i] > 1.0) {
	    printf("avg = %f backward_rate[i+1]=%f ,PQ[i+1]=%f,forward_rate[i-1]=%f,PQ[i-1]=%f,forward_rate[i]=%f, backward_rate[i]=%f,PQ[i,t]=%f,PQ[i,t-delta]=%f i=%d \n",avg,backward_rate[i+1],PQ[i+1],forward_rate[i-1],PQ[i-1],forward_rate[i], backward_rate[i],PQ[i],tempo,i);
        }
     }
    return PQ[q];
}
double forward_euler(double delta,double aposb ,double ppos,double anegf,double pneg,double anowf ,double anowb,double pnow) {
  double pnew; /* update value of probability of finding q packets at time t !*/
   /* forward euler */
   pnew=pnow+(aposb*ppos+anegf*pneg-(anowf+anowb)*pnow)*delta; 
  return pnew;
}
void drandom_init_memo() {
   // double x;
   /* int i,seed;*/
   int seed;
    clock_t start, end;
    double cpu_time_used;
    start = clock();
    seed=cpu_time_used;
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    srand48(seed);
    srand48( (unsigned int) time( NULL ));
}
