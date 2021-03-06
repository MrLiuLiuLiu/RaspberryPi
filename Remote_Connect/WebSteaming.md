
# 即時影像監控-使用Pi Camera & Motion

## 簡介

為能在網路上達成即時影像監控的功能，這邊以串流技術實現。串流是一種能將影音檔案在網路傳輸的過程，提供即時播放的技術，原理是把一連串的影音資料壓縮後，以網際網路分段傳送的方式，將檔案傳輸至用戶端，讓用戶不需要等待檔案下載完成，即可觀賞影像。

## 實作教學

這邊主要使用motion來實現即時影像監控的功能，操作步驟分成四個階段，流程圖參照如下:

![image](https://github.com/MrLiuLiuLiu/RaspberryPi/blob/master/motion%E6%93%8D%E4%BD%9C%E6%B5%81%E7%A8%8B%E5%9C%96.png)

### 安裝motion服務:

更新系統至最新版本
```
sudo apt-get update
```

安裝motion軟體
```
sudo apt-get install motion
```

### 設定motion服務

#### 修改motion .conf 設定檔參數
-----------------------------------------------------------------------------------------------------------
```
sudo nano /etc/motion/motion.conf
```
.conf設定檔內部參數 : 
```
#修改關鍵設定值

daemon : 設定為 on
webcam_localhost : 設定為 off

#修改設定值(選擇性)

framerate(及時更新畫面的速率): 設定為100
stream_maxrate(每秒捕捉畫面的速率) : 設定為100
output_pictures off
ffmpeg_output_movies off

#管理motion連線使用 port 8080

control_port 8080

#連線webcam使用port 8081

web_port 8081
```

#### 設定motion為常駐服務 
-----------------------------------------------------------------------------------------------------------

```
sudo nano /etc/default/motion
```
motion檔內部參數 : 
```
start_motion_daemon = yes
```

#### 更改motion影像檔
-----------------------------------------------------------------------------------------------------------

建立放置圖檔的新資料夾
```
mkdir 存放圖檔資料夾名稱
```
更改motion所屬群組
```
sudo  chgrp motion /home/pi/存放圖檔資料夾名稱
```
更改放置motion圖檔資料夾的權限
```
sudo chmod -R 777存放圖檔資料夾名稱
```
chmod 指令是用於改變檔案權限，權限設定可分為兩種 : 數字或符號，這邊以數字做為權限的變更 : 

777分別為owner/group/others三種身份每個身分擁有read/write/execute權限，每個權限的分數

對照表如下：r:4 w:2 x:1，身分(owner/group/others)擁有三種權限(r/w/x)分數是皆以累加的方式，

因此7=r(4)+w(2)+x(1)的意思是指這身分具有r/w/x權限，詳細內容請參考[Linux 的檔案權限與目錄配置](http://linux.vbird.org/linux_basic/0210filepermission.php )

#### 在motion .conf 設定檔修改預設路徑
-----------------------------------------------------------------------------------------------------------
找到 target_dir : 設定儲存圖檔新路徑，一開始預設路徑為 /var/lib/motion，目前變更為/home/pi/motion
```
sudo nano /etc/motion/motion.conf
```

### 啟動/關閉motion服務

啟動motion網路串流服務
```
sudo service motion start
```
關閉motion網路串流服務
```  
sudo service motion start
```
### 連線motion服務

查詢raspberry pi IP，圖中紅色框框內的數字表示樹梅派的ip 
```
sudo ifconfig
```

![image](https://github.com/MrLiuLiuLiu/RaspberryPi/blob/master/Raspberry%20ip%20%E6%9F%A5%E8%A9%A2.png)

至網站打上raspberry pi IP : 8081 


## 測試結果

### 問題一: 重新開機後，再一次連線網站，出現灰色畫面

解決辦法 : 在/etc/modules 加上bcm2835-v4l2，參照[Lane Tech HS - PCL - Raspberry Pi Motion Activated Camera](https://www.hackster.io/daniel-jablonski/lane-tech-hs-pcl-raspberry-pi-motion-activated-camera-6de824)

## 參考資料

### motion設定教學

#### 中文說明

[Raspberry Pi 安裝 Webcam 和 Motion Webcam Server](http://tekibrain.blogspot.tw/2013/05/raspberry-pi-webcam-motion-webcam-server.html)

[Raspberry-pi-time-lapse-using-motion-and-webcam](https://blog.gtwang.org/iot/raspberry-pi/raspberry-pi-time-lapse-using-motion-and-webcam/)

#### 英文說明

[Build a Raspberry Pi Webcam Server in Minutes](https://pimylifeup.com/raspberry-pi-webcam-server/)

[How to use a Raspberry Pi to remotely watch your home](http://www.techradar.com/how-to/computing/use-a-raspberry-pi-to-remotely-watch-your-home-1314466)

[Lane Tech HS - PCL - Raspberry Pi Motion Activated Camera](https://www.hackster.io/daniel-jablonski/lane-tech-hs-pcl-raspberry-pi-motion-activated-camera-6de824)

### motion 更改權限
https://raspberrypi.stackexchange.com/questions/12378/what-permissions-does-motion-require-to-write-to-specific-directory 
             

