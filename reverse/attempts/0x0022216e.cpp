// ?Rva0022216EGet@@YAPBDABVAsciiString@@@Z
// partial score=0.95 date=2026-10-05
// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT /Ireference/shims/bfmealloc
// stlport
//
// ?Rva0022216EGet@@YAPBDABVAsciiString@@@Z @0x0022216E (59B).
// Free lookup in the Rva00222061 holder map at g_00DFE4C4+0x28: ensure via
// rowed Rva002220DCInit 0x002220DC, find via rowed _M_find 0x001F8437,
// miss returns 0, hit returns value text (value+8) or 0 when empty.
// Callers 0x0029DD43 0x0029DF3D 0x0029F9A3 0x003C4A80. Prev Rva002220DCInit
// flags plus stlport map flags from Rva00222061Ctor sibling.
#include "ascii_string.h"
#include <map>

class Object
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
};

struct Rva00222061View
{
	char m_pad[0x28];
	_STL::map<AsciiString, AsciiString> m_map;
};

struct Rva00575674
{
	Rva00222061View *volatile m_ptr;
};

extern Rva00575674 g_00DFE4C4;
// ?g_00DFE4C4@@3VRva00575674@@A: the global at VA 0xdfe4c4 is ?g_00DFE4C4@@3PAXA.
#pragma comment(linker, "/alternatename:?g_00DFE4C4@@3VRva00575674@@A=?g_00DFE4C4@@3PAXA")

void Rva002220DCInit();

// ?Rva0022216EGet@@YAPBDABVAsciiString@@@Z
const char *Rva0022216EGet(const AsciiString &key)
{
	if (g_00DFE4C4.m_ptr == 0)
		Rva002220DCInit();
	_STL::map<AsciiString, AsciiString>::iterator it = g_00DFE4C4.m_ptr->m_map.find(key);
	if (it != g_00DFE4C4.m_ptr->m_map.end())
	{
		int v = *(int *)&(*it).second;
		return (const char *)(v ? v + 8 : 0);
	}
	return 0;
}
