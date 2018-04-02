# 條碼掃描-使用Pi Camera & OpenCV

## 簡介

條碼辨識是利用條碼上黑白條對光的反射率來解讀條碼符號上的數據。本專案是以Raspberry Pi 與Pi Camera作為條碼掃描器的基礎，結合 z-bar 套件實現條碼辨識，圖示為條碼辨識的運作架構，分成三個區塊，每個區塊實現一個功能:

1. 條碼掃描 : 以z-bar套件實作條碼辨識，可掃描的條碼類型: 二維條碼
2. 聲音提醒 : Pi Camera鏡頭偵測到條碼後發出提示聲，告知使用者偵測到條碼
3. 條碼紀錄 : 把掃描的條碼數據紀錄至csv檔
 
## 實作說明

### 條碼掃描 

本專案以[z-bar 1.04](https://pypi.python.org/pypi/zbar-py/1.0.4)版本套件實作條碼辨識，但使用的攝像頭是Pi camera 並無自動對焦，因此可以掃描條碼類型為:二維條碼。

 ```
from picamera.array import PiRGBArray
from picamera import PiCamera
from PIL import Image
import time
import sys
import cv2
import zbar
import numpy

# Initialise Raspberry Pi camera
camera = PiCamera()
camera.resolution = (640, 480)
rawCapture = PiRGBArray(camera, size=(640,480))

# allow camera to warm up
time.sleep(0.1)
print "PiCamera ready"

# Create a barcode reader
scanner = zbar.Scanner()
# Capture frames from the camera
# cap = cv2.VideoCapture(0)

while(True):
for frame in camera.capture_continuous(rawCapture, format="bgr", use_video_port=True):
    # grab the raw NumPy array representing the output image
    output = frame.array.copy()
    gray = cv2.cvtColor(output, cv2.COLOR_BGR2GRAY,dstCn=0)
    Barcodeimage = Image.fromarray(gray)

    # scan the Barcodeimage for barcodes
    results = scanner.scan(Barcodeimage)

    # extract results
    for symbol in results :
        # do something useful with results
        print(symbol.type,symbol.data)
        
    # show the frame
    cv2.imshow("image", frame)
    # clear stream for next frame
    rawCapture.truncate(0)

    # Wait for the  key
    keypress = cv2.waitKey(1) & 0xFF
    if keypress == ord('q'):
        break

# When everything is done, release the capture
camera.close()
cv2.destroyAllWindows()
 ```
 
### 安裝UV4L驅動程式(選擇性)

在/dev/video0中找不到[Pi Camera Module](https://www.ics.com/blog/raspberry-pi-camera-module )，是因為Raspberry Pi的相機模組是由CSI介面傳輸，Linux系統的攝影驅動程式並不支援此類型，需要安裝UV4L驅動程式才可以啟動相機模組，詳細說明參照:[Raspberry Pi 3 CSI介面攝影機的UV4L驅動安裝](http://kenneth.tw/2017/03/13/raspberry-pi-3-csi介面攝影機的uv4l驅動安裝-2) & [解決 Raspberry Pi 找不到 /dev/video0](http://open-rotorman.blogspot.tw/2014/06/raspberry-pi-raspberry-pi-devvideo0.html)。

### 聲音提醒

以RPI.GPIO套件的[PWM](https://sourceforge.net/p/raspberry-gpio-python/wiki/PWM/)函式控制[蜂鳴器](https://sites.google.com/site/zsgititit/home/raspberry-shu-mei-pai/raspberry-shi-yong-fengbuzzier)的聲響。程式運作的流程是先判斷Pi Camera 攝像頭是否讀取到條碼型式，若有則發出提示聲，若無則不發出聲響。

蜂鳴器補充說明:[Buzzer Module](https://www.sunfounder.com/learn/sensor-kit-v2-0-for-raspberry-pi-b-plus/lesson-10-buzzer-module-sensor-kit-v2-0-for-b-plus.html)

[!image](https://github.com/MrLiuLiuLiu/RaspberryPi/blob/master/Using%20PWM%20in%20RPi.GPIO%20For%20Buzzer2.png)
 ```
for frame in camera.capture_continuous(rawCapture, format="bgr", use_video_port=True):
            
	# grab the raw NumPy array representing the output image
        output = frame.array.copy()
        gray = cv2.cvtColor(output, cv2.COLOR_BGR2GRAY,dstCn=0)
        Barcodeimage = Image.fromarray(gray)

  	# scan the Barcodeimage for barcodes
        results = scanner.scan(Barcodeimage)

        if(len(results) > 0):

                for symbol in results :
                    
                    print(symbol.type,symbol.data)
                   
    	# buzz 1 second for data has uploaded
		buzz.start(50)
    	time.sleep(1)
        buzz.stop()
        	
	# show the frame
        cv2.imshow("image", output)
	# clear the stream in preparation for the next frame
        rawCapture.truncate(0)
    
        # Wait for the key       
        keypress = cv2.waitKey(1) & 0xFF
        if keypress == ord('q'):
               break
 ```

假如程式執行時會出現下圖的警告，解決辦法是在picamera 接收影像的程式區塊中加入try ….. catch 異常處理方式，詳細說明參照:
![image](https://github.com/MrLiuLiuLiu/RaspberryPi/blob/master/Warning%20For%20Using%20GPIO.png)

- [How To Best Use Try Except In Python – Especially For Beginners](http://www.techbeamers.com/use-try-except-python/)
- [try、raise 陳述句](https://openhome.cc/Gossip/Python/TryStatement.html)
- [Unified try/except/finally](https://docs.python.org/2.5/whatsnew/pep-341.html)

![image](https://github.com/MrLiuLiuLiu/RaspberryPi/blob/master/Using%20Try...Finally%20to%20Eliminate%20Warning.png)
 ```
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

		# open .csv to wait for uploading scanned data
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
 ```
 
### 條碼紀錄 

透過csv套件與檔案處理觀念的結合，實作出掃描後可以紀錄條碼數據的功能。程式運作的流程是當Pi camera 攝像頭讀取到條碼型式時， 便將條碼的數據紀錄至csv檔，檔案屬性設定為a，詳細說明參照:

- [Python對於CSV文檔的讀取與寫入](https://hk.saowen.com/a/e486e7398f537ec9100f26afb18e2093dd34b830e94259628b3d2bd3b0b68d6c) 
- [Python 学习笔记 （6）—— 读写文件](http://blog.51cto.com/pmghong/1349978)
- [Python - 文件I / O](http://www.tutorialspoint.com/python/python_files_io.htm) 

[!image](https://github.com/MrLiuLiuLiu/RaspberryPi/blob/master/Using%20csv%20package%20%26%20Python%20IO%20to%20%20upload%20scanned%20data.png)
```
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

 ```

### 常用指令

- dpkg -L package_name : 檢視 apt-get install 檔案安裝的路徑 ，說明參考[Where does apt-get install GO](https://www.raspberrypi.org/forums/viewtopic.php?t=59463)
- sudo nano /etc/modules : 編輯/etc/modules ，自動匯入模組
- rm – 刪除檔案及目錄指令 : rm –r  目錄名稱
