#include "TestButton.h"

TestButton::TestButton(wchar_t * normal, wchar_t * focus, wchar_t * click, wchar_t * labelText, D2D1_POINT_2F offset, int id):
	Button(normal, focus, click, labelText, offset),
	m_iButtonId(id)
{
}
TestButton::~TestButton()
{
}


void TestButton::OnLeftMouseClick()
{
	SetPressed(true);
}

void TestButton::OnLeftMouseRelease()
{
	SetPressed(false);
}

void TestButton::OnRightMouseClick()
{
}

void TestButton::OnRightMouseRelease()
{
}

void TestButton::OnFocus()
{
	SetFocused(true);
}

void TestButton::OnFocusOut()
{
	SetFocused(false);
}
