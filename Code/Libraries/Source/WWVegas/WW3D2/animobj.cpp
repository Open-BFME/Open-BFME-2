// cl: /Ireference/shims/bfme2hanim /Ireference/shims/bfme2htree /Ireference/shims/bfme2renderobj /Ireference/shims/bfmeanimobj /arch:SSE /G7 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
// Derived from the Generals Zero Hour reference with verified BFME2 ownership.
// (Libraries/Source/WWVegas/WW3D2/animobj.cpp); this unit had no counterpart under Code/.
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
#include "rendobj.h"	// the verified BFME2 base object must win the include guard
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
 *                     $Archive:: /Commando/Code/ww3d2/animobj.cpp                            $*
 *                                                                                             *
 *                       Author:: Greg_h                                                       *
 *                                                                                             *
 *                     $Modtime:: 12/13/01 6:56p                                              $*
 *                                                                                             *
 *                    $Revision:: 10                                                          $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 *   Animatable3DObjClass::Animatable3DObjClass -- constructor                                 *
 *   Animatable3DObjClass::Animatable3DObjClass -- copy constructor                            *
 *   Animatable3DObjClass::~Animatable3DObjClass -- destructor                                 *
 *   Animatable3DObjClass::operator = -- assignment operator                                   *
 *   Animatable3DObjClass::Release -- Releases any anims being held by this object             *
 *   Animatable3DObjClass::Render -- Update this object for rendering                          *
 *   Animatable3DObjClass::Special_Render -- "special render" function for animatables         *
 *   Animatable3DObjClass::Set_Transform -- sets the transform and marks sub-objects as dirty  *
 *   Animatable3DObjClass::Set_Position -- Sets the position and marks sub-objects as dirty    *
 *   Animatable3DObjClass::Get_Num_Bones -- returns number of bones in this object             *
 *   Animatable3DObjClass::Get_Bone_Name -- returns the name of the given bone                 *
 *   Animatable3DObjClass::Get_Bone_Index -- returns the index of the given bone               *
 *   Animatable3DObjClass::Set_Animation -- set the animation state to "none" (base pose)      *
 *   Animatable3DObjClass::Set_Animation -- Set the animation state to the given anim/frame    *
 *   Animatable3DObjClass::Set_Animation -- set the animation state to a blend of two anims    *
 *   Animatable3DObjClass::Set_Animation -- Set animation state with an anim combo             *
 *   Animatable3DObjClass::Get_Bone_Transform -- return the transform for the given bone       *
 *   Animatable3DObjClass::Get_Bone_Transform -- return the transform for the given bone       *
 *   Animatable3DObjClass::Capture_Bone -- capture the specified bone (override animation)     *
 *   Animatable3DObjClass::Release_Bone -- release the specified bone (allow animation)        *
 *   Animatable3DObjClass::Is_Bone_Captured -- returns whether the specified bone is captured  *
 *   Animatable3DObjClass::Control_Bone -- sets the transform for the bone                     *
 *   Animatable3DObjClass::Update_Sub_Object_Transforms -- recalculate the transforms for our  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */


#include "animobj.h"
#include "htree.h"
#include "assetmgr.h"
#include "hanim.h"
#include "hcanim.h"
#include "ww3d.h"
#include "wwmemlog.h"
#include "animatedsoundmgr.h"


/***********************************************************************************************
 * Animatable3DObjClass::Animatable3DObjClass -- constructor                                   *
 *                                                                                             *
 * INPUT:                                                                                      *
 * htree_name -- name of the hierarchy tree which defines the "bone" structure for this object *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   12/8/98    GTH : Created.                                                                 *
 *=============================================================================================*/
// BFME fetches a named hierarchy through a free helper at 0x0017FC7C rather
// than through the asset manager's virtual Get_HTree.
HTreeClass * Get_HTree(const char * name);

