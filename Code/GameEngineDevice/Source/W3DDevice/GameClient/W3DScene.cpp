// cl: /D__PLACEMENT_VEC_NEW_INLINE /FIzh_ascii.h /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /Ireference/shims/bfme2ray /DBFME_WWSTRING_NATIVE_CSTR_ASSIGN /Ireference/shims/wwstring_teardown/zhmd /G7 /arch:SSE /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /DBFME_MODULE_NO_MPO /DZH_EMIT_POOL_GLUE /Ireference/shims/bfmerendobj /Ireference/shims/debugvtable /Ireference/shims/bfmestages /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/bfmeanimobj /Ireference/shims/indexbuffercount /Ireference/shims/bfmecaps /Ireference/shims/bfmehcanim /Ireference/shims/bfmevector /Ireference/shims/bfmemapper /Ireference/shims/meshmatdesclayout /Ireference/shims/bfmeshader /Ireference/shims/bfmecpudetect /Ireference/shims/bfmepool /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Ireference/shims/bfmealloc /Ireference/shims/bfmehashtable /Ireference/shims/bfmelist /Ireference/shims/stlp_nodealloc /ICode/GameEngine/Source/Common /Ireference/shims/w3droadbuffer /Ireference/shims/bfmeterraintracks /ICode/Libraries/Include/Lib
// Link view first: Vector3 Length/Normalize/ctor and the scalar operator* stay inline without emitting
// /O2 copies that compete with retail's owners (0x000692B3, 0x0006924F, 0x006CD510, 0x00066382, 0x0007DFB3).
// RefCountClass's inline members and deleting destructor are retail's
// size-optimised bodies: compile them for size, as hlod.cpp does.
// Include canonical RefCountData.h first so RefCountClass::Delete_This compiles
// retail's 20B ::delete this body (0x0006CE57) instead of Zero Hour's 12B copy;
// multilist.h's inline members also compile for size here.
#pragma optimize("s", on)
#include "../../../../Libraries/Source/WWVegas/WWLib/RefCountData.h"
#include "multilist.h"
#include "refcount.h"
#pragma optimize("", on)
#include "../../../../../reference/shims/bfme_vector3_full_link/vector3_full_link.h"
// stlport
// Ported verbatim from the Generals Zero Hour reference
// (GameEngineDevice/Source/W3DDevice/GameClient/W3DScene.cpp); this unit had no counterpart under Code/.
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

// BFME 2 has no W3D memory pools (see Code/Libraries/Source/WWVegas/WWLib/always.h).
#include "always.h"
#undef W3DMPO_GLUE
#define W3DMPO_GLUE(ARGCLASS)
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

// FILE: W3DScene.cpp /////////////////////////////////////////////////////////
//
// Scene manger for display using W3DDispaly.  A scene manager can customize
// the rendering process, culling, material passes ...
//
// Author: Colin Day, April 2001
//
///////////////////////////////////////////////////////////////////////////////

// SYSTEM INCLUDES ////////////////////////////////////////////////////////////
#include <stdlib.h>

// USER INCLUDES //////////////////////////////////////////////////////////////
#include "Lib/BaseType.h"
#include "Common/GlobalData.h"
#include "Common/PerfTimer.h"
#include "Common/Player.h"
#include "Common/PlayerList.h"
#include "GameLogic/Object.h"
#include "GameLogic/GameLogic.h"
#include "GameClient/Drawable.h"
#include "GameClient/ParticleSys.h"
#include "GameClient/Color.h"
#include "GameClient/View.h"
#include "W3DDevice/GameClient/HeightMap.h"
#include "coltest.h" // BFME2 RayCollisionTestClass (reference/shims/bfme2ray): out-of-line ctors as retail calls them
#include "W3DDevice/GameClient/W3DScene.h"
#include "W3DDevice/GameClient/W3DDynamicLight.h"
#include "W3DDevice/GameClient/W3DShadow.h"
#include "W3DDevice/GameClient/W3DStatusCircle.h"
#include "W3DDevice/GameClient/W3DCustomScene.h"
// W3DShroudMaterialPassClass's deleting dtor (0x0006F1DD, 28B) is /O1 size-optimised.
#pragma optimize("s", on)
#include "W3DDevice/GameClient/W3DShroud.h"
#pragma optimize("", on)
#include "WW3D2/camera.h"
#include "WW3D2/dx8renderer.h"
#include "WW3D2/sortingrenderer.h"
#include "WW3D2/dx8wrapper.h"
#include "WW3D2/Light.h"
#include "WW3D2/matpass.h"
#include "WW3D2/shader.h"
#include "WW3D2/DX8Caps.h"
// Retail keeps the size-optimized RGB/HSV definitions in ColorSpaceO1Inlines.
// Declare the shared calls here so this unit cannot supply a different copy.
#include "vector3.h"
void RGB_To_HSV(Vector3 &, const Vector3 &);
void HSV_To_RGB(Vector3 &, const Vector3 &);

