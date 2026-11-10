// cl: /G7 /arch:SSE /Ireference/shims/bfmecamera /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /DNDEBUG /MD /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
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
#define Matrix4x4 Matrix4
// RefCountClass's inline members and deleting destructor are retail's
// size-optimised bodies: compile them for size, as hlod.cpp does.
#pragma optimize("s", on)
#include "../../../../../reference/shims/bfmepool/mempool.h"
#include "refcount.h"
#pragma optimize("", on)
#include "winbase_shim.h"
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

/* $Header: /Commando/Code/ww3d2/hanim.cpp 3     12/13/01 7:01p Patrick $ */
/*********************************************************************************************** 
 ***                            Confidential - Westwood Studios                              *** 
 *********************************************************************************************** 
 *                                                                                             * 
 *                 Project Name : Commando / G 3D Library                                      * 
 *                                                                                             * 
 *                     $Archive:: /Commando/Code/ww3d2/hanim.cpp                              $* 
 *                                                                                             * 
 *                       Author:: Greg_h                                                       * 
 *                                                                                             * 
 *                     $Modtime:: 12/13/01 6:54p                                              $* 
 *                                                                                             * 
 *                    $Revision:: 3                                                           $* 
 *                                                                                             * 
 *---------------------------------------------------------------------------------------------* 
 * Functions:                                                                                  * 
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */


// Retail links the size-optimized WeightInfoStruct vector deleting destructor (??_E,
// the copy htree.cpp emits); it takes the optimization state of the first function
// that needs it, so this unemitted anchor needs it first. The private struct is reached
// by befriending the anchor while hanim.h is first read; layout and names are unchanged.
struct BfmeWeightInfoVddAnchor;
#define private private: friend struct BfmeWeightInfoVddAnchor; private
#include "hanim.h"
#undef private
struct BfmeWeightInfoVddAnchor { typedef NamedPivotMapClass::WeightInfoStruct Info; };
static void bfmeWeightInfoVddAnchor(BfmeWeightInfoVddAnchor::Info *p) { delete [] p; }
#pragma optimize("", on)
#include "hanim.h"
#include "assetmgr.h"
#include "htree.h"
#include "motchan.h"
#include "chunkio.h"
#include "w3d_file.h"
#include "wwdebug.h"
#include <string.h>
#include "nstrdup.h"
// bfme link decl-only begin
template <> bool VectorClass<float>::operator==(VectorClass<float> const &) const;
template <> int DynamicVectorClass<float>::ID(float const &);
template <> int VectorClass<float>::ID(float const &);
template <> int VectorClass<float>::ID(float const *);
template <> bool VectorClass<float>::Resize(int, float const *);
template <> bool VectorClass<BfmeWeightInfoVddAnchor::Info>::Resize(int, BfmeWeightInfoVddAnchor::Info const *);
// bfme link decl-only end

// Retail keeps one HAnimComboDataClass pool allocator (0x001963A0); this unit calls it.
template <> HAnimComboDataClass *ObjectPoolClass<HAnimComboDataClass, 256>::Allocate_Object_Memory(void);

// BFME1's hanim.h inserts _bfme_hanim_fade before Get_Num_Pivots, while the
// BFME2 retail calls in this TU use Get_Num_Pivots at vtable +0x34 and
// Is_Node_Motion_Present at +0x3C. HRawLoadW3D.cpp uses the same target-side
// interface view. Keep this ABI shim local; do not alter the donor header.
class BFME2HAnimClassSlots : public RefCountClass, public HashableClass
{
public:
	enum
	{
		CLASSID_UNKNOWNANIM	= 0xFFFFFFFF,
		CLASSID_HRAWANIM		= 0,
		CLASSID_LASTANIM		= 0x0000FFFF
	};

