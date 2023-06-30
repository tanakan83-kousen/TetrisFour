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

	//���s
	bool Run(double x, double y,int &turn);
	//�G���[��ʕ\��
	void eDisplay();
	tetofour &t;
	Board &b;

private:
	//�N���b�N�������W�̒���
	void clickPos(double x, double y);

	////�G���[�̃E�B���h�E�ɂ���////
	SDL_Window* eWindow;
	SDL_Surface* eSurface;
	SDL_Texture* eMessage;
	SDL_Renderer* eRenderer;

	//�N���b�N�������W
	Pos position{0,0};
};