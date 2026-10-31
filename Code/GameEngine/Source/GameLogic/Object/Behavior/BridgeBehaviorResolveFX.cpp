// cl: /FIzh_ascii.h /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_bridgebehavior /Ireference/shims/update_modules_bfme2 /Ireference/shims/moduledata /Ireference/shims/zh_outofline /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /Ireference/shims/bfmerendobj /Ireference/shims/debugvtable /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/bfmeanimobj /Ireference/shims/indexbuffercount /Ireference/shims/bfmecaps /Ireference/shims/bfmehcanim /Ireference/shims/bfmevector /Ireference/shims/bfmemapper /Ireference/shims/meshmatdesclayout /Ireference/shims/bfmeshader /Ireference/shims/bfmecpudetect /Ireference/shims/bfmepool /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Ireference/shims/bfmealloc /Ireference/shims/bfmehashtable /Ireference/shims/bfmelist /Ireference/shims/asciistring_downloadmanager /Ireference/shims/stlp_nodealloc /Ireference/shims/asciistring_thin /ICode/GameEngine/Source/Common /Ireference/shims/w3droadbuffer /Ireference/shims/bfmeterraintracks /ICode/Libraries/Include/Lib /ICode/Libraries/Include /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ivendor/stlport /Ireference/shims/asciistring_outofline /ICode/GameEngine/Include /Ireference/shims/iniexception /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
// Retail 0x00456A49, 470B: BridgeBehavior::resolveFX.
// Body: Zero Hour's resolveFX (GeneralsMD GameEngine/Source/GameLogic/Object/
// Behavior/BridgeBehavior.cpp). Target evidence: the bridge is found through
// TerrainLogic slot 0xA4 from the object at this+8, the template through
// TheTerrainRoads->findBridge (0x002DB4DA), and the four name getters
// (getDamageToOCLString 0x002DACF4 and the address-named damage-FX,
// repaired-OCL and repaired-FX getters 0x00456725/0x0045674D/0x00456774)
// feed TheObjectCreationListStore / TheFXListStore lookups, ending with the
// resolved flag at +0xFC. BFME 2 deltas: four body states by three effects,
// the OCL/FX tables at +0x3C/+0x6C/+0x9C/+0xCC, and no sound resolution.

#define BFME_SNAPSHOT_NAME_SLOT
#define BFME_MODULE_NO_MPO
#define Matrix4x4 Matrix4  // BFME renamed it
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine
#include "ascii_string.h"
#include "GameClient/FXList.h"
#include "GameClient/TerrainRoads.h"
#include "GameLogic/Object.h"
#include "GameLogic/ObjectCreationList.h"
#include "GameLogic/TerrainLogic.h"
#include "GameLogic/Module/BridgeBehavior.h"

// Address-named TerrainRoadType name getters (ZH getDamageToFXString,
// getRepairedToOCLString and getRepairedToFXString).
class Rva00456725
{
public:
	AsciiString rva00456725(int a, int b);
	char m_pad00[0xA4];
	AsciiString m_strings[80]; // +0xA4
};

class Rva0045674D
{
public:
	AsciiString rva0045674D(int a, int b);
	AsciiString m_strings[80]; // +0x00
};

class Rva00456774
{
public:
	AsciiString rva00456774(int a, int b);
	AsciiString m_strings[80]; // +0x00
};

class Anim2DTemplate
{
public:
	AsciiString getName() const;
};

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
void BridgeBehavior::resolveFX( void )
{
	Object *us = getObject();
	Bridge *bridge = TheTerrainLogic->findBridgeAt( us->getPosition() );

	// sanity
	if( bridge == 0 )
		return;

	// get the bridge template name
	AsciiString bridgeTemplateName = ((const Anim2DTemplate *)bridge)->getName();

	// find the bridge template
	TerrainRoadType *bridgeTemplate = TheTerrainRoads->findBridge( bridgeTemplateName );

	// sanity
	if( bridgeTemplate == 0 )
		return;

	AsciiString name;
	for( Int bodyState = BODY_PRISTINE; bodyState < BODYDAMAGETYPE_COUNT; ++bodyState )
	{

		// initialize the fx and ocl lists
		for( Int i = 0; i < MAX_BRIDGE_BODY_FX; ++i )
		{

			name = bridgeTemplate->getDamageToOCLString( (BodyDamageType)bodyState, i );
			m_damageToOCL[ bodyState ][ i ] = TheObjectCreationListStore->findObjectCreationList( name.str() );

			name = ((Rva00456725 *)bridgeTemplate)->rva00456725( bodyState, i );
			m_damageToFX[ bodyState ][ i ] = TheFXListStore->findFXList( name.str() );

			name = ((Rva0045674D *)bridgeTemplate)->rva0045674D( bodyState, i );
			m_repairToOCL[ bodyState ][ i ] = TheObjectCreationListStore->findObjectCreationList( name.str() );

			name = ((Rva00456774 *)bridgeTemplate)->rva00456774( bodyState, i );
			m_repairToFX[ bodyState ][ i ] = TheFXListStore->findFXList( name.str() );

		}  // end for i

	}  // end for, bodyState

	// fx are now "resolved"
	m_fxResolved = true;

}  // end resolveFX
