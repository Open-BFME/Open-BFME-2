// cl: /O2 /G6 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /D_CRTIMP= /D_STLP_NO_CSTD_FUNCTION_IMPORTS /Ireference/shims/sweep
// stlport

// BFME2's base destructor call goes to the rowed 14-byte body at 0x001B4E74
// (??1SubsystemInterface@@UAE@XZ, folded with ??1Snapshot/??1Subsystem-
// Interface pins), so the base is declared under that established name: zero
// new pins for the base call. The member's identity is unrecovered (opaque
// address-derived name on the BFME2 target).
//
// The class is not W3DRenderObjectSnapshot: that class's vftable is
// 0x00BC59F4 (slot 2 returns the string "W3DRenderObjectSnapshot"; see
// W3DGhostObjectScene.cpp). This one's 15-slot vftable 0x00C7C5C0 is
// installed by the ctor at 0x0061EEE0 (subsystem base ctor 0x001B4E63, then
// news a 0x200-byte member into +0x0C) and by this dtor. BFME1 carries the
// same body as the address-derived Rva009EB960 singleton destructor, whose
// member is the asset-registry object; named here after the BFME2 ctor.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Snapshot.h
// Base ctor 0x001B4E63 / dtor 0x001B4E74 by their row names ??0/??1SubsystemInterface (SubsystemInterface.cpp).
#include "../../../../Libraries/Source/subsystem/SubsystemInterface.h"

#define _STLP_USE_STATIC_LIB 1

#include <vector>
// vector<void*> members kept from this unit's link copies, moved beside <vector> so
// they precede every use. Import-inline: these members are inlined at every use here,
// and this unit's out-of-line copies (referenced from .debug$F alone) are not the ones
// the link keeps.
namespace _STL { template <> __declspec(dllimport) __forceinline allocator<void *>::~allocator() {} }
namespace _STL { template <> _STLP_alloc_proxy<void **, void *, allocator<void *> >::~_STLP_alloc_proxy(); }
namespace _STL {
template <> __declspec(dllimport) __forceinline _Vector_base<void *, allocator<void *> >::~_Vector_base() { if (_M_start != 0) _M_end_of_storage.deallocate(_M_start, _M_end_of_storage._M_data - _M_start); }
}
#include <deque>
#include <hash_map>

#include <cstddef>

// vector<void*> begin/end otherwise instantiate per-TU COMDATs (one byte
// shape per TU flags); explicit dllimport+forceinline specializations take
// those calls inline so this TU emits no external copies.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void **vector<void*>::begin()
{ return _M_start; }
template <> __declspec(dllimport) __forceinline
void **vector<void*>::end()
{ return _M_finish; }
template <> __declspec(dllimport) __forceinline
size_t vector<void*>::size() const
{ return size_t(this->_M_finish - this->_M_start); }
template <> __declspec(dllimport) __forceinline
void *&vector<void*>::operator[](size_t __n)
{ return *(begin() + __n); }
}
#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <set>
#include <windows.h>
// Bind to the kept retail copy instead of emitting this unit's own.
// bfme link decl-only begin
// bfme link decl-only end
// Suppress this TU's non-retail copy of ?deallocate@?$allocator@H@_STL@@QBEXPAHI@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> void allocator<int>::deallocate(int *,unsigned int) const; }
// Suppress this TU's non-retail copy of ??1?$_Rb_tree_base@PAURva001408C0Target@@V?$allocator@PAURva001408C0Target@@@_STL@@@_STL@@:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva001408C0Target;
namespace _STL { template <> _Rb_tree_base<Rva001408C0Target *,allocator<Rva001408C0Target *> >::~_Rb_tree_base(); }
// Suppress this TU's non-retail copy of ?deallocate@?$allocator@U?$_Rb_tree_node@PAURva001408C0Target@@@_STL@@@_STL@@QBEXPAU?$_Rb_:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva001408C0Target;
namespace _STL { template <> void allocator<_Rb_tree_node<Rva001408C0Target *> >::deallocate(_Rb_tree_node<Rva001408C0Target *> *,unsigned int) const; }

