// cl: /arch:SSE2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression
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

/*************************************************************************************************** 
 ***                  C O N F I D E N T I A L  ---  W E S T W O O D  S T U D I O S               *** 
 *************************************************************************************************** 
 *                                                                                                 * 
 *                     Project Name : G                                                            * 
 *                                                                                                 * 
 *                         $Archive::                                                             $* 
 *                                                                                                 * 
 *                          Creator::Scott K. Bowen - 7/15/2002                                        *
 *                                                                                                 * 
 *                          $Author::                                                             $* 
 *                                                                                                 * 
 *                         $Modtime::                                                             $* 
 *                                                                                                 * 
 *                        $Revision::                                                             $* 
 *                                                                                                 * 
 *-------------------------------------------------------------------------------------------------* 
 * Functions:                                                                                      * 
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  - - -  - - */

////////////////////////////////////////////////////////////////////////////////////////////////////
// Include files ///////////////////////////////////////////////////////////////////////////////////

// RefCountClass's inline members and deleting destructor are retail's
// size-optimised bodies: compile them for size, as hlod.cpp does.
// multilist.h's inline members are retail's size-optimised bodies: compile
// them for size (as hlod.cpp/decalsys.cpp do) so this unit's copies match.
#include "multilist.h"
#pragma optimize("", on)
#include "refcount.h"
#include "static_sort_list.h"

#include "rendobj.h"
// bfme link decl-only begin
template <> bool RefMultiListClass<RenderObjClass>::Release_Head();
// bfme link decl-only end

////////////////////////////////////////////////////////////////////////////////////////////////////
// Initialization Functions ////////////////////////////////////////////////////////////////////////

DefaultStaticSortListClass::DefaultStaticSortListClass(void) :
	StaticSortListClass(),
	SortLists(),
	MinSort(1),
	MaxSort(MAX_SORT_LEVEL)
{
}

DefaultStaticSortListClass::~DefaultStaticSortListClass(void)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// Virtual functions ///////////////////////////////////////////////////////////////////////////////

void DefaultStaticSortListClass::Add_To_List(RenderObjClass * robj, unsigned int sort_level)
{
	if(sort_level < 1 || sort_level > MAX_SORT_LEVEL) {
		WWASSERT(0);
		return;
	}
	SortLists[sort_level].Add_Tail(robj, false);
}

// BFME 2 retail 0x001769B0 (121 bytes): the render hooks are gone, the mesh renderer is
// reached through a pointer, and every level that rendered also flushes the FXShader
// renderer (the gap-filler context at 0x00DF6F94, flush 0x00174BA6).
#include "Rva00DF6F94GapFillerContext.h"
extern Rva00DF6F94GapFillerContext *TheMeshGapFillerContext;
#include "DX8MeshRendererClass.h"
extern DX8MeshRendererClass *TheDX8MeshRenderer;

void DefaultStaticSortListClass::Render_And_Clear(RenderInfoClass & rinfo)
{
	// We go from higher sort level to lower, since lower sort level means higher priority (in
	// front), so lower sort level meshes need to be rendered later.
	for(unsigned int sort_level = MaxSort; sort_level >= MinSort; sort_level--) {
		bool render=false;
		for (	RenderObjClass *robj = SortLists[sort_level].Remove_Head(); robj;
				robj = SortLists[sort_level].Remove_Head())
		{
			robj->Render(rinfo);
			robj->Release_Ref();
			render = true;
		}
		if (render) {
			TheDX8MeshRenderer->Flush();
			TheMeshGapFillerContext->rva174ba6();
		}
	}
}

