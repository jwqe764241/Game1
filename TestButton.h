#pragma once

#include "Button.h"
#include "IDelegate.h"

class TestButton : public Button, public IDelegate
{
public:
	TestButton(wchar_t* normal, wchar_t* focus, wchar_t* click, wchar_t* labelText, D2D1_POINT_2F offset);
	~TestButton();

	virtual void OnLeftMouseClick()   override;
	virtual void OnLeftMouseRelease() override;

	virtual void OnRightMouseClick()   override;
	virtual void OnRightMouseRelease() override;

	virtual void OnFocus()    override;
	virtual void OnFocusOut() override;
};