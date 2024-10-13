
#include <iostream>
#include <cstdio>
#include <cstdlib>
// #include <stdio.h>     /* for printf */
// #include <stdlib.h>    /* for exit */
#include <getopt.h>
#include <signal.h>
#include  "disp.h"

#include "tsargs.h"

extern simWindow wndSim;

int TSargs::init( int argc, char **argv ) 
{

 int c;

 extern int MAXELEVS;     // Number of elevators (1 to 10 only)
 extern int MAXFLOORS;    // Number of floors (2 to 10 only)
 extern int MAXPERSONS;   // Maximum people in building
 extern int ELEVWAIT;     // Min. seconds to wait at floors
 extern int CAPACITY;     // Maximum people in an elevator
 extern int TRAVELTIME;   // Seconds to travel between floors
 extern int TICDELAY;     // Tic Delay for slowing down simulation"
 extern int SIMTIME;      // Simulator run time "

struct params {
	int *vl;
	int v;
	const char *nome;
	const char *descr;
	char prmOpt;
} prms[] = {
	{ &MAXELEVS,    10, "maxLevels",  "Number of elevators (1 to 10 only)" , 'l' },
	{ &MAXFLOORS,   10, "maxFloors",  "Number of floors (2 to 10 only)" , 'f' },
	{ &MAXPERSONS, 750, "maxPersons", "Maximum people in building" , 'p' },
	{ &ELEVWAIT,    20, "elevWait",   "Min. seconds to wait at floors", 'm' },
	{ &CAPACITY,    18, "capacity",   "Maximum people in an elevator", 'c' },
	{ &TRAVELTIME,   5, "traveltime", "Seconds to travel between floors", 't' },
	{ &TICDELAY,    10, "ticDelay",   "Tic Delay for slowing down simulation n*(0,1s)", 'y' },
	{ &SIMTIME,    300, "simTime",    "Simulator run time (s)", 'R' },
	{ 0, 0, 0, 0, 0 }
  };   

  while( (c = getopt(argc, argv, "l:f:p:m:c:t:y:R:") ) != -1 ) {
       switch (c)  {
        
       case 'l':
            MAXELEVS = atoi( optarg );
            break;

       case 'f':
            MAXFLOORS = atoi( optarg );
            break;

       case 'p':
            MAXPERSONS = atoi( optarg );
            break;

       case 'm':
            ELEVWAIT = atoi( optarg );
            break;

       case 'c':
			CAPACITY = atoi( optarg );
            break;

       case 't':
			TRAVELTIME = atoi( optarg );
            break;
			
       case 'y':
			TICDELAY = atoi( optarg );
            break;
			   
	   case 'R':
			SIMTIME = atoi( optarg );
            break;			   

			   
       default:
			// Imprime ajuda
			// printf("Chamada de %s com parametros : \n" , argv[0] );
			   
			wndSim.disp_suspend();
			printf( "Chamada de %s  com parametros : \n" , argv[0] );			   
            for( int i = 0 ; prms[i].vl  ; ++i ) {
				printf( " opcao %c : -> %s , default: %d\n", 
					prms[i].prmOpt,
					prms[i].descr,
					prms[i].v
					);
			};			
			return( -1 );
    }
  }
	wndSim.disp_resume();
	return( 0 );
}
