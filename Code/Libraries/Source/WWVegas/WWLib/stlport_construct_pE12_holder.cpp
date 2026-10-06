// cl: /Ob2 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??$_Construct@URva00423A4A@@U1@@_STL@@YAXPAURva00423A4A@@ABU1@@Z retail 0x00423E83 45B
// _STL::_Construct<Rva00423A4A,Rva00423A4A> null-guarded placement-new copy
// over a single 12-byte holder element via the twin-pinned copy ctor at
// 0x00423A4A. Evidence: chain lane (calls 0x00423A4A just landed) plus
// uninit-copy 0x00423ED1 and fill-n 0x0042449C loops stepping 0xC.
#include <memory>
#include <vector>

struct BfmeE12 { float x, y, z; };

struct Rva00423A4A
{
	_STL::vector<BfmeE12 *> m_vec;
	Rva00423A4A(const Rva00423A4A &o);
};

template void _STL::_Construct<Rva00423A4A, Rva00423A4A>(Rva00423A4A *, const Rva00423A4A &);
