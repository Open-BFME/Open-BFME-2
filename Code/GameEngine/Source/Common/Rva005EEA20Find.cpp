// cl: /MD
// ?rva005EEA20@Rva005EEA20@@QAEPAVObject@@PAVPlayer@@_N1@Z, retail 0x005EEA20, 166 bytes.
// First-match finder variant of Rva005EEB7BCollect: same map lookup then
// LeaField+4 range, TheGameLogic findObjectByID, +4 flag 0x80 at +0x108,
// optional +0x113 check gated by arg2, +0x258 getCurrentVictim,
// getControllingPlayer flag check, optional victim 0x80 check gated by arg3.
// Evidence: callers 0x005D7C63 0x005D8475 0x005D8636 pass ecx=this+0x28 with
// Player* plus 1/1 bools; callees rowed; globals g_00DFEEF8 TheGameLogic.
// Honest address name; owner unproven.

class Player;
class Object;
class AIUpdateInterface;

enum ObjectID
{
	OBJECTID_INVALID = 0
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};

extern GameLogic *TheGameLogic;

class Rva002A8F24
{
public:
	void *rva002A8F24(Player *player);
};

extern Rva002A8F24 *g_00DFEEF8;
// g_00DFEEF8: matched references place it at VA 0xdfeef8 (zero-filled .bss).
Rva002A8F24 * g_00DFEEF8;

class Rva005C4AD1LeaField
{
public:
	void *get() const;
};

class Player
{
public:
	bool rva002AA245() const; // 0x002AA245
};

struct FlagBlock
{
	unsigned char m_pad[0x108];
	unsigned char m_flag80;
	unsigned char m_pad2[10];
	unsigned char m_flag04;
};

class AIUpdateInterface
{
public:
	Object *getCurrentVictim() const;
};

class Object
{
public:
	Player *getControllingPlayer() const;
	char m_pad0[4];
	FlagBlock *m_pflags;
	char m_pad1[0x258 - 8];
	AIUpdateInterface *m_ai;
};

struct IdRange
{
	ObjectID *m_begin;
	ObjectID *m_end;
};

class Rva005EEA20
{
public:
	Object *rva005EEA20(Player *player, bool skipStealth, bool skipVictimCheck);
};

Object *Rva005EEA20::rva005EEA20(Player *player, bool skipStealth, bool skipVictimCheck)
{
	void *store = g_00DFEEF8->rva002A8F24(player);
	Rva005C4AD1LeaField *holder = *(Rva005C4AD1LeaField **)store;
	IdRange *range = (IdRange *)(void *)holder->get();
	ObjectID *it = range->m_begin;
	ObjectID *end = range->m_end;
	Object *result = 0;
	for (; result == 0 && it != end; ++it)
	{
		Object *obj = TheGameLogic->findObjectByID(*it);
		if (!obj)
			continue;
		if (obj->m_pflags->m_flag80 & 0x80)
			continue;
		if (!skipStealth && (obj->m_pflags->m_flag04 & 4))
			continue;
		Object *victim = obj->m_ai->getCurrentVictim();
		if (!victim)
			continue;
		Player *ctrl = victim->getControllingPlayer();
		if (!ctrl->rva002AA245())
			continue;
		if (!skipVictimCheck && (victim->m_pflags->m_flag80 & 0x80))
			continue;
		result = obj;
	}
	return result;
}
