#ifndef ACTION_H
#define ACTION_H
//#include <opencv2/opencv.hpp>
//#include <raspicam/raspicam_cv.h>
#include <irobot.h>
#include <createoi.h>
#pragma once

namespace _ROBOT{
class Action;

class Arm {
   public:
    Arm();
    ~Arm();
    int init(std::string port);
    int prepare(void);
    int pickup(void);
    int dropdown(void);
    int goHome(void);
    int done(void);
    void stop(void) {    
           if(mArmIo> 0){
               close(mArmIo);
              mArmIo = 0;
            };
         }
   private:
    const int TIMEOUT = 1000;
    int mArmIo;
    int m_timeout;

    int receive(byte *data, int length);
    int send(char const* data);
    int send(char const* data, int length);

    friend class Action;
};
/*
class PiCamera {
public:
    PiCamera(){};
   ~PiCamera(){};
    int capture_image(int *dx,int *dy);
private:
    raspicam::RaspiCam_Cv Camera;
    IplImage* GetThresholdedImage(IplImage* img);
    int find_object(cv::Mat &image, CvPoint& point);
    friend class Action;
};

*/
typedef void (Action::*stateHandler)(int);

#define set(target_)  \
    (mState = target_)


class Action {
    public:

    const int INIT_SPEED_ = 20;
       const int INIT_SPEED_INVERSE = -20;
       const int SPEED_ = 400;
       const int SPEED_INVERSE = -400;
       const int FIRST_MOVE = 480;
       const int SECOND_MOVE = 320;
       const int THIRD_MOVE = 98;
       const int FINAL_MOVE = 410;
       //const int DEGREE_180 =  98;


        Action(void);
         ~Action();

        int init(char arm, char robot);

        Arm* getArm() { return &mArm;}
        iRobot* getRobot() { return &mRobot;}

        void forward(int steps);
        void backward(int steps);
        void adjust(int steps);
        void turn(int steps);
        void reverse(int steps);
        void prepare(int steps);
        void pickup(int steps);
        void dropdown(int steps);
        void rotate(int steps);
        void operator()() {
                run();
            }

    private:
        const std::string port_string = "/dev/ttyUSB";
        Action& operator=(const Action& rhs );
        Action(const Action& rhs );
        void operator()(int s) { if(mState) (this->*mState)(s);
                                 else stop();
                               }

        std::thread  readThread;
        Arm       mArm;
	//	PiCamera  mPiCam;
        iRobot    mRobot;
        int       mStep;
        uint16_t  mSpeed;
        int       mNextStep;
        int       mDone;
        int       sensorData[100];
        int readArm();
        void drive(uint16_t speed, uint16_t radius){
                mRobot.drive(speed,radius);
        };
        int run(void);
        void stop(void);
        void setSteps(int current, int next)   {mStep = current;mNextStep = next;}
        bool hitWall();
        stateHandler mState;

     };

}

#endif