// ?Animatable3DObjClass::Animatable3DObjClass present-unmatched
Animatable3DObjClass::Animatable3DObjClass(const char * htree_name) :
	IsTreeValid(0),
	HTree(NULL),
	_bfme_a3o_v0(NULL),
	CurMotionMode(BASE_POSE)
{
	// Inline struct members can't be initialized in init list for some reason...
  ModeAnim.Motion=NULL;
	ModeAnim.Frame=0.0f;
	ModeAnim.PrevFrame=0.0f;
	ModeAnim.LastSyncTime=WW3D::Get_Sync_Time();
	ModeAnim.frameRateMultiplier=1.0;	// 020607 srj -- added
	ModeAnim.animDirection=1.0;	// 020607 srj -- added
	ModeInterp.Motion0=NULL;
	ModeInterp.Motion1=NULL;
	ModeInterp.Frame0=0.0f;
	ModeInterp.Frame1=0.0f;
	ModeInterp.Percentage=0.0f;
	ModeCombo.AnimCombo=NULL;
  
	/*
	** Store a pointer to the htree
	*/
	if (htree_name == NULL) {
		HTree = NULL;
	} else if (htree_name[0] == 0) {
		HTree = W3DNEW HTreeClass;
		HTree->Init_Default ();
	} else {
		HTreeClass * source = ::Get_HTree(htree_name);
		if (source != NULL) {
			HTree = W3DNEW HTreeClass(*source);
		} else {
			WWDEBUG_SAY(("Unable to find HTree: %s\r\n",htree_name));
			HTree = W3DNEW HTreeClass;
			HTree->Init_Default();
		}
	}
}


/***********************************************************************************************
 * Animatable3DObjClass::Animatable3DObjClass -- copy constructor                              *
 *                                                                                             *
 * INPUT:                                                                                      *
 * src -- animatable object to copy.                                                           *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   12/8/98    GTH : Created.                                                                 *
 *=============================================================================================*/
// ?Animatable3DObjClass::Animatable3DObjClass present-unmatched
Animatable3DObjClass::Animatable3DObjClass(const Animatable3DObjClass & src) :
	CompositeRenderObjClass(src),
	IsTreeValid(0),
	CurMotionMode(BASE_POSE),
	HTree(NULL),
	_bfme_a3o_v0(NULL)
{
   // Inline struct members can't be initialized in init list for some reason...
	ModeAnim.Motion=NULL;
	ModeAnim.Frame=0.0f;
	ModeAnim.PrevFrame=0.0f;
	ModeAnim.LastSyncTime=WW3D::Get_Sync_Time();
	ModeAnim.frameRateMultiplier=1.0;	// 020607 srj -- added
	ModeAnim.animDirection=1.0;	// 020607 srj -- added
	ModeInterp.Motion0=NULL;
	ModeInterp.Motion1=NULL;
	ModeInterp.Frame0=0.0f;
	ModeInterp.Frame1=0.0f;
	ModeInterp.Percentage=0.0f;
	ModeCombo.AnimCombo=NULL;

	*this = src;
}


/***********************************************************************************************
 * Animatable3DObjClass::~Animatable3DObjClass -- destructor                                   *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   12/8/98    GTH : Created.                                                                 *
 *=============================================================================================*/
// ?Animatable3DObjClass::~Animatable3DObjClass present-unmatched
Animatable3DObjClass::~Animatable3DObjClass(void)
{
	Release();

	if (HTree) {
		delete HTree;
	}
}


/***********************************************************************************************
 * Animatable3DObjClass::operator = -- assignment operator                                     *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   3/2/99     GTH : Created.                                                                 *
 *=============================================================================================*/
Animatable3DObjClass & Animatable3DObjClass::operator = (const Animatable3DObjClass & that)
{ 
	if (&that != this) {
		Release();
		if (HTree) {
			delete HTree;
		}

		CompositeRenderObjClass::operator = (that);

		IsTreeValid = 0;
		CurMotionMode = BASE_POSE;
		ModeAnim.Motion = NULL;
		ModeAnim.Frame = 0.0f;
		ModeAnim.PrevFrame = 0.0f;
		ModeAnim.LastSyncTime = WW3D::Get_Sync_Time();
		ModeAnim.frameRateMultiplier=1.0;	// 020607 srj -- added
		ModeAnim.animDirection=1.0;	// 020607 srj -- added
		ModeInterp.Motion0 = NULL;
		ModeInterp.Motion1 = NULL;
		ModeInterp.Frame0 = 0.0f;
		ModeInterp.Frame1 = 0.0f;
		ModeInterp.Percentage = 0.0f;
		ModeCombo.AnimCombo = NULL;

		HTree = W3DNEW HTreeClass(*that.HTree);
	}
	return *this; 
}

/***********************************************************************************************
 * Animatable3DObjClass::Release -- Releases any anims being held by this object               *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   12/8/98    GTH : Created.                                                                 *
 *=============================================================================================*/
