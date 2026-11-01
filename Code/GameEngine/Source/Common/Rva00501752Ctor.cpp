// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??0Rva00501776@@QAE@XZ @0x00501752 36B: ctor constructing vectors at +0x14/+0x20 via rowed Vector_base 0x00211E58; evidence same offsets as dtor 0x00501776 and caller 0x00503A28
#include <vector>

#include "../../../Libraries/Include/Lib/BfmeE16.h"
// bfme link decl-only BfmeE16
namespace _STL { template <> vector<BfmeE16, allocator<BfmeE16> >::~vector(); }

struct Rva00501776
{
	char m_pad[0x14];
	_STL::vector<BfmeE16> m_a;
	_STL::vector<BfmeE16> m_b;
	Rva00501776();
};

Rva00501776::Rva00501776()
{
}
