// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX -Ireference/open-bfme-1/game/GameEngine/Source/Common /ICode/GameEngine/Include /I. /Ireference/shims/bfme2_ascii
//
// ?onObjectCreated@BattlePlanUpdate@@UAEXXZ @0x0049797F 204B.
// Slot 5 (offset 0x14) of vtable 0x0084FBAC (class of ??1Rva004978A3 in
// BattlePlanUpdateRva004978A3Dtor.cpp). Calls FilteredFind 0x0028BB9E,
// OpaqueRefElement4 operator= 0x00239099 (10 copies), Object::setWeaponSetFlag
// 0x00290963, Object::setWeaponLock 0x00290B24 and BattlePlanUpdate::enableTurret
// 0x0049773F (rowed). Layout follows BattlePlanUpdate_enableTurret.cpp
// (m_object at +8, m_ai at +0x258 guarding the weapon lock).

// stlport
#include "Code/GameEngine/Source/Common/GameLogicObjectLookupView.h"
#include "Common/BfmeAudioEventPrefix136.h"
#include "Code/Libraries/Include/Lib/Coord3D.h"

class Drawable;
class Player;
class Rva002AA14DBonuses;
struct BattlePlanUpdateModuleData;
enum BattlePlanStatus
{
	PLANSTATUS_NONE = 0, NONE = PLANSTATUS_NONE,
	BOMBARDMENT, HOLDTHELINE, SEARCHANDDESTROY,
	PLANSTATUS_BOMBARDMENT = BOMBARDMENT,
	PLANSTATUS_HOLDTHELINE = HOLDTHELINE,
	PLANSTATUS_SEARCHANDDESTROY = SEARCHANDDESTROY
};

enum TransitionStatus { IDLE,UNPACKING,ACTIVE,PACKING };

enum DisabledType { DISABLED_PARALYZED=4 };

enum ObjectStatusTypes
{
	OBJECT_STATUS_8 = 8
};

enum NameKeyType
{
	NK_UNKNOWN = 0,
	NAMEKEY_INVALID = NK_UNKNOWN
};

class BattleModelFlags {
 unsigned long m_words[19];
public:
 __forceinline unsigned long test(int bit) const { return m_words[bit>>5] & (1ul<<(bit&31)); }
 __forceinline void set(int bit) { m_words[bit>>5] |= (1ul<<(bit&31)); }
 __forceinline void reset(int bit) { m_words[bit>>5] &= ~(1ul<<(bit&31)); }
};

enum WeaponSetType
{
	WST_0 = 0
};

enum WeaponSlotType
{
	WSLT_0 = 0
};

enum WeaponLockType
{
	WLT_0 = 0,
	WLT_1 = 1
};

class SpecialPowerTemplate;
class SpecialPowerModuleInterface;

class AIUpdateInterface;

class Module;
class BattlePlanBodyInterfaceView;

class Object
{
	friend class BattlePlanUpdate;
protected:
	Module *findModule(NameKeyType) const;
public:
	SpecialPowerModuleInterface *getSpecialPowerModule(const SpecialPowerTemplate *power) const;
	void setWeaponSetFlag(WeaponSetType type);
	bool setWeaponLock(WeaponSlotType slot, WeaponLockType lock);
	float getVisionRange() const;
	float getShroudClearingRange() const;
	void setVisionRange(float);
	void setShroudClearingRange(float);
	Player *getControllingPlayer() const;
public:
	Drawable *getDrawable() const;
public:
	void rva0028AE6D();
public:
	__forceinline void clearModelConditionState(int bit) {
  if(m_modelConditionFlags.test(bit)) { m_modelConditionFlags.reset(bit); rva0028AE6D(); }
 }
public:
	__forceinline void setModelConditionState(int bit) {
  if(!m_modelConditionFlags.test(bit)) { m_modelConditionFlags.set(bit); rva0028AE6D(); }
 }
public:
	const Coord3D *getPosition() const { return &position; }
public:
	ObjectID getID() const { return id; }
public:
	AIUpdateInterface *getAI();
public:
	char pad00[0x38];
public:
	Coord3D position;
public:
	char pad44[0x74-0x44];
public:
	ObjectID id;
public:
	char pad78[0x10C-0x78];
public:
	BattleModelFlags m_modelConditionFlags;
public:
	char pad158[0x254-0x158];
public:
	BattlePlanBodyInterfaceView *m_body; // +0x254
public:
	AIUpdateInterface *m_aiDirect; // +0x258
public:
	void setDisabledUntil(DisabledType,unsigned);
public:
	void setStatus(ObjectStatusTypes status, bool set);
};



