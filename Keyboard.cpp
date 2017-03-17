#include "Keyboard.h"


Keyboard::Keyboard()
{
}
Keyboard::~Keyboard()
{
}


bool Keyboard::KeyIsPressed(unsigned char keyCode) const
{
	return keyStates[keyCode];
}


void Keyboard::Flush()
{
	FlushKey();
}
void Keyboard::FlushKey()
{
	keyBuffer = std::queue<Event>();
}
void Keyboard::FlushChar()
{
	charBuffer = std::queue<char>();
}


bool Keyboard::KeyIsEmpty() const
{
	return keyBuffer.empty();
}
bool Keyboard::CharIsEmpty() const
{
	return charBuffer.empty();
}


Keyboard::Event Keyboard::ReadKey()
{
	if (keyBuffer.size() > 0u) {
		Keyboard::Event event = keyBuffer.front();
		keyBuffer.pop();
		return event;
	}
	else {
		return Keyboard::Event();
	}
}
char Keyboard::ReadChar()
{
	if (charBuffer.size() > 0u) {
		unsigned char charCode = charBuffer.front();
		charBuffer.pop();
		return charCode;
	}
	else {
		return NULL;
	}
}


void Keyboard::EnableAutorepeat()
{
	autorepeatEnable = true;
}
void Keyboard::DisableAutorepeat()
{
	autorepeatEnable = false;
}
bool Keyboard::AutorepeatIsEnable()
{
	return autorepeatEnable;
}


void Keyboard::OnKeyPressed(unsigned char keyCode)
{
	keyStates[keyCode] = true;
	keyBuffer.push(Keyboard::Event(Keyboard::Event::Press, keyCode));
	TrimBuffer(keyBuffer);
}
void Keyboard::OnKeyReleased(unsigned char keyCode)
{
	keyStates[keyCode] = false;
	keyBuffer.push(Keyboard::Event(Keyboard::Event::Release, keyCode));
	TrimBuffer(keyBuffer);
}
void Keyboard::OnChar(char charCode)
{
	charBuffer.push(charCode);
	TrimBuffer(charBuffer);
}
template <typename T>
void Keyboard::TrimBuffer(std::queue<T>& buffer)
{
	while (buffer.size() > bufferSize) {
		buffer.pop();
	}
}
