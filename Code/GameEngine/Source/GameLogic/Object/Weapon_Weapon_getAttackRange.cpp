// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/open-bfme-1/inputs/reference/shims/ini /Ireference/open-bfme-1/inputs/reference/shims/weapon /Ireference/open-bfme-1/inputs/reference/shims/iniexception /Ireference/open-bfme-1/inputs/reference/shims/ini_noinline /Ireference/open-bfme-1/inputs/reference/shims/sweep /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/GameEngine/Source/GameLogic/Object
//
// ?getAttackRange@Weapon@@QBEMPBVObject@@@Z
// retail 0x002C9BF8, 63 bytes. Dedicated TU ported from the Open-BFME-1
// donor game/GameEngine/Source/GameLogic/Object/Weapon.cpp (reference/open-bfme-1 @ 6d943426).
// The donor body does not place at BFME 1's flags; compiled /O1 it is
// byte-identical to retail once relocations are masked (unique hit on
// unclaimed .text). Only the placed body is defined here; the donor's
// other definitions are omitted.
// stlport
#define Matrix4x4 Matrix4  // BFME renamed it
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

// FILE: Weapon.cpp ///////////////////////////////////////////////////////////////////////////////
// Author: Colin Day, November 2001
// Desc:   Weapon descriptions
///////////////////////////////////////////////////////////////////////////////////////////////////

// INCLUDES ///////////////////////////////////////////////////////////////////////////////////////
// This TU calls the independently witnessed matrix-copy variant at 0x132200.
// Rename the reference header declaration locally; the published setter is a different body.
#define setTransformMatrix rva00132200
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#undef setTransformMatrix

#define DEFINE_DEATH_NAMES
#define DEFINE_WEAPONBONUSCONDITION_NAMES
#define DEFINE_WEAPONBONUSFIELD_NAMES
#define DEFINE_WEAPONCOLLIDEMASK_NAMES
#define DEFINE_WEAPONAFFECTSMASK_NAMES
#define DEFINE_WEAPONRELOAD_NAMES
#define DEFINE_WEAPONPREFIRE_NAMES

#include "Common/CRC.h"
#include "Common/CRCDebug.h"
#include "Common/GameAudio.h"
#include "Common/GameState.h"
#include "Common/INI.h"
#include "Common/PerfTimer.h"
#include "Common/Player.h"
#include "Common/ThingFactory.h"
#include "Common/ThingTemplate.h"
#include "Common/Xfer.h"
 
#include "GameClient/Drawable.h"
#include "GameClient/FXList.h"
#include "GameClient/InGameUI.h"
#include "GameClient/ParticleSys.h"

#include "GameLogic/Damage.h"
#include "GameLogic/ExperienceTracker.h"
#include "GameLogic/GameLogic.h"
#include "GameLogic/AIPathfind.h"
#include "GameLogic/Module/BehaviorModule.h"
#include "GameLogic/Module/BodyModule.h"
#include "GameLogic/Module/ContainModule.h"
#include "GameLogic/Module/LaserUpdate.h"
#include "GameLogic/Module/UpdateModule.h"
#include "GameLogic/Module/SpecialPowerCompletionDie.h"
#include "GameLogic/Module/AssaultTransportAIUpdate.h"
#include "GameLogic/Object.h"
#include "GameLogic/ObjectCreationList.h"
#include "GameLogic/PartitionManager.h"
#include "GameLogic/Weapon.h"

#include "GameLogic/Module/AIUpdate.h"
#include "GameLogic/Module/AssistedTargetingUpdate.h"
#include "GameLogic/Module/ProjectileStreamUpdate.h"
#include "GameLogic/Module/PhysicsUpdate.h"
#include "GameLogic/TerrainLogic.h"

#define RATIONALIZE_ATTACK_RANGE
#define ATTACK_RANGE_IS_2D

#ifdef ATTACK_RANGE_IS_2D
	const DistanceCalculationType ATTACK_RANGE_CALC_TYPE = FROM_BOUNDINGSPHERE_2D;
#else
	const DistanceCalculationType ATTACK_RANGE_CALC_TYPE = FROM_BOUNDINGSPHERE_3D;
