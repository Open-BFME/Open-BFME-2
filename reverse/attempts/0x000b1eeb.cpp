// ?setModelName@W3DDebrisDraw@@UAEXVAsciiString@@HW4ShadowType@@@Z
// partial score=0.9 date=2026-10-08
// Banked native-layout reconstruction; no ledger admission or provider pins.
// Boundary B1EEB..B207F RET12; WorldBuilder VA957710 names setModelName.
// Donor: own full legacy source and BF1 full W3DDebrisDraw.cpp at9cbfb551.
// Retail changes: options16B, drawable userdata248, shadow params40B.
// Matrix scope now reproduces frame40; trial405B vs404B (OR EAX vs AL,
// colour stores reordered), with3 unresolved descriptor/creation calls.
// Ctor79514/dtor793FA/assign9A41B are historically labelled AudioEventRTS.
// Verified callers include Shadow-table parserB9AFF and terrain claim decal
// 4E65CF; neutral shadow descriptor here does not assert the original name.
// Six existing consumer units carry10 verified ctor/dtor references; reconcile
// those providers and consumers before adding any binding. Actual audio
// virtual dtor pin4EC395 differs; old UAE->QAE alias must be reviewed.
// Creation9A8D3 whole302B dispatches descriptor+8; args(render,params,drawable),
// returns pointer, RET12; independent native ABI evidence read in this pass.
// Removal518E0 is an existing12B stdcall vslot2 thunk; rewrite the historical
// Gen0003AC38 spelling to existing Rva000518E0Thunk in a future verified trial.
// cl: /O1 /arch:SSE /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/open-bfme-1/reference/shims/ini /Ireference/open-bfme-1/reference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Benchmark /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
#define Matrix4x4 Matrix4  // BFME renamed it
#define __PLACEMENT_VEC_NEW_INLINE  // always.h/GameMemory.h define array placement-new themselves
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

// FILE: W3DDebrisDraw.cpp ////////////////////////////////////////////////////////////////////////
// Author: Colin Day, November 2001
// Desc:   Default w3d draw module
///////////////////////////////////////////////////////////////////////////////////////////////////

// INCLUDES ///////////////////////////////////////////////////////////////////////////////////////

#include "Common/FileSystem.h"	// this is only here to pull in LOAD_TEST_ASSETS
#include "Common/GlobalData.h"
#include "Common/ThingTemplate.h"
#include "GameClient/Drawable.h"
#include "GameLogic/Object.h"
#include "GameClient/Shadow.h"
#include "GameClient/FXList.h"
#include "GameLogic/TerrainLogic.h"

#include "WW3D2/HAnim.h"
#include "WW3D2/HLod.h"
#include "WW3D2/RendObj.h"
#include "W3DDevice/GameClient/Module/W3DDebrisDraw.h"
#include "W3DDevice/GameClient/W3DAssetManager.h"
#include "W3DDevice/GameClient/W3DDisplay.h"
#include "W3DDevice/GameClient/W3DScene.h"
#include "W3DDevice/GameClient/W3DShadow.h"

HAnimClass *Get_HAnim(const char *name);

// BFME's render interfaces predate the Zero Hour headers used to build this
// source tree.  Keep the retail virtual slots and the extended shadow
// descriptor local to this translation unit.
class BfmeSceneView
{
public:
	__forceinline void addRenderObject(RenderObjClass *renderObject)
	{
		typedef void (BfmeSceneView::*Method)(RenderObjClass *);
		(this->*(*(Method *)&(*(void ***)this)[2]))(renderObject);
	}
};

class BfmeRenderObjectView
{
public:
	__forceinline void setTransform(const Matrix3D &transform)
	{
		typedef void (BfmeRenderObjectView::*Method)(const Matrix3D &);
		(this->*(*(Method *)&(*(void ***)this)[21]))(transform);
	}