#include "WW3D2/shdlib.h"
// bfme link decl-only begin
template <> bool RefMultiListClass<RenderObjClass>::Add(RenderObjClass *, bool);
template <> bool RefMultiListClass<RenderObjClass>::Release_Head();
// bfme link decl-only end
// Imported-forceinline: this unit inlines RefMultiListClass<RenderObjClass>::Remove
// and must not emit its 48-byte COMDAT copy, which was first in link order and
// differs from retail's 47-byte body (rowed 0x0006EF4E, RefMultiListRenderObjRemove.cpp).
template <> __declspec(dllimport) __forceinline
bool RefMultiListClass<RenderObjClass>::Remove(RenderObjClass *obj)
{
	bool result = Internal_Remove(obj);
	if (result) {
		obj->Release_Ref();
	}
	return result;
}
#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif

///////////////////////////////////////////////////////////////////////////////
// DEFINITIONS ////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///@todo: Remove these globals since we no longer need W3D to call them for us.
extern void DoTrees(RenderInfoClass & rinfo);
extern void DoShadows(RenderInfoClass & rinfo, Bool stencilPass);
extern void DoParticles(RenderInfoClass & rinfo);

// No texturing, no zbuffer reading/writing, primary gradient, no
// blending, no fogging - mostly for use in solid-colored opaque objects.
#define SC_PLAYER_COLOR ( SHADE_CNST(ShaderClass::PASS_ALWAYS, ShaderClass::DEPTH_WRITE_DISABLE, ShaderClass::COLOR_WRITE_ENABLE, \
	ShaderClass::SRCBLEND_ONE, ShaderClass::DSTBLEND_ZERO, ShaderClass::FOG_DISABLE, ShaderClass::GRADIENT_MODULATE, ShaderClass::SECONDARY_GRADIENT_DISABLE, \
	ShaderClass::TEXTURING_DISABLE, ShaderClass::ALPHATEST_DISABLE, ShaderClass::CULL_MODE_ENABLE, \
	ShaderClass::DETAILCOLOR_DISABLE, ShaderClass::DETAILALPHA_DISABLE) )
static ShaderClass PlayerColorShader(SC_PLAYER_COLOR);

//=============================================================================
// RTS3DScene::RTS3DScene
//=============================================================================
/** */
//=============================================================================
// The retail constructor is defined in RTS3DSceneCtor.cpp.

//=============================================================================
// RTS3DScene::~RTS3DScene
//=============================================================================
// Definition is in RTS3DSceneCtor.cpp, whose private class view matches the
// BFME2 layout rather than Zero Hour's mask and per-player material passes.


// ?RTS3DScene::setGlobalLight present-unmatched
void	RTS3DScene::setGlobalLight(LightClass *pLight, Int lightIndex)
{
	if (m_numGlobalLights < (lightIndex+1))
		m_numGlobalLights=(lightIndex+1);
	REF_PTR_SET(m_globalLight[lightIndex], pLight);
}