struct Payload0049797F
{
	char m_pad00[8];
	void *m_specialPowerTemplate; // +0x08
	char m_pad0C[0x1c - 0x0c];
	OpaqueRefElement4 m_bombardmentUnpackName; // +0x1c
	OpaqueRefElement4 m_bombardmentPackName; // +0x20
	char m_pad24[4];
	OpaqueRefElement4 m_bombardmentAnnouncementName; // +0x28
	OpaqueRefElement4 m_searchAndDestroyUnpackName; // +0x2c
	OpaqueRefElement4 m_searchAndDestroyIdleName; // +0x30
	OpaqueRefElement4 m_searchAndDestroyPackName; // +0x34
	char m_pad38[4];
	OpaqueRefElement4 m_searchAndDestroyAnnouncementName; // +0x3c
	OpaqueRefElement4 m_holdTheLineUnpackName; // +0x40
	OpaqueRefElement4 m_holdTheLinePackName; // +0x44
	char m_pad48[4];
	OpaqueRefElement4 m_holdTheLineAnnouncementName; // +0x4c
};

class BattlePlanUpdate
{
public:
	virtual NameKeyType getModuleNameKey() const;
	virtual void onObjectCreated();
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

	// The virtual getter supplies the compiler-owned vptr at +0x00.
	BattlePlanUpdateModuleData *data; // +0x04 (unmapped Module base member)
	Object *m_object; // +0x08
	char m_pad0C[0x24 - 0x0C];
	BattlePlanStatus m_currentPlan; // +0x24
	BattlePlanStatus m_desiredPlan; // +0x28
	BattlePlanStatus m_planAffectingArmy; // +0x2C
	TransitionStatus m_status; // +0x30
	unsigned m_nextReadyFrame; // +0x34
	SpecialPowerModuleInterface *m_specialPowerModule; // +0x38
	bool m_invalidSettings; // +0x3C
	bool m_centeringTurret; // +0x3D
	Rva002AA14DBonuses *m_bonuses; // +0x40
	OpaqueRefElement4 unpack[4], pack[4], announcement[4], idle[4]; // +0x44..+0x83
	unsigned m_handle84; // +0x84
	ObjectID m_visionObjectID; // +0x88
};

void BattlePlanUpdate::onObjectCreated()
{
	Payload0049797F *payload = (Payload0049797F *)data;
	Object *obj = m_object;
	void *key = payload->m_specialPowerTemplate;
	if (key == 0)
	{
		m_invalidSettings = true;
	}
	else
	{
		m_specialPowerModule = obj->getSpecialPowerModule(reinterpret_cast<const SpecialPowerTemplate *>(key));
		unpack[BOMBARDMENT] = payload->m_bombardmentUnpackName;
		pack[BOMBARDMENT] = payload->m_bombardmentPackName;
		announcement[BOMBARDMENT] = payload->m_bombardmentAnnouncementName;
		unpack[SEARCHANDDESTROY] = payload->m_searchAndDestroyUnpackName;
		pack[SEARCHANDDESTROY] = payload->m_searchAndDestroyPackName;
		idle[SEARCHANDDESTROY] = payload->m_searchAndDestroyIdleName;
		announcement[SEARCHANDDESTROY] = payload->m_searchAndDestroyAnnouncementName;
		unpack[HOLDTHELINE] = payload->m_holdTheLineUnpackName;
		pack[HOLDTHELINE] = payload->m_holdTheLinePackName;
		announcement[HOLDTHELINE] = payload->m_holdTheLineAnnouncementName;
		m_object->setWeaponSetFlag(WST_0);
		if (obj->m_aiDirect != 0)
			obj->setWeaponLock(WSLT_0, WLT_1);
		enableTurret(false);
	}
}