// Animatable3DObjClass::Release: defined in Animatable3DObjRelease.cpp (its row's unit).

/***********************************************************************************************
 * Animatable3DObjClass::Render -- Update this object for rendering                            *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   12/8/98    GTH : Created.                                                                 *
 *=============================================================================================*/
// ?Animatable3DObjClass::Render present-unmatched
void Animatable3DObjClass::Render(RenderInfoClass & rinfo)
{
	if (HTree == NULL) return;

	if (Is_Not_Hidden_At_All() == false) {
		return;
	}

	if ( CurMotionMode == SINGLE_ANIM ) {
		if ( ModeAnim.AnimMode != ANIM_MODE_MANUAL ) {
			Single_Anim_Progress();
		}
	}

	if (!Is_Hierarchy_Valid() || Are_Sub_Object_Transforms_Dirty()) {
		Update_Sub_Object_Transforms();
	}
}

/***********************************************************************************************
 * Animatable3DObjClass::Special_Render -- "special render" function for animatables           *
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
// ?Animatable3DObjClass::Special_Render present-unmatched
void Animatable3DObjClass::Special_Render(SpecialRenderInfoClass & rinfo)
{
	if (HTree == NULL) return;

	if ( CurMotionMode == SINGLE_ANIM ) {
		if ( ModeAnim.AnimMode != ANIM_MODE_MANUAL ) {
			Single_Anim_Progress();
		}
	}

	if (!Is_Hierarchy_Valid()) {
		Update_Sub_Object_Transforms();
	}
}


/***********************************************************************************************
 * Animatable3DObjClass::Set_Transform -- sets the transform and marks sub-objects as dirty    *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   3/2/99     GTH : Created.                                                                 *
 *=============================================================================================*/
// ?Animatable3DObjClass::Set_Transform present-unmatched
void Animatable3DObjClass::Set_Transform(const Matrix3D &m)
{ 
	CompositeRenderObjClass::Set_Transform(m); 
	Set_Hierarchy_Valid(false); 
}


/***********************************************************************************************
 * Animatable3DObjClass::Set_Position -- Sets the position and marks sub-objects as dirty      *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   3/2/99     GTH : Created.                                                                 *
 *=============================================================================================*/
// ?Animatable3DObjClass::Set_Position present-unmatched
void Animatable3DObjClass::Set_Position(const Vector3 &v)
{ 
	CompositeRenderObjClass::Set_Position(v); 
	Set_Hierarchy_Valid(false); 
}


/***********************************************************************************************
 * Animatable3DObjClass::Get_Num_Bones -- returns number of bones in this object               *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   3/2/99     GTH : Created.                                                                 *
 *=============================================================================================*/
int Animatable3DObjClass::Get_Num_Bones(void)
{
	if (HTree) {
		return HTree->Num_Pivots();
	} else {
		return 1;
	}
}


/***********************************************************************************************
 * Animatable3DObjClass::Get_Bone_Name -- returns the name of the given bone                   *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   3/2/99     GTH : Created.                                                                 *
 *=============================================================================================*/
const char * Animatable3DObjClass::Get_Bone_Name(int bone_index)
{
	if (HTree) {
		return HTree->Get_Bone_Name(bone_index);
	} else {
		return "RootTransform";
	}
}


/***********************************************************************************************
 * Animatable3DObjClass::Get_Bone_Index -- returns the index of the given bone                 *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   3/2/99     GTH : Created.                                                                 *
 *=============================================================================================*/
int Animatable3DObjClass::Get_Bone_Index(const char * bonename)
{
	if (HTree) {
		return HTree->Get_Bone_Index(bonename);
	} else {
		return 0;
	}
}



/***********************************************************************************************
 * Animatable3DObjClass::Set_Animation -- set the animation state to "none" (base pose)        *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   12/8/98    GTH : Created.                                                                 *
 *=============================================================================================*/
void Animatable3DObjClass::Set_Animation(void)
{
	Release();
	CurMotionMode = BASE_POSE;
	Set_Hierarchy_Valid(false);
}


/***********************************************************************************************
 * Animatable3DObjClass::Set_Animation -- Set the animation state to the given anim/frame      *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   12/8/98    GTH : Created.                                                                 *
 *=============================================================================================*/
