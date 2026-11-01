// cl: /DNDEBUG /DWIN32 /MD /EHsc
// stlport
// ??0Rva002E1F42@@QAE@XZ @0x002E1F21 33B ctor via baseConstruct plus vtable plus vector base.
// Evidence: thiscall ctor storing vtable 0x00804A84 at +0 then vector_base
// 0x00211E58 at +0xC with allocator temp at [esp+7] after baseConstruct
// 0x001B4E63; dtor 0x002E1F42 frees +0xC then base; prev/next share /O1.
#include <vector>
#include "../../../Libraries/Include/Lib/BfmeE16.h"
// bfme link decl-only BfmeE16
namespace _STL { template <> vector<BfmeE16, allocator<BfmeE16> >::~vector(); }
// Suppress this TU's non-retail BfmeE16 proxy deallocate copy (family2-LK3 row 34):
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> void _STLP_alloc_proxy<BfmeE16*, BfmeE16, allocator<BfmeE16> >::deallocate(BfmeE16*, size_t);
}

// _Vector_base<BfmeE16>::~_Vector_base is inline-only in retail; expanded here so this TU emits no copy.
namespace _STL {
template <> __declspec(dllimport) __forceinline
_Vector_base<BfmeE16, allocator<BfmeE16> >::~_Vector_base() {
  if (_M_start != 0)
    _M_end_of_storage.deallocate(_M_start, _M_end_of_storage._M_data - _M_start);
}
}

// 0x001B4E63 is the rowed SubsystemInterface ctor.
#include "../../../Libraries/Source/subsystem/SubsystemInterface.h"

class __declspec(novtable) BFME2NativeNetworkBase
{
public:
	__forceinline BFME2NativeNetworkBase() { reinterpret_cast<SubsystemInterface *>(this)->SubsystemInterface::SubsystemInterface(); }
	virtual ~BFME2NativeNetworkBase();
private:
	char m_flag;
	int m_value;
};

class Rva002E1F42 : public BFME2NativeNetworkBase
{
public:
	~Rva002E1F42();	// rowed out of line; this view must not emit its own
	Rva002E1F42();
private:
	_STL::vector<BfmeE16> m_0c;
};

Rva002E1F42::Rva002E1F42()
{
}
