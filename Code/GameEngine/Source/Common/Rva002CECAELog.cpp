// cl: /DNDEBUG /MD /GX
//
// Rva002CECAEAppend, retail 0x002CECAE, 120 bytes.
//
// Guarded format-and-append sibling of _fprintf in FprintfAppendLine.cpp:
// when the TheGameLogic byte at +0x70 is set and format is non-null, the
// args format through msvcr71 _vsnprintf into a 1000-byte frame buffer, a
// StringBase temp takes the buffer through the rowed const-char
// constructor at 0x37BA0, and the line appends to the target's vector at
// +4 through the same BfmeVector<AsciiString>::push_back spelling the
// _fprintf TU lands, before the temp tears down through the 0x36410 fold.
// Four callers in 0x006F477E pass target plus format; the owning target
// class is otherwise unproven, so the honest address name stands.

#include <stdarg.h>

extern "C" __declspec(dllimport) int __cdecl _vsnprintf(char *buffer, unsigned int size, const char *format, va_list args);

template <typename T>
class StringBase
{
public:
	StringBase(const T *text);
	~StringBase();

private:
	struct Header
	{
		int ref_count;
		unsigned short length;
		unsigned short capacity;
		T data[1];
	};

	Header *m_data;
};

class AsciiString : public StringBase<char>
{
private:
};

template <typename T>
class BfmeVector
{
public:
	void push_back(const T &x);

private:
	T *m_start;
	T *m_finish;
	T *m_end;
};

class GameLogic
{
public:
	char m_pad[0x70];
	bool m_logEnabled; // +0x70
};

extern GameLogic *TheGameLogic;

struct Rva002CECAETarget
{
	char m_pad[4];
	BfmeVector<AsciiString> m_lines;
};

void Rva002CECAEAppend(Rva002CECAETarget *target, const char *format, ...)
{
	bool enabled = TheGameLogic->m_logEnabled;
	if (enabled && format != 0)
	{
		char buffer[1000];
		va_list args;
		va_start(args, format);
		_vsnprintf(buffer, sizeof(buffer), format, args);
		va_end(args);
		StringBase<char> tmp(buffer);
		target->m_lines.push_back((const AsciiString &)tmp);
	}
}
