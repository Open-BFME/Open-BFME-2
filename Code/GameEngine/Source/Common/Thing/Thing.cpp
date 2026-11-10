// cl: /Ireference/shims/zh_overridable_outofline /FIzh_ascii.h /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
// Link view first: Vector3::Length (and Normalize/Vector3(x,y,z) in the full view) stay inline without
// emitting /O2 copies that compete with retail's owners (0x000692B3, 0x0006924F, 0x006CD510).
#include "../../../../../reference/shims/bfme_vector3_lenfull_link/vector3_lenfull_link.h"
// Link view first: Matrix3D(), Matrix3D(bool) and Matrix3D(const Matrix3D&) stay inline without
// emitting /O2 copies that compete with retail's owners (0x000423C5, 0x0004C91A, 0x0006645C).
#include "../../../../../reference/shims/bfme_matrix3d_full_link/matrix3d_full_link.h"
// stlport
// readable body of ?getTemplate@Thing@@QBEPBVThingTemplate@@XZ: Code/GameEngine/Source/Common/Thing/Thing_isKindOf.cpp
// The compiler-generated vector constructor iterator (??_H) takes the
// optimization state of the first function that needs it. Retail links one
// copy, the /O1 body at 0x00001423; this unemitted anchor makes this unit's
// copy that same body, so it no longer loses to retail's at link time.
// It can also change how later array constructions here compile; checked to
// change nothing else in this unit, but if a function added later that builds
// an array will not match, try it without this block.
struct BfmeVciAnchorElem { BfmeVciAnchorElem(); };
static void bfmeVciAnchor() { BfmeVciAnchorElem anchor[2]; (void)anchor; }
#pragma optimize("", on)
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

// FILE: Thing.cpp ////////////////////////////////////////////////////////////
// Created:   Colin Day, May 2001
//
// Desc:      Things are the base class for objects and drawables, objects
//						are logic side representations while drawables are client
//						side.  Common data will be held in the Thing defined here
//						and systems that need to work with both of them will work with
//						"Things"
//
//-----------------------------------------------------------------------------
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#include "Common/PerfTimer.h"
#include "Common/Thing.h"
#include "Common/ThingTemplate.h"
#include "Common/ThingFactory.h"
#include "Common/GlobalData.h"
#include "Common/NameKeyGenerator.h"
#include "Common/Player.h"
#include "Common/PlayerList.h"
#include "Common/Team.h"
#include "Lib/Trig.h"
#include "GameLogic/TerrainLogic.h"
// bfme link decl-only begin
namespace _STL { template <> void _Base_bitset<4>::_M_do_and(_Base_bitset<4> const &); }
// bfme link decl-only end

class BFMERetailThingVTable
{
public:
	virtual Real calculateHeightAboveTerrain() const = 0;
	virtual void slot1() = 0;
	virtual void slot2() = 0;
	virtual void slot3() = 0;
	virtual void slot4() = 0;
	virtual void reactToTransformChange(const Matrix3D *oldMtx, const Coord3D *oldPos, Real oldAngle) = 0;
};

class BFMERetailTerrainLogicVTable
{
public:
	virtual void slot0() = 0;
	virtual void slot1() = 0;
	virtual void slot2() = 0;
	virtual void slot3() = 0;
	virtual void slot4() = 0;
	virtual void slot5() = 0;
	// ZH's TerrainLogic.h puts getGroundHeight at slot 5; retail calls
	// [vtable+0x18], one slot further out.
	virtual Real getGroundHeight(Real x, Real y, Coord3D *normal = NULL) const = 0;
	virtual void slot7() = 0;
	virtual void slot8() = 0;
	virtual void slot9() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void slot17() = 0;
	virtual PathfindLayerEnum alignOnTerrain(Real angle, const Coord3D& pos, Bool stickToGround, Matrix3D& mtx) = 0;
	virtual Bool isUnderwater(Real x, Real y, Real *waterZ, Real *terrainZ) = 0;
};

class BFMEThingSetTransformVTable
{
public:
	virtual void slot0() = 0;
	virtual void slot1() = 0;
	virtual void slot2() = 0;
	virtual void slot3() = 0;
	virtual void slot4() = 0;
	virtual void slot5() = 0;
	virtual void reactToTransformChange() = 0;
};

#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif

// Thing::Thing: defined in ThingConstructor.cpp (its row's unit).

// Thing::~Thing: defined in ThingConstructor.cpp (its row's unit; retail lowers
// the live-instance count, which Zero Hour's empty destructor here did not).

//DECLARE_PERF_TIMER(ThingMatrixStuff)

//=============================================================================
// ?getTemplate@Thing@@ present-unmatched
// Retail reads m_template raw: 26 TUs emit mov eax,[ecx+4]; ret, and rowed
// bodies inline that load. ZH's OVERRIDE conversion would resolve overrides
// (null-check plus tail-call to getFinalOverride); the non-overloaded
// pointer keeps this TU's copy byte-identical to retail's.
inline const ThingTemplate *Thing::getTemplate() const
{
	return m_template.getNonOverloadedPointer();
}

//=============================================================================
#pragma optimize("s", on)
void Thing::getUnitDirectionVector2D(Coord3D& dir) const
{
	dir = *getUnitDirectionVector2D();
}
#pragma optimize("", on)

//=============================================================================

