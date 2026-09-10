// cl: /O2 /G6 /Oi /DNDEBUG /MD
//
// strdup, retail 0x006C4C70, 57 bytes. Inlined strlen, two-argument
// byte allocator (size, tag 0), then memcpy as rep movsd/movsb.

#include <string.h>
#pragma intrinsic(strlen)
#pragma intrinsic(memcpy)

namespace _STL
{
	template<class T>
	class allocator
	{
	public:
		static T *allocate(unsigned n, void const *hint);
	};
}

extern "C" char *strdup(const char *s)
{
	unsigned n = (unsigned)strlen(s) + 1;
	char *d = _STL::allocator<char>::allocate(n, 0);
	memcpy(d, s, n);
	return d;
}
