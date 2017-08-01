#ifndef FUNC_H
#define FUNC_H

#include <signal.h>
//################################################
extern int init_arm(void);
extern int init_robot(void);
extern int init_state(const uint16_t turn0);
extern int action(void);
extern volatile sig_atomic_t flag ;
extern int timer_;
extern int TARGE_X;
extern int TARGE_Y;

//################################################

#endif // FUNC_H
