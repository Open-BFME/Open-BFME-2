// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /D_CRTIMP= /D_STLP_NO_CSTD_FUNCTION_IMPORTS
// platformsdk
// stlport
// AssetManagerImpl constructor identity: WB167D4F0 names it in its own
// assertion; the complete native624DB0..625034 body and member lifecycle
// independently establish the shared asset-manager layout. Clean BFME1 donor
// 90fffa62857c131831171802121eef7e6604eb58 (unchanged from reviewed ba7ddda7)
// Rva009EB960Ctor.cpp supplies the constructor semantics. Native introduces
// two additional words at +24/+30, shifting locks/queues/groups by eight.
// Hash-map and deque element spellings are constructor storage ABI views;
// native initialization and matched siblings prove those helpers, not original
// application element names. Worker vtable retains its established opaque owner.

#define _STLP_USE_STATIC_LIB 1

// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#define _STLP_BFME_LOWER_BOUND_EXTERN  // call retail's one __lower_bound<const size_t*> (vendor/stlport/stl/_hashtable.c)
#pragma push_macro("_CRTIMP")
#undef _CRTIMP
#define _CRTIMP __declspec(dllimport)
#include <process.h>
#pragma pop_macro("_CRTIMP")
#include <deque>
#include <hash_map>
#include <new>
#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <set>
#include <string.h>
#include <windows.h>
#include <cstddef>
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> __declspec(dllimport) __forceinline allocator<void *>::~allocator() {} }
// bfme link decl-only begin
namespace _STL { template <> _STLP_alloc_proxy<void **, void *, allocator<void *> >::~_STLP_alloc_proxy(); }
namespace _STL { template <> _Vector_base<void *, allocator<void *> >::~_Vector_base(); }
namespace _STL { template <> vector<void *, allocator<void *> >::~vector(); }
namespace _STL { template <> void vector<void *, allocator<void *> >::_M_clear(); }
namespace _STL { template <> void vector<void *, allocator<void *> >::_M_fill_insert(void **, unsigned int, void *const &); }
namespace _STL { template <> void vector<void *, allocator<void *> >::_M_insert_overflow(void **, void *const &, __true_type const &, unsigned int, bool); }
namespace _STL { template <> void ** allocator<void *>::allocate(unsigned int, void const *) const; }
namespace _STL { template <> unsigned int vector<void *, allocator<void *> >::capacity() const; }
namespace _STL { template <> void vector<void *, allocator<void *> >::insert(void **, unsigned int, void *const &); }
namespace _STL { template <> void vector<void *, allocator<void *> >::reserve(unsigned int); }
// bfme link decl-only end
// Suppress this TU's non-retail copy of ?begin@?$hashtable@U?$pair@$$CBHH@_STL@@HU?$hash@H@2@U?$_Select1st@U?$pair@$$CBHH@_STL@@@2:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> _Ht_iterator<pair<int const ,int>,_Nonconst_traits<pair<int const ,int> >,int,hash<int>,_Select1st<pair<int const ,int> >,equal_to<int>,allocator<pair<int const ,int> > > hashtable<pair<int const ,int>,int,hash<int>,_Select1st<pair<int const ,int> >,equal_to<int>,allocator<pair<int const ,int> > >::begin(); }
// Suppress this TU's non-retail copy of ??1?$_Deque_base@HV?$allocator@H@_STL@@@_STL@@QAE@XZ:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> _Deque_base<int,allocator<int> >::~_Deque_base(); }
// Suppress this TU's non-retail copy of ?deallocate@?$allocator@H@_STL@@QBEXPAHI@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> void allocator<int>::deallocate(int *,unsigned int) const; }
// Suppress this TU's non-retail copy of ??1?$deque@HV?$allocator@H@_STL@@@_STL@@QAE@XZ:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> deque<int,allocator<int> >::~deque(); }
// Suppress this TU's non-retail copy of ?_M_create_nodes@?$_Deque_base@HV?$allocator@H@_STL@@@_STL@@IAEXPAPAH0@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> void _Deque_base<int,allocator<int> >::_M_create_nodes(int * *,int * *); }
// Suppress this TU's non-retail copy of ??1?$_Rb_tree_base@PAURva001408C0Target@@V?$allocator@PAURva001408C0Target@@@_STL@@@_STL@@:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva001408C0Target;
namespace _STL { template <> _Rb_tree_base<Rva001408C0Target *,allocator<Rva001408C0Target *> >::~_Rb_tree_base(); }
// Suppress this TU's non-retail copy of ?deallocate@?$allocator@U?$_Rb_tree_node@PAURva001408C0Target@@@_STL@@@_STL@@QBEXPAU?$_Rb_:
// the kept copy serves the link. Plain declaration-only form (no __imp_).

namespace _STL { template <> void allocator<_Rb_tree_node<Rva001408C0Target *> >::deallocate(_Rb_tree_node<Rva001408C0Target *> *,unsigned int) const; }
// Suppress this TU's non-retail copy of ??1?$hashtable@U?$pair@$$CBHH@_STL@@HU?$hash@H@2@U?$_Select1st@U?$pair@$$CBHH@_STL@@@2@U?$:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> hashtable<pair<const int, int>, int, hash<int>, _Select1st<pair<const int, int> >, equal_to<int>, allocator<pair<const int, int> > >::~hashtable(); }
// Suppress this TU's non-retail copy of ?_M_initialize_buckets@?$hashtable@U?$pair@$$CBHH@_STL@@HU?$hash@H@2@U?$_Select1st@U?$pair:
// the kept copy serves the link. Plain declaration-only form (no __imp_).

