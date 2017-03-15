#pragma once
#include <queue>
#include <bitset>

class Keyboard
{
	friend class Frame;

	class Event
	{
	public:
		enum Type
		{
			Press,
			Release,
			Invalid
		};
	private:
		Type type;
		unsigned char code;
	public:
		Event()
			:
			type(Invalid),
			code(0u)
		{}
		Event(Type type, unsigned char code)
			:
			type(type),
			code(code)
		{}
		bool IsPress() const
		{
			return type == Press;
		}
		bool IsRelease() const
		{
			return type == Release;
		}
		bool IsValid() const
		{
			return type != Invalid;
		}
		unsigned char GetCode() const
		{
			return code;
		}
	};
public:
	Keyboard();
	~Keyboard();

	bool KeyIsPressed(unsigned char keyCode) const;

	void Flush();
	void FlushKey();
	void FlushChar();

	bool KeyIsEmpty() const;
	bool CharIsEmpty() const;

	Keyboard::Event ReadKey();
	           char ReadChar();

	void EnableAutorepeat();
	void DisableAutorepeat();
	bool AutorepeatIsEnable();
private:
	void OnKeyPressed(unsigned char keyCode);
	void OnKeyReleased(unsigned char keyCode);
	void OnChar(char charCode);

	template <typename T>
	void TrimBuffer(std::queue<T>& buffer);
private:
	static constexpr unsigned int nKeys = 256u;
	static constexpr unsigned int bufferSize = 4u;
	bool autorepeatEnable = false;
	std::bitset<nKeys> keyStates;
	std::queue<char> charBuffer;
	std::queue<Event> keyBuffer;

};



