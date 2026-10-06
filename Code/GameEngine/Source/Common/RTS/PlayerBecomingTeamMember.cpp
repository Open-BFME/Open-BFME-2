// cl: /DNDEBUG /MD
//
// ?becomingTeamMember@Player@@QAEXPAVObject@@_N@Z @0x002AD4EC (257B): Zero
// Hour Player::becomingTeamMember in source order, plus one BFME 2 tail.
// Target evidence: not OBJECT_STATUS_UNDER_CONSTRUCTION (2) through the rowed
// Object::testStatus 0x0004E536 gates the rowed power dispatch 0x0028D99A
// (friend_adjustPowerForPlayer); the neutral-player test reads ThePlayerList
// +0x18; NAMEKEY("AutoDepositUpdate") (string 0x00BF5504) through the rowed
// nameToKey and findModule feeds AutoDepositUpdate::awardInitialCaptureBonus
// 0x0049A26F (pinned: its body rearms the deposit frame, then returns unless
// a player, the +0x24 award flag and a positive module-data bonus); the
// battle-plan branch sums the three plan counters at +0xAC/+0xB0/+0xB4, checks
// Object +0x435 (areModulesReady) and calls the rowed apply/remove pair
// 0x002AC917/0x002AC92B; KINDOF_DOZER is template +0x109 bit 0x40, the AI
// update +0x258 answers isIdle at slot 0x1B8 and TheInGameUI adds (slot
// 0x1A4) or removes (slot 0x1A8, with the player index +0x54) the idle
// worker. BFME 2 addition (structural): on joining, when Player +0x2E8 is set
// and the object's +0x250 interface answers slot 2 non-zero, the object is
// handed to the rowed Rva004F56FC::rva004F56FC 0x004F56FC.

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

enum ObjectStatusTypes
{
	OBJECT_STATUS_UNDER_CONSTRUCTION = 2
};

class Player;
class Module;

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};
extern NameKeyGenerator *TheNameKeyGenerator;
#define NAMEKEY(x) TheNameKeyGenerator->nameToKey(x)

class AutoDepositUpdate
{
public:
	void awardInitialCaptureBonus(Player *player);
};

class AIUpdateInterface
{
public:
#define AI_SLOT(n) virtual void aiSlot##n();
#define AI_SLOT10(n) AI_SLOT(n##0) AI_SLOT(n##1) AI_SLOT(n##2) AI_SLOT(n##3) AI_SLOT(n##4) \
	AI_SLOT(n##5) AI_SLOT(n##6) AI_SLOT(n##7) AI_SLOT(n##8) AI_SLOT(n##9)
	AI_SLOT10(0) AI_SLOT10(1) AI_SLOT10(2) AI_SLOT10(3) AI_SLOT10(4)
	AI_SLOT10(5) AI_SLOT10(6) AI_SLOT10(7) AI_SLOT10(8) AI_SLOT10(9)
	AI_SLOT10(10)
#undef AI_SLOT10
#undef AI_SLOT
	virtual Bool isIdle() const;				// slot 110 (+0x1B8)
};

class Rva002AD5D5Interface
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual Int slot2();
};

class ThingTemplate
{
public:
	Bool isKindOfDozer() const { return (m_kindOf109 & 0x40) != 0; }

private:
	char m_pad[0x109];
	unsigned char m_kindOf109;
};

class Object
{
public:
	Bool testStatus(ObjectStatusTypes bit) const;
	void friend_adjustPowerForPlayer(Bool yes);
	Module *findUpdateModule(NameKeyType key) const { return findModule(key); }
	Bool areModulesReady() const { return m_modulesReady; }
	Bool isKindOfDozer() const { return m_template->isKindOfDozer(); }
	AIUpdateInterface *getAIUpdateInterface() const { return m_ai; }
	Rva002AD5D5Interface *getRva002AD5D5() const { return m_250; }

protected:
	Module *findModule(NameKeyType key) const;

private:
	void *m_vtbl;
	const ThingTemplate *m_template;			// +0x04
	char m_pad08[0x250 - 0x08];
	Rva002AD5D5Interface *m_250;				// +0x250
	char m_pad254[0x258 - 0x254];
	AIUpdateInterface *m_ai;					// +0x258
	char m_pad25C[0x435 - 0x25C];
	Bool m_modulesReady;						// +0x435
};

