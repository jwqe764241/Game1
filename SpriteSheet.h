#pragma once
#include "Graphics.h"
#include "GameDefine.h"

class SpriteSheet
{
private:
	Graphics* gfx;

	ID2D1Bitmap* m_pBitmap;
	ID2D1BitmapBrush* m_pBitmapBrush;
	UINT m_spriteWidth, m_spriteHeight;
	UINT m_spriteAcross;

public:
	SpriteSheet(wchar_t* fileName, Graphics* gfx);
	SpriteSheet(wchar_t* fileName, Graphics* gfx, UINT spriteWidth, UINT spriteHeight);
	~SpriteSheet();

	void Draw();
	void Draw(UINT index, UINT x, UINT y);

private:
	HRESULT LoadBitmapFromFile(PCWSTR resourceName, ID2D1Bitmap ** ppBitmap);
};