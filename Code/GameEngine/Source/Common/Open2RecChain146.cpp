// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
//
// Retail 0x001EF90E 146B:
// ?rva001EF90E@Rva001EF90E@@QAEXVAsciiString@@HVUnicodeString@@HH@Z
// Chain from 0x001EF5BD: GetMap virtual 0x54 returns RecMap for find and
// end check. On found copies Open2Rec from node+0x14 and calls Bar virtual
// 0xFC with (rec wide int int). Second arg at +0xC unused proving 5-arg
// shape with ret 0x14. Dummy virtuals pad GetMap to 21 and Bar to 63.
//
#pragma optimize("t", on)
#include <map>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _Rb_tree_iterator<T, LeftTraits>& a,
                              const _Rb_tree_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}
#pragma optimize("", on)

typedef unsigned short RawWChar;

template <typename T>
struct BfmeStringData
{
	int refCount;
	unsigned short length;
	unsigned short capacity;
	T text[1];
};

#include "ascii_string.h"


#include "unicode_string.h"

struct AsciiComparator
{
	bool operator()(AsciiString s1, AsciiString s2) const;
};

class Open2Rec4F1120
{
public:
	AsciiString m_at00;
	AsciiString m_at04;
	AsciiString m_at08;
	int m_at0c;
	int m_at10;
	int m_at14;
	int m_at18;
	int m_at1c;
	int m_at20;
	int m_at24;
	int m_at28;
	int m_at2c;
	int m_at30;
};

typedef _STL::map<AsciiString, Open2Rec4F1120, AsciiComparator> Rec4F1120Map;

class Rva001EF90E
{
public:
	virtual void D00(); virtual void D01(); virtual void D02(); virtual void D03();
	virtual void D04(); virtual void D05(); virtual void D06(); virtual void D07();
	virtual void D08(); virtual void D09(); virtual void D10(); virtual void D11();
	virtual void D12(); virtual void D13(); virtual void D14(); virtual void D15();
	virtual void D16(); virtual void D17(); virtual void D18(); virtual void D19();
	virtual void D20();
	virtual Rec4F1120Map *GetMap();
	virtual void D22(); virtual void D23(); virtual void D24(); virtual void D25();
	virtual void D26(); virtual void D27(); virtual void D28(); virtual void D29();
	virtual void D30(); virtual void D31(); virtual void D32(); virtual void D33();
	virtual void D34(); virtual void D35(); virtual void D36(); virtual void D37();
	virtual void D38(); virtual void D39(); virtual void D40(); virtual void D41();
	virtual void D42(); virtual void D43(); virtual void D44(); virtual void D45();
	virtual void D46(); virtual void D47(); virtual void D48(); virtual void D49();
	virtual void D50(); virtual void D51(); virtual void D52(); virtual void D53();
	virtual void D54(); virtual void D55(); virtual void D56(); virtual void D57();
	virtual void D58(); virtual void D59(); virtual void D60(); virtual void D61();
	virtual void D62();
	virtual void Bar(Open2Rec4F1120 rec, UnicodeString msg, int a, int b);
	void rva001EF90E(AsciiString key, int dummy, UnicodeString msg, int a, int b);
};

void Rva001EF90E::rva001EF90E(AsciiString key, int dummy, UnicodeString msg, int a, int b)
{
	Rec4F1120Map *m1 = GetMap();
	Rec4F1120Map::iterator it = m1->find(key);
	Rec4F1120Map *m2 = GetMap();
	if (it != m2->end()) {
		Bar(it->second, msg, a, b);
	}
}
