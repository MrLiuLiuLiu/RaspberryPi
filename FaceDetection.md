# 使用Pi camera 與 OpenCV 進行人臉偵測

## 簡介

本專案是以opencv 與樹梅派去實現人臉偵測的功能，圖示為人臉偵測的運作架構，分成三個區塊:

1. 從樹梅派相機接收影像

2. 使用opencv 中具備人臉偵測功能的程式庫，對相機接收的影像進行人臉偵測 

3. 把偵測人臉的結果顯示在螢幕上

![image](https://github.com/MrLiuLiuLiu/RaspberryPi/blob/master/RaspberryPi%E4%BA%BA%E8%87%89%E5%81%B5%E6%B8%AC%E9%81%8B%E4%BD%9C%E6%9E%B6%E6%A7%8B.png)

 
## 工作原理

臉部偵測(Face Detection)基本作法是先做特徵擷取(Feature Extraction)，接著偵測檢查特徵(Cascade Detection)，進行特徵部位的辨識，如眼睛、耳朵、鼻子、臉型。

本專案使用的OpenCV人臉偵測演算法，是採用Paul Viola與Michael Jones發表的Robust Real-Time Face Detection實現，圖示為人臉偵測演算法的架構，由三個部分組成:

詳細說明為[Implementing face detection using the Haar Cascades and AdaBoost algorithm](https://hub.packtpub.com/implementing-face-detection-using-haar-cascades-adaboost-algorithm/)

圖片來源為:[Vision based interface system for hands free control of an intelligent wheelchair](https://link.springer.com/article/10.1186/1743-0003-6-33#Fig4)
![image](https://media.springernature.com/original/springer-static/image/art%3A10.1186%2F1743-0003-6-33/MediaObjects/12984_2008_Article_193_Fig4_HTML.jpg) 

### 使用Haar-like特徵檢測人臉特徵，並加入積分圖提高對Haar-like特徵求值的速度

詳細說明參照[Haar+Adaboost级联分类器分解](https://blog.csdn.net/lijihw_1022/article/details/51374073) : 

- Haar-like特徵 : 所有的人臉都有一些相似的特徵，透過Haar-like定義的四種檢測視窗，對待識別的圖片進行掃描，並根據檢測框架中的黑色區域與白色區域之比
  例，計算出該掃描區域的特徵值。
  
  
- 積分圖 : 由於每一塊檢測視窗中掃描後的Haar-like特徵值，擁有數以萬計的排列組合，如以Viola提出的最基本四個特徵為例，在一個24×24大小的視窗中的任意排
  列至少可以產生10萬種的特徵，因此，面對這麼龐大的計算量，積分圖可以求出圖像中所有區域像素和的算法，進而提高了圖像特徵值計算的效率。
  
### 使用AdaBoost算法區分人臉和非人臉

已檢測的人臉特徵值作為一個樣本，每一份樣本視為一個弱分類，AdaBoost便是把弱分類集合，轉換成強分類，幫助我們建立對人臉偵測更加嚴謹的辨識基準。
針對AdaBoost演算法大致分為三個重點，詳細說明參照[AdaBoost算法原理及OpenCV实例](https://blog.csdn.net/dcrmg/article/details/53038993)

- 針對訓練數據的分布進行初始化 : 假設有N個樣本，則每一個訓練樣本最開始訓練都被赋予相同的權值：1/N。

- 訓練弱分類器 : 如果某個樣本已準確地被分類，那麼下一次的疊加訓練，權值就被降低；相反地，如果某個樣本没有被準確地被分類，其權值就得提高，然後權值更新 
  過的樣本就會被用於訓練下一個分類器，整個訓練過程迭代進行下去。
  
- 將訓練得到的弱分類器组合成強分類器 : 各個弱分類器的訓練過程結束後，會提高分類誤差率小的弱分類器權重，降低分類誤差率大的弱分類器權重。 

### 使用Cascade Classifier把強分類器級聯一起，提高人臉辨識的準確率

一開始將特徵(feature)分成好幾個classifier。最前面的classier辨識率最低，但是可以先篩選掉不是人臉的圖片；接下來的Classier處理比較難篩選掉的圖片依此類推，直到最後一個classier為止，留下來的就會是確定有人臉的照片。

## 實作說明

### 人臉偵測


#### 注意事項 

先確認OpenCV 放置Cascade Classifier的路徑，若無更改路徑會發生編譯錯誤的訊息，使用OpenCV預設路徑為:
 ```
    /home/pi/opencv-3.0.0/data/haarcascades/haarcascade_frontalface_alt.xml
```

#### 參考教學

- 靜態辨識 : 透過Picamera鏡頭拍攝圖像後，人臉辨識結果以圖片方式呈現，程式碼參照[OpenCV with Raspberry Pi Camera Face Detection Tutorial](https://pythonprogramming.net/raspberry-pi-camera-opencv-face-detection-tutorial/) 

- 動態辨識 : 透過Picamera鏡頭以錄影方式，進行人臉辨識，程式碼參照[Raspberry-Pi-Camera-Face-Detection-Python](https://github.com/AsankaD7/Raspberry-Pi-Camera-Face-Detection-Python/blob/master/faceDetectPiVideo.py) 

### Haar-like特徵分類器訓練


#### 流程介紹

分類器訓練分的實作流程如下，大致分為三個重點 : 

- 資料準備 : 需要正面圖像樣本與負面圖像樣本
- 創建樣本 : 目的是為產生正圖像特徵向量的文件.vec檔
- 訓練樣本 : 以opencv_traincascade 指令進行樣本的訓練

![image](https://github.com/MrLiuLiuLiu/RaspberryPi/blob/master/Haa-like%E7%89%B9%E5%BE%B5%E5%88%86%E9%A1%9E%E5%99%A8%E8%A8%93%E7%B7%B4%E6%B5%81%E7%A8%8B.png)

#### 參考教學

##### 英文

- [Creating your own Haar Cascade OpenCV Python Tutorial](https://pythonprogramming.net/haar-cascade-object-detection-python-opencv-tutorial/) : 

 本專案參考此程式作為練習Haa-like特徵分類器的操作，並使用單一正面圖像樣本進行訓練，這個程式可分為兩個區塊討論 : 
 
  - 資料準備 : 使用Python 透過urlib 套件下載正面圖像樣本或負面圖像樣本(如程式一)，並替除掉無法正常顯示的圖檔(程式二)
  
  程式一 : 
   ```
import urllib.request
import cv2
import numpy as np
import os

def store_raw_images():
    neg_images_link = '//image-net.org/api/text/imagenet.synset.geturls?wnid=n00523513'   
    neg_image_urls = urllib.request.urlopen(neg_images_link).read().decode()
    pic_num = 1
    
    if not os.path.exists('neg'):
        os.makedirs('neg')
        
    for i in neg_image_urls.split('\n'):
        try:
            print(i)
            urllib.request.urlretrieve(i, "neg/"+str(pic_num)+".jpg")
            img = cv2.imread("neg/"+str(pic_num)+".jpg",cv2.IMREAD_GRAYSCALE)
            # should be larger than samples / pos pic (so we can place our image on it)
            resized_image = cv2.resize(img, (100, 100))
            cv2.imwrite("neg/"+str(pic_num)+".jpg",resized_image)
            pic_num += 1
            
        except Exception as e:
            print(str(e))  
  ```           
 程式二 : 
   ```
    def find_uglies():
    match = False
    for file_type in ['neg']:
        for img in os.listdir(file_type):
            for ugly in os.listdir('uglies'):
                try:
                    current_image_path = str(file_type)+'/'+str(img)
                    ugly = cv2.imread('uglies/'+str(ugly))
                    question = cv2.imread(current_image_path)
                    if ugly.shape == question.shape and not(np.bitwise_xor(ugly,question).any()):
                        print('That is one ugly pic! Deleting!')
                        print(current_image_path)
                        os.remove(current_image_path)
                except Exception as e:
                    print(str(e))
   ```
  - 樣本訓練 :  使用OpenCV Cascade Classifier Training的方式，產生Haar-like特徵分類器需要的樣本進行訓練，參照[Training Haar Cascades]
(https://memememememememe.me/post/training-haar-cascades/)

- [OpenCV haartraining (Rapid Object Detection With A Cascade of Boosted Classifiers Based on Haar-like Features](http://note.sonots.com/SciSoftware/haartraining.html#v6f077ba) :

 介紹Haa-like特徵分類器訓練樣本的流程

##### 中文

- [自己训练haar特征的adaboost分类器进行人脸识别](https://blog.csdn.net/SGamble/article/details/52890637):

 介紹使用多份正面圖像進行分類器訓練樣本的流程

                                                                                                                                                                                                           





 

