#pragma once
#include "tetofour.h"
#include "board.h"

//座標
typedef struct {
	int i;
	int j;
}CIE;

class Cpu {
public:
	Cpu(tetofour &t,Board &b);
	//実行
	bool Run(int &turn,int level);
	tetofour &t;
	Board &b;
	
	vector<vector<int>> score;
private:
	//ランダムに打つ場所を決める
	int Random(Board &copyboard);
	//打つ座標
	vector<CIE> put;
	//モンテカルロ法を実行
	void Montecarlo(int depth);

	int max_score;
	int maxj;
	int maxi;
	void Play(int &depth);
	int depth;
	//最大実行回数
	int max_depth;
};