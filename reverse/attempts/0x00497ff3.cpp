// ?setStatus@BattlePlanUpdate@@IAEXW4TransitionStatus@@@Z
// partial score=0.9237408 date=2026-10-09
// ?setStatus@BattlePlanUpdate@@IAEXW4TransitionStatus@@@Z
// partial score=0.98 date=2026-10-09
// stlport
// cl: /O1 /G7 /D_STLP_NO_EXCEPTIONS /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /I.
//
// BattlePlanUpdate.cpp: BattlePlanUpdate bodies retail links from this TU
// (tu_map approved). The turret helpers were folded in from split units with
// these exact flags; one BattlePlanUpdate view carries the offsets each body
// was verified against: +0x08 object, +0x2C affecting army, +0x30 status.
// getCommandOption stays split: it reads its plan through the interface
// subobject (+0x08 of that base), which this view cannot express.
// onObjectCreated (0x0049797F) stays split for now: it calls
// Object::setWeaponLock, whose kept definition is not retail's, and folding it
// would stop this unit linking.

// Status semantic donor: BFME1 BattlePlanUpdateSetStatus.cpp at 9cbfb551.
// BFME2 1241B native 497FF3 follows ZH transition switches, but stores one
// playing handle at84 and four banks of ref-counted audio names at44..80.
#include "Common/BfmeAudioEventPrefix136.h"
#include "unicode_string.h"
#include "Code/GameEngine/Source/Common/GameLogicObjectLookupView.h"
#include "Code/Libraries/Include/Lib/Coord3D.h"
#include <bitset>
class Player { public: char pad[0x54]; int index; };
class Drawable { public: void setAnimationLoopDuration(unsigned); };
// Native uses nineteen DWORDs for the 591-bit model-condition mask.
// The only accesses here are proven fixed indices21..32 from the donor;
// spell their BitFlags operations directly to keep the native inlined form.
class BattleModelFlags {
 unsigned long m_words[19];
public:
 __forceinline unsigned long test(int bit) const { return m_words[bit>>5] & (1ul<<(bit&31)); }
 __forceinline void set(int bit) { m_words[bit>>5] |= (1ul<<(bit&31)); }
 __forceinline void reset(int bit) { m_words[bit>>5] &= ~(1ul<<(bit&31)); }
};
enum TransitionStatus { IDLE,UNPACKING,ACTIVE,PACKING };
struct BattlePlanUpdateModuleData {
 char pad00[0xC];
 unsigned m_bombardmentPlanAnimationFrames,m_holdTheLinePlanAnimationFrames,
 m_searchAndDestroyPlanAnimationFrames,m_transitionIdleFrames;
 char pad1C[8]; AsciiString m_bombardmentMessageLabel; //24
 char pad28[0x10]; AsciiString m_searchAndDestroyMessageLabel; //38
 char pad3C[0xC]; AsciiString m_holdTheLineMessageLabel; //48
};
class AudioManager {
public:
 virtual void slot0();
 virtual void slot1();
 virtual void slot2();
 virtual void slot3();
 virtual void slot4();
 virtual void slot5();
 virtual void slot6();
 virtual void slot7();
 virtual void slot8();
 virtual void slot9();
 virtual void slot10();
 virtual void slot11();
 virtual void slot12();
 virtual void slot13();
 virtual void slot14();
 virtual void slot15();
 virtual void slot16();
 virtual void slot17();
 virtual void slot18();
 virtual void slot19();
 virtual void slot20();
 virtual void slot21();
 virtual void slot22();
 virtual void slot23();
 virtual void slot24();
 virtual int addAudioEvent(const BfmeAudioEventPrefix136 *);
 virtual void slot26(); virtual void removeAudioEvent(unsigned);
};
class GameTextInterface {
public:
 virtual void slot0();
 virtual void slot1();
 virtual void slot2();
 virtual void slot3();
 virtual void slot4();
 virtual void slot5();
 virtual void slot6();
 virtual void slot7();
 virtual void slot8();
 virtual void slot9();
 virtual void slot10();
 virtual void slot11();
 virtual void slot12();
 virtual void slot13();
 virtual UnicodeString fetch(const AsciiString &,bool *);
};
class InGameUI {
public:
 virtual void slot0();
 virtual void slot1();
 virtual void slot2();
 virtual void slot3();
 virtual void slot4();
 virtual void slot5();
 virtual void slot6();
 virtual void slot7();
 virtual void slot8();
 virtual void slot9();
 virtual void slot10();
 virtual void slot11();
 virtual void slot12();
 virtual void slot13();
 virtual void slot14();
 virtual void slot15();
 virtual void __cdecl message(UnicodeString,...);
};
struct Rva002D893BColorSource;
enum RadarEventType { RADAR_EVENT_BATTLE_PLAN=7 };
class Radar { public: void rva002D893B(const Rva002D893BColorSource *,const Coord3D *,RadarEventType,float); };
class Rva0033F15DDwordSlot { public: void set(int); };
extern AudioManager *TheAudio; extern GameLogic *TheGameLogic;
extern GameTextInterface *TheGameText; extern InGameUI *TheInGameUI;
extern Radar *TheRadar;
enum BattlePlanStatus
{
	PLANSTATUS_NONE = 0, NONE=0, BOMBARDMENT, HOLDTHELINE, SEARCHANDDESTROY
};

