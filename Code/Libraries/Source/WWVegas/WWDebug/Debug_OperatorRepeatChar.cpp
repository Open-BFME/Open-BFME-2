// cl: /DNDEBUG /MD /EHsc
//
// Debug::operator<<(const RepeatChar &), retail 0x0003A620 (127 bytes,
// ret 4). Debug vtable (RVA 0x7BE810) slot 0x3C, where the CheckBegin and
// CrashBegin units call it for their RepeatChar('=', 80) rulers.
//
// Ported from Open-BFME-1 debug_debug.cpp (b1 0x0088B2B0). BFME2 takes the
// RepeatChar by const reference and counts down a local copy of m_count
// instead of consuming the caller's object (retail never stores back to
// [c+4]).

#pragma optimize("y", off)

extern "C" void *memset(void *dest, int value, unsigned int count);

class Debug
{
public:
	class RepeatChar
	{
		friend class Debug;

		char m_char;
		int m_count;

	public:
		RepeatChar(char ch, int count) : m_char(ch), m_count(count) {}
	};

	virtual Debug &operator<<(const RepeatChar &c);

private:
	virtual void AddOutput(const char *str, unsigned int len);
};

// ??6Debug@@UAEAAV0@ABVRepeatChar@0@@Z
Debug &Debug::operator<<(const RepeatChar &c)
{
	int count = c.m_count;
	if (count >= 10)
	{
		char help[10];
		memset(help, c.m_char, 10);
		while ((count -= 10) >= 0)
			Debug::AddOutput(help, 10);
	}
	while (count-- > 0)
		Debug::AddOutput(&c.m_char, 1);
	return *this;
}
