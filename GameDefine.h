#pragma once

#include <Windows.h>

namespace GameUtils{

	template <typename T>
	void SafeRelease(T ** pTy) {
		if(pTy) {
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
