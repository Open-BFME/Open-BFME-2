// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /ICode/GameEngine/Include /Ireference/shims/bfme2_ascii
//
// ?rva00453652@GettingBuiltBehavior@@UAEX_N@Z, retail 0x00453652 (691 bytes):
// slot 4 of the GettingBuiltBehavior interface vftable 0x00C403C8 (this =
// GettingBuiltBehavior+0x20; layout as GettingBuiltBehaviorIfaceSlots.cpp,
// whose slot 21 walk calls this slot).  WorldBuilder twin 0x0116BF10
// (callgraph lead, unnamed).  Finishes construction of the owner: unless
// forced, the slot-7 check for the controlling player must pass; marks +0x32,
// runs the rowed 0x0045318B prepare step when not forced, fills +0x2C from
// the template's 0x0033AA1F when unset, latches the +0x438 bit into +0x35
// (moving objects out of the footprint through BuildAssistant and the
// player's +0x3BC list when set), resets +0x280 and the construction
// statuses, swaps model conditions 0x43 -> 0x44/0x45 when appropriate,
// clears conditions 5, 62 and 60, wakes the module, restarts the build loop
// sound chosen from module data +0x08/+0x0C/+0x10, updates upgrades,
// restores the body's health and marks the control bar dirty.
#include "ascii_string.h"
#include "Common/BfmeAudioEventPrefix136.h"

typedef float Real;
typedef int Int;
typedef unsigned int UnsignedInt;

enum ObjectID;

enum ObjectStatusTypes
{
	OBJECT_STATUS_UNDER_CONSTRUCTION = 2,
	OBJECT_STATUS_RECONSTRUCTING = 0x14,
	OBJECT_STATUS_57 = 0x57
};

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1
};

template <int N> class Rva00453652Slots : public Rva00453652Slots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class Rva00453652Slots<0>
{
};

class Player;
#include "../../../../Include/Common/ThingTemplate.h"

// Object +0x254: slot 4 the health, slot 5 the maximum, slot 42 a health set.
class Rva00453652Body : public Rva00453652Slots<4>
{
public:
	virtual Real getHealth() = 0;	// slot 4
	virtual Real getMaxHealth() = 0;	// slot 5
	virtual void gap6() = 0; virtual void gap7() = 0; virtual void gap8() = 0; virtual void gap9() = 0;
	virtual void gap10() = 0; virtual void gap11() = 0; virtual void gap12() = 0; virtual void gap13() = 0;
	virtual void gap14() = 0; virtual void gap15() = 0; virtual void gap16() = 0; virtual void gap17() = 0;
	virtual void gap18() = 0; virtual void gap19() = 0; virtual void gap20() = 0; virtual void gap21() = 0;
	virtual void gap22() = 0; virtual void gap23() = 0; virtual void gap24() = 0; virtual void gap25() = 0;
	virtual void gap26() = 0; virtual void gap27() = 0; virtual void gap28() = 0; virtual void gap29() = 0;
	virtual void gap30() = 0; virtual void gap31() = 0; virtual void gap32() = 0; virtual void gap33() = 0;
	virtual void gap34() = 0; virtual void gap35() = 0; virtual void gap36() = 0; virtual void gap37() = 0;
	virtual void gap38() = 0; virtual void gap39() = 0; virtual void gap40() = 0; virtual void gap41() = 0;
	virtual void rva00453652Slot42(Real health) = 0;	// slot 42
};

class Rva0010CBits
{
public:
	unsigned int test(int bit) const
	{
		return m_words[bit >> 5] & (1U << (bit & 0x1f));
	}
	void set(int bit) { m_words[bit >> 5] |= (1U << (bit & 0x1f)); }
	void clear(int bit)
	{
		m_words[bit >> 5] &= ~(1U << (bit & 0x1f));
	}
private:
	unsigned int m_words[19]; // +0x00
};

