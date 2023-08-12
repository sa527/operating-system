/*10/08/2023*/

/*Planning of the code, this code will be executed in three steps. 
The initial step involves creating the "even.c" program, which takes the 
parameter "n" from the command line and outputs the first "n" even numbers. 
In the subsequent step, a delay of 5 seconds using the "sleep(5)" function 
will be incorporated into the program. Finally, in the last step, the program 
will be enhanced to respond to the "HUP" and "INT" signals.*/
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <unistd.h>
#include <signal.h>


bool isEven(char c)
{
    return (c >= '0' && c <= '9' && (c - '0') % 2 == 0);
}

// Signal for SIGHUP
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
	char input[10001]; //Assume  the maximum inpur is not over than 10001
      
    int a=1;
    signal(SIGHUP, handleHUP);
    signal(SIGINT, handleINT);

    printf("Enter the number, Please!\n");
    fgets(input, sizeof(input), stdin);
    sleep(5);
    int length = 0;
    while (input[length] != '\n' && input[length] != '\0')
    {
        if (!isdigit(input[length]))
        {
            printf("Stopping due to non-digit character.\n");
            return 0;
        }
        
        if (isEven(input[length])&& a==1)
        {
            printf("The first even number is: %c\n", input[length]);
            a=2;
        }
        
        length++;
    }
    
	return 0;
}