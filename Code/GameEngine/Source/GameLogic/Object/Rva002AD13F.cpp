// cl: /MD /GX /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// stlport
//
// ?rva002AD13F@Rva002AD13F@@QAE_NPAVRva002AD13FKeySource@@@Z @0x002AD13F 95B
// Target evidence: reads a table pointer at this+0x330 and returns false when
// its element count is zero. A null input clears the table and returns true;
// otherwise it reads a NameKeyType at input+0x54, finds that key, erases the
// iterator when present, and returns whether it removed an entry.
// Structural inference: the clear, key-only find, and iterator erase calls
// resolve to the existing ArmorTemplate hash_map bodies at 0x001DBCDC,
// 0x002888D4, and 0x001E2861. The container's mapped type and both owner
// identities remain inferred; ArmorTemplate supplies the established compiler
// spelling for those shared helpers.

#include <hash_map>
#include <cstddef>
// bfme link decl-only begin
namespace _STL { template <> void __malloc_alloc<0>::deallocate(void *, unsigned int); }
// bfme link decl-only end
// Suppress this TU's non-retail copy of ?deallocate@?$allocator@U?$_Hashtable_node@U?$pair@$$CBW4NameKeyType@@VArmorTemplate@@@_ST:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
enum NameKeyType; class ArmorTemplate;
namespace _STL { template <> void allocator<_Hashtable_node<pair<NameKeyType const ,ArmorTemplate> > >::deallocate(_Hashtable_node<pair<NameKeyType const ,ArmorTemplate> > *,unsigned int) const; }
// Keep const begin out of line and inline STLport's const bucket access.
namespace _STL { template <> vector<void *>::const_iterator _STL::vector<void *>::begin() const; }
namespace _STL { template <> __declspec(dllimport) __forceinline void *const &vector<void *>::operator[](size_t n) const { return *(begin() + n); } }
// Suppress this TU's non-retail vector<void*> operator[] copy (family2-LK3 row 25):
// the retail copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> void *&_STL::vector<void*>::operator[](size_t);
}
// Suppress this TU's non-retail vector<void*> size copy (family2-LK3 row 17):
// the retail copy serves the link. Plain declaration-only form (no __imp_).
// Suppress the TU's non-retail const-begin copy (row 47 family2-LK3): the
// /Od retail copy in stlport_vector_voidptr.cpp serves the link instead.
namespace _STL {
template <> size_t vector<void*>::size() const;
template <> void **vector<void*>::begin();
template <> void **vector<void*>::end();
}

enum NameKeyType
{
	NAMEKEY_INVALID = 0,
	NAMEKEY_MAX = 1 << 23,
	FORCE_NAMEKEYTYPE_LONG = 0x7fffffff
};

namespace rts
{
template <typename T> struct hash
{
	size_t operator()(const T &value) const { return (size_t)value; }
};
}

#include "../../../Include/GameLogic/Armor.h"

typedef std::hash_map<NameKeyType, ArmorTemplate, rts::hash<NameKeyType>,
	std::equal_to<NameKeyType> > Rva002AD13FKeyTable;

// Use the existing clear and erase instantiations for this table type.
namespace _STL {
typedef hashtable<pair<const NameKeyType, ArmorTemplate>, NameKeyType,
    rts::hash<NameKeyType>, _Select1st<pair<const NameKeyType, ArmorTemplate> >,
    equal_to<NameKeyType>, allocator<pair<const NameKeyType, ArmorTemplate> > > ArmorTable;
template <> void ArmorTable::clear();
template <> void ArmorTable::erase(const const_iterator &);
}

class Rva002AD13FKeyTableHolder
{
	int m_prefix;

public:
	Rva002AD13FKeyTable m_keyTable;
};

class Rva002AD13FKeySource
{
	char m_pad[0x54];

public:
	NameKeyType m_key;
};

class Rva002AD13F
{
	char m_pad[0x330];
	Rva002AD13FKeyTableHolder *m_keyTable;

public:
	bool rva002AD13F(Rva002AD13FKeySource *keySource);
};

bool Rva002AD13F::rva002AD13F(Rva002AD13FKeySource *keySource)
{
	if (m_keyTable->m_keyTable.size() == 0)
		return false;

	if (keySource == 0)
	{
		m_keyTable->m_keyTable.clear();
		return true;
	}

	NameKeyType key = keySource->m_key;
	Rva002AD13FKeyTable::iterator found = m_keyTable->m_keyTable.find(key);
	if (found != m_keyTable->m_keyTable.end())
	{
		m_keyTable->m_keyTable.erase(found);
		return true;
	}
	return false;
}
