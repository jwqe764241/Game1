#pragma once

class IDelegate
{
public:
	virtual void OnLeftMouseClick() = 0;
	virtual void OnLeftMouseRelease() = 0;

	virtual void OnRightMouseClick() = 0;
	virtual void OnRightMouseRelease() = 0;

	virtual void OnFocus() = 0;
	virtual void OnFocusOut() = 0;
};