// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /GX
// SPDX-License-Identifier: GPL-3.0-or-later
// ZH/BFME1 BattlePlanUpdate::setBattlePlan semantic source at9cbfb551.
// Original target name is not asserted; WB helper11F6130 and callers from
// native setStatus497FF3 establish this BattlePlanUpdate member's purpose.
// Target-specific layout: module scalars8C/90/94, stealth98, health9C/A0;
// Object body254; bonus pointer40, affecting-army plan2C. Existing providers
// establish their ABI. Static StealthDetectorUpdate keys preserve native scopes.
typedef float Real;
typedef bool Bool;
enum BattlePlanStatus {PLANSTATUS_NONE,PLANSTATUS_BOMBARDMENT,PLANSTATUS_HOLDTHELINE,PLANSTATUS_SEARCHANDDESTROY};
enum MaxHealthChangeType { MAX_HEALTH_TYPE_DUMMY=0 };
enum NameKeyType { NAMEKEY_INVALID=0 };
class NameKeyGenerator { public: NameKeyType nameToKey(const char *); };
extern NameKeyGenerator *TheNameKeyGenerator;
class Module;
class Object;
class Rva002AA14DBonuses { public: Real m_armorScalar;int m_bombardment,m_searchAndDestroy,m_holdTheLine;Real m_sightRangeScalar;char masks[0x38]; };
class Player { public: void changeBattlePlan(BattlePlanStatus,int,Rva002AA14DBonuses *); int iterateObjects(int (__cdecl *)(Object *,void *),void *) const; };
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
class Object { public:
 Player *getControllingPlayer() const;
 Real getVisionRange() const; Real getShroudClearingRange() const;
 void setVisionRange(Real);void setShroudClearingRange(Real);
 Module *findModule(NameKeyType) const;
 char pad[0x254];BattlePlanBodyInterfaceView *m_body;
};
class Rva004A2D49 { public: void rva004A2D49(Bool); };
struct BattlePlanUpdateArmyDataView {
 char pad[0x8C];Real m_holdTheLineArmorDamageScalar,m_searchAndDestroySightRangeScalar,m_strategyCenterSearchAndDestroySightRangeScalar;
 Bool m_strategyCenterSearchAndDestroyDetectsStealth;char pad99[3];
 Real m_strategyCenterHoldTheLineMaxHealthScalar;MaxHealthChangeType m_strategyCenterHoldTheLineMaxHealthChangeType;
};
int __cdecl Rva004977B5(Object *,void *);
class BattlePlanUpdate { public:
 void rva00497AE8(BattlePlanStatus);
 const BattlePlanUpdateArmyDataView *getBattlePlanUpdateModuleData() const { return data; }
 Object *getObject() const { return object; }
 void *vtable;BattlePlanUpdateArmyDataView *data;Object *object;
 char pad0C[0x20];BattlePlanStatus m_planAffectingArmy;char pad30[0x10];Rva002AA14DBonuses *m_bonuses;
};
void BattlePlanUpdate::rva00497AE8( BattlePlanStatus plan )
{
	const BattlePlanUpdateArmyDataView *data = getBattlePlanUpdateModuleData();
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
