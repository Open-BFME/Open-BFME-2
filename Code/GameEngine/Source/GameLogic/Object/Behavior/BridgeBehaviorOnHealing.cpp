// cl: /FIzh_ascii.h /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_bridgebehavior /Ireference/shims/update_modules_bfme2 /Ireference/shims/moduledata /Ireference/shims/zh_outofline /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /Ireference/shims/bfmerendobj /Ireference/shims/debugvtable /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/bfmeanimobj /Ireference/shims/indexbuffercount /Ireference/shims/bfmecaps /Ireference/shims/bfmehcanim /Ireference/shims/bfmevector /Ireference/shims/bfmemapper /Ireference/shims/meshmatdesclayout /Ireference/shims/bfmeshader /Ireference/shims/bfmecpudetect /Ireference/shims/bfmepool /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Ireference/shims/bfmealloc /Ireference/shims/bfmehashtable /Ireference/shims/bfmelist /Ireference/shims/asciistring_downloadmanager /Ireference/shims/stlp_nodealloc /Ireference/shims/asciistring_thin /ICode/GameEngine/Source/Common /Ireference/shims/w3droadbuffer /Ireference/shims/bfmeterraintracks /ICode/Libraries/Include/Lib /ICode/Libraries/Include /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ivendor/stlport /Ireference/shims/asciistring_outofline /ICode/GameEngine/Include /Ireference/shims/iniexception /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
// Retail 0x004572B1, 141B: BridgeBehavior::onHealing, entered through the
// DamageModuleInterface subobject at BridgeBehavior+0x24 (object this-0x1C,
// BridgeBehaviorInterface this-0x04 whose slot 1 is getTowerID).
// Body: Zero Hour's onHealing (GeneralsMD GameEngine/Source/GameLogic/Object/
// Behavior/BridgeBehavior.cpp) with the BFME 2 layout shared by the matched
// BridgeTowerBehavior::onHealing 0x00458997: body module Object+0x254
// (getMaxHealth slot 0x18), DamageInfo amount +0x20 / source +0x08, the
// tower kind-of bit at template+0x10B bit 0 (ZH KINDOF_BRIDGE_TOWER) and
// out-of-line Object::attemptHealing 0x0028FE55.

#define BFME_SNAPSHOT_NAME_SLOT
#define BFME_MODULE_NO_MPO
#define Matrix4x4 Matrix4  // BFME renamed it
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine
#include "GameLogic/GameLogic.h"
#include "GameLogic/Object.h"
#include "GameLogic/Module/BodyModule.h"
#include "GameLogic/Module/BridgeBehavior.h"

// BFME 2's 0x7C-byte DamageInfo: its default constructor is the rowed 0x00263895, address-named
// Rva00263895Member; trivially destroyed. Zero Hour's DamageInfo has other offsets.
// BFME 2's 0x7C-byte DamageInfo as a local: its default constructor is the
// rowed 0x00263895, address-named Rva00263895Member; trivially destroyed.
class Rva00263895Member
{
public:
	Rva00263895Member();
	unsigned char m_pad00[0x08];
	ObjectID m_sourceID;			// +0x08
	unsigned char m_pad0C[0x10 - 0x0C];
	Int m_damageType;			// +0x10
	unsigned char m_pad14[0x1C - 0x14];
	Int m_deathType;			// +0x1C
	Real m_amount;				// +0x20
	unsigned char m_pad24[0x7C - 0x24];
};

// The body module's slots as retail calls them; Zero Hour's interface orders them differently.
class BridgeBodyModuleView
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual Real getMaxHealth() const;
};

// The owner's template pointer at +0x04 and the template's kind-of bytes (ZH KINDOF_BRIDGE and
// KINDOF_BRIDGE_TOWER at +0x10A bit 6 and +0x10B bit 0; the BFME bit names are not recovered).
struct BridgeKindOfView
{
	unsigned char m_pad00[0x10A];
	unsigned char m_kindOf10A;
	unsigned char m_kindOf10B;
};

struct BridgeObjectTemplateView
{
	unsigned char m_pad00[0x04];
	const BridgeKindOfView *m_template;
};

// ------------------------------------------------------------------------------------------------
// Retail 0x004571FB, 182B: BridgeBehavior::onDamage, the damage-interface slot
// before onHealing. Zero Hour's body in the same BFME 2 layout; the tower
// damage record is the 0x7C-byte local built by 0x00263895 and handed to the
// out-of-line Object::attemptDamage 0x0029848E.
// ------------------------------------------------------------------------------------------------
void BridgeBehavior::onDamage( DamageInfo *damageInfo )
{

	// get the bridge object
	Object *bridge = getObject();

	// get bridge body module
	BridgeBodyModuleView *body = (BridgeBodyModuleView *)bridge->getBodyModule();

	// what is our percentage of the damage done to the bridge
	Real damagePercentage = ((const Rva00263895Member *)damageInfo)->m_amount / body->getMaxHealth();

	// if our source is a tower, don't do anything
	Object *source = TheGameLogic->findObjectByID( ((const Rva00263895Member *)damageInfo)->m_sourceID );
	if( source && (((const BridgeObjectTemplateView *)source)->m_template->m_kindOf10B & 1) )
		return;

	// apply damage to all towers
	for( Int i = 0; i < BRIDGE_MAX_TOWERS; ++i )
	{
		Object *tower = TheGameLogic->findObjectByID( getTowerID( (BridgeTowerType)i ) );
		if( tower )
		{
			BridgeBodyModuleView *towerBody = (BridgeBodyModuleView *)tower->getBodyModule();
			Rva00263895Member towerDamage;
			towerDamage.m_amount = towerBody->getMaxHealth() * damagePercentage;
			towerDamage.m_sourceID = getObject()->getID();
			towerDamage.m_damageType = ((const Rva00263895Member *)damageInfo)->m_damageType;
			towerDamage.m_deathType = ((const Rva00263895Member *)damageInfo)->m_deathType;
			tower->attemptDamage( (DamageInfo *)&towerDamage );
		}
	}

}  // end onDamage

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
void BridgeBehavior::onHealing( DamageInfo *damageInfo )
{

	//
	// get our body info so we now how much healing percent is being done to us ... we need this
	// so that we can propagate the same healing percentage amont the towers and the bridge
	//
	BridgeBodyModuleView *body = (BridgeBodyModuleView *)getObject()->getBodyModule();
	Real healingPercentage = ((const Rva00263895Member *)damageInfo)->m_amount / body->getMaxHealth();

	//
	// if the healing didn't come from a bridge tower, then we must propagate this healing
	// to all our towers
	//
	Object *source = TheGameLogic->findObjectByID( ((const Rva00263895Member *)damageInfo)->m_sourceID );
	if( source == 0 || (((const BridgeObjectTemplateView *)source)->m_template->m_kindOf10B & 1) == 0 )
	{
		Object *tower;

		for( Int i = 0; i < BRIDGE_MAX_TOWERS; i++ )
		{

			tower = TheGameLogic->findObjectByID( getTowerID( (BridgeTowerType)i ) );
			if( tower )
			{
				BridgeBodyModuleView *towerBody = (BridgeBodyModuleView *)tower->getBodyModule();
				tower->attemptHealing( healingPercentage * towerBody->getMaxHealth(), getObject() );
			}  // end if

		}  // end for i

	}  // end if

}  // end onHealing
