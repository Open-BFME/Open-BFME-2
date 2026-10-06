// cl: /Ireference/shims/bfme2_ascii /EHs /MD /DNDEBUG /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva152d1c@Rva00152D1CObj@@QAEXH@Z @0x00152D1C 170B evidence: caller 0x00117172 via [mesh+0x94]->[+0xB8] arg 4; LINK BONUS 131B Rva00117120Cluster; virtual slot0 or 0 then AsciiString from char then copy +0x18 then vector copy +0x0C then 0x15288F.
// Evidence: pin ?rva152d1c@Rva00152D1CObj@@QAEXH@Z; callees rowed 0x00037BA0 0x000365F0 0x0010E604 0x0007C5D5 0x00036410 pin 0x0015288F; prev/next Common.
#include "ascii_string.h"

struct Rva0007BB16Record;
namespace _STL {
template <class T> class allocator {};
template <class T, class A = allocator<T> > class vector
{
public:
	vector(const vector &other);
	~vector();
private:
	void *m_00;
	void *m_01;
	void *m_02;
};
}

class Rva00152D1CInner
{
public:
	virtual const char *v00();
};

class Rva0015288F
{
public:
	void rva0015288F(int a1, int a2, int a3, int a4);
};

class Rva00152D1CObj
{
public:
	void rva152d1c(int n);
private:
	char m_pad[8];
	Rva00152D1CInner *m_08;
	_STL::vector<Rva0007BB16Record> m_vec;
	AsciiString m_str;
};

void Rva00152D1CObj::rva152d1c(int n)
{
	Rva00152D1CInner *inner = m_08;
	const char *v = inner ? inner->v00() : 0;
	AsciiString tmp1(v);
	AsciiString tmp2(m_str);
	_STL::vector<Rva0007BB16Record> tmpVec(m_vec);
	((Rva0015288F *)this)->rva0015288F((int)tmp1.str(), (int)tmp2.str(), (int)&tmpVec, n);
}
