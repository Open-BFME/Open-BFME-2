// cl: /MD /O1 /GX /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// stlport
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

template void Rva00051B89Table::erase(const Rva00051B89Table::const_iterator &);
