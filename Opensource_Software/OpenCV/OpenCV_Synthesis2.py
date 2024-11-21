import cv2
import numpy as np

alpha = 0.5

img1 = cv2.imread('images/cat2.jpg')
img2 = cv2.imread('images/effect1.png')

img1 = cv2.resize(img1 , (512, 512) )
img2 = cv2.resize(img2 , (512, 512) )

cv2.imshow("cat2", img1 )
cv2.imshow("effect1", img2 )

blended = ( img1 * alpha + img2 * (1-alpha) )
blended = blended.astype(np.uint8) # 소수점 발생을 제거하기 위함

blended2 = cv2.add( img1, img2 )

cv2.imshow('img1 * alpha + img2 * (1-alpha)', blended)
cv2.imshow('add_blend', blended2)
