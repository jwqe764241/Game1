#include "Game.h"


int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow) 
{
	if (SUCCEEDED(CoInitialize(NULL))) {

		{
			Game game = Game(hInstance, "#729814545_Game");

			//TODO:���Ӿȿ� Frame ���� �����ͷ� ���� �� �ֵ��� �ϱ�
			if (game.Start(nCmdShow, "What the fuck") == S_OK)
				game.StartLooping();

			CoUninitialize();
		}
	}
}