// File-static matrix copy (LK3-style): the TU's copy-ctor COMDAT loses
// the link (first in link order), and the unrowed body below inlines the
// construction, so the def cannot just go away. The helper keeps a call in
// the source while the copy-ctor goes unused.
static void CopyThingMatrix3D(Matrix3D &dst, const Matrix3D &src)
{
    dst[0] = src[0];
    dst[1] = src[1];
    dst[2] = src[2];
}

//=============================================================================
// the nice thing about this is that we don't have to recalc out cached terrain stuff.
// Thing::setPositionZ: retail 0x0030A92C, matched in ThingRva0030A92C.cpp.

//=============================================================================
// byte-exact reconstruction: Code/GameEngine/Source/Common/Thing/ThingSetPosition.cpp
//=============================================================================
// byte-exact reconstruction: Code/GameEngine/Source/Common/Thing/ThingSetOrientation.cpp
//=============================================================================
// byte-exact reconstruction: Code/GameEngine/Source/Common/Thing/ThingSetTransformMatrix.cpp
//=============================================================================

//-------------------------------------------------------------------------------------------------
// byte-exact reconstruction: Code/GameEngine/Source/Common/Thing/Thing_isKindOf.cpp
// ?isKindOf@Thing@@QBE_NW4KindOfType@@@Z present-unmatched
Bool Thing::isKindOf(KindOfType t) const 
{ 
	// Retail stores the template kind mask at +0x108.
	const KindOfMaskType &kindOf = *(const KindOfMaskType *)((const char *)getTemplate() + 0x108);
	return TEST_KINDOFMASK(kindOf, t);
}

//-------------------------------------------------------------------------------------------------
static Bool (*volatile _bfme_force_test_kindof_any)(const KindOfMaskType&, const KindOfMaskType&) = &TEST_KINDOFMASK_ANY;

// Thing::isKindOfMulti: defined in ThingIsAnyKindOf.cpp (its row's unit).

// Thing::isAnyKindOf: retail 0x0030ADC7 is rowed in ThingIsAnyKindOf.cpp (BFME 2's
// BitFlags<69> spelling); the Zero Hour BitFlags<116> copy here was not retail's body.

// ------------------------------------------------------------------------------------------------
#pragma optimize("s", on)
Real Thing::calculateHeightAboveTerrain() const 
{
	//USE_PERF_TIMER(ThingMatrixStuff)
	const Coord3D* pos = getPosition();
	Real terrainZ = reinterpret_cast<const BFMERetailTerrainLogicVTable *>(TheTerrainLogic)->getGroundHeight( pos->x, pos->y );
	Real myZ = pos->z;
	return myZ - terrainZ;
}
#pragma optimize("", on)

//-------------------------------------------------------------------------------------------------
Real Thing::getHeightAboveTerrain() const
{
	if (!(m_cacheFlags & VALID_ALTITUDE_TERRAIN))
	{
		m_cachedAltitudeAboveTerrain = reinterpret_cast<const BFMERetailThingVTable *>(this)->calculateHeightAboveTerrain();
		m_cacheFlags |= VALID_ALTITUDE_TERRAIN;
	}
	return m_cachedAltitudeAboveTerrain;
}

//-------------------------------------------------------------------------------------------------
// Thing::getHeightAboveTerrainOrWater: defined in ThingGetHeightAboveTerrainOrWater.cpp (its row's unit).

//=============================================================================
/** If we treat this as airborne, then they slide down slopes.  This checks whether
they are high enough that we should let them act like they're flying. jba. */
//=============================================================================
// ?isSignificantlyAboveTerrain@Thing@@QBE_NXZ present-unmatched
Bool Thing::isSignificantlyAboveTerrain() const 
{
	// If it's high enough that it will take more than 3 frames to return to the ground,
	// then it's significantly airborne.  jba
	return (getHeightAboveTerrain() > -(3*3)*TheGlobalData->m_gravity);
}


//-------------------------------------------------------------------------------------------------
// Thing::convertBonePosToWorldPos is defined with its retail-matched body in Code/GameEngine/Source/Common/Thing/ThingConvertBonePosToWorldPos.cpp (0x0030A528).

// ------------------------------------------------------------------------------------------------
/** Push the 'in' parameter through our transformation matrix and store in 'out' */
// ------------------------------------------------------------------------------------------------
// Thing::transformPoint is defined with its retail-matched body in Code/GameEngine/Source/Common/Thing/ThingTransformPointFinish.cpp (0x0030A812).

// Carrier to keep emitting the 10B Matrix3D::Set_Y_Translation alias rowed from
// this TU after Thing::setPosition moved to ThingSetPosition.cpp.
// ?carrierThingSetYTranslation@@YAXXZ present-unmatched
void carrierThingSetYTranslation()
{
	Matrix3D m;
	m.Set_Y_Translation(0.0f);
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?setPeer@Rva007F9B80@@QAEXPAX@Z=?Set_Y_Translation@Matrix3D@@QAEXM@Z")

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?m@Gen_007f9590@@QAEXH@Z=?Set_Y_Translation@Matrix3D@@QAEXM@Z")
#pragma comment(linker, "/alternatename:?bfmeSetGM@BfmeDerivedGM@@QAEXPAX@Z=?Set_Y_Translation@Matrix3D@@QAEXM@Z")
#pragma comment(linker, "/alternatename:?bfmeAddAEB@BfmeOwnerAEB@@QAEXPAVBfmeThingAEB@@@Z=?Set_Y_Translation@Matrix3D@@QAEXM@Z")