// Model condition set builders used for the 0x43 -> 0x44/0x45 swap.
class Rva001E4912
{
public:
	Rva001E4912 *rva001E4912(int a1, unsigned int a2, unsigned int a3); // 0x001E4912
	unsigned int m_words[19];
};

class Rva0028F59A
{
public:
	Rva0028F59A(Int a1, Int a2);	// 0x0028F59A
	unsigned int m_words[19];
};

// The controlling player's +0x3BC list.
class ScoreKeeper
{
public:
	void addObjectBuilt(class Object *obj, int a2); // 0x0039CBCE
};

class Object
{
public:
	Player *getControllingPlayer() const;	// 0x0028AFA9
	void setStatus(ObjectStatusTypes status, bool set);	// 0x0023DB0E
	void setEffectivelyDead(bool dead);	// 0x0028D2FB
	void rva0028CFB2(const Int *clearFlags, const Int *setFlags);	// 0x0028CFB2
	void setBuilder(const Object *obj);	// 0x0028AFE7
	void updateUpgradeModules();	// 0x00292EEA
	void rva0028AE6D();	// model-condition change notifier

	const ThingTemplate *getTemplate() const { return m_template; }
	const struct Coord3D *getPosition() const { return (const struct Coord3D *)m_position; }
	Real getOrientation() const { return m_orientation; }
	ObjectID getID() const { return m_id; }
	Rva00453652Body *getBodyModule() const { return m_body; }
	ScoreKeeper *rva00453652PlayerList(Player *player) const { return (ScoreKeeper *)((char *)player + 0x3BC); }
	__forceinline void clearModelConditionState(int mc)
	{
		if (m_conditionBits.test(mc))
		{
			m_conditionBits.clear(mc);
			rva0028AE6D();
		}
	}

	unsigned char m_pad000[0x04];
	const ThingTemplate *m_template;	// +0x04
	unsigned char m_pad008[0x38 - 0x08];
	float m_position[3];	// +0x38
	Real m_orientation;	// +0x44
	unsigned char m_pad048[0x74 - 0x48];
	ObjectID m_id;	// +0x74
	unsigned char m_pad078[0x10C - 0x78];
	Rva0010CBits m_conditionBits;	// +0x10C
	unsigned char m_pad158[0x254 - 0x158];
	Rva00453652Body *m_body;	// +0x254
	unsigned char m_pad258[0x280 - 0x258];
	Real m_constructionPercent;	// +0x280
	unsigned char m_pad284[0x436 - 0x284];
	bool m_436;	// +0x436
	unsigned char m_pad437;
	unsigned char m_438;	// +0x438
};

#include "../../../../Include/Common/BuildAssistantClass.h"
extern BuildAssistant *TheBuildAssistant;

#include "../../../../Include/Common/GameAudio.h"
extern AudioManager *TheAudio;

#include "../../../../Include/GameClient/ControlBar.h"
extern ControlBar *TheControlBar;

// A sound reference that releases what it holds.
struct Rva00453652Sound : public OpaqueRefElement4
{
};

class ModuleData;
#include "../../../../Include/GameLogic/Module/GettingBuiltBehaviorModuleData.h"

#include "../../../../Include/GameLogic/Module/BehaviorModule.h"
#include "../../../../Include/GameLogic/Module/UpdateModule.h"




class GettingBuiltBehaviorInterface : public Rva00453652Slots<4>
{
public:
	virtual void rva00453652(bool forced) = 0;	// slot 4
	virtual void gap5() = 0;
	virtual void gap6() = 0;
	virtual bool rva0045314E(Player *player) = 0;	// slot 7
};

class GettingBuiltBehavior : public UpdateModule, public GettingBuiltBehaviorInterface
{
public:
	virtual void rva00453652(bool forced);
	void rva0045318B();	// 0x0045318B

private:
	Object *getObject() const { return m_object; }
	const GettingBuiltBehaviorModuleData *data() const { return (const GettingBuiltBehaviorModuleData *)m_moduleData; }