enum WhichTurretType
{
	TURRET_INVALID = -1,

	TURRET_MAIN = 0,
	TURRET_ALT,

	MAX_TURRETS
};

class AIUpdateInterface
{
public:
	WhichTurretType getWhichTurretForCurWeapon() const;
	bool isTurretInNaturalPosition(WhichTurretType tur) const;
	void recenterTurret(WhichTurretType tur);
	void setTurretEnabled(WhichTurretType tur, bool enabled);
};

class Object
{
public:
 Player *getControllingPlayer() const;
 Drawable *getDrawable() const;
 void rva0028AE6D();
 __forceinline void clearModelConditionState(int bit) {
  if(m_modelConditionFlags.test(bit)) { m_modelConditionFlags.reset(bit); rva0028AE6D(); }
 }
 __forceinline void setModelConditionState(int bit) {
  if(!m_modelConditionFlags.test(bit)) { m_modelConditionFlags.set(bit); rva0028AE6D(); }
 }

 const Coord3D *getPosition() const { return &position; }
 ObjectID getID() const { return id; }

	// Declaration only: the retail copy lives in Object.cpp (0x00313EB6) and
	// reads m_ai at +0x19C. Defining it here would emit a second COMDAT copy.
	AIUpdateInterface *getAI();

public:
	char pad00[0x38]; Coord3D position;
 char pad44[0x74-0x44]; ObjectID id;
 char pad78[0x10C-0x78]; BattleModelFlags m_modelConditionFlags;
 char pad158[0x258-0x158];	// vtable + members ahead of m_aiDirect
	AIUpdateInterface *m_aiDirect;	// +0x258 (retail-measured direct AI slot, not the +0x19C getAI member)
};

// recenterTurret's host: this body reads its AI cell at +0x258 through an
// inline accessor, while the rowed Object::getAI (0x00313EB6) reads +0x19C.
class Rva00497769Host
{
public:
	AIUpdateInterface *getAI() { return m_ai; }

private:
	char pad00[0x38]; Coord3D position;
 char pad44[0x74-0x44]; ObjectID id;
 char pad78[0x10C-0x78]; BattleModelFlags m_modelConditionFlags;
 char pad158[0x258-0x158];	// vtable + members ahead of m_ai
	AIUpdateInterface *m_ai;	// +0x258
};

class BattlePlanUpdate
{
public:
	BattlePlanStatus getActiveBattlePlan() const;
 void createVisionObject();
 void rva00497AE8(BattlePlanStatus); // native status transition's army-bonus helper; original name uncertain


protected:
	void setStatus(TransitionStatus);
 void enableTurret(bool enable);
	void recenterTurret();
	bool isTurretInNaturalPosition();

private:
	Object *getObject() { return m_object; }
 const BattlePlanUpdateModuleData *getBattlePlanUpdateModuleData() const { return data; }

	void *m_vtable; // +0x00
	BattlePlanUpdateModuleData *data; // +0x04 (unmapped Module base member)
	Object *m_object; // +0x08
	char m_pad0C[0x24 - 0x0C];
 BattlePlanStatus m_currentPlan;
 int m_pad28;
	int m_planAffectingArmy;	// +0x2C
	TransitionStatus m_status; //+30
 unsigned m_nextReadyFrame; char pad38[0xC];
 OpaqueRefElement4 unpack[4],pack[4],announcement[4],idle[4];
 unsigned m_handle84;
};

