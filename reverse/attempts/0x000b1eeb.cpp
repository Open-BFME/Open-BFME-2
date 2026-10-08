// ?setModelName@W3DDebrisDraw@@UAEXVAsciiString@@HW4ShadowType@@@Z
// partial score=0.99 date=2026-10-08
// cl: /O1 /G7 /arch:SSE /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/open-bfme-1/reference/shims/ini /Ireference/open-bfme-1/reference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Benchmark /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
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

struct BfmeShadowTypeInfo
{
	char m_shadowNames[128];
	ShadowType m_type;
	Bool m_allowUpdates;
	Bool m_allowWorldAlign;
	unsigned char m_padding86[2];
	Real m_sizeX;
	Real m_sizeY;
	Real m_offsetX;
	Real m_offsetY;
	Real m_unmodelled98;
	Real m_unmodelled9c;
	Bool m_unmodelleda0;
};

// Retail exposes the scaled/recoloured BFME factory as a cdecl wrapper.  Its
// 0x00901F80 body is also reached by ModelConditionInfo's named validation
// caller and implements this exact three-argument ABI.
RenderObjClass *Create_Render_Obj(const char *name, Real scale, Int color);

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

// Native descriptor identity remains under review; no alias to AudioEventRTS.
class Rva00079514 {
public:
 Rva00079514(); ~Rva00079514();
 AsciiString first,second; int type; float sx,sy,ox,oy,extra,default20; char flags[3];
};
class Rva0013101E {
public:
 Rva0013101E():a(0),b(0),c(0),d1(0),d2(0),d3(0) {}
 void setColor(unsigned color) { a=1;b=0;c=0;d1=color;d2=0;d3=0; }
 unsigned a:3,b:27,c:1,keep:1; unsigned d1,d2,d3;
};
RenderObjClass *Rva00137364CreateRenderObj(const char*,float,const Rva0013101E &);
class Rva0009A8D3 { public: Shadow *rva0009A8D3(RenderObjClass *, Rva00079514 *, Drawable *); };
class Gen0003AC38 { public: void handle(void *); };
void W3DDebrisDraw::setModelName(AsciiString name,Color color,ShadowType t) {
 if(m_renderObject==0 && !name.isEmpty()) {
  Rva0013101E options;
  if(color) options.setColor(color|0xff000000);
  m_renderObject=Rva00137364CreateRenderObj(name.str(),getDrawable()->getScale(),options);
  if(m_renderObject) {
   reinterpret_cast<BfmeSceneView *>(W3DDisplay::m_3DScene)->addRenderObject(m_renderObject);
   reinterpret_cast<BfmeRenderObjectView *>(m_renderObject)->setUserData(reinterpret_cast<unsigned char *>(getDrawable())+0x248,false);
   Matrix3D transform; transform.Set(Vector3(0,0,0));
   reinterpret_cast<BfmeRenderObjectView *>(m_renderObject)->setTransform(transform);
  }
  if(t!=SHADOW_NONE) {
   Rva00079514 info; info.type=t; info.sx=0;info.sy=0;info.extra=0;
   m_shadow=((Rva0009A8D3 *)TheW3DShadowManager)->rva0009A8D3(m_renderObject,&info,0);
  } else if(TheW3DShadowManager && m_shadow) {
   ((Gen0003AC38 *)TheW3DShadowManager)->handle(m_shadow);m_shadow=0;
  }
  m_modelName=name;m_modelColor=color;
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

