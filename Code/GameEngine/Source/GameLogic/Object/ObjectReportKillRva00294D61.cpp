// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /ICode/GameEngine/Source/Common
// ?report@Rva00294D61@@QAEXPAVObject@@H@Z @0x00294D61 509B.
// Native 0x00294D61..0x00294F5E RET8. The older WB CD2040 pairing is
// refuted; native callers and Object fields establish this scoring operation.
// Original method name remains unknown; preserve its address-derived view.
// Object template +4, Player template +0x34, contain callback slot 68,
// member hero lookup and float/thiscall sacrifice are verified from retail.
// No artificial barriers, fixed callback addresses, or ABI casts.
// Retail-guided: walk the killer chain while the template bit 0x800000 is set,
// then score the victim once (StatsCollector counters, ScoreKeeper, bounty).
class Object;
class Player;

#include "GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;

#include "../../../Include/Common/PlayerList.h"
extern PlayerList *ThePlayerList;

#include "../../../Include/Common/ScoreKeeperClass.h"

enum Relationship { RELATIONSHIP_INVALID = 0, RELATIONSHIP_1 = 1, RELATIONSHIP_2 = 2 };

class Team;
class Player
{
public:
	bool isLocalPlayer() const;
	Relationship getRelationship(const Team *team) const;
	void doBountyForKill(const Object *killer, const Object *victim);
	bool addSkillPointsForKill(const Object *killer, const Object *victim);
	char m_pad00[0x34];
	void *m_template; // +0x34
	char m_pad38[0x2EC - 0x38];
	Team *m_2EC; // +0x2EC
	char m_pad2F0[0x3BC - 0x2F0];
	ScoreKeeper m_scoreKeeper; // +0x3BC
};

struct Rva00294D61Template
{
	char m_pad000[0x10D];
	unsigned char m_10D; // +0x10D
	char m_pad10E[0x115 - 0x10E];
	unsigned char m_115; // +0x115
	char m_pad116[0x11F - 0x116];
	unsigned char m_11F; // +0x11F
	unsigned int m_120;  // +0x120
};

struct Rva00294D61PlayerTemplate
{
	char m_pad000[0x1BC];
	unsigned char m_1BC; // +0x1BC
};

#include "../../../Include/Common/CreateAHeroHero.h"

void Rva00294D4B(Object *, Object *);
typedef void (*Cb)(Object *, Object *);
class ContainModule
{
public:
#define BFME_V(N) virtual void v##N();
	BFME_V(00) BFME_V(01) BFME_V(02) BFME_V(03) BFME_V(04) BFME_V(05) BFME_V(06) BFME_V(07)
	BFME_V(08) BFME_V(09) BFME_V(10) BFME_V(11) BFME_V(12) BFME_V(13) BFME_V(14) BFME_V(15)
	BFME_V(16) BFME_V(17) BFME_V(18) BFME_V(19) BFME_V(20) BFME_V(21) BFME_V(22) BFME_V(23)
	BFME_V(24) BFME_V(25) BFME_V(26) BFME_V(27) BFME_V(28) BFME_V(29) BFME_V(30) BFME_V(31)
	BFME_V(32) BFME_V(33) BFME_V(34) BFME_V(35) BFME_V(36) BFME_V(37) BFME_V(38) BFME_V(39)
	BFME_V(40) BFME_V(41) BFME_V(42) BFME_V(43)
	BFME_V(44) BFME_V(45) BFME_V(46) BFME_V(47) BFME_V(48) BFME_V(49) BFME_V(50) BFME_V(51) BFME_V(52) BFME_V(53) BFME_V(54) BFME_V(55) BFME_V(56) BFME_V(57) BFME_V(58) BFME_V(59) BFME_V(60) BFME_V(61) BFME_V(62) BFME_V(63) BFME_V(64) BFME_V(65) BFME_V(66) BFME_V(67) 
	virtual void v68(Cb cb, const Object *victim, int one);
#undef BFME_V
};

class Object
{
public:
	Player *getControllingPlayer() const;
	void rva00294C1A(Object *, bool, float);
	Relationship getRelationship(const Object *other) const;

