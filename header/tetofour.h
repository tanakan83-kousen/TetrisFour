#pragma once
#include "SDL.h"
#include "SDL_ttf.h"
using namespace std;
#include "header\\stdc++.h"

class tetofour
{
public:
	tetofour();
	//最初の設定を選択
	void Start(int No);
	//初期化関数
	bool Initialize();
	//実行中
	void RunLoop();
	//結果
	void Result(int turn);
	//終了か継続か選択
	int Finish();
	//シャットダウン
	void Shutdown();

	//フォント指定
	TTF_Font* font;
	#define FONT_PATH "PixelMplus-20130602\\PixelMplus10-Regular.ttf"

	int turn = 1; //1:赤  -1:青

	int myturn = 0; //先行or後攻
	
	int mode = 0;//1:対人 2:対cpu

	int level = 0; //cpuのレベル
	#define EASY 50
	#define NORMAL 800
	#define HARD 3000
	//ウィンドウの縦幅
	const int height = 720;
	//ウィンドウの横幅
	const int width = 840;

	//枠外の幅
	const int Hrange = 60;
	const int Wrange = 70;

	//クリックした座標
	SDL_Point mouse_position;

	//1マスの大きさ
	const int mass = (width - Wrange * 2) / 7;

private:
	////メインウィンドウについて////
	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;

	////リザルトウィンドウについて////
	SDL_Window* rWindow;
	SDL_Renderer* rRenderer;
	SDL_Surface* rSurface;
	SDL_Texture* rMessage;

	/////スタートウィンドウについて/////
	SDL_Window* sWindow;
	SDL_Renderer* sRenderer;
	SDL_Surface* sSurface;
	SDL_Texture* sMessage;

	/////フィニッシュウィンドウについて////
	SDL_Window* fWindow;
	SDL_Renderer* fRenderer;
	SDL_Surface* fSurface;
	SDL_Texture* fMessage;
	
	////駒について//////
	SDL_Surface* blue;
	SDL_Surface* red;
	SDL_Texture* BlueTex;
	SDL_Texture* RedTex;
	SDL_Surface* white;
	SDL_Texture* whiteTex;
	
	//表示関数
	void Display();
	//入力処理
	void ProcessInput();
	
	//続けるかどうか
	bool mIsRunning;
};