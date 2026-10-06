// cl: /Ireference/shims/bfme2_ascii /EHsc /MD
// stlport
// ?rva0021BD22@Rva0021BD22@@QAEPAHH@Z @0x0021BD22 31B
// __thiscall map-find wrapper: map<int,int> at +0x54, returns &value (node+0x14)
// or null via rowed _M_find 0x00388F63. Evidence: ecx+0x54 map, lea/push key,
// cmp found vs [map], je null else add 0x14, ret 4; callers 0x0021BDD3/0x0021BDFB.
#include <map>

struct Rva0021BD22
{
	char pad[0x54];
	_STL::map<int, int> m_map;
	int *rva0021BD22(int key);
};

int *Rva0021BD22::rva0021BD22(int key)
{
	_STL::map<int, int>::iterator it = m_map.find(key);
	if (it != m_map.end())
		return &(*it).second;
	return 0;
}
