import create
import driver
from time import sleep
import math
import armcontrol
from camSet import clickImage
from camSet import processImage
from camSet import getDist1
from camSet import checkAlignment
from detectColor import findColor
from camSet import processImage1
from detectColor import findColor
from camSet import fillCol
import binmanager
import sys

def pickObject():
    clickImage()
    crop_img = processImage()
    color = findColor(crop_img)
    #dist = getDist1(crop_img, color)
    angle = "4"  #3
    speed = 50
    while 1:
       #sleep(1)
       print("---------------------------------------")
       clickImage()
       crop_img = processImage()
       #color = findColor(crop_img)
       dist = getDist1(crop_img, color)
       checkAlign = checkAlignment(dist, color)
       val=0.08
       
       if checkAlign == 1:
            print("MOVE RIGHT")
            arm.sendCmd("6")   
            arm.sendCmd(angle) 
       elif checkAlign == 2:
            print("MOVE LEFT")
            arm.sendCmd("7")
            arm.sendCmd(angle) 
       elif checkAlign == 3:
            print("BOT TURNS LEFT")
            temp = (0.35 * abs(dist))/(248)
            print("temp = ",temp)
            if temp <= val:
                driver.turnSlightLeft(val, speed) #1 degree (11 units) = 0.02
            else:
                driver.turnSlightLeft(temp, speed)
       elif checkAlign == 4:
            print("BOT TURNS RIGHT")
            temp = (0.35 * abs(dist))/(248)
            print("temp = ",temp)
            if temp <= val:
                driver.turnSlightLeft(val, speed)
            else:
                driver.turnSlightRight(temp, speed)
       elif checkAlign == 0:
            print("GRAB")
            arm.sendCmd("3")
            sleep(3.5)
            break
       elif checkAlign == -1:
            print("BLOCK IS NOT FOUND")
            turnsL = 0
            turnsR = 0
            i=0
            val = 0.1
            while(checkAlignment(dist, color) == -1 and i<2):
                print("CHECK IN LEFT...",i)
                driver.turnSlightLeft(val, speed)
                turnsL+=1
                #sleep(1)
                clickImage()
                crop_img = processImage()
                dist = getDist1(crop_img, color)
                i+=1

            print("i = ",i)
            if i==2:        
                print("BLOCK STILL NOT FOUND")
                print("GOTO INITIAL POSITION")
                arm.sendCmd("8")
                sleep(1)
                driver.turnSlightRight(val*3, speed)

            i=0
            while(checkAlignment(dist, color) == -1):
                print("CHECK IN RIGHT...",i)
                driver.turnSlightRight(val, speed)
                #sleep(1)
                clickImage()
                crop_img = processImage()
                dist = getDist1(crop_img, color)
                #i+=1
    return color



exitY = sys.argv[1]

bm = binmanager.BinManager()
driver = driver.Driver(0,0, bm)
#driver = driver.Driver(3,1, bm)
arm = armcontrol.ArmControl("/dev/ttyUSB0")
sleep(8)
#arm.sendCmd("9")
#sleep(3)
#driver.driveScan()
'''
print "++++++++++++++++++++Scanning Bins++++++++++++++++++"
arm.sendCmd("9")
#sleep(1)
driver.driveScan()



arm.sendCmd("2")
#sleep(1)
print "++++++++++++++++++++Driving to First Block ++++++++++++++++++"

driver.driveTo(5,6)

#clickImage()
#crop_img = processImage()
color = pickObject()
#sleep(5)
print "++++++++++++++++++++Driving to First Bin at Pos" ,  bm.getPosByColor(color), "++++++++++++++++++"
if bm.getPosByColor(color)[0] != -1 :
   driver.driveTo(bm.getPosByColor(color)[0], bm.getPosByColor(color)[1])
   driver.driveTo(bm.getPosByColor(color)[0]-1, bm.getPosByColor(color)[1])

   arm.sendCmd("5")
   sleep(0.5)
else:
   oddout = bm.getPosByColor(color)
   arm.sendCmd("2")
   #sleep(1)
print "++++++++++++++++++++Driving to Second Block++++++++++++++++++"
driver.driveTo(3,5)
arm.sendCmd("2")
#sleep(1)
driver.driveTo(5,5)

color = pickObject()
#sleep(5)
print "++++++++++++++++++++Driving to 2 Bin at Pos" ,  bm.getPosByColor(color), "++++++++++++++++++"
if bm.getPosByColor(color)[0] != -1 :
   driver.driveTo(bm.getPosByColor(color)[0], bm.getPosByColor(color)[1])
   driver.driveTo(bm.getPosByColor(color)[0]-1, bm.getPosByColor(color)[1])

   arm.sendCmd("5")
   sleep(0.5)
else:
   oddout = bm.getPosByColor(color)
   arm.sendCmd("1")
   sleep(3)
print "++++++++++++++++++++Driving to Third Block++++++++++++++++++"
driver.driveTo(3,4)
arm.sendCmd("2")
#sleep(1)
driver.driveTo(5,4)

color = pickObject()
#sleep(5)
print "++++++++++++++++++++Driving to 3 Bin at Pos" ,  bm.getPosByColor(color), "++++++++++++++++++"
if bm.getPosByColor(color)[0] != -1 :
   driver.driveTo(bm.getPosByColor(color)[0], bm.getPosByColor(color)[1])
   driver.driveTo(bm.getPosByColor(color)[0]-1, bm.getPosByColor(color)[1])

   arm.sendCmd("5")
   sleep(0.5)
else:
   oddout = bm.getPosByColor(color)
   arm.sendCmd("1")
   sleep(3)
print "++++++++++++++++++++Driving to Last Block++++++++++++++++++"
driver.driveTo(3,3)
arm.sendCmd("2")
#sleep(1)
driver.driveTo(5,3)

color = pickObject()
#sleep(5)
print "++++++++++++++++++++Driving to 4 Bin at Pos" ,  bm.getPosByColor(color), "++++++++++++++++++"
if bm.getPosByColor(color)[0] != -1 :
   driver.driveTo(bm.getPosByColor(color)[0], bm.getPosByColor(color)[1])
   driver.driveTo(bm.getPosByColor(color)[0]-1, bm.getPosByColor(color)[1])
   arm.sendCmd("5")
   sleep(0.5)
else:
   oddout = bm.getPosByColor(color)

print "++++++++++++++++++++Driving to Odd one Out Block++++++++++++++++++"
driver.driveTo(oddout[0]-1, oddout[1])
arm.sendCmd("2")
#sleep(1)
driver.driveTo(oddout[0], oddout[1])
pickObject()
#sleep(5)
#leave
driver.driveTo(6, 6)
driver.driveTo(9, 6)


'''
 
arm.sendCmd("2")
driver.driveTo(0,1,100)
#sleep(1)
pickObject()
driver.disable()