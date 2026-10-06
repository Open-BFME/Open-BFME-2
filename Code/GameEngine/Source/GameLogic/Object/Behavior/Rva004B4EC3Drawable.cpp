// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD
// ?Rva004B4EC3@@YG_NPAVDrawable@@PAXMM@Z @0x004B4EC3 78B: drawable subobject broadcast.
// Iterates AsciiString range at +0xC (begin at +0 end at +4, 4B elements),
// calls rowed Drawable 0x00278689 with (elem,1,0) then rowed 0x002724FD with
// (elem,1,1,float at +0x10,float at +0x14) via rowed Drawable this at +0x8.
// Returns false if empty else true. Frees 0x10. Callers 0x004B50A9 0x004B51BE.
#include "ascii_string.h"

class Drawable
{
public:
	bool rva00278689(const AsciiString &name, bool a2, bool a3);
	void rva002724FD(const AsciiString &a, int b, int c, float d, float e);
};

bool __stdcall Rva004B4EC3(Drawable *drawable, void *range, float c, float d)
{
	AsciiString *cur = *(AsciiString **)range;
	bool ret = false;
	if (cur != *(AsciiString **)((char *)range + 4)) {
		ret = true;
		for (; cur != *(AsciiString **)((char *)range + 4); ++cur)
		{
			drawable->rva00278689(*cur, true, false);
			drawable->rva002724FD(*cur, 1, 1, c, d);
		}
	}
	return ret;
}