// Animatable3DObjClass::Set_Animation(HAnimClass*, float, int): defined in Animatable3DObjSetAnimationMH.cpp (its row's unit).	

/***********************************************************************************************
 * Animatable3DObjClass::Set_Animation -- set the animation state to a blend of two anims      *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   12/8/98    GTH : Created.                                                                 *
 *=============================================================================================*/
// Animatable3DObjClass::Set_Animation(HAnimClass*, float, HAnimClass*, float, float): defined in Animatable3DObjSetAnimationBlend.cpp (its row's unit).


/***********************************************************************************************
 * Animatable3DObjClass::Set_Animation -- Set animation state with an anim combo               *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   12/8/98    GTH : Created.                                                                 *
 *=============================================================================================*/
// Animatable3DObjClass::Set_Animation(HAnimComboClass*): defined in Animatable3DObjSetAnimationCombo.cpp (its row's unit).


/***********************************************************************************************
 * Animatable3DObjClass::Peek_Animation													                 *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   12/8/98    GTH : Created.                                                                 *
 *=============================================================================================*/
// ?Animatable3DObjClass::Peek_Animation present-unmatched
HAnimClass *	Animatable3DObjClass::Peek_Animation( void )
{
	if ( CurMotionMode == SINGLE_ANIM ) {
		return ModeAnim.Motion;
	} else {
		return NULL;
	}
}


/***********************************************************************************************
 * Animatable3DObjClass::Get_Bone_Transform -- return the transform for the given bone         *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   12/8/98    GTH : Created.                                                                 *
 *=============================================================================================*/
// ?Animatable3DObjClass::Get_Bone_Transform present-unmatched
const Matrix3D &	Animatable3DObjClass::Get_Bone_Transform(const char * bonename)
{
	if (HTree) {
		WWASSERT(HTree);
		WWASSERT(bonename);
		
		int idx = HTree->Get_Bone_Index(bonename);
		return Get_Bone_Transform(idx);
	} else {
		return Get_Transform();
	}
}


/***********************************************************************************************
 * Animatable3DObjClass::Get_Bone_Transform -- return the transform for the given bone         *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   12/8/98    GTH : Created.                                                                 *
 *=============================================================================================*/
// ?Animatable3DObjClass::Get_Bone_Transform present-unmatched
const Matrix3D &	Animatable3DObjClass::Get_Bone_Transform(int boneindex)
{
	Validate_Transform();

	if (HTree) {
		/*
		** If our hierarchy isn't valid, we just need to evaluate our animation
		** state.
		*/
		if (!Is_Hierarchy_Valid()) {
			Update_Sub_Object_Transforms();
		}

		return HTree->Get_Transform(boneindex);
	} else {
		return Transform;
	}
}


/***********************************************************************************************
 * Animatable3DObjClass::Capture_Bone -- capture the specified bone (override animation)       *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   3/2/99     GTH : Created.                                                                 *
 *=============================================================================================*/
// ?Animatable3DObjClass::Capture_Bone present-unmatched
void Animatable3DObjClass::Capture_Bone(int boneindex)
{ 
	if (HTree) {
		HTree->Capture_Bone(boneindex); 
	}
}


/***********************************************************************************************
 * Animatable3DObjClass::Release_Bone -- release the specified bone (allow animation)          *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   3/2/99     GTH : Created.                                                                 *
 *=============================================================================================*/
// ?Animatable3DObjClass::Release_Bone present-unmatched
void Animatable3DObjClass::Release_Bone(int boneindex)
{ 
	if (HTree) {
		HTree->Release_Bone(boneindex); 
	}
}


/***********************************************************************************************
 * Animatable3DObjClass::Is_Bone_Captured -- returns whether the specified bone is captured    *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   3/2/99     GTH : Created.                                                                 *
 *=============================================================================================*/
bool Animatable3DObjClass::Is_Bone_Captured(int boneindex) const					
{ 
	if (HTree) {
		return HTree->Is_Bone_Captured(boneindex); 
	} else {
		return false;
	}
}


/***********************************************************************************************
 * Animatable3DObjClass::Control_Bone -- sets the transform for the bone                       *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   3/2/99     GTH : Created.                                                                 *
 *=============================================================================================*/
