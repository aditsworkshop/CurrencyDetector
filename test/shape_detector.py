#/usr/bin/python

'''
This program detects the basic geometric shapes based on the vertices.

What it does?

- Reads the image
- Converts into the grey image
- Use threshold(second parameter below) to realize the actual shape to concentrate in the given image
  threshold(<image>,<ThresholdValue>,<MaxThresholdValue>,1)
- Use findContours() to figure out the edges, ends
- Use approxPolyDP() to approximate the final image and its output is the list of vertices' value
  Hence, we find the length of the list and these denotes the vertices of the shape.
'''

import os
from subprocess import call
from sys import argv

import numpy as np
import cv2

# execute: python shape_detector.py <image_name>
# argv reads image name from the command line arguement and assigns it to the imagename
script,imagename = argv

# Read the image
img = cv2.imread(imagename)

# Get gray scale image version of the same`
gray = cv2.imread(imagename,0)

#ret,thresh = cv2.threshold(gray,127,255,1)
ret,thresh = cv2.threshold(gray,230,255,1)
cv2.imshow('Gray',gray)
cv2.waitKey(0)

contours,h = cv2.findContours(thresh,1,2)

for cnt in contours:
	approx = cv2.approxPolyDP(cnt,0.01*cv2.arcLength(cnt,True), True)
	vertices = len(approx)

	if vertices == 5:
		print "Pentagon"
		cv2.drawContours(img,[cnt],0,255,-1)
	elif vertices == 4:
		print "Square"
		cv2.drawContours(img,[cnt],0,(0,0,255),-1)
	elif vertices == 3:
		print "Triangle"
		cv2.drawContours(img,[cnt],0,(0,255,0),-1)
	elif vertices > 15:
		print "Circle"
		cv2.drawContours(img,[cnt],0,(0,255,255),-1)

cv2.imshow('img',img)
cv2.waitKey(0)
cv2.destroyAllWindows()
