// cl: /Ireference/shims/bfmerendobj /arch:SSE /G7 /DNDEBUG /MD /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression
// The compiler-generated vector constructor iterator (??_H) takes the
// optimization state of the first function that needs it. Retail links one
// copy, the /O1 body at 0x00001423; this unemitted anchor makes this unit's
// copy that same body, so it no longer loses to retail's at link time.
// It can also change how later array constructions here compile; checked to
// change nothing else in this unit, but if a function added later that builds
// an array will not match, try it without this block.
struct BfmeVciAnchorElem { BfmeVciAnchorElem(); };
#pragma optimize("gsy", on)
// Match HashableClass's retail base and deleting destructors, as in hcanim.cpp.
// Its first emitted copy must use the native size-optimized header bodies.
#include "hash.h"
static void bfmeVciAnchor() { BfmeVciAnchorElem anchor[2]; (void)anchor; }
// HashableClass's inline members and deleting destructor are retail's size-optimised bodies
// (0x000EF9C2 ctor, 0x000EF9D6 ??_G): include its header here under the same state hcanim.cpp
// uses, ahead of any header that would reach it unoptimised.
#include "hash.h"
#define Matrix4x4 Matrix4
// Retail treats array delete as nothrow: ~NamedPivotMapClass (0x001976F0) has
// no EH state store between its WeightInfo teardown and the PivotMapClass
// base's, which the compiler drops only when delete[] cannot throw.
#define __PLACEMENT_VEC_NEW_INLINE // always.h supplies array placement new/delete.
#include <new>

// RefCountClass's inline members and deleting destructor are retail's
// size-optimised bodies: compile them for size, as hlod.cpp does.
#pragma optimize("s", on)
#include "../../../../../reference/shims/bfmepool/mempool.h"
#include "refcount.h"
// Match the native Hashable deleting destructor, as hcanim.cpp does.
#include "hash.h"
#include "rendobj.h"	// the bfmerendobj shim has to win the include guard
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
#pragma optimize("gsy", on)
static void bfmeWeightInfoVddAnchor(BfmeWeightInfoVddAnchor::Info *p) { delete [] p; }
#pragma optimize("", on)
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
template <> bool VectorClass<HAnimComboDataClass *>::operator==(VectorClass<HAnimComboDataClass *> const &) const;
template <> bool DynamicVectorClass<HAnimComboDataClass *>::Delete(int);
template <> int DynamicVectorClass<float>::ID(float const &);
template <> int VectorClass<float>::ID(float const &);
template <> int VectorClass<float>::ID(float const *);
template <> bool VectorClass<float>::Resize(int, float const *);
template <> bool DynamicVectorClass<BfmeWeightInfoVddAnchor::Info>::Add(BfmeWeightInfoVddAnchor::Info const &);
template <> bool VectorClass<BfmeWeightInfoVddAnchor::Info>::Resize(int, BfmeWeightInfoVddAnchor::Info const *);
// bfme link decl-only end



/*
**
**	HAnimComboClass
**
**
*/


NamedPivotMapClass::~NamedPivotMapClass(void)
{
}

// Inline: the retail copy (0x00196170) is the select-any one hanim_weight_vector_add.cpp
// emits with the Add it inlines into.
inline NamedPivotMapClass::WeightInfoStruct & NamedPivotMapClass::WeightInfoStruct::operator = (WeightInfoStruct const &that)
{	
	if(Name) delete [] Name;
	assert(that.Name != 0);
	Name = nstrdup(that.Name); 
	Weight = that.Weight; 
	return *this; 
}

// add a name & weight to the arrays
void NamedPivotMapClass::Add(const char *Name, float Weight)
{
	WeightInfoStruct info;
	info.Name = (char *) Name;
	info.Weight = Weight;
	WeightInfo.Add(info);	
	info.Name = 0;
}

// configure the base pivot map using the specified tree
// ?Update_Pivot_Map@NamedPivotMapClass@@QAEXPBVHTreeClass@@@Z is rowed in its own unit; this copy collided with it.

/*
**
*/
DEFINE_AUTO_POOL(HAnimComboDataClass,256);

// ??1HAnimClass@@UAE@XZ
HAnimClass::~HAnimClass(void)
{
}


// Definition moved to hanim_HAnimComboClass_ctor.cpp: the /G7 split TU needs
// the body visible to inline it into HAnimComboClass::HAnimComboClass(int).


// ??0HAnimComboDataClass@@QAE@ABV0@@Z is rowed in its own unit; this copy collided with it.


// ??1HAnimComboDataClass@@QAE@XZ is rowed in its own unit; this copy collided with it.


// HAnimComboDataClass::Set_HAnim (0x001007B0) is a size-optimised body from
// the /O1 region (inc/dec refcounts); this /G7 /O2 unit only calls it. It is
// built in HAnimComboDataSetHAnim.cpp.



/*	
**	HAnimComboClass
**
**
*/

HAnimComboClass::HAnimComboClass(void)
{}

// Body split to hanim_HAnimComboClass_ctor.cpp. See hanim_weight_vector_add.cpp.


// ??1HAnimComboClass@@QAE@XZ is rowed in its own unit; this copy collided with it.





// Get_Motion is defined in HAnimComboClassGetMotion.cpp.

__declspec(noinline) inline HAnimClass *HAnimComboClass::Peek_Motion( int index )
{
	HAnimComboDataClass *data = HAnimComboData[index];
	WWASSERT(data);

	HAnimClass *anim = data->Peek_HAnim();
	return anim;
}

void	HAnimComboClass::Set_Frame( int index, float frame )
{
	HAnimComboDataClass *data = HAnimComboData[index];
	WWASSERT(data);

	data->Set_Frame(frame);
}

float	HAnimComboClass::Get_Frame( int index )
{
	HAnimComboDataClass *data = HAnimComboData[index];
	WWASSERT(data);

	return data->Get_Frame();
}

__declspec(noinline) inline void	HAnimComboClass::Set_Weight( int index, float weight )
{
	HAnimComboDataClass *data = HAnimComboData[index];
	WWASSERT(data);

	data->Set_Weight(weight);
}

__declspec(noinline) inline float	HAnimComboClass::Get_Weight( int index )
{
	HAnimComboDataClass *data = HAnimComboData[index];
	WWASSERT(data);

	return data->Get_Weight();
}


// Get_Pivot_Weight_Map has the same /G7 provider as Get_Motion.

__declspec(noinline) inline PivotMapClass	*HAnimComboClass::Peek_Pivot_Weight_Map( int index )
{
	HAnimComboDataClass *data = HAnimComboData[index];
	WWASSERT(data);

	return data->Peek_Pivot_Map();
}

// ?Append_Anim_Combo_Data@HAnimComboClass@@QAEXPAVHAnimComboDataClass@@@Z is rowed in its own unit; this copy collided with it.

// ?Remove_Anim_Combo_Data@HAnimComboClass@@QAEXPAVHAnimComboDataClass@@@Z is rowed in its own unit; this copy collided with it.


// ?bfmeAnchorHAnimComboAccessors absent-from-retail
void bfmeAnchorHAnimComboAccessors(HAnimComboClass *combo, int index, float weight)
{
	combo->Peek_Motion(index);
	combo->Set_Weight(index, weight);
	combo->Get_Weight(index);
	combo->Peek_Pivot_Weight_Map(index);
}

// ?bfmeAnchorHAnimPivotMap absent-from-retail
PivotMapClass *bfmeAnchorHAnimPivotMap()
{
	return new PivotMapClass();
}
