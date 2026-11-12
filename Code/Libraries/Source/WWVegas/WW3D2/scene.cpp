// cl: /Ireference/shims/bfme2ray /DBFME_WWSTRING_NATIVE_CSTR_ASSIGN /Ireference/shims/wwstring_teardown/zhmd /arch:SSE /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
// The old +0x9C getter placement depended on a refuted base-destructor layout.
// Precise BFME2 lifetime/copy proofs retain 32 opaque bytes there; no hook identity is claimed.
// stlport
// The compiler-generated vector constructor iterator (??_H) takes the
// optimization state of the first function that needs it. Retail links one
// copy, the /O1 body at 0x00001423; this unemitted anchor makes this unit's
// copy that same body, so it no longer loses to retail's at link time.
// It can also change how later array constructions here compile; checked to
// change nothing else in this unit, but if a function added later that builds
// an array will not match, try it without this block.
#include "../../../../GameEngine/Include/Common/BfmeVciAnchorElem.h"
#pragma optimize("gsy", on)
static void bfmeVciAnchor() { BfmeVciAnchorElem anchor[2]; (void)anchor; }
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

/***********************************************************************************************
 ***              C O N F I D E N T I A L  ---  W E S T W O O D  S T U D I O S               ***
 ***********************************************************************************************
 *                                                                                             *
 *                 Project Name : WW3D                                                         *
 *                                                                                             *
 *                     $Archive:: /VSS_Sync/ww3d2/scene.cpp                                   $*
 *                                                                                             *
 *                   Org Author:: Greg_h                                                       *
 *                                                                                             *
 *                       Author : Kenny Mitchell                                               * 
 *                                                                                             * 
 *                     $Modtime:: 07/01/02 12:55p                                              $*
 *                                                                                             *
 *                    $Revision:: 24                                                          $*
 *                                                                                             *
 * 06/27/02 KM Shader system light environment updates                                       *
 * 07/01/02 KM Coltype enum change to avoid MAX conflicts									   *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 *   SceneClass::SceneClass -- constructor                                                     *
 *   SceneClass::~SceneClass -- destructor                                                     *
 *   SceneClass::Render -- preps the scene for rendering, derived classes should override      *
 *   SceneClass::Add_Render_Object -- base add function                                        *
 *   SceneClass::Remove_Render_Object -- base remove function                                  *
 *   SceneClass::Set_Depth_Cue -- set the depth cue values                                     *
 *   SceneClass::Set_Fog_Range -- set the fog range                                            *
 *   SceneClass::Get_Fog_Range -- get the fog range                                            *
 *   SceneClass::Render -- preps the scene for rendering, derived classes should add functional*
 *   SimpleSceneClass -- Constructor                                                           *
 *   SimpleSceneClass::~SimpleSceneClass -- destructor                                         *
 *   SimpleSceneClass::Add_Render_Object -- add a render object to the scene                   *
 *   SimpleSceneClass::Remove_Render_Object -- remove a render object from this scene          *
 *   SimpleSceneClass::Visiblity_Check -- set the visiblity status of the render objects       *
 *   SimpleSceneClass::Render -- internal scene rendering function                             *
 *   SimpleSceneClass::Render -- Render this scene                                             *
 *   SimpleSceneClass::Create_Iterator -- create an iterator for this scene                    *
 *   SimpleSceneClass::Destroy_Iterator -- destroy an iterater of this scene                   *
 *   SceneClass::Save -- saves scene settings into a chunk                                     *
 *   SceneClass::Load -- loads scene settings from a chunk                                     *
 *   SimpleSceneClass::Compute_Point_Visibility -- returns visibility of a point               *
 *   SimpleSceneClass::Remove_All_Render_Objects -- Removes all render objects from the scene  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */


// RefCountClass's inline members and deleting destructor are retail's
// size-optimised bodies: compile them for size, as hlod.cpp does.
// multilist.h's inline members are retail's size-optimised bodies: compile
// them for size (as hlod.cpp/decalsys.cpp do) so this unit's copies match.
#include "multilist.h"
#include "refcount.h"
#pragma optimize("", on)
#include "scene.h"
#include "plane.h"
#include "camera.h"
#include "ww3d.h"
#include "rinfo.h"
#include "chunkio.h"
#include "dx8renderer.h"
#include "dx8wrapper.h"
#include "sortingrenderer.h"
#include "coltest.h"


