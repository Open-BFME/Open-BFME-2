// cl: /EHsc /DNDEBUG /MD /D_STLP_USE_STATIC_LIB C:/Program Files/Git/ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// stlport
// ??0PSThreadClass@@QAE@PAX@Z @0x0055436A 79B
// Thread-subclass ctor: ThreadClass(0) base plus int-pointer map at +0x5C
// plus arg store at +0x68 and zero bytes/dword at +0x50 +0x51 +0x54 +0x58.
// Evidence: new(0x6C) plus lea +0x9C push at caller 0x0055443F; rowed
// ThreadClass ctor 0x00610430 map ctor 0x0033C432; vtable 0x0086B0D0;
// size 0x6C matches allocation.
#include <map>
// bfme link decl-only begin
namespace _STL { template <> _Rb_tree_base<pair<int const, void *>, allocator<pair<int const, void *> > >::_Rb_tree_base(allocator<pair<int const, void *> > const &); }
namespace _STL { template <> _Rb_tree<int, pair<int const, void *>, _Select1st<pair<int const, void *> >, less<int>, allocator<pair<int const, void *> > >::~_Rb_tree(); }
namespace _STL { template <> void _Rb_tree<int, pair<int const, void *>, _Select1st<pair<int const, void *> >, less<int>, allocator<pair<int const, void *> > >::_M_erase(_Rb_tree_node<pair<int const, void *> > *); }
// bfme link decl-only end
// Suppress this TU's non-retail copy of ??1?$_Rb_tree_base@U?$pair@$$CBHPAX@_STL@@V?$allocator@U?$pair@$$CBHPAX@_STL@@@2@@_STL@@QA:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> _Rb_tree_base<pair<int const ,void *>,allocator<pair<int const ,void *> > >::~_Rb_tree_base(); }
// Suppress this TU's non-retail copy of ?deallocate@?$allocator@U?$_Rb_tree_node@U?$pair@$$CBHPAX@_STL@@@_STL@@@_STL@@QBEXPAU?$_Rb:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> void allocator<_Rb_tree_node<pair<int const ,void *> > >::deallocate(_Rb_tree_node<pair<int const ,void *> > *,unsigned int) const; }
// Keep __node_alloc<true,0>::deallocate inline-only: every call here is inlined,
// and this TU's /O1 COMDAT copy differs from the copy the link keeps.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void _STLP_CALL __node_alloc<true, 0>::deallocate(void *__p, size_t __n)
{ if (__n > (size_t)_MAX_BYTES) __stl_delete(__p); else _M_deallocate(__p, __n); }
}
#include "../../../Libraries/Source/WWVegas/WWLib/ThreadClass.h"
// Pointer-map storage retains this unit's verified ABI view; payload type is provisional.
class PSThreadClass : public ThreadClass
{
public:
	PSThreadClass(void *arg);
	virtual ~PSThreadClass(); // Native owner: PersistentStorageThread.cpp, RVA 0x0055405A.
protected:
	virtual void Thread_Function(); // Native slot 2: RVA 0x005580FB.
private:
	bool m_50;
	bool m_51;
	int m_54;
	bool m_58;
	_STL::map<int, void *> m_5C;
	void *m_68;
};
PSThreadClass::PSThreadClass(void *arg) : ThreadClass(0)
{
	m_68 = arg;
	m_51 = false;
	m_58 = false;
	m_50 = false;
	m_54 = 0;
}
