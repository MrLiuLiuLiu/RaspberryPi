

1.	pi camera 實務應用

3.1網路即時影像監控


	-簡介
要能夠在網路上達成即時影像監控的功能，這邊以串流技術實現。
串流是一種能將影音檔案在網路傳輸的過程，提供即時播放的技術，原理是把一連串的影音資料壓縮後，以網際網路分段傳送的方式，將檔案傳輸至用戶端，讓用戶不需要等待檔案下載完成，即可觀賞影像。

    -工具         
         這邊分別介紹motion和 mjpeg streamer，以實現即時影像監控的功能

Motion


(1)	安裝motion服務:

(1.1)	更新系統至最新版本

sudo apt-get update
			
(1.2)	安裝motion軟體

  sudo apt-get install motion

(2)	設定motion服務

(2.1) 修改motion .conf 設定檔參數

sudo nano /etc/motion/motion.conf

(2.1.1)修改關鍵設定值

- daemon : 設定為 on
- webcam_localhost : 設定為 off

(2.1.2)修改設定值(選擇性)

-framerate(及時更新畫面的速率): 設定為100
     
- stream_maxrate(每秒捕捉畫面的速率) : 設定為100

-output_pictures off

-ffmpeg_output_movies off

(2.1.3)管理motion連線使用 port 8080 : control_port 8080
(2.1.4)連線webcam使用port 8081 : web_port 8081

  (2.2) 設定motion為常駐服務 

       sudo nano /etc/default/motion

       (2.2.1) 修改start_motion_daemon = yes


(3)	啟動/關閉motion服務


(3.1)啟動motion網路串流服務

    sudo service motion start

(3.2)關閉motion網路串流服務
  
    sudo service motion start

(4)	連線motion服務

(4.1)查詢raspberry pi IP 

    Sudo ifconfig

(4.2)至網站打上raspberry pi IP : 8081

(5)	更改motion圖檔儲存路徑


(5.1)建立放置圖檔的新資料夾

   Mkdir存放圖檔資料夾名稱

(5.2) 更改motion所屬群組

    Sudo  chgrp motion /home/pi/存放圖檔資料夾名稱

(5.3)更改放置motion圖檔資料夾的權限，

    Sudo chmod -R 777存放圖檔資料夾名稱

   			 -說明 : 
              Chmod 指令是用於改變檔案權限，權限設定可分為兩種 : 數字 
              或符號，這邊以數字做為權限的變更 : 777分別為owner/group/
              others三種身份，每個身分擁有read/write/execute權限，每個  
              權限的分數對照表如下：r:4w:2 x:1，身分(owner/group/others)
              擁有三種權限(r/w/x)分數是皆以累加的方式，因此
              7=r(4)+w(2)+x(1)的意思是指這身分具有r/w/x權限。

http://linux.vbird.org/linux_basic/0210filepermission.php 

(5.2) 在motion .conf 設定檔修改預設路徑

 sudo nano /etc/motion/motion.conf

 (5.2.1) 找到 target_dir : 設定儲存圖檔新路徑 

 


1.3測試結果

   (1)重新開機後，再一次連線網站，出現灰色畫面

(1.1)	解決辦法 : 在/etc/init.d/motion 加上 sudo modprobe bcm2835-v4l2

1.4參考資料

(1)	motion設定教學

-Motion Guide
http://htmlpreview.github.io/?https://github.com/Motion-Project/motion/blob/master/motion_guide.html#Install_Apt
-Motion Guide in git hub
https://github.com/Motion-Project/motion 
-Build a Raspberry Pi Webcam Server in Minutes
https://pimylifeup.com/raspberry-pi-webcam-server/ 
-How to use a Raspberry Pi to remotely watch your home
http://www.techradar.com/how-to/computing/use-a-raspberry-pi-to-remotely-watch-your-home-1314466 
   -Raspberry Pi 安裝 Webcam 和 Motion Webcam Server
http://tekibrain.blogspot.tw/2013/05/raspberry-pi-webcam-motion-webcam-server.html 


(2)	motion 更改權限
https://raspberrypi.stackexchange.com/questions/12378/what-permissions-does-motion-require-to-write-to-specific-directory 
                   
https://raspberrypi.stackexchange.com/questions/27737/unable-to-open-video-device-and-grey-screen 