/**Find all objects which need to be drawn in a special way because they are occluded by other
objects.
@todo:  Need some kind of scene subdivision or find way to use Partition manger to speed up the ray
intersection tests.  Maybe truncate the ray to terrain length before using it?
*/
// ?RTS3DScene::flagOccludedObjects present-unmatched
void RTS3DScene::flagOccludedObjects(CameraClass * camera)
{
	Vector3 camPosition=camera->Get_Position();

	//Find which objects are actually occluded
	RenderObjClass **occludee=m_potentialOccludees;
	LineSegClass lineseg;
	CastResultStruct result;
	Bool hit=FALSE;
	Vector3 newEndPoint;
	result.ComputeContactPoint=false;
	RayCollisionTestClass raytest(lineseg,&result,COLL_TYPE_ALL,false,false);
	raytest.CollisionType=COLL_TYPE_ALL;

	m_occludedObjectsCount=0;

	for (Int i=0; i<m_numPotentialOccludees; i++,occludee++)
	{	
		raytest.Ray.Set(camPosition,(*occludee)->Get_Position());

		RenderObjClass **occluder=m_potentialOccluders;

		//Check this object against all other possible blocking objects
		for (Int j=0; j<m_numPotentialOccluders; j++,occluder++)
		{
			// Do a quick ray-sphere test (Graphics Gems I,  p388)
			RenderObjClass *robj=*occluder;

			const SphereClass *sphere = &robj->Get_Bounding_Sphere();

			// make a vector from the ray origin to the sphere center
			Vector3 sphere_vector(sphere->Center - raytest.Ray.Get_P0());
			
			// get the dot product between the sphere_vector and the ray vector
			Real Alpha = Vector3::Dot_Product(sphere_vector, raytest.Ray.Get_Dir());

			Real Beta = sphere->Radius * sphere->Radius - (Vector3::Dot_Product(sphere_vector, sphere_vector) - Alpha * Alpha);

			if(Beta < 0.0f)
				continue;	//no intersection
				
			//Do a more accurate test against object geometry
			if (robj->Cast_Ray(raytest))
			{
				//Found an object closer than last closest object
				//Adjust our results and refine search
				raytest.CollidedRenderObj = robj;
				hit=TRUE;
				//reset the result space for next test
				result.StartBad = false; result.Fraction = 1.0f;
				break;
			}
		}
		if (hit)
		{	//ocludee was blocked by something so flag it for custom rendering
			DrawableInfo *drawInfo=(DrawableInfo *)(*occludee)->Get_User_Data();
			drawInfo->m_flags |= DrawableInfo::ERF_IS_OCCLUDED;
			m_potentialOccludees[m_occludedObjectsCount++] = *occludee;
		}
	}
}

//=============================================================================
// RTS3DScene::castRay
//=============================================================================
/** Does a ray intersection test against objects in our scene.
	By default, it only tests objects determined to be visible to the user.
	Setting testAll forces it to test all objects in the scene.
	CollisionType is used as a mask to ignore certain types of objects.
 */
//=============================================================================
// ?RTS3DScene::castRay present-unmatched
Bool RTS3DScene::castRay(RayCollisionTestClass & raytest, Bool testAll, Int collisionType)
{
// this shouldn't be necessary here, and would be an undesirable performance hit.
// if you ever add or modify code here, it MIGHT become necessary... so do so with caution. (srj)
//#ifdef DIRTY_CONDITION_FLAGS
//	StDrawableDirtyStuffLocker lockDirtyStuff;
//#endif

	//temporary results for each object tested
	CastResultStruct result;
	RayCollisionTestClass tempRayTest(raytest.Ray,&result);
	Vector3 newEndPoint;
	Bool hit=FALSE;

	tempRayTest.CollisionType = COLL_TYPE_ALL;
	//check if a mesh is translucent before colliding with it. Skips headlights, etc.
	tempRayTest.CheckTranslucent = true;

	RefRenderObjListIterator it(&RenderList);

	// select the first object
	it.First();

	while (!it.Is_Done())
	{
		// get the render object
		RenderObjClass * robj = it.Peek_Obj();
		it.Next();

		// only intersect if it was visible or if we must test all
		if(robj->Get_Collision_Type() & collisionType && (testAll || robj->Is_Really_Visible()))
		{
			// Do a quick ray-sphere test (Graphics Gems I,  p388)
			const SphereClass *sphere = &robj->Get_Bounding_Sphere();

			// make a vector from the ray origin to the sphere center
			Vector3 sphere_vector(sphere->Center - tempRayTest.Ray.Get_P0());
		
			// get the dot product between the sphere_vector and the ray vector
			Real Alpha = Vector3::Dot_Product(sphere_vector, tempRayTest.Ray.Get_Dir());

			Real Beta = sphere->Radius * sphere->Radius - (Vector3::Dot_Product(sphere_vector, sphere_vector) - Alpha * Alpha);

			if(Beta < 0.0f)
				continue;	//no intersection
			
			//Do a more accurate test against object geometry
			if (robj->Cast_Ray(tempRayTest))
			{
				//Found an object closer than last closest object
				//Adjust our results and refine search
				raytest.CollidedRenderObj = robj;
				hit=TRUE;
				//Refine search by making ray shorter
				tempRayTest.Ray.Compute_Point(tempRayTest.Result->Fraction,&newEndPoint);
				tempRayTest.Ray.Set(raytest.Ray.Get_P0(),newEndPoint);
				//intersection point is at the end of shortened ray, so adjust fraction to 1.0
				tempRayTest.Result->Fraction=1.0f;
			}
		}
	}

	//Store results of ray intersection test including a clipped ray that ends on object.
	raytest.Ray=tempRayTest.Ray;
	return hit;
}

