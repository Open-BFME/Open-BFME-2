// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /MD /arch:SSE
// HordeMeleeHoldGround.cpp -- per-unit attack-state accessors recovered from
// WorldBuilder leads (reverse/wb_name_leads.csv). WB's debug build names the
// members and asserts !(index<0||index>=m_AttackInfo.size()); retail keeps
// that range check as a guard. m_AttackInfo is a vector of per-unit states at
// +0x08 (WB member name); the state values 2 (rotating) and 3 (arrived) come
// from the accessor names.

typedef int Int;
typedef bool Bool;
typedef unsigned int UnsignedInt;

// STLport vector<Int> view.
class AttackInfoVector
{
public:
	UnsignedInt size() const { return m_finish - m_start; }
	Int &operator[](UnsignedInt i) { return m_start[i]; }
	const Int &operator[](UnsignedInt i) const { return m_start[i]; }

private:
	Int *m_start;
	Int *m_finish;
	Int *m_endOfStorage;
};

#include "ascii_string.h"
class Xfer;

enum { UNIT_ROTATING = 2, UNIT_ARRIVED = 3 };

class HordeMeleeHoldGround
{
public:
	virtual Bool isUnitRotating(Int index) const;
	virtual void setUnitRotating(Int index);
	virtual void setUnitArrived(Int index);
	void rva005837F0(Xfer *xfer);

private:
	unsigned char m_pad04[4];
	AttackInfoVector m_AttackInfo;		// +0x08
};

// HordeMeleeHoldGround::isUnitRotating, retail 0x00583726.
Bool HordeMeleeHoldGround::isUnitRotating(Int index) const
{
	if (index < 0 || index >= m_AttackInfo.size())
		return false;
	return m_AttackInfo[index] == UNIT_ROTATING;
}

// HordeMeleeHoldGround::setUnitRotating, retail 0x00583750.
void HordeMeleeHoldGround::setUnitRotating(Int index)
{
	if (index < 0 || index >= m_AttackInfo.size())
		return;
	m_AttackInfo[index] = UNIT_ROTATING;
}

// HordeMeleeHoldGround::setUnitArrived, retail 0x00583772.
void HordeMeleeHoldGround::setUnitArrived(Int index)
{
	if (index < 0 || index >= m_AttackInfo.size())
		return;
	m_AttackInfo[index] = UNIT_ARRIVED;
}

#define PAD_VIRTUAL_10(p) 	virtual void p##0(); virtual void p##1(); virtual void p##2(); virtual void p##3(); virtual void p##4(); 	virtual void p##5(); virtual void p##6(); virtual void p##7(); virtual void p##8(); virtual void p##9();
#define PAD_VIRTUAL_100 PAD_VIRTUAL_10(v0) PAD_VIRTUAL_10(v1) PAD_VIRTUAL_10(v2) PAD_VIRTUAL_10(v3) PAD_VIRTUAL_10(v4) 	PAD_VIRTUAL_10(v5) PAD_VIRTUAL_10(v6) PAD_VIRTUAL_10(v7) PAD_VIRTUAL_10(v8) PAD_VIRTUAL_10(v9)

enum ObjectStatusTypes
{
	RVA_OBJECT_STATUS_1C = 0x1C
};

enum CommandSourceType
{
	CMD_FROM_AI = 2
};

#include "../../../../../Include/GameLogic/Module/AIUpdate.h"

// The object's AI (+0x258): slot 110 answers a bool; its command interface
// sits at +0x20.

class Object
{
public:
	Object *rva002931F5(bool flag);
	Bool testStatus(ObjectStatusTypes status) const;
	void rva00295F05(bool value);
	AIUpdateInterface *getAI() const { return m_ai; }
private:
	char m_pad000[0x258];
	AIUpdateInterface *m_ai;	// +0x258
};

struct Rva00583794Node
{
	Rva00583794Node *m_next;
	Rva00583794Node *m_prev;
	Object *m_object;
};

struct Rva00583794List
{
	Rva00583794Node *m_head;
};

struct Rva00583794Range
{
	int m_00;
	const Rva00583794List *m_list;
};

template <int N> class Rva00583794Slots : public Rva00583794Slots<N - 1>
{
public:
	virtual void gap(char (*slot)[N]) = 0;
};

