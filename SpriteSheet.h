#pragma once
#include "Graphics.h"
#include "IDrawable.h"
#include "GameDefine.h"

class SpriteSheet : public IDrawable
{
private:
	const wchar_t* m_fileName;

	ID2D1Bitmap* m_pBitmap;
	ID2D1BitmapBrush* m_pBitmapBrush;

public:
	UINT m_spriteWidth, m_spriteHeight;
	UINT m_spriteAcross;

public:
	SpriteSheet(const wchar_t* fileName);
	SpriteSheet(const wchar_t* fileName, UINT spriteWidth, UINT spriteHeight);
	~SpriteSheet();

	virtual void CreateDeviceResources();
	virtual void ReleaseDeviceResources();
	virtual void Draw();
			void Draw(UINT index, float x, float y); // overloaded.
			void Draw(float x, float y, float width, float height); // overloaded.

	D2D1_SIZE_F GetSize() { return D2D1_SIZE_F{ static_cast<float>(m_spriteWidth), static_cast<float>(m_spriteHeight) }; }
private:
	HRESULT LoadBitmapFromFile(PCWSTR resourceName, ID2D1Bitmap ** ppBitmap);
};