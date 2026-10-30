// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /GX
//
// _fprintf, retail 0x002CEC42, 108 bytes.
//
// Game-side format-and-append helper (extern C, cdecl varargs, 357 raw
// callers passing an object plus a format string): null format returns
// immediately, otherwise the args format through msvcr71 _vsnprintf into a
// 1000-byte frame buffer, an AsciiString temp takes the buffer through the
// rowed const-char constructor at 0x37BA0, and the line appends to the
// object's vector at +4 through vector<AsciiString>::push_back (pinned
// 0x2DBE6, whose AsciiString element is proven by the 0x2C485 copy helper
// calling the rowed 0x365F0 copy ctor) before the temp tears down through
// the 0x36410 fold. The first object field is unproven padding.

#include "../../../../reference/shims/bfme2_ascii/ascii_string.h"
#include <stdarg.h>

extern "C" __declspec(dllimport) int __cdecl _vsnprintf(char *buffer, unsigned int size, const char *format, va_list args);

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

struct FprintfTarget
{
	char m_pad[4];
	BfmeVector<AsciiString> m_lines;
};

// _fprintf
extern "C" void fprintf(FprintfTarget *target, const char *format, ...)
{
	if (format == 0)
		return;
	char buffer[1000];
	va_list args;
	va_start(args, format);
	_vsnprintf(buffer, sizeof(buffer), format, args);
	va_end(args);
	AsciiString tmp(buffer);
	target->m_lines.push_back(tmp);
}
