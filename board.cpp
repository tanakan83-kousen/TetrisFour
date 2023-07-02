#include "header\\board.h"

using namespace std;

Board::Board(tetofour &t)
	:sboard(6, vector<string>(7))
	, board(6, vector<SDL_Texture*>(7))
	, boardPos(6, vector<SDL_Rect>(7))
	, rboard(5)
	,rsboard(5)
	,rboardPos(4)
	,t(t)
{

}

void Board::bInitialize() {
	
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 7; j++) {
			sboard[i][j] = "null";
			boardPos[i][j].x = 80 + t.mass * j;
			boardPos[i][j].y = 70 + t.mass * i;
			boardPos[i][j].w = 80;
			boardPos[i][j].h = 80;
		}
	}
	for (int i = 0; i < 4; i++) {
		rsboard[i] = "null";
		rboardPos[i].w = 40;
		rboardPos[i].h = 40;
	}
}

bool Board::checkFull() {
	for (int j = 0; j < 7; j++) {
		if (sboard[5][j] == "null") {
			return false;
		}
	}
	Board::Under();
	return true;
}

bool Board::checkPut(int i, int j) {
	//‚·‚Å‚É‚»‚±‚É‹î‚ª‚ ‚é‚©
	if (sboard[i][j] != "null") {
		return false;
	}

	//‰º‚É‹î‚ª‚ ‚é‚©
	int yi = i;
	while (yi < 5) {
		if (sboard[yi + 1][j] == "null") {
			return false;
		}
		yi++;
	}
	return true;
}

bool Board::check4Connect(int i, int j, string s) {
	int xj = j, yi = i;
	int holizon = 1, vertical = 1, Rdiagonal = 1, Ldiagonal = 1;
	int right = 0, left = 0, up = 0, down = 0, Ldown = 0, Lup = 0, Rdown = 0, Rup = 0;

	//¶
	while (xj > 0 && sboard[i][xj - 1] == s) {
		left++;
		xj--;
	}
	holizon += left;

	//‰E
	xj = j, yi = i;
	while (xj < 6 && sboard[i][xj + 1] == s) {
		right++;
		xj++;
	}
	holizon += right;

	if (holizon == 4) {
		Holizon(i, j, left, right);
		return true;
	}

	//ã
	xj = j, yi = i;
	while (yi > 0 && sboard[yi - 1][xj] == s) {
		up++;
		yi--;
	}
	vertical += up;

	//‰º
	xj = j, yi = i;
	while (yi < 5 && sboard[yi + 1][xj] == s) {
		down++;
		yi++;
	}
	vertical += down;

	if (vertical == 4) {
		Vertical(i, j, up, down);
		return true;
	}

	// ¶ŽÎ‚ß‰º
	xj = j, yi = i;
	while (xj > 0 && yi < 5 && sboard[yi + 1][xj - 1] == s) {
		Ldown++;
		xj--;
		yi++;
	}
	Ldiagonal += Ldown;

	//  ‰EŽÎ‚ßã
	xj = j, yi = i;
	while (xj < 6 && yi > 0 && sboard[yi - 1][xj + 1] == s) {
		Rup++;
		xj++;
		yi--;
	}
	Ldiagonal += Rup;

	if (Ldiagonal == 4) {
		LDiagonal(i, j, Ldown, Rup);
		return true;
	}

	//  ‰EŽÎ‚ß‰º
	xj = j, yi = i;
	while (xj < 6 && yi < 5 && sboard[yi + 1][xj + 1] == s) {
		Rdown++;
		xj++;
		yi++;
	}
	Rdiagonal += Rdown;

	// ¶ŽÎ‚ßã	
	xj = j, yi = i;
	while (xj > 0 && yi > 0 && sboard[yi - 1][xj - 1] == s) {
		Lup++;
		xj--;
		yi--;
	}
	Rdiagonal += Lup;

	if (Rdiagonal == 4) {
		RDiagonal(i, j, Rdown, Lup);
		return true;
	}

	return false;
}

void Board::Holizon(int i, int j,int left,int right) {
	int p = 0;
	rboardPos[p].x = 100 + t.mass * j, rboardPos[p].y = 90 + t.mass * i;
	rsboard[p] = "white";
	p++;
	int xj = j, yi = i;
	while (left > 0) {
		rboardPos[p].x = 100 + t.mass * (xj - 1), rboardPos[p].y = 90 + t.mass * i;
		rsboard[p] = "white";
		xj--;
		left--;
		p++;
	}
	xj = j, yi = i;
	while (right > 0) {
		rboardPos[p].x = 100 + t.mass * (xj + 1), rboardPos[p].y = 90 + t.mass * i;
		rsboard[p] = "white";
		xj++;
		right--;
		p++;
	}
}

void Board::Vertical(int i,int j,int up, int down) {
	int p = 0;
	rboardPos[p].x = 100 + t.mass * j, rboardPos[p].y = 90 + t.mass * i;
	rsboard[p] = "white";
	p++;
	int xj = j, yi = i;
	while (up > 0) {
		rboardPos[p].x = 100 + t.mass * xj, rboardPos[p].y = 90 + t.mass * (yi - 1);
		rsboard[p] = "white";
		yi--;
		up--;
		p++;
	}
	xj = j, yi = i;
	while (down > 0) {
		rboardPos[p].x = 100 + t.mass * xj, rboardPos[p].y = 90 + t.mass * (yi + 1);
		rsboard[p] = "white";
		yi++;
		down--;
		p++;
	}
}

void Board::RDiagonal(int i,int j, int Rdown, int Lup) {
	int p = 0;
	rboardPos[p].x = 100 + t.mass * j, rboardPos[p].y = 90 + t.mass * i;
	rsboard[p] = "white";
	p++;
	int xj = j, yi = i;
	while (Rdown > 0) {
		rboardPos[p].x = 100 + t.mass * (xj + 1), rboardPos[p].y = 90 + t.mass * (yi + 1);
		rsboard[p] = "white";
		xj++;
		yi++;
		Rdown--;
		p++;
	}
	xj = j, yi = i;
	while (Lup > 0) {
		rboardPos[p].x = 100 + t.mass * (xj - 1), rboardPos[p].y = 90 + t.mass * (yi - 1);
		rsboard[p] = "white";
		xj--;
		yi--;
		Lup--;
		p++;
	}
}

void Board::LDiagonal(int i,int j, int Ldown, int Rup) {
	int p = 0;
	rboardPos[p].x = 100 + t.mass * j, rboardPos[p].y = 90 + t.mass * i;
	rsboard[p] = "white";
	p++;
	int xj = j, yi = i;
	while (Ldown > 0) {
		rboardPos[p].x = 100 + t.mass * (xj - 1), rboardPos[p].y = 90 + t.mass * (yi + 1);
		rsboard[p] = "white";
		xj--;
		yi++;
		Ldown--;
		p++;
	}
	xj = j, yi = i;
	while (Rup > 0) {
		rboardPos[p].x = 100 + t.mass * (xj + 1), rboardPos[p].y = 90 + t.mass * (yi - 1);
		rsboard[p] = "white";
		xj++;
		yi--;
		Rup--;
		p++;
	}
}

void Board::Under() {
	for (int i = 5; i >= 1; i--) {
		for (int j = 6; j >= 0; j--) {
			if (sboard[i - 1][j] == "red") {
				sboard[i][j] = "red";
			}
			else if (sboard[i - 1][j] == "blue") {
				sboard[i][j] = "blue";
			}
			else {
				sboard[i][j] = "null";
			}
		}
	}
	for (int j = 0; j < 7; j++) {
		sboard[0][j] = "null";
	}
}