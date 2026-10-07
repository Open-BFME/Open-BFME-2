// cl: /Ireference/shims/bfme2renderobj /DNDEBUG /DWIN32 /D_WINDOWS /MT /EHsc /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
// BFME 2 AggregateDefClass::Build_Subobject_List, RVA 0x001A4010, 1039 bytes.
// Donor: BFME 1 a38d345e79e3bfa4417212ffa37d53ca1ccae65f,
// game/Libraries/Source/WWVegas/WW3D2/agg_def.cpp; continued from the
// banked BFME 2 reconstruction at reverse/attempts/0x001a4010.cpp.
// Target evidence: AggregateDef table 0x00BD6C70 has this method at +0x40,
// Is_Object_In_List at +0x3C, and Add_Subobject at +0x38. Matched Initialize
// calls +0x40 after creating the vanilla model. Target accesses establish
// the bone/subobject virtual slots; names and algorithm come from the donor.
// The target omits an intermediate cleanup state across array deallocation.
// Declare the pointer-array deallocator nonthrowing to preserve that lifetime.
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
#include "rendobj.h"	// the bfmerendobj shim has to win the include guard
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
 *                     $Archive:: /Commando/Code/ww3d2/agg_def.cpp          $*
 *                                                                                             *
 *                       Author:: Patrick Smith
 *                                                                                             *
 *                     $Modtime:: 4/05/01 10:21a                                              $*
 *                                                                                             *
 *                    $Revision:: 5                                                           $*
 *                                                                                             *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */


#include "agg_def.h"
#include "htree.h"
#include "w3derr.h"
#include "chunkio.h"
#include "wwdebug.h"
#include "assetmgr.h"
#include "matinfo.h"
#include "texture.h"
#include "wwstring.h"

#include <windows.h>


void __cdecl operator delete[](void *) throw();
class AggregateSubobjectCalls { public:
virtual void slot0()=0;
virtual void slot1()=0;
virtual void slot2()=0;
virtual void slot3()=0;
virtual void slot4()=0;
virtual void slot5()=0;
virtual void slot6()=0;
virtual void slot7()=0;
virtual void slot8()=0;
virtual void slot9()=0;
virtual void slot10()=0;
virtual void slot11()=0;
virtual void slot12()=0;
virtual void slot13()=0;
virtual void slot14()=0;
virtual bool Is_Object_In_List(const char *, DynamicVectorClass<RenderObjClass *> &)=0;
};

