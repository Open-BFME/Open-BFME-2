// cl: /Ireference/shims/bfme2_ascii /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ??0Rva005DE9E3@@QAE@I@Z @0x005DE9C4 31B
// Gap ctor: vtable 0x00876AFC plus vector<Rva005DE5B5> at +4 via rowed 0x005DE870 plus zero at +0x10.
// Evidence: between rows of stlport_vector_rva005de5b5_dtor.cpp; callee rowed 0x005DE870;
// Table C76AFC is owned by the rowed Rva005DE9E3 destructor; callers 0x005DEA09 0x005DEC0C 0x005DEE4B.
#include <vector>
class Rva005DE5B5;
// The vector ctor is rowed at 0x005DE870; this TU only calls it.
namespace _STL { template <> vector<Rva005DE5B5,allocator<Rva005DE5B5> >::vector(unsigned int); template <> _Vector_base<Rva005DE5B5,allocator<Rva005DE5B5> >::~_Vector_base(); template <> vector<Rva005DE5B5,allocator<Rva005DE5B5> >::~vector(); }

#include "Rva005DE5B5.h"

class Rva005DE9E3
{
public:
	Rva005DE9E3(unsigned int n);
	virtual ~Rva005DE9E3();
private:
	_STL::vector<Rva005DE5B5, _STL::allocator<Rva005DE5B5> > m_04;
	int m_10;
};

Rva005DE9E3::Rva005DE9E3(unsigned int n)
	: m_04(n)
{
	m_10 = 0;
}
