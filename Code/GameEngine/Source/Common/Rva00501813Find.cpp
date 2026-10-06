// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva00501813@Rva00501813@@QAEHH@Z @0x00501813 49B: map find plus Sub copy returning second dword; evidence rowed _M_find 0x00388F63 pinned copy 0x005017B4 rowed dtor 0x00501776 and caller 0x004FB5BC
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

struct Rva00501813
{
	int m_head;
	_STL::map<int, int> m_map;
	int rva00501813(int key);
};

struct Rva00501844
{
	int m_head;
	_STL::map<int, int> m_map;
	int rva00501844(int key);
};

int Rva00501813::rva00501813(int key)
{
	const Rva00501DD4Sub *found = (const Rva00501DD4Sub *)&m_map.find(key)->second;
	Rva00501DD4Sub tmp(*found);
	int ret = *(const int *)((const char *)&tmp + 4);
	((Rva00501776 *)&tmp)->~Rva00501776();
	return ret;
}

int Rva00501844::rva00501844(int key)
{
	const Rva00501DD4Sub *found = (const Rva00501DD4Sub *)&m_map.find(key)->second;
	Rva00501DD4Sub tmp(*found);
	int ret = *(const int *)((const char *)&tmp + 8);
	((Rva00501776 *)&tmp)->~Rva00501776();
	return ret;
}
