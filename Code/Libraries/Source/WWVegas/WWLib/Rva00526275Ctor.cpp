// cl: /Ireference/shims/bfmelist /GX /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??0Rva00526275@@QAE@XZ @0x00526275 74B evidence: member +0 Rva00330757Member 0x00330757 size 0x10 then lists +0x10/+0x14 via rowed Coord3D List_base 0x00280A8D then zero +0x18; factory 0x00526F46 allocs 0x1c.
// Honest-address ctor (naming rule).
#include <list>

#include "../../../Include/Lib/Coord3D.h"

class Rva00330757Member
{
public:
	Rva00330757Member();
	~Rva00330757Member();
private:
	char m_pad[0x10];
};

class Rva00526275
{
public:
	Rva00526275();
private:
	Rva00330757Member m_head;
	_STL::list<Coord3D> m_list10;
	_STL::list<Coord3D> m_list14;
	int m_18;
};

Rva00526275::Rva00526275() : m_head(), m_list10(), m_list14()
{
	m_18 = 0;
}
