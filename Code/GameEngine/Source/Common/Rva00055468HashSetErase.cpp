// cl: /MD /O1 /GX /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// stlport46
//
// hashtable<Rva00051B89Keyed*>::erase(const const_iterator&) @ 0x00054C44 (79B).
// Target evidence: the body calls the 1-arg _M_bkt_num_key at 0x00053EA8,
// which hands &key and the bucket count to 0x00051B89; that helper hashes
// the key as a pointer (null -> 0, else the dword at +8). Callers at
// 0x0005546D 0x000570AC 0x0005B433 0x0005FD3A 0x00060C70 0x000610B9
// 0x000613E5 are unrowed. The row was formerly named as the
// hash_map<NameKeyType, ArmorTemplate> erase, but retail's Armor
// hash_map::erase (0x001E2861) calls the inline-hash copy at 0x000557BB,
// so this is a different, pointer-keyed table. Key, element and functor
// names are placeholders; only the erase shape (trivial element, malloc
// node free, out-of-line 1-arg bucket helper) is target fact. Flags carried
// from the former ArmorHashMapErase.cpp row that byte-matched here.
#include <hash_set>
#include <cstddef>
// bfme link decl-only begin
namespace _STL { template <> void __malloc_alloc<0>::deallocate(void *, unsigned int); }
// bfme link decl-only end
// Suppress this TU's non-retail copy of ?deallocate@?$allocator@U?$_Hashtable_node@PAURva00051B89Keyed@@@_STL@@@_STL@@QBEXPAU?$_Ha:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva00051B89Keyed;
namespace _STL { template <> void allocator<_Hashtable_node<Rva00051B89Keyed *> >::deallocate(_Hashtable_node<Rva00051B89Keyed *> *,unsigned int); }
// Suppress this TU's non-retail vector<void*> operator[] copy (family2-LK3 row 25):
// the retail copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> void *&_STL::vector<void*>::operator[](size_t);
}
// Suppress this TU's non-retail vector<void*> size copy (family2-LK3 row 17):
// the retail copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> size_t vector<void*>::size() const;
template <> void **vector<void*>::begin();
template <> void **vector<void*>::end();
}

struct Rva00051B89Keyed;

struct Rva00051B89Hash
{
	size_t operator()(Rva00051B89Keyed *const &key) const;
};

typedef std::hashtable<
	Rva00051B89Keyed *,
	Rva00051B89Keyed *,
	Rva00051B89Hash,
	std::_Identity<Rva00051B89Keyed *>,
	std::equal_to<Rva00051B89Keyed *>,
	std::allocator<Rva00051B89Keyed *> > Rva00051B89Table;

namespace _STL {
template <> void Rva00051B89Table::erase(const Rva00051B89Table::const_iterator &);
}

// BFME1 f989 Rva006B9AA0RequestDrain.cpp supplies the STLport wrapper
// shape. Target 00055468..00055475 receives the existing pointer-keyed
// table at ECX and its two-word const iterator by value; it calls the
// established 00054C44 erase with &iterator and RET8. Request identity
// from the donor remains unknown in BFME2.
typedef std::hash_set<Rva00051B89Keyed *, Rva00051B89Hash> Rva00051B89Set;
template void Rva00051B89Set::erase(Rva00051B89Set::iterator);
