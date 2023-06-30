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
		//�N���b�N�����ꏊ���}�X�ړ���
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
	//�N���b�N�������W���擾
	clickPos(x,y);
	
	//�����ɒu���邩
	if (b.checkPut(position.i, position.j)) {
		//��s(��)
		if (turn == 1) {
			b.sboard[position.i][position.j] = "red";
			//�l�Ȃ����Ă�����I��
			if (b.check4Connect(position.i, position.j, "red")) {
				t.Result(turn);
				turn *= -1;
				return false;
			}
		}
		//��U(��)
		else if (turn == -1) {
			b.sboard[position.i][position.j] = "blue";
			//�l�Ȃ����Ă�����I��
			if (b.check4Connect(position.i, position.j, "blue")) {
				t.Result(turn);
				turn *= -1;
				return false;
			}
		}
		//�ŉ��s�����܂��Ă������i������
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
	//�G���[�E�B���h�E�쐬
	eWindow = SDL_CreateWindow(
		"e",//�^�C�g��
		t.width / 3,//�����x
		t.height / 3,//�����y
		t.width / 2,//��
		t.height / 4,//����
		0//�t���O
	);
	if (!eWindow) {
		SDL_Log("Failed to create eWindow : %s", SDL_GetError());
		return;
	}
	//�G���[�����_���[�쐬
	eRenderer = SDL_CreateRenderer(
		eWindow,
		-1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC //�t���O
	);
	if (!eRenderer) {
		SDL_Log("Failed to create eRenderer: %s", SDL_GetError());
		return;
	}

	//�t�H���g�ݒ�
	t.font = TTF_OpenFont(FONT_PATH, 60);
	if (!t.font) {
		SDL_Log("Failed to Open TTF: %s", SDL_GetError());
		return;
	}

	//�\�������ݒ�
	eSurface = TTF_RenderUTF8_Blended(t.font, "Can't Put!!", { 255, 255, 255, 255 });
	eMessage = SDL_CreateTextureFromSurface(eRenderer, eSurface);
	SDL_SetRenderDrawColor(eRenderer, 0, 0, 0, 255);
	SDL_RenderClear(eRenderer);

	int iw, ih;
	SDL_QueryTexture(eMessage, NULL, NULL, &iw, &ih);
	SDL_Rect txtRect = { 0,0,iw,ih };
	SDL_Rect pasteRect = { 100,90,iw,ih };

	//�`��
	SDL_RenderCopy(eRenderer, eMessage, &txtRect, &pasteRect);
	SDL_RenderPresent(eRenderer);

	//1.5�b�ԕ\��������
	SDL_Delay(1500);
	SDL_DestroyRenderer(eRenderer);
	SDL_DestroyWindow(eWindow);
	return;

}