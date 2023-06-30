#include "header\\player.h"

Player::Player(tetofour &t,Board &b)
	:eWindow(nullptr)
	, eRenderer(nullptr)
	, eSurface(nullptr)
	, eMessage(nullptr)
	,t(t)
	,b(b)
{

}

void Player::clickPos(double x, double y) {
	for (int i = 0; i < 6; i++) {
		//クリックした場所がマス目内か
		if (60 + t.mass * i < y && y < 60 + t.mass * (i + 1)) {
			for (int j = 0; j < 7; j++) {
				if (70 + t.mass * j < x && x < 70 + t.mass * (j + 1)) {
					x = 80 + t.mass * j;
					y = 70 + t.mass * i;

					position.i = i;
					position.j = j;
				}
				else if (70 > x || x > t.width - t.Wrange) {
					x = -1000;
					break;
				}
			}
		}
		else if (60 > y || y > t.height - t.Hrange) {
			y = -1000;
			break;
		}
	}
}

bool Player::Run(double x, double y,int &turn) {
	//クリックした座標を取得
	clickPos(x,y);
	
	//そこに置けるか
	if (b.checkPut(position.i, position.j)) {
		//先行(赤)
		if (turn == 1) {
			b.sboard[position.i][position.j] = "red";
			//四つつながっていたら終了
			if (b.check4Connect(position.i, position.j, "red")) {
				t.Result(turn);
				turn *= -1;
				return false;
			}
		}
		//後攻(青)
		else if (turn == -1) {
			b.sboard[position.i][position.j] = "blue";
			//四つつながっていたら終了
			if (b.check4Connect(position.i, position.j, "blue")) {
				t.Result(turn);
				turn *= -1;
				return false;
			}
		}
		//最下行が埋まっていたら一段下げる
		if(b.checkFull());
		turn *= -1;
	}
	else {
		eDisplay();
	}
	return true;
}

void Player::eDisplay() {
	int tthe = TTF_Init();
	if (tthe != 0) {
		SDL_Log("Failed to TTF Init %s", SDL_GetError());
		return;
	}
	//エラーウィンドウ作成
	eWindow = SDL_CreateWindow(
		"e",//タイトル
		t.width / 3,//左上のx
		t.height / 3,//左上のy
		t.width / 2,//幅
		t.height / 4,//高さ
		0//フラグ
	);
	if (!eWindow) {
		SDL_Log("Failed to create eWindow : %s", SDL_GetError());
		return;
	}
	//エラーレンダラー作成
	eRenderer = SDL_CreateRenderer(
		eWindow,
		-1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC //フラグ
	);
	if (!eRenderer) {
		SDL_Log("Failed to create eRenderer: %s", SDL_GetError());
		return;
	}

	//フォント設定
	t.font = TTF_OpenFont(FONT_PATH, 60);
	if (!t.font) {
		SDL_Log("Failed to Open TTF: %s", SDL_GetError());
		return;
	}

	//表示文字設定
	eSurface = TTF_RenderUTF8_Blended(t.font, "Can't Put!!", { 255, 255, 255, 255 });
	eMessage = SDL_CreateTextureFromSurface(eRenderer, eSurface);
	SDL_SetRenderDrawColor(eRenderer, 0, 0, 0, 255);
	SDL_RenderClear(eRenderer);

	int iw, ih;
	SDL_QueryTexture(eMessage, NULL, NULL, &iw, &ih);
	SDL_Rect txtRect = { 0,0,iw,ih };
	SDL_Rect pasteRect = { 100,90,iw,ih };

	//描画
	SDL_RenderCopy(eRenderer, eMessage, &txtRect, &pasteRect);
	SDL_RenderPresent(eRenderer);

	//1.5秒間表示させる
	SDL_Delay(1500);
	SDL_DestroyRenderer(eRenderer);
	SDL_DestroyWindow(eWindow);
	return;

}