//============================================================================
// RTS3DScene::renderSingleDrawable
//=============================================================================
/** Renders a single drawable entity. */
//=============================================================================
// RTS3DScene::renderSpecificDrawables: no retail row yet; the Zero Hour copy called the
// Zero Hour three-argument renderOneObject, which BFME 2 does not have (its renderOneObject
// takes a fourth int).

//============================================================================
// RTS3DScene::renderOneObject
//=============================================================================
/** Renders a single drawable entity. */
//=============================================================================
// RTS3DScene::renderOneObject: retail's body is the row at 0x0006FB59
// (RTS3DSceneRenderOneObject.cpp); this unit only declares it. Its Zero Hour copy here
// was a second definition that pulled Zero Hour-only Object/Drawable members.

//DECLARE_PERF_TIMER(translucentRender)

/**Draw everything that was submitted from this scene*/

/**Generate a predefined light environment(s) that will be applied to many objects.  Useful for things like totally fogged
objects and most generaic map objects that are not lit by dynamic lights.*/
// RTS3DScene::updateFixedLightEnvironments (retail 0x0006E716) lives in
// W3DSceneUpdateFixedLightEnvironments.cpp: BFME 2 builds it at /O1, unlike
// this unit's /O2 rows, and it differs from the Zero Hour body.

/**Generate custom rendering passes for each potential player color.  This is currently only used
to render occluded objects using the color of the player*/
// ?RTS3DScene::updatePlayerColorPasses present-unmatched
void RTS3DScene::updatePlayerColorPasses(void)
{
#ifdef USE_NON_STENCIL_OCCLUSION
	Vector3 hsv,rgb;

	if (TheGlobalData->m_enableBehindBuildingMarkers && TheGameLogic->getShowBehindBuildingMarkers())
	{
		Int numPlayers=ThePlayerList->getPlayerCount();

		for (Int i=0; i<numPlayers; i++)
		{	Player *player=ThePlayerList->getNthPlayer(i);
			Int playerIndex=player->getPlayerIndex();
			Real red,green,blue,alpha;
			GameGetColorComponentsReal(player->getPlayerColor(),&red,&green,&blue,&alpha);
			RGB_To_HSV(hsv,Vector3(red,green,blue));
			hsv.Z*=TheGlobalData->m_occludedLuminanceScale;
			HSV_To_RGB(rgb,hsv);
			VertexMaterialClass *vmat=m_occludedMaterialPass[playerIndex]->Peek_Material();
			vmat->Set_Emissive(rgb);
		}
	}
#endif
}

#define ZBias 0.0001f

//DECLARE_PERF_TIMER(NonTerrainRender)

//=============================================================================
// RTS3DScene::Customized_Renderer
//=============================================================================
/** Custom render method for the RTS3DScene, custom render properties for our
  * particular game go here */
//=============================================================================
// RTS3DScene::Customized_Render: retail's body is the row at 0x0007054F
// (RTS3DSceneRva0007054F.cpp); this unit only declares it, so its vtable binds there.

