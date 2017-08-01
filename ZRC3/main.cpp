#include "driver.h"

int main(){
	startOI_MT ("/dev/ttyUSB0");
	enterFullMode ();
	Driver* driver = new Driver();
	driver->driveForward(40,300);
	enterSafeMode ();
    stopOI_MT();  // close the comm ports 
   

}