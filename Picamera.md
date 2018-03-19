# Pi Camera 使用教學

這邊將Pi Camera的使用步驟分成三個部分 :   
- 硬體設定: 介紹如何在樹梅派的系統上啟動Pi Camera的功能，並檢查Pi Camera 有無正常運作。
- 軟體安裝: 介紹如何在樹梅派的系統上安裝Pi Camera 軟體套件的流程。
- 測試功能: 以Python程式語言設計簡單的程式測試Pi Camera 照相與錄影的功能。

## 硬體設定

### 啟動相機模組 : 


開啟樹梅派設定: sudo raspi-config
   ![image](https://github.com/MrLiuLiuLiu/RaspberryPi/blob/master/%E5%95%9F%E5%8B%95%E7%9B%B8%E6%A9%9F%E6%A8%A1%E7%B5%84-%E6%AD%A5%E9%A9%9F%E5%9B%9B.png)
   
選擇第5項 : Interfacing Options 

   ![image](https://github.com/MrLiuLiuLiu/RaspberryPi/blob/master/%E5%95%9F%E5%8B%95%E7%9B%B8%E6%A9%9F%E6%A8%A1%E7%B5%84-%E6%AD%A5%E9%A9%9F%E4%BA%8C.png)

選擇 Pi Camera , 按下Enable

   ![image](https://github.com/MrLiuLiuLiu/RaspberryPi/blob/master/%E5%95%9F%E5%8B%95%E7%9B%B8%E6%A9%9F%E6%A8%A1%E7%B5%84-%E6%AD%A5%E9%A9%9F%E4%B8%89.png)
   
   ![image](https://github.com/MrLiuLiuLiu/RaspberryPi/blob/master/%E5%95%9F%E5%8B%95%E7%9B%B8%E6%A9%9F%E6%A8%A1%E7%B5%84-%E6%AD%A5%E9%A9%9F%E5%9B%9B.png)

選擇 Finish

   ![image](https://github.com/MrLiuLiuLiu/RaspberryPi/blob/master/%E5%95%9F%E5%8B%95%E7%9B%B8%E6%A9%9F%E6%A8%A1%E7%B5%84-%E6%AD%A5%E9%A9%9F%E4%BA%94.png)

### 測試相機模組 :

在[樹梅派官網](https://www.raspberrypi.org/documentation/usage/camera/raspicam/ )有介紹到Picamera 拍照、錄影及圖像相關參數設定的指令，
這邊以Picamera 拍照的指令先測試 Picamera 能否正常運作，於命令提示列打上下列指令 : 

```raspistill -o output.jpg```
               
## 軟體安裝

在命令提示字列中安裝pi camera套件，網站中有提到兩種方式，進行安裝

### 直接以linux系統管理套件的指令 : 
```apt-get install python-picamera ```   		
### [以Python管理套件的指令](https://picamera.readthedocs.io/en/release-1.13/install.html): 
```pip install picamera ```

## 成果測試

### 實現照相功能 : 

#### 使用Python與 pi camera套件產生靜態圖像

使用capture()方法捕捉靜態圖像，程式碼參考[Getting started with picamera](https://projects.raspberrypi.org/en/projects/getting-started-with-picamera)

```
from time import sleep
from picamera import PiCamera

camera = PiCamera()
camera.resolution = (1024, 768) #設定圖片解析度
camera.start_preview() #圖片預覽
sleep(2) # Camera warm-up time
camera.capture('test.jpg') #將圖片轉成.jpg
```


####  使用Python 與 Open CV產生靜態圖像

這邊是參考[Accessing the Raspberry Pi Camera with OpenCV and Python](https://www.pyimagesearch.com/2015/03/30/accessing-the-raspberry-pi-camera-with-opencv-and-python/)的範例進行實作
```
# import the necessary packages
from picamera.array import PiRGBArray
from picamera import PiCamera
import time
import cv2
 
# initialize the camera and grab a reference to the raw camera capture
camera = PiCamera()
rawCapture = PiRGBArray(camera)
 
time.sleep(0.1)
 
# grab an image from the camera
camera.capture(rawCapture, format="bgr")
image = rawCapture.array
 
# display the image on screen and wait for a keypress
cv2.imshow("Image", image)
cv2.waitKey(0)

(2.2)開啟命令提示列，執行 : python test_image.py
```

### 實現攝影功能

#### 使用Python與 pi camera套件紀錄動態影像

使用start_recording()方法紀錄動態影像，程式碼參考[Getting started with picamera](https://projects.raspberrypi.org/en/projects/getting-started-with-picamera)
```
import picamera
camera = picamera.PiCamera()
camera.resolution = (640, 480)  #設定影像解析度 
camera.start_recording('record_video.h264') #開啟攝影功能camera.wait_recording(60) #設定攝影時間          
camera.stop_recording()  #關閉攝影功能
```

使用Python 與 Open CV紀錄動態影像

```
# import the necessary packages
from picamera.array import PiRGBArray
from picamera import PiCamera
import time
import cv2
 
# initialize the camera and grab a reference to the raw camera capture
camera = PiCamera()
camera.resolution = (640, 480)
camera.framerate = 32
rawCapture = PiRGBArray(camera, size=(640, 480))

time.sleep(0.1)
 
# capture frames from the camera
for frame in camera.capture_continuous(rawCapture, format="bgr", use_video_port=True):

	image = frame.array
 
	# show the frame
	cv2.imshow("Frame", image)
	key = cv2.waitKey(1) & 0xFF
	
	rawCapture.truncate(0)
	
	if key == ord("q"):
		break
```
## 參考網站 :

[pi camera & opencv & python 使用教學](https://www.pyimagesearch.com/2015/03/30/accessing-the-raspberry-pi-camera-with-opencv-and-python/) 

[pi camera api 參考資料](http://picamera.readthedocs.io/en/release-1.13/index.html) 

