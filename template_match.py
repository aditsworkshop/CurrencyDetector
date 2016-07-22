#! /usr/bin/python

import cv2
import numpy as np

imagepath = './images/1000.jpg'
templatepath = './templates/1000_template.jpg'

img = cv2.imread(imagepath)
cv2.imshow('detected', img)
cv2.waitKey(0)
img = cv2.imread(templatepath)
cv2.imshow('detected', img)
cv2.waitKey(0)

img_clr = cv2.imread(imagepath)
grey_img = cv2.cvtColor(img_clr, cv2.COLOR_BGR2GRAY)

template_clr = cv2.imread(templatepath,0)
w,h = template_clr.shape[::-1]

res = cv2.matchTemplate(grey_img, template_clr, cv2.TM_CCOEFF_NORMED)
threshold = 0.90
loc = np.where( res >= threshold )

print loc

for pt in zip(*loc[::-1]):
	cv2.rectangle(grey_img, pt,(pt[0]+w,pt[1]+h),(0,255,255),2)

cv2.imshow('detected', grey_img)
cv2.waitKey(0)
cv2.destroyAllWindows()
