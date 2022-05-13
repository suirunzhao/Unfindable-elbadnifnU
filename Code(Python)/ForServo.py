import mediapipe as mp
import numpy as np
import cv2
import serial
import sys
import time

#Setup Communication path for arduino
arduino = serial.Serial(port='/dev/cu.usbmodem14401', baudrate=9600)
time.sleep(2) #change the port(14401) showing in your Arduino IDE
print("Connected to Arduino...")


cap = cv2.VideoCapture(0) #When you connect to web camera chage 0 to 1 
cap.set(3,1280) #display size
cap.set(4,720)

facemesh = mp.solutions.face_mesh
face = facemesh.FaceMesh(static_image_mode=True, min_tracking_confidence=0.6, min_detection_confidence=0.6)
draw = mp.solutions.drawing_utils

while True:

	_, me = cap.read()

	rgb = cv2.cvtColor(me, cv2.COLOR_BGR2RGB)

	op = face.process(rgb)
	if op.multi_face_landmarks:
		for i in op.multi_face_landmarks:
			print(i.landmark[0].x*1280)
			xx = int(i.landmark[0].x*1280)
			print(xx)
			# sending data to arduino
			data = "X{0:d}YZ".format(xx)
			arduino.write(data.encode())

			
	cv2.imshow("window", cv2.flip(me,1)) #you can delete this if you do not want to show
	if cv2.waitKey(1) == 27:
		cap.release()
		cv2.destroyAllWindows()
		break
