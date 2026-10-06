// ??0Rva00414BA4Element@@QAE@ABU0@@Z
// partial score=0.93 date=2026-10-06
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

struct BfmeAssignExtra
{
	int v0;
	int v1;
	int v2;
};

struct BfmeAssignRecord44
{
	BfmeAssignRecord44 &operator=(const BfmeAssignRecord44 &other);
	char m_00[4]; // +0x00
	int m_04; // +0x04
	int m_08; // +0x08
	int m_0c; // +0x0C
	Rva0039BCF8 *m_10; // +0x10
	int m_14; // +0x14
	_STL::list<int, _STL::allocator<int> > m_list; // +0x18
	int m_1c; // +0x1C
	BfmeAssignExtra m_20; // +0x20 (12B via movsd x3)
};

BfmeAssignRecord44 &BfmeAssignRecord44::operator=(const BfmeAssignRecord44 &other)
{
	if (this == &other)
		return *this;
	((Rva0055A91A *)this)->rva0055A91A();
	m_04 = other.m_04;
	m_08 = other.m_08;
	m_0c = other.m_0c;
	m_list = other.m_list;
	m_1c = other.m_1c;
	m_20 = other.m_20;
	if (other.m_10 != 0)
		((Rva0055A91A *)this)->rva0055A93C(other.m_10);
	return *this;
}

extern int g_00C3A08C;

struct Rva00414BA4Element
{
	Rva00414BA4Element(const Rva00414BA4Element &other);
	int m_00; // +0x00 (set to &g_00C3A08C)
	int m_04; // +0x04
	int m_08; // +0x08
	int m_0c; // +0x0C
	Rva0039BCF8 *m_10; // +0x10
	int m_14; // +0x14
	_STL::list<int, _STL::allocator<int> > m_list; // +0x18
	int m_1c; // +0x1C
	BfmeAssignExtra m_20; // +0x20
	int m_2c; // +0x28? (to reach 44? Actually 0x20+12=0x2C=44, so no m_2c. Keep 44.)
};

// ??0Rva00414BA4Element@@QAE@ABU0@@Z present-unmatched
Rva00414BA4Element::Rva00414BA4Element(const Rva00414BA4Element &other)
	: m_00((int)&g_00C3A08C),
	m_04(other.m_04),
	m_08(other.m_08),
	m_0c(other.m_0c),
	m_10(0),
	m_14(-1),
	m_list(other.m_list)
{
	m_1c = other.m_1c;
	m_20.v0 = other.m_20.v0;
	m_20.v1 = other.m_20.v1;
	m_20.v2 = other.m_20.v2;
	if (other.m_10 != 0)
		((Rva0055A91A *)this)->rva0055A93C(other.m_10);
}
