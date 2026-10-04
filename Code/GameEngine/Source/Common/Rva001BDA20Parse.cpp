// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /MD
#include "ascii_string.h"
// ?rva00331842@Rva001BDA20@@QAEXPAUlua_State@@H@Z @0x00331842 181B
// Rva001BDA20 Lua-variant reader via lua_type switch and rowed callees.
// Evidence: unlock lane unblocks 0x00335A61; ecx is Rva001BDA20 via set call; callees rowed.
struct lua_State;
extern "C" int __cdecl lua_type(lua_State *L, int idx);
extern "C" const char *__cdecl lua_tostring(lua_State *L, int idx);
extern "C" double __cdecl lua_tonumber(lua_State *L, int idx);

struct Rva00990210Range;
struct Rva00990030Range;
extern unsigned __cdecl Rva00990210Lookup(Rva00990210Range *range, int index);
extern unsigned __cdecl Rva00990030Lookup(Rva00990030Range *range, int index);

class Rva0036CA00Str
{
	void *m_item;
};

class Rva001BDA20
{
	char m_00[4];
	float m_num;
	bool m_bool;
	char m_pad9[3];
	int m_int;
	Rva0036CA00Str m_str;
	int m_tag;
public:
	void set(const Rva0036CA00Str &s);
	void rva00331842(lua_State *L, int idx);
};

void Rva001BDA20::rva00331842(lua_State *L, int idx)
{
	switch (lua_type(L, idx)) {
	case 2:
		m_num = (float)lua_tonumber(L, idx);
		m_tag = 1;
		break;
	case 3: {
		set(*(const Rva0036CA00Str *)&AsciiString(lua_tostring(L, idx)));
		break;
	}
	case 4:
		m_int = (int)Rva00990030Lookup((Rva00990030Range *)L, idx);
		m_tag = 3;
		break;
	case 6: {
		unsigned v = Rva00990210Lookup((Rva00990210Range *)L, idx);
		m_bool = (v != 0);
		m_tag = 2;
		break;
	}
	default:
		m_tag = 0;
		break;
	}
}
