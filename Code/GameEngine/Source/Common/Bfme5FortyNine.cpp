// cl: -Ireference/open-bfme-1/game/GameEngine/Source/Common
// Four more: a limit picked by a global switch, a search through a two-level
// list, a commit of two pending bytes, and a mask add.

class BfmeItemDS
{
public:
	int m_bfmeHead;						// +0x00
	void *m_bfmeKey;					// +0x04
};

class BfmeNodeDS
{
public:
	BfmeNodeDS *m_bfmeNext;					// +0x00
	int m_bfmeGap;						// +0x04
	BfmeItemDS *m_bfmeItem;					// +0x08
};

class Gen_00428090
{
public:
	bool bfmeContains(void *key) const;

private:
	int m_bfmeHead;						// +0x00
	BfmeNodeDS *m_bfmeList;					// +0x04
};

// ?bfmeContains@Gen_00428090@@QBE_NPAX@Z
bool Gen_00428090::bfmeContains(void *key) const
{
	BfmeNodeDS *head = m_bfmeList;

	for (BfmeNodeDS *node = head->m_bfmeNext; node != head; node = node->m_bfmeNext)
	{
		if (node->m_bfmeItem->m_bfmeKey == key)
			return true;
	}

	return false;
}
