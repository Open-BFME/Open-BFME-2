// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
//
// ?evaluateSkirmishSpecialPowerIsReady@ScriptConditions@@IAE_NPAVParameter@@0@Z
// @ 0x003E9062 404B (SKIRMISH_SPECIAL_POWER_READY; evaluateConditionHelper
// 0x003EA9AF passes the player and power Parameters).
//
// Identity: Zero Hour ScriptConditions::evaluateSkirmishSpecialPowerIsReady
// (donor source; BFME 1 a2c8039e6 ScriptConditionsSkirmishSpecialPowerIsReady.cpp
// carries the same player-mask delta), confirmed by target evidence: the
// power Parameter's cached frame at +0x20 (-1 = never, > now = not yet),
// findSpecialPowerTemplate on its string, the player-mask walk (rva00357B82,
// getEachPlayerFromMask), the team prototype / instance / member walks,
// getSpecialPowerModule, canUseSpecialPower and the module's isReady and
// getReadyFrame slots (+0x04, +0x10). BFME2 skips members with status bit 2
// or any disabled bit (BitFlags<11> at +0x1C8) and scales the ten-second
// retry window by the frame-rate global 0x00DBA4E4.
//
// Codegen: retail tests the first member into EDI, jumps past the loop-top
// reload and compares the iterator in memory on the back edge. VC7.1 emits
// that only with Team::iterate_TeamMemberList (0x00263864) and
// DLINK_ITERATOR<Object>::advance (0x00263526) compiled in this unit over the
// virtual-inheritance Object skeleton (as AIPlayer::isSupplySourceAttacked and
// ScriptConditionsRva003E8E23.cpp). With the opaque 24-byte iterator of
// ScriptConditions_evaluateTeamStateIs.cpp the member stays in ECX and is
// copied (the 0.949 bank).

typedef bool Bool;
typedef int Int;

#include "ascii_string.h"

class ThingTemplate;
class Object;
class SpecialPowerTemplate;
class SpecialPowerModuleInterface;

class BfmeObjectVirtualTail { public: unsigned char m_vt[4]; };

class BfmeObjectVbptrCarrier : public virtual BfmeObjectVirtualTail
{
public:
	unsigned char m_carrier[4];
};

class BfmeObjectVtbl { public: virtual void bfmeObjectSlot0(); };

class BfmeObjectDlinkBase
{
public:
	Object *dlink_next_TeamMemberList() const;
};

class BfmeObjectThingPad
{
public:
	const ThingTemplate *getTemplate() const { return m_template; }
private:
	const ThingTemplate *m_template; // +0x00 Object+0x04
	unsigned char m_pad[0x64 - 4]; // +0x04
};

template <int NUMBITS>
class BitFlags
{
public:
	Bool any() const;
private:
	unsigned int m_bits[(NUMBITS + 31) / 32];
};
typedef BitFlags<11> DisabledMaskType;

enum ObjectStatusTypes
{
	OBJECT_STATUS_02 = 0x02
};

class Object : public BfmeObjectVtbl, public BfmeObjectDlinkBase,
	public BfmeObjectThingPad, public BfmeObjectVbptrCarrier
{
public:
	Bool testStatus(ObjectStatusTypes bit) const;
	Bool isDisabled() const { return m_disabledMask.any(); }
	SpecialPowerModuleInterface *getSpecialPowerModule(const SpecialPowerTemplate *power) const;
private:
	unsigned char m_pad[0x1C8 - 0x70];
	DisabledMaskType m_disabledMask; // +0x1C8
};

template <class OBJCLASS>
class DLINK_ITERATOR
{
public:
	typedef OBJCLASS* (OBJCLASS::*GetNextFunc)() const;
private:
	OBJCLASS* m_cur;
	GetNextFunc m_getNextFunc;
public:
	DLINK_ITERATOR(OBJCLASS* cur, GetNextFunc getNextFunc) : m_cur(cur), m_getNextFunc(getNextFunc)
	{
	}
	void advance()
	{
		if (m_cur)
			m_cur = ((*m_cur).*(m_getNextFunc))();
	}
	Bool done() const
	{
		return m_cur == 0;
	}
	OBJCLASS* cur() const
	{
		return m_cur;
	}
};

#include "../../../Include/Common/MemoryPoolObject.h"

#include "Common/Snapshot.h"

class Parameter
{
public:
	const AsciiString &getString() const { return m_string; }
	unsigned char m_beforeString[0x10];
	AsciiString m_string; // +0x10
	unsigned char m_pad14[0x20 - 0x14];
	Int m_cachedFrame; // +0x20
};

