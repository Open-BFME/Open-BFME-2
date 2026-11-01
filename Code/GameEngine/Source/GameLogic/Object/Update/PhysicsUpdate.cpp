// cl: /FIzh_ascii.h /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /MD /O1 /GX /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /DBFME_MODULE_NO_MPO /DZH_EMIT_POOL_GLUE /Ireference/shims/bfmerendobj /Ireference/shims/debugvtable /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/bfmeanimobj /Ireference/shims/indexbuffercount /Ireference/shims/bfmecaps /Ireference/shims/bfmehcanim /Ireference/shims/bfmevector /Ireference/shims/bfmemapper /Ireference/shims/meshmatdesclayout /Ireference/shims/bfmeshader /Ireference/shims/bfmecpudetect /Ireference/shims/bfmepool /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Ireference/shims/bfmealloc /Ireference/shims/bfmehashtable /Ireference/shims/bfmelist /Ireference/shims/asciistring_downloadmanager /Ireference/shims/stlp_nodealloc /Ireference/shims/asciistring_thin /ICode/GameEngine/Source/Common /Ireference/shims/w3droadbuffer /Ireference/shims/bfmeterraintracks /ICode/Libraries/Include/Lib /Ireference/shims/bfme_namekey /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/shims -ICode/Libraries/Source/Compression/LZHCompress/CompLibHeader /Ireference/shims/bfme2htree /Ireference/shims/bfme2renderobj /Ireference/shims/bfmecamera /Ireference/shims/bfmelight /Ireference/shims/bfmeparticlehandle /Ireference/shims/bfmeparticleload /Ireference/shims/bfmeparticlequat /Ireference/shims/bfmeparticlesave /Ireference/shims/bfmeparticleline /Ireference/shims/bfme2ray /Ireference/shims/bfme2scene -D_STLP_USE_STATIC_LIB -DNDEBUG -DWIN32 -D_WINDOWS /Ireference/shims/bfmefrustum
// stlport
// Ported verbatim from the Generals Zero Hour reference
// (GameEngine/Source/GameLogic/Object/Update/PhysicsUpdate.cpp); this unit had no counterpart under Code/.
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

// PhysicsBehavior.cpp 
// Simple rigid body physics
// Author: Michael S. Booth, November 2001

#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

// please talk to MDC (x36804) before taking this out
#define NO_DEBUG_CRC

#include "Common/PerfTimer.h"
#include "Common/ThingTemplate.h"
#include "Common/Xfer.h"
#include "GameLogic/GameLogic.h"
#include "GameLogic/Module/AIUpdate.h"
#include "GameLogic/Module/BodyModule.h"
#include "GameLogic/Module/ContainModule.h"
#include "GameLogic/Module/CrushDie.h"		// for CrushEnum
#include "GameLogic/Module/PhysicsUpdate.h"
#include "GameLogic/Object.h"
#include "GameLogic/ScriptEngine.h"
#include "GameLogic/TerrainLogic.h"
#include "GameLogic/Weapon.h"
#include "GameLogic/LogicRandomValue.h"

const Real DEFAULT_MASS = 1.0f;

const Real DEFAULT_SHOCK_YAW = 0.05f;
const Real DEFAULT_SHOCK_PITCH = 0.025f;
const Real DEFAULT_SHOCK_ROLL = 0.025f;

const Real DEFAULT_FORWARD_FRICTION = 0.15f;
const Real DEFAULT_LATERAL_FRICTION = 0.15f;
const Real DEFAULT_Z_FRICTION = 0.8f;
const Real DEFAULT_AERO_FRICTION = 0.0f;

// Air friction used to be completely separate and unclamped, so this constant must be split.
// The fact it defaults to 0 shows it.
const Real MIN_AERO_FRICTION = 0.00f;
const Real MIN_NON_AERO_FRICTION = 0.01f;
const Real MAX_FRICTION = 0.99f;

const Real STUN_RELIEF_EPSILON = 0.5f;

#include "Common/CRCDebug.h"
// Suppress this TU's non-retail copy of ?test@?$bitset@$0N@@_STL@@QBE_NI@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> bool bitset<13>::test(unsigned int) const; }

const Int MOTIVE_FRAMES = LOGICFRAMES_PER_SECOND / 3;

#define SLEEPY_PHYSICS

#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif

//-------------------------------------------------------------------------------------------------
static Real angleBetweenVectors(const Coord3D& inCurDir, const Coord3D& inGoalDir)
{
	Vector3 curDir;
	curDir.X = inCurDir.x;
	curDir.Y = inCurDir.y;
	curDir.Z = inCurDir.z;
	curDir.Normalize();

	Vector3 goalDir;
	goalDir.X = inGoalDir.x;
	goalDir.Y = inGoalDir.y;
	goalDir.Z = inGoalDir.z;
	goalDir.Normalize();

	// dot of two unit vectors is cos of angle between them.
	Real cosine = Vector3::Dot_Product(curDir, goalDir);

	// bound it in case of numerical error
	Real angleBetween = (Real)ACos(clamp(-1.0f, cosine, 1.0f));

	return angleBetween;
}

