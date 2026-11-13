// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??1Rva001ED0DE@@QAE@XZ @0x001ED0DE 92B.
// Non-virtual dtor: vector<Rva001EC349> at +0x18, vector<AsciiString> at +0x0C, three strings at +0x08..+0x00.
// Evidence: callees rowed 0x001ECFDF 0x0002CC70 0x00036410(x3); callers 0x001ED26C 0x001ED353 0x001ED5FF.
#include <vector>

#include "ascii_string.h"

// A declaration-only specialization stops this TU emitting its own
// vector<AsciiString> dtor COMDAT, so the call binds the kept copy.
namespace _STL {
template <> vector<AsciiString, allocator<AsciiString> >::~vector();
template <> _Vector_base<AsciiString, allocator<AsciiString> >::~_Vector_base();
template <> void _STLP_alloc_proxy<AsciiString*, AsciiString, allocator<AsciiString> >::deallocate(AsciiString*, size_t);
template <> void allocator<AsciiString>::deallocate(AsciiString*, size_t) const;
}


#include "OpaqueRefCounted.h"

#include "../../../../GameEngine/Include/Common/OpaqueRefElement4.h"

#include "../../../../GameEngine/Include/Common/Rva001EC349.h"

class Rva001ED0DE
{
public:
	~Rva001ED0DE();
private:
	AsciiString m_00;
	AsciiString m_04;
	AsciiString m_08;
	_STL::vector<AsciiString, _STL::allocator<AsciiString> > m_0C;
	_STL::vector<Rva001EC349, _STL::allocator<Rva001EC349> > m_18;
};

// bfme link decl-only begin
namespace _STL { template <> void _Destroy<Rva001EC349 *>(Rva001EC349 *,Rva001EC349 *); }
namespace _STL { template <> void __destroy<Rva001EC349 *,Rva001EC349>(Rva001EC349 *,Rva001EC349 *,Rva001EC349 *); }
namespace _STL { template <> void __destroy_aux<Rva001EC349 *>(Rva001EC349 *,Rva001EC349 *,_STL::__false_type const &); }
namespace _STL { template <> vector<Rva001EC349,_STL::allocator<Rva001EC349> >::~vector(); }
// bfme link decl-only end
Rva001ED0DE::~Rva001ED0DE()
{
}
