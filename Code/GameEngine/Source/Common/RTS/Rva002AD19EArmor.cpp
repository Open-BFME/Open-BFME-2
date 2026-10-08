// cl: /MD /GX /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// stlport
// ?rva002AD19E@Rva002AD19E@@QAE_NPAX@Z @0x002AD19E 95B.
// Armor-map remove-or-clear returning bool. Evidence: unlock lane, callees
// clear/_M_find/erase for hash_map<NameKeyType ArmorTemplate> are rowed in
// Armor.cpp, +0x334 store with map at +4 size at +0x14, arg+0x34 key,
// neighbours PlayerGetRelationship/PlayerO1Shard share Player RTS shard.
#include <hash_map>

enum NameKeyType
{
	NK_Zero = 0
};
class ArmorTemplate
{
};
namespace rts
{
	template<class T> struct hash
	{
		unsigned int operator()(const T &x) const { return (unsigned int)x; }	// Zero Hour's rts::hash<NameKeyType>, inline
	};
}
typedef std::hash_map<NameKeyType, ArmorTemplate, rts::hash<NameKeyType>, std::equal_to<NameKeyType> > ArmorTemplateMap;
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
