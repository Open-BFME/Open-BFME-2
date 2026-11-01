// cl: /Ireference/shims/weapon_outofline /Ireference/shims/zh_outofline /Ireference/shims/updatemodule_ctor /Ireference/shims/bfme2_vector3 /FIzh_ascii.h /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /G7 /arch:SSE /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /DBFME_MODULE_NO_MPO /DZH_EMIT_POOL_GLUE /Ireference/shims/bfmerendobj /Ireference/shims/debugvtable /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/bfmeanimobj /Ireference/shims/indexbuffercount /Ireference/shims/bfmecaps /Ireference/shims/bfmehcanim /Ireference/shims/bfmevector /Ireference/shims/bfmemapper /Ireference/shims/meshmatdesclayout /Ireference/shims/bfmeshader /Ireference/shims/bfmecpudetect /Ireference/shims/bfmepool /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Ireference/shims/bfmealloc /Ireference/shims/bfmehashtable /Ireference/shims/bfmelist /Ireference/shims/asciistring_downloadmanager /Ireference/shims/stlp_nodealloc /Ireference/shims/asciistring_thin /ICode/GameEngine/Source/Common /Ireference/shims/w3droadbuffer /Ireference/shims/bfmeterraintracks /ICode/Libraries/Include/Lib
// stlport
// Ported verbatim from the Generals Zero Hour reference (GameEngine/Source/GameLogic/Object/Behavior/DumbProjectileBehavior.cpp); this unit had no counterpart under Code/.
#define Matrix4x4 Matrix4  // BFME renamed it
#define __PLACEMENT_VEC_NEW_INLINE  // always.h/GameMemory.h define array placement-new themselves
// stlport
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

// FILE: DumbProjectileBehavior.cpp
// Author: Steven Johnson, July 2002
// Desc:   

// Select the frozen Vector3 view before transitive donor headers. Its
// Normalize/Length COMDATs are independently verified at retail RVAs.
#include "vector3.h"
// Bind the shared retail clear before KindOf.h instantiates its inline helpers.
// GameMemory supplies array placement new; select the same guard as PreRTS
// before the early STL headers so the CRT does not define it a second time.
#define __PLACEMENT_VEC_NEW_INLINE
#include "Lib/Basetype.h"
#include "Common/BitFlags.h"
template <> void BitFlags<116>::clear();

#line 38
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#include "Common/BezierSegment.h"
#include "Common/GameCommon.h"
#include "Common/GameState.h"
#include "Common/Player.h"
#include "Common/ThingTemplate.h"
#include "Common/RandomValue.h"
#include "Common/Xfer.h"
#include "GameClient/Drawable.h"
#include "GameClient/FXList.h"
#include "GameLogic/GameLogic.h"
#include "GameLogic/Object.h"
#include "GameLogic/PartitionManager.h"
#include "GameLogic/Module/ContainModule.h"
#include "GameLogic/Module/DumbProjectileBehavior.h"
#include "GameLogic/Module/MissileAIUpdate.h"
#include "GameLogic/Module/PhysicsUpdate.h"
#include "GameLogic/Weapon.h"
// bfme link decl-only begin
namespace _STL { template <> unsigned long _Base_bitset<4>::_S_maskbit(unsigned int); }
// bfme link decl-only end

// BFME 2's Object keeps its behavior list at +0x244 (the matched
// Object::findModule 0x0028B6D6 walks it there), its contain module at +0x250
// and its body module at +0x254; this tree's Zero Hour Object.h has +0x18C,
// +0x190 and +0x194. This unit reads them through these functions instead of
// the header's inline getters, whose Zero Hour copies would otherwise come
// early in link order and displace every BFME 2 unit's copy (retail has no
// out-of-line Object getter: the 7-byte bodies at 0x00313E8C/93/9A are
// GameWindow text-colour getters).
static BehaviorModule **getRetailBehaviorModules( const Object *obj ) { return *(BehaviorModule ** const *)((const char *)obj + 0x244); }
static ContainModuleInterface *getRetailContain( const Object *obj ) { return *(ContainModuleInterface * const *)((const char *)obj + 0x250); }
static BodyModuleInterface *getRetailBodyModule( const Object *obj ) { return *(BodyModuleInterface * const *)((const char *)obj + 0x254); }

