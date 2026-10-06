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
// Target RVA0x001A3190 262B: aggregate vtable VA0x00BD6C70 slot0x30.
// Target establishes RenderObj slots0x18/0x80/0x84/0x88/0xC8 and
// inline refcount at +4. Names and traversal algorithm derive from donor.
RenderObjClass *
AggregateDefClass::Find_Subobject
(
	RenderObjClass &model,
	const char mesh_path[MESH_PATH_ENTRIES][MESH_PATH_ENTRY_LEN],
	const char bone_path[MESH_PATH_ENTRIES][MESH_PATH_ENTRY_LEN]
)
{
	RenderObjClass *parent_model = &model;
	parent_model->Add_Ref ();

	// Loop through all the models in our "path" until we've either failed
	// or found the exact mesh we were looking for...
	for (int index = 1;
		  (mesh_path[index][0] != 0) && (parent_model != NULL);
		  index ++) {

		// Look one level deeper into the subobject chain...
		RenderObjClass *sub_obj = NULL;
		if (bone_path[index][0] == 0) {
			sub_obj = parent_model->Get_Sub_Object_By_Name (mesh_path[index]);
		} else {

			int bone_index = parent_model->Get_Bone_Index (bone_path[index]);
			int subobj_count = parent_model->Get_Num_Sub_Objects_On_Bone (bone_index);

			// Loop through all the subobjects on this bone
			for (int subobj_index = 0; (subobj_index < subobj_count) && (sub_obj == NULL); subobj_index ++) {

				// Is this the subobject we were looking for?
				RenderObjClass *ptemp_obj = parent_model->Get_Sub_Object_On_Bone (subobj_index, bone_index);
				if (::lstrcmpi (ptemp_obj->Get_Name (), mesh_path[index]) == 0) {
					sub_obj = ptemp_obj;
				} else {
					REF_PTR_RELEASE (ptemp_obj);
				}
			}
		}

		REF_PTR_RELEASE (parent_model);

		// The parent for the next iteration is the subobject on this one.
		parent_model = sub_obj;
	}

	// Return a pointer to the subobject
	return parent_model;
}
