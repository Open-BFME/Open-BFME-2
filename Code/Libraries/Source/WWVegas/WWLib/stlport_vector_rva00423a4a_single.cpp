// cl: /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport

// ??0Rva0042499E@@QAE@I@Z
// retail 0x0042499E, 107 bytes. Honest ctor over a vector<Rva00423A4A> base:
// count-taking _Vector_base at 0x005C8C37, default Rva00423A4A temp at
// ebp-0x1c via empty base 0x00211E58, then the rowed 3-arg
// __uninitialized_fill_n dispatch 0x004246EE. Evidence: chain lane (calls
// 0x004246EE just landed); caller 0x00424CB6 passes n through and builds the
// trailing vector at +0xC; unblocks 0x00424CB6.
#include <vector>

struct BfmeE12 { float x, y, z; };

struct Rva00423A4A
{
	_STL::vector<BfmeE12 *> m_vec;
	Rva00423A4A() {}
	Rva00423A4A(const Rva00423A4A &o);
};

namespace _STL
{
template <class ForwardIter, class Size, class T>
ForwardIter __uninitialized_fill_n(ForwardIter first, Size n, const T &x);
}

struct Rva0042499E : _STL::_Vector_base<Rva00423A4A, _STL::allocator<Rva00423A4A> >
{
	Rva0042499E(unsigned int n);
};

Rva0042499E::Rva0042499E(unsigned int n)
	: _STL::_Vector_base<Rva00423A4A, _STL::allocator<Rva00423A4A> >(n, allocator_type())
{
	this->_M_finish = _STL::__uninitialized_fill_n(this->_M_start, n, Rva00423A4A());
}

// ??0Rva00424CB6@@QAE@I@Z
// retail 0x00424CB6, 33 bytes. Honest ctor with vector<Rva00423A4A> holder at
// +0x00 via rowed 0x0042499E plus vector<BfmeE16> at +0x0C via empty base
// 0x00211E58. Evidence: chain lane (calls 0x0042499E just landed); caller
// 0x004257C6 in 0x004257AD; unblocks 0x004257AD.
struct BfmeE16 { float x, y, z, w; };

struct Rva00424CB6
{
	Rva0042499E m_00;
	_STL::vector<BfmeE16> m_0c;
	Rva00424CB6(unsigned int n);
};

Rva00424CB6::Rva00424CB6(unsigned int n) : m_00(n) {}