/**Convert a player index to a color index, we use this because color indices are
assigned in left-right binary flipped fashion so as not to occupy lower bits unless
necessary.  This is used because lower bits are free for use by stencil shadow
rendering*/
#define NUMBER_PLAYER_COLOR_BITS 4	//need 4 bits to encode 8 players because indices start at 1 (not 0).
Int playerIndexToColorIndex(Int playerIndex)
{
	Int tmp=playerIndex;
	Int result=0;
	Int flippedPosition;

	//Player index is stored in 4 bits
	for (Int i=0; i<NUMBER_PLAYER_COLOR_BITS; i++)
	{
		flippedPosition = NUMBER_PLAYER_COLOR_BITS-1-i;	//correct position of bit after it's flipped left/right

		if (flippedPosition > i)
		{	//shifting left
			result |= (tmp & (1<<i))<<(flippedPosition-i);
		}
		else
		{	//shifting right
			result |= (tmp & (1<<i))>>(i-flippedPosition);
		}
	}
	return result;
}

/**Utility function used to render a full screen quad with the specified color and
stencil mask*/
void renderStenciledPlayerColor( UnsignedInt color, UnsignedInt stencilRef, Bool clear=FALSE)
{
	struct _TRANSLITVERTEX {
	    Vector4 p;
		DWORD color;   // diffuse color    
	} v[4];

	Int xpos, ypos, width, height;

	TheTacticalView->getOrigin(&xpos,&ypos);
	width=TheTacticalView->getWidth();
	height=TheTacticalView->getHeight();

    v[0].p.Set(xpos+width, ypos+height, 0.0f, 1.0f );
    v[1].p.Set(xpos+width, 0, 0.0f, 1.0f );
    v[2].p.Set(xpos, ypos+height, 0.0f, 1.0f );
    v[3].p.Set(xpos,  0, 0.0f, 1.0f );
    v[0].color = color;
    v[1].color = color;
    v[2].color = color;
    v[3].color = color;

	DX8Wrapper::Set_Shader(PlayerColorShader);
	VertexMaterialClass *vmat=VertexMaterialClass::Get_Preset(VertexMaterialClass::PRELIT_DIFFUSE);
	DX8Wrapper::Set_Material(vmat);
	REF_PTR_RELEASE(vmat);
	DX8Wrapper::Apply_Render_State_Changes();	//force update all renderstates

	LPDIRECT3DDEVICE8 m_pDev=DX8Wrapper::_Get_D3D_Device8();

	if (!m_pDev)
		return;	//need device to render anything.

	//draw polygons like this is very inefficient but for only 2 triangles, it's
	//not worth bothering with index/vertex buffers.
	m_pDev->SetVertexShader(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);

	// Set stencil states
	DX8Wrapper::Set_DX8_Render_State(D3DRS_STENCILENABLE, TRUE );
	DX8Wrapper::Set_DX8_Render_State(D3DRS_ZENABLE, TRUE );
	DWORD	oldColorWriteEnable=0x12345678;
	if (clear)
	{	//we want to clear the stencil buffer to some known value whereever a player index is stored
		Int occludedMask=TheW3DShadowManager->getStencilShadowMask();
		DX8Wrapper::Set_DX8_Render_State(D3DRS_STENCILREF,      0x80808080 );
		DX8Wrapper::Set_DX8_Render_State(D3DRS_STENCILMASK,     occludedMask );	//isolate bits containing occluder|playerIndex
		DX8Wrapper::Set_DX8_Render_State(D3DRS_STENCILWRITEMASK,0xffffffff );
		DX8Wrapper::Set_DX8_Render_State(D3DRS_STENCILFUNC,  D3DCMP_LESS );	//only draw to pixels that match the reference value
		DX8Wrapper::Set_DX8_Render_State(D3DRS_STENCILZFAIL, D3DSTENCILOP_REPLACE );	
		DX8Wrapper::Set_DX8_Render_State(D3DRS_STENCILPASS,  D3DSTENCILOP_REPLACE );	//pixels which had occluded player colors, get MSB set.
		DX8Wrapper::Set_DX8_Render_State(D3DRS_STENCILFAIL,  D3DSTENCILOP_ZERO );	//pixels which had no occluded player colors are cleared.
		DX8Wrapper::Set_DX8_Render_State(D3DRS_ZFUNC, D3DCMP_NEVER  );	//fail all access to the frame buffer to improve memory bandwidth

		//disable writes to color buffer
		if (DX8Wrapper::Get_Current_Caps()->Get_DX8_Caps().PrimitiveMiscCaps & D3DPMISCCAPS_COLORWRITEENABLE)
		{	DX8Wrapper::_Get_D3D_Device8()->GetRenderState(D3DRS_COLORWRITEENABLE, &oldColorWriteEnable);
			DX8Wrapper::Set_DX8_Render_State(D3DRS_COLORWRITEENABLE,0);
		}
		else
		{	//device does not support disabling writes to color buffer so fake it through alpha blending
			DX8Wrapper::Set_DX8_Render_State(D3DRS_ALPHABLENDENABLE, TRUE);
			DX8Wrapper::Set_DX8_Render_State(D3DRS_SRCBLEND, D3DBLEND_ZERO );
			DX8Wrapper::Set_DX8_Render_State(D3DRS_DESTBLEND, D3DBLEND_ONE );
		}
	}
	else
	{	DX8Wrapper::Set_DX8_Render_State(D3DRS_STENCILREF,      stencilRef );
		DX8Wrapper::Set_DX8_Render_State(D3DRS_STENCILMASK,     0xffffffff );
		DX8Wrapper::Set_DX8_Render_State(D3DRS_STENCILWRITEMASK,0xffffffff );	
		DX8Wrapper::Set_DX8_Render_State(D3DRS_STENCILFUNC,  D3DCMP_EQUAL );
		DX8Wrapper::Set_DX8_Render_State(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP );
		DX8Wrapper::Set_DX8_Render_State(D3DRS_STENCILPASS,  D3DSTENCILOP_KEEP );
		DX8Wrapper::Set_DX8_Render_State(D3DRS_STENCILFAIL,  D3DSTENCILOP_KEEP );

		//Make occluded pixels transparent
		DX8Wrapper::Set_DX8_Render_State(D3DRS_ALPHABLENDENABLE, TRUE);
		DX8Wrapper::Set_DX8_Render_State(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
		DX8Wrapper::Set_DX8_Render_State(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );
	}

	if (DX8Wrapper::_Is_Triangle_Draw_Enabled())
		m_pDev->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v, sizeof(_TRANSLITVERTEX));

	// turn off the stencil buffer
	DX8Wrapper::Set_DX8_Render_State(D3DRS_STENCILENABLE, FALSE );
	DX8Wrapper::Set_DX8_Render_State(D3DRS_ALPHABLENDENABLE, FALSE);	//restore shader state
	DX8Wrapper::Set_DX8_Render_State(D3DRS_SRCBLEND, D3DBLEND_ONE );
	DX8Wrapper::Set_DX8_Render_State(D3DRS_DESTBLEND, D3DBLEND_ZERO );
	DX8Wrapper::Set_DX8_Render_State(D3DRS_ZFUNC, D3DCMP_ALWAYS);

	if (oldColorWriteEnable != 0x12345678)
		DX8Wrapper::Set_DX8_Render_State(D3DRS_COLORWRITEENABLE,oldColorWriteEnable);

}  // end renderStencilShadows

