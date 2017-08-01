#include "driver.h"
#include <iostream>


int straighten(int hit){
	int hitl = hit == 1 ? 1 : 0;
	int hitr = hit == 2 ? 1: 0;
	

	while(1){
		std::cout << "adjusting" << std::endl;

		int* sensorList = getAllSensors();
		//Left cliff is 21
		
std::cout << "      " <<sensorList[21] << ", " 
			<< sensorList[22] << ", " 
			<< sensorList[23] << ", " 
			<< sensorList[24] << std::endl;
		int left = sensorList[21];
		int right = sensorList[24];
		int fl = sensorList[22];
		int fr = sensorList[23];
		if(left <2000 && right < 2000){
			break;
		}else if (left < 2000){
			std::cout << "LEFT" << std::endl;
			directDrive(-20, -20);
			usleep(60000); 	
			directDrive(0, 20);
			hitl = 1;
		}else if (right < 2000){
			std::cout << "RIGHT" << std::endl;
			directDrive(-20, -20);
			usleep(60000); 	
			directDrive(20, 0);
			hitr = 1;
		}else if (fl < 2000 && hitr){
			//left overturned
			std::cout <<"OverturnedLeft" <<std::endl;
			while(right > 2000){
				int* sensorList = getAllSensors();
				int right = sensorList[24];
				directDrive(-0, -20);
				usleep(60000);
			}
		}else if (fr < 2000 && hitl){
			std::cout <<"OverturnedRight" <<std::endl;
			//right overturned
			while(left > 2000){
				int* sensorList = getAllSensors();
				int left = sensorList[21];
				directDrive(-20, 0);
				usleep(60000);
			}
			
		}else{
			directDrive(20,20);
		}
		usleep(10000); 
	}
return 0;

}

int Driver::driveForward(int speed, int distance){
	int startDist = getDistance();
	int currentdist = 0;
	int lastLeft =getLeftEncoder();
	int lastRight =getRightEncoder(); 
	int rhit = 0;
	int lhit = 0;
	while(1){
		int speedL = speed;
		int speedR = speed;
		currentdist+= getDistance()-startDist;
		if(currentdist >=distance){
			break;
		}
		int left = getLeftEncoder();
		int right= getRightEncoder(); 
		std::cout << left << ", " << right<<std::endl;
		int dleft = left-lastLeft;
		int dright = right-lastRight;
		
		std::cout << dleft<< ", " << dright<<std::endl;
		if(dright > dleft){
			int adjust = (dright-dleft)/2;
			if(adjust < -20 )
                    		adjust = -20;
			speedL +=(adjust*1.1);
			speedR -=adjust;
			printf("adjust < 0 %d \r\n", adjust);
			std::cout << speedL << ", "<<  speedR << std::endl;
		}else{
			int adjust = (dleft-dright)/2;
			if (adjust > 20 )
                    		adjust = 20;
			speedL -=adjust;
			speedR +=(adjust*1.1);
			printf("adjust > 0 %d \r\n", adjust);
		}
		directDrive(speedL, speedR);
		usleep(60000); 
		int* sensorList = getAllSensors();
		//Left cliff is 21
		std::cout << "      " <<sensorList[21] << ", " 
			<< sensorList[22] << ", " 
			<< sensorList[23] << ", " 
			<< sensorList[24] << std::endl;
		if(sensorList[21] < 2000){
			lhit = 1;
		}

		if(sensorList[24] < 2000){
			rhit = 1;
		}
		if(currentdist > 100 && currentdist< 200){
			if(sensorList[21] < 2000){
				directDrive(0, 20);
				usleep(150000);
				lastLeft = 0;
				lastRight = 0;
			}

			if(sensorList[24] < 2000){
				directDrive(20, 0);
				usleep(150000);
				lastLeft = 0;
				lastRight = 0;
			}
		}

		if((rhit || lhit) &&(rhit!=lhit)){
			directDrive(0,0);
			usleep(60000);
			directDrive(-20,-20);
			usleep(150000);
			int ind = rhit ? 2 : 1;
			straighten(ind);
			rhit = lhit =0;
			//startDist = getDistance()- currentdist;
		}else{
			currentdist+= getDistance()-startDist;
		}
	

}
	straighten(0);
  return 0;
}

int Driver::turnRight(){
  return 0;
}
int Driver::turnLeft(){
	std::cout << "turning" <<std::endl;
	int hit = 0;
	directDrive(20,20);
	usleep(280000);
	while(1){
		directDrive(-20, 20);
		int* sensorList = getAllSensors();	
		if(hit == 0 && sensorList[22] < 2000){
			hit = 1;
		}else if (hit == 1 && sensorList[22] >2000){
			usleep(90000);
			break;
		}

		usleep(60000); 
	}
	
}

