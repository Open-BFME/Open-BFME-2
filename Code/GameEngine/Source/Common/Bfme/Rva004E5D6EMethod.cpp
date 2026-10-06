// ?rva004E5D6E@Rva004E5D6E@@QAEXXZ
// @0x004E5D6E 68B via STL clear: for_each delete + erase + zero + 0xff000000 store
// cl: /MD /Oy- /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
#include <algorithm>
#include <vector>

class Rva004E5A78;

struct Rva004E5CB0Deleter
{
	void operator()(Rva004E5A78 *p) const;
};

struct Rva004E5D6EChild
{
	unsigned char m_pad[0x18];
	unsigned int m_field18;
};

class Rva004E5D6E
{
public:
	void rva004E5D6E();
private:
	unsigned char m_pad0[0xc];
	Rva004E5D6EChild *m_p; // +0xc
	_STL::vector<void *, _STL::allocator<void *> > m_vec; // +0x10
	int m_a; // +0x1c
	int m_b; // +0x20
	int m_c; // +0x24
};
void Rva004E5D6E::rva004E5D6E()
{
	m_a = 0;
	m_b = 0;
	m_c = 0;
	_STL::for_each((Rva004E5A78 **)m_vec.begin(), (Rva004E5A78 **)m_vec.end(), Rva004E5CB0Deleter());
	_STL::vector<void *, _STL::allocator<void *> > *pv = &m_vec;
	pv->erase(pv->begin(), pv->end());
	m_p->m_field18 = 0xff000000;
}
