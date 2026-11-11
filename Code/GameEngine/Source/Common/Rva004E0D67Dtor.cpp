// cl: /O1 /MD /EHsc
// ??1LivingWorldBuilding@@UAE@XZ, retail 0x004E0D67..0x004E0E5C (245 bytes, EH):
// the destructor of the Snapshot-derived Rva004E0B60 family object (the same
// +0x2C/+0x30/+0x34 fields that Rva004E0ADBFamily.cpp reads; opaque pin of
// its scalar deleting destructor 0x004E0E5C, tables 0x00C61618 and
// 0x00C61610 at +4). It broadcasts through the rowed rva004E0B60 with the
// slot-1 vcall thunk 0x005CB260, ::deletes its +0x2C object, zeroes +0x40
// and +0x44, ::deletes every object of its +0x30 list and takes its +4
// listener off TheLivingWorldLogic's +0x1C list (rowed erase 0x002B7250).
// Then its parts die as retail's unwind map lists them: the +0x3C holder
// (rowed 0x002B2E8E), the +0x30 list storage and the +8 buffer base (GameFree;
// unwind copies 0x0007FAB3), the +4 listener base (restores 0x00C62A20; copy
// 0x004EDFFF) and Snapshot. Identities are not established.
// LivingWorldBuilding's Snapshot slots carry BFME2's capitalized names and the
// non-const name getter, as LivingWorldBuilding.cpp declares them (table 0x00C61618).
#define BFME_SNAPSHOT_CAPITALIZED_SLOTS
#define BFME_SNAPSHOT_NAME_SLOT
#define BFME_SNAPSHOT_NONCONST_NAME_SLOT
#include "../../../../reference/shims/moduledata/Common/Snapshot.h"
#include "../../Include/Common/RegionTurnObserverView.h"

void __cdecl Rva00030830GameFree(void *);

class Rva005CB260 { public: void rva005CB260(); };

struct Rva004EFour
{
	void (Rva005CB260::*a)();
	int b;
	int c;
	int d;
};

#include "../../Include/Common/Rva004E0B60.h"

class CreateAHeroData;

#include "../../Include/Common/Rva002B7250.h"

class LivingWorldLogic
{
public:
	unsigned char m_pad00[0x1C];
	Rva002B7250 m_list1C;
};

extern LivingWorldLogic *TheLivingWorldLogic;

#include "../../../Libraries/Source/Apt/AptRefTarget.h"

void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);

struct Rva004F6093Target
{
	char m_pad00[0xAC];
	TargetRef00217D4C m_ac;			// +0xAC
};

class Rva004F6093Holder
{
public:
	~Rva004F6093Holder()
	{
		if (m_ptr)
			ReleaseTreeHintRef00217D4C(&m_ptr->m_ac);
	}
private:
	Rva004F6093Target *m_ptr;
};

class Rva004E0D67Owned
{
public:
	virtual ~Rva004E0D67Owned();
};

struct Gen_uw_0007fab3
{
	~Gen_uw_0007fab3() { if (m_begin) Rva00030830GameFree(m_begin); }
	void *m_begin;
	void *m_end;
	void *m_capacity;
};

struct Gen_uwm_0007fab3
{
	~Gen_uwm_0007fab3() { if (m_begin) Rva00030830GameFree(m_begin); }
	Rva004E0D67Owned **m_begin;
	Rva004E0D67Owned **m_end;
	Rva004E0D67Owned **m_capacity;
};

// The +4 listener is the RegionTurnObserverView base (table 0x00C61610, own
// table 0x00C62A20 restored inline), with LivingWorldBuilding.cpp's overrides.
class LivingWorldBuilding : public Snapshot, public Gen_uw_0007fab3, public RegionTurnObserverView
{
public:
	virtual ~LivingWorldBuilding();
	virtual void BeginTurn(int, int);
	virtual void LoadPostProcess();
	virtual const char *GetSnapshotName();
	virtual void DoXfer(Xfer *xfer);
private:
	unsigned char m_pad14[0x2C - 0x14];
	Rva004E0D67Owned *m_2C;
	Gen_uwm_0007fab3 m_list;		// +0x30
	Rva004F6093Holder m_3C;
	int m_40;
	int m_44;
};

LivingWorldBuilding::~LivingWorldBuilding()
{
	Rva004EFour f = { &Rva005CB260::rva005CB260, 0, 0, 0 };
	reinterpret_cast<Rva004E0B60 *>(this)->rva004E0B60(f, (int)this);
	::delete m_2C;
	m_40 = 0;
	m_44 = 0;
	Rva004E0D67Owned **end = m_list.m_end;
	for (Rva004E0D67Owned **p = m_list.m_begin; p != end; ++p)
		::delete *p;
	TheLivingWorldLogic->m_list1C.rva002B7250((CreateAHeroData *)static_cast<RegionTurnObserverView *>(this));
}
