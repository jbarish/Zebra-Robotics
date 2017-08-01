/***********************************************************************
  Action.cpp
  This file is internal use only for robot challenge -L Yang
***********************************************************************/

#include <iostream>
#include <fstream>
#include <unistd.h>
//#include <thread>
#include <cstdlib>
#include <time.h>
#include <cmath>
#include <ctime>
#include "func.h"
#include "Action.h"

using namespace std;
//using namespace cv;
using namespace _ROBOT;


Arm::Arm():mArmIo(0),m_timeout(0)
{
}

Arm::~Arm()
{
    if(mArmIo> 0){

        close(mArmIo);
    }

}

int Arm::init(std::string port)
{
    int serialIo = open((char*)port.c_str(), O_RDWR | O_NOCTTY);
    if (serialIo == -1){
        return ERROR::NOSUCHDEVICE;
    }
    sleep(3);

    struct termios tio;
    std::memset(&tio, 0,sizeof(tio));
    tio.c_cflag = B115200 | CS8 | CLOCAL | CREAD;
    tio.c_iflag = IGNPAR;

    tio.c_cc[VTIME]    = 1;
    tio.c_cc[VMIN]     = 0;
    tcflush(serialIo, TCIFLUSH);
    tcsetattr(serialIo, TCSANOW, &tio);

    mArmIo= serialIo ;

    return 0;

}


int Arm::done(void)
{

    if(mArmIo == 0) return 0;

    if(m_timeout)
    {
        char data[2];

        int err = receive(data,1);
        if(err < 0) {
            cout << "recieve erro !" << err << endl;
            return -1;
        }
        if(data[0] == '0') { //arm is done moving
           cout << "finished" <<endl;
           m_timeout = 0;
           return 0;
        }
        --m_timeout;
        cout << "=";
        if(!m_timeout) {
            cout << "time out " << endl;
            return 0;
        }
    }
    return -1;

}
int Arm::prepare(void)
{
    int err =  send("7");
    return err;
}

int Arm::pickup(void)
{
    return send("8");

}

int Arm::dropdown(void)
{
    return send("9");

}

int Arm::goHome(void)
{
   return send("a");
   m_timeout = 1; //no need to wait long
}

int Arm::send(char const* data)
{
    send(data, 1);
    return 0;
}
int Arm::send(char const* data, int length)
{
    if(mArmIo == 0) return 0;
    int err= write(mArmIo,(void*)data,length);
    if (err<0){
        cout << "send error:" << err << endl;
        return -1;
    }
    m_timeout = TIMEOUT;
    return 0;
}

int Arm::receive(byte *data, int length)
{

    if(mArmIo == 0) return 0;

    int total= 0;
    while(total!=length){
        int len = read(mArmIo,&data[total],1);
        if (len <0){
            return -1;
        }
        else {
            total+=len;
        }

    }
    return 0;

}
/*
int PiCamera::capture_image(int *dx,int *dy)
{
    int x,y;
    cv::Mat image;
    int nCount=2; 

    Camera.set( CV_CAP_PROP_FORMAT, CV_8UC3 );
    if (!Camera.open()) {cerr<<"Error opening the camera"<<endl;return -1;}
    for ( int i=0; i<nCount; i++ ) {
        Camera.grab();
        Camera.retrieve ( image);
        if(image.empty()) {
           cout << "image empty:" << i<< endl;
          break;
        }
     }
    Camera.release();
    if(image.empty()) {
    
      return 0;
    }

    cv::cvtColor(image,image,cv::COLOR_BGR2RGB);
    CvPoint point;
    find_object(image, point);
    if((point.x == 0)&&(point.y== 0)){
      x = 105;
      y = 1;
    }else {

       x = point.x - TARGE_X;
       y = point.y - TARGE_Y;
    }
    *dx = x;
    *dy = y;
   if((abs(x) <=20)&& (abs(y) <= 20) ) return 0;
   else return -1;

}

IplImage* PiCamera::GetThresholdedImage(IplImage* img)
{
    IplImage* imgHSV = cvCreateImage(cvGetSize(img), 8, 3);
    cvCvtColor(img, imgHSV, CV_BGR2HSV);

    IplImage* imgThreshed = cvCreateImage(cvGetSize(img), 8, 1);

    cvInRangeS(imgHSV, cvScalar(0, 100, 100), cvScalar(10, 255, 255), imgThreshed);  
    cvReleaseImage(&imgHSV);
    return imgThreshed;
}


int PiCamera::find_object(Mat &image, CvPoint& point)
{

    IplImage* imgScribble = new IplImage(image);

     IplImage* imgYellowThresh = GetThresholdedImage(imgScribble);

    Mat frame = cvarrToMat(imgYellowThresh);
 
    CvMoments *moments = (CvMoments*)malloc(sizeof(CvMoments));
    cvMoments(imgYellowThresh, moments, 1);

    double moment10 = cvGetSpatialMoment(moments, 1, 0);
    double moment01 = cvGetSpatialMoment(moments, 0, 1);
    double area = cvGetCentralMoment(moments, 0, 0);

    point.x = 0;
    point.y = 0;

    if(area > 0) {
        point.x = moment10/area;
        point.y = moment01/area;
    }

    delete imgScribble;
    cvReleaseImage(&imgYellowThresh);
    delete moments;

    return 0;
}
*/
Action::Action():
 mStep(-1),mSpeed(0),mNextStep(0),mDone(0)
{
    memset(sensorData,0,sizeof(sensorData));
}

