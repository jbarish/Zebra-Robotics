#ifndef DRIVER_H
#define DRIVER_H
#include <createoi.h>
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <sys/time.h>

class Driver {

public:

int driveForward(int, int);

int turnRight();
int turnLeft();

};

#endif
