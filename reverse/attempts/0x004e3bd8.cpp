// ?rva004E3BD8@@YAXPAVINI@@HPAV?$vector@UBfmePod88@@V?$allocator@UBfmePod88@@@_STL@@@_STL@@@Z
// partial score=0.9 date=2026-10-06
// cl: /O1 /MD /EHsc
//
// ?rva004E3BD8@@YAXPAVINI@@PAU?$vector@UBfmePod88@@V?$allocator@UBfmePod88@@@_STL@@@_STL@@@Z @0x004E3BD8 90B.
// Static two-arg builder: bump the world counter into a 0x58-byte
// Rva004E3184 buffer via the pinned 0x4E30D5 init, run the rowed INI
// initFromINI over a static FieldParse table, push the buffer into the
// arg vector through the rowed BfmePod88 push_back, and let the buffer's
// implicit destructor (rowed 0x4E3184) close the EH region. Retail
// 0x004E3BD8..0x004E3C32. The buffer is an empty 0x58 view (size forced by
// the frame); the table VA goes through a g_00 file-RVA extern.

class Rva002BA8F1Logic;
Rva002BA8F1Logic *g_009FEF10 = 0;

class Rva002B3171BumpCounter
{
public:
	int bump() throw();
};

class Rva004E30D5
{
public:
	void rva004E30D5(void *arg) throw();
};

struct FieldParse;

class INI
{
public:
	void initFromINI(void *buf, const FieldParse *table);
};

extern int g_008616C0;

struct BfmePod88;

namespace _STL
{
template <class T> class allocator
{
};
template <class T, class A = allocator<T> > class vector
{
public:
	void push_back(const T &value);
};
}

class __declspec(novtable) Rva004E3184
{
public:
	virtual ~Rva004E3184();

private:
	char m_pad[0x54];
};

// ?rva004E3BD8@@YAXPAVINI@@PAU?$vector@UBfmePod88@@V?$allocator@UBfmePod88@@@_STL@@@_STL@@@Z
void __cdecl rva004E3BD8(INI *ini, int unused, _STL::vector<BfmePod88> *vec)
{
	Rva004E3184 buf;
	((Rva004E30D5 *)&buf)->rva004E30D5((void *)((Rva002B3171BumpCounter *)g_009FEF10)->bump());
	ini->initFromINI(&buf, (FieldParse *)&g_008616C0);
	vec->push_back(*(const BfmePod88 *)&buf);
}