	__forceinline void setUserData(void *value, Bool recursive)
	{
		typedef void (BfmeRenderObjectView::*Method)(void *, Bool);
		(this->*(*(Method *)&(*(void ***)this)[86]))(value, recursive);
	}
};

// Native descriptor at79514/793FA is40 bytes; historical AudioEventRTS
// owner is not asserted here. Constructor and destructor require reconciliation.
struct Rva00079514ShadowParams {
 Rva00079514ShadowParams(); ~Rva00079514ShadowParams();
 AsciiString name0,name4; int type8; float fC,f10,f14,f18,f1C,f20;
 unsigned char flag24,flag25,flag26;
};
class Rva0013101E {public:
 unsigned a:1,b:29,c:1,keep:1; unsigned d1,d2,d3;
 Rva0013101E(){a=0;b=0;c=0;d1=0;d2=0;d3=0;}
 void setColor(unsigned color){a=1;b=0;c=0;d2=0;d3=0;d1=color;}
};
RenderObjClass *Rva00137364CreateRenderObj(const char*,Real,const Rva0013101E&);
class Rva0009A8D3 {public:Shadow *rva0009A8D3(RenderObjClass*,Rva00079514ShadowParams*,Drawable*);};
class Gen0003AC38 {public:void handle(void*);};

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// ??0W3DDebrisDraw@@ is implemented by the exact retail thunk in
// W3DDebrisDrawCtorThunk.cpp.

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// ??1W3DDebrisDraw@@MAE@XZ present-unmatched
W3DDebrisDraw::~W3DDebrisDraw(void)
{
	if (TheW3DShadowManager && m_shadow)
	{	
		TheW3DShadowManager->removeShadow(m_shadow);
		m_shadow = NULL;
	}
	if (m_renderObject)
	{
		W3DDisplay::m_3DScene->Remove_Render_Object(m_renderObject);
  	REF_PTR_RELEASE(m_renderObject);
 		m_renderObject = NULL; 	
	}
	for (int i = 0; i < STATECOUNT; ++i)
	{
		REF_PTR_RELEASE(m_anims[i]);
		m_anims[i] = NULL;
	}
}

//-------------------------------------------------------------------------------------------------
// ?setShadowsEnabled@W3DDebrisDraw@@UAEX_N@Z present-unmatched
void W3DDebrisDraw::setShadowsEnabled(Bool enable)
{
	if (m_shadow)
		m_shadow->enableShadowRender(enable);
}

