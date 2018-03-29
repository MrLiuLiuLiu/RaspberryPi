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


AdaBoost人脸检测原理
https://blog.csdn.net/atpccb/article/details/51210162 

1.	使用Haar-like特徵檢測人臉特徵，並使用積分圖（Integral Image）加快對Haar-like特徵求值的速度: 
https://blog.csdn.net/lijihw_1022/article/details/51374073 
1.1Haar-like特徵 :所有的人臉都有一些相似的特徵，透過Haar-like定義的四種檢測視窗，對待識別的圖片進行掃描，並根據檢測框架中的黑色區域與白色區域之比例，計算出該掃描區域的特徵值。

 
1.2積分圖:由於每一塊檢測視窗中掃描後的Haar-like特徵值，擁有數以
萬計的排列組合，如以Viola提出的最基本四個特徵為例，在一個24×24大小的視窗中的任意排列至少可以產生10萬種的特徵，因此，面對這麼龐大的計算量，積分圖可以求出圖像中所有區域像素和的算法，進而提高了圖像特徵值計算的效率。
  
2.	用AdaBoost算法區分人臉和非人臉的強分類器 : 已檢測的人臉特徵  
  值作為一個樣本，每一份樣本視為一個弱分類，AdaBoost便是把弱分類集
  合， 轉換成強分類，幫助我們建立對人臉偵測更加嚴謹的辨識基準。

	2.1針對AdaBoost演算法大致可分為三個重點，詳細說明可參照
		https://blog.csdn.net/dcrmg/article/details/53038993
(1)	針對訓練數據的分布進行初始化 : 假設有N個樣本，則每一個訓練樣本 
最開始訓練都被赋予相同的權值：1/N。
(2)	訓練弱分類器 : 如果某個樣本已準確地被分類，那麼下一次的疊加訓練，權值就被降低；相反地，如果某個樣本没有被準確地被分類，其權值就得提高，然後權值更新過的樣本就會被用於訓練下一個分類器，整個訓練過程迭代進行下去。
(3)	將訓練得到的弱分類器组合成強分類器 : 各個弱分類器的訓練過程結束後，會提高分類誤差率小的弱分類器權重，降低分類誤差率大的弱分類器權重。 
        
3.	加入Cascade Classifier把強分類器級聯一起，提高人臉辨識的準確率

一開始將特徵(feature)分成好幾個classifier。最前面的classier辨識率最低，但是可以先篩選掉不是人臉的圖片；接下來的Classier處理比較難篩選掉的圖片依此類推，直到最後一個classier為止，留下來的就會是確定有人臉的照片。

 


