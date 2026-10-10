// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva00501DF1@Rva00501DF1@@QAEHH@Z @0x00501DF1 49B: map find plus copy of the 0x2C LivingWorld AI player record returning its first dword; evidence rowed _M_find 0x00388F63 copy 0x005017B4 and dtor 0x00501776 on the same local and caller 0x004FB5AD
#include <map>

// map/set<int> internals otherwise instantiate the less<int>::operator()
// COMDAT (one byte shape per TU flags); an explicit dllimport+forceinline
// specialization takes those calls inline so this TU emits no external copy.
namespace _STL {
template <> __declspec(dllimport) __forceinline
bool less<int>::operator()(const int &a, const int &b) const
{ return a < b; }
}

struct Rva00501776
{
	Rva00501776(const Rva00501776 &that);
	~Rva00501776();
	int m_00;
	int m_04;
	int m_08;
	char m_rest[0x20];
};

struct Rva00501DF1
{
	int m_head;
	_STL::map<int, int> m_map;
	int rva00501DF1(int key);
};

int Rva00501DF1::rva00501DF1(int key)
{
	const Rva00501776 *found = (const Rva00501776 *)&m_map.find(key)->second;
	Rva00501776 tmp(*found);
	return tmp.m_00;
}
