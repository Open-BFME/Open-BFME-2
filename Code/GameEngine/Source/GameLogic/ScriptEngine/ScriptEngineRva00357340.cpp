// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva00357340@ScriptEngine@@QAEXPAXPAUCoord3D@@@Z, retail 0x00357340 132B unlock.
// Evidence: list at +0x1A498 from ScriptEngine_dtor; StringBase isEmpty rowed
// 0x00001E2F; CRC Rva003ECA13Get 0x3ECA13; Coord3D normalize rowed 0x000035B6;
// three movsd block copy plus subss trio needs /arch:SSE.
#define _STLP_NO_EXCEPTIONS 1
#include <list>
#include <algorithm>

#include "ascii_string.h"


unsigned long __cdecl Rva003ECA13Get(const AsciiString &s);

#include "../../../../Libraries/Include/Lib/Coord3D.h"


struct Rva00357340Entry
{
	int m_key;
	Coord3D m_pos;
};

struct Rva00357340Arg
{
	char m_pad0[0x38];
	float m_f38;
	float m_f3C;
	float m_f40;
	char m_pad1[0x88 - 0x44];
	AsciiString m_str88;
};

class ScriptEngine
{
public:
	void rva00357340(void *p, Coord3D *dst);

private:
	char m_pad[0x1A498];
	_STL::list<Rva00357340Entry, _STL::allocator<Rva00357340Entry> > m_list1A498; // +0x1A498
};

void ScriptEngine::rva00357340(void *p, Coord3D *dst)
{
	Rva00357340Arg *arg = (Rva00357340Arg *)p;
	if (arg->m_str88.isEmpty())
		return;
	if (!dst)
		return;
	unsigned long crc = Rva003ECA13Get(arg->m_str88);
	for (_STL::list<Rva00357340Entry, _STL::allocator<Rva00357340Entry> >::iterator it = m_list1A498.begin(); it._M_node != m_list1A498.end()._M_node; ++it)
	{
		if (it->m_key == (int)crc)
		{
			*dst = it->m_pos;
			dst->x -= arg->m_f38;
			dst->y -= arg->m_f3C;
			dst->z -= arg->m_f40;
			dst->normalize();
			return;
		}
	}
}
