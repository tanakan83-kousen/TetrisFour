#include "header\\tetofour.h"
#include "header\\board.h"
#include "header\\player.h"
#include "header\\cpu.h"

using namespace std;
tetofour t;
Board b(t);

tetofour::tetofour()
	:mWindow(nullptr)
	, mRenderer(nullptr)
	, rWindow(nullptr)
	, font(nullptr)
	, rSurface(nullptr)
	, rRenderer(nullptr)
	, rMessage(nullptr)
	, sWindow(nullptr)
	, sSurface(nullptr)
	, sRenderer(nullptr)
	, sMessage(nullptr)
	, fWindow(nullptr)
	, fSurface(nullptr)
	, fRenderer(nullptr)
	, fMessage(nullptr)
	, mIsRunning(true)
	, blue(nullptr)
	, red(nullptr)
	, white(nullptr)
	, whiteTex(nullptr)
	,BlueTex(nullptr)
	,RedTex(nullptr)
	, mouse_position()

{

}

bool tetofour::Initialize()
{
	//sdl�̏�����
	int sdlResult = SDL_Init(SDL_INIT_VIDEO);
	if (sdlResult != 0) {
		SDL_Log("Failed to SDL Init:%s", SDL_GetError());
		return false;
	}
	SDL_Point window_position = {
	SDL_WINDOWPOS_CENTERED,
	SDL_WINDOWPOS_CENTERED
	};

	//���C���E�B���h�E�쐬
	mWindow = SDL_CreateWindow(
		"TetoFour",//�^�C�g��
		100,//�����x
		50,//�����y
		width,//��
		height,//����
		0//�t���O
	);
	if (!mWindow) {
		SDL_Log("Failed to create mwindow : %s", SDL_GetError());
		return false;
	}

	//���C�������_���[�쐬
	mRenderer = SDL_CreateRenderer(
		mWindow,
		-1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC //�t���O
	);
	if (!mRenderer) {
		SDL_Log("Failed to create mrenderer: %s", SDL_GetError());
		return false;
	}
	//��̐ݒ�
	b.bInitialize();
	mIsRunning = true;
	return true;
}

void tetofour::Start(int No) {
	//ttf�̊J�n
	int ttfresult = TTF_Init();
	if (ttfresult != 0) {
		SDL_Log("Failed to TTF Init: %s", SDL_GetError());
	}

	sWindow = SDL_CreateWindow(
		"Start",//�^�C�g��
		width / 5,//�����x
		height / 3,//�����y
		int(width * 1.15),//��
		height / 2,//����
		0//�t���O
	);
	if (!sWindow) {
		SDL_Log("Failed to create sWindow : %s", SDL_GetError());
		return ;
	}

	sRenderer = SDL_CreateRenderer(
		sWindow,
		-1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC //�t���O
	);
	if (!sRenderer) {
		SDL_Log("Failed to create sRenderer: %s", SDL_GetError());
		return ;
	}

	font = TTF_OpenFont(FONT_PATH, 60);
	if (!font) {
		SDL_Log("Failed to Open TTF: %s", SDL_GetError());
		return ;
	}
	if (No == 1) {
		sSurface = TTF_RenderUTF8_Blended(font, "Player : P  Cpu : C", { 255, 255, 255, 255 });
	}
	else if (No == 2) {
		sSurface = TTF_RenderUTF8_Blended(font, "first : 1  second : 2", { 255, 255, 255, 255 });
	}
	else if (No == 3) {
		sSurface = TTF_RenderUTF8_Blended(font, "Easy : E  Normal : N Hard : H", { 255, 255, 255, 255 });
	}

	sMessage = SDL_CreateTextureFromSurface(sRenderer, sSurface);

	SDL_SetRenderDrawColor(sRenderer, 0, 0, 0, 255);
	SDL_RenderClear(sRenderer);

	int iw, ih;
	SDL_QueryTexture(sMessage, NULL, NULL, &iw, &ih);

	SDL_Rect txtRect = { 0,0,iw,ih };
	SDL_Rect pasteRect = { 80,90,iw,ih };

	SDL_RenderCopy(sRenderer, sMessage, &txtRect, &pasteRect);
	SDL_RenderPresent(sRenderer);

	while (true) {
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			switch (event.type) {

			case SDL_KEYDOWN:
				break;

			case SDL_QUIT:
				mIsRunning = false;
				break;
			}
		}
		if (mIsRunning == false) break;
		const Uint8* state = SDL_GetKeyboardState(NULL);
		if (No == 1) {
			if (state[SDL_SCANCODE_P])
			{
				mode = 1;
			}
			else if (state[SDL_SCANCODE_C]) {
				mode = 2;
			}

			if (mode != 0) break;
		}
		else if (No == 2) {
			if (state[SDL_SCANCODE_1])
			{
				myturn = 1;
			}
			else if (state[SDL_SCANCODE_2]) {
				myturn = -1;
			}

			if (myturn != 0) break;
		}
		else if (No == 3) {
			if (state[SDL_SCANCODE_E])
			{
				level = 50;
			}
			else if (state[SDL_SCANCODE_N]) {
				level = 800;
			}
			else if (state[SDL_SCANCODE_H]) {
				level = 3000;
			}

			if (level != 0) break;
		}
	}
	
	SDL_DestroyRenderer(sRenderer);
	SDL_DestroyWindow(sWindow);
	return;

}