// ?enableTurret@BattlePlanUpdate@@IAEX_N@Z, retail 0x0049773F (42B).
// Ported from the Zero Hour reference
// (GameLogic/Object/Update/BattlePlanUpdate.cpp): fetch the object's AI,
// ask it which turret the current weapon uses, and enable or disable that
// turret. A missing AI or an invalid turret changes nothing.
void BattlePlanUpdate::enableTurret(bool enable)
{
	AIUpdateInterface *ai = getObject()->m_aiDirect;
	if (ai)
	{
		WhichTurretType tur = ai->getWhichTurretForCurWeapon();
		if (tur != TURRET_INVALID)
		{
			ai->setTurretEnabled(tur, enable);
		}
	}
}

// ?recenterTurret@BattlePlanUpdate@@IAEXXZ, retail 0x00497769 (36B).
// Ported from the Zero Hour reference: fetch the object's AI, ask it which
// turret the current weapon uses, and recenter that turret. A missing AI or an
// invalid turret recenters nothing.
void BattlePlanUpdate::recenterTurret()
{
	AIUpdateInterface *ai = ((Rva00497769Host *)getObject())->getAI();
	if (ai)
	{
		WhichTurretType tur = ai->getWhichTurretForCurWeapon();
		if (tur != TURRET_INVALID)
		{
			ai->recenterTurret(tur);
		}
	}
}

// ?isTurretInNaturalPosition@BattlePlanUpdate@@IAE_NXZ, retail 0x0049778D (40B).
// Ported from the Zero Hour reference: fetch the object's AI, ask it which
// turret the current weapon uses, and report whether that turret sits in its
// natural position. A missing AI or an invalid turret reads as not in position.
bool BattlePlanUpdate::isTurretInNaturalPosition()
{
	AIUpdateInterface *ai = getObject()->m_aiDirect;
	if (ai)
	{
		WhichTurretType tur = ai->getWhichTurretForCurWeapon();
		if (tur != TURRET_INVALID)
		{
			return ai->isTurretInNaturalPosition(tur);
		}
	}
	return false;
}

// ?getActiveBattlePlan@BattlePlanUpdate@@QBE?AW4BattlePlanStatus@@XZ
// BFME2 BattlePlanUpdate active-plan getter, transferred from the exact
// BFME1 reconstruction
// (Code/GameEngine/Source/GameLogic/Object/Update/BattlePlanUpdate.cpp).
// Retail BFME2 keeps the same fields: the affecting army at +0x2C and the
// transition status at +0x30; only the active status reads the army.
BattlePlanStatus BattlePlanUpdate::getActiveBattlePlan() const
{
	if (m_status == 2)
	{
		return (BattlePlanStatus)m_planAffectingArmy;
	}
	return PLANSTATUS_NONE;
}

