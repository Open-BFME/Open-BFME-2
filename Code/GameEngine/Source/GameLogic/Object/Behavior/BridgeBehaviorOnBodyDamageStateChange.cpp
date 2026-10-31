// cl: /FIzh_ascii.h /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_bridgebehavior /Ireference/shims/update_modules_bfme2 /Ireference/shims/moduledata /Ireference/shims/zh_outofline /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /Ireference/shims/bfmerendobj /Ireference/shims/debugvtable /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/bfmeanimobj /Ireference/shims/indexbuffercount /Ireference/shims/bfmecaps /Ireference/shims/bfmehcanim /Ireference/shims/bfmevector /Ireference/shims/bfmemapper /Ireference/shims/meshmatdesclayout /Ireference/shims/bfmeshader /Ireference/shims/bfmecpudetect /Ireference/shims/bfmepool /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Ireference/shims/bfmealloc /Ireference/shims/bfmehashtable /Ireference/shims/bfmelist /Ireference/shims/asciistring_downloadmanager /Ireference/shims/stlp_nodealloc /Ireference/shims/asciistring_thin /ICode/GameEngine/Source/Common /Ireference/shims/w3droadbuffer /Ireference/shims/bfmeterraintracks /ICode/Libraries/Include/Lib /ICode/Libraries/Include /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ivendor/stlport /Ireference/shims/asciistring_outofline /ICode/GameEngine/Include /Ireference/shims/iniexception /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
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

#define BFME_SNAPSHOT_NAME_SLOT
#define BFME_MODULE_NO_MPO
#define Matrix4x4 Matrix4  // BFME renamed it
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine
#include "ascii_string.h"
#include "../../../../Include/Common/BfmeAudioEventPrefix136.h"
#include "Common/GameAudio.h"
#include "Common/Radar.h"
#include "GameClient/TerrainRoads.h"
#include "GameLogic/Object.h"
#include "GameLogic/TerrainLogic.h"
#include "GameLogic/Module/BridgeBehavior.h"

// The bridge template's repaired and damaged sound entries.
class BridgeRoadSoundView
{
public:
	unsigned char m_pad00[0x64];
	OpaqueRefElement4 m_damageToSound[4];
	unsigned char m_pad74[0xD4 - 0x74];
	OpaqueRefElement4 m_repairedToSound[4];
};

class Anim2DTemplate
{
public:
	AsciiString getName() const;
};

// TheAudio's slots as retail calls them; Zero Hour's manager orders them differently.
class BridgeAudioManagerView
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


// The audio event's object-id setter, address-named as rowed.
class Rva002D9531
{
public:
	void rva002D9531(int value);
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
	AsciiString bridgeTemplateName = ((const Anim2DTemplate *)bridge)->getName();

	// find the bridge template
	TerrainRoadType *bridgeTemplate = TheTerrainRoads->findBridge( bridgeTemplateName );

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
			BfmeAudioEventPrefix136 sound( ((BridgeRoadSoundView *)bridgeTemplate)->m_repairedToSound[ newState ], 0 );
			reinterpret_cast<Rva002D9531 *>( &sound )->rva002D9531( us->getID() );
			((BridgeAudioManagerView *)TheAudio)->addAudioEvent( &sound );
		}

		for( Int i = 0; i < MAX_BRIDGE_BODY_FX; i++ )
			doAreaEffects( bridgeTemplate, bridge, m_repairToOCL[ newState ][ i ], m_repairToFX[ newState ][ i ] );

	}  // end if
	else
	{

		// play the sound
		if( bridgeTemplate )
		{
			BfmeAudioEventPrefix136 sound( ((BridgeRoadSoundView *)bridgeTemplate)->m_damageToSound[ newState ], 0 );
			reinterpret_cast<Rva002D9531 *>( &sound )->rva002D9531( us->getID() );
			((BridgeAudioManagerView *)TheAudio)->addAudioEvent( &sound );
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