int tetofour::Finish() {
	int ttfresult = TTF_Init();
	if (ttfresult != 0) {
		SDL_Log("Failed to TTF Init: %s", SDL_GetError());
	}

	fWindow = SDL_CreateWindow(
		"Finish",//�^�C�g��
		width / 5,//�����x
		height / 5,//�����y
		int(width * 0.95),//��
		height / 4,//����
		0//�t���O
	);
	if (!fWindow) {
		SDL_Log("Failed to create fWindow : %s", SDL_GetError());
		return 0;
	}

	fRenderer = SDL_CreateRenderer(
		fWindow,
		-1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC //�t���O
	);
	if (!fRenderer) {
		SDL_Log("Failed to create rRenderer: %s", SDL_GetError());
		return 0;
	}

	font = TTF_OpenFont(FONT_PATH, 60);
	if (!font) {
		SDL_Log("Failed to Open TTF: %s", SDL_GetError());
		return 0;
	}
	
	fSurface = TTF_RenderUTF8_Blended(font, "One more : 1  Finish : 2", { 255, 255, 255, 255 });

	fMessage = SDL_CreateTextureFromSurface(fRenderer, fSurface);

	SDL_SetRenderDrawColor(fRenderer, 0, 0, 0, 255);
	SDL_RenderClear(fRenderer);

	int iw, ih;
	SDL_QueryTexture(fMessage, NULL, NULL, &iw, &ih);

	SDL_Rect txtRect = { 0,0,iw,ih };
	SDL_Rect pasteRect = { 80,80,iw,ih };


	SDL_RenderCopy(fRenderer, fMessage, &txtRect, &pasteRect);
	SDL_RenderPresent(fRenderer);

	int checkContinue = 0;
	while (true) {
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			switch (event.type) {

			case SDL_KEYDOWN:
				break;

			case SDL_QUIT:
				mIsRunning = false;
				break;
			}
		}
		const Uint8* state = SDL_GetKeyboardState(NULL);
		
		if (state[SDL_SCANCODE_1])
		{
			checkContinue = 1;
		}
		else if (state[SDL_SCANCODE_2]) {
			checkContinue = 2;
		}

		if (checkContinue != 0) break;
	}
	SDL_DestroyRenderer(fRenderer);
	SDL_DestroyWindow(fWindow);
	return checkContinue;

}

void tetofour::Display() {
	SDL_SetRenderDrawColor(
		mRenderer,
		224,//r
		255,//g
		255,//b
		255//a...������
	);

	SDL_RenderClear(mRenderer);

	SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);

	SDL_Rect wall{
		Wrange,//����x
		Hrange,//����y
		5,//����
		height - Hrange * 2//�c��
	};

	//�g��������(�c6�~��7�A1�}�X120�~120)
	for (int i = Wrange; i <= width - Wrange; i += mass) {
		wall.x = i;
		SDL_RenderFillRect(mRenderer, &wall);
	}
	wall.x = Wrange;
	wall.h = 5;
	wall.w = width - Wrange * 2 + 5;
	for (int i = Hrange; i <= height - Hrange; i += mass) {
		wall.y = i;
		SDL_RenderFillRect(mRenderer, &wall);
	}

	//�̋��ݒ�
	blue = SDL_LoadBMP("img\\blue.bmp");
	BlueTex = SDL_CreateTextureFromSurface(mRenderer, blue);
	SDL_FreeSurface(blue);

	//�Ԃ̋��ݒ�
	red = SDL_LoadBMP("img\\red.bmp");
	RedTex = SDL_CreateTextureFromSurface(mRenderer, red);
	SDL_FreeSurface(red);
	
	white = SDL_LoadBMP("img\\white.bmp");
	whiteTex = SDL_CreateTextureFromSurface(mRenderer, white);
	SDL_FreeSurface(white) ;

	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 7; j++) {
			if (b.sboard[i][j] == "red") {
				b.board[i][j] = RedTex;
			}
			else if (b.sboard[i][j] == "blue") {
				b.board[i][j] = BlueTex;
			}
			else {
				b.board[i][j] = nullptr;
			}
			SDL_RenderCopy(mRenderer, b.board[i][j], nullptr, &b.boardPos[i][j]);
		}
	}
	
	for (int i = 0; i < 4; i++) {
		if (b.rsboard[i] == "white") {
			SDL_RenderCopy(mRenderer, whiteTex, nullptr, &b.rboardPos[i]);
		}
		
	}
	
	SDL_RenderPresent(mRenderer);
}

