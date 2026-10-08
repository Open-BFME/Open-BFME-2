class BfmeThingCFF;

class BfmeOwnerCFF;

// The owner is the Player and this the TeamPrototype (the ledger rows).
class TeamPrototype;
class Player
{
public:
	void addTeamToList(TeamPrototype *team);
	void removeTeamFromList(TeamPrototype *team);
};

class BfmeThingCFF
{
public:
	void bfmeGoCFF(BfmeOwnerCFF *owner);
	unsigned char m_bfmeHead[8];
	BfmeOwnerCFF *m_bfmeOwner;
};

void BfmeThingCFF::bfmeGoCFF(BfmeOwnerCFF *owner)
{
	if (owner != 0)
	{
		if (m_bfmeOwner != 0)
			((Player *)m_bfmeOwner)->removeTeamFromList((TeamPrototype *)this);
		m_bfmeOwner = owner;
		((Player *)owner)->addTeamToList((TeamPrototype *)this);
	}
}