	virtual ~BFME2HAnimClassSlots(void);
	virtual const char *Get_Name(void) const = 0;
	virtual const char *Get_HName(void) const = 0;
	virtual const char *Get_Key(void) = 0;
	virtual int Get_Num_Frames(void) = 0;
	virtual float Get_Frame_Rate(void) = 0;
	virtual float Get_Total_Time(void) = 0;
	virtual void Get_Translation(int pividx, float frame) = 0;
	virtual void Get_Orientation(int pividx, float frame) = 0;
	virtual void Get_Translation(Vector3& translation, int pividx, float frame) const = 0;
	virtual bool Get_Orientation(Quaternion& orientation, int pividx, float frame) const = 0;
	virtual void Get_Transform(Matrix3D&, int pividx, float frame) const = 0;
	virtual bool Get_Visibility(int pividx, float frame) = 0;
	virtual int Get_Num_Pivots(void) const = 0;
	virtual bool Is_Node_Motion_Present(int pividx) = 0;
	virtual bool Has_X_Translation(int pividx) = 0;
	virtual bool Has_Y_Translation(int pividx) = 0;
	virtual bool Has_Z_Translation(int pividx) = 0;
	virtual bool Has_Rotation(int pividx) = 0;
	virtual bool Has_Visibility(int pividx) = 0;
	virtual int Class_ID(void) const = 0;
};



/*
**
**	HAnimComboClass
**
**
*/


// configure the base pivot map using the specified tree
void NamedPivotMapClass::Update_Pivot_Map(const HTreeClass *Tree)
{
	// first, resize the base pivot map to fit the tree
	int numPivots = Tree->Num_Pivots();

	Resize(numPivots);
	ActiveCount = numPivots;

	// first, reset all weights to 1 (the default)
	while(numPivots--) {
		(*this)[numPivots] = 1.0f;
	}

	// for each named pivot, find the correct index and set the weight if the indicated bone is present
	// note: there is no check for redundant names
	int count = WeightInfo.Count();
	while(count--) {
		int actualPivot = Tree->Get_Bone_Index(WeightInfo[count].Name);
		if(actualPivot != -1) {
			(*this)[actualPivot] = WeightInfo[count].Weight;
		} 
	}
}

/*
**
*/
DEFINE_AUTO_POOL(HAnimComboDataClass,256);


// ?HAnimComboDataClass::HAnimComboDataClass present-unmatched
HAnimComboDataClass::HAnimComboDataClass(bool shared) 
: Shared(shared), HAnim(0), PivotMap(0), Frame(0), Weight(1) 
{}


// ?HAnimComboDataClass::HAnimComboDataClass present-unmatched
HAnimComboDataClass::HAnimComboDataClass(const HAnimComboDataClass &src)
:	PivotMap(src.Get_Pivot_Map()),
	HAnim(src.Get_HAnim())
{
	Shared = src.Is_Shared();
	Frame = src.Get_Frame();
	Weight = src.Get_Weight();
}

// ?HAnimComboDataClass::Copy present-unmatched
void HAnimComboDataClass::Copy(const HAnimComboDataClass *src)
{
	if(src) {
		HAnim = src->Get_HAnim();
		PivotMap = src->Get_Pivot_Map();
		Frame = src->Get_Frame();
			Weight = src->Get_Weight();
	} else {
		HAnim = 0;
		PivotMap = 0;
		Frame = 0;
		Weight = 1;
	}
}

// ?HAnimComboDataClass::Clear present-unmatched
void HAnimComboDataClass::Clear(void) 
{
	if ( HAnim != NULL ) {
		HAnim->Release_Ref();
		HAnim = NULL;
	}

	// not sure if the pivot map should be deleted or just have everything set to one.
	// removing it effectively sets it to one, so that's what I'm doing for now.
	if(PivotMap) {
		PivotMap->Release_Ref();
		PivotMap = NULL;
	}

	Frame = 0.0f;
	Weight = 1.0;
	PivotMap = NULL;
}

inline void HAnimComboDataClass::Set_HAnim(HAnimClass *motion)
{
	if ( motion != NULL ) {
		motion->Add_Ref();
	}
	if ( HAnim != NULL ) {
		HAnim->Release_Ref();
	}
	HAnim = motion;
}