void tetofour::ProcessInput() {
	bool click = false;
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type){

		case SDL_KEYDOWN:
			break;

		case SDL_MOUSEBUTTONDOWN:
			SDL_GetMouseState(&mouse_position.x, &mouse_position.y);
			click = true;
			break;

		case SDL_QUIT:
			mIsRunning = false;
			break;
		}
	}
	
	if (mode == 1) {
		if (click) {
			Player p(t, b);
			 mIsRunning = p.Run(mouse_position.x, mouse_position.y,turn);
		}
	}
	else if (mode == 2) {
		if (turn == myturn) {
			if (click) {
				Player p(t, b);
				mIsRunning = p.Run(mouse_position.x, mouse_position.y,turn);
			}
		}
		else {
			Cpu c(t, b);
			SDL_Delay(300);
			mIsRunning = c.Run(turn,level);
		}
	}
}

void tetofour::RunLoop() {
	//���[�h�I��
	Start(1);
	//������cpu�Ȃ�
	if (mode == 2) {
		//��U��U�I��
		Start(2);
		//cpu���x���I��
		Start(3);
	}
	
	while (mIsRunning) {
		ProcessInput();
		Display();
	}
}

void tetofour::Result(int turn) {
	int ttfresult = TTF_Init();
	if (ttfresult != 0) {
		SDL_Log("Failed to TTF Init: %s", SDL_GetError());
	}

	rWindow = SDL_CreateWindow(
		"Result",//�^�C�g��
		width /3,//�����x
		height/3,//�����y
		width / 2,//��
		height / 4,//����
		0//�t���O
	);
	if (!rWindow) {
		SDL_Log("Failed to create rWindow : %s", SDL_GetError());
		return;
	}

	rRenderer = SDL_CreateRenderer(
		rWindow,
		-1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC //�t���O
	);
	if (!rRenderer) {
		SDL_Log("Failed to create rRenderer: %s", SDL_GetError());
		return;
	}

	font = TTF_OpenFont(FONT_PATH, 60);
	if (!font) {
		SDL_Log("Failed to Open TTF: %s", SDL_GetError());
		return;
	}
	//��U�Ȃ�Ԃ̏���
	if (turn == 1) {
		rSurface = TTF_RenderUTF8_Blended(font, "Red Win!!", { 255, 255, 255, 255 });
	}
	//��U�Ȃ�̏���
	else if (turn == -1) {
		rSurface = TTF_RenderUTF8_Blended(font, "Blue Win!!", { 255, 255, 255, 255 });
	}
	
	rMessage = SDL_CreateTextureFromSurface(rRenderer, rSurface);

	SDL_SetRenderDrawColor(rRenderer, 0, 0, 0, 255);
	SDL_RenderClear(rRenderer);

	int iw, ih;
	SDL_QueryTexture(rMessage, NULL, NULL, &iw, &ih);

	SDL_Rect txtRect = { 0,0,iw,ih };
	SDL_Rect pasteRect = { 100,90,iw,ih };


	SDL_RenderCopy(rRenderer, rMessage, &txtRect, &pasteRect);
	SDL_RenderPresent(rRenderer);

	SDL_Delay(2000);
	SDL_DestroyRenderer(rRenderer);
	SDL_DestroyWindow(rWindow);
	
	return;
}

void tetofour::Shutdown() {
	turn = 1;
	myturn = 0;
	mode = 0;
	level = 0;
	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
	TTF_CloseFont(font);
	TTF_Quit();
}
