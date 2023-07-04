#pragma once
#include "header\\tetofour.h"
using namespace std;

class Board 
{
public:
	Board(tetofour &t);
	//�ŉ��s�����܂��Ă��邩
	bool checkFull();
	//board�̏�����
	void bInitialize();
	//�����ɒu���邩
	bool checkPut(int i, int j);
	//4�����Ă��邩
	bool check4Connect(int i, int j, string s);

	//�{�[�h
	vector<vector<string>> sboard;
	vector<vector<SDL_Texture*>> board;
	vector<vector<SDL_Rect>> boardPos;

	//���U���g�{�[�h
	vector<SDL_Texture*> rboard;
	vector<string> rsboard;
	vector<SDL_Rect> rboardPos;

	tetofour &t;

private:
	//����������
	void Holizon(int i,int j,int left,int right);
	//�c��������
	void Vertical(int i,int j, int up,int down);
	//���΂ߔ���(�E�と����)
	void LDiagonal(int i,int j,int Ldown,int Rup);
	//�E�΂ߔ���(���と�E��)
	void RDiagonal(int i,int j,int Rdown, int Lup);
	//��i������
	void Under();
};