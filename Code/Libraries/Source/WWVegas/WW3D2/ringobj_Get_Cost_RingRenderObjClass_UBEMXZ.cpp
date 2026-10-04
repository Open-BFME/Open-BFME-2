// cl: -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 -DNDEBUG -DWIN32 -D_WINDOWS -MD -EHsc -Ireference/open-bfme-1/inputs/reference/shims/sweep -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Os
// stlport
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

/***********************************************************************************************
 ***              C O N F I D E N T I A L  ---  W E S T W O O D  S T U D I O S               ***
 ***********************************************************************************************
 *                                                                                             *
 *                 Project Name : WW3D                                                         *
 *                                                                                             *
 *                     $Archive:: /Commando/Code/ww3d2/ringobj.cpp                            $*
 *                                                                                             *
 *                       Author:: Greg Hjelstrom                                               *
 *                                                                                             *
 *                     $Modtime:: 11/24/01 6:17p                                              $*
 *                                                                                             *
 *                    $Revision:: 27                                                          $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 *   RingRenderObjClass::RingRenderObjClass -- Constructor                                     *
 *   RingRenderObjClass::RingRenderObjClass -- Constructor - init from a definition            *
 *   RingRenderObjClass::RingRenderObjClass -- Copy constructor                                *
 *   RingRenderObjClass::~RingRenderObjClass -- destructor                                     *
 *   RingRenderObjClass::operator -- assignment operator												     *
 *   RingRenderObjClass::Get_Num_Polys -- returns number of polygons									  *
 *   RingRenderObjClass::Get_Name -- returns name															  *
 *   RingRenderObjClass::Set_Name -- sets the name                                             *
 *   RingRenderObjClass::Set_Color -- Sets the color of the Ring                               *
 *   RingRenderObjClass::Init_Ring_Render_System -- global initialization needed for Ring		  *
 *   RingRenderObjClass::Shutdown_Ring_Render_System -- cleanup Ring render system				  *
 *   RingRenderObjClass::Set_Ring_Display_Mask -- Sets global display mask for all Ringes		  *
 *   RingRenderObjClass::Get_Ring_Display_Mask -- returns the display mask							  *
 *   RingRenderObjClass::update_mesh_data -- Updates vertex positions, etc                     *
 *   RingRenderObjClass::render_Ring -- submits the Ring to the GERD									  *
 *   RingRenderObjClass::vis_render_Ring -- submits Ring to the GERD for VIS						  *
 *   RingRenderObjClass::RingRenderObjClass -- constructor												  *
 *   RingRenderObjClass::RingRenderObjClass -- Constructor - init from a definition				  *
 *   RingRenderObjClass::RingRenderObjClass -- copy constructor										  *
 *   RingRenderObjClass::RingRenderObjClass -- Constructor from a wwmath aaRing					  *
 *   RingRenderObjClass::operator -- assignment operator                                       *
 *   RingRenderObjClass::Clone -- clones the Ring															  *
 *   RingRenderObjClass::Class_ID -- returns the class-id for AARing's								  *
 *   RingRenderObjClass::Render -- render this Ring														  *
 *   RingRenderObjClass::Special_Render -- special render this Ring (vis)							  *
 *   RingRenderObjClass::Set_Transform -- set the transform for this Ring							  *
 *   RingRenderObjClass::Set_Position -- Set the position of this Ring								  *
 *   RingRenderObjClass::update_cached_Ring -- update the world-space version of this Ring	  *
 *   RingRenderObjClass::Cast_Ray -- cast a ray against this Ring										  *
 *   RingRenderObjClass::Cast_AARing -- cast an AARing against this Ring							  *
 *   RingRenderObjClass::Cast_OBRing -- cast an OBRing against this Ring							  *
 *   RingRenderObjClass::Get_Obj_Space_Bounding_Sphere -- return the object-space bounding sper*
 *   RingRenderObjClass::Get_Obj_Space_Bounding_Box -- returns the obj-space bounding box      *
 *   RingRenderObjClass::Scale -- scales ring uniformly.                                       *
 *   RingRenderObjClass::Scale -- scales ring non-uniformly.                                   *
 *   RingRenderObjClass::Update_Cached_Bounding_Volumes -- Updates world-space bounding volum  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */


#include "ringobj.h"
#include "w3d_util.h"
#include "wwdebug.h"
#include "vertmaterial.h"
#include "ww3d.h"
#include "chunkio.h"
#include "rinfo.h"
#include "coltest.h"
#include "inttest.h"
#include	"matrix3.h"
#include	"wwmath.h"
#include "assetmgr.h"
#include "wwstring.h"
#include "bound.h"
#include "camera.h"
#include "statistics.h"
#include "predlod.h"
#include "dx8wrapper.h"
#include "dx8indexbuffer.h"
#include "dx8vertexbuffer.h"
#include "sortingrenderer.h"
#include "vector3i.h"
#include "visrasterizer.h"


float RingRenderObjClass::Get_Cost(void) const
{
	return Get_Num_Polys();	// Currently cost == polys
}
