// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX -Ireference/open-bfme-1/game/GameEngine/Source/Common /ICode/GameEngine/Include /I. /Ireference/shims/bfme2_ascii
// SPDX-License-Identifier: GPL-3.0-or-later
// ZH/BFME1 BattlePlanUpdate::setBattlePlan semantic source at9cbfb551.
// Original target name is not asserted; WB helper11F6130 and callers from
// native setStatus497FF3 establish this BattlePlanUpdate member's purpose.
// Target-specific layout: module scalars8C/90/94, stealth98, health9C/A0;
// Object body254; bonus pointer40, affecting-army plan2C. Existing providers
// establish their ABI. Static StealthDetectorUpdate keys preserve native scopes.
// stlport
#include "Code/GameEngine/Source/Common/GameLogicObjectLookupView.h"
#include "Common/BfmeAudioEventPrefix136.h"
#include "Code/Libraries/Include/Lib/Coord3D.h"

class AIUpdateInterface;
class Drawable;
class SpecialPowerTemplate;
class SpecialPowerModuleInterface;
struct BattlePlanUpdateModuleData;
enum TransitionStatus { IDLE,UNPACKING,ACTIVE,PACKING };

enum DisabledType { DISABLED_PARALYZED=4 };

enum ObjectStatusTypes
{
	OBJECT_STATUS_8 = 8
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

class BattleModelFlags {
 unsigned long m_words[19];
public:
 __forceinline unsigned long test(int bit) const { return m_words[bit>>5] & (1ul<<(bit&31)); }
 __forceinline void set(int bit) { m_words[bit>>5] |= (1ul<<(bit&31)); }
 __forceinline void reset(int bit) { m_words[bit>>5] &= ~(1ul<<(bit&31)); }
};

typedef float Real;
typedef int Int;
typedef bool Bool;
enum BattlePlanStatus
{
	PLANSTATUS_NONE = 0, NONE = PLANSTATUS_NONE,
	BOMBARDMENT, HOLDTHELINE, SEARCHANDDESTROY,
	PLANSTATUS_BOMBARDMENT = BOMBARDMENT,
	PLANSTATUS_HOLDTHELINE = HOLDTHELINE,
	PLANSTATUS_SEARCHANDDESTROY = SEARCHANDDESTROY
};
enum MaxHealthChangeType { MAX_HEALTH_TYPE_DUMMY=0 };
enum NameKeyType
{
	NK_UNKNOWN = 0,
	NAMEKEY_INVALID = NK_UNKNOWN
};
class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};
extern NameKeyGenerator *TheNameKeyGenerator;
class Module;
class Object;
class Rva0024C7B3Member
{
public:
	Rva0024C7B3Member();

	unsigned char m_data[0x1C];
};

class Rva002AA14DBonuses
{
public:
	Rva002AA14DBonuses() throw();

