// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD
// ?Rva004B4F11@@YG_NPAVDrawable@@PAXMM@Z @0x004B4F11 86B: drawable conditional broadcast.
// Iterates AsciiString range at +0xC, calls rowed 0x00278689 with (elem,0,1);
// if false calls rowed 0x002724FD with (elem,0,1,-c,d) where c at +0x10
// d at +0x14 via rowed Drawable this at +0x8. Returns true if second call ran.
// Frees 0x10. Callers 0x004B5088 0x004B5183. Sibling of 0x004B4EC3.
#include "ascii_string.h"

class Drawable
{
public:
	bool rva00278689(const AsciiString &name, bool a2, bool a3);
	void rva002724FD(const AsciiString &a, int b, int c, float d, float e);
};

bool __stdcall Rva004B4F11(Drawable *drawable, void *range, float c, float d)
{
	AsciiString *cur = *(AsciiString **)range;
	bool ret = false;
	for (; cur != *(AsciiString **)((char *)range + 4); ++cur)
	{
		if (drawable->rva00278689(*cur, false, true))
			continue;
		drawable->rva002724FD(*cur, 0, 1, -c, d);
		ret = true;
	}
	return ret;
}
