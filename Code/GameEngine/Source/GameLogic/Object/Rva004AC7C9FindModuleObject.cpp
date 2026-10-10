// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /O1 /EHs /MD /arch:SSE /G7 /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_CRTIMP=
// stlport
// 0x004AC722 (69B) shares the helper: DestroyEnvironmentUpdate releases the object found by id
// through it. 0x004AC7C9 (130B): first object of the kind-of 0x65 partition query (accepted kind mask
// 0x65, rejected mask KINDOF_NONE) whose behaviour modules answer slot 31 of their
// secondary interface (+0x0C); returns that object's +0x74 pointer, or null. The check is
// the file-static helper 0x004AC5F5 (32B), which the compiler gives the object in EAX while
// it stays a noinline static with this single caller in the unit. Target evidence: bytes and
// callee relocations; the filter classes are views of the established partition filter
// ctors (0x000421C8 base, 0x0004584D accept-by-kind-of, 0x00045411 bit mask) and the
// filtered all-objects query 0x006256F0. Names are address-derived.
#include "ascii_string.h"
#include "../../Common/PartitionRangeQueryCallView.h"
#include "../../Common/GameLogicObjectLookupView.h"

typedef bool Bool;
class Object;
class PartitionManager;
extern PartitionManager *ThePartitionManager;

class Rva000421C8
{
public:
	Rva000421C8() : m_next(0) {}
	virtual ~Rva000421C8() {}
	virtual Bool allow(Object *obj) = 0;
	virtual int getPlayerMask();
	Rva000421C8 *m_next;
};

class BfmeFixedStorage0004543D
{
public:
	BfmeFixedStorage0004543D(const BfmeFixedStorage0004543D &other) throw();
private:
	unsigned char m_bytes[28];
};

struct Rva00045411BitSet
{
	Rva00045411BitSet(int unused, int bit) throw();
	unsigned int m_bits[7];
};

template <int NUMBITS> class BitFlags;
extern BitFlags<116> KINDOFMASK_NONE;

class Rva0004584D : public Rva000421C8
{
public:
	Rva0004584D(const BfmeFixedStorage0004543D &a, const BfmeFixedStorage0004543D &b) throw();
	virtual Bool allow(Object *obj);
	BfmeFixedStorage0004543D m_08;
	BfmeFixedStorage0004543D m_24;
};

struct BfmeResultA
{
	void *m_value;
	~BfmeResultA();
};

class BfmeResultForwardB
{
public:
	BfmeResultA bfmeForwardResultB(int value);
};

class ModuleInterface
{
public:
#define S(n) virtual void s##n();
	S(0) S(1) S(2) S(3) S(4) S(5) S(6) S(7) S(8) S(9) S(10) S(11) S(12) S(13) S(14) S(15)
	S(16) S(17) S(18) S(19) S(20) S(21) S(22) S(23) S(24) S(25) S(26) S(27) S(28) S(29) S(30)
#undef S
	virtual int slot31();	// +0x7C
};

struct Module
{
	char m_pad[0xC];
	ModuleInterface m_interface;	// +0x0C secondary interface
};

class Object
{
public:
	char m_pad000[0x74];
	Object *m_74;
	char m_pad078[0x244 - 0x78];
	Module **m_modules;	// +0x244
};

static __declspec(noinline) int Rva004AC5F5(Object *object)
{
	for (Module **m = object->m_modules; *m; ++m)
	{
		int r = (*m)->m_interface.slot31();
		if (r)
			return r;
	}
	return 0;
}

Object *Rva004AC7C9()
{
	BfmeResultA iter = ((BfmeResultForwardB *)ThePartitionManager)->bfmeForwardResultB(
		(int)&Rva0004584D(*(BfmeFixedStorage0004543D *)&Rva00045411BitSet(0, 0x65),
			*(BfmeFixedStorage0004543D *)&KINDOFMASK_NONE));
	for (Object *o = ((BfmeWideResult *)&iter)->next(); o; o = ((BfmeWideResult *)&iter)->next())
	{
		if (Rva004AC5F5(o))
			return o->m_74;
	}
	return 0;
}

extern GameLogic *TheGameLogic;

class Actor
{
public:
	virtual void release(float amount);
};

class DestroyEnvironmentUpdate
{
public:
	void rva004AC722();

private:
	char m_pad[0x24];
	unsigned int m_objectID;
};

void DestroyEnvironmentUpdate::rva004AC722()
{
	ObjectID id = (ObjectID)m_objectID;
	if (id == 0)
		return;
	Object *obj = TheGameLogic->findObjectByID(id);
	if (obj != 0) {
		Actor *actor = (Actor *)Rva004AC5F5(obj);
		if (actor != 0) {
			actor->release(0.0f);
			TheGameLogic->destroyObject(obj);
		}
	}
	m_objectID = 0;
}
