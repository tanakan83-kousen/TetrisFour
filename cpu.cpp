#include "header\\cpu.h"
Cpu::Cpu(tetofour &t, Board &b)
	:t(t)
	, b(b)
	, score(6, vector<int>(7))
	, depth(0)
	, maxi(0)
	, maxj(0)
	, max_score(0)
	, put(7)
	,max_depth(0)
{

}

bool Cpu::Run(int &turn,int level) {
	max_depth = level * 7;
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 7; j++) {
			score[i][j] = 0;
		}
	}
	Montecarlo(0);
	int n;
	max_score = 0;
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 7; j++) {
			if (score[i][j] > max_score) {
				maxi = i;
				maxj = j;
				max_score = score[i][j];
			}
		}
	}
	if (max_score == 0) {
		n = Random(b);
		maxi = put[n].i, maxj = put[n].j;
	}

	if (turn == 1) {
		b.sboard[maxi][maxj] = "red";
		if (b.check4Connect(maxi, maxj, "red")) {
			t.Result(turn);
			turn *= -1;
			return false;
		}
	}
	else {
		b.sboard[maxi][maxj] = "blue";
		if (b.check4Connect(maxi, maxj, "blue")) {
			t.Result(turn);
			turn *= -1;
			return false;
		}
	}
	b.checkFull();
	turn *= -1;
	return true;
	
}

void Cpu::Montecarlo(int depth) {
	//難易度によって繰り返す
	if (depth >= max_depth) return;
	Play(depth);
	Montecarlo(depth + 1);
}

void Cpu::Play(int &depth) {
	Board copyboard = b;
	
	int cputurn = t.myturn * -1;
	string users;
	string cpus;
	if (cputurn == 1) {
		cpus = "red";
		users = "blue";
	}
	else {
		cpus = "blue";
		users = "red";
	}

	//最初の一手はランダムに決め打ちする
	int n = Random(copyboard);
	copyboard.sboard[put[n].i][put[n].j] = cpus;

	int firsti = put[n].i, firstj = put[n].j;
	depth += 7;
	while (true) {
		if (copyboard.check4Connect(put[n].i, put[n].j, cpus)) {
			//cpuが勝利したらスコアをプラス
			score[firsti][firstj] += 1;
			break;
		}
		copyboard.checkFull();

		n = Random(copyboard);
		copyboard.sboard[put[n].i][put[n].j] = users;
		if (copyboard.check4Connect(put[n].i, put[n].j, users)) {
			break;
		}
		copyboard.checkFull();

		n = Random(copyboard);
		copyboard.sboard[put[n].i][put[n].j] = cpus;
	}

}

int Cpu::Random(Board &copyboard) {
	int n = 0;
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 7; j++) {
			if (copyboard.checkPut(i, j)) {
				put[n].i = i, put[n].j = j;
				n++;
			}
		}
	}
	random_device rnd;
	n = rnd() % 7;
	return n;
}