// vector<Coord3D>::erase is one shared STLport instantiation in retail
// (0x002A133B: BezierSegment's clear, vector<Coord3D>::resize 0x000CA2F3 and
// AIStateMachine's ctor/clear all call it) and it passes its copy tag by
// reference. This unit's bfmealloc headers would instantiate a by-value-tag
// copy, the first of that name in link order, so the constructor's
// m_flightPath.clear() uses the shared instantiation instead of emitting one.
template <> Coord3D *std::vector<Coord3D>::erase( Coord3D *first, Coord3D *last );

// This unit imports free (no /D_CRTIMP=), so its out-of-line vector<Coord3D>
// deallocation helpers call __imp__free where every other unit's call _free.
// Nothing here calls them out of line, but as the first copies in link order
// they displaced the rest. Declared imported and force-inlined (bodies
// verbatim from the headers), they are not emitted.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void allocator<Coord3D>::deallocate(Coord3D *__p, size_t __n) const {
  _STLP_ASSERT( (__p == 0) == (__n == 0) )
    if (__p != 0) ::free((void*)__p);
}
template <> __declspec(dllimport) __forceinline
void _STLP_alloc_proxy<Coord3D*, Coord3D, allocator<Coord3D> >::deallocate(Coord3D *__p, size_t __n) {
    __stl_alloc_rebind(__STATIC_CAST(_Base&, *this),(Coord3D*)0).deallocate(__p, __n);
}
template <> __declspec(dllimport) __forceinline
_Vector_base<Coord3D, allocator<Coord3D> >::~_Vector_base() {
    if (_M_start !=0)
    _M_end_of_storage.deallocate(_M_start, _M_end_of_storage._M_data - _M_start);
}
// The vector destructor itself is called out of line (retail 0x0007FAB3, 14B,
// a direct _free call); this unit's copy would inline __imp__free (15B) and,
// first in link order, displace every retail-equal copy. Declare it only.
template <> vector<Coord3D, allocator<Coord3D> >::~vector();
}

#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
const Int DEFAULT_MAX_LIFESPAN = 10 * LOGICFRAMES_PER_SECOND;

//-----------------------------------------------------------------------------
// ??0DumbProjectileBehaviorModuleData@@ present-unmatched
DumbProjectileBehaviorModuleData::DumbProjectileBehaviorModuleData() : 
	m_maxLifespan(DEFAULT_MAX_LIFESPAN),
	m_detonateCallsKill(FALSE),
	m_orientToFlightPath(TRUE),
	m_tumbleRandomly(FALSE),
	m_firstHeight(0.0f),
	m_secondHeight(0.0f),
	m_firstPercentIndent(0.0f),
	m_secondPercentIndent(0.0f),	
	m_garrisonHitKillCount(0),
	m_garrisonHitKillFX(NULL),
	m_flightPathAdjustDistPerFrame(0.0f)
{
}

//-----------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
// ??0DumbProjectileBehavior@@ present-unmatched
DumbProjectileBehavior::DumbProjectileBehavior( Thing *thing, const ModuleData* moduleData ) : UpdateModule( thing, moduleData )
{
	m_launcherID = INVALID_ID;
	m_victimID = INVALID_ID;
	m_detonationWeaponTmpl = NULL;
	m_lifespanFrame = 0;
	m_flightPath.clear();
	m_flightPathSegments = 0;
	m_flightPathSpeed = 0;
	m_flightPathStart.zero();
	m_flightPathEnd.zero();
	m_currentFlightPathStep = 0;
	m_extraBonusFlags = 0;

  m_hasDetonated = FALSE;
} 

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
inline Bool within(Real min, Real val, Real max)
{
	return min <= val && val <= max;
}

//-------------------------------------------------------------------------------------------------
inline Bool notWithin(Real min, Real val, Real max)
{
	return val < min || val > max;
}

#ifdef NOT_IN_USE

#define NO_ONLY_RETURN_CLIPPED_PITCHES