#define MAX_VISIBLE_OCCLUDED_PLAYER_OBJECTS	512 //maximum number of occluded objects permitted per player

/*Version which does not require stencil buffer*/
// RTS3DScene::flushOccludedObjects / flushTranslucentObjects: BFME 2's passes are the
// rows in RTS3DSceneFlushTranslucent.cpp and flushOccludedObjectsIntoStencil; the Zero Hour
// copies here called the three-argument renderOneObject BFME 2 does not have.


//=============================================================================
// RTS3DScene::createLightsIterator
//=============================================================================
/** Returns an iterator of the lights in the scene. */
//=============================================================================
// RTS3DScene::createLightsIterator: defined in RTS3DScene_createLightsIterator.cpp (its row's unit).


//=============================================================================
// RTS3DScene::destroyLightsIterator
//=============================================================================
/** Destroys the iterator returned by createLightsIterator. */
//=============================================================================
// ?RTS3DScene::destroyLightsIterator present-unmatched
void RTS3DScene::destroyLightsIterator(RefRenderObjListIterator * it)
{
	delete it;
}


//=============================================================================
// RTS3DScene::addDynamicLight
//=============================================================================
/** Adds a dynamic light. */
//=============================================================================
// ?RTS3DScene::addDynamicLight present-unmatched
void RTS3DScene::addDynamicLight(W3DDynamicLight * obj)
{
	m_dynamicLightList.Add(obj);
	UpdateList.Add(obj);
}