struct Rva001408C0Target;
typedef Rva001408C0Target *Rva001408C0Key;
typedef _STL::set<Rva001408C0Key> Rva001408C0Set;
namespace _STL {
template <> deque<int, allocator<int> >::~deque();
template <> __declspec(dllimport) __forceinline
_Rb_tree_node<Rva001408C0Target *> *allocator<_Rb_tree_node<Rva001408C0Target *> >::allocate(size_t __n, const void *) const
{ return __n != 0 ? (_Rb_tree_node<Rva001408C0Target *> *)allocator<char>::allocate(__n * sizeof(_Rb_tree_node<Rva001408C0Target *>), 0) : 0; }
template <> __declspec(dllimport) __forceinline
_Rb_tree_node<Rva001408C0Target *> *_STLP_alloc_proxy<_Rb_tree_node<Rva001408C0Target *> *, _Rb_tree_node<Rva001408C0Target *>, allocator<_Rb_tree_node<Rva001408C0Target *> > >::allocate(size_t __n)
{ return __stl_alloc_rebind(static_cast<_Base &>(*this), (_Rb_tree_node<Rva001408C0Target *> *)0).allocate(__n, 0); }
}
// Keep STLport's pointer-set construction inline without competing external copies.
namespace _STL {
typedef _Rb_tree<Rva001408C0Key, Rva001408C0Key, _Identity<Rva001408C0Key>,
    less<Rva001408C0Key>, allocator<Rva001408C0Key> > AssetPointerLinkTree;
template <> __declspec(dllimport) __declspec(nothrow) __forceinline
_STLP_alloc_proxy<_Rb_tree_node<Rva001408C0Key> *, _Rb_tree_node<Rva001408C0Key>, allocator<_Rb_tree_node<Rva001408C0Key> > >::_STLP_alloc_proxy(
    const allocator<_Rb_tree_node<Rva001408C0Key> > &__a, _Rb_tree_node<Rva001408C0Key> *__p)
    : allocator<_Rb_tree_node<Rva001408C0Key> >(__a), _M_data(__p) {}
template <> __declspec(dllimport) __forceinline
_Rb_tree_base<Rva001408C0Key, allocator<Rva001408C0Key> >::_Rb_tree_base(const allocator_type &__a)
    : _M_header(_STLP_CONVERT_ALLOCATOR(__a, _Node), (_Node *)0)
{ _M_header._M_data = _M_header.allocate(1); }
// ?AssetPointerLinkTree::_M_empty_initialize present-unmatched
template <> __declspec(dllimport) __declspec(nothrow) __forceinline
void AssetPointerLinkTree::_M_empty_initialize()
{
    _S_color(this->_M_header._M_data) = _S_rb_tree_red;
    _M_root() = 0;
    _M_leftmost() = this->_M_header._M_data;
    _M_rightmost() = this->_M_header._M_data;
}
// ?AssetPointerLinkTree::_Rb_tree present-unmatched
template <> __declspec(dllimport) __forceinline
AssetPointerLinkTree::_Rb_tree(const less<Rva001408C0Key> &__comp, const allocator_type &__a)
    : _Rb_tree_base<Rva001408C0Key, allocator<Rva001408C0Key> >(__a),
      _M_node_count(0), _M_key_compare(__comp)
{ _M_empty_initialize(); }
}
namespace _STL {
template <> __declspec(dllimport) __forceinline
set<Rva001408C0Key>::set() : _M_t(less<Rva001408C0Key>(), allocator<Rva001408C0Key>()) {}
}

class BfmeThingBVA
{
public:
	__forceinline BfmeThingBVA()
	{
		m_value = 0;
		m_active = true;
	}

	BfmeThingBVA &operator=(BfmeThingBVA &other)
	{
		if (this != &other)
		{
			bfmeStepBVA(&other);
			m_active = true;
			m_value = other.m_value;
		}
		return *this;
	}

	void bfmeStepBVA(BfmeThingBVA *other);

	Rva001408C0Set m_tree;
	unsigned int m_value;
	bool m_active;
};

// The shared release leaf 0x009EB7A0 decrements the low word at +4 and, once
// it reaches zero with bit 24 set, dispatches through the vtable at +0.
class Rva009EB7A0RefOwner
{
public:
	void Release_Ref();

	void *m_vtable;
	unsigned int m_refs : 16;
	unsigned int m_bits16 : 8;
	unsigned int m_deleteOnRelease : 1;
	unsigned int m_bits25 : 7;
};

struct Gen_t_009ee630_p12cd
{
	int a[3];
};

struct Gen_t_009ee750_p12cd
{
	Rva009EB7A0RefOwner *m_object;
	int m_unmodelled[2];
};

struct Gen_t_009edfe0_p12cd
{
	int a[3];
};

