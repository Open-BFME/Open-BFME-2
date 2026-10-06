// cl: -Ireference/open-bfme-1/game/GameEngine/Source/Common
// Six more: a reset, two walks over a circular list, a two-flag veto reached
// by a back-step, a float read behind two guards, and a fill.

class BfmeNodeDI
{
public:
	BfmeNodeDI *m_bfmeNext;					// +0x00
	int m_bfmeGap;						// +0x04
	void *m_bfmeKey;					// +0x08
};

class BfmeThingDI
{
public:
	int m_bfmeHead[29];					// +0x00
	void *m_bfmeKey;					// +0x74
};

class Gen_001EFD20
{
public:
	bool bfmeIsNew(const BfmeThingDI *thing) const;

private:
	int m_bfmeHead[31];					// +0x00
	BfmeNodeDI *m_bfmeList;					// +0x7C
};

// ?bfmeIsNew@Gen_001EFD20@@QBE_NPBVBfmeThingDI@@@Z
bool Gen_001EFD20::bfmeIsNew(const BfmeThingDI *thing) const
{
	BfmeNodeDI *head = m_bfmeList;

	void *key = thing->m_bfmeKey;

	for (BfmeNodeDI *node = head->m_bfmeNext; node != head; node = node->m_bfmeNext)
	{
		if (key == node->m_bfmeKey)
			return false;
	}

	return true;
}
