// cl: /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /Ireference/shims/bfme2_ascii /ICode/Libraries/Include
// TU Code/GameEngine/Source/GameLogic/Object/Behavior/BridgeTowerBehavior.cpp
//
// Built on the canonical BFME2 module headers (LINK-168 die-unit recipe). BFME2's
// Snapshot has GetSnapshotName where Zero Hour spells crc, so this unit's tables no
// longer name the Zero Hour ?crc@BehaviorModule nothing in BFME2 defines.
class Thing;
class ModuleData;
class Xfer;
#include "../../../../Include/GameLogic/Module/DamageModuleClass.h"
#include "../../../../Include/GameLogic/Module/DieModuleInterface.h"
#include "../../../../Include/Common/NameKeyGenerator.h"
#include "../object.h"

extern GameLogic *TheGameLogic;
extern NameKeyGenerator *TheNameKeyGenerator;

enum BridgeTowerType { BRIDGE_TOWER_FROM_LEFT = 0 };

#define BFME_DISP8_LEA_NEG_SBB_GETTER(NAME, LEADISP, ADDIMM) \
	class NAME \
	{ \
	public: \
		int get() const; \
	}; \
	int NAME::get() const \
	{ \
		const char *field = (const char *)this; \
		const void *base = field - LEADISP; \
		field += ADDIMM; \
		return base ? (int)field : 0; \
	}

//
// ?getBridgeTowerBehaviorInterfaceFromObject@BridgeTowerBehavior@@SAPAVBridgeTowerBehaviorInterface@@PAVObject@@@Z,
// retail 0x0045880B, 54 bytes. Dedicated TU.
// In the BridgeTowerBehavior.cpp code range (after setBridge 0x004586EE); called
// by the Dozer/Worker scaffolding and repair paths. ZH shape: reject a null
// object or one whose template lacks KINDOF_BRIDGE_TOWER (bit 0 of template
// byte +0x10B in BFME2), then scan the BehaviorModule array at +0x244 and ask
// each module's +0x0C interface sub-object for the tower interface at slot 13
// (+0x34).

// These views expose only the measured template/module pointers and kind-of byte.
// These partial views do not require private Object/ThingTemplate helpers
// to be redeclared when this body joins the original translation unit.
struct BridgeTowerKindOfView
{
	char m_pad[0x10B];
	unsigned char m_kindOfByte10B;
};

struct BridgeTowerObjectTemplateView
{
	char m_pad[4];
	const BridgeTowerKindOfView *m_template;
	char m_remaining[0x244 - 8];
	BehaviorModule **m_modules244;
};

// 0x004543A9 is also reached through the this-0x14 thunk 0x004543E3 in four
// vtables, so it is virtual (same body).
BFME_DISP8_LEA_NEG_SBB_GETTER(Rva0045875FLeaNegSbbField, 12, 0x0C)

//-------------------------------------------------------------------------------------------------
// Zero Hour BridgeTowerBehavior.h's interface. Retail's +0x10 table 0xC40C9C holds
// setBridge 0x004586EE, getBridgeID 0x001DB0A8 and setTowerType 0x005F69CE.
class BridgeTowerBehaviorInterface
{
public:
	virtual void setBridge( Object *bridge ) = 0;
	virtual ObjectID getBridgeID( void ) = 0;
	virtual void setTowerType( BridgeTowerType type ) = 0;
};