#endif

#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif

// damage is ALWAYS 3d
const DistanceCalculationType DAMAGE_RANGE_CALC_TYPE = FROM_BOUNDINGSPHERE_3D;

//-------------------------------------------------------------------------------------------------
static void parsePerVetLevelAsciiString( INI* ini, void* /*instance*/, void * store, const void* /*userData*/ )
{
	AsciiString* s = (AsciiString*)store;
	VeterancyLevel v = (VeterancyLevel)INI::scanIndexList(ini->getNextToken(), TheVeterancyNames);
	s[v] = ini->getNextAsciiString();
}

//-------------------------------------------------------------------------------------------------
static void parseAllVetLevelsAsciiString( INI* ini, void* /*instance*/, void * store, const void* /*userData*/ )
{
	AsciiString* s = (AsciiString*)store;
	AsciiString a = ini->getNextAsciiString();
	for (Int i = LEVEL_FIRST; i <= LEVEL_LAST; ++i)
		s[i] = a;
}

//-------------------------------------------------------------------------------------------------
static void parsePerVetLevelFXList( INI* ini, void* /*instance*/, void * store, const void* /*userData*/ )
{
	typedef const FXList* ConstFXListPtr;
	ConstFXListPtr* s = (ConstFXListPtr*)store;
	VeterancyLevel v = (VeterancyLevel)INI::scanIndexList(ini->getNextToken(), TheVeterancyNames);
	const FXList* fx = NULL;
	INI::parseFXList(ini, NULL, &fx, NULL);
	s[v] = fx;
}

//-------------------------------------------------------------------------------------------------
static void parseAllVetLevelsFXList( INI* ini, void* /*instance*/, void * store, const void* /*userData*/ )
{
	typedef const FXList* ConstFXListPtr;
	ConstFXListPtr* s = (ConstFXListPtr*)store;
	const FXList* fx = NULL;
	INI::parseFXList(ini, NULL, &fx, NULL);
	for (Int i = LEVEL_FIRST; i <= LEVEL_LAST; ++i)
		s[i] = fx;
}

//-------------------------------------------------------------------------------------------------
static void parsePerVetLevelPSys( INI* ini, void* /*instance*/, void * store, const void* /*userData*/ )
{
	typedef const ParticleSystemTemplate* ConstParticleSystemTemplatePtr;
	ConstParticleSystemTemplatePtr* s = (ConstParticleSystemTemplatePtr*)store;
	VeterancyLevel v = (VeterancyLevel)INI::scanIndexList(ini->getNextToken(), TheVeterancyNames);
	ConstParticleSystemTemplatePtr pst = NULL;
	INI::parseParticleSystemTemplate(ini, NULL, &pst, NULL);
	s[v] = pst;
}

