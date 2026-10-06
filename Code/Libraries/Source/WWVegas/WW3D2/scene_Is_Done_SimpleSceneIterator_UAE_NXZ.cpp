// cl: -DNDEBUG -DWIN32 -D_WINDOWS -MD -EHsc -Ireference/open-bfme-1/inputs/reference/shims/sweep -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2
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
	// Retail destructor is provided by SimpleSceneIteratorDeletingDestructor.cpp.
	virtual ~SimpleSceneIterator();
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

// ?Is_Done@SimpleSceneIterator@@UAE_NXZ
// retail 0x00140E90, 17 bytes. Dedicated TU carrying the Open-BFME-1 donor
// preamble (game/Libraries/Source/WWVegas/WW3D2/scene.cpp,
// reference/open-bfme-1) and only this body; the donor's other definitions
// are omitted. Compiled /Os the donor emits it byte-identical to retail
// (unique masked placement on unclaimed .text).

bool SimpleSceneIterator::Is_Done(void)
{
	return RobjIterator.Is_Done();
}