/*
** Chunk ID's used by SceneClass
*/
enum 
{
	SCENECLASS_CHUNK_VARIABLES			= 0x00042300,

	SCENECLASS_VARIABLE_AMBIENTLIGHT	= 0x00,
	SCENECLASS_VARIABLE_POLYRENDERMODE,
	SCENECLASS_VARIABLE_FOGCOLOR,
	SCENECLASS_VARIABLE_FOGENABLED,
	SCENECLASS_VARIABLE_FOGSTART,
	SCENECLASS_VARIABLE_FOGEND,
};

/*
** SimpleSceneIterator
** This iterator is used by the SimpleSceneClass to allow
** the user to iterate through its render objects. 
*/
class SimpleSceneIterator : public SceneIterator
{
public:
	virtual void					First(void);
	virtual void					Next(void);
	virtual bool					Is_Done(void);
	virtual RenderObjClass *	Current_Item(void);

protected:

	SimpleSceneIterator(RefRenderObjListClass * renderlist,bool onlyvis);

	RefRenderObjListIterator	RobjIterator;	
	SimpleSceneClass *			Scene;	
	bool								OnlyVis;

	friend class SimpleSceneClass;
};


/***********************************************************************************************
 * SceneClass::SceneClass -- constructor                                                       *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   12/10/98   GTH : Created.                                                                 *
 *=============================================================================================*/
// SceneClass::SceneClass (0x00140C60) is rowed in SimpleSceneClassConstructorBFME2.cpp,
// whose SimpleSceneClass ctor emits the same body; a strong copy here duplicated it.
// The ctor also emitted (through the vtable) five scene.h inline virtuals rowed here;
// direct calls keep them emitted.
// ?bfmeAnchorSceneClassInlineRows absent-from-retail
void bfmeAnchorSceneClassInlineRows(SceneClass *scene, RenderInfoClass &rinfo, const Vector3 &v, bool on)
{
	scene->SceneClass::Set_Fog_Color(v);
	scene->SceneClass::Set_Ambient_Light(v);
	scene->SceneClass::Set_Fog_Range(0.0f, 1.0f);
	scene->SceneClass::Set_Fog_Enable(on);
	scene->SceneClass::Compute_Point_Visibility(rinfo, v);
}


/***********************************************************************************************
 * SceneClass::~SceneClass -- destructor                                                       *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   12/10/98   GTH : Created.                                                                 *
 *=============================================================================================*/
// ??1SceneClass@@UAE@XZ present-unmatched
// inline (a COMDAT copy) like the SceneClass views that the SimpleSceneClass units emit.
inline SceneClass::~SceneClass(void)
{
}

/***********************************************************************************************
 * SceneClass::Add_Render_Object -- base add function                                          *
 *                                                                                             *
 * This function only sets the render object's scene pointer and calls the notify method.      *
 * Derived classes must add the functionality of actually storing a pointer to the object      *
 * and doing something with it :)                                                              *
 *                                                                                             *
 * INPUT:                                                                                      *
 * obj - pointer to the object to add                                                          *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   2/25/99    GTH : Created.                                                                 *
 *=============================================================================================*/
// SceneClass::Add_Render_Object is defined with its retail-matched body in Code/Libraries/Source/WWVegas/WW3D2/SceneOwnership.cpp (0x00140CD0).


/***********************************************************************************************
 * SceneClass::Remove_Render_Object -- base remove function                                    *
 *                                                                                             *
 * Similar to the add function; concrete derived classes must override and actually remove     *
 * the object...                                                                               *
 *                                                                                             *
 * INPUT:                                                                                      *
 * obj - pointer to the object to remove                                                       * 
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   2/25/99    GTH : Created.                                                                 *
 *=============================================================================================*/
// SceneClass::Remove_Render_Object is defined with its retail-matched body in Code/Libraries/Source/WWVegas/WW3D2/SceneOwnership.cpp (0x00140CE0).


/***********************************************************************************************
 * SceneClass::Render -- preps the scene for rendering, derived classes should add functionalit*
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   12/10/98   GTH : Created.                                                                 *
 *=============================================================================================*/
// SceneClass::Render: BFME 2's body is the row 0x00141170 in SceneClass_Render.cpp;
// Zero Hour's copy here duplicated it.

/***********************************************************************************************
 * SceneClass::Save -- saves scene settings into a chunk                                       *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *=============================================================================================*/