//=============================================================================
// RTS3DScene::addDynamicLight
//=============================================================================
/** Adds a dynamic light. */
//=============================================================================
// RTS3DScene::getADynamicLight: retail's body is the row at 0x0006F94A
// (RTS3DSceneGetADynamicLight.cpp); this unit only declares it.
// Its Zero Hour body was the only caller of the rowed W3DDynamicLight::setEnabled, so keep it emitted.
// ?bfmeAnchorW3DDynamicLightSetEnabled@@YAXPAVW3DDynamicLight@@@Z absent-from-retail
void bfmeAnchorW3DDynamicLightSetEnabled(W3DDynamicLight *light) { light->setEnabled(true); }

//=============================================================================
// RTS3DScene::removeDynamicLight
//=============================================================================
/** Removes a dynamic light. */
//=============================================================================
// ?RTS3DScene::removeDynamicLight present-unmatched
void RTS3DScene::removeDynamicLight(W3DDynamicLight * obj)
{
	m_dynamicLightList.Remove(obj);
}

//=============================================================================
// RTS3DScene::doRender
//=============================================================================
/** Render the scene */
//=============================================================================
// RTS3DScene::doRender is rowed at 0x0006ED36 (Rva0006ED36Call.cpp); the Zero Hour copy
// here was a second definition.

//=============================================================================
// RTS3DScene::draw
//=============================================================================
/** Customized render for the 2d scene management */
//=============================================================================
// RTS3DScene::draw: Zero Hour's body called the Zero Hour WW3D::Render(scene, camera)
// overload, which BFME 2 does not have; no retail row yet (see the ZH reference).


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//=============================================================================
// RTS2DScene::RTS2DScene
//=============================================================================
/** */
//=============================================================================
// ??0RTS2DScene@@QAE@XZ is rowed in its own unit; this copy collided with it.  // end RTS2DScene

//=============================================================================
// RTS2DScene::~RTS2DScene
//=============================================================================
/** */
//=============================================================================
// RTS2DScene::~RTS2DScene: no retail row yet; the Zero Hour copy emitted a Zero Hour
// RTS2DScene vtable (SimpleSceneClass::Create_Iterator(bool)) that BFME 2 does not have.

//=============================================================================
// RTS2DScene::Custimized_Render
//=============================================================================
/** Customized render for the 2d scene management */
//=============================================================================

//=============================================================================
// RTS2DScene::doRender
//=============================================================================
/** Render the scene */
//=============================================================================
// RTS2DScene::doRender is rowed at 0x0006EE27 (Rva0006ED36Call.cpp); the Zero Hour copy
// here was a second definition.

//=============================================================================
// RTS2DScene::draw
//=============================================================================
/** Customized render for the 2d scene management */
//=============================================================================
// RTS2DScene::draw: see RTS3DScene::draw above.



///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//=============================================================================
// RTS3DInterfaceScene::RTS3DInterfaceScene
//=============================================================================
/** */
//=============================================================================
// RTS3DInterfaceScene ctor/dtor/Customized_Render: no retail rows yet; the Zero Hour
// copies emitted its Zero Hour vtable, as RTS2DScene's did.



/// The following is an :archive" of a partial attempt at detecting the mapshroud hack
/*
 *
	


 *
 */


#pragma inline_depth(0)
// ?bfmeAnchorW3DShroudMaterialPassClass absent-from-retail
void bfmeAnchorW3DShroudMaterialPassClass(W3DShroudMaterialPassClass *pass)
{
    new (pass) W3DShroudMaterialPassClass;
    pass->W3DShroudMaterialPassClass::~W3DShroudMaterialPassClass();
}
#pragma inline_depth()
