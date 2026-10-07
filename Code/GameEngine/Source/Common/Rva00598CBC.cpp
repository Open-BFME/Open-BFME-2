// cl: /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva00598CBC@Rva00598CBC@@QAEXXZ @0x00598CBC 65B via vector-assign plus slot-gated push_back
// Evidence: chain from 0x00598007; caller 0x004EBFC2; vector at +0x4C like Rva00598B2A; m_30 at +0x30 like Rva00598007; rowed vector assign 0x000BDB46 and push_back 0x0002DBE6 and Find 0x00506C82; global g_00E063D4
// The emitted unsigned max copy must match retail RVA 0x00013740.
// Define it for speed, then restore this unit's flags for its own bodies.
#include <stl/_algobase.h>
#pragma optimize("s", off)
#pragma optimize("t", on)
namespace _STL {
template <> inline const unsigned int &max<unsigned int>(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#pragma optimize("", on)

#include <vector>
#include "ascii_string.h"

struct MidVecHolder
{
	char _pad[0x8c];
	_STL::vector<AsciiString> m_vec;
};

struct Rva002A8AB1Record
{
	char _pad0[0x160];
	MidVecHolder *m_160;
};

class Rva00598007
{
public:
	Rva002A8AB1Record *rva00598007();
};

struct Rva00506C82Arg
{
	char _pad[0x50];
	int m_50;
};

class GameSlot
{
public:
	char _pad[0x50];
	int m_50;
};

GameSlot *__cdecl Rva00506C82Find(const Rva00506C82Arg *arg);

extern AsciiString g_00E063D4;

class Rva00598CBC
{
public:
	void rva00598CBC();
private:
	char _pad0[0x30];
	void *m_30;
	char _pad1[0x4c - 0x34];
	_STL::vector<AsciiString> m_vec;
};

void Rva00598CBC::rva00598CBC()
{
	Rva002A8AB1Record *rec = ((Rva00598007 *)this)->rva00598007();
	_STL::vector<AsciiString> &src = rec->m_160->m_vec;
	m_vec = src;
	GameSlot *slot = Rva00506C82Find((const Rva00506C82Arg *)m_30);
	if (slot && slot->m_50 != 0) {
		m_vec.push_back(g_00E063D4);
	}
}