// ?setStatus@BattlePlanUpdate@@IAEXW4TransitionStatus@@@Z present-unmatched
void BattlePlanUpdate::setStatus(TransitionStatus newStatus)
{
    const BattlePlanUpdateModuleData *modData = getBattlePlanUpdateModuleData();
    Object *obj = getObject();
    if (m_status == newStatus)
        return;
    TransitionStatus oldStatus = m_status;
    TheAudio->removeAudioEvent(m_handle84);
    m_handle84=1;
    switch (oldStatus)
    {
    case UNPACKING:
        switch (m_currentPlan)
        {
        case BOMBARDMENT:
            obj->clearModelConditionState(21);
            break;
        case HOLDTHELINE:
            obj->clearModelConditionState(25);
            break;
        case SEARCHANDDESTROY:
            obj->clearModelConditionState(29);
            break;
        }
        break;
    case ACTIVE:
        switch (m_currentPlan)
        {
        case BOMBARDMENT:
            obj->clearModelConditionState(24);
            break;
        case HOLDTHELINE:
            obj->clearModelConditionState(28);
            break;
        case SEARCHANDDESTROY:
            obj->clearModelConditionState(32);
            break;
        }
        break;
    case PACKING:
        switch (m_currentPlan)
        {
        case BOMBARDMENT:
            obj->clearModelConditionState(22);
            break;
        case HOLDTHELINE:
            obj->clearModelConditionState(26);
            break;
        case SEARCHANDDESTROY:
            obj->clearModelConditionState(30);
            break;
        }
        break;
    }
    unsigned now = TheGameLogic->getFrame();
    switch (newStatus)
    {
    case IDLE:
        m_currentPlan = NONE;
        m_nextReadyFrame = now + modData->m_transitionIdleFrames;
        break;
    case UNPACKING:
        TheRadar->rva002D893B((const Rva002D893BColorSource *)obj->getControllingPlayer(),obj->getPosition(),RADAR_EVENT_BATTLE_PLAN,4.0f);
        createVisionObject();
        switch (m_currentPlan)
        {
        case BOMBARDMENT:
            obj->setModelConditionState(21);
            obj->getDrawable()->setAnimationLoopDuration(modData->m_bombardmentPlanAnimationFrames);
            m_nextReadyFrame = now + modData->m_bombardmentPlanAnimationFrames;
            TheInGameUI->message(TheGameText->fetch(modData->m_bombardmentMessageLabel, 0));
            break;
        case HOLDTHELINE:
            obj->setModelConditionState(25);
            obj->getDrawable()->setAnimationLoopDuration(modData->m_holdTheLinePlanAnimationFrames);
            m_nextReadyFrame = now + modData->m_holdTheLinePlanAnimationFrames;
            TheInGameUI->message(TheGameText->fetch(modData->m_holdTheLineMessageLabel, 0));
            break;
        case SEARCHANDDESTROY:
            obj->setModelConditionState(29);
            obj->getDrawable()->setAnimationLoopDuration(
                modData->m_searchAndDestroyPlanAnimationFrames);
            m_nextReadyFrame = now + modData->m_searchAndDestroyPlanAnimationFrames;
            TheInGameUI->message(TheGameText->fetch(modData->m_searchAndDestroyMessageLabel, 0));
            break;
        }
        {
            if (unpack[m_currentPlan].referent) {
                BfmeAudioEventPrefix136 event(unpack[m_currentPlan],obj->getID());
                ((Rva0033F15DDwordSlot *)&event)->set(obj->getControllingPlayer()->index);
                m_handle84=TheAudio->addAudioEvent(&event);
            }
        }
        {
            if (announcement[m_currentPlan].referent) {
                BfmeAudioEventPrefix136 event(announcement[m_currentPlan],obj->getID());
                ((Rva0033F15DDwordSlot *)&event)->set(obj->getControllingPlayer()->index);
                TheAudio->addAudioEvent(&event);
            }
        }
        break;
    case ACTIVE:
        rva00497AE8(m_currentPlan);
        switch (m_currentPlan)
        {
        case BOMBARDMENT:
            obj->setModelConditionState(24);
            break;
        case HOLDTHELINE:
            obj->setModelConditionState(28);
            break;
        case SEARCHANDDESTROY:
            obj->setModelConditionState(32);
            break;
        }
        {
            if (idle[m_currentPlan].referent) {
                BfmeAudioEventPrefix136 event(idle[m_currentPlan],obj->getID());
                ((Rva0033F15DDwordSlot *)&event)->set(obj->getControllingPlayer()->index);
                m_handle84=TheAudio->addAudioEvent(&event);
            }
        }
        break;
    case PACKING:
        rva00497AE8(NONE);
        switch (m_currentPlan)
        {
        case BOMBARDMENT:
            obj->setModelConditionState(22);
            obj->getDrawable()->setAnimationLoopDuration(modData->m_bombardmentPlanAnimationFrames);
            m_nextReadyFrame = now + modData->m_bombardmentPlanAnimationFrames;
            break;
        case HOLDTHELINE:
            obj->setModelConditionState(26);
            obj->getDrawable()->setAnimationLoopDuration(modData->m_holdTheLinePlanAnimationFrames);
            m_nextReadyFrame = now + modData->m_holdTheLinePlanAnimationFrames;
            break;
        case SEARCHANDDESTROY:
            obj->setModelConditionState(30);
            obj->getDrawable()->setAnimationLoopDuration(
                modData->m_searchAndDestroyPlanAnimationFrames);
            m_nextReadyFrame = now + modData->m_searchAndDestroyPlanAnimationFrames;
            break;
        }
        {
            if (pack[m_currentPlan].referent) {
                BfmeAudioEventPrefix136 event(pack[m_currentPlan],obj->getID());
                ((Rva0033F15DDwordSlot *)&event)->set(obj->getControllingPlayer()->index);
                m_handle84=TheAudio->addAudioEvent(&event);
            }
        }
        break;
    }
    m_status = newStatus;
}