// ?HAnimComboDataClass::Set_Pivot_Map present-unmatched
void HAnimComboDataClass::Set_Pivot_Map(PivotMapClass *map)
{
	if ( map != NULL ) {
		map->Add_Ref();
	}
	if ( PivotMap != NULL ) {
		PivotMap->Release_Ref();
	}
	PivotMap = map;
}

/*
**	This function will replace the current pivot map (if any) with another pivot map that is
** set to 1 for only those pivot indices that actually have data.
*/
// ?HAnimComboDataClass::Build_Active_Pivot_Map present-unmatched
void HAnimComboDataClass::Build_Active_Pivot_Map(void) 
{
	if ( PivotMap != NULL ) {
		PivotMap->Release_Ref();
	}
	if(HAnim == NULL) {
		PivotMap = 0;
		return;
	}

	int numpivots = reinterpret_cast<BFME2HAnimClassSlots *>(HAnim)->Get_Num_Pivots();
	PivotMap = NEW_REF( PivotMapClass, ());
	PivotMap->Resize(numpivots);

	int count = 0;
	while(count < numpivots) {
		if(reinterpret_cast<BFME2HAnimClassSlots *>(HAnim)->Is_Node_Motion_Present(count)) {
			PivotMap->Add(1);

		} else {
			PivotMap->Add(0);
		}
		count++;
	}
}

/*	
**	HAnimComboClass
**
**
*/

HAnimComboClass::HAnimComboClass( int num_animations )
{
	HAnimComboData.Resize(num_animations);

	while(num_animations--) {
		HAnimComboData.Add(new HAnimComboDataClass());
	}
}


// ??1HAnimComboClass@@QAE@XZ is rowed in its own unit; this copy collided with it.


// ?HAnimComboClass::Clear present-unmatched
void	HAnimComboClass::Clear( void )
{
	int numAnimations = HAnimComboData.Count();
	while ( numAnimations-- ) {
		HAnimComboDataClass *data = HAnimComboData[numAnimations];
		if(data && (! data->Is_Shared()))
			data->Clear();
	}
}

// ?HAnimComboClass::Normalize_Weights present-unmatched
bool	HAnimComboClass::Normalize_Weights(void)
{
	// NOTE: This can only work if either no anims have pivot weight maps (in which case we will
	// adjust the anim weights to ensure normalization), or else if all do (in which case we will
	// adjust the pivot maps). Otherwise we do nothing and return false.
	int anim_count = Get_Num_Anims();
	if (!anim_count) return true;	// Trivially succeeded
	
	// Loop over all anims. Check if all or none have pivot maps, and also calculate the minimum
	// number of pivots.
	int anim_idx = 0;
	bool all_pivot_maps = true;
	bool none_pivot_maps = true;
	int num_anim_pivots = 100000;
	for (anim_idx = 0; anim_idx < anim_count; anim_idx++ ) {
		num_anim_pivots = MIN(num_anim_pivots, reinterpret_cast<BFME2HAnimClassSlots *>(Peek_Motion(anim_idx))->Get_Num_Pivots());
		bool has_pivot_map = Peek_Pivot_Weight_Map(anim_idx) != NULL;
		all_pivot_maps &= has_pivot_map;
		none_pivot_maps &= !has_pivot_map;
	}
	if ( num_anim_pivots == 100000 ) {
		num_anim_pivots = 0;
	}

	if (none_pivot_maps) {

		// Calculate total weight of all active anims, ensure it is very close to 1.
		float weight_total = 0.0f;
		for (anim_idx = 0; anim_idx < anim_count; anim_idx++ ) {
			if (Peek_Motion(anim_idx) != NULL ) {
				float	weight = Get_Weight(anim_idx);
				weight_total += weight;
			}
		}

		// weight_total should be very close to 1. If not, normalize this pivot's weights
		if (weight_total != 0.0 && WWMath::Fabs( weight_total - 1.0 ) > WWMATH_EPSILON) {
			float oo_total = 1.0f / weight_total;
			for (anim_idx = 0; anim_idx < anim_count; anim_idx++ ) {
				if (Peek_Motion(anim_idx) != NULL ) {
					Set_Weight(anim_idx, Get_Weight(anim_idx) * oo_total);
				}
			}
		}

	} else {

		if (all_pivot_maps) {

			// For each pivot, calculate total weight of all active anims, ensure close to 1.
			for (int piv_idx = 1; piv_idx < num_anim_pivots; piv_idx++) {

				float weight_total = 0.0f;
				for (anim_idx = 0; anim_idx < anim_count; anim_idx++ ) {
					if (Peek_Motion(anim_idx) != NULL ) {
						float	weight = Get_Weight(anim_idx) * (*Peek_Pivot_Weight_Map(anim_idx))[piv_idx];
						weight_total += weight;
					}
				}

				// weight_total should be very close to 1. If not, normalize this pivot's weights
				if (weight_total != 0.0 && WWMath::Fabs( weight_total - 1.0 ) > WWMATH_EPSILON) {
					float oo_total = 1.0f / weight_total;
					for (anim_idx = 0; anim_idx < anim_count; anim_idx++ ) {
						if (Peek_Motion(anim_idx) != NULL ) {
							PivotMapClass *pivot_map = HAnimComboData[anim_idx]->Get_Pivot_Map();
							float new_weight = (*pivot_map)[piv_idx] * oo_total;
							(*pivot_map)[piv_idx] = new_weight;
							pivot_map->Release_Ref();
						}
					}
				}

			}

		} else {
			return false;
		}
	}

	return true;

}