template <> class Rva00583794Slots<0>
{
};

class Rva00583794Iface : public Rva00583794Slots<70>
{
public:
	virtual void fill(Rva00583794Range *range) = 0;
};

struct Rva00583794Member04
{
	char m_pad00[0x20];
	void *m_vtable;
};

// The code-pointer table at RVA 0x86FC50 groups 0x00583794 with the matched
// HordeMeleeHoldGround bodies at 0x00583726/0x00583750/0x00583772. That is
// target-table evidence for the family; the exact method and +0x04 member
// identities remain unresolved. The Ghidra boundary is 0x00583794..0x005837F0.
// ?rva00583794@Rva00583794@@QAEXPAVObject@@@Z @0x00583794 92B
class Rva00583794
{
public:
	void rva00583933(Object *object);
	void rva00583794(Object *object);

private:
	void *m_vtable;
	Rva00583794Member04 *m_member04;
};

void Rva00583794::rva00583794(Object *object)
{
	object->rva002931F5(false);
	Rva00583794Range range;
	((Rva00583794Iface *)&m_member04->m_vtable)->fill(&range);
	for (Rva00583794Node *node = range.m_list->m_head->m_next;
		node != range.m_list->m_head;
		node = node->m_next)
	{
		Object *item = node->m_object;
		if (item != 0 && !item->testStatus(RVA_OBJECT_STATUS_1C))
			item->rva00295F05(0);
	}
}

// Slot 3 of the same table (RVA 0x86FC3C), native 0x00583933..0x005839A7
// RET 4 (its argument is unused): the same walk over the +0x04 member's
// object list, sending each live object's AI idle (from the AI, unless its
// slot 110 says otherwise) before the per-object call slot 5 also makes.
// ?rva00583933@Rva00583794@@QAEXPAVObject@@@Z @0x00583933 116B
void Rva00583794::rva00583933(Object *)
{
	Rva00583794Range range;
	((Rva00583794Iface *)&m_member04->m_vtable)->fill(&range);
	for (Rva00583794Node *node = range.m_list->m_head->m_next;
		node != range.m_list->m_head;
		node = node->m_next)
	{
		Object *item = node->m_object;
		if (item != 0)
		{
			if (!item->testStatus(RVA_OBJECT_STATUS_1C))
			{
				AIUpdateInterface *ai = item->getAI();
				if (ai != 0 && !ai->isIdle())
					ai->aiIdle(CMD_FROM_AI);
			}
			item->rva00295F05(0);
		}
	}
}

// The native table at 0x86FC50 slot7 and the class-name literal establish
// this Horde transfer family. Native5837F0..5838B5 checks version1 and
// serializes the expected name through Xfer slots10 and27. Method name is
// address-derived. The four-byte version local preserves the observed
// EBP-14 version / EBP-10 string placement; only its first two bytes are
// transferred. Plain strings reproduce both native cleanup funclets.
class Snapshot;
class AsciiString;
class UnicodeString;
class PooledString;
struct Coord3DBase;
struct ICoord3D;
struct Region3D;
class IRegion3D;
class Coord2D;
struct ICoord2D;
struct Region2D;
struct IRegion2D;
class RealRange;
struct RGBColor;
class RGBAColorReal;
class RGBAColorInt;
struct XferUnknown11;
#include "../../../../../Include/Common/BfmeXfer.h"

class Xfer::Version
{
public:
    unsigned char version;
    unsigned char current;
    unsigned char pad[2];
};
#include "../../../../../Include/Common/XferException.h"
static __forceinline const char *TransferHordeVersion(Xfer *xfer, Xfer::Version &version)
{
    version.version = 1;
    version.current = 1;
    *xfer == version;
    return "HordeMeleeHoldGround";
}
void HordeMeleeHoldGround::rva005837F0(Xfer *xfer)
{
    Xfer::Version version;
    AsciiString expected(TransferHordeVersion(xfer, version));
    AsciiString actual(expected);
    *xfer == actual;
    if (actual.compare(expected) != 0)
        throw XferException(4, "Xfer data saved by %s is now being loaded by %s", actual.str(), expected.str());
}
