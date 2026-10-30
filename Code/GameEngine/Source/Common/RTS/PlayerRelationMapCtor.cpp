// cl: /O1 /arch:SSE /G7 /MD /EHsc /DNDEBUG /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc /Ireference/shims/moduledata
// stlport
// ??0PlayerRelationMap@@QAE@XZ @0x002AF6F7 50B.
// Target evidence: Team::Team (0x003A39A7) news a 0x18-byte block and runs
// this body on it, storing the result at Team+0x11C next to the rowed
// TeamRelationMap ctor 0x003A3959 (+0x118); the body arms EH state 0 for an
// unwindable base, stores vtable 0x00BFDD90 and constructs the rowed
// hash_map<int, Rva002AF438Element> at +4 (0x002AF625). Donor: ZH Player.h
// PlayerRelationMap (Snapshot-derived relation map; BFME2 keys a hash_map).
// The class name is carried from the donor; the element type stays address-named.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#define _STLP_BFME_LOWER_BOUND_EXTERN  // call retail's one __lower_bound<const size_t*> (vendor/stlport/stl/_hashtable.c)
#include <hash_map>
#include <cstddef>
// map<unsigned> internals otherwise instantiate the less<unsigned>::operator()
// COMDAT (one byte shape per TU flags); an explicit specialization declaration
// suppresses this TU's copy so callers bind retail's instead.
namespace _STL {
template <> bool less<unsigned int>::operator()(const unsigned int &a, const unsigned int &b) const;
// Suppress this TU's non-retail vector<void*> size copy (family2-LK3 row 17):
// the retail copy serves the link. Plain declaration-only form (no __imp_).
template <> size_t vector<void*>::size() const;
template <> void **vector<void*>::begin();
}
#define BFME_SNAPSHOT_NAME_SLOT
#include "Common/Snapshot.h"
// bfme link decl-only begin
namespace _STL { template <> _STLP_alloc_proxy<void **, void *, allocator<void *> >::~_STLP_alloc_proxy(); }
namespace _STL { template <> _Vector_base<void *, allocator<void *> >::~_Vector_base(); }
namespace _STL { template <> vector<void *, allocator<void *> >::~vector(); }
namespace _STL { template <> void *& vector<void *, allocator<void *> >::operator[](unsigned int); }
namespace _STL { template <> void vector<void *, allocator<void *> >::_M_clear(); }
namespace _STL { template <> void vector<void *, allocator<void *> >::_M_fill_insert(void **, unsigned int, void *const &); }
namespace _STL {
// end() and the fill insert(pos, n, x) are taken inline, as retail's
// hashtable::_M_initialize_buckets does (59 bytes: it reads _M_finish and
// calls the rowed _M_fill_insert); dllimport + forceinline emits no copy.
template <> __declspec(dllimport) __forceinline void **vector<void*>::end()
{ return _M_finish; }
template <> __declspec(dllimport) __forceinline void vector<void*>::insert(void **pos, size_t n, void *const &x)
{ _M_fill_insert(pos, n, x); }
}
namespace _STL { template <> void vector<void *, allocator<void *> >::_M_insert_overflow(void **, void *const &, __true_type const &, unsigned int, bool); }
namespace _STL { template <> void vector<void *, allocator<void *> >::_M_set(void **, void **, void **); }
namespace _STL { template <> void ** allocator<void *>::allocate(unsigned int, void const *) const; }
namespace _STL { template <> unsigned int vector<void *, allocator<void *> >::capacity() const; }
namespace _STL { template <> void vector<void *, allocator<void *> >::reserve(unsigned int); }
// bfme link decl-only end

struct Rva002AF438Element {Rva002AF438Element();Rva002AF438Element(const Rva002AF438Element&);Rva002AF438Element&operator=(const Rva002AF438Element&);~Rva002AF438Element(){}char bytes[8]; bool operator==(const Rva002AF438Element&)const;};

class PlayerRelationMap : public Snapshot
{
public:
	PlayerRelationMap();
protected:
	virtual ~PlayerRelationMap();
public:
protected:
	virtual void loadPostProcess();
	virtual const char *GetSnapshotName() const;
	virtual void xfer(Xfer *xfer);
private:
	_STL::hash_map<int, Rva002AF438Element> m_map;
};

PlayerRelationMap::PlayerRelationMap()
{
}