class PlayerList
{
public:
	Player *getNeutralPlayer() { return m_neutralPlayer; }

private:
	char m_pad[0x18];
	Player *m_neutralPlayer;					// +0x18
};
extern PlayerList *ThePlayerList;

class InGameUI
{
public:
#define UI_SLOT(n) virtual void uiSlot##n();
#define UI_SLOT10(n) UI_SLOT(n##0) UI_SLOT(n##1) UI_SLOT(n##2) UI_SLOT(n##3) UI_SLOT(n##4) \
	UI_SLOT(n##5) UI_SLOT(n##6) UI_SLOT(n##7) UI_SLOT(n##8) UI_SLOT(n##9)
	UI_SLOT10(0) UI_SLOT10(1) UI_SLOT10(2) UI_SLOT10(3) UI_SLOT10(4)
	UI_SLOT10(5) UI_SLOT10(6) UI_SLOT10(7) UI_SLOT10(8) UI_SLOT10(9)
	UI_SLOT(100) UI_SLOT(101) UI_SLOT(102) UI_SLOT(103) UI_SLOT(104)
#undef UI_SLOT10
#undef UI_SLOT
	virtual void addIdleWorker(Object *obj);					// slot 105 (+0x1A4)
	virtual void removeIdleWorker(Object *obj, Int playerNumber);	// slot 106 (+0x1A8)
};
extern InGameUI *TheInGameUI;

class Rva004F56FC
{
public:
	void rva004F56FC(Object *obj);
};

class Player
{
public:
	void applyBattlePlanBonusesForObject(Object *obj) const;
	void removeBattlePlanBonusesForObject(Object *obj) const;
	void becomingTeamMember(Object *obj, Bool yes);
	Int getNumBattlePlansActive() const
	{
		return m_bombardBattlePlans + m_holdTheLineBattlePlans + m_searchAndDestroyBattlePlans;
	}
	Int getPlayerIndex() const { return m_playerIndex; }

private:
	char m_pad[0x54];
	Int m_playerIndex;							// +0x54
	char m_pad58[0xAC - 0x58];
	Int m_bombardBattlePlans;					// +0xAC
	Int m_holdTheLineBattlePlans;				// +0xB0
	Int m_searchAndDestroyBattlePlans;			// +0xB4
	char m_padB8[0x2E8 - 0xB8];
	Rva004F56FC *m_2e8;							// +0x2E8
};

void Player::becomingTeamMember(Object *obj, Bool yes)
{
	if (!obj)
		return;

	if (!obj->testStatus(OBJECT_STATUS_UNDER_CONSTRUCTION))
	{
		obj->friend_adjustPowerForPlayer(yes);
	}

	if (this != ThePlayerList->getNeutralPlayer() && yes)
	{
		NameKeyType key_AutoDepositUpdate = NAMEKEY("AutoDepositUpdate");
		AutoDepositUpdate *adu = (AutoDepositUpdate *)obj->findUpdateModule(key_AutoDepositUpdate);
		if (adu != 0)
		{
			adu->awardInitialCaptureBonus(this);
		}
	}

	if (getNumBattlePlansActive() > 0 && obj->areModulesReady())
	{
		if (yes)
		{
			applyBattlePlanBonusesForObject(obj);
		}
		else
		{
			removeBattlePlanBonusesForObject(obj);
		}
	}

	if (obj->isKindOfDozer()
			&& obj->getAIUpdateInterface()
			&& obj->getAIUpdateInterface()->isIdle())
	{
		if (yes)
			TheInGameUI->addIdleWorker(obj);
		else
			TheInGameUI->removeIdleWorker(obj, getPlayerIndex());
	}

	if (yes && m_2e8 && obj->getRva002AD5D5() && obj->getRva002AD5D5()->slot2())
	{
		m_2e8->rva004F56FC(obj);
	}
}