void	HAnimComboClass::Set_Motion( int index, HAnimClass *motion )
{
	HAnimComboDataClass *data = HAnimComboData[index];
	WWASSERT(data);

	data->Set_HAnim(motion);
}

// ?HAnimComboClass::Peek_Motion present-unmatched
inline HAnimClass *HAnimComboClass::Peek_Motion( int index )
{
	HAnimComboDataClass *data = HAnimComboData[index];
	WWASSERT(data);

	HAnimClass *anim = data->Peek_HAnim();
	return anim;
}

// ?HAnimComboClass::Set_Weight present-unmatched
inline void	HAnimComboClass::Set_Weight( int index, float weight )
{
	HAnimComboDataClass *data = HAnimComboData[index];
	WWASSERT(data);

	data->Set_Weight(weight);
}

// ?HAnimComboClass::Get_Weight present-unmatched
inline float	HAnimComboClass::Get_Weight( int index )
{
	HAnimComboDataClass *data = HAnimComboData[index];
	WWASSERT(data);

	return data->Get_Weight();
}

// ?HAnimComboClass::Set_Pivot_Weight_Map present-unmatched
void	HAnimComboClass::Set_Pivot_Weight_Map( int index, PivotMapClass *map )
{
	HAnimComboDataClass *data = HAnimComboData[index];
	WWASSERT(data);

	data->Set_Pivot_Map(map);
}

// Get_Pivot_Weight_Map is owned by HAnimComboClassGetMotion.cpp at 0x00196740.
// Normalize_Weights inlines the data accessor; do not emit a competing copy.

// ?HAnimComboClass::Peek_Pivot_Weight_Map present-unmatched
inline PivotMapClass	*HAnimComboClass::Peek_Pivot_Weight_Map( int index )
{
	HAnimComboDataClass *data = HAnimComboData[index];
	WWASSERT(data);

	return data->Peek_Pivot_Map();
}

void HAnimComboClass::Append_Anim_Combo_Data(HAnimComboDataClass * Data)
{
	HAnimComboData.Add(Data);
}

void HAnimComboClass::Remove_Anim_Combo_Data(HAnimComboDataClass * Data)
{
	HAnimComboData.Delete(Data);
}

template int VectorClass<BfmeWeightInfoVddAnchor::Info>::ID(BfmeWeightInfoVddAnchor::Info const &);
template bool VectorClass<BfmeWeightInfoVddAnchor::Info>::operator==(VectorClass<BfmeWeightInfoVddAnchor::Info> const &) const;
