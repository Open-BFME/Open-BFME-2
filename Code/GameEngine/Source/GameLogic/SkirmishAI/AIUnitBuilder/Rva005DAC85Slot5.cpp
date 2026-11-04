// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfmelist /O1 /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /arch:SSE
// stlport
// Native 0x005DACC0..0x005DADD1 (273B); WorldBuilder names this slot
// AIBuildableUnit::updatePriority (lead, not asserted as the name here).
// Evidence: vtable slot5 of 0x008765F8 class Rva005DAC85 via dtor row; layout from base Rva0055B0CC plus m_40; callees rowed rva002A8F24 bucket_count rva002D06CA get rva002A7461 plus pin rva002A8AB1 plus virtual slot2; globals VA 0xDFEEF8 0xDFF000 0xBBB8D8 0xBC3EE8 0xC765F0
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
#include "../../../../Include/GameLogic/Rva002A8F24.h"
extern Rva002A8F24 *TheSkirmishAIManager;

class ThingTemplate;
#include "../../../../Include/Common/ThingFactory.h"
extern ThingFactory *TheThingFactory;





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

class Xfer;

class Rva0055B0CC
{
public:
	Rva0055B0CC();
	virtual ~Rva0055B0CC();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
	virtual void slot5();
	virtual void Slot6(void *arg1, bool arg2);
	virtual void slot7();
	virtual void slot8();
	virtual void slot9();
	virtual void slot10();
	virtual void slot11();
	virtual void Rva0055AED6(Xfer *xfer, void *arg2);
protected:
	float m_04;
	int m_factoryID;
	AsciiString m_templateName;
	unsigned int m_10;
	char m_pad14[4];
	float m_18;
	char m_pad1C[0x10];
};

// The +0x3C string is destroyed by its own inline ~AsciiString (the
// releaseBuffer worker 0x00036410) before the base dtor runs.
class Rva005DAC85 : public Rva0055B0CC
{
public:
	void updatePriority();
	virtual ~Rva005DAC85();
	char m_pad2C[0x10];
private:
	AsciiString m_3C; // +0x3C
	void *m_40; // +0x40
};

// Slot 2 (0x0055B0B9, a float getter) is spelled void in the base view to keep
// its vtable alias; read it through a float-typed view of the same table.
struct Rva005DAC85Slot2View
{
	virtual void s0();
	virtual void s1();
	virtual float slot2() const;
};

inline float maxv(float leftValue, float rightValue) { return leftValue >= rightValue ? leftValue : rightValue; }
inline float maxi(float firstValue, float secondValue) { if (firstValue >= secondValue) return firstValue; return secondValue; }
struct Rva005DACC0PlayerView { char pad[0x60]; Rva002A7389 sk; };
// Retail 0x005DACC0..0x005DADD1, vtable 0x008765F8 slot 5. The player's
// score-keeper subobject (+0x60) is read through a typed view: a pointer
// local cast from m_40 gives the native register roles. The x87 lower
// clamp is written as a negated >= test, then capped at 1800 + 300 * (1 - ratio).
void Rva005DAC85::updatePriority()
{
	IntMap *map = *(IntMap **)((char *)TheSkirmishAIManager->rva002A8F24((Player *)m_40) + 0xC);
	if (map->bucket_count() < 2)
		return;
	const ThingTemplate *found = TheThingFactory->findTemplate(m_templateName);
	if ((*(unsigned char *)((char *)found + 0x11F) & 0x80) != 0)
		return;
	if ((*(unsigned char *)((char *)found + 0x113) & 4) != 0)
		return;
	Rva002A8AB1Record *rec = TheSkirmishAIManager->rva002A8AB1(m_40);
	Rva005DACC0PlayerView *pv = (Rva005DACC0PlayerView *)m_40;
	float fa = (float)pv->sk.get(0);
	float div = fa / (float)((Rva002A7461 *)&pv->sk)->rva002A7461();
	float priorityAdjustment = rec->m_160->arrA[rec->m_16C] - div;
	priorityAdjustment *= rec->m_160->arrB[rec->m_16C];
	float sum = ((const Rva005DAC85Slot2View *)this)->slot2() + priorityAdjustment;
	float priority;
	if (!(sum >= rec->m_160->arrA[3])) priority = rec->m_160->arrA[3];
	else priority = sum;
	float maxPriority = 1.0f - div;
	maxPriority *= 300.0f;
	maxPriority += 1800.0f;
	priority = maxPriority > priority ? priority : maxPriority;
	m_18 = priority;
}