	Real m_armorScalar; // +0x00
	Int m_bombardment; // +0x04
	Int m_searchAndDestroy; // +0x08
	Int m_holdTheLine; // +0x0C
	Real m_sightRangeScalar; // +0x10
	Rva0024C7B3Member m_validKindOf; // +0x14
	Rva0024C7B3Member m_invalidKindOf; // +0x30
};
class Team;
class Player
{
public:
	void changeBattlePlan(BattlePlanStatus,int,Rva002AA14DBonuses *);
	int iterateObjects(int (__cdecl *)(Object *,void *),void *) const;
	char m_pad00[0x54];
	int index; // +0x54
	char m_pad58[0x294];
	Team *m_team; // +0x2EC +0x2ec
};
class BattlePlanBodyInterfaceView { public:
 virtual void slot0();
 virtual void slot1();
 virtual void slot2();
 virtual void slot3();
 virtual void slot4();
 virtual void slot5();
 virtual Real getMaxHealth();
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
 virtual void setMaxHealth(Real,MaxHealthChangeType);
};
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
class Rva004A2D49 { public: void rva004A2D49(Bool); };
struct BattlePlanUpdateArmyDataView {
 char pad[0x8C];Real m_holdTheLineArmorDamageScalar,m_searchAndDestroySightRangeScalar,m_strategyCenterSearchAndDestroySightRangeScalar;
 Bool m_strategyCenterSearchAndDestroyDetectsStealth;char pad99[3];
 Real m_strategyCenterHoldTheLineMaxHealthScalar;MaxHealthChangeType m_strategyCenterHoldTheLineMaxHealthChangeType;
};
int __cdecl Rva004977B5(Object *,void *);
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
void BattlePlanUpdate::rva00497AE8( BattlePlanStatus plan )
{
	const BattlePlanUpdateArmyDataView *data = (const BattlePlanUpdateArmyDataView *)getBattlePlanUpdateModuleData();
	const BattlePlanUpdateArmyDataView *retailData =
		(const BattlePlanUpdateArmyDataView *)data;
	Object *obj = getObject();
	Player *player = obj->getControllingPlayer();
	if( player )
	{
		switch( m_planAffectingArmy )
		{
			case PLANSTATUS_BOMBARDMENT:
			{
				//Remove the previous plan!
				player->changeBattlePlan( PLANSTATUS_BOMBARDMENT, -1, m_bonuses );

				//The only building bonus is actually the turret, and that's already handled!
				break;
			}
			case PLANSTATUS_HOLDTHELINE:
			{
				//Remove the previous plan!
				player->changeBattlePlan( PLANSTATUS_HOLDTHELINE, -1, m_bonuses );

				//Remove building health bonuses
				if( retailData->m_strategyCenterHoldTheLineMaxHealthScalar != 1.0f )
				{
					BattlePlanBodyInterfaceView *body = obj->m_body;
					body->setMaxHealth( body->getMaxHealth() * 1.0f / retailData->m_strategyCenterHoldTheLineMaxHealthScalar, retailData->m_strategyCenterHoldTheLineMaxHealthChangeType );
				}
				break;
			}
			case PLANSTATUS_SEARCHANDDESTROY:
			{
				//Remove the previous plan!
				player->changeBattlePlan( PLANSTATUS_SEARCHANDDESTROY, -1, m_bonuses );

				//Remove sight range bonus
				if( retailData->m_strategyCenterSearchAndDestroySightRangeScalar != 1.0f )
				{
					obj->setVisionRange( obj->getVisionRange() * 1.0f / retailData->m_strategyCenterSearchAndDestroySightRangeScalar );
					obj->setShroudClearingRange( obj->getShroudClearingRange() * 1.0f / retailData->m_strategyCenterSearchAndDestroySightRangeScalar );
				}

				//Remove stealth detection
				if( retailData->m_strategyCenterSearchAndDestroyDetectsStealth )
				{
					static NameKeyType key_StealthDetectorUpdate = TheNameKeyGenerator->nameToKey( "StealthDetectorUpdate" );
					Rva004A2D49 *update = (Rva004A2D49*)obj->findModule( key_StealthDetectorUpdate );
					if( update )
					{
						update->rva004A2D49( false );
					}
				}

				break;
			}
		}

		//Revert to default no-bonuses!
		m_bonuses->m_armorScalar = 1.0f;
		m_bonuses->m_sightRangeScalar = 1.0f;
		m_bonuses->m_bombardment = 0;
		m_bonuses->m_searchAndDestroy = 0;
		m_bonuses->m_holdTheLine = 0;

		//Add new bonuses!
		switch( plan )
		{
			case PLANSTATUS_NONE:
				//Paralyze troops!
				player->iterateObjects( Rva004977B5, (void*)data );
				break;
			case PLANSTATUS_BOMBARDMENT:
				//Set the bombardment bonuses
				m_bonuses->m_bombardment = 1; //for weapon bonuses

				//Add the new plan!
				player->changeBattlePlan( PLANSTATUS_BOMBARDMENT, 1, m_bonuses );
				break;

			case PLANSTATUS_HOLDTHELINE:
				//Add building health bonuses
				if( retailData->m_strategyCenterHoldTheLineMaxHealthScalar )
				{
					BattlePlanBodyInterfaceView *body = obj->m_body;
					body->setMaxHealth( body->getMaxHealth() * retailData->m_strategyCenterHoldTheLineMaxHealthScalar, retailData->m_strategyCenterHoldTheLineMaxHealthChangeType );
				}

				//Set the hold-the-line bonuses
				m_bonuses->m_armorScalar = retailData->m_holdTheLineArmorDamageScalar;
				m_bonuses->m_holdTheLine = 1; //for weapon bonuses

				//Add the new plan!
				player->changeBattlePlan( PLANSTATUS_HOLDTHELINE, 1, m_bonuses );
				break;
			case PLANSTATUS_SEARCHANDDESTROY:
				//Add sight range bonus
				if( retailData->m_strategyCenterSearchAndDestroySightRangeScalar != 1.0f )
				{
					obj->setVisionRange( obj->getVisionRange() * retailData->m_strategyCenterSearchAndDestroySightRangeScalar );
					obj->setShroudClearingRange( obj->getShroudClearingRange() * retailData->m_strategyCenterSearchAndDestroySightRangeScalar );
				}

				//Enable stealth detection
				if( retailData->m_strategyCenterSearchAndDestroyDetectsStealth )
				{
					static NameKeyType key_StealthDetectorUpdate = TheNameKeyGenerator->nameToKey( "StealthDetectorUpdate" );
					Rva004A2D49 *update = (Rva004A2D49*)obj->findModule( key_StealthDetectorUpdate );
					if( update )
					{
						update->rva004A2D49( true );
					}
				}

				//Set the search-and-destroy bonuses
				m_bonuses->m_searchAndDestroy = 1; //for weapon bonuses
				m_bonuses->m_sightRangeScalar = retailData->m_searchAndDestroySightRangeScalar;

				//Add the new plan!
				player->changeBattlePlan( PLANSTATUS_SEARCHANDDESTROY, 1, m_bonuses );
				break;
		}
		m_planAffectingArmy = plan;
	}
}