//-------------------------------------------------------------------------------------------------
// Retail layout (constructor 0x00458704): BehaviorModule at +0, the tower interface
// at +0x10 (0xC40C9C), DieModuleInterface at +0x14 (0xC40C98), DamageModuleInterface
// at +0x18 (0xC40C8C), m_bridgeID +0x1C, m_type +0x20. The primary table 0xC40D64 has
// BFME2's twelve slots: slot 3 is the rowed xfer 0x004587CD.
class BridgeTowerBehavior : public BehaviorModule,
							public BridgeTowerBehaviorInterface,
							public DieModuleInterface,
							public DamageModuleInterface
{
public:
	BridgeTowerBehavior( Thing *thing, const ModuleData *moduleData );

	virtual NameKeyType getModuleNameKey() const
	{
		static NameKeyType nk = TheNameKeyGenerator->nameToKey( "BridgeTowerBehavior" );
		return nk;
	}

	// BehaviorModuleInterface slot 13 (0xC40CA8 holds 0x002533D3 there, the +0x0C to
	// +0x10 conversion): Zero Hour's getBridgeTowerBehaviorInterface.
	virtual void *slot13() { return static_cast<BridgeTowerBehaviorInterface *>( this ); }
	BridgeTowerBehaviorInterface *getBridgeTowerBehaviorInterface( void ) { return this; }

	virtual void setBridge( Object *bridge );
	virtual ObjectID getBridgeID( void );
	virtual void setTowerType( BridgeTowerType type );

	static BridgeTowerBehaviorInterface *getBridgeTowerBehaviorInterfaceFromObject( Object *obj );

	// Damage methods
	virtual DamageModuleInterface *getDamage() { return this; }
	virtual void onDamage( DamageInfo *damageInfo );
	virtual void onHealing( DamageInfo *damageInfo );
	virtual void onBodyDamageStateChange( const DamageInfo *damageInfo,
										  BodyDamageType oldState,
										  BodyDamageType newState );

	// Die methods
	virtual DieModuleInterface *getDie() { return this; }
	virtual void onDie( const DamageInfo *damageInfo );

protected:
	virtual ~BridgeTowerBehavior();
	virtual void xfer( Xfer *xfer );

	ObjectID m_bridgeID;					///< the bridge we're a part of
	BridgeTowerType m_type;				///< type of tower (positioning) we are
};

//-------------------------------------------------------------------------------------------------
// Retail's BehaviorModule destructor is inline and empty: ~BridgeTowerBehavior
// 0x004586C7 restores BehaviorModule's tables 0xBEEA7C/0xBEE9C0 in place before
// its tail jump to ~ObjectModule 0x0049B47C. The header only declares it, so this
// unit supplies the inline body. Retail keeps no out-of-line copy.
// ?BehaviorModule::~BehaviorModule absent-from-retail
inline BehaviorModule::~BehaviorModule()
{
}

// Bodies follow the Generals Zero Hour reference
// (GameEngine/Source/GameLogic/Object/Behavior/BridgeTowerBehavior.cpp).
/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

////////////////////////////////////////////////////////////////////////////////
//																																						//
//  (c) 2001-2003 Electronic Arts Inc.																				//
//																																						//
////////////////////////////////////////////////////////////////////////////////

// FILE: BridgeTowerBehavior.cpp //////////////////////////////////////////////////////////////////
// Author: Colin Day, July 2002
// Desc:   Behavior module for the towers attached to bridges that can be targeted
///////////////////////////////////////////////////////////////////////////////////////////////////

// INCLUDES ///////////////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

// The native constructor and scalar deleting destructor are provided by
// BridgeTowerBehaviorCtor.cpp using this same virtual class declaration.

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
BridgeTowerBehavior::~BridgeTowerBehavior( void )
{

}

  // end ~BridgeTowerBehavior

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
void BridgeTowerBehavior::setBridge( Object *bridge )
{

	if( bridge == NULL )
		m_bridgeID = INVALID_OBJECT_ID;
	else
		m_bridgeID = bridge->getID();

}

  // end setBridge

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
ObjectID BridgeTowerBehavior::getBridgeID( void )
{

	return m_bridgeID;

}

  // end getBridge

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
void BridgeTowerBehavior::setTowerType( BridgeTowerType type )
{

	m_type = type;

}

  // end setTowerType

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
void BridgeTowerBehavior::onBodyDamageStateChange( const DamageInfo* damageInfo, 
																									 BodyDamageType oldState, 
																									 BodyDamageType newState )
{

}

  // end onBodyDamageStateChange

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
void BridgeTowerBehavior::onDie( const DamageInfo *damageInfo )
{

	// kill the bridge object, this will kill all the towers.  BFME 2 numbers
	// DamageType differently from the Zero Hour Damage.h this unit includes:
	// retail passes 8, BFME 2's DAMAGE_UNRESISTABLE (as SpawnBehavior_onSpawnDeath.cpp
	// declares it), where Zero Hour's default argument would push 11. Retail pushes DEATH_NORMAL, 0.
	Object *bridge = TheGameLogic->findObjectByID( getBridgeID() );
	if( bridge )
		bridge->kill( (DamageType)8 /* DAMAGE_UNRESISTABLE */, (DeathType)0 /* DEATH_NORMAL */ );

}

  // end onDie

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------------------------------------
/** Given an object, return a bridge tower interface if that object has one */
// ------------------------------------------------------------------------------------------------
// BridgeTowerBehavior::getBridgeTowerBehaviorInterfaceFromObject: defined in BridgeTowerBehaviorGetInterfaceFromObject.cpp (its row's unit).
  // getBridgeTowerBehaviorInterfaceFromObject

