// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??0Rva002FED8D@@QAE@VAsciiString@@@Z, retail 0x002FED8D, 95 bytes.
// Ctor over an AsciiString name (+4, via the pinned StringBase copy ctor
// 0x000365F0), an int +8 set to 1, a _STL::list<BfmePod8> +0x0C built from
// the one-byte stack allocator temporary through the rowed _List_base
// ctor at 0x0035C9A6 (CreateCrateDieModuleDataCtor precedent), and an int
// +0x10 zeroed. The vtable at 0x00807408 is installed by the compiler
// from the virtual dtor below (DIR32-masked like any vtable install).
// The owner class is unproven (callers unclaimed), hence the honest Rva
// address name. The by-value parameter is destroyed at the end through
// the rowed StringBase dtor 0x00036410 (getStaticGameLODIndex precedent).
#include <list>

struct BfmePod8
{
	int a[2];
};

template <typename T> struct BfmeStringData
{
	int refCount;
	unsigned short length;
	unsigned short capacity;
	T text[1];
};

#include "ascii_string.h"


class Rva002FED8D
{
public:
	Rva002FED8D(AsciiString name);
	virtual ~Rva002FED8D();
private:
	AsciiString m_name;
	int m_val8;
	_STL::list<BfmePod8> m_list;
	int m_val10;
};

Rva002FED8D::Rva002FED8D(AsciiString name) : m_name(name), m_val8(1), m_list(), m_val10(0)
{
}

// Rva002FED8D::~Rva002FED8D: defined in Rva002FED8DDtor.cpp (its row's unit).
