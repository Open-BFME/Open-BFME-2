// cl: /MD /EHsc
// ??1Rva005D1D38@@UAE@XZ retail 0x005D1D38 87B
// Two-base dtor: own vptrs C75734 (+0) and C7572C (+0xC); under EH state 1,
// when the owner at +0x14 is set, the +0xC subobject is unregistered from the
// list at +8 of that owner through the rowed ?rva002B7250@Rva002B7250
// 0x002B7250; the second base's inline dtor restores C75284 and the pinned
// first-base dtor ??1Rva005CCDDD@@UAE@XZ 0x005CCDDD runs. Caller: rowed ??_G
// 0x005D1DAF (vtable 0x00C75734). Names address-derived.

class CreateAHeroData;

#include "../../Include/Common/Rva002B7250.h"

struct Rva005D1D38Owner
{
	int m_00;
	int m_04;
	Rva002B7250 m_list; // +0x08
};

// Class views as StrategicInGameUIResolveBattleChecklistItem.cpp declares
// them (that unit's ctor 0x005D1DCB stores the same vptrs), so the three
// vtables this dtor references are the copies the link keeps. The owner
// pointer at +0x14 is that view's `battle`.
class Rva005CCDDD {public:Rva005CCDDD();virtual ~Rva005CCDDD();virtual void slot04() = 0;virtual void clickSlot08();virtual void slot0C() = 0;virtual void slot10() = 0;virtual void slot14() = 0;virtual void slot18() = 0;int unknown4;void *payload;};
class Rva005D1D38Second {public:virtual void observerSlot0(int) = 0;virtual void observerSlot1(void*,unsigned) = 0;~Rva005D1D38Second(){} };
class Rva005D1D38:public Rva005CCDDD,public Rva005D1D38Second {public:Rva005D1D38(void*,void*);virtual ~Rva005D1D38();virtual void clickSlot08();void*planner;void*battle;};

Rva005D1D38::~Rva005D1D38()
{
	if (battle)
		((Rva005D1D38Owner *)battle)->m_list.rva002B7250((CreateAHeroData *)static_cast<Rva005D1D38Second *>(this));
}