//-------------------------------------------------------------------------------------------------
static Bool calcTrajectory(
	const Coord3D& start,		// in: where the projectile starts
	const Coord3D& end,			// in: where the projectile wants to end up
	Real velocity,					// in: the initial speed of the projectile
	Real minPitch,					// in: min pitch (-PI/2)
	Real maxPitch,					// in: max pitch (-PI/2)
	Bool preferShortPitch,	// in: prefer the shorter or longer path?
	Real& angle,						// out: the angle to aim
	Real& pitch							// out: the pitch to aim for 
)
{
	Bool exactTarget = false;

	angle = 0.0f;
	pitch = 0.0f;

	if (velocity <= 0.0f)
	{
		DEBUG_CRASH(("cant get there from here (1)"));
		return false;
	}

	Real dx = end.x - start.x;
	Real dy = end.y - start.y;
	Real dz = end.z - start.z;

	// calculating the angle is trivial.
	angle = atan2(dy, dx);

	// calculating the pitch requires a bit more effort.
	Real horizDistSqr = sqr(dx) + sqr(dy);
	Real horizDist = sqrt(horizDistSqr);

	// calc the two possible pitches that will cover the given horizontal range.
	// (this is actually only true if dz==0, but is a good first guess)
	Real gravity = fabs(TheGlobalData->m_gravity);
	Real gravityTwoDZ = gravity * 2.0f * dz;

	// let's start by aiming directly for it. we know this isn't right (unless gravity
	// is zero, which it's not) but is a good starting point...
	Real theta = atan2(dz, horizDist);
	// if the angle isn't pretty shallow, we can get a better initial guess by using
	// the code below...
	const Real SHALLOW_ANGLE = 0.5f * PI / 180.0f;
	if (fabs(theta) > SHALLOW_ANGLE)
	{
		Real t = horizDist / velocity;
		Real vz = (dz/t + 0.5f*gravity*t);
		Real sineOfAngle = clamp(-1.0f, vz / velocity, 1.0f);
		theta = ASin(sineOfAngle)*0.5f;
	}

/*
	this is, in theory, the "right" formula for dz==0, but I
	get better results with the stuff above:

	Real sineOfAngle = (gravity * horizDist) / sqr(velocity);
	if (sineOfAngle > 1.0f)
	{
		return false;	
	}
	Real theta = ASin(sineOfAngle)*0.5f;
*/

	Real pitches[2];
	Real cosPitches[2];
	Real sinPitches[2];
	Real theta_min = max(minPitch, -PI/2);
	Real theta_max = min(maxPitch, PI/2);
	const Real MIN_ANGLE_DIFF = (PI/(180.0f*16.0f));	// 1/16th of a degree. yes, we need that accuracy.
//Int numLoops = 0;
	while (theta_max > theta_min + MIN_ANGLE_DIFF)
	{
//++numLoops;
		pitches[0] = theta;	// shallower angle
		pitches[1] = (theta >= 0.0) ? (PI/2 - theta) : (-PI/2 - theta);	// steeper angle
		
		DEBUG_ASSERTCRASH(pitches[0]<=PI/2&&pitches[0]>=-PI/2,("bad pitches[0] %f\n",rad2deg(pitches[0])));
		DEBUG_ASSERTCRASH(pitches[1]<=PI/2&&pitches[1]>=-PI/2,("bad pitches[1] %f\n",rad2deg(pitches[1])));

		// calc the horiz-speed & time for each.
		// note that time can only be negative for 90<angle<270, and since we
		// ruled those out above, we're gold.
		sinPitches[0] = Sin(pitches[0]);
		sinPitches[1] = Sin(pitches[1]);
		cosPitches[0] = Cos(pitches[0]); 
		cosPitches[1] = Cos(pitches[1]);
		Real t0 = (horizDist / (velocity * cosPitches[0]));
		Real t1 = (horizDist / (velocity * cosPitches[1]));

		t0 = MAX(0,t0);
		t1 = MAX(0,t1);


		DEBUG_ASSERTCRASH(t0>=0&&t1>=0,("neg time"));
		
		Int preferred = ((t0 < t1) == (preferShortPitch)) ? 0 : 1;

		// ok, NOW... since dz is virtually NEVER zero, do a little approximation
		// to get a better guess. (solving the equations directly are hard and
		// it's simpler to approximate)
		Bool tooClose = false;
		Real vx, vz, root;

		vz = velocity*sinPitches[preferred];

		root = sqr(vz) - gravityTwoDZ;
		if (root < 0.0f)
		{
			// oops, no solution for our preferred pitch. try the other one.
			if (preferred == 0)	
				tooClose = true;	// if this fails for the shallow case, it's 'cuz the result is too close
			preferred = 1 - preferred;
			vz = velocity*sinPitches[preferred];
			root = sqr(vz) - gravityTwoDZ;
			if (root < 0.0f)
			{
				DEBUG_CRASH(("cant get there from here (2)"));
				return false;
			}
		}

#ifdef ONLY_RETURN_CLIPPED_PITCHES
		// if we get this far, we have some plausible solution...
		// it actually may be off, but let's go ahead and set the result
		// (along with the "exact" flag) so that the caller will want to
		// try to use the result. (we'll probably iterate and overwrite
		// this result with a more precise one.)
		if (within(minPitch, pitches[preferred], maxPitch))
		{
			pitch = pitches[preferred];
			exactTarget = true;
		}
#else
		// if we get this far, we have some plausible solution...
		// it actually may be off, but let's go ahead and set the result
		// (along with the "exact" flag) so that the caller will want to
		// try to use the result. (we'll probably iterate and overwrite
		// this result with a more precise one.) NOTE however that we
		// don't validate it's within the proper range... caller must do that!
		pitch = pitches[preferred];
		exactTarget = true;
#endif

		vx = velocity*cosPitches[preferred];
		Real actualRange = (vx*(vz + sqrt(root)))/gravity;
		const Real CLOSE_ENOUGH_RANGE = 5.0f;
		if (tooClose || (actualRange < horizDist - CLOSE_ENOUGH_RANGE))
		{
			theta_min = theta;
			theta = (theta + theta_max) * 0.5f;
		}
		else if (actualRange > horizDist + CLOSE_ENOUGH_RANGE)
		{
			theta_max = theta;
			theta = (theta + theta_min) * 0.5f;
		}
		else
		{
			break;
		}
	}

//DEBUG_LOG(("took %d loops to find a match\n",numLoops));
	if (exactTarget)
		return true;

	return false;
}

