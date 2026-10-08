// cl: /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc
// Retail 0x00456C1F, 593B: BridgeBehavior::onBodyDamageStateChange, entered
// through the DamageModuleInterface subobject at BridgeBehavior+0x24 (the
// object is this-0x1C, resolveFX and doAreaEffects are called on this-0x24,
// the death frame is +0x104 and the resolved flag +0xFC).
// Body: Zero Hour's onBodyDamageStateChange (GeneralsMD GameEngine/Source/
// GameLogic/Object/Behavior/BridgeBehavior.cpp). BFME 2 deltas: the sound is
// a local audio event built from the bridge template's repaired/damaged sound
// entries (TerrainRoadType+0xD4/+0x64 indexed by the new state, guarded by a
// template null test), stamped with the object id (0x002D9531) and passed to
// TheAudio slot 0x64; the OCL/FX tables are BridgeBehavior+0x3C/+0x6C
// (damage) and +0x9C/+0xCC (repair). TerrainLogic slot 0xC4 is
// updateBridgeDamageStates and Radar slot 0x14 queueTerrainRefresh.

#include "ascii_string.h"
#include "Common/BfmeAudioEventPrefix136.h"

typedef int Int;
typedef bool Bool;

enum BodyDamageType
{
	BODY_PRISTINE = 0,
	BODY_RUBBLE = 3
};

enum ObjectID
{
	INVALID_ID = 0
};

struct Coord3D;
class DamageInfo;
class ObjectCreationList;
class FXList;

class Object
{
public:
	const Coord3D *getPosition() const { return (const Coord3D *)m_pos; }
	ObjectID getID() const { return m_id; }
	unsigned char m_pad00[0x38];
	unsigned char m_pos[12];
	unsigned char m_pad44[0x74 - 0x44];
	ObjectID m_id;
};

class TerrainRoadType
{
public:
	unsigned char m_pad00[0x64];
	OpaqueRefElement4 m_damageToSound[4];
	unsigned char m_pad74[0xD4 - 0x74];
	OpaqueRefElement4 m_repairedToSound[4];
};

struct Rva002DB4DANode;

// TheTerrainRoads->findBridge.
struct Rva002DB4DA
{
	Rva002DB4DANode *rva002DB4DA(AsciiString name);
};

extern Rva002DB4DA *TheTerrainRoads;

class Bridge
{
public:
	AsciiString rva000AF1DD() const;
};

class TerrainLogic
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v0a();
	virtual void v0b();
	virtual void v0c();
	virtual void v0d();
	virtual void v0e();
	virtual void v0f();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void v14();
	virtual void v15();
	virtual void v16();
	virtual void v17();
	virtual void v18();
	virtual void v19();
	virtual void v1a();
	virtual void v1b();
	virtual void v1c();
	virtual void v1d();
	virtual void v1e();
	virtual void v1f();
	virtual void v20();
	virtual void v21();
	virtual void v22();
	virtual void v23();
	virtual void v24();
	virtual void v25();
	virtual void v26();
	virtual void v27();
	virtual void v28();
	virtual Bridge *findBridgeAt(const Coord3D *loc) const;
	virtual void v2a();
	virtual void v2b();
	virtual void v2c();
	virtual void v2d();
	virtual void v2e();
	virtual void v2f();
	virtual void v30();
	virtual void updateBridgeDamageStates();
};

extern TerrainLogic *TheTerrainLogic;

class AudioManager
{
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
	virtual int addAudioEvent(const BfmeAudioEventPrefix136 *event);
};

extern AudioManager *TheAudio;

class Radar
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
	virtual void queueTerrainRefresh();
};

extern Radar *TheRadar;

// The audio event's object-id setter, address-named as rowed.
class Rva002D9531
{
public:
	void rva002D9531(int value);
};

enum
{
	BODYDAMAGETYPE_COUNT = 4,
	MAX_BRIDGE_BODY_FX = 3
};

class UpdateModule
{
public:
	virtual ~UpdateModule();
protected:
	Object *getObject() const { return m_object; }
private:
	const void *m_moduleData;
	Object *m_object;
	unsigned char m_pad0C[0x20 - 0x0C];
};

class BridgeBehaviorInterface
{
public:
	virtual void setTower(int towerType, Object *tower) = 0;
};

class DamageModuleInterface
{
public:
	virtual void onDamage(DamageInfo *damageInfo) = 0;
	virtual void onHealing(DamageInfo *damageInfo) = 0;
	virtual void onBodyDamageStateChange(const DamageInfo *damageInfo,
		BodyDamageType oldState, BodyDamageType newState) = 0;
};