	char m_pad000[4];
	Rva00294D61Template *m_template; // +0x04
	char m_pad008[0x74 - 0x08];
	int m_74; // +0x74
	int m_78; // +0x78
	char m_pad07C[0x250 - 0x7C];
	ContainModule *m_250; // +0x250
	char m_pad254[0x274 - 0x254];
	Object *m_274; // +0x274
	char m_pad278[0x436 - 0x278];
	unsigned char m_436; // +0x436
	char m_pad437[0x46C - 0x437];
	int m_46C; // +0x46C
	int m_470; // +0x470
};

class Rva00294D61 : public Object
{
public:
	void report(Object *victim, int arg1);
};

// VA 0x00E032F8: the StatsCollector pointer BfmeOwnVVDCtor.cpp defines.
class StatsCollector;
extern StatsCollector *g_00E032F8;
class CreateAHeroData;
#include "../../../Include/GameLogic/CreateAHeroManager.h"
extern CreateAHeroManager *TheCreateAHeroManager;

void Rva00294D61::report(Object *victimObj, int arg1)
{
	Object *killer = this;
	unsigned int chainBit = 0x800000;
	for (;;)
	{
		if ((killer->m_template->m_120 & chainBit) == 0)
			break;
		if (killer->m_78 == 0 || killer->m_78 == killer->m_74)
			break;
		Object *next = TheGameLogic->findObjectByID((ObjectID)killer->m_78);
		if (!next)
			break;
		killer = next;
	}

	if (victimObj->m_436)
		return;
	victimObj->m_436 = 1;

	if (killer->m_template->m_11F & 0x40)
	{
		Player *kp = killer->getControllingPlayer();
		if (kp != 0 && killer->getControllingPlayer()->isLocalPlayer())
		{
			CreateAHeroHero *hero = (CreateAHeroHero *)TheCreateAHeroManager->rva002197A6(killer->m_74);
			if (hero != 0)
				hero->rva004088F0(victimObj, arg1);
		}
	}

	if (arg1 == 1 || arg1 == 2)
	{
		if ((victimObj->m_template->m_10D & 0x80) == 0)
		{
			Player *vp = victimObj->getControllingPlayer();
			Player *kp = killer->getControllingPlayer();
			void *sc = g_00E032F8;
			if (sc != 0 && ThePlayerList != 0 && ThePlayerList->m_local == kp)
			{
                if (kp && vp) {
                    switch (kp->getRelationship(vp->m_2EC)) {
                    case 0: ++*(int *)((char *)g_00E032F8+0x2C); break;
                    case 2: ++*(int *)((char *)g_00E032F8+0x24); break;
                    default: ++*(int *)((char *)g_00E032F8+0x28); break;
                    }
                } else ++*(int *)((char *)sc+0x28);
			}
			if (vp != 0)
				vp->m_scoreKeeper.addObjectLost(victimObj);
			if (killer->getRelationship(victimObj) == 0 && kp != vp)
			{
				if (kp != 0)
				{
					killer->m_470 += 1;
					Object *owner = killer->m_274;
					killer->m_46C += 1;
					if (owner != 0 && (owner->m_template->m_115 & 0x20))
					{
						owner->m_470 += 1;
						owner->m_46C += 1;
					}
					kp->m_scoreKeeper.addObjectDestroyed(victimObj);
					kp->doBountyForKill(killer, victimObj);
				}
				if (vp != 0 && ((Rva00294D61PlayerTemplate *)vp->m_template)->m_1BC)
					vp->addSkillPointsForKill(killer, victimObj);
				if ((killer->m_template->m_120 & 2) != 0 && killer->m_250 != 0)
				{
					killer->m_250->v68(Rva00294D4B, victimObj, 1);
					return;
				}
                if ((killer->m_template->m_120 & 0x4000) != 0 && killer->m_274 != 0)
                    killer->m_274->rva00294C1A(victimObj, false, 1.0f);
                else
                    killer->rva00294C1A(victimObj, false, 1.0f);
			}
		}
	}
}