//-------------------------------------------------------------------------------------------------
// ?setFullyObscuredByShroud@W3DDebrisDraw@@UAEX_N@Z present-unmatched
void W3DDebrisDraw::setFullyObscuredByShroud(Bool fullyObscured)
{
	if (m_shadow)
		m_shadow->enableShadowInvisible(fullyObscured);
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// ?setModelName@W3DDebrisDraw@@UAEXVAsciiString@@HW4ShadowType@@@Z present-unmatched
void W3DDebrisDraw::setModelName(AsciiString name, Color color, ShadowType t)
{
  if (m_renderObject == NULL && !name.isEmpty())
	{
		Rva0013101E colorOptions;
		if(color != 0)colorOptions.setColor(color | 0xFF000000);
		m_renderObject=Rva00137364CreateRenderObj(name.str(),getDrawable()->getScale(),colorOptions);
		DEBUG_ASSERTCRASH(m_renderObject, ("Debris model %s not found!\n",name.str()));
		if (m_renderObject)
		{
			reinterpret_cast<BfmeSceneView *>(W3DDisplay::m_3DScene)->addRenderObject(m_renderObject);

			reinterpret_cast<BfmeRenderObjectView *>(m_renderObject)->setUserData(
				reinterpret_cast<unsigned char *>(getDrawable()) + 0x248, false);
			
			///@todo: Change back to identity once we figure out why objects show up at 0,0,0
			/// OBJECT_PILE
//			transform.Set(Vector3(0,0,9999));
			Matrix3D transform;
			transform.Set(Vector3(0,0,0));
			reinterpret_cast<BfmeRenderObjectView *>(m_renderObject)->setTransform(transform);
		}
		
		if (t != SHADOW_NONE)
		{
			Rva00079514ShadowParams shadowInfo;
			shadowInfo.type8=t;
			shadowInfo.fC=0;
			shadowInfo.f10=0;
			shadowInfo.f1C=0;
			m_shadow=reinterpret_cast<Rva0009A8D3*>(TheW3DShadowManager)->rva0009A8D3(m_renderObject,&shadowInfo,0);
		}
		else
		{
			if (TheW3DShadowManager && m_shadow)
			{	
				reinterpret_cast<Gen0003AC38*>(TheW3DShadowManager)->handle(m_shadow);
				m_shadow = NULL;
			}
		}

		// save the model name and color
		m_modelName = name;
		m_modelColor = color;

	}
}

//-------------------------------------------------------------------------------------------------
void W3DDebrisDraw::setAnimNames(AsciiString initial, AsciiString flying, AsciiString final, const FXList* finalFX)
{
	int i;
	for (i = 0; i < STATECOUNT; ++i)
	{
		if (m_anims[i] != NULL)
		{
			m_anims[i]->Release_Ref();
			m_anims[i] = NULL;
		}
		m_anims[i] = NULL;
	}

	m_anims[INITIAL] = initial.isEmpty() ? NULL : Get_HAnim(initial.str());
	m_anims[FLYING] = flying.isEmpty() ? NULL : Get_HAnim(flying.str());
	if (_strcmpi(final.str(), "STOP") == 0)
	{
		m_finalStop = true;
		final = flying;
	}
	else
	{
		m_finalStop = false;
	}
	m_anims[FINAL] = final.isEmpty() ? NULL : Get_HAnim(final.str());
	m_state = 0;
	m_frames = 0;
	m_fxFinal = finalFX;

	m_animInitial = initial;
	m_animFlying = flying;
	m_animFinal = final;

}

//-------------------------------------------------------------------------------------------------
static Bool isAnimationComplete(RenderObjClass* r)
{
	if (r->Class_ID() == RenderObjClass::CLASSID_HLOD)
	{
		HLodClass *hlod = (HLodClass*)r;
		return hlod->Is_Animation_Complete();
	}

	return true;
}

//-------------------------------------------------------------------------------------------------
static Bool isNearlyZero(const Coord3D* vel)
{
	const Real TINY = 0.01f;
	return fabs(vel->x) < TINY && fabs(vel->y) < TINY && fabs(vel->z) < TINY;
}

// ------------------------------------------------------------------------------------------------
// byte-exact reconstruction: Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DDebrisDrawReactToTransformChange.cpp
// W3DDebrisDraw::reactToTransformChange is defined with its retail-matched body in Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DDebrisDrawReactToTransformChange.cpp (0x000B1A14).

//-------------------------------------------------------------------------------------------------
// W3DDebrisDraw::doDrawModule is defined with its retail-matched body in Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DDebrisDrawModule.cpp (0x000B1A37).

// ------------------------------------------------------------------------------------------------
/** CRC */
// ------------------------------------------------------------------------------------------------
// ?crc@W3DDebrisDraw@@MAEXPAVXfer@@@Z present-unmatched
void W3DDebrisDraw::crc( Xfer *xfer )
{

	// extend base class
	DrawModule::crc( xfer );

}  // end crc

// The exact xfer body lives in W3DDebrisDrawXfer.cpp, which declares BFME's
// retail Xfer and by-value string layouts.

// ------------------------------------------------------------------------------------------------
/** Load post process */
// ------------------------------------------------------------------------------------------------
// ?loadPostProcess@W3DDebrisDraw@@MAEXXZ present-unmatched
void W3DDebrisDraw::loadPostProcess( void )
{

	// extend base class
	DrawModule::loadPostProcess();

}  // end loadPostProcess
