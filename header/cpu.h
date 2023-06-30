#pragma once
#include "tetofour.h"
#include "board.h"

typedef struct {
	int i;
	int j;
}CIE;

class Cpu {
public:
	Cpu(tetofour &t,Board &b);
	bool Run(int &turn,int level);
	tetofour &t;
	Board &b;
	vector<vector<int>> score;
private:
	int Random(Board &copyboard);
	vector<CIE> put;
	void Montecarlo(int depth);
	int max_score;
	int maxj;
	int maxi;
	void Play(int &depth);
	int depth;
	int max_depth;
};