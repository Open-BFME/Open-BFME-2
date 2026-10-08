// cl: /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
// ?rva003BA4DB@@YAHPAURva003BA4DBArg@@H@Z @0x003BA4DB 92B: when the flag holder exists and
// argc is above one, append the argument's text to the holder's string vector at +0xC54.
#include "ascii_string.h"

namespace _STL
{
template <class T> class allocator
{
};

template <class T, class A = allocator<T> > class vector
{
public:
	void push_back(const T &value);
};
}

extern void *g_00DFE758;

struct Rva003BA4DBArg
{
	char m_pad00[4];
	const char *m_04;
};

// ?rva003BA4DB@@YAHPAURva003BA4DBArg@@H@Z @0x003BA4DB
int __cdecl rva003BA4DB(Rva003BA4DBArg *arg, int argc)
{
	if (g_00DFE758 != 0 && argc > 1)
	{
		AsciiString text(arg->m_04);
		((_STL::vector<AsciiString> *)((char *)g_00DFE758 + 0xC54))->push_back(text);
	}
	return 2;
}