void SceneClass::Save(ChunkSaveClass & csave)
{
	csave.Begin_Chunk(SCENECLASS_CHUNK_VARIABLES);
	WRITE_MICRO_CHUNK(csave,SCENECLASS_VARIABLE_AMBIENTLIGHT,AmbientLight);
	WRITE_MICRO_CHUNK(csave,SCENECLASS_VARIABLE_POLYRENDERMODE,PolyRenderMode);
	WRITE_MICRO_CHUNK(csave,SCENECLASS_VARIABLE_FOGCOLOR,FogColor);
	WRITE_MICRO_CHUNK(csave,SCENECLASS_VARIABLE_FOGENABLED,FogEnabled);
	WRITE_MICRO_CHUNK(csave,SCENECLASS_VARIABLE_FOGSTART,FogStart);
	WRITE_MICRO_CHUNK(csave,SCENECLASS_VARIABLE_FOGEND,FogEnd);
	csave.End_Chunk();
}


/***********************************************************************************************
 * SceneClass::Load -- loads scene settings from a chunk                                       *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *=============================================================================================*/
void SceneClass::Load(ChunkLoadClass & cload)
{
	cload.Open_Chunk();
	if (cload.Cur_Chunk_ID() == SCENECLASS_CHUNK_VARIABLES) {
		
		while (cload.Open_Micro_Chunk()) {
			switch(cload.Cur_Micro_Chunk_ID()) {
				READ_MICRO_CHUNK(cload,SCENECLASS_VARIABLE_AMBIENTLIGHT,AmbientLight);
				READ_MICRO_CHUNK(cload,SCENECLASS_VARIABLE_POLYRENDERMODE,PolyRenderMode);
				READ_MICRO_CHUNK(cload,SCENECLASS_VARIABLE_FOGCOLOR,FogColor);
				READ_MICRO_CHUNK(cload,SCENECLASS_VARIABLE_FOGENABLED,FogEnabled);
				READ_MICRO_CHUNK(cload,SCENECLASS_VARIABLE_FOGSTART,FogStart);
				READ_MICRO_CHUNK(cload,SCENECLASS_VARIABLE_FOGEND,FogEnd);
			}
			cload.Close_Micro_Chunk();
		}

	} else {
		WWDEBUG_SAY(("Unhandled Chunk: 0x%X in file: %s line: %d\r\n",cload.Cur_Chunk_ID(),__FILE__,__LINE__));
	}
	cload.Close_Chunk();
}


/***********************************************************************************************
 * SimpleSceneClass -- Constructor                                                             *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   3/24/98    GTH : Created.                                                                 *
 *   9/10/99    GTH : Created.                                                                 *
 *=============================================================================================*/
// SimpleSceneClass::SimpleSceneClass is defined byte-exact in
// SimpleSceneClassConstructorBFME2.cpp (0x00142960).

/***********************************************************************************************
 * SimpleSceneClass::~SimpleSceneClass -- destructor                                           *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   3/24/98    GTH : Created.                                                                 *
 *=============================================================================================*/
// Native SimpleSceneClass destructor is owned by SimpleSceneClass_dtor.cpp.
// The unrowed donor copy here did not reproduce the native member teardown.


/***********************************************************************************************
 * SimpleSceneClass::Remove_All_Render_Objects -- Removes all render objects from the scene    *
 *                                                                                             *
 *                                                                                             *
 *                                                                                             *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   8/27/2001  hy : Created.                                                                  *
 *=============================================================================================*/
// The retail loop is defined in SceneOwnership.cpp (0x00141370).
// It peeks the owning list and removes through SimpleScene's virtual path.

/***********************************************************************************************
 * SimpleSceneClass::Add_Render_Object -- add a render object to the scene                     *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   3/24/98    GTH : Created.                                                                 *
 *=============================================================================================*/
// byte-exact reconstruction: Code/GameEngine/Source/Common/SimpleSceneClass_Add_Render_Object_Thunk.cpp
// SimpleSceneClass::Add_Render_Object is defined with its retail-matched body in Code/Libraries/Source/WWVegas/WW3D2/SceneOwnership.cpp (0x001413A0).


/***********************************************************************************************
 * SimpleSceneClass::Remove_Render_Object -- remove a render object from this scene            *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   3/24/98    GTH : Created.                                                                 *
 *=============================================================================================*/
