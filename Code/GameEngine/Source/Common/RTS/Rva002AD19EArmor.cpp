// cl: /MD /GX /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// stlport
// ?rva002AD19E@Rva002AD19E@@QAE_NPAX@Z @0x002AD19E 95B.
// Armor-map remove-or-clear returning bool. Evidence: unlock lane, callees
// clear/_M_find/erase for hash_map<NameKeyType ArmorTemplate> are rowed in
// Armor.cpp, +0x334 store with map at +4 size at +0x14, arg+0x34 key,
// neighbours PlayerGetRelationship/PlayerO1Shard share Player RTS shard.
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
	NK_Zero = 0
};
#include "../../../Include/GameLogic/Armor.h"
namespace rts
{
	template<class T> struct hash
	{
		unsigned int operator()(const T &x) const { return (unsigned int)x; }	// Zero Hour's rts::hash<NameKeyType>, inline
	};
}
typedef std::hash_map<NameKeyType, ArmorTemplate, rts::hash<NameKeyType>, std::equal_to<NameKeyType> > ArmorTemplateMap;
// Use the existing clear and erase instantiations for this table type.
namespace _STL {
typedef hashtable<pair<const NameKeyType, ArmorTemplate>, NameKeyType,
    rts::hash<NameKeyType>, _Select1st<pair<const NameKeyType, ArmorTemplate> >,
    equal_to<NameKeyType>, allocator<pair<const NameKeyType, ArmorTemplate> > > ArmorTable;
template <> void ArmorTable::clear();
template <> void ArmorTable::erase(const const_iterator &);
}

struct Rva002AD19EStore
{
	void *m_vtbl;
	ArmorTemplateMap m_map;
};
struct Rva002AD19EKey
{
	char _pad[52];
	NameKeyType m_key;
};
class Rva002AD19E
{
	char _pad[820];
public:
	bool rva002AD19E(void *arg);
	Rva002AD19EStore *m_store;
};
bool Rva002AD19E::rva002AD19E(void *arg)
{
	if (m_store->m_map.size() == 0)
		return false;
	if (arg == 0) {
		m_store->m_map.clear();
		return true;
	}
	NameKeyType key = ((const Rva002AD19EKey *)arg)->m_key;
	ArmorTemplateMap::iterator it = m_store->m_map.find(key);
	if (it != m_store->m_map.end()) {
		m_store->m_map.erase(it);
		return true;
	}
	return false;
}
