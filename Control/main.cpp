#include <iostream>
#include <fstream>
#include <irobot.h>
#include <psensor.h>
#include <pthread.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include "func.h"
#include "Action.h"
#define ms_100 100000
#define ms_10  10000
#define max_us 1000000
using namespace std;
int TARGE_X; 
int TARGE_Y; 

int getTarget()
{
    ifstream myfile;
    myfile.open("target0");
    myfile >> TARGE_X;
    myfile >> TARGE_Y;
    cout << "TARGE_X:" <<TARGE_X << ", Y = " << TARGE_Y << endl;
    myfile.close();
    return 0;
}

int delay(int s,int ms)
{
  if(s > 0)  sleep(s);
  if(ms > 0) usleep(ms *ms_100);
  cout << "delay: " << s << "sec "  << ms << "00ms"  << endl;
  return 0;
}
int delay_0(int ms_x)
{
    cout << "ms_x" <<ms_x << endl;
    if(ms_x > 100){
        int s = ms_x/100;
        sleep(s);
        usleep((ms_x - s*100)*ms_10);
    } else {
        usleep(ms_x*ms_10);
    }
    return 0;
}

int main()
{
    cout << "Hello from pi" << endl;
    getTarget();

    cout << "press input the the arm+irobot tty [01] " << endl;

    std::string cc;
    cin >> cc;
    const char* cc0 = cc.data();

    _ROBOT::Action action;
    action.init(cc0[0],cc0[1]);
    //scheduler is abandoned for this round,will be added later
    while(!flag)
    {
		action();
        usleep(ms_10);
    }

    return 0;

}