void Animatable3DObjClass::Control_Bone(int bindex,const Matrix3D & objtm,bool world_space_translation)
{ 
#ifdef WWDEBUG	
	for (int j=0; j<3; j++) {
		for (int i=0; i<4; i++) {
			WWASSERT(WWMath::Is_Valid_Float(objtm[j][i]));
		}
	}
#endif

	if (HTree) {
		HTree->Control_Bone(bindex,objtm,world_space_translation); 
		Set_Hierarchy_Valid(false);
	}
}

/***********************************************************************************************
 * Animatable3DObjClass::Update_Sub_Object_Transforms -- recalculate the transforms for our su *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   12/8/98    GTH : Created.                                                                 *
 *=============================================================================================*/
void Animatable3DObjClass::Update_Sub_Object_Transforms(void)
{
	/*
	** BFME: an object slaved to another animatable takes that one's finished
	** pose instead of evaluating any motion of its own. The master's pivots are
	** in the master's object space, so they are carried across through the
	** transform that maps the master's space into ours. (Ported from Open-BFME-1
	** animobj.cpp; retail 0x001A5900 has the same shape.)
	*/
	if (_bfme_a3o_v0 != NULL) {

		if (!_bfme_a3o_v0->Is_Hierarchy_Valid()) {
			_bfme_a3o_v0->Update_Sub_Object_Transforms();
		}

		// Named only after that call: retail re-reads the member across it and
		// then keeps it in a register for the three uses below.
		Animatable3DObjClass * master = _bfme_a3o_v0;

		Matrix3D tm;
		master->Validate_Transform();
		master->Transform.Get_Inverse(tm);

		Validate_Transform();
		Matrix3D::Multiply(Transform,tm,&tm);

		// The member again, not `master`: retail re-reads it across the Multiply,
		// which it has to -- nothing tells the compiler that call cannot touch it.
		HTree->Slave_Update(_bfme_a3o_v0->HTree,tm);

		Set_Hierarchy_Valid(true);
		return;
	}

	/*
	** The RenderObj impementation will cause our 'container' 
	** to update if we are not valid yet
	*/
	CompositeRenderObjClass::Update_Sub_Object_Transforms();

	/*
	** Update the transforms
	*/
	switch (CurMotionMode) {

		case BASE_POSE:
			Base_Update(Transform);
			break;

		/*
		** BFME dropped the AnimatedSoundMgrClass::Trigger_Sound call Zero Hour
		** makes after each of these updates; retail's arms are the bare update.
		*/
		case SINGLE_ANIM:
			
			if ( ModeAnim.AnimMode != ANIM_MODE_MANUAL ) {
				Single_Anim_Progress();
			}
			Anim_Update(Transform,ModeAnim.Motion,ModeAnim.Frame);
			break;

		case DOUBLE_ANIM:
			Blend_Update(Transform,ModeInterp.Motion0,ModeInterp.Frame0,
				ModeInterp.Motion1,ModeInterp.Frame1,ModeInterp.Percentage);
  			break;

		case MULTIPLE_ANIM:
			Combo_Update(Transform,ModeCombo.AnimCombo);
			break;

		default:
			break;
	}
	Set_Hierarchy_Valid(true);
}


/***********************************************************************************************
 * Animatable3DObjClass::Simple_Evaluate_Bone -- If the animation is 'single', evaluate the    *
 *																	given pivot and return its transform.		  *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   04/13/2000    PDS : Created.                                                              *
 *=============================================================================================*/
bool Animatable3DObjClass::Simple_Evaluate_Bone(int boneindex, Matrix3D *tm) const
{
	bool retval = false;

	//
	//	Only do this for simple animations
	//
	if (	CurMotionMode == NONE ||
			CurMotionMode == BASE_POSE ||
			CurMotionMode == SINGLE_ANIM)
	{		
		//
		//	Determine which frame we should be on, then use this
		// information to determine the bone's transform.
		//
		float curr_frame = Compute_Current_Frame ();
		retval = Simple_Evaluate_Bone (boneindex, curr_frame, tm);
	
	} else {
		
		const_cast <Animatable3DObjClass *>(this)->Update_Sub_Object_Transforms();
		*tm = HTree->Get_Transform(boneindex);

	}

	return retval;
}


/***********************************************************************************************
 * Animatable3DObjClass::Simple_Evaluate_Bone -- If the animation is 'single', evaluate the    *
 *																	given pivot and return its transform.		  *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   04/13/2000    PDS : Created.                                                                *
 *=============================================================================================*/