class DieModuleInterface
{
public:
	virtual void onDie(const DamageInfo *damageInfo) = 0;
};

class BridgeBehavior : public UpdateModule, public BridgeBehaviorInterface,
	public DamageModuleInterface, public DieModuleInterface
{
public:
	virtual void onBodyDamageStateChange(const DamageInfo *damageInfo,
		BodyDamageType oldState, BodyDamageType newState);

protected:
	void resolveFX();
	void doAreaEffects(TerrainRoadType *bridgeTemplate, Bridge *bridge,
		const ObjectCreationList *ocl, const FXList *fx);

private:
	unsigned char m_pad2C[0x3C - 0x2C];
	const ObjectCreationList *m_damageToOCL[ BODYDAMAGETYPE_COUNT ][ MAX_BRIDGE_BODY_FX ];
	const FXList *m_damageToFX[ BODYDAMAGETYPE_COUNT ][ MAX_BRIDGE_BODY_FX ];
	const ObjectCreationList *m_repairToOCL[ BODYDAMAGETYPE_COUNT ][ MAX_BRIDGE_BODY_FX ];
	const FXList *m_repairToFX[ BODYDAMAGETYPE_COUNT ][ MAX_BRIDGE_BODY_FX ];
	Bool m_fxResolved;
	Bool m_scaffoldPresent;
	unsigned char m_padFE[0x104 - 0xFE];
	unsigned int m_deathFrame;
};

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
void BridgeBehavior::onBodyDamageStateChange( const DamageInfo* damageInfo,
																							BodyDamageType oldState,
																							BodyDamageType newState )
{

	//
	// check for coming back from the dead, if our new state is not the rubble state, we can't
	// possibly be dead
	//
	if( newState != BODY_RUBBLE )
		m_deathFrame = 0;

	// first resolve any fx stuff if we need to
	if( m_fxResolved == false )
		resolveFX();

	// sanity
	if( m_fxResolved == false )
		return;

	Object *us = getObject();
	Bridge *bridge = TheTerrainLogic->findBridgeAt( us->getPosition() );

	// sanity
	if( bridge == 0 )
		return;

	// get the bridge template name
	AsciiString bridgeTemplateName = bridge->rva000AF1DD();

	// find the bridge template
	TerrainRoadType *bridgeTemplate = (TerrainRoadType *)TheTerrainRoads->rva002DB4DA( bridgeTemplateName );

	//
	// given the old state and the new state, did we get worse (damaged) or did
	// we get better (repaired)?
	//
	Bool gotRepaired = oldState > newState;

	// get the effect data
	AsciiString soundString;
	AsciiString oclString[ MAX_BRIDGE_BODY_FX ];
	AsciiString fxString[ MAX_BRIDGE_BODY_FX ];
	if( gotRepaired )
	{

		// play the sound
		if( bridgeTemplate )
		{
			BfmeAudioEventPrefix136 sound( bridgeTemplate->m_repairedToSound[ newState ], 0 );
			reinterpret_cast<Rva002D9531 *>( &sound )->rva002D9531( us->getID() );
			TheAudio->addAudioEvent( &sound );
		}

		for( Int i = 0; i < MAX_BRIDGE_BODY_FX; i++ )
			doAreaEffects( bridgeTemplate, bridge, m_repairToOCL[ newState ][ i ], m_repairToFX[ newState ][ i ] );

	}  // end if
	else
	{

		// play the sound
		if( bridgeTemplate )
		{
			BfmeAudioEventPrefix136 sound( bridgeTemplate->m_damageToSound[ newState ], 0 );
			reinterpret_cast<Rva002D9531 *>( &sound )->rva002D9531( us->getID() );
			TheAudio->addAudioEvent( &sound );
		}

		for( Int i = 0; i < MAX_BRIDGE_BODY_FX; i++ )
			doAreaEffects( bridgeTemplate, bridge, m_damageToOCL[ newState ][ i ], m_damageToFX[ newState ][ i ] );

	}  // end else

	// update bridge damage states
	TheTerrainLogic->updateBridgeDamageStates();

	//
	// for the local player, if this bridge has switched from rubble, to usable, or from
	// usable to rubble, we should reflect the change on the radar
	//
	if( oldState == BODY_RUBBLE || newState == BODY_RUBBLE )
		TheRadar->queueTerrainRefresh();

}  // end onBodyDamageStateChange
