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
	}

}