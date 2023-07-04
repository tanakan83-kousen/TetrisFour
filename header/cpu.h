#pragma once
#include "tetofour.h"
#include "board.h"

//���W
typedef struct {
	int i;
	int j;
}CIE;

class Cpu {
public:
	Cpu(tetofour &t,Board &b);
	//���s
	bool Run(int &turn,int level);
	tetofour &t;
	Board &b;
	
	vector<vector<int>> score;
private:
	//�����_���ɑłꏊ�����߂�
	int Random(Board &copyboard);
	//�ł��W
	vector<CIE> put;
	//�����e�J�����@�����s
	void Montecarlo(int depth);

	int max_score;
	int maxj;
	int maxi;
	void Play(int &depth);
	int depth;
	//�ő���s��
	int max_depth;
};