// cl: /Ireference/shims/bfme2_ascii /DBFME_ASCII_DTOR_DECL /O1 /G7 /arch:SSE /Oy- /DNDEBUG /MD /EHsc
//
// ?Rva003336ADGet@@YA_N_NPBD@Z @0x003336AD (117B): cdecl bool(bool, const char *).
// Reads the drawable link at +0x9C of the Lua state global (VA 0x00E01DBC, see
// CurDrawablePrevAnimFraction.cpp) and, when the link is set, its drawable at
// +0x0C. With a drawable it forwards the name as a temporary AsciiString to the
// rowed Drawable 0x00278689 with the flag inverted and a false tail argument,
// returning that result; every other path returns false.
// Target evidence: global/offset reads and the rowed callee; the Lua-state and
// link struct names are views shared with the CurDrawable siblings. The slot is
// read through a volatile view: retail keeps the +0x9C address and loads it twice.
#include "ascii_string.h"

class Drawable
{
public:
	bool rva00278689(const AsciiString &name, bool a, bool b);
};

struct LuaDrawableLink3336AD
{
	char m_pad000[0x0C];
	Drawable *m_drawable;	// +0x0C
};

struct LuaDrawableHolder3336AD
{
	LuaDrawableLink3336AD *m_link;
};

struct LuaDrawableState3336AD
{
	char m_pad000[0x9C];
	LuaDrawableHolder3336AD m_holder;	// +0x9C
};
class LuaScriptEngine;
extern LuaScriptEngine *TheLuaScriptEngine;

// ?Rva003336ADGet@@YA_N_NPBD@Z
bool Rva003336ADGet(bool flag, const char *name)
{
	LuaDrawableLink3336AD *volatile *slot = &reinterpret_cast<LuaDrawableState3336AD *>(TheLuaScriptEngine)->m_holder.m_link;
	if (*slot)
	{
		Drawable *drawable = (*slot)->m_drawable;
		AsciiString key(name);
		if (drawable)
			return drawable->rva00278689(key, !flag, false);
	}
	return false;
}
