// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// ?reserve@?$vector@URva0008DE1CElement@@V?$allocator@URva0008DE1CElement@@@_STL@@@_STL@@QAEXI@Z @0x0008B5B5 125B
// Evidence: unlock lane; 24B element via push 0x18 pop idiv; callees _M_allocate_and_copy 0x0008A1D0
// allocate 0x00395944 (shared 24B fold) _free 0x00030830; capacity check then
// allocate vs allocate_and_copy; prev StlportVectorOverflow0008B503 sibling flags.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <vector>

struct Rva0008DE1CElement
{
    char m_pad[24];

public:
    Rva0008DE1CElement(const Rva0008DE1CElement &that);
};

// The element copy-construct is retail's guarded copy through the 0x00089822
// copy constructor (0x0008A173, rowed as Rva0008A173Copy); this unit is the
// first in link order to emit _Construct for the element, so spell it so.
struct Rva0073DAB0Blk
{
	int a;
	int b;
	int c;
	char d;
};

class Rva0073DAB0
{
	Rva0073DAB0Blk m;

public:
	Rva0073DAB0 &set(const Rva0073DAB0Blk *p);
};

class Rva00089822
{
public:
	Rva00089822(const Rva00089822 &other) throw();

private:
	int m_00;
	int m_04;
	Rva0073DAB0 m_rva;
};
// Retail __uninitialized_copy calls this 18-byte wrapper out of line.
// Keeping its definition non-inline also preserves the 38-byte copy loop.
namespace _STL
{
template <> void _Construct<Rva0008DE1CElement, Rva0008DE1CElement>(Rva0008DE1CElement *p, const Rva0008DE1CElement &v)
{
	if (p != 0)
		new (p) Rva00089822(reinterpret_cast<const Rva00089822 &>(v));
}
}

template void _STL::vector<Rva0008DE1CElement>::reserve(unsigned int);
