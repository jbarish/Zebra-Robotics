#!/usr/bin/env python
import cv2
import numpy as np
from picamera import PiCamera
from time import sleep
from detectColor import findColor
camera = PiCamera()

def clickImage():	
	camera.start_preview(fullscreen=False, window=(100,20,640,480))
	i=1
	camera.capture('/home/pi/Robotics/Zebra-Robotics/python/pic%s.jpg' % i)
	camera.stop_preview()
	#sleep(2)

def processImage():
	fn = 'pic1'
	img = cv2.imread(fn+'.jpg')
	img = cv2.resize(img, (500, 500)) 

	#dims = img.shape

	M = cv2.getRotationMatrix2D((500/2,500/2),180,1)
	img = cv2.warpAffine(img,M,(500,500))

	crop_img = img[250:500, 0:500] 

	cv2.imwrite(fn+'.jpg', crop_img)

	# NOTE: its img[y: y + h, x: x + w] and *not* img[x: x + w, y: y + h]

	'''
	for i in range(500):
  	  cv2.circle(crop_img, (i,250), 1, (255,255,0), 1)
	'''

	for i in range(250):
 	   cv2.circle(crop_img, (249,i), 1, (255, 255,255), 1)
	return crop_img

def processImage1():
	fn = 'pic1'
	img = cv2.imread(fn+'.jpg')
	img = cv2.resize(img, (500, 500)) 

	cv2.imwrite(fn+'.jpg', img)
        return img


def fillCol(crop_img):
    for y in range(0,249):  #240,241
        for x in range(0, 499):
            col = crop_img[y,x]            
            if (col[0]<50 and col[1]<50 and col[2]>70):  #B, G, R
                #print(x,y,"RED")
                cv2.circle(crop_img, (x,y), 1, (255,255,255), 5)
    cv2.imwrite('new.jpg', crop_img)

def getDist1(crop_img, color):
    min = 1000
    max = -1000
    print("inside getDist1, color : ",color)
    for y in range(230,250):  #240,241
        for x in range(0, 499):
            col = crop_img[y,x]
            if color==1:    #RED
                if (col[0]<50 and col[1]<50 and col[2]>70):
                    if(x<min):
                        min=x
                    if(x>max):
                        max=x
                    #cv2.circle(crop_img, (x,y), 1, (255,0,0), 2)
            elif color==3:    #BLUE
                if (col[0]>100 and col[1]<50 and col[2]<50):
                    if(x<min):
                        min=x
                    if(x>max):
                        max=x
            elif color==2:    #GREEN
                if (col[0]<50 and col[1]>100 and col[2]<50):
                    if(x<min):
                        min=x
                    if(x>max):
                        max=x
            elif color==0:    #YELLOW
                if (col[0]<50 and col[1]>90 and col[2]>90):
                    if(x<min):
                        min=x
                    if(x>max):
                        max=x
                
    cv2.circle(crop_img, (min,y), 1, (255,255,255), 2)
    cv2.circle(crop_img, (max,y), 1, (255,255,255), 2)
    temp = (int)((min+max)/2)
    for i in range(250):
        cv2.circle(crop_img, (temp,i), 1, (255,255,255), 1)
    print("temp=",temp)
    dist = temp - 249
    print("dist=",dist)
    cv2.imwrite('new.jpg', crop_img)       
    return dist

def checkAlignment(dist):
    if dist>25 and dist <= 55 and dist != -249:  #right arm
        return 1
    elif dist<-25 and dist >= -55 and dist != -249: #left arm
        return 2
    elif dist < -55 and dist != -249: #left bot
        return 3
    elif dist > 55 and dist != -249: #right bot
        return 4
    elif dist>=-25 and dist<=25:
        return 0
    elif dist == -249:
        return -1

'''
#crop_img = processImage()
file = 'grab_19.jpg'
crop_img = cv2.imread(file)
color = findColor(file)  # 0-red, 1-green, 2-blue, 3-yellow
#fillCol(crop_img)
dist = getDist1(crop_img, color)
'''



