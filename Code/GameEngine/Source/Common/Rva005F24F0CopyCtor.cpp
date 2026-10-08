// cl: /O1 /G7 /arch:SSE /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// ??0Rva005F24F0@@QAE@ABV0@@Z, retail 0x005F24F0..0x005F252A (58 bytes, EH,
// RET 4). A copy constructor that default-constructs its leading 0x10-byte
// member (rowed Rva00330757Member 0x00330757) and copies only the set at
// +0x10 from the source (rowed STLport _Rb_tree copy constructor 0x005F2439
// of set<Rva005F2439Element>). There is no WorldBuilder match, so the owner
// stays address-derived. The earlier blocked verdict was on 0x005F2439,
// which is rowed now.

#include <set>
#include <vector>

struct BfmeE16 { float x, y, z, w; };

class Rva00330757Member
{
public:
	Rva00330757Member();

private:
	_STL::vector<BfmeE16> m_items;	// +0x00
	int m_flags;					// +0x0C
};

struct Rva005F2439Element {
 Rva005F2439Element(); Rva005F2439Element(const Rva005F2439Element&);
 ~Rva005F2439Element(); Rva005F2439Element&operator=(const Rva005F2439Element&);
 char bytes[8];
};
bool operator<(const Rva005F2439Element&,const Rva005F2439Element&);

class Rva005F24F0
{
public:
	Rva005F24F0(const Rva005F24F0 &other);

private:
	Rva00330757Member m_member00;				// +0x00
	_STL::set<Rva005F2439Element> m_set10;		// +0x10
};

Rva005F24F0::Rva005F24F0(const Rva005F24F0 &other)
	: m_set10(other.m_set10)
{
}
