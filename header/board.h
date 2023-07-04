#pragma once
#include "header\\tetofour.h"
using namespace std;

class Board 
{
public:
	Board(tetofour &t);
	//最下行が埋まっているか
	bool checkFull();
	//boardの初期化
	void bInitialize();
	//そこに置けるか
	bool checkPut(int i, int j);
	//4つ揃っているか
	bool check4Connect(int i, int j, string s);

	//ボード
	vector<vector<string>> sboard;
	vector<vector<SDL_Texture*>> board;
	vector<vector<SDL_Rect>> boardPos;

	//リザルトボード
	vector<SDL_Texture*> rboard;
	vector<string> rsboard;
	vector<SDL_Rect> rboardPos;

	tetofour &t;

private:
	//横方向判定
	void Holizon(int i,int j,int left,int right);
	//縦方向判定
	void Vertical(int i,int j, int up,int down);
	//左斜め判定(右上→左下)
	void LDiagonal(int i,int j,int Ldown,int Rup);
	//右斜め判定(左上→右下)
	void RDiagonal(int i,int j,int Rdown, int Lup);
	//一段下げる
	void Under();
};