// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// STLport 4.5.3 single-object _Destroy (stl/_construct.h: __pointer->~_Tp())
// for three element types, retail 0x000BC859, 0x000BC862 and 0x000BC86B
// (9B each): load the pointer argument into ecx and tail-jump to the rowed
// destructor -- ??1Rva000B9AAA@@QAE@XZ (0x000B9AAA), ??1Rva00B9AC2@@QAE@XZ
// (0x000B9AC2) and ??1Rva00079554Record@@QAE@XZ (0x00079554). They sit in
// the STLport list/vector run after 0x000BC834; no direct caller reaches
// them in retail. The element types keep the class keys their other rows use.
#include <memory>

class Rva000B9AAA
{
public:
	~Rva000B9AAA();
};

struct Rva00B9AC2
{
	~Rva00B9AC2();
};

struct Rva00079554Record
{
	~Rva00079554Record();
};

// 0x000C251D / 0x000C2526 (9B each): the same for BfmeVectorRecord000BDF17
// (dtor 0x000BE201) and Rva000BEDF0Record (dtor 0x000BEDF0).
#include <vector>
#include "../../../../GameEngine/Include/Common/BfmeVectorRecord000BDF17.h"

struct Rva000BEDF0Record
{
	~Rva000BEDF0Record();
};

template void _STL::_Destroy<Rva000B9AAA>(Rva000B9AAA *);
template void _STL::_Destroy<BfmeVectorRecord000BDF17>(BfmeVectorRecord000BDF17 *);
template void _STL::_Destroy<Rva000BEDF0Record>(Rva000BEDF0Record *);
template void _STL::_Destroy<Rva00B9AC2>(Rva00B9AC2 *);
template void _STL::_Destroy<Rva00079554Record>(Rva00079554Record *);
