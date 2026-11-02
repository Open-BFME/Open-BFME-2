// cl: -Ireference/open-bfme-1/game/GameEngine/Source/Common
class BfmeTargetAM
{
public:
	virtual void bfmeSlot00AM(void);
	virtual void bfmeSlot01AM(void);
	virtual void bfmeSlot02AM(void);
	virtual void bfmeSlot03AM(void);
	virtual void bfmeSlot04AM(void);
	virtual void bfmeSlot05AM(void);
	virtual bool bfmeTestAM(void *value);
};

class Object;

// Partition filter base (vftable slot 2 is its rowed getPlayerMask, 0x0036CC7A),
// the same view ReplenishUnitsBehaviorUpdate.cpp declares.
#include "../../Include/GameLogic/PartitionFilter.h"

// Partition filter with vftable 0x00C49F14 (dtor, allow, getPlayerMask); bfmeCheckAM is its allow (slot 1).
class Rva00260F77Filter : public Rva000421C8
{
public:
	Rva00260F77Filter(BfmeTargetAM *target, bool invert);
	virtual ~Rva00260F77Filter();
	virtual bool allow(Object *value);

	BfmeTargetAM *m_bfmeTargetAM;
	bool m_bfmeInvertAM;
};

bool Rva00260F77Filter::allow(Object *value)
{
	if (m_bfmeTargetAM == 0)
		return 1;

	if (m_bfmeInvertAM)
		return m_bfmeTargetAM->bfmeTestAM(value);

	return !m_bfmeTargetAM->bfmeTestAM(value);
}

Rva00260F77Filter::Rva00260F77Filter(BfmeTargetAM *target, bool invert)
	: m_bfmeTargetAM(target), m_bfmeInvertAM(invert)
{
}

