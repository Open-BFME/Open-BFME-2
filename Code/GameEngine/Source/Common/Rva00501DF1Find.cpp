// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva00501DF1@Rva00501DF1@@QAEHH@Z @0x00501DF1 49B: map find plus Sub copy returning first dword; evidence rowed _M_find 0x00388F63 pinned copy 0x005017B4 rowed dtor 0x00501776 and caller 0x004FB5AD
#include <map>

struct Rva00501DD4Sub
{
	Rva00501DD4Sub(const Rva00501DD4Sub &that);
	char m_data[0x2c];
};

struct Rva00501776
{
	~Rva00501776();
	char m_data[0x2c];
};

struct Rva00501DF1
{
	int m_head;
	_STL::map<int, int> m_map;
	int rva00501DF1(int key);
};

int Rva00501DF1::rva00501DF1(int key)
{
	const Rva00501DD4Sub *found = (const Rva00501DD4Sub *)&m_map.find(key)->second;
	Rva00501DD4Sub tmp(*found);
	int ret = *(const int *)&tmp;
	((Rva00501776 *)&tmp)->~Rva00501776();
	return ret;
}
