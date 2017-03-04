#include "Game.h"

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow) {

	if (SUCCEEDED(CoInitialize(NULL))){
		{
			Game * game = new Game(hInstance);

			if (game->Start(nCmdShow) != S_OK) {
				//TODO:게임시작 오류 에러처리
			}
		}
		CoUninitialize();
	}

}