class Rva009EEA70CleanupDeleting
{
public:
	virtual ~Rva009EEA70CleanupDeleting();
};

class AssetManagerImpl;
class AssetRegistry;
class Q1Receiver0134FAAC;
extern Q1Receiver0134FAAC *TheQ1Receiver;

class Q1Receiver0134FAAC
{
public:
	void m009F0E50(int value);
	void m009F19E0(int value);
};

class Rva00624130
{
public:
	void rva00624130();
};

typedef _STL::hash_map<int, int> GenHashMap0C;
typedef _STL::hash_map<int, int> GenHashMap44;
typedef _STL::deque<int> GenDeque;

class AssetManagerImpl
{
public:
	AssetManagerImpl();
	~AssetManagerImpl();

private:
	uintptr_t m_thread;
	void *m_unknown04;
	bool m_active;
	unsigned char m_pad09[3];
	GenHashMap0C m_map0c;
	__int64 m_budget20;
	__int64 m_limit28;
	unsigned int m_reserved30;
	CRITICAL_SECTION m_lock34;
	GenHashMap44 m_map4c;
	GenHashMap44::iterator m_iterator60;
	CRITICAL_SECTION m_lock68;
	GenDeque m_deques80[7];
	BfmeThingBVA m_set198;
	BfmeThingBVA m_set1ac;
	BfmeThingBVA m_set1c0;
	BfmeThingBVA m_set1d4;
	unsigned int m_field1e8;
	unsigned int m_field1ec;
	unsigned char m_pad1f0[4];
	bool m_flag1f4;
	bool m_flag1f5;
	bool m_flag1f6;
	unsigned char m_pad1f7;
	Rva009EEA70CleanupDeleting *m_hashContext;
};

typedef char GenDtorSizeCheck[sizeof(AssetManagerImpl) == 0x200 ? 1 : -1];

class Rva0061EEE0 : public SubsystemInterface
{
public:
	Rva0061EEE0();
	virtual ~Rva0061EEE0();

private:
	AssetManagerImpl *m_renderObject;
};

Rva0061EEE0::~Rva0061EEE0()
{
	delete m_renderObject;
}

// Clean BFME1 donor 9cbfb551fe20dae985f91f2319d8997287b6a705:
// game/Libraries/Source/assetmanager/Gen_dtor_009eb9e0_Destructor.cpp.
// WB 0x0167D7F0 self-assertion names AssetManagerImpl::~AssetManagerImpl;
// native constructor 0x00624DB0 and the 0x200-byte allocation establish layout.
// Native fields at +20/+24 and +28/+2C are wider than the donor, shifting
// later members by eight. Container int spellings are verified storage views.
// Native RET at 0x006252C8 closes the 649-byte body (the old 646-byte
// inventory truncates its add-esp/RET). Global delete uses worker vslot flag 0
// followed by operator delete; /EHs preserves both hash-map cleanup states.
AssetManagerImpl::~AssetManagerImpl()
{
	Q1Receiver0134FAAC *receiver = (Q1Receiver0134FAAC *)this;

	{
		BfmeThingBVA empty;
		m_set1c0 = empty;
	}
	receiver->m009F0E50((int)&m_set1c0);
	receiver->m009F19E0((int)&m_set1c0);

	m_limit28 = 0;
	for (;;)
	{
		int i;
		for (i = 0; i < 7; ++i)
		{
			if (!m_deques80[i].empty())
				break;
		}
		if (i >= 7)
			break;
		receiver->m009F19E0((int)&m_set1c0);
		((Rva00624130 *)this)->rva00624130();
		Sleep(1);
	}

	TheQ1Receiver = 0;
	m_active = true;
	WaitForSingleObject((HANDLE)m_thread, INFINITE);

	for (GenHashMap44::iterator it = m_map4c.begin(); it != m_map4c.end(); ++it)
	{
		((Rva009EB7A0RefOwner *)it->second)->m_deleteOnRelease = 1;
		((Rva009EB7A0RefOwner *)it->second)->Release_Ref();
	}
	m_map4c.clear();

	::delete m_hashContext;
	DeleteCriticalSection(&m_lock34);
	DeleteCriticalSection(&m_lock68);
}

// Native 0x0061EEE0..0x0061EF5F: base construction has an unwind state,
// which requires saving this as well as the new-expression allocation.
Rva0061EEE0::Rva0061EEE0()
{
	m_renderObject = new AssetManagerImpl;
}
