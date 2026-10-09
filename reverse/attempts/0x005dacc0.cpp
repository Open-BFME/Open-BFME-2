// ?rva005DACC0@Rva005DAC85@@QAEXXZ
// partial score=0.94 date=2026-10-09
// ?rva005DACC0@Rva005DAC85@@QAEXXZ
// Revised bank: native005DACC0..005DADD1; WB AIBuildableUnit::updatePriority is a strong lead.
// Existing address-view harness retained until its full class contract is reconciled.
// Correct unordered clamp behavior: x>m keeps m; all other cases choose x.
// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfmelist /O1 /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /arch:SSE
// stlport
// ?rva005DACC0@Rva005DAC85@@QAEXXZ @0x005DACC0 273B evidence: vtable slot5 of 0x008765F8 class Rva005DAC85 via dtor row; layout from base Rva0055B0CC plus m_40; callees rowed rva002A8F24 bucket_count rva002D06CA get rva002A7461 plus pin rva002A8AB1 plus virtual slot2; globals VA 0xDFEEF8 0xDFF000 0xBBB8D8 0xBC3EE8 0xC765F0
#include "ascii_string.h"

class Player;

namespace _STL
{
template <class T1, class T2> struct pair
{
	T1 first;
	T2 second;
};
template <class T> struct hash
{
};
template <class T> struct equal_to
{
};
template <class T> class allocator
{
};
template <class K, class V, class H, class E, class A> class hash_map
{
public:
	unsigned int bucket_count() const;
};
}

typedef _STL::hash_map<int, int, _STL::hash<int>, _STL::equal_to<int>, _STL::allocator<_STL::pair<const int, int> > > IntMap;

struct Rva002A8AB1Record;
class Rva002A8F24
{
public:
	void *rva002A8F24(Player *player);
	Rva002A8AB1Record *rva002A8AB1(void *key);
};
extern Rva002A8F24 *g_00DFEEF8;

class Rva002D06CA
{
public:
	void *rva002D06CA(const AsciiString *key);
};
extern Rva002D06CA *TheThingFactory;





class Rva002A7389
{
public:
	int get(int);
};

class Rva002A7461
{
public:
	int rva002A7461();
};

struct MidData
{
	char pad00[0x10];
	float arrA[42];
	float arrB[8];
};

struct Rva002A8AB1Record
{
	char pad00[0x160];
	MidData *m_160;
	char pad164[8];
	int m_16C;
};

class Rva0055B0CC
{
	friend class Rva005DAC85;
public:
	virtual void slot0();
	virtual void slot1();
	virtual float slot2();
	virtual void slot3();
	virtual void slot4();
	virtual void slot5();
	virtual void Slot6(void *arg1, bool arg2);
	virtual void slot7();
	virtual void slot8();
	virtual void slot9();
	virtual void slot10();
	virtual void slot11();
	virtual void Rva0055AED6(void *xfer, void *arg2);
	virtual ~Rva0055B0CC();
private:
	float m_04;
	int m_08;
	AsciiString m_0C;
	unsigned int m_10;
	char m_pad14[4];
	float m_18;
	char m_pad1C[0x10];
};

class Rva005DAC85 : public Rva0055B0CC
{
public:
	void rva005DACC0();
private:
	char m_pad2C[0x14];
	void *m_40;
};

// ?rva005DACC0@Rva005DAC85@@QAEXXZ present-unmatched
void Rva005DAC85::rva005DACC0()
{
	IntMap *map = *(IntMap **)((char *)g_00DFEEF8->rva002A8F24((Player *)m_40) + 0xC);
	if (map->bucket_count() < 2)
		return;
	void *found = TheThingFactory->rva002D06CA((const AsciiString *)&m_0C);
	if ((*(unsigned char *)((char *)found + 0x11F) & 0x80) != 0)
		return;
	if ((*(unsigned char *)((char *)found + 0x113) & 4) != 0)
		return;
	Rva002A8AB1Record *rec = g_00DFEEF8->rva002A8AB1(m_40);
	Rva002A7389 *sub = (Rva002A7389 *)((char *)m_40 + 0x60);
	float fa = (float)sub->get(0);
	float div = fa / (float)((Rva002A7461 *)sub)->rva002A7461();
	float v = rec->m_160->arrA[rec->m_16C] - div;
	v *= rec->m_160->arrB[rec->m_16C];
	float sum = slot2() + v;
	float m = (double)sum >= (double)rec->m_160->arrA[3] ? sum : rec->m_160->arrA[3];
	float x = 1.0f - div;
	x *= 300.0f;
	x += 1800.0f;
	m = x > m ? m : x;
	m_18 = m;
}