//-------------------------------------------------------------------------------------------------
static void parseAllVetLevelsPSys( INI* ini, void* /*instance*/, void * store, const void* /*userData*/ )
{
	typedef const ParticleSystemTemplate* ConstParticleSystemTemplatePtr;
	ConstParticleSystemTemplatePtr* s = (ConstParticleSystemTemplatePtr*)store;
	ConstParticleSystemTemplatePtr pst = NULL;
	INI::parseParticleSystemTemplate(ini, NULL, &pst, NULL);
	for (Int i = LEVEL_FIRST; i <= LEVEL_LAST; ++i)
		s[i] = pst;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// PUBLIC DATA ////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
extern WeaponStore *TheWeaponStore;					///< the weapon store definition

///////////////////////////////////////////////////////////////////////////////////////////////////
// PRIVATE DATA ///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
/* WeaponTemplate::TheWeaponTemplateFieldParseTable: defined by its owning unit */

///////////////////////////////////////////////////////////////////////////////////////////////////
// PUBLIC FUNCTIONS ///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

  // end postProcessLoad

//-------------------------------------------------------------------------------------------------
// BFME keeps two reload bounds before the delay bounds; the Zero Hour header
// has only one reload value, so use the witnessed retail offsets locally.
struct BfmeWeaponTemplateFireTimingView
{
	unsigned char m_prefix[0x4b0];
	Int m_minClipReloadTime;
	Int m_maxClipReloadTime;
	Int m_minDelayBetweenShots;
	Int m_maxDelayBetweenShots;
};

//-------------------------------------------------------------------------------------------------
static Bool is2DDistSquaredLessThan(const Coord3D& a, const Coord3D& b, Real distSqr)
{
	Real da = sqr(a.x - b.x) + sqr(a.y - b.y);
	return da <= distSqr;
}

//-------------------------------------------------------------------------------------------------
// Retail temporary-weapon overloads live in WeaponStore_createAndFireTempWeapon.cpp.

//-------------------------------------------------------------------------------------------------
// Exact bytes in game/masm_dumps/_findWeaponTemplate_WeaponStore_QBEPBVWeaponTemplate_VAsciiString_1E4F50.asm
// (true body 0x1E4F50/183B; BFME AsciiString.str buffer at +8 vs ZH +4 blocks C++ match)

 

 

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
// Retail Weapon::computeBonus is defined in Weapon_computeBonus.cpp.

//-------------------------------------------------------------------------------------------------
// BFME's WeaponBonus carries SIX fields where the reference enum stops at five
// (DAMAGE, RADIUS, RANGE, RATE_OF_FIRE, PRE_ATTACK), so the local is 0x18 bytes
// rather than 0x14 and its constructor writes six 1.0f stores. Both reload
// entry points below are otherwise the reference bodies unchanged.
struct BfmeWeaponBonus
{
	BfmeWeaponBonus()
	{
		for (int i = 0; i < 6; ++i)
			m_field[i] = 1.0f;
	}

	Real m_field[6];
};

//-------------------------------------------------------------------------------------------------
// Retail contained-ammo-aware setClipPercentFull lives in Weapon_setClipPercentFull.cpp.

//-------------------------------------------------------------------------------------------------
static void clipToTerrainExtent(Coord3D& approachTargetPos)
{
	Region3D bounds;
	TheTerrainLogic->getExtent(&bounds);
	if (approachTargetPos.x < bounds.lo.x+PATHFIND_CELL_SIZE_F) {	 
		approachTargetPos.x = bounds.lo.x+PATHFIND_CELL_SIZE_F;
	}
	if (approachTargetPos.y < bounds.lo.y+PATHFIND_CELL_SIZE_F) {
		approachTargetPos.y = bounds.lo.y+PATHFIND_CELL_SIZE_F;
	}
	if (approachTargetPos.x > bounds.hi.x-PATHFIND_CELL_SIZE_F) {
		approachTargetPos.x = bounds.hi.x-PATHFIND_CELL_SIZE_F;
	}
	if (approachTargetPos.y > bounds.hi.y-PATHFIND_CELL_SIZE_F) {
		approachTargetPos.y = bounds.hi.y-PATHFIND_CELL_SIZE_F;
	}
}

//-------------------------------------------------------------------------------------------------
// BFME widened the reference's bonus-only signature: its getAttackRange takes
// the source object and the source's position as well as the bonus, so the
// range can depend on where the shooter is.
class BfmeRangedWeaponTemplate
{
public:
	Real getAttackRange( const Object *source, const WeaponBonus &bonus,
			const Coord3D *sourcePos ) const;			///< retail ILT 0x0002ffb3
};

// BFME's weapon keeps its template at +0x04, where the reference class puts it
// at +0x08 -- the same offset Object::getAmmoPipShowingInfo reads.
struct BfmeWeaponTemplateField
{
	char m_unreconstructed_00[4];					///< the vtable pointer
	const BfmeRangedWeaponTemplate *m_template;			///< retail this+0x04
};

Real Weapon::getAttackRange(const Object *source) const
{ 
	BfmeWeaponBonus bonus;
	computeBonus(source, 0, (WeaponBonus &)bonus);
	return ((const BfmeWeaponTemplateField *)this)->m_template->getAttackRange(
		source, (const WeaponBonus &)bonus, source->getPosition()); 

	//Contained objects have longer ranges.
	//const Object *container = source->getContainedBy();
	//if( container )
	//{
	//	attackRange += container->getGeometryInfo().getBoundingCircleRadius();
	//}
	//return attackRange;
}

//-------------------------------------------------------------------------------------------------
// BFME's getStatus is a CACHED query, not a recomputation. A helper works the
// status out and reports through a bool-by-pointer -- pre-set to true -- whether
// the answer may be cached; the cache at Weapon+0x10 is rewritten only when the
// helper leaves that flag set AND the value actually changed, and the value
// RETURNED is the helper's, not the cache. The method is const in the mangled
// name and still writes +0x10, so retail writes through the const too.
class BfmeWeaponStatusCache
{
public:
	WeaponStatus bfmeComputeStatus( Bool *valid ) const;		///< retail ILT 0x0001e6a0

	char m_unreconstructed_00[0x10];
	WeaponStatus m_bfmeCached;					///< retail this+0x10
};

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
class AssistanceRequestData
{
public:
	AssistanceRequestData();

	const Object *m_requestingObject;
	Object *m_victimObject;
	Real m_requestDistanceSquared;
};

//-------------------------------------------------------------------------------------------------
static void makeAssistanceRequest( Object *requestOf, void *userData )
{
	AssistanceRequestData *requestData = (AssistanceRequestData *)userData;

	// Don't ask ourselves (can't believe I forgot this one)
	if( requestOf == requestData->m_requestingObject )
		return;

	// Only request of our kind of people
	if( !requestOf->getTemplate()->isEquivalentTo( requestData->m_requestingObject->getTemplate() ) )
		return;

	// Who are close enough
	Real distSq = ThePartitionManager->getDistanceSquared( requestOf, requestData->m_requestingObject, FROM_CENTER_2D );
	if( distSq > requestData->m_requestDistanceSquared )
		return;

	// and respond to requests
	static const NameKeyType key_assistUpdate = NAMEKEY("AssistedTargetingUpdate");
	AssistedTargetingUpdate *assistModule = (AssistedTargetingUpdate*)requestOf->findUpdateModule(key_assistUpdate);
	if( assistModule == NULL )
		return;

	// and say yes
	if( !assistModule->isFreeToAssist() )
		return;

	assistModule->assistAttack( requestData->m_requestingObject, requestData->m_victimObject );
}

//-------------------------------------------------------------------------------------------------
// BFME Object layout (proven via retail body @ 0x1E2D60): m_ai @ +0x204, m_weaponSet @ +0x264.
// getDrawable is virtual vtable+0x28 (ZH header inlines m_drawable @ +0x80).
// No enclosing-container early-out; turret math gated by WeaponTemplate+0x534 flag.
struct BFME_Object_AIField {
	unsigned char pad[0x204];
	const AIUpdateInterface* ai;
};
struct BFME_Object_WeaponSetField {
	unsigned char pad[0x264];
	WeaponSet weaponSet;
};
class BFME_Object_GetDrawable {
public:
	virtual void _v0() = 0;
	virtual void _v1() = 0;
	virtual void _v2() = 0;
	virtual void _v3() = 0;
	virtual void _v4() = 0;
	virtual void _v5() = 0;
	virtual void _v6() = 0;
	virtual void _v7() = 0;
	virtual void _v8() = 0;
	virtual void _v9() = 0;
	virtual Drawable* getDrawable() const = 0; // vtable +0x28
};

//-------------------------------------------------------------------------------------------------
// Retail 0x1E37F0: the former 55-byte extent ended after PUSH EDI.
// The full body ends at RET 0x1E38CF; it uses Drawable vslot +0x28,
// the existing opaque bool setter at 0x411DD0, and no physics tail.
class Gen_00411DD0 { public: void bfmeSet(Bool); };

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// Retail object-target terrain LOS lives in Weapon_isClearFiringLineOfSightTerrain_Object.cpp.

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// Retail coordinate terrain LOS overload lives in Weapon_isClearFiringLineOfSightTerrain.cpp.

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
/** Determine whether if source was at goalPos whether it would have clear line of sight. */
// Retail coordinate terrain LOS overload lives in Weapon_isClearFiringLineOfSightTerrain.cpp.

  // end crc

// ------------------------------------------------------------------------------------------------
/** Xfer
	* Version Info:
	* 1: Initial version */
// ------------------------------------------------------------------------------------------------
struct BfmeWeaponVersion
{
	unsigned char data[2];
};

union BfmeWeaponVersionStorage
{
	BfmeWeaponVersion version;
	unsigned char padding[4];
};

struct BfmeWeaponFormattedText
{
	char *text;
	int tag;
};

extern "C" BfmeWeaponFormattedText *__cdecl bfmeFormatText(
	BfmeWeaponFormattedText *result, int tag, const char *format, ...);
extern void __declspec(noreturn) __stdcall _CxxThrowException(
	void *object, void *throwInfo);
extern int g_guardTargetTypeThrowInfo;

class BfmeWeaponXferView
{
public:
	virtual void slot00();
	virtual bool IsLoading();
	virtual bool IsStoring();
	virtual bool IsCRC();
	virtual bool IsLightCRC();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual BfmeWeaponXferView &slot09(void *, unsigned int);
	virtual BfmeWeaponXferView &xferVersion(BfmeWeaponVersion &);
	virtual BfmeWeaponXferView &slot11();
	virtual BfmeWeaponXferView &slot12();
	virtual BfmeWeaponXferView &slot13();
	virtual BfmeWeaponXferView &slot14();
	virtual BfmeWeaponXferView &slot15();
	virtual BfmeWeaponXferView &slot16();
	virtual BfmeWeaponXferView &slot17();
	virtual BfmeWeaponXferView &slot18();
	virtual BfmeWeaponXferView &slot19();
	virtual BfmeWeaponXferView &slot20();
	virtual BfmeWeaponXferView &slot21();
	virtual BfmeWeaponXferView &slot22();
	virtual BfmeWeaponXferView &slot23();
	virtual BfmeWeaponXferView &slot24();
	virtual BfmeWeaponXferView &slot25();
	virtual BfmeWeaponXferView &xferAsciiString(AsciiString &);
	virtual BfmeWeaponXferView &slot27();
	virtual BfmeWeaponXferView &slot28();
	virtual BfmeWeaponXferView &xferUnsignedInt(unsigned int &);
	virtual BfmeWeaponXferView &xferInt(int &);
	virtual BfmeWeaponXferView &xferUnsignedShort(unsigned short &);
	virtual BfmeWeaponXferView &slot32();
	virtual BfmeWeaponXferView &slot33();
	virtual BfmeWeaponXferView &slot34();
	virtual BfmeWeaponXferView &xferBool(bool &);
};

class Rva00034045NameAccessor
{
public:
	AsciiString getName() const;
};


struct BfmeWeaponLayout
{
	char vftable[8];
	const WeaponTemplate *m_template;
	ObjectID m_projectileStreamID;
	WeaponSlotType m_wslot;
	WeaponStatus m_status;
	unsigned int m_ammoInClip;
	unsigned int m_whenWeCanFireAgain;
	unsigned int m_whenPreAttackFinished;
	unsigned int m_whenLastReloadStarted;
	unsigned int m_lastFireFrame;
	unsigned int m_suspendFXFrame;
	unsigned int m_maxShotCountLegacy;
	unsigned int m_gameFrame;
	int m_maxShotCount;
	int m_curBarrel;
	int m_numShotsForCurBarrel;
	std::vector<Int> m_scatterTargetsUnused;
	bool m_pitchLimited;
	char m_pitchPadding[3];
	unsigned int m_field50;
	int m_field54;
	int m_field58;
};

typedef char BfmeWeaponLayoutTemplateOffset[(offsetof(BfmeWeaponLayout, m_template) == 8) ? 1 : -1];
typedef char BfmeWeaponLayoutVectorOffset[(offsetof(BfmeWeaponLayout, m_scatterTargetsUnused) == 0x44) ? 1 : -1];

extern void friend_xferObjectID(Xfer *xfer, ObjectID *objectID);
extern void bfmeWeaponSlotXfer(Xfer *xfer, void *value);
extern void bfmeWeaponStatusXfer(Xfer *xfer, void *value);

  // end xfer

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
// Body in WeaponBonusSet_parseWeaponBonusSet.cpp: retail calls INI::scanPercentToReal
// out of line, which this TU's INI shim inlines.