#endif NOT_IN_USE

//-------------------------------------------------------------------------------------------------
// Prepares the missile for launch via proper weapon-system channels.
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// The actual firing of the missile once setup. Uses a Bezier curve with points parameterized in ini
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
/**
 * Simulate one frame of a missile's behavior
 */
// ?update@DumbProjectileBehavior@@ present-unmatched
UpdateSleepTime DumbProjectileBehavior::update()
{
	const DumbProjectileBehaviorModuleData* dumbProjectileBehaviorModuleData = getDumbProjectileBehaviorModuleData();

	if (m_lifespanFrame != 0 && TheGameLogic->getFrame() >= m_lifespanFrame)
	{
		// lifetime demands detonation
		detonate();
		return UPDATE_SLEEP_NONE;
	}

	if( m_currentFlightPathStep >= m_flightPath.size() )
	{
		// No more steps to use. Would go out of bounds on vector, so have to do something.
		// We could allow physics to take over and make us fall, but the point of this whole task
		// is to guarentee where the shell explodes.  This way, it _will_ explode at the target point.
		detonate();
		return UPDATE_SLEEP_NONE;
	}

	if (m_victimID != INVALID_ID && dumbProjectileBehaviorModuleData->m_flightPathAdjustDistPerFrame > 0.0f)
	{
		Object* victim = TheGameLogic->findObjectByID(m_victimID);
		if (victim)
		{
			Coord3D newVictimPos;
			victim->getGeometryInfo().getCenterPosition(*victim->getPosition(), newVictimPos);
			Coord3D delta;
			delta.x = newVictimPos.x - m_flightPathEnd.x;
			delta.y = newVictimPos.y - m_flightPathEnd.y;
			delta.z = newVictimPos.z - m_flightPathEnd.z;
			Real distVictimMovedSqr = sqr(delta.x) + sqr(delta.y) + sqr(delta.z);
			if (distVictimMovedSqr > 0.1f)
			{
				Real distVictimMoved = sqrtf(distVictimMovedSqr);
				if (distVictimMoved > dumbProjectileBehaviorModuleData->m_flightPathAdjustDistPerFrame)
					distVictimMoved = dumbProjectileBehaviorModuleData->m_flightPathAdjustDistPerFrame;
				delta.normalize();
				m_flightPathEnd.x += distVictimMoved * delta.x;
				m_flightPathEnd.y += distVictimMoved * delta.y;
				m_flightPathEnd.z += distVictimMoved * delta.z;
				if (!calcFlightPath(false))
				{
					DEBUG_CRASH(("Hmm, recalc of flight path returned false... should this happen?"));
					detonate();
					return UPDATE_SLEEP_NONE;
				}
			}
		}
	}

	//Otherwise, continue to force the flight path
	Coord3D flightStep = m_flightPath[m_currentFlightPathStep];

	if (dumbProjectileBehaviorModuleData->m_orientToFlightPath && (!dumbProjectileBehaviorModuleData->m_tumbleRandomly) )
  {
    if ( m_currentFlightPathStep > 0)
	  {
	  // this seems reasonable; however, if this object has a PhysicsBehavior on it, this calc will be wrong, 
	  // since Physics is applying gravity, which we duly ignore, but the prevPos won't be what we expect.
	  // get it from the flight path instead. (srj)
	  //Coord3D prevPos = *getObject()->getPosition();

		  Coord3D prevPos = m_flightPath[m_currentFlightPathStep - 1];

		  Vector3 curDir;
		  curDir.X = flightStep.x - prevPos.x;
		  curDir.Y = flightStep.y - prevPos.y;
		  curDir.Z = flightStep.z - prevPos.z;
		  curDir.Normalize();	// buildTransformMatrix wants it this way
      Matrix3D orientMtx;
		  Vector3 flightPosition;
		  flightPosition.X = flightStep.x;
		  flightPosition.Y = flightStep.y;
		  flightPosition.Z = flightStep.z;
		  orientMtx.buildTransformMatrix(flightPosition, curDir);
		  getObject()->setTransformMatrix(&orientMtx);
    }
    else // oops! how do we orient the projectile on the zeroeth frame? This didn't matter until we started using the
      //long, blurry projectile graphics which look badly oriented on step 0 of the flight path
      // so lets orient it the same as if it were on frame 1!
    {
		  Coord3D prevPos = m_flightPath[0];
		  Coord3D curPos = m_flightPath[1];

		  Vector3 curDir;
		  curDir.X = curPos.x - prevPos.x;
		  curDir.Y = curPos.y - prevPos.y;
		  curDir.Z = curPos.z - prevPos.z;
		  curDir.Normalize();	// buildTransformMatrix wants it this way
      Matrix3D orientMtx;
		  Vector3 flightPosition;
		  flightPosition.X = flightStep.x;
		  flightPosition.Y = flightStep.y;
		  flightPosition.Z = flightStep.z;
		  orientMtx.buildTransformMatrix(flightPosition, curDir);
		  getObject()->setTransformMatrix(&orientMtx);
    }

	}
	else
	{
		getObject()->setPosition(&flightStep);
	}

	// note that we want to use getHighestLayerForDestination() here, so that anything even slightly
	// below the bridge translates into GROUND. (getLayerForDestination just does a "closest" check)
	PathfindLayerEnum oldLayer = getObject()->getLayer();
	PathfindLayerEnum newLayer = TheTerrainLogic->getHighestLayerForDestination(getObject()->getPosition());
	getObject()->setLayer(newLayer);

	if (oldLayer != LAYER_GROUND && newLayer == LAYER_GROUND)
	{
		// see if we' still in the bridge's xy area
		Coord3D tmp = *getObject()->getPosition();
		tmp.z = 9999.0f;
		PathfindLayerEnum testLayer = TheTerrainLogic->getHighestLayerForDestination(&tmp);
		if (testLayer == oldLayer)
		{
			// ensure we are slightly above the bridge, to account for fudge & sloppy art
			const Real FUDGE = 2.0f;
			tmp.z = TheTerrainLogic->getLayerHeight(tmp.x, tmp.y, testLayer) + FUDGE;
			getObject()->setPosition(&tmp);
			// blow'd up!
			detonate();
			return UPDATE_SLEEP_NONE;
		}
	}

	++m_currentFlightPathStep;

	return UPDATE_SLEEP_NONE;//This no longer flys with physics, so it needs to not sleep
}

// ------------------------------------------------------------------------------------------------
/** displayFlightPath for debugging */
// ------------------------------------------------------------------------------------------------
#if defined(_DEBUG) || defined(_INTERNAL)
#endif

// ------------------------------------------------------------------------------------------------
/** CRC */
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
/** Xfer method
	* Version Info:
	* 1: Initial version */
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
/** Load post process */
// ------------------------------------------------------------------------------------------------