void
AggregateDefClass::Build_Subobject_List
(
	RenderObjClass &original_model,
	RenderObjClass &model
)
{
	extern RenderObjClass * Create_Render_Obj (const char *passet_name);
	int index;

	// Loop through all the bones in this render obj
	int bone_count = model.Get_Num_Bones ();
	for (int bone_index = 0; bone_index < bone_count; bone_index ++) {
		const char *pbone_name = model.Get_Bone_Name (bone_index);

		// Build a list of nodes that are contained in the vanilla model
		DynamicVectorClass <RenderObjClass *> orig_node_list;
		for (index = 0;
			  index < original_model.Get_Num_Sub_Objects_On_Bone (bone_index);
			  index ++) {
			RenderObjClass *psubobj = original_model.Get_Sub_Object_On_Bone (index, bone_index);
			if (psubobj != NULL) {
				orig_node_list.Add (psubobj);
			}
		}

		// Build a list of nodes that are contained in this bone
		DynamicVectorClass <RenderObjClass *> node_list;
		for (index = 0;
			  index < model.Get_Num_Sub_Objects_On_Bone (bone_index);
			  index ++) {
			RenderObjClass *psubobj = model.Get_Sub_Object_On_Bone (index, bone_index);
			if (psubobj != NULL) {
				node_list.Add (psubobj);
			}
		}

		register int node_count = node_list.Count ();
		if (node_count > 0) {

			// Loop through the subobjects and add each one to our internal list
			W3dAggregateSubobjectStruct subobj_info = { 0 };
			for (int node_index = 0; node_index < node_count; node_index ++) {
				RenderObjClass *psubobject = node_list[node_index];
				WWASSERT (psubobject != NULL);

				// Is this subobject new?  (i.e. not in a 'vanilla' instance?)
				const char *prototype_name = psubobject->Get_Name ();
				if (psubobject != NULL &&
					 (reinterpret_cast<AggregateSubobjectCalls *>(this)->Is_Object_In_List (prototype_name, orig_node_list) == false)) {

					// Add this subobject to our list
					::lstrcpy (subobj_info.SubobjectName, prototype_name);
					::lstrcpy (subobj_info.BoneName, pbone_name);
					Add_Subobject (subobj_info);
					m_Info.SubobjectCount ++;

					// Attach this render object to the 'original' model (this is done
					// so we can do texture compares later)
					// Target attachment is a nonthrowing virtual call at +0x94.
					// Keep this call view local; other slots are not identified here.
					class __declspec (novtable) RetailRenderObjCallView {
					public:
						virtual void slot00 (void) = 0;
						virtual void slot01 (void) = 0;
						virtual void slot02 (void) = 0;
						virtual void slot03 (void) = 0;
						virtual void slot04 (void) = 0;
						virtual void slot05 (void) = 0;
						virtual void slot06 (void) = 0;
						virtual void slot07 (void) = 0;
						virtual void slot08 (void) = 0;
						virtual void slot09 (void) = 0;
						virtual void slot10 (void) = 0;
						virtual void slot11 (void) = 0;
						virtual void slot12 (void) = 0;
						virtual void slot13 (void) = 0;
						virtual void slot14 (void) = 0;
						virtual void slot15 (void) = 0;
						virtual void slot16 (void) = 0;
						virtual void slot17 (void) = 0;
						virtual void slot18 (void) = 0;
						virtual void slot19 (void) = 0;
						virtual void slot20 (void) = 0;
						virtual void slot21 (void) = 0;
						virtual void slot22 (void) = 0;
						virtual void slot23 (void) = 0;
						virtual void slot24 (void) = 0;
						virtual void slot25 (void) = 0;
						virtual void slot26 (void) = 0;
						virtual void slot27 (void) = 0;
						virtual void slot28 (void) = 0;
						virtual void slot29 (void) = 0;
						virtual void slot30 (void) = 0;
						virtual void slot31 (void) = 0;
						virtual void slot32 (void) = 0;
						virtual void slot33 (void) = 0;
						virtual void slot34 (void) = 0;
						virtual void slot35 (void) = 0;
 virtual void slot36(void) = 0;
						virtual int Add_Sub_Object_To_Bone (RenderObjClass *, const char *, const Vector3 *) throw () = 0;
						static __forceinline void Attach (RenderObjClass *model, RenderObjClass *subobj, const char *bone)
						{
							((RetailRenderObjCallView *)model)->Add_Sub_Object_To_Bone (subobj, bone, NULL);
						}
					};
					RenderObjClass *prender_obj = Create_Render_Obj (prototype_name);
					RetailRenderObjCallView::Attach (&original_model, prender_obj, pbone_name);
					if (prender_obj != NULL) {
						prender_obj->Release_Ref ();
					}
				}
			}
		}

		// Free our hold on the render objs in the original node list
		for (index = 0; index < orig_node_list.Count (); index ++) {
			RenderObjClass *p_orig_node = orig_node_list[index];
			if (p_orig_node != NULL) {
				p_orig_node->Release_Ref ();
				orig_node_list[index] = NULL;
			}
		}
		orig_node_list.Delete_All ();

		// Free our hold on the render objs in the node list
		for (index = 0; index < node_list.Count (); index ++) {
			RenderObjClass *p_node = node_list[index];
			if (p_node != NULL) {
				p_node->Release_Ref ();
				node_list[index] = NULL;
			}
		}
		node_list.Delete_All ();
	}

	return ;
}
