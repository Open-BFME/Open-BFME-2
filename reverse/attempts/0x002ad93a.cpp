// ?rva002AD93A@Player@@QAEXPBVUpgradeTemplate@@H@Z
// partial score=0.95 date=2026-10-04
// cl: /O1 /DNDEBUG /MD
// ?rva002AD93A@Player@@QAEXPBVUpgradeTemplate@@H@Z @0x002AD93A 195B: Player upgrade completion team update plus Eva own-ally-enemy
// Evidence: outer list at +0x32C payload TeamPrototype first Team at +0x334 Team next via +0x40 getter row 0x005C4AF5 inner TeamMemberList iterate 0x00263864 advance 0x00263526 updateUpgradeModules 0x00292EEA Eva via ThePlayerList local +0x10 getRelationship 0x002AD0C6 Eva 0x001DE2DA at g_00DFDC30 caller 0x002AE329

enum Relationship
{
	ENEMIES = 0,
	NEUTRAL = 1,
	ALLIES = 2
};

class Object;
class Team;
class TeamPrototype;
class UpgradeTemplate;
class PlayerList;
struct Coord3D;

template<class OBJCLASS>
class DLINK_ITERATOR
{
public:
	DLINK_ITERATOR() {}
	DLINK_ITERATOR(OBJCLASS *cur, void *pmf) { (void)cur; (void)pmf; }
	void advance();
	bool done() const { return m_cur == 0; }
	OBJCLASS *cur() const { return m_cur; }
private:
	OBJCLASS *m_cur;
	unsigned char m_pad[28];
};

template<class OBJCLASS>
class Rva001705A0DlinkIterator
{
public:
	void advance();
	bool done() const { return m_cur == 0; }
	OBJCLASS *cur() const { return m_cur; }
private:
	OBJCLASS *m_cur;
	unsigned char m_pad[28];
};

class Rva005C4AF5DBase1
{
public:
	virtual void base1Slot();
};

class Rva005C4AF5DBase2
{
public:
	virtual void base2Slot();
};

class Rva005C4AF5DwordField : public Rva005C4AF5DBase1, public Rva005C4AF5DBase2
{
public:
	int get() const;
	char m_lead[0x40];
	int m_value;
};

class Object
{
public:
	void updateUpgradeModules();
};

class Team
{
public:
	DLINK_ITERATOR<Object> iterate_TeamMemberList() const;
};

class TeamPrototype
{
public:
	char m_pad[0x334];
	Team *m_firstTeam;
};

struct PlayerTeamNode
{
	PlayerTeamNode *m_next;
	PlayerTeamNode *m_prev;
	TeamPrototype *m_proto;
};

struct PlayerTeamHead
{
	PlayerTeamNode *m_next;
};

class UpgradeTemplate
{
public:
	char m_pad[0x4C];
	int m_evaOwn;
	int m_evaAlly;
	int m_evaEnemy;
};

class PlayerList
{
public:
	char m_pad[0x10];
	class Player *m_local;
};

class Eva
{
public:
	void rva001DE2DA(int eventId, const Coord3D *pos, int x);
};

struct Coord3D
{
	float x;
	float y;
	float z;
};

extern PlayerList *ThePlayerList;
extern Eva *g_00DFDC30;

class Player
{
public:
	void rva002AD93A(const UpgradeTemplate *upgrade, int x);
	Relationship getRelationship(const Team *team) const;
private:
	char m_pad00[0x2EC];
	Team *m_team2EC;
	char m_pad2F0[0x32C - 0x2EC - 4];
	PlayerTeamHead *m_list32C;
};

// ?rva002AD93A@Player@@QAEXPBVUpgradeTemplate@@H@Z present-unmatched
void Player::rva002AD93A(const UpgradeTemplate *upgrade, int x)
{
	for (PlayerTeamNode *node = m_list32C->m_next; node != (PlayerTeamNode *)m_list32C; node = node->m_next)
	{
		typedef int (Rva005C4AF5DwordField::*GetNextFn)() const;
		GetNextFn nextFn = &Rva005C4AF5DwordField::get;
		TeamPrototype *proto = node->m_proto;
		Team *team = proto->m_firstTeam;
		while (team != 0)
		{
			DLINK_ITERATOR<Object> iter = team->iterate_TeamMemberList();
			Rva001705A0DlinkIterator<Object> &riter = (Rva001705A0DlinkIterator<Object> &)iter;
			Object* &obj = reinterpret_cast<Object*&>(riter);
			for (; obj != 0; riter.advance())
				obj->updateUpgradeModules();
			team = (Team *)(reinterpret_cast<Rva005C4AF5DwordField *>(team)->*nextFn)();
		}
	}

	if (upgrade == 0 || x != 0)
		return;

	int eventId = -1;
	Player *localPlayer = ThePlayerList->m_local;
	if (this == localPlayer)
	{
		eventId = upgrade->m_evaOwn;
	}
	else if (localPlayer != 0 && m_team2EC != 0)
	{
		if (localPlayer->getRelationship(m_team2EC) == ALLIES)
			eventId = upgrade->m_evaAlly;
		else
			eventId = upgrade->m_evaEnemy;
	}
	g_00DFDC30->rva001DE2DA(eventId, 0, 0);
}