Action::~Action() {
}

void Action::stop(void)
{
    static int stopped = 0;
    if(stopped == 0) {
        stopped = 1;
        mRobot.dStraight(0);
        mRobot.modesafe();
        mRobot.stop();
        cout << "stop" <<endl;
    }
}

int Action::init(char arm, char robot)
{
    std::string port_arm,port_irobot;

    port_arm = port_string + arm;
    port_irobot = port_string + robot;

    cout << "arm:" << port_arm << endl;
    cout << "robot:" << port_irobot << endl;

    int err = mRobot.start(port_irobot);
    if(!err) mRobot.modefull();


    mArm.init(port_arm);
    readArm();
    set(&Action::prepare);
    mDone = 1;

    return 0;
}

int Action::run(void)
{

    if(mStep==0) {
        if(mSpeed != 0) {// we must run
            mRobot.dStraight(0);
            mSpeed = 0;
        }
        (*this)(mNextStep);

    } else if(mStep > 0){
        if(hitWall()) {
            mStep = 0;
        }else {
            mStep--;
        }

    } else {
        if(mDone == 1) {
            mDone = 0;
            (*this)(mNextStep);
        }
    }

    return 0;

}

bool Action::hitWall()
{
   if ((sensorData[(int)(SENSOR::bumpfleft)] > 1000) ||
       (sensorData[(int)(SENSOR::bumpfright)] > 1000)){
       cout << "#";
       return 1;
   } else {
       cout << ".";
       return 0;
   }

}
int turn_steps = 0;
const int Adjust_1_feet = 150;

void Action::adjust(int steps)
{
  /* static int adjust_counter = 0;
    int next = 0;
    int dx,dy;
    int diff = 0;

	diff = mPiCam.capture_image(&dx,&dy);

    if((diff == 0) ||(adjust_counter > 2)){ //in range, drop the object
        adjust_counter = 0;
        set(&Action::dropdown);

	} else { 
	    dy = dy /2;	
		
        if(abs(dx) > 40) {
            next =  Adjust_1_feet +dy + 1000;
            turn_steps = 20;
            if(abs(dx) > 100)  turn_steps = 40;
			if(dx < 0) turn_steps = turn_steps* (-1);
		}
        set(&Action::backward);
    }

    setSteps(steps,next);

    adjust_counter++;*/
}

void Action::forward(int steps)
{

    if(steps == FIRST_MOVE ) {
        mSpeed = INIT_SPEED_;
        unsigned short rw=40,lw=67; 
        mRobot.driveDirect(rw, lw);
        set(&Action::pickup);
    } else if(steps == SECOND_MOVE){
        mSpeed = SPEED_;
        set(&Action::adjust);
    } else {
        set(NULL);
    }

    if(steps != FIRST_MOVE) drive(mSpeed,pDrive::STRAIGHT);
    setSteps(steps,0);



}
void Action::backward(int steps)
{

    int speed;
    if(steps < 0) {
        speed = INIT_SPEED_;
        steps = abs(steps);

    } else {
        speed = INIT_SPEED_INVERSE;
        if(steps > 1000) steps = steps -1000;
    }

    int next = 0;
    mSpeed = speed;
    drive(speed,pDrive::STRAIGHT);

    if(turn_steps != 0 ) {
        set(&Action::turn);
        next = turn_steps;
        turn_steps = 0;

    } else {
        set(&Action::adjust);
    }

    setSteps(steps,next);  //need change

}

void Action::turn(int steps)
{
    mSpeed = INIT_SPEED_;

    if(steps < 0) {
        drive(mSpeed,pDrive::CCW);
        cout << " CCW" << endl;
    } else {
        drive(mSpeed,pDrive::CW);
        cout << " CW" << endl;
    }
    set(&Action::backward); // need to move forward
    steps = abs(steps);
    setSteps(steps,Adjust_1_feet*(-1));  //need change

}

void Action::reverse(int steps)
{

    mSpeed = INIT_SPEED_INVERSE;
    if(steps == FINAL_MOVE) mSpeed = SPEED_INVERSE;

    drive(mSpeed,pDrive::STRAIGHT);

    if(steps == FINAL_MOVE ) {
        set(NULL);
        setSteps(steps,0);
        mArm.goHome();
    }else {
       set(&Action::reverse);
       setSteps(steps,FINAL_MOVE);
    }

}

void Action::prepare(int steps)
{

    mArm.prepare();


    set(&Action::forward);
    setSteps(-1,FIRST_MOVE);

}

void Action::pickup(int steps)
{

    mArm.pickup();

    set(&Action::forward);
    setSteps(-1,SECOND_MOVE);

}

void Action::dropdown(int steps)
{
    mArm.dropdown();

    set(&Action::reverse);
    setSteps(-1,THIRD_MOVE/*DEGREE_180*/);

}
void Action::rotate(int steps)
{
   std::string command = "c" + std::to_string(steps);
   mArm.send(command.c_str(),command.length());
   set(&Action::dropdown);
   setSteps(-1,0);
}

int Action::readArm()
{
  /*
    std::function<void()> read =
            [this](){
        while (!flag){
           int err =  mArm.done();
           if(err == 0) {
               mDone = 1;
           }
           usleep(50);
        }

    };

    readThread = std::thread(read);
    readThread.detach();
    return 0;
  */
}
