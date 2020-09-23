#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int delivered = 0; 
int number_of_signals = 0;

void alarm_handler(int signum)
{ //signal handler
  delivered = 1;
}

void int_handler(int signum)
{
  printf("\nTotal number of seconds: %d\n", number_of_signals);
  exit(1);
}

int main(int argc, char * argv[])
{
  signal(SIGALRM,alarm_handler); //register handler to handle SIGALRM
  signal(SIGINT, int_handler);
  alarm(1); //Schedule a SIGALRM for 1 second
  number_of_signals++;
  while (1){
    while(delivered == 0); //busy wait for signal to be delivered
    delivered = 0;
    alarm(1);
    number_of_signals++;
  }
  return 0; //never reached
}

