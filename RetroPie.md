
# 以樹莓派打造一台專屬的遊戲主機-使用Retropie

## Retropie 介紹

Retropie 是一套整合各家遊戲主機模擬器的開源系統，而且是以Linux核心建構的平台，因此，在使用的模擬器類型相容性高，支援的遊戲也多，操作方式則可以由命令列設定，使用彈性相對的大，適合中階進階者使用。

## Retropie模擬器安裝方式

RetroPie模擬器安裝方式這邊提供兩種流程:

>  直接將RetroPie模擬器燒錄在SD卡上

>  在已安裝RESPBERRY 系統上安裝RetroPie模擬器

### 直接將RetroPie模擬器燒錄在SD卡上

- Step1 :至[RetroPie官網](https://retropie.org.uk/download/)下載模擬器壓縮檔

- Step2 :檔案解壓縮後，以[Win32DiskImager](https://sourceforge.net/projects/win32diskimager/)將解壓縮的模擬器映像檔寫入SD卡中

### 參考資料

[RetroPie軟硬體準備與初始安裝](https://3q.9527.tw/88)

[RetroPie First Installation](https://retropie.org.uk/docs/First-Installation/) 

### 在已安裝RESPBERRY系統上安裝RetroPie模擬器

- Step1 : 開啟RESPBERRY 系統上的命令提示列

- Step2 : 依序打上下列指令

 RESPBERRY 系統更新
```
sudo apt-get update && sudo apt-get upgrade 
```
 
 安裝RetroPie腳本設定需要的套件
```
sudo apt-get install git lsb-release
```

  下載最新版RetroPie腳本
```
 cd git clone --depth=1 https://github.com/RetroPie/RetroPie-Setup.git
```

  執行腳本
```
cd RetroPie-Setup
chmod +x retropie_setup.sh
sudo ./retropie_setup.sh
```
- Step3 :安裝選擇

  完整安裝
  
  Manage Packages >> Quick Install

  自訂安裝
  
  Core Packages -Main / Optional / Experimental

### 參考資料

[RetroPie Manual-Installation](https://retropie.org.uk/docs/Manual-Installation/) 

### 測試結果

會出現下列連結顯示失敗的畫面 : https://www.raspberrypi.org/forums/viewtopic.php?f=66&p=1211557 

## RetroPie遊戲ROM檔之傳輸方式

在進行遊戲ROM檔傳輸前，須先知道遊戲ROM檔放置資料夾的路徑，如下列說明:

遊戲目錄結構 : \\retropie\roms\各遊戲主機平台\遊戲ROM檔

### USB隨身碟傳輸

USB隨身碟傳輸分成兩種式進行 :　

> 一是自動將隨身碟現有的遊戲ROM檔複製到SD卡的ROM資料夾，並從SD卡執行遊戲ROM檔

> 二是直接在隨身碟執行遊戲ROM檔

#### 從隨身碟自動複製遊戲ROM檔至SD卡

Step1 : 檢查隨身碟的儲存格式是否為FAT32

Step2 : 在隨身碟建立一個資料夾，名稱為retropie

Step3 : 將隨身碟插置樹莓派之USB插槽，並等待隨身碟的提示燈不再閃爍，此步驟會將RetroPie模擬器的資料夾自動在隨身碟建立

Step4 : 拔除樹莓派上的隨身碟，並將其插至電腦USB插槽，開啟隨身碟，尋找名稱為ROM的資料夾，再把遊戲ROM檔放進此資料夾

Step5 : 再插回樹莓派之USB插槽，等待隨身碟的提示燈不再閃爍，此步驟會將ROM資料夾的遊戲ROM檔複製到SD卡中

#### 在隨身碟上啟動遊戲ROM檔

Step1 : 進入RetroPie Setup Menu

Step2 : 選擇RetroPie Setup Script 進行更新

Step3 : 選擇 Setup / Tools中usbromservice (USB ROM Service)重新啟動

Step4 : 確認隨身碟儲存格式是否為FAT-32

Step5 : 在隨身碟中建立名稱為retropie-mount的資料夾

Step6 : 再次啟動樹莓派，此步驟會將RetroPie模擬器中資料夾的檔案與隨身碟資料夾的檔案同步

#### 參考資料

[從隨身碟自動複製遊戲ROM檔至SD卡操作說明](https://3q.9527.tw/90)

[在隨身碟上啟動遊戲ROM檔操作說明](https://github.com/retropie/retropie-setup/wiki/Running-ROMs-from-a-USB-drive) 

### Samba 分享

#### 利用網路分享的方式進行遊戲ROM檔的管理

在Windows 系統的電腦資料夾路徑欄位打上\\RETROPIE

即可在網路共用的視窗存取RetroPie模擬器的資料夾，前提是電腦要與樹莓派連上線，才能夠在電腦上將遊戲ROM檔案傳輸至RetroPie模擬器的資料夾中。

#### 參考資料

[Transferring Roms with Samba Share](https://github.com/retropie/retropie-setup/wiki/Transferring-Roms) 

## RetroPie遊戲進度之存檔方式

### 照遊戲主機的存檔方式儲存

#### psx模擬器

Step1 : 將遊戲模擬器BIOS檔 : SCPH1001.BIN 放進BIOS資料夾中
Step2 : 至RetroPie set-up選單，依序選擇configuration/tools >> Resetromsdir
Step3 : 重新啟動樹莓派

#### 在遊戲畫面中啟用快捷鍵儲存

使用預設快捷鍵select+x呼叫Retroarch選單

#### 參考資料

[Solved memory card psx question](https://www.reddit.com/r/RetroPie/comments/6lyfa0/solved_memory_card_psx_question/?st=j7v5utn1&sh=d67956e7)

[Changing the location of savefile directory](https://www.reddit.com/r/RetroPie/comments/3dyki2/changing_the_location_of_savefile_directory_and/) 

## RetroPie遊戲金手指

在遊戲闖關過程中，也許會面臨卡關的情況，因此需要修改遊戲參數的金手指，以達成玩家對破關的需求，而RetroPie模擬器也提供金手指的功能，這邊以三個部分說明 : 一為遊戲金手指的下載，二為遊戲金手指參數檔的建立

### 遊戲金手指的下載

- Step1 : RetroPie 模擬器選單中選擇Retroarch進入 或者在遊戲畫面中使用預設快捷鍵select+x呼叫Retroarch選單

- Step2 : 進入Retroarch選單後，選擇Online Updater >> Update Cheats : 所有遊戲金手指參數檔皆放置 /opt/retropie/configs/all/retroarch/cheats
      
### 遊戲金手指的啟用

- Step1 : 在啟動的遊戲畫面中使用預設快捷鍵select+x呼叫Retroarch選單

- Step2 : 依序選擇Quick Menu >> Cheats >> Load Cheat File

- Step3 : 畫面底下會列出目前啟動的遊戲金手指參數，接著依據需求在每項金手指參數 ，按下左右鍵，決定啟用或不啟用(左為ON，右為OFF)

- Step4 : 選擇Apply Cheat Changes，然後按下按鍵  B 離開金手指設定選單，選擇 resume ，回到遊戲畫面，即可完成金手指的啟用步驟。

### 遊戲金手指參數檔的建立

- Step1 : 至/opt/retropie/configs/all/retroarch/cheats/路徑下選擇要建立遊戲主機金手指 的資料夾

- Step2 : 在建立遊戲主機金手指的資料夾下，建立一個為.cht檔的檔案

- Step3 : 遊戲主機金手指的參數格式請參照網址: https://retropie.org.uk/docs/Cheats/

### 參考資料 

https://www.reddit.com/r/RetroPie/comments/4ceyty/you_cant_get_cheats_to_work_well_heres_how/?st=j7v6dzmd&sh=f09316a4 

