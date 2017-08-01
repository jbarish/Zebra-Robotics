#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <pthread.h>
#include <time.h>

#define CLOCKID CLOCK_REALTIME
#define SIG SIGRTMIN

#define errExit(msg)    do { perror(msg); exit(EXIT_FAILURE); \
                       } while (0)
timer_t timerid;

volatile sig_atomic_t flag = 0;

void my_function(int sig){ // can be called asynchronously
  flag = 1; // set flag
}

int timer_ = 0;

static void handler(int sig, siginfo_t *si, void *uc)
{

   if(si->si_value.sival_ptr == &timerid) {
      timer_ = 1;

   }
}
//scheduler is abandoned for this chalange, will be added later
