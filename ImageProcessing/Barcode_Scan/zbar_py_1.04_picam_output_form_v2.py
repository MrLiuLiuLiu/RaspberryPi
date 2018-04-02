from picamera.array import PiRGBArray
from picamera import PiCamera
from PIL import Image
import RPi.GPIO as GPIO
import time
import sys
import cv2
import zbar
import numpy
import csv
# Initialise Raspberry Pi camera
camera = PiCamera()
camera.resolution = (640, 480)
rawCapture = PiRGBArray(camera, size=(640,480))

# Initialise GPIO
GPIO.setmode(GPIO.BOARD)
GPIO.setup(12, GPIO.OUT)
Buzz = GPIO.PWM(12, 50)  # Set GPIO Channel For Buzzer =12 frequency=50Hz

# Allow camera to warm up
time.sleep(0.1)
print "PiCamera ready"

# Create a barcode reader
scanner = zbar.Scanner()

try:

    # Capture frames from the camera
    for frame in camera.capture_continuous(rawCapture, format="bgr", use_video_port=True):
            
	# grab the raw NumPy array representing the output image
        output = frame.array.copy()
        gray = cv2.cvtColor(output, cv2.COLOR_BGR2GRAY,dstCn=0)
        Barcodeimage = Image.fromarray(gray)


  	# scan the Barcodeimage for barcodes
        results = scanner.scan(Barcodeimage)

        if(len(results) > 0):

                ofile  = open('test.csv', 'a')
                writer = csv.writer(ofile)
                for symbol in results :
                    
                    print(symbol.type,symbol.data)
                    # update scanned record to csv 
                    writer.writerow((str(symbol.type),str(symbol.data)))
    	
        ofile.close()
    	# buzz 1 second for data has uploaded
		Buzz.start(50)
    	time.sleep(1)
        Buzz.stop()
        	
	# show the frame
        cv2.imshow("image", output)
	# clear the stream in preparation for the next frame
        rawCapture.truncate(0)
    
        # Wait for the key       
        keypress = cv2.waitKey(1) & 0xFF
        if keypress == ord('q'):
               break

finally:
       
	GPIO.cleanup()