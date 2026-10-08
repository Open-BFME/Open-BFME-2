// cl: /MD
// ?canPlayerGarrison@ActionManager@@QAE_NPBVPlayer@@PBVObject@@W4CommandSourceType@@@Z
// @0x0041C21B 122B. Zero Hour's ActionManager::canPlayerGarrison: null
// guards, effectively-dead and structure tests, a garrisonable contain, then
// owner / neutral relationship and an empty contain. contextCommandForNewSelection
// (0x0030ECD6) calls it with TheActionManager (0x00E030E8) in ECX, as Zero Hour's
// SelectionInfo.cpp does; the body never reads this. Formerly rowed as the
// stdcall free function Rva0041C21BIsVisible.
// Evidence: callers 0x00261478 (36B, pushes [esi+8]/arg/[esi+0x10]) and 0x0030ECD6 (767B);
// rowed callees ?getControllingPlayer@Object@@QBEPAVPlayer@@XZ and
// ?getRelationship@Player@@QBE?AW4Relationship@@PBVTeam@@@Z; virtual slots +0x10 (bool)
// and +0x114 (int(int)) on Object+0x250; flags Object+0x438 bit0 and [Object+4]+0x108 bit 0x80.

enum Relationship
{
	ENEMIES = 0,
	NEUTRAL = 1,
	ALLIES = 2
};

class Team;
class Object;
class Player
{
public:
	Relationship getRelationship(const Team *that) const;
};

class Team
{
public:
	Player *getControllingPlayer() const;
};

struct FlagBlock108
{
	char pad[0x108];
	unsigned char flags;
};

class VisIface
{
public:
	virtual void d00();
	virtual void d01();
	virtual void d02();
	virtual void d03();
	virtual bool IsActive();
	virtual void d05();
	virtual void d06();
	virtual void d07();
	virtual void d08();
	virtual void d09();
	virtual void d10();
	virtual void d11();
	virtual void d12();
	virtual void d13();
	virtual void d14();
	virtual void d15();
	virtual void d16();
	virtual void d17();
	virtual void d18();
	virtual void d19();
	virtual void d20();
	virtual void d21();
	virtual void d22();
	virtual void d23();
	virtual void d24();
	virtual void d25();
	virtual void d26();
	virtual void d27();
	virtual void d28();
	virtual void d29();
	virtual void d30();
	virtual void d31();
	virtual void d32();
	virtual void d33();
	virtual void d34();
	virtual void d35();
	virtual void d36();
	virtual void d37();
	virtual void d38();
	virtual void d39();
	virtual void d40();
	virtual void d41();
	virtual void d42();
	virtual void d43();
	virtual void d44();
	virtual void d45();
	virtual void d46();
	virtual void d47();
	virtual void d48();
	virtual void d49();
	virtual void d50();
	virtual void d51();
	virtual void d52();
	virtual void d53();
	virtual void d54();
	virtual void d55();
	virtual void d56();
	virtual void d57();
	virtual void d58();
	virtual void d59();
	virtual void d60();
	virtual void d61();
	virtual void d62();
	virtual void d63();
	virtual void d64();
	virtual void d65();
	virtual void d66();
	virtual void d67();
	virtual void d68();
	virtual int CheckActive(int v);
};

class Object
{
public:
	Player *getControllingPlayer() const;

public:
	void *m_vtbl;
	FlagBlock108 *m_block4;
	char m_pad08[0x250 - 8];
	VisIface *m_vis;
	char m_pad254[0x304 - 0x254];
	Team *m_team;
	char m_pad308[0x438 - 0x308];
	unsigned char m_flags438;
};

enum CommandSourceType { CMD_FROM_PLAYER = 0 };

class ActionManager
{
public:
	bool canPlayerGarrison(const Player *player, const Object *obj, CommandSourceType commandSource);
};

bool ActionManager::canPlayerGarrison(const Player *player, const Object *obj, CommandSourceType commandSource)
{
	if (player == 0 || obj == 0)
		return false;
	if ((obj->m_flags438 & 1) || ((obj->m_block4->flags & 0x80) == 0))
		return false;
	VisIface *vis = obj->m_vis;
	if (vis == 0 || !vis->IsActive())
		return false;
	if (player == obj->getControllingPlayer())
		return true;
	if (player->getRelationship(obj->m_team) != NEUTRAL)
		return false;
	return vis->CheckActive(0) == 0;
}
