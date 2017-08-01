import numpy as np
import cv2
from color import Color
	
lower_blue = np.array([110, 50, 50])									  
upper_blue = np.array([130, 255, 255])

lower_yellow = np.array([0,41,100])
upper_yellow = np.array([46,242,255])
'''
lower_yellow = np.array([20,100,100])
upper_yellow = np.array([30,255,255])
'''
lower_red = np.array([0,100,100])
upper_red = np.array([20,255,255])

lower_green = np.array([45,100,50])
upper_green = np.array([75,255,255])

def findRed(img):
	mask = cv2.inRange(img, lower_red, upper_red)
	count = cv2.countNonZero(mask)
	print("No of red pixels---->",count)
	return count

def findYellow(img):
	mask = cv2.inRange(img, lower_yellow, upper_yellow)
	count = cv2.countNonZero(mask)
	print("No of yellow pixels---->",count)
	return count

def findBlue(img):
	mask = cv2.inRange(img, lower_blue, upper_blue)
	count = cv2.countNonZero(mask)
	print("No of blue pixels---->",count)
	return count
	
def findGreen(img):
	mask = cv2.inRange(img, lower_green, upper_green)
	count = cv2.countNonZero(mask)
	print("No of green pixels---->",count)
	return count


def findColor(img):
	#img = cv2.imread(file)
	img = cv2.cvtColor(img, cv2.COLOR_BGR2HSV)
	r = findRed(img)
	g = findGreen(img)
	b = findBlue(img)
	y = findYellow(img)
	arr = [r,g,b,y]
	max = arr[0]
	pos = 0
	for i in range(1,4):
		if arr[i] > max:
			max = arr[i]
			pos = i

	colors = [Color.RED,Color.GREEN, Color.BLUE, Color.YELLOW]
	print("COLOR DETECTED - ", pos, colors[pos])
	return colors[pos]

#findColor("blue.jpg")
