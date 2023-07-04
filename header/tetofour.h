#pragma once
#include "SDL.h"
#include "SDL_ttf.h"
using namespace std;
#include "header\\stdc++.h"

class tetofour
{
public:
	tetofour();
	//�ŏ��̐ݒ��I��
	void Start(int No);
	//�������֐�
	bool Initialize();
	//���s��
	void RunLoop();
	//����
	void Result(int turn);
	//�I�����p�����I��
	int Finish();
	//�V���b�g�_�E��
	void Shutdown();

	//�t�H���g�w��
	TTF_Font* font;
	#define FONT_PATH "PixelMplus-20130602\\PixelMplus10-Regular.ttf"

	int turn = 1; //1:��  -1:��

	int myturn = 0; //��sor��U
	
	int mode = 0;//1:�ΐl 2:��cpu

	int level = 0; //cpu�̃��x��
	#define EASY 50
	#define NORMAL 800
	#define HARD 3000
	//�E�B���h�E�̏c��
	const int height = 720;
	//�E�B���h�E�̉���
	const int width = 840;

	//�g�O�̕�
	const int Hrange = 60;
	const int Wrange = 70;

	//�N���b�N�������W
	SDL_Point mouse_position;

	//1�}�X�̑傫��
	const int mass = (width - Wrange * 2) / 7;

private:
	////���C���E�B���h�E�ɂ���////
	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;

	////���U���g�E�B���h�E�ɂ���////
	SDL_Window* rWindow;
	SDL_Renderer* rRenderer;
	SDL_Surface* rSurface;
	SDL_Texture* rMessage;

	/////�X�^�[�g�E�B���h�E�ɂ���/////
	SDL_Window* sWindow;
	SDL_Renderer* sRenderer;
	SDL_Surface* sSurface;
	SDL_Texture* sMessage;

	/////�t�B�j�b�V���E�B���h�E�ɂ���////
	SDL_Window* fWindow;
	SDL_Renderer* fRenderer;
	SDL_Surface* fSurface;
	SDL_Texture* fMessage;
	
	////��ɂ���//////
	SDL_Surface* blue;
	SDL_Surface* red;
	SDL_Texture* BlueTex;
	SDL_Texture* RedTex;
	SDL_Surface* white;
	SDL_Texture* whiteTex;
	
	//�\���֐�
	void Display();
	//���͏���
	void ProcessInput();
	
	//�����邩�ǂ���
	bool mIsRunning;
};