//-------------------------------------------------------------------------------------------------
static Real heightToSpeed(Real height)
{
	// don't bother trying to remember how far we've fallen; instead,
	// back-calc it from our speed & gravity... v = sqrt(2*g*h)
	return sqrt(fabs(2.0f * TheGlobalData->m_gravity * height));
} 

//-------------------------------------------------------------------------------------------------
// LINK-DUP: ??0PhysicsBehaviorModuleData@@QAE@XZ owned by PhysicsBehaviorModuleDataCtor.cpp; declare only here.
// LINK-DUP: ?buildFieldParse@PhysicsBehaviorModuleData@@SAXAAVMultiIniFieldParse@@@Z owned by BehaviorModuleDataBuildFieldParse.cpp; declare only here.
// LINK-DUP: ??0PhysicsBehavior@@QAE@PAVThing@@PBVModuleData@@@Z owned by PhysicsBehaviorCtor.cpp; declare only here.

//-------------------------------------------------------------------------------------------------
static void parseHeightToSpeed( INI* ini, void * /*instance*/, void *store, const void* /*userData*/ )
{
	// don't bother trying to remember how far we've fallen; instead,
	// back-calc it from our speed & gravity... v = sqrt(2*g*h)
	Real height = INI::scanReal(ini->getNextToken());
	*(Real *)store = heightToSpeed(height);
} 

//-------------------------------------------------------------------------------------------------
static void parseFrictionPerSec( INI* ini, void * /*instance*/, void *store, const void* /*userData*/ )
{
	Real fricPerSec = INI::scanReal(ini->getNextToken());
	Real fricPerFrame = fricPerSec * SECONDS_PER_LOGICFRAME_REAL;
	*(Real *)store = fricPerFrame;
} 

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

const Real INVALID_VEL_MAG = -1.0f;

//-------------------------------------------------------------------------------------------------
static ProjectileUpdateInterface* getPui(Object* obj)
{
	if (!obj->isKindOf(KINDOF_PROJECTILE))
		return NULL;

	ProjectileUpdateInterface* objPui = NULL;
	for (BehaviorModule** behaviorModule = obj->getBehaviorModules(); *behaviorModule; ++behaviorModule)
	{
		if ((objPui = (*behaviorModule)->getProjectileUpdateInterface()) != NULL)
			return objPui;
	}
	return NULL;
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
void PhysicsBehavior::setIgnoreCollisionsWith(const Object* obj)
{
	m_ignoreCollisionsWith = obj ? obj->getID() : INVALID_ID; 
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
inline Bool isVerySmall3D(const Coord3D& v)
{
	const Real THRESH = 0.01f;
	return (fabs(v.x) < THRESH && fabs(v.y) < THRESH && fabs(v.z) < THRESH);
}

//-------------------------------------------------------------------------------------------------
inline Bool isZero3D(const Coord3D& v)
{
	return v.x == 0.0f && v.y == 0.0f && v.z == 0.0f;
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------
inline Real calcDistSqr(const Coord3D& lhs, const Coord3D& rhs)
{
	return sqr(lhs.x - rhs.x) + sqr(lhs.y - rhs.y) + sqr(lhs.z - rhs.z);
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
/** 
 * Resolve the collision between getObject() and other by computing
 * the amount the objects have overlapd, and applying proportional forces to 
 * push them apart.
 * Note that this call only applies forces to our object, not to "other".  Since the
 * forces should be equal and opposite, this could be optimized.
 * @todo Make this work properly for non-cylindrical objects (MSB)
 * @todo Physics collision resolution is 2D - should it be 3D? (MSB)
 */
//DECLARE_PERF_TIMER(PhysicsBehavioronCollide)
//-------------------------------------------------------------------------------------------------
static Bool perpsLogicallyEqual( Real perpOne, Real perpTwo )
{
	// Equality with a wiggle fudge.
  const Real PERP_RANGE = 0.15f;
	return fabs( perpOne - perpTwo ) <= PERP_RANGE;
}

//-------------------------------------------------------------------------------------------------
/** Do the collision
 *  Cases:
 *  * The crusheeOther is !OVERLAPPABLE or !CRUSHABLE.								Result: return false
 *  * The crusherMe is !CRUSHER.																			Result: return false
 *  * crusher is CRUSHER, crushee is CRUSHABLE but allied.						Result: return false
 *  * crusher is CRUSHER, crushee is OVERLAPPABLE but not CRUSHABLE.  Result: return false
 *  * crushee has no PhysicsBehavior.																	Result: return false
 *  * crusher is CRUSHER, crushee is CRUSHABLE, but is too hard.			Result: return false
 *  * crusher is CRUSHER, crushee is CRUSHABLE, hardness ok.					Result: crush, return true
 *
 * Return true if we want to skip having physics push us apart // LORENZEN
 */
//-------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
/** Test whether unit needs to die because of being on illegal cell, upside down, outside legal bounds **/
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
/** CRC */
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
/** Xfer method
	* Version Info:
	* 1: Initial version */
// ------------------------------------------------------------------------------------------------
// byte-exact reconstruction: Code/GameEngine/Source/GameLogic/Object/Update/PhysicsBehaviorXfer.cpp

// ------------------------------------------------------------------------------------------------
/** Load post process */
// ------------------------------------------------------------------------------------------------