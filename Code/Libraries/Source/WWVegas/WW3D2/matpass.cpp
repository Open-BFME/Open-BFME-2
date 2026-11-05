// cl: /Ireference/shims/bfmeshader /DBFME_WWSTRING_NATIVE_CSTR_ASSIGN /Ireference/shims/wwstring_teardown/zhmd /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
// platformsdk
// dxsdk
// stlport
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
 *                 Project Name : WW3d                                                         *
 *                                                                                             *
 *                     $Archive:: /Commando/Code/ww3d2/matpass.cpp                            $*
 *                                                                                             *
 *              Original Author:: Greg Hjelstrom                                               *
 *                                                                                             *
 *                       Author : Kenny Mitchell                                               * 
 *                                                                                             * 
 *                     $Modtime:: 06/27/02 1:27p                                              $*
 *                                                                                             *
 *                    $Revision:: 8                                                           $*
 *                                                                                             *
 * 06/27/02 KM Changes to max texture stage caps															*
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 *   MaterialPassClass::MaterialPassClass -- Constructor                                       *
 *   MaterialPassClass::~MaterialPassClass -- Destructor                                       *
 *   MaterialPassClass::Install_Materials -- Plug our material settings into D3D               *
 *   MaterialPassClass::Set_Texture -- Set texture to use                                      *
 *   MaterialPassClass::Set_Shader -- Set the shader to use                                    *
 *   MaterialPassClass::Set_Material -- set vertex material to use                             * 
 *   MaterialPassClass::Get_Texture -- Get a pointer to the texture                            *
 *   MaterialPassClass::Get_Material -- get the vertex material                                *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */


#include "dx8caps.h" // BFME2 DX8Caps layout (MaxTexturesPerPass at +0x2B0) has to win the include guard over the ZH sibling
#include "matpass.h"
#include "vertmaterial.h"
#include "shader.h"
#include "texture.h"
#include "statistics.h"
#include "dx8wrapper.h"


bool MaterialPassClass::EnablePerPolygonCulling = true;


/***********************************************************************************************
 * MaterialPassClass::MaterialPassClass -- Constructor                                         *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   2/26/2001  gth : Created.                                                                 *
 *=============================================================================================*/
// ??0MaterialPassClass@@ is implemented by the exact retail thunk in
// MaterialPassClassCtorThunk.cpp.

/***********************************************************************************************
 * MaterialPassClass::~MaterialPassClass -- Destructor                                         *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   12/9/99    gth : Created.                                                                 *
 *	  06/27/02   kjm : Changes to max texture stage caps															*
 *=============================================================================================*/
// The exact BFME destructor is implemented in MaterialPassClassDestructor.cpp,
// whose local declaration preserves BFME's owning texture-stage wrappers.


/***********************************************************************************************
 * MaterialPassClass::Install_Materials -- Plug our material settings into D3D                 *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   12/9/99    gth : Created.                                                                 *
 *   2/26/2001  gth : Changed to Install_Materials                                             *
 *=============================================================================================*/
// MaterialPassClass::Install_Materials is rowed at 0x0013EFA0 in
// MaterialPassInstallMaterials.cpp; this unit's copy was not retail's.
// Its Peek_Texture call kept the rowed out-of-line accessor (0x002C7469)
// emitted here; this anchor keeps it.
// ?bfmeAnchorMatpassPeekTexture absent-from-retail
TextureClass *bfmeAnchorMatpassPeekTexture(const MaterialPassClass *pass)
{
	return pass->Peek_Texture(0);
}

/***********************************************************************************************
 * MaterialPassClass::Set_Shader -- Set the shader to use                                      *
 *                                                                                             *
 * INPUT:                                                                                      *
 * shader - shader for this material pass                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   12/9/99    gth : Created.                                                                 *
 *=============================================================================================*/
void MaterialPassClass::Set_Shader(ShaderClass shader)
{
	Shader = shader;
	Shader.Enable_Fog ("MaterialPassClass");
}


/***********************************************************************************************
 * MaterialPassClass::Set_Material -- set vertex material to use                               *
 *                                                                                             *
 * INPUT:                                                                                      *
 * mat - pointer to the vertex material this material pass uses                                *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   12/9/99    gth : Created.                                                                 *
 *=============================================================================================*/
void MaterialPassClass::Set_Material(VertexMaterialClass * mat)
{
	REF_PTR_SET(Material,mat);
}
