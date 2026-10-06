// cl: /Oi /DNDEBUG /MD
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

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:__strdup=_strdup")
