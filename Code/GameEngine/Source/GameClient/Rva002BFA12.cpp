// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva002BFA12@Rva002BFA12@@QAEXPAX@Z @0x002BFA12 54B
// Insert-if-absent: hashtable _M_find 0x002888D4 on map at +0x98 with key from arg+0x24,
// on miss ObjectLookupMap::findSlot 0x0041F4E5 on same address then store arg.
// Evidence: retail calls both on ecx+0x98 with same key pointer; caller 0x00539411 passes
// global at 0x00DFEF18 as this and object with key at +0x24; ArmorTemplateMap typedef
// mirrors Rva0035516CArmorFind.cpp so find inlines to rowed _M_find.
#include <hash_map>
#include <cstddef>

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
	size_t operator()(const T &value) const;
};

}

class ArmorTemplate
{
public:
	float m_damageCoefficient[38];
};

typedef std::hash_map<
	NameKeyType,
	ArmorTemplate,
	rts::hash<NameKeyType>,
	std::equal_to<NameKeyType> > ArmorTemplateMap;

class Object;

class ObjectLookupMap
{
public:
	Object **findSlot(int *key);
};

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
