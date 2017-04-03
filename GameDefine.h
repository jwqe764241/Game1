#pragma once

#include <Windows.h>
#include <math.h>

//#ifndef HINST_THISCOMPONENT
//EXTERN_C IMAGE_DOS_HEADER __ImageBase;
//#define HINST_THISCOMPONENT ((HINSTANCE)&__ImageBase)
//#endif // !HINST_THISCOMPONENT

namespace GameUtils{

	template <typename T>
	void SafeRelease(T ** pTy) {
		if((*pTy)) {
			(*pTy)->Release();
			(*pTy) = NULL;
		}
	}

	namespace Debug 
	{
	}

	namespace Type {
		typedef char State;

		typedef struct _SCREENSIZE {
			int width;
			int height;
		} SCREENSIZE, *LPSCREENSIZE;

		typedef struct _MOUSEPOINT {
			int x;
			int y;
		} MOUSEPOINT, *LPMOUSEPOINT;
	}

	namespace Constant 
	{
		namespace Enemy {
			const GameUtils::Type::State STATE_DIED  = 1;
			const GameUtils::Type::State STATE_ALiVE = 2;
		}

		namespace Button {
			const int BUTTON_START  = 0;
			const int BUTTON_RANK   = 1;
			const int BUTTON_HOW    = 2;
			const int BUTTON_INFO   = 3;
			const int BUTTON_CREDIT = 4;
		}

		namespace Level {
			const int LEVEL_MAIN    = WM_USER + 1;
			const int LEVEL_LEVEL1  = WM_USER + 2;
			const int LEVEL_LEVEL2  = WM_USER + 3;
			const int LEVEL_RANK    = WM_USER + 4;
			const int LEVEL_HOW     = WM_USER + 5;
			const int LEVEL_INFO    = WM_USER + 6;
			const int LEVEL_CREDIT  = WM_USER + 7;
			const int LEVEL_END     = WM_USER + 8;
		}

	}

}