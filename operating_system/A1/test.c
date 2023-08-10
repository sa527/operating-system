/*10/08/2023*/

/*Planning of the code, this code will be executed in three steps. 
The initial step involves creating the "even.c" program, which takes the 
parameter "n" from the command line and outputs the first "n" even numbers. 
In the subsequent step, a delay of 5 seconds using the "sleep(5)" function 
will be incorporated into the program. Finally, in the last step, the program 
will be enhanced to respond to the "HUP" and "INT" signals.*/
#include <stdio.h>
#include <stdbool.h>

bool evenNumber(const char input[], int length) 
{
	bool loop=true;
	for (int i = 0; i < length-1; ++i)
	{
		if (input[i]%2 ==0)
		{
			printf("The first even number is:%c\n", input[i]);
			break;
		}
		if (input[i] >= '0' && input[i] <= '9')//we have to consider for the step 3. otherwise program never stop.
		{
			loop =false;
		}
	}
	return loop;
}

int main(int argc, char const *argv[])
{
	char input[10001]; //Assume  the maximum inpur is not over than 10001
	int length =0;
	int loop=0;
	while(loop ==0)
	{	
		printf("Enter the number,Please!\n");//let's user input the number
		fgets(input, sizeof(input), stdin);//
		while(input[length]!= '\0'){ // we have to know what is the length of the input;
		length++;
		}
		if (evenNumber(input,length)==false)
		{
			loop=1;a
		}
	}
	return 0;
}