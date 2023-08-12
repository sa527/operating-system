/*10/08/2023*/

/*Planning of the code, this code will be executed in three steps. 
The initial step involves creating the "even.c" program, which takes the 
parameter "n" from the command line and outputs the first "n" even numbers. 
In the subsequent step, a delay of 5 seconds using the "sleep(5)" function 
will be incorporated into the program. Finally, in the last step, the program 
will be enhanced to respond to the "HUP" and "INT" signals.*/
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>


void handleHUP(int signum)
{
    printf("Ouch!");
}

// Signal for SIGINT
void handleINT(int signum)
{
    printf("Yeah!");
}

int main(int argc, char const *argv[])
{
    signal(SIGHUP, handleHUP);
    signal(SIGINT, handleINT);

    sleep(5);
    int length =atoi(argv[1]);;
    for (int i = 0; i < length*2; ++i)
        {
            if (i%2 ==0)
            {
               printf("%i\n",i);
            }
            
        }    
	return 0;
}