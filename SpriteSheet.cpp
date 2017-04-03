#include "SpriteSheet.h"

SpriteSheet::SpriteSheet(const wchar_t* fileName):
	m_fileName(fileName),
	m_pBitmap(NULL),
	m_pBitmapBrush(NULL)
{
	CreateDeviceResources();
	m_spriteAcross = 1;
}
SpriteSheet::SpriteSheet(const wchar_t * fileName, UINT spriteWidth, UINT spriteHeight)
	: SpriteSheet(fileName)
{
	m_spriteWidth = spriteWidth;
	m_spriteHeight = spriteHeight;
	m_spriteAcross = (UINT)m_pBitmap->GetSize().width / spriteWidth;
}
SpriteSheet::~SpriteSheet()
{
	ReleaseDeviceResources();
}


void SpriteSheet::CreateDeviceResources()
{
	LoadBitmapFromFile(m_fileName, &m_pBitmap);
	m_spriteWidth = m_pBitmap->GetSize().width;
	m_spriteHeight = m_pBitmap->GetSize().height;
}

void SpriteSheet::ReleaseDeviceResources()
{
	GameUtils::SafeRelease(&m_pBitmap);
	GameUtils::SafeRelease(&m_pBitmapBrush);
}

void SpriteSheet::Draw()
{
	Graphics::GetInstance()->GetRenderTarget()->DrawBitmap(
		m_pBitmap,
		D2D1::RectF(0.f, 0.f,
			m_pBitmap->GetSize().width,
			m_pBitmap->GetSize().height),
		1.0f,
		D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR,
		D2D1::RectF(0.f, 0.f,
			m_pBitmap->GetSize().width,
			m_pBitmap->GetSize().height)
	);
}

void SpriteSheet::Draw(UINT index, float x, float y)
{
	D2D1_RECT_F src = D2D1::RectF(
		(FLOAT)((index % m_spriteAcross) * m_spriteWidth),
		(FLOAT)((index / m_spriteAcross) * m_spriteHeight),
		(FLOAT)((index % m_spriteAcross) * m_spriteWidth) + m_spriteWidth-1,
		(FLOAT)((index / m_spriteAcross) * m_spriteHeight) + m_spriteHeight-1
	);

	D2D1_RECT_F dest = D2D1::RectF(
		x, y,
		x + m_spriteWidth, y + m_spriteHeight
	);

	Graphics::GetInstance()->GetRenderTarget()->DrawBitmap(
		m_pBitmap,
		dest,
		1.0f,
		D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR,
		src
	);
}

void SpriteSheet::Draw(float x, float y, float width, float height)
{
	D2D1_RECT_F dest = D2D1::RectF(x, y, x + width, y + height);
	Graphics::GetInstance()->GetRenderTarget()->DrawBitmap(
		m_pBitmap,
		dest,
		1.0f,
		D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR,
		D2D1::RectF(0.f, 0.f, m_spriteWidth, m_spriteHeight)
	);
}

HRESULT SpriteSheet::LoadBitmapFromFile(
	PCWSTR resourceName,
	ID2D1Bitmap** ppBitmap)
{
	IWICBitmapDecoder *pDecoder		= nullptr;
	IWICBitmapFrameDecode *pSource	= nullptr;
	IWICStream *pStream				= nullptr;
	IWICFormatConverter *pConverter = nullptr;
	IWICBitmapScaler *pScaler		= nullptr;

	DWORD imageFileSize = 0;

	HRESULT hr = Graphics::GetInstance()->GetImagingFactory()->CreateDecoderFromFilename(
		resourceName,
		NULL,
		GENERIC_READ,
		WICDecodeMetadataCacheOnLoad,
		&pDecoder
	);
	if (SUCCEEDED(hr))
	{
		hr = pDecoder->GetFrame(0, &pSource);
	}

	if (SUCCEEDED(hr))
	{
		hr = Graphics::GetInstance()->GetImagingFactory()->CreateFormatConverter(&pConverter);
	}

	if (SUCCEEDED(hr))
	{
		hr = pConverter->Initialize(
			pSource,
			GUID_WICPixelFormat32bppPBGRA,
			WICBitmapDitherTypeNone,
			NULL,
			0.f,
			WICBitmapPaletteTypeMedianCut
		);
	}

	if (SUCCEEDED(hr))
	{
		hr = Graphics::GetInstance()->GetRenderTarget()->CreateBitmapFromWicBitmap(
			pConverter,
			NULL,
			ppBitmap
		);
	}

	GameUtils::SafeRelease(&pDecoder);
	GameUtils::SafeRelease(&pSource);
	GameUtils::SafeRelease(&pStream);
	GameUtils::SafeRelease(&pConverter);
	GameUtils::SafeRelease(&pScaler);

	return hr;
}