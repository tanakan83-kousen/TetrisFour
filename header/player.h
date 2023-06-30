#pragma once
#include "header\\tetofour.h"
#include "header\\board.h"

typedef struct {
	int i;
	int j;
}Pos;

class Player {
public:
	Player(tetofour &t,Board &b);

	//実行
	bool Run(double x, double y,int &turn);
	//エラー画面表示
	void eDisplay();
	tetofour &t;
	Board &b;

private:
	//クリックした座標の調整
	void clickPos(double x, double y);

	////エラーのウィンドウについて////
	SDL_Window* eWindow;
	SDL_Surface* eSurface;
	SDL_Texture* eMessage;
	SDL_Renderer* eRenderer;

	//クリックした座標
	Pos position{0,0};
};