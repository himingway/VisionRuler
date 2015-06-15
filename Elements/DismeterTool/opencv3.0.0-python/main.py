# -*- coding: UTF-8 -*-
# main.py
import cv2
import numpy

def nothing(x):
    pass
cv2.namedWindow('image')
cv2.createTrackbar('Threshold','image',140,255,nothing)
cv2.createTrackbar('DBlur','image',8,15,nothing)
while(1):
    k=cv2.waitKey(1)&0xFF
    if k==27:
        cv2.destroyAllWindows()
    Threshold=cv2.getTrackbarPos('Threshold','image')
    DBlur=cv2.getTrackbarPos('DBlur','image')
    src = cv2.imread("1.bmp", 1)
    cv2.imshow("image",src)
    img = cv2.cvtColor(src, cv2.COLOR_RGB2GRAY)
    a,img2 = cv2.threshold(img,Threshold,255,cv2.THRESH_BINARY)
    img3 = cv2.medianBlur(img2,(2*DBlur+1))
    img5,contours,hierarchy=cv2.findContours(img3,cv2.RETR_CCOMP,cv2.CHAIN_APPROX_NONE)
    if(len(contours)>=3):
        img6= cv2.drawContours(img5,contours,2,(255,255,0), 1)
        img6= cv2.drawContours(img5,contours,0,(255,255,0), 1)
        center1,radius1=cv2.minEnclosingCircle(contours[0])
        center2,radius2=cv2.minEnclosingCircle(contours[2])
        img7 = cv2.circle(src,(int(center1[0]),int(center1[1])),int(radius1),(0,0,255),2)
        img7 = cv2.circle(src,(int(center1[0]),int(center2[1])),int(radius2),(0,130,0),2)
        a=str(round((float(radius1)/float(radius2)*150.0),2))
        b=str(radius2)
        cv2.putText(src,"r= "+a+"um", (110,123), cv2.FONT_HERSHEY_SIMPLEX, 1, (0,0,255),2)
        cv2.putText(src,"R=150.00"+"um", (110,90), cv2.FONT_HERSHEY_SIMPLEX, 1,(0,130,0),2)
        cv2.imshow("image",src)
        cv2.imshow("image",src)   
