// cl: /Ireference/shims/bfme2renderobj /DNDEBUG /DWIN32 /D_WINDOWS /MT /EHsc /Ireference/shims/sweep /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/Compression /Ireference/shims/sweep
// The compiler-generated vector constructor iterator (??_H) takes the
// optimization state of the first function that needs it. Retail links one
// copy, the /O1 body at 0x00001423; this unemitted anchor makes this unit's
// copy that same body, so it no longer loses to retail's at link time.
// It can also change how later array constructions here compile; checked to
// change nothing else in this unit, but if a function added later that builds
// an array will not match, try it without this block.
struct BfmeVciAnchorElem { BfmeVciAnchorElem(); };
#pragma optimize("gsy", on)
// Share the retail size context with the RefCountClass release declaration.
#include "refcount.h"
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
#include "rendobj.h"
#include "agg_def.h"
#include "wwdebug.h"
#include <windows.h>

// BFME1 donor revision 5cae4bdffcc0fb2dd6f0a2a6c1a7328bd0fb0cfc,
// game/Libraries/Source/WWVegas/WW3D2/agg_def.cpp.
// Target RVA0x001A3880 87B: aggregate vtable VA0x00BD6C70 slot0x2C.
// Target factory is the rowed global Create_Render_Obj RVA0x00136175.
// Target attachment uses RenderObj slot0x94 with trailing null offset;
// target inline release decrements +4 and calls slot0 at zero.
RenderObjClass * __cdecl Create_Render_Obj(const char *);
void
AggregateDefClass::Attach_Subobjects (RenderObjClass &base_model)
{
	// Now loop through all the subobjects and attach them to the appropriate bone
	for (int index = 0; index < m_SubobjectList.Count (); index ++) {
		W3dAggregateSubobjectStruct *psubobj_info = m_SubobjectList[index];
		if (psubobj_info != NULL) {

			// Now create this subobject and attach it to its bone.
			RenderObjClass *prender_obj = ::Create_Render_Obj (psubobj_info->SubobjectName);
			if (prender_obj != NULL) {

				// Attach this object to the requested bone
				if (base_model.Add_Sub_Object_To_Bone (prender_obj, psubobj_info->BoneName) == false) {
					WWDEBUG_SAY (("Unable to attach %s to %s.\r\n", psubobj_info->SubobjectName, psubobj_info->BoneName));
				}

				// Release our hold on this pointer
				prender_obj->Release_Ref ();
			} else {
				WWDEBUG_SAY (("Unable to load aggregate subobject %s.\r\n", psubobj_info->SubobjectName));
			}
		}
	}

	return ;
}
