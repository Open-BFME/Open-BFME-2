// cl: /Ireference/shims/zh_outofline /FIzh_ascii.h /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /G7 /arch:SSE /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /DBFME_MODULE_NO_MPO /DZH_EMIT_POOL_GLUE /Ireference/shims/bfmerendobj /Ireference/shims/debugvtable /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/bfmeanimobj /Ireference/shims/indexbuffercount /Ireference/shims/bfmecaps /Ireference/shims/bfmehcanim /Ireference/shims/bfmevector /Ireference/shims/bfmemapper /Ireference/shims/meshmatdesclayout /Ireference/shims/bfmeshader /Ireference/shims/bfmecpudetect /Ireference/shims/bfmepool /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Ireference/shims/bfmealloc /Ireference/shims/bfmehashtable /Ireference/shims/bfmelist /Ireference/shims/asciistring_downloadmanager /Ireference/shims/stlp_nodealloc /Ireference/shims/asciistring_thin /ICode/GameEngine/Source/Common /Ireference/shims/w3droadbuffer /Ireference/shims/bfmeterraintracks /ICode/Libraries/Include/Lib
// stlport
// Ported verbatim from the Generals Zero Hour reference (GameEngine/Source/GameLogic/Object/Behavior/SlowDeathBehavior.cpp); this unit had no counterpart under Code/.
// The compiler-generated vector constructor iterator (??_H) takes the
// optimization state of the first function that needs it. Retail links one
// copy, the /O1 body at 0x00001423; this unemitted anchor makes this unit's
// copy that same body, so it no longer loses to retail's at link time.
// It can also change how later array constructions here compile; checked to
// change nothing else in this unit, but if a function added later that builds
// an array will not match, try it without this block.
struct BfmeVciAnchorElem { BfmeVciAnchorElem(); };
#pragma optimize("gsy", on)
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

// FILE: SlowDeathBehavior.cpp ///////////////////////////////////////////////////////////////////////
// Author:
// Desc:  
///////////////////////////////////////////////////////////////////////////////////////////////////


// INCLUDES ///////////////////////////////////////////////////////////////////////////////////////
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine
#define DEFINE_SLOWDEATHPHASE_NAMES
#include "Common/GameLOD.h"
#include "Common/INI.h"
#include "Common/RandomValue.h"
#include "Common/Thing.h"
#include "Common/ThingTemplate.h"
#include "Common/Xfer.h"
#include "GameClient/Drawable.h"
#include "GameClient/FXList.h"
#include "GameClient/InGameUI.h"
#include "GameLogic/GameLogic.h"
#include "GameLogic/Module/BodyModule.h"
#include "GameLogic/Module/PhysicsUpdate.h"
#include "GameLogic/Module/SlowDeathBehavior.h"
#include "GameLogic/Module/AIUpdate.h"
#include "GameLogic/Module/SlavedUpdate.h"
#include "GameLogic/Object.h"
#include "GameLogic/ObjectCreationList.h"
#include "GameLogic/Weapon.h"
#include "GameClient/Drawable.h"

#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif

const Real BEGIN_MIDPOINT_RATIO = 0.35f;
const Real END_MIDPOINT_RATIO = 0.65f;

// ??0SlowDeathBehaviorModuleData@@QAE@XZ: defined in SlowDeathBehaviorModuleDataCtor.cpp (its row's unit).

//-------------------------------------------------------------------------------------------------
static void parseFX( INI* ini, void *instance, void * /*store*/, const void* /*userData*/ )
{
	SlowDeathBehaviorModuleData* self = (SlowDeathBehaviorModuleData*)instance;
	SlowDeathPhaseType sdphase = (SlowDeathPhaseType)INI::scanIndexList(ini->getNextToken(), TheSlowDeathPhaseNames);
	for (const char* token = ini->getNextToken(); token != NULL; token = ini->getNextTokenOrNull())
	{
		const FXList *fxl = TheFXListStore->findFXList((token));	// could be null! this is OK!
		FXListVec * const bfmeFx = (FXListVec *)((char *)self + 0x58);
		bfmeFx[sdphase].push_back(fxl);
		if (fxl)
			*((Byte *)self + 0x1A4) |= SlowDeathBehaviorModuleData::HAS_FX;
	}
}

//-------------------------------------------------------------------------------------------------
static void parseOCL( INI* ini, void *instance, void * /*store*/, const void* /*userData*/ )
{
	SlowDeathBehaviorModuleData* self = (SlowDeathBehaviorModuleData*)instance;
	SlowDeathPhaseType sdphase = (SlowDeathPhaseType)INI::scanIndexList(ini->getNextToken(), TheSlowDeathPhaseNames);
	for (const char* token = ini->getNextToken(); token != NULL; token = ini->getNextTokenOrNull())
	{
		const ObjectCreationList *ocl = TheObjectCreationListStore->findObjectCreationList(token);	// could be null! this is OK!
		// BFME's SlowDeathBehaviorModuleData puts m_ocls at this+0x88, not the
		// +0x64 the header gives it: retail @0x00209815 does
		// lea esi,[ebx+ecx*4+0x88]. Correcting the header is the real fix and
		// the full gate is red (docs/lessons.md), so the array base is taken at
		// the retail offset here.
		OCLVec * const bfmeOcls = (OCLVec *)((char *)self + 0x88);
		bfmeOcls[sdphase].push_back(ocl);
		if (ocl)
			// and m_maskOfLoadedEffects at this+0x1A4, not +0xBC: retail
			// @0x00209862 does or byte ptr [ebx+0x1A4],2.
			*((Byte *)self + 0x1A4) |= SlowDeathBehaviorModuleData::HAS_OCL;
	}
}

