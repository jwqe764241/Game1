#include "Game.h"

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow) 
{
	if (SUCCEEDED(CoInitialize(NULL))) {

		{
			Graphics::GetInstance();
			Game game = Game(hInstance, "#CustomGame");

			//TODO:���Ӿȿ� Frame ���� �����ͷ� ���� �� �ֵ��� �ϱ�
			if (game.Start(nCmdShow, "What the fuck") == S_OK)
				game.Looping();

			CoUninitialize();
		}
	}
}