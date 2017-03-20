#pragma once

#include <Windows.h>

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
		void myassert(bool, ...);
	}

	namespace Constant 
	{
	}

}