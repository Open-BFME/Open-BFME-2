// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?rva004FF9C9@Rva004FF9C9@@QAEPAXH@Z @0x004FF9C9 19B: map find thunk returning node+0x34.
// Retail is lea eax [esp+4] push eax add ecx 4 call rowed int-int _M_find
// 0x00388F63 then add eax 0x34 ret 4. The map lives at +4; the +0x34 is the
// vector inside the mapped value (value+0x20 since second starts at node+0x14).
// Reuses the rowed int-int _M_find like stlport_map_004FF8DA.cpp because
// _M_find only touches keys. Caller 0x0059BB50 uses the return as a vector
// with stride 0x14.
#include <map>

class Rva004FF9C9
{
	char m_pad[4];
	_STL::map<int, int> m_map;
public:
	void *rva004FF9C9(int key);
};

void *Rva004FF9C9::rva004FF9C9(int key)
{
	_STL::map<int, int>::iterator it = m_map.find(key);
	return (char *)it._M_node + 0x34;
}