// BFME2 has no crc. Primary slot 1 is the shared loadPostProcess 0x0058B03E and slot 2
// the class-name getter 0x00458759 (rowed ?Rva458759Get); this unit leaves both to
// their base declarations. xfer: defined in BridgeTowerBehaviorXfer.cpp (its row's unit).

// ---- from Code/GameEngine/Source/GameLogic/Object/Behavior/BridgeTowerBehaviorCtor.cpp

// BFME2 native constructor 0x00458704 and deleting destructor 0x004587B1.
// Use the real donor virtual declaration (verified BFME1 f36a4db066),
// retaining ownership of the vtable-triggered implicit deleting destructor.
// Native clears both existing declared members at +0x1C and +0x20;
// the latter initialization is absent from the ZH source.

BridgeTowerBehavior::BridgeTowerBehavior(Thing *thing, const ModuleData *moduleData)
    : BehaviorModule(thing, moduleData)
{
    m_bridgeID = INVALID_OBJECT_ID;
    m_type = (BridgeTowerType)0;
}

// ---- from Code/GameEngine/Source/GameLogic/Object/Behavior/BridgeTowerBehaviorGetInterfaceFromObject.cpp

// ?getBridgeTowerBehaviorInterfaceFromObject@BridgeTowerBehavior@@SAPAVBridgeTowerBehaviorInterface@@PAVObject@@@Z
BridgeTowerBehaviorInterface *BridgeTowerBehavior::getBridgeTowerBehaviorInterfaceFromObject(Object *obj)
{
	// sanity
	if (obj == 0 || (((const BridgeTowerObjectTemplateView *)obj)->m_template->m_kindOfByte10B & 1) == 0)
		return 0;

	// get the bridge tower behavior module
	BehaviorModule **bmi;
	BridgeTowerBehaviorInterface *bbi;
	for (bmi = ((const BridgeTowerObjectTemplateView *)obj)->m_modules244; *bmi; ++bmi)
	{
		bbi = (BridgeTowerBehaviorInterface *)(*bmi)->slot13();
		if (bbi)
			return bbi;
	}

	// interface not found
	return 0;
}

// tu-skeleton: 0x00458759 6B ?Rva458759Get@@YAHXZ -- matched in Code/GameEngine/Source/Common/ConstIntGetters4.cpp (not merged yet)

// ---- from Code/GameEngine/Source/Common/Disp8LeaNegSbbGetters.cpp

// Disp8 lea-neg-sbb getters: thirteen-byte __thiscall members with one shape:
//
//     lea eax,[ecx-<LEADISP>] / add ecx,<ADDIMM> / neg eax / sbb eax,eax / and eax,ecx / ret
//
// A pointer derived from `this` is null-tested branchlessly: neg sets carry
// exactly when the derived base is nonzero and sbb spreads it to a full mask
// that selects the adjusted `this` or null. Deriving the base from a live
// field-local keeps `this` in ecx so the adjustment compiles to an in-place
// add instead of a lea into a scratch register. Identity is not recovered:
// every name is derived from its address.
// No // cl: line (defaults match the shape).


// tu-skeleton: 0x004587CD 62B ?xfer@BridgeTowerBehavior@@MAEXPAVXfer@@@Z -- matched in Code/GameEngine/Source/GameLogic/Object/Behavior/BridgeTowerBehaviorXfer.cpp (not merged yet)

// tu-skeleton: 0x00458841 342B ?onDamage@BridgeTowerBehavior@@UAEXPAVDamageInfo@@@Z -- matched in Code/GameEngine/Source/GameLogic/Object/Behavior/BridgeTowerBehaviorOnDamage.cpp (not merged yet)

// tu-skeleton: 0x00458997 241B ?onHealing@BridgeTowerBehavior@@UAEXPAVDamageInfo@@@Z -- matched in Code/GameEngine/Source/GameLogic/Object/Behavior/BridgeTowerBehaviorOnHealing.cpp (not merged yet)
