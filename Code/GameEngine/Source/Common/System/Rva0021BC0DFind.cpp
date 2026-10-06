// cl: /Ireference/shims/bfme2_ascii /EHsc /MD
// stlport
// CreateAHeroManager::CreateAHeroSubClass::rva0021BC0D @ 0x0021BC0D 31B (unnamed
// in WB; called by WB CreateAHeroSubClass::GetBling/GetBlingIndex on their this)
// __thiscall map-find wrapper: map<int,int> at +0x24, stores found node into
// *out and returns found != end via rowed _M_find 0x00388F63. Evidence: ecx+0x24
// map, lea/push key, cmp found vs [map], setne al, ret 8; callers 0x0021BCA7 etc;
// sibling Rva0021BD22Find.cpp wraps same _M_find at +0x54 returning &second.
#include <map>

class CreateAHeroManager
{
public:
	struct CreateAHeroSubClass;
};

struct CreateAHeroManager::CreateAHeroSubClass
{
	char pad[0x24];
	_STL::map<int, int> m_map;
	unsigned char rva0021BC0D(int key, void **out);
};

unsigned char CreateAHeroManager::CreateAHeroSubClass::rva0021BC0D(int key, void **out)
{
	_STL::map<int, int>::iterator it = m_map.find(key);
	*out = it._M_node;
	return it._M_node != m_map.end()._M_node;
}
