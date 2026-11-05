// cl: /O1 /DNDEBUG /MD /EHsc /G7 /arch:SSE /Ireference/shims/bfme2_ascii /D_STLP_USE_STATIC_LIB
// stlport
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#define _STLP_BFME_COPY_TRIVIAL_EXTERN  // call retail's one __copy_trivial (vendor/stlport/stl/_algobase.h)
#define _STLP_BFME_LOWER_BOUND_EXTERN  // call retail's one __lower_bound<const size_t*> (vendor/stlport/stl/_hashtable.c)
#include <hash_map>
#include <cstddef>
// bfme link decl-only begin
namespace _STL { template <> _Vector_base<void *, allocator<void *> >::_Vector_base(allocator<void *> const &); }
namespace _STL { template <> vector<void *, allocator<void *> >::vector(allocator<void *> const &); }
namespace _STL { template <> _STLP_alloc_proxy<void **, void *, allocator<void *> >::~_STLP_alloc_proxy(); }
namespace _STL { template <> _Vector_base<void *, allocator<void *> >::~_Vector_base(); }
namespace _STL { template <> vector<void *, allocator<void *> >::~vector(); }
namespace _STL { template <> void *& vector<void *, allocator<void *> >::operator[](unsigned int); }
namespace _STL { template <> void vector<void *, allocator<void *> >::_M_clear(); }
namespace _STL { template <> void vector<void *, allocator<void *> >::_M_fill_insert(void **, unsigned int, void *const &); }
namespace _STL { template <> void vector<void *, allocator<void *> >::_M_insert_overflow(void **, void *const &, __true_type const &, unsigned int, bool); }
namespace _STL { template <> void vector<void *, allocator<void *> >::_M_set(void **, void **, void **); }
namespace _STL { template <> void ** allocator<void *>::allocate(unsigned int, void const *) const; }
namespace _STL { template <> unsigned int vector<void *, allocator<void *> >::capacity() const; }
namespace _STL { template <> void vector<void *, allocator<void *> >::insert(void **, unsigned int, void *const &); }
namespace _STL { template <> void vector<void *, allocator<void *> >::reserve(unsigned int); }
namespace _STL { template <> allocator<void *>::~allocator(); }
// bfme link decl-only end
// Suppress this TU's non-retail copy of ?deallocate@?$allocator@U?$_Hashtable_node@U?$pair@$$CBHURva0041EFE0Element@@@_STL@@@_STL@:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva0041EFE0Element;
namespace _STL { template <> void allocator<_Hashtable_node<pair<int const ,Rva0041EFE0Element> > >::deallocate(_Hashtable_node<pair<int const ,Rva0041EFE0Element> > *,unsigned int) const; }
// Keep __node_alloc<true,0>::deallocate inline-only: every call here is inlined,
// and this TU's /O1 COMDAT copy differs from the copy the link keeps.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void _STLP_CALL __node_alloc<true, 0>::deallocate(void *__p, size_t __n)
{ if (__n > (size_t)_MAX_BYTES) __stl_delete(__p); else _M_deallocate(__p, __n); }
}
// map<unsigned> internals otherwise instantiate the less<unsigned>::operator()
// COMDAT (one byte shape per TU flags); an explicit specialization declaration
// suppresses this TU's copy so callers bind retail's instead.
namespace _STL {
template <> bool less<unsigned int>::operator()(const unsigned int &a, const unsigned int &b) const;
// Suppress this TU's non-retail vector<void*> size copy (family2-LK3 row 17):
// the retail copy serves the link. Plain declaration-only form (no __imp_).
template <> size_t vector<void*>::size() const;
template <> void **vector<void*>::begin();
template <> void **vector<void*>::end();
}

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

struct Rva0041EFE0Element
{
public:
	bool operator<(const Rva0041EFE0Element&)const;
	bool operator==(const Rva0041EFE0Element&)const;
	char bytes[1]; // +0x00
};
namespace _STL {template<> struct hash<Rva0041EFE0Element> { unsigned operator()(const Rva0041EFE0Element&) const; };}

// 0x001B4E63 is the rowed SubsystemInterface ctor.
#include "../../../Libraries/Source/subsystem/SubsystemInterface.h"

class __declspec(novtable) BFME2NativeNetworkBase
{
public:
	__forceinline BFME2NativeNetworkBase() { reinterpret_cast<SubsystemInterface *>(this)->SubsystemInterface::SubsystemInterface(); }
	virtual ~BFME2NativeNetworkBase() { _ReadWriteBarrier(); }
private:
	char m_flag;
	int m_value;
};

// ??0Rva0022BD9ASubsystem@@QAE@XZ @0x0041EFFF 67B
// Target evidence: leaf, called by GameEngine::init 0x0022F999 via new;
// calls rowed baseConstruct 0x001B4E63 then two rowed hash_map ctors 0x0041EFE0
// at +0x0C and +0x20; vtable 0x0083AF78 auto; neighbours 0x0041EFE0 0x0041F25E.
// Precedent Rva00222061Ctor Shell-pattern novtable base for EH after baseConstruct.
namespace _STL {
template <> hash_map<int, Rva0041EFE0Element>::hash_map();
typedef pair<const int, Rva0041EFE0Element> SubsystemTableValue;
typedef hashtable<SubsystemTableValue, int, hash<int>,
    _Select1st<SubsystemTableValue>, equal_to<int>,
    allocator<SubsystemTableValue> > SubsystemTable;
template <> void SubsystemTable::clear();
}

class Rva0022BD9ASubsystem : public BFME2NativeNetworkBase
{
public:
	Rva0022BD9ASubsystem();
	virtual ~Rva0022BD9ASubsystem();

private:
	_STL::hash_map<int, Rva0041EFE0Element> m_map0C;
	_STL::hash_map<int, Rva0041EFE0Element> m_map20;
};

Rva0022BD9ASubsystem::Rva0022BD9ASubsystem()
	: m_map0C(),
	  m_map20()
{
}