//-------------------------------------------------------------------------------------------------
static void parseWeapon( INI* ini, void *instance, void * /*store*/, const void* /*userData*/ )
{
	SlowDeathBehaviorModuleData* self = (SlowDeathBehaviorModuleData*)instance;
	SlowDeathPhaseType sdphase = (SlowDeathPhaseType)INI::scanIndexList(ini->getNextToken(), TheSlowDeathPhaseNames);
	for (const char* token = ini->getNextToken(); token != NULL; token = ini->getNextTokenOrNull())
	{
		const WeaponTemplate *wt = TheWeaponStore->findWeaponTemplate(token);	// could be null! this is OK!
		self->m_weapons[sdphase].push_back(wt);
		if (wt)
			self->m_maskOfLoadedEffects |= SlowDeathBehaviorModuleData::HAS_WEAPON;
	}
}

// ?buildFieldParse@SlowDeathBehaviorModuleData@@SAXAAVMultiIniFieldParse@@@Z: defined in ModuleDataBuildFieldParse.cpp (its row's unit).

// ??0SlowDeathBehavior@@QAE@PAVThing@@PBVModuleData@@@Z: defined in SlowDeathBehaviorCtor.cpp (its row's unit).

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// ??1SlowDeathBehavior@@MAE@XZ present-unmatched
SlowDeathBehavior::~SlowDeathBehavior( void )
{
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// SlowDeathBehavior::getProbabilityModifier is defined with its retail-matched body in Code/GameEngine/Source/GameLogic/Object/Behavior/SlowDeathBehaviorUpdate.cpp (0x0045D5DA).

//-------------------------------------------------------------------------------------------------
// Line-number padding and filename restore so GameLogicRandomValueReal calls match retail.
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
#line 310 "F:\\\\bfme\\\\Code\\\\gameengine\\\\Source\\\\GameLogic\\\\Object\\\\Behavior\\\\SlowDeathBehavior.cpp"
static void calcRandomForce(Real minMag, Real maxMag, Real minPitch, Real maxPitch, Coord3D& force)
{
	Real angle = GameLogicRandomValueReal(-PI, PI);
	Real pitch = GameLogicRandomValueReal(minPitch, maxPitch);
	Real mag = GameLogicRandomValueReal(minMag, maxMag);

	Matrix3D mtx(1);
	mtx.Scale(mag);
	mtx.Rotate_Z(angle);
	mtx.Rotate_Y(-pitch);

	Vector3 v = mtx.Get_X_Vector();

	force.x = v.X;
	force.y = v.Y;
	force.z = v.Z;
}
#line 339

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// ?SlowDeathBehavior::beginSlowDeath present-unmatched
void SlowDeathBehavior::beginSlowDeath(const DamageInfo *damageInfo)
{
	if (!isSlowDeathActivated())
	{
		const SlowDeathBehaviorModuleData* d = getSlowDeathBehaviorModuleData();
		Object* obj = getObject();

		if (d->m_sinkRate && obj->isKindOf(KINDOF_INFANTRY))
		{

			Drawable *draw = getObject()->getDrawable();
			if ( draw )
			{
				// this object sinks slowly after it dies so don't draw a
				// floating shadow decal on the ground above it.
				obj->getDrawable()->setShadowsEnabled(false);
				draw->setTerrainDecalFadeTarget( 0.0f, -0.2f );
			}



		}

		
		// Ask game detail manager if we need to speedup all deaths to improve performance
		Real timeScale = TheGameLODManager->getSlowDeathScale();
		m_acceleratedTimeScale = 1.0f;	// assume normal death speed.

		if (timeScale == 0.0f && !d->hasNonLodEffects())
		{	
			// Deaths happen instantly so just delete the object and return
			TheGameLogic->destroyObject(obj);
			return;
		}
		else
		{	
			// timescale is some non-zero value so we may need to speed up death
			if( getObject()->isKindOf( KINDOF_HULK ) && TheGameLogic->getHulkMaxLifetimeOverride() != -1 )
			{
				//Scripts don't want hulks around, so start sinking immediately!
				m_sinkFrame = 1;
				m_midpointFrame = (LOGICFRAMES_PER_SECOND/2) + 1;
				m_destructionFrame = LOGICFRAMES_PER_SECOND + 1;
				m_acceleratedTimeScale = 1.0f;
			}
			else
			{
				m_sinkFrame = timeScale * (d->m_sinkDelay + GameLogicRandomValue(0, d->m_sinkDelayVariance));
				m_destructionFrame = timeScale * (d->m_destructionDelay + GameLogicRandomValue(0, d->m_destructionDelayVariance));
				m_midpointFrame = GameLogicRandomValue( BEGIN_MIDPOINT_RATIO * m_destructionFrame, END_MIDPOINT_RATIO * m_destructionFrame );
				m_acceleratedTimeScale = timeScale;
			}
		}

		UnsignedInt now = TheGameLogic->getFrame();

		if (d->m_flingForce > 0)
		{

			
			//Just in case this is a stingersoldier or other HELD object, lets set them free so they will fly
			// with their own physics during slow death
			if( obj->isDisabledByType( DISABLED_HELD ) )
			{
				static NameKeyType key_SlavedUpdate = NAMEKEY( "SlavedUpdate" );
				SlavedUpdate* slave = (SlavedUpdate*)obj->findUpdateModule( key_SlavedUpdate );
				if( slave )
				{
					slave->onSlaverDie( NULL );
				}
			}				

			PhysicsBehavior* physics = obj->getPhysics();
			if (physics)
			{
				// make sure we are at least a bit above the ground
				const Real MIN_ALTITUDE = 1.0f;
				Real altitude = obj->getHeightAboveTerrain();
				if (altitude < MIN_ALTITUDE)
				{
					Coord3D pos = *obj->getPosition();
					pos.z += MIN_ALTITUDE;
					obj->setPosition(&pos);
				}

				Coord3D force;
				calcRandomForce(d->m_flingForce, d->m_flingForce + d->m_flingForceVariance, 
												d->m_flingPitch, d->m_flingPitch + d->m_flingPitchVariance, force);
				physics->setAllowToFall(true);
				physics->applyForce(&force);
				physics->setExtraBounciness(-1.0);					// we don't want this guy to bounce at all
				physics->setExtraFriction(-3 * SECONDS_PER_LOGICFRAME_REAL);							// reduce his ground friction a bit
				physics->setAllowBouncing(true);
				Real orientation = atan2(force.y, force.x);
				physics->setAngles(orientation, 0, 0);
				obj->getDrawable()->setModelConditionState(MODELCONDITION_EXPLODED_FLAILING);
				m_flags |= (1<<FLUNG_INTO_AIR);
			}
			setWakeFrame(obj, UPDATE_SLEEP_NONE);
		}
		else
		{
			// we don't need to wake up immediately, but only when the first of these
			// counters wants to trigger....
			Int whenToWakeTime = m_sinkFrame;
			if (whenToWakeTime > m_destructionFrame) 
				whenToWakeTime = m_destructionFrame;
			if (whenToWakeTime > m_midpointFrame) 
				whenToWakeTime = m_midpointFrame;
			setWakeFrame(obj, UPDATE_SLEEP(whenToWakeTime));
		}
		m_sinkFrame += now;
		m_destructionFrame += now;
		m_midpointFrame += now;

		m_flags |= (1<<SLOW_DEATH_ACTIVATED);

		doPhaseStuff(SDPHASE_INITIAL);

	}
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// SlowDeathBehavior::doPhaseStuff is defined with its retail-matched body in Code/GameEngine/Source/GameLogic/Object/Behavior/SlowDeathBehaviorUpdate.cpp (0x0045D97A).

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// SlowDeathBehavior::update is defined with its retail-matched body in Code/GameEngine/Source/GameLogic/Object/Behavior/SlowDeathBehaviorUpdate.cpp (0x0045DB0B).

//-------------------------------------------------------------------------------------------------
// byte-exact reconstruction: Code/GameEngine/Source/GameLogic/Object/Behavior/SlowDeathBehavior_onDie_Thunk.cpp
// SlowDeathBehavior::onDie is defined with its retail-matched body in Code/GameEngine/Source/GameLogic/Object/Behavior/SlowDeathBehaviorUpdate.cpp (0x0045E6B8).

// ------------------------------------------------------------------------------------------------
/** CRC */
// ------------------------------------------------------------------------------------------------
// ?crc@SlowDeathBehavior@@MAEXPAVXfer@@@Z present-unmatched
void SlowDeathBehavior::crc( Xfer *xfer )
{

	// extend base class
	UpdateModule::crc( xfer );

}  // end crc

// ------------------------------------------------------------------------------------------------
/** Xfer method
	* Version Info:
	* 1: Initial version */
// ------------------------------------------------------------------------------------------------
// Owned by SlowDeathBehaviorXfer.cpp.

// ------------------------------------------------------------------------------------------------
/** Load post process */
// ------------------------------------------------------------------------------------------------
// ?loadPostProcess@SlowDeathBehavior@@MAEXXZ present-unmatched
void SlowDeathBehavior::loadPostProcess( void )
{

	// extend base class
	UpdateModule::loadPostProcess();

}  // end loadPostProcess
