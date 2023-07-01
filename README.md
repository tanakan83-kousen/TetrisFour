# TetrisFour
## 環境
Windows 11
Visual Studio 2022
SDL2
SDL2_ttf

## 概要
重力付き四目並べにテトリスの要素を取り入れたものです。c++にSDL2を用いて作成しました。
基本的なルールは重力付き四目並べと同じで、それに「一番下の段が駒で埋まった場合、その段を消し上の段を一段ずつ下げる」というものを取り入れました。また、CPUにはモンテカルロ法を用いています。

## 開始方法
zipファイルを展開し、ReleaceフォルダにあるGame.exeを実行していただければゲームを開始できます。

## ゲームの仕様
### 1.モードの選択
対人の場合はPキーを、対CPUの場合はCキーを入力してください。Pキーを入力した場合は4に飛びます。
![Start 2023_07_01 23_40_26](https://github.com/tanakan83-kousen/TetrisFour/assets/111548773/19d9057f-b9aa-4a7e-af14-4201f81fa431)

### 2.先攻・後攻の選択
先攻(first)なら1キーを、後攻なら2キーを入力してください。なお、テンキーではなくメインのキーで入力してください。
![Start 2023_07_01 23_40_38](https://github.com/tanakan83-kousen/TetrisFour/assets/111548773/22f2e4bc-f99f-47b3-bded-eb128f0a6156)

### 3.CPUレベルの選択
EasyならEキーを、NormalならNキーを、HardならHキーを入力してください。
![Start 2023_07_01 23_40_43](https://github.com/tanakan83-kousen/TetrisFour/assets/111548773/dea9fcc7-9032-4597-a648-8ae6faf01ef6)

### 4.ゲーム開始
マス目内をクリックして駒を置いてください。縦・横・斜めのいずれかで4つ揃ったら勝ちです。なお、「一番下の段が埋まったが同時に4つ揃った場合」は「その段を消し上の段を一段ずつ下げる」が発生せずゲーム終了となります。
![TetoFour 2023_07_01 23_40_49](https://github.com/tanakan83-kousen/TetrisFour/assets/111548773/f9b95aa2-9fd5-4343-b9c6-e8887ef8de62)

### 5.ゲーム終了
もう一度ゲームをする場合は1キーを、終了する場合は2キーを入力してください。先ほどと同様、テンキーではなくメインのキーで入力してください。
![TetoFour 2023_07_01 23_41_06](https://github.com/tanakan83-kousen/TetrisFour/assets/111548773/5f15df10-437b-4687-8372-416fa35438ee)