bool Animatable3DObjClass::Simple_Evaluate_Bone(int boneindex, float frame, Matrix3D *tm) const
{
	bool retval = false;

	//
	//	Only do this for simple animations
	//
	if (HTree != NULL) {
		
		if (CurMotionMode == SINGLE_ANIM) {
			retval = HTree->Simple_Evaluate_Pivot (ModeAnim.Motion, boneindex, frame, Get_Transform (), tm);
		} else if (CurMotionMode == NONE || CurMotionMode == BASE_POSE) {
			retval = HTree->Simple_Evaluate_Pivot (boneindex, Get_Transform (), tm);
		} else {
			*tm = Transform;
		}

	} else {
		*tm = Transform;
	}

	return retval;
}


/***********************************************************************************************
 * Animatable3DObjClass::Compute_Current_Frame -- Returns the animation frame for the next rend*
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS: Only works for Single and CSingle!                                                *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   04/13/2000    PDS : Created.                                                              *
 *=============================================================================================*/
// ?Animatable3DObjClass::Compute_Current_Frame present-unmatched
/***********************************************************************************************
 * Animatable3DObjClass::Single_Anim_Progress -- progess anims for loop and once               *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:  Only works for Single and CSingle                                                *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   10/26/99    BMG : Created.                                                                 *
 *=============================================================================================*/
// ?Animatable3DObjClass::Single_Anim_Progress present-unmatched
void Animatable3DObjClass::Single_Anim_Progress(void)
{
    if (CurMotionMode == SINGLE_ANIM) {
        ModeAnim.Frame = Compute_Current_Frame(&ModeAnim.animDirection);
        ModeAnim.LastSyncTime = WW3D::Get_Sync_Time();
        Set_Hierarchy_Valid(false);
    }
}

/***********************************************************************************************
 * Animatable3DObjClass::Is_Animation_Complete -- is the current animation on the last frame?  *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS: Only works for Single, ONCE anims                                                 *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   4/13/99    BMG : Created.                                                                 *
 *=============================================================================================*/
// Animatable3DObjClass::Is_Animation_Complete: defined in Animatable3DObjIsAnimationComplete.cpp (its row's unit).

/***********************************************************************************************
 * Animatable3DObjClass::Peek_Animation_And_Info *
 *=============================================================================================*/
// Animatable3DObjClass::Peek_Animation_And_Info: defined in Animatable3DObjPeekAnimationAndInfo.cpp (its row's unit).

/***********************************************************************************************
 * Animatable3DObjClass::Set_Animation_Frame_Rate_Multiplier *
 *=============================================================================================*/
// ?Animatable3DObjClass::Set_Animation_Frame_Rate_Multiplier present-unmatched
void Animatable3DObjClass::Set_Animation_Frame_Rate_Multiplier(float multiplier)
{
	// 020607 srj -- added
	ModeAnim.frameRateMultiplier = multiplier;
}

// (gth) TESTING DYNAMICALLY SWAPPING SKELETONS!

// ?Animatable3DObjClass::Set_HTree present-unmatched
void Animatable3DObjClass::Set_HTree(HTreeClass * new_htree) 
{ 
	WWMEMLOG(MEM_ANIMATION);
	// try to ensure that the htree we're using has the same structure...
	WWASSERT(new_htree->Num_Pivots() == HTree->Num_Pivots()); 
	
	// just assign it...
	if (HTree != NULL) {
		delete HTree;
	}
	HTree = W3DNEW HTreeClass(*new_htree);
}


// EOF - animobj.cpp

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?Cast_AABox@CompositeRenderObjClass@@UAE_NAAVAABoxCollisionTestClass@@@Z=?Set_Animation_Frame_Rate_Multiplier@Animatable3DObjClass@@UAEXM@Z")
#pragma comment(linker, "/alternatename:?Cast_OBBox@CompositeRenderObjClass@@UAE_NAAVOBBoxCollisionTestClass@@@Z=?Peek_Animation_And_Info@Animatable3DObjClass@@UAEPAVHAnimClass@@AAMAAH10@Z")
#pragma comment(linker, "/alternatename:?Intersect_AABox@CompositeRenderObjClass@@UAE_NAAVAABoxIntersectionTestClass@@@Z=?Is_Animation_Complete@Animatable3DObjClass@@UBE_NXZ")
