// cl: /Ob2 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
//
// ??0Rva002B72C9@@QAE@ABU0@@Z retail 0x002B72C9 35B
// Evidence: two POD dwords plus vector<unsigned> at +8; vector copy via rowed 0x002CFAB9
// caller 0x002B8242 in 0x002B8226 operates on same 20-byte stride; imul 0x14 in 0x002BC3C6
// same 35B copy shape as BfmeVectorRecord family; class identity unproven so honest Rva name.
#include <vector>

struct Rva002B72C9
{
	unsigned int word0;
	unsigned int word4;
	_STL::vector<unsigned int> values08;
	Rva002B72C9(const Rva002B72C9 &o);
};

Rva002B72C9::Rva002B72C9(const Rva002B72C9 &o) : word0(o.word0), word4(o.word4), values08(o.values08)
{
}
