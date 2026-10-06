// ?rva00152CDA@Rva00152D1CObj@@QAEPAV1@PAV1@@Z
// partial score=0.9 date=2026-10-06
// cl: /Ireference/shims/bfme2_ascii /O1 /EHs /MD /DNDEBUG /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva00152CDA@Rva00152D1CObj@@QAEPAV1@PAV1@@Z @0x00152CDA 66B evidence: unlocks 0x00152DE9; same layout +8 +0x0C +0x18 as 0x00152D1C; forwards other members with constant 4 and self-check.
// Evidence: pin none; callees pin 0x0015288F virtual slot0 AsciiString str; prev/next Common.
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
	Rva00152D1CObj *rva00152CDA(Rva00152D1CObj *other);
private:
	static __forceinline const char *strOf(const Rva00152D1CObj *o) { return o->m_str.str(); }
	char m_pad[8];
	Rva00152D1CInner *m_08;
	_STL::vector<Rva0007BB16Record> m_vec;
	AsciiString m_str;
};

// ?rva00152CDA@Rva00152D1CObj@@QAEPAV1@PAV1@@Z @0x00152CDA 66B
Rva00152D1CObj *Rva00152D1CObj::rva00152CDA(Rva00152D1CObj *other)
{
	if (this == other)
		return this;
	Rva00152D1CInner *inner;
	const char *s;
	const char *v;
	s = strOf(other);
	inner = other->m_08;
	v = inner ? inner->v00() : 0;
	((Rva0015288F *)this)->rva0015288F((int)v, (int)s, (int)&other->m_vec, 4);
	return this;
}
