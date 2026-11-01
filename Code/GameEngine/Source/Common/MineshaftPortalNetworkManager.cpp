// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata /DNDEBUG /MD /GX /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_STLP_USE_MALLOC /D_CRTIMP=
// stlport
//
// ??0MineshaftPortalNetworkManager@@QAE@XZ @0x003733C8 (73B).
// Ctor for MI class MineshaftPortalNetworkManager (primary 0xC via baseConstruct, secondary
// Snapshot at +0xC vtable 0x00BBB554, map<int,void*> at +0x10). Calls rowed
// baseConstruct 0x001B4E63 then rowed map 0x0033C432. Vtables 0x00C17E14/
// 0x00C17E04 via gate. Evidence: vtable stores, callees rowed, dtor rowed
// 0x0037381C, caller 0x0022F8CB.
#include <map>
#include "Common/Snapshot.h"
// bfme link decl-only begin
namespace _STL { template <> _Rb_tree_base<pair<int const, void *>, allocator<pair<int const, void *> > >::_Rb_tree_base(allocator<pair<int const, void *> > const &); }
// bfme link decl-only end

// __malloc_alloc<0> allocate/deallocate otherwise instantiate per-TU
// COMDATs (one byte shape per TU malloc/free wiring); explicit
// dllimport+forceinline specializations take those calls inline so this
// TU emits no external copies.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void *__malloc_alloc<0>::allocate(size_t __n)
{ void *__r = malloc(__n); if (!__r) __r = _S_oom_malloc(__n); return __r; }
template <> __declspec(dllimport) __forceinline
void __malloc_alloc<0>::deallocate(void *__p, size_t)
{ free((char *)__p); }
}

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

// 0x001B4E63 is the rowed SubsystemInterface ctor.
#include "../../../Libraries/Source/subsystem/SubsystemInterface.h"

class __declspec(novtable) Rva003733C8Primary
{
public:
	__forceinline Rva003733C8Primary() { reinterpret_cast<SubsystemInterface *>(this)->SubsystemInterface::SubsystemInterface(); }
	virtual ~Rva003733C8Primary() { _ReadWriteBarrier(); }
private:
	char m_flag;
	int m_value;
};

class MineshaftPortalNetworkManager : public Rva003733C8Primary, public Snapshot
{
public:
	MineshaftPortalNetworkManager();
	virtual ~MineshaftPortalNetworkManager();
private:
	_STL::map<int, void *> m_map;
};

MineshaftPortalNetworkManager::MineshaftPortalNetworkManager()
{
}