class Team : public MemoryPoolObject, public Snapshot
{
public:
	Team *dlink_next_TeamInstanceList() const;
	DLINK_ITERATOR<Object> iterate_TeamMemberList() const
	{
		return DLINK_ITERATOR<Object>(m_dlinkhead_TeamMemberList, &Object::dlink_next_TeamMemberList);
	}
private:
	unsigned char m_teamPad[0x38 - 8];
	Object *m_dlinkhead_TeamMemberList; // +0x38
};

class TeamPrototype
{
public:
	DLINK_ITERATOR<Team> iterate_TeamInstanceList() const
	{
		return DLINK_ITERATOR<Team>(m_dlinkhead_TeamInstanceList, &Team::dlink_next_TeamInstanceList);
	}
private:
	unsigned char m_pad[0x334];
	Team *m_dlinkhead_TeamInstanceList; // +0x334
};

struct PlayerTeamNode
{
	PlayerTeamNode *m_next;
	PlayerTeamNode *m_prev;
	TeamPrototype *m_value;
};

class Player
{
public:
	PlayerTeamNode *getPlayerTeams() const { return m_playerTeamPrototypes; }
private:
	char m_pad[0x32C];
	PlayerTeamNode *m_playerTeamPrototypes; // +0x32C
};

class PlayerList
{
public:
	Player *getEachPlayerFromMask(Int &mask);
};
extern PlayerList *ThePlayerList;

#include "../../../Include/GameLogic/ScriptEngine.h"
extern ScriptEngine *TheScriptEngine;

#include "../../Common/GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;

class SpecialPowerModuleInterface
{
public:
	virtual void slot00();
	virtual Bool isReady() const;
	virtual void slot08();
	virtual void slot0C();
	virtual unsigned int getReadyFrame() const;
};

class SpecialPowerStore
{
public:
	const SpecialPowerTemplate *findSpecialPowerTemplate(AsciiString name); // 0x0029B6EB
	Bool canUseSpecialPower(Object *obj, const SpecialPowerTemplate *power);
};
extern SpecialPowerStore *TheSpecialPowerStore;
extern Int BfmeLogicFramesPerSecond;

class ScriptConditions
{
protected:
	Bool evaluateSkirmishSpecialPowerIsReady(Parameter *pSkirmishPlayerParm, Parameter *pPower);
};

Bool ScriptConditions::evaluateSkirmishSpecialPowerIsReady(Parameter *pSkirmishPlayerParm, Parameter *pPower)
{
	if (pPower->m_cachedFrame == -1)
		return false;
	if (pPower->m_cachedFrame > 0 && (unsigned int)pPower->m_cachedFrame > TheGameLogic->getFrame())
		return false;
	unsigned int nextFrame = BfmeLogicFramesPerSecond * 10 + TheGameLogic->getFrame();
	const SpecialPowerTemplate *power = TheSpecialPowerStore->findSpecialPowerTemplate(pPower->getString());
	if (power == 0) {
		pPower->m_cachedFrame = -1;
		return false;
	}

	Int mask = TheScriptEngine->rva00357B82(pSkirmishPlayerParm);
	while (mask) {
		Player *pPlayer = ThePlayerList->getEachPlayerFromMask(mask);
		if (pPlayer == 0)
			continue;
		for (PlayerTeamNode *it = pPlayer->getPlayerTeams()->m_next; it != pPlayer->getPlayerTeams(); it = it->m_next) {
			for (DLINK_ITERATOR<Team> iter = it->m_value->iterate_TeamInstanceList(); !iter.done(); iter.advance()) {
				Team *team = iter.cur();
				if (!team)
					continue;
				for (DLINK_ITERATOR<Object> oiter = team->iterate_TeamMemberList(); !oiter.done(); oiter.advance()) {
					Object *pObj = oiter.cur();
					if (!pObj)
						continue;
					if (pObj->testStatus(OBJECT_STATUS_02) || pObj->isDisabled())
						continue;
					SpecialPowerModuleInterface *mod = pObj->getSpecialPowerModule(power);
					if (mod) {
						if (!TheSpecialPowerStore->canUseSpecialPower(oiter.cur(), power))
							continue;
						if (mod->isReady())
							return true;
						if (mod->getReadyFrame() < nextFrame)
							nextFrame = mod->getReadyFrame();
					}
				}
			}
		}
	}
	pPower->m_cachedFrame = nextFrame;
	return false;
}
