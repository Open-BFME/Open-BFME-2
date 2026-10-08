// cl: /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
// ?rva003BA537@@YAHPAURva003BA537Arg@@H@Z @0x003BA537 101B: the argc-gated append of
// 0x003BA4DB, with the else branch setting the byte at 0x00E02D78.
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
extern unsigned char g_00E02D78;

struct Rva003BA537Arg
{
	char m_pad00[4];
	const char *m_04;
};

// ?rva003BA537@@YAHPAURva003BA537Arg@@H@Z @0x003BA537
int __cdecl rva003BA537(Rva003BA537Arg *arg, int argc)
{
	if (g_00DFE758 != 0 && argc > 1)
	{
		AsciiString text(arg->m_04);
		((_STL::vector<AsciiString> *)((char *)g_00DFE758 + 0x10F4))->push_back(text);
	}
	else
	{
		g_00E02D78 = 1;
	}
	return 2;
}
