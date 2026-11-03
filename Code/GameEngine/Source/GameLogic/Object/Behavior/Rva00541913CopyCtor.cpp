// cl: /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??0Rva00541913@@QAE@ABV0@@Z @0x00541913 66B. Copy ctor for member-plus-vector holder.
// Evidence: calls rowed Rva00330757Member default ctor 0x00330757 for +0 then rowed vector<Rva00541021> copy ctor 0x00541434 for +0x10 then copies dword +0x1c; caller 0x00541F1F; prev/next are vector bodies.
// Honest Rva name; /O1 for push/mov idioms; /EHsc for vector copy unwind; bfmealloc for vector allocator.
#include <vector>

// The vector element is Rva00541021 (an int then a Region3D; 0x00541434).
struct Rva00541021 {
	int a[7];
};

#include "../../../../../Libraries/Include/Lib/BfmeE16.h"
// bfme link decl-only begin
namespace _STL { template <> vector<Rva00541021, allocator<Rva00541021> >::vector(vector<Rva00541021, allocator<Rva00541021> > const &); }
// bfme link decl-only end
// bfme link decl-only BfmeE16
namespace _STL { template <> vector<BfmeE16, allocator<BfmeE16> >::~vector(); }

#include "../../../../Include/Common/Rva00330757Member.h"

class Rva00541913
{
public:
	Rva00541913(const Rva00541913 &that);
private:
	Rva00330757Member m_00;
	_STL::vector<Rva00541021> m_10;
	int m_1C;
};

Rva00541913::Rva00541913(const Rva00541913 &that)
	: m_10(that.m_10)
	, m_1C(that.m_1C)
{
}