	UnsignedInt m_soundHandle;	// +0x24
	Real m_28;	// +0x28
	Int m_2C;	// +0x2C
	bool m_30;	// +0x30
	bool m_31;	// +0x31
	bool m_32;	// +0x32
	bool m_33;	// +0x33
	bool m_34;	// +0x34
	bool m_35;	// +0x35
	bool m_36;	// +0x36
	Int m_38;	// +0x38
	bool m_3C;	// +0x3C
	bool m_3D;	// +0x3D
};

void GettingBuiltBehavior::rva00453652(bool forced)
{
	Object *obj = getObject();
	if (!obj)
		return;
	Player *player = obj->getControllingPlayer();
	if (!player)
		return;
	if (!forced && !rva0045314E(player))
		return;

	Real health = obj->getBodyModule()->getHealth();
	m_32 = true;
	if (!forced)
		rva0045318B();
	if (m_2C == 0)
		m_2C = obj->getTemplate()->calcTimeToBuild(player, 0, -1);

	m_35 = obj->m_438 & 1;
	if (m_35)
	{
		obj->rva00453652PlayerList(obj->getControllingPlayer())->addObjectBuilt(obj, 1);
		obj->m_436 = false;
		TheBuildAssistant->moveObjectsForConstruction(obj->getTemplate(), obj->getPosition(), obj->getOrientation(), player);
	}

	if (m_36)
	{
		obj->m_constructionPercent = -1.0f;
	}
	else
	{
		if (m_35)
			obj->m_constructionPercent = 0.0f;
		obj->setStatus(OBJECT_STATUS_57, false);
		if (m_33)
			obj->setStatus(OBJECT_STATUS_RECONSTRUCTING, true);
		obj->setStatus(OBJECT_STATUS_UNDER_CONSTRUCTION, true);
	}

	if (m_35 || m_36)
	{
		obj->setEffectivelyDead(false);
		m_33 = false;
	}
	else
	{
		obj->m_constructionPercent = obj->getBodyModule()->getMaxHealth() * 100.0f;
	}

	if (m_35 || (!m_33 && !m_36))
	{
		Rva001E4912 setFlags;
		obj->rva0028CFB2((const Int *)&Rva0028F59A(0, 0x43), (const Int *)setFlags.rva001E4912(0, 0x44, 0x45));
	}

	m_34 = false;
	obj->clearModelConditionState(5);
	obj->clearModelConditionState(62);
	obj->clearModelConditionState(60);
	obj->setBuilder(obj);
	m_3C = false;
	setWakeFrame(getObject(), UPDATE_SLEEP_NONE);

	const GettingBuiltBehaviorModuleData *gettingBuiltBehaviorModuleData = data();
	if (TheAudio)
	{
		if (m_soundHandle >= 5)
			TheAudio->removeAudioEvent(m_soundHandle);
		Rva00453652Sound sound;
		if (m_35)
		{
			if (gettingBuiltBehaviorModuleData->m_selfRepairFromRubbleLoop.referent)
				sound.OpaqueRefElement4::operator=(gettingBuiltBehaviorModuleData->m_selfRepairFromRubbleLoop);
		}
		else if (!m_33)
		{
			if (gettingBuiltBehaviorModuleData->m_selfBuildingLoop.referent)
				sound.OpaqueRefElement4::operator=(gettingBuiltBehaviorModuleData->m_selfBuildingLoop);
		}
		else
		{
			if (gettingBuiltBehaviorModuleData->m_selfRepairFromDamageLoop.referent)
				sound.OpaqueRefElement4::operator=(gettingBuiltBehaviorModuleData->m_selfRepairFromDamageLoop);
		}
		if (sound.referent)
		{
			BfmeAudioEventPrefix136 event(sound, obj->getID());
			m_soundHandle = TheAudio->addAudioEvent(&event);
		}
	}

	obj->updateUpgradeModules();
	obj->getBodyModule()->rva00453652Slot42(health);
	obj->setEffectivelyDead(false);
	TheControlBar->markUIDirty();
	m_3D = true;
}
