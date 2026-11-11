// cl: /DBFME_SNAPSHOT_NAME_SLOT /Ireference/shims/update_modules_bfme2 /Ireference/shims/moduledata /O1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/open-bfme-1/reference/shims/ini /Ireference/open-bfme-1/reference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Benchmark /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
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

#pragma inline_depth(0)
// ?bfmeDebrisDrawInterfaceAnchor absent-from-retail
DebrisDrawInterface *bfmeDebrisDrawInterfaceAnchor(W3DDebrisDraw *draw)
{
	return draw->W3DDebrisDraw::getDebrisDrawInterface();
}
#pragma inline_depth()

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
		(this->*(*(Method *)&(*(void ***)this)[85]))(value, recursive);
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
// W3DDebrisDraw::setModelName (0x000B1EEB) is recovered byte-exact in
// W3DDebrisDrawSetModelName.cpp; the BFME 1-shaped draft that stood here is gone.

//-------------------------------------------------------------------------------------------------
// W3DDebrisDraw::setAnimNames remains in the matched W3DDebrisDraw.cpp unit.

//-------------------------------------------------------------------------------------------------
static Bool isAnimationComplete(RenderObjClass* renderObj)
{
	if (renderObj->Class_ID() == RenderObjClass::CLASSID_HLOD)
	{
		HLodClass *hlod = (HLodClass*)renderObj;
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
// The Snapshot name getter is defined in SubsystemNameGetters.cpp.

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
