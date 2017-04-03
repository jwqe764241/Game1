#pragma once

#include "IDrawable.h"
#include "IDelegate.h"
#include "TextWriter.h"
#include "SpriteSheet.h"

class Button : public IDrawable
{
public:
	Button(wchar_t* normal, wchar_t* focus, wchar_t* click, wchar_t* labelText, D2D1_POINT_2F offset);
	~Button();

	virtual void CreateDeviceResources() override;
	virtual void ReleaseDeviceResources() override;

	virtual void Draw() override;

	void SetSize(float width, float height);
	D2D1_SIZE_F GetSize();

protected:
	void SetPressed(bool value);
	bool GetPressed();

	void SetFocused(bool value);
	bool GetFocused();

public:
	D2D1_POINT_2F m_offset;

	SpriteSheet m_normalSpriteSheet;
	SpriteSheet m_focusedSpriteSheet;
	SpriteSheet m_clickedSpriteSheet;

private:
	D2D1_SIZE_F m_size;

	bool m_pressed;
	bool m_focused;

	TextWriter m_buttonLabelLayout;
	wchar_t* m_buttonLabelText;

};