namespace _STL { template <> void hashtable<pair<const int, int>, int, hash<int>, _Select1st<pair<const int, int> >, equal_to<int>, allocator<pair<const int, int> > >::_M_initialize_buckets(size_t); }
// Suppress this TU's non-retail copy of ?clear@?$hashtable@U?$pair@$$CBHH@_STL@@HU?$hash@H@2@U?$_Select1st@U?$pair@$$CBHH@_STL@@@2:
// the kept copy serves the link. Plain declaration-only form (no __imp_).

namespace _STL { template <> void hashtable<pair<const int, int>, int, hash<int>, _Select1st<pair<const int, int> >, equal_to<int>, allocator<pair<const int, int> > >::clear(); }
// Suppress this TU's non-retail copy of ??1?$_Rb_tree@PAURva001408C0Target@@PAU1@U?$_Identity@PAURva001408C0Target@@@_STL@@U?$less:
// the kept copy serves the link. Plain declaration-only form (no __imp_).

namespace _STL { template <> _Rb_tree<Rva001408C0Target *, Rva001408C0Target *, _Identity<Rva001408C0Target *>, less<Rva001408C0Target *>, allocator<Rva001408C0Target *> >::~_Rb_tree(); }
// Suppress this TU's non-retail vector<void*> operator[] copy (family2-LK3 row 25):
// the retail copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> void *&_STL::vector<void*>::operator[](size_t);
}
// Suppress this TU's non-retail vector<void*> begin/end copies (family2-LK3 rows 6/9):
// the retail copies serve the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> void **vector<void*>::begin();
template <> void **vector<void*>::end();
}
// Suppress this TU's non-retail vector<void*> size copy (family2-LK3 row 17):
// the retail copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> size_t vector<void*>::size() const;
}

#pragma intrinsic(memset)


typedef Rva001408C0Target *Rva001408C0Key;
typedef _STL::set<Rva001408C0Key> Rva001408C0Set;
namespace _STL {
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

struct Q1ReceiverLocalSet
{
	Rva001408C0Set m_tree;
	volatile unsigned int m_count;
	volatile bool m_active;
	unsigned char m_padding[3];

	__forceinline Q1ReceiverLocalSet() { clear(); }

	void clear()
	{
		m_count = 0;
		m_active = true;
	}
};

class Rva009EEA70CleanupDeleting
{
public:
	Rva009EEA70CleanupDeleting() : m_last(1)
	{
		for (unsigned int i = 0; i < 0xafcf; ++i)
			m_data[i] = 0;
	}

	virtual ~Rva009EEA70CleanupDeleting();

	unsigned int m_data[0xafcf];
	unsigned int m_last;
};

class AssetManagerImpl;
class Q1Receiver0134FAAC;
extern Q1Receiver0134FAAC *TheQ1Receiver;
extern void __cdecl Rva00622670ThreadProc(void *);

typedef _STL::hash_map<int, int> GenHashMap1470;
typedef _STL::hash_map<int, int> GenHashMap14C0;
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
	GenHashMap1470 m_map0c;
	unsigned int m_field20;
	unsigned int m_reserved24;
	unsigned int m_field28;
	unsigned int m_field2c;
	unsigned int m_reserved30;
	CRITICAL_SECTION m_lock34;
	GenHashMap14C0 m_map4c;
	GenHashMap14C0::iterator m_iterator60;
	CRITICAL_SECTION m_lock68;
	GenDeque m_deques80[7];
	Q1ReceiverLocalSet m_set198;
	Q1ReceiverLocalSet m_set1ac;
	Q1ReceiverLocalSet m_set1c0;
	Q1ReceiverLocalSet m_set1d4;
	unsigned int m_field1e8;
	unsigned int m_field1ec;
	unsigned char m_pad1f0[4];
	bool m_flag1f4;
	bool m_flag1f5;
	bool m_flag1f6;
	unsigned char m_pad1f7;
	Rva009EEA70CleanupDeleting *m_hashContext;
};

typedef char GenDtorSizeCheck[sizeof(AssetManagerImpl) == 0x1fc ? 1 : -1];
typedef char RegistryWorkerSizeCheck[sizeof(Rva009EEA70CleanupDeleting) == 0x2bf44 ? 1 : -1];

AssetManagerImpl::AssetManagerImpl()
	: m_active(false),
	  m_map0c(100),
	  m_field20(0),
	  m_reserved24(0),
	  m_field28(0x10000000),
	  m_field2c(0),
	  m_reserved30(0),
	  m_map4c(100)
{
	m_field1e8 = 0;
	m_field1ec = 0;
	m_flag1f4 = true;
	m_flag1f5 = true;
	m_flag1f6 = false;

	m_iterator60 = m_map4c.begin();

	void *workerMemory = ::operator new(0x2bf44);
	Rva009EEA70CleanupDeleting *worker;
	if (workerMemory != 0)
	{
		worker = new (workerMemory) Rva009EEA70CleanupDeleting;
	}
	else
	{
		worker = 0;
	}
	m_hashContext = worker;

	InitializeCriticalSection(&m_lock34);
	InitializeCriticalSection(&m_lock68);
	TheQ1Receiver = (Q1Receiver0134FAAC *)this;
	m_thread = _beginthread(Rva00622670ThreadProc, 0, this);
	Sleep(1);
}
