// cl: /Ireference/shims/bfmelist /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva0055A91A@Rva0055A91A@@QAEXXZ @ 0x0055A91A 34B
// Evidence: LINK BONUS via 0x0039C09C; inner Rva0039BCF8 at +0x10 via rowed rva0039BCF8 0x0039BCF8; flag +0x14 set -1; list<int> at +0x18 via rowed clear 0x0023DAA5; count +0x1C set 0; callers 0x0039C0CA 0x0041453E 0x0055A93F 0x0055AC2D 0x0055A993; layout like Rva0055AA06 list/count.
#include <list>

class Rva0039BCF8
{
public:
	void **rva0039BCF8(void *val);
	char m_pad00[0x100];
	int m_100; // +0x100
};

class ModuleData;

class Rva0039C7A5Holder
{
public:
	void add(const ModuleData *data);
};

class Rva0055A91A
{
public:
	void rva0055A91A();
	void rva0055A93C(Rva0039BCF8 *p);
private:
	char m_pad00[0x10];
	Rva0039BCF8 *m_10; // +0x10
	int m_14; // +0x14
	_STL::list<int, _STL::allocator<int> > m_list; // +0x18
	int m_1c; // +0x1C
};

void Rva0055A91A::rva0055A91A()
{
	if (m_10 == 0)
		return;
	m_10->rva0039BCF8(this);
	m_14 = -1;
	m_list.clear();
	m_1c = 0;
}

void Rva0055A91A::rva0055A93C(Rva0039BCF8 *p)
{
	rva0055A91A();
	if (p == 0)
		return;
	m_10 = p;
	m_14 = p->m_100;
	((Rva0039C7A5Holder *)p)->add((const ModuleData *)this);
}
