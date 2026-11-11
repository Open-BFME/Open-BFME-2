// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva002BFA12@Rva002BFA12@@QAEXPAX@Z @0x002BFA12 54B
// Insert-if-absent: hashtable _M_find 0x002888D4 on map at +0x98 with key from arg+0x24,
// on miss ObjectLookupMap::findSlot 0x0041F4E5 on same address then store arg.
// Evidence: retail calls both on ecx+0x98 with same key pointer; caller 0x00539411 passes
// global at 0x00DFEF18 as this and object with key at +0x24; ArmorTemplateMap typedef
// mirrors Rva0035516CArmorFind.cpp so find inlines to rowed _M_find.
#include <hash_map>
#include <vector>
#include <cstddef>
// Suppress this TU's non-retail vector<void*> size copy (family2-LK3 row 17):
// the retail copy serves the link. Plain declaration-only form (no __imp_).
// Suppress the TU's non-retail const-begin copy (row 47 family2-LK3): the
// /Od retail copy in stlport_vector_voidptr.cpp serves the link instead.
namespace _STL {
template <> vector<void *>::const_iterator _STL::vector<void *>::begin() const;
template <> size_t vector<void*>::size() const;
template <> void **vector<void*>::begin();
template <> void **vector<void*>::end();
}
namespace _STL {
template <> __declspec(dllimport) __forceinline
vector<void *>::const_reference vector<void *>::operator[](size_type __n) const { return *(begin() + __n); }
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
	size_t operator()(const T &value) const { return (size_t)value; }	// Zero Hour's rts::hash<NameKeyType>, inline
};

}
// The hash body is inline-only in retail; keep this TU's copy from emitting.
namespace rts
{
template <> __declspec(dllimport) __forceinline
size_t hash<NameKeyType>::operator()(const NameKeyType &value) const { return (size_t)value; }
}


#include "../../Include/GameLogic/Armor.h"

typedef std::hash_map<
	NameKeyType,
	ArmorTemplate,
	rts::hash<NameKeyType>,
	std::equal_to<NameKeyType> > ArmorTemplateMap;

class Object;

#include "../../Include/Common/ObjectLookupMap.h"

class Rva002BFA12
{
public:
	void rva002BFA12(void *obj);

private:
	char m_pad[0x98];
	ArmorTemplateMap m_map;
};

void Rva002BFA12::rva002BFA12(void *obj)
{
	NameKeyType key = *(NameKeyType *)((char *)obj + 0x24);
	if (m_map.find(key) == m_map.end())
	{
		ObjectLookupMap *om = (ObjectLookupMap *)&m_map;
		*om->findSlot((int *)&key) = (Object *)obj;
	}
}

class Rva002D3627Host { public: __declspec(noinline) int rva002BED69(); };
int Rva002D3627Host::rva002BED69() {
 int *value=(int*)((char*)this+0x88);return ++*value;
}
