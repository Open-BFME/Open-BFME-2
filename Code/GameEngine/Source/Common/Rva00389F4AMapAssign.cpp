// cl: /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
//
// ?rva00389F4A@Rva00389F4A@@QAEHH@Z @0x00389F4A, 45B.
// Post-increment id at this+0x274 then map<int,int> at this+0x278 assign
// via rowed operator[] 0x0028932C. Retail lea/push of the stack id, add
// ecx,0x278 call, then store arg and return old id. Sole caller 0x0038A905
// passes its method arg through and keeps the returned id. Honest address
// name; class and method identity unproven.
#include <map>

class Rva00389F4A
{
public:
	int rva00389F4A(int val);
private:
	char m_pad[0x274];
	int m_next;
	_STL::map<int, int> m_map;
};

int Rva00389F4A::rva00389F4A(int val)
{
	int id = m_next++;
	m_map[id] = val;
	return id;
}