// byte-exact reconstruction: Code/GameEngine/Source/Common/SimpleSceneClass_Remove_Render_Object_Thunk.cpp
// SimpleSceneClass::Remove_Render_Object is defined with its retail-matched body in Code/Libraries/Source/WWVegas/WW3D2/SceneOwnership.cpp (0x00141860).

// byte-exact reconstruction: Code/GameEngine/Source/Common/SimpleSceneClass_Register_Thunk.cpp
// SimpleSceneClass::Register is defined with its retail-matched body in Code/Libraries/Source/WWVegas/WW3D2/SceneOwnership.cpp (0x00141400).

// byte-exact reconstruction: Code/GameEngine/Source/Common/SimpleSceneClass_Unregister_Thunk.cpp
// SimpleSceneClass::Unregister is defined with its retail-matched body in Code/Libraries/Source/WWVegas/WW3D2/SceneOwnership.cpp (0x001414D0).



/***********************************************************************************************
 * SimpleSceneClass::Visiblity_Check -- set the visiblity status of the render objects         *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   3/24/98    GTH : Created.                                                                 *
 *   4/13/98    NH : Added non-trivial checking (sphere vs. frustum).                          *
 *=============================================================================================*/


/***********************************************************************************************
 * SimpleSceneClass::Compute_Point_Visibility -- returns visibility of a point                 *
 *                                                                                             *
 *    This function is used by the default dazzle behavior.  SimpleSceneClass's implementation *
 *    casts a ray against every object in the scene to see if the dazzle is occluded.          *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   6/13/2001  gth : Created.                                                                 *
 *=============================================================================================*/
// SimpleSceneClass::Compute_Point_Visibility: BFME 2's body is the row 0x001418F0 in SceneOwnership.cpp;
// Zero Hour's copy here duplicated it.


/***********************************************************************************************
 * SimpleSceneClass::Render -- Render this scene                                               *
 *                                                                                             *
 * passes the gerd and camera to all render objects for rendering...                           *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   12/10/98  GTH : Created.                                                                 *
 *   06/27/02	KM Shader system light environment updates                                       *
 *=============================================================================================*/
// SimpleSceneClass::Customized_Render is rowed in SimpleSceneClassConstructorBFME2.cpp;
// the Zero Hour copy here duplicated it. It was also what emitted the rowed
// RenderObjClass::Get_Render_Hook inline here; this pointer is a compile anchor for
// that row, not a retail data claim.
extern RenderHookClass *(RenderObjClass::*const _bfmeInlineAnchorGetRenderHook)() =
	&RenderObjClass::Get_Render_Hook;

// SimpleSceneClass::Post_Render_Processing is defined with its retail-matched body in Code/Libraries/Source/WWVegas/WW3D2/SimpleSceneClass_Post_Render_Processing.cpp (0x00141BB0).

/***********************************************************************************************
 * SimpleSceneClass::Create_Iterator -- create an iterator for this scene                      *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   3/27/98    GTH : Created.                                                                 *
 *=============================================================================================*/


/***********************************************************************************************
 * SimpleSceneClass::Destroy_Iterator -- destroy an iterater of this scene                     *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   3/27/98    GTH : Created.                                                                 *
 *=============================================================================================*/
// ?Destroy_Iterator@SimpleSceneClass@@ present-unmatched
void SimpleSceneClass::Destroy_Iterator(SceneIterator * it)
{
	delete it;
}


// ??0SimpleSceneIterator@@IAE@PAV?$RefMultiListClass@VRenderObjClass@@@@_N@Z present-unmatched
SimpleSceneIterator::SimpleSceneIterator(RefRenderObjListClass * list,bool onlyvis) : 
	RobjIterator(list)
{
	// TODO: make SimpleSceneIterator able to iterate through only the visible nodes.
	OnlyVis = onlyvis;
}

void SimpleSceneIterator::First(void)
{
	RobjIterator.First();
}

void SimpleSceneIterator::Next(void)
{
	RobjIterator.Next();
}

// SimpleSceneIterator::Is_Done: BFME 2's body is the row 0x00140E90 in scene_Is_Done_SimpleSceneIterator_UAE_NXZ.cpp;
// Zero Hour's copy here duplicated it.

RenderObjClass * SimpleSceneIterator::Current_Item(void)
{
	return RobjIterator.Peek_Obj();
}
