// BFME 2 HAnim interface, scoped explicitly to hcanim.cpp.
// Target: primary table 007D5CB8 has 23 slots; key slot 3, fade slot 12,
// six presence predicates at 15-20, Class_ID at 21 and memory query at 22.
// The obsolete value-returning translation/orientation overloads are absent.
// Existing constructor, destructor and inline constant bodies are retained.
// Other animation units retain their existing headers pending shared adoption.
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

/* $Header: /Commando/Code/ww3d2/hanim.h 3     12/13/01 7:01p Patrick $ */
/*********************************************************************************************** 
 ***                            Confidential - Westwood Studios                              *** 
 *********************************************************************************************** 
 *                                                                                             * 
 *                 Project Name : Commando / G 3D Library                                      * 
 *                                                                                             * 
 *                     $Archive:: /Commando/Code/ww3d2/hanim.h                                $* 
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


#if defined(_MSC_VER)
#pragma once
#endif

#ifndef HANIM_H
#define HANIM_H

#include "always.h"
#include "quat.h"
#include "refcount.h"
#include "w3d_file.h"
#include "hash.h"
#include "mempool.h"
#include "refcount.h"
#include "slist.h"
#include "vector.h"

struct NodeMotionStruct;
class MotionChannelClass;
class BitChannelClass;
class HTreeClass;
class ChunkLoadClass;
class ChunkSaveClass;
class HTreeClass;



#define EMBEDDED_SOUND_BONE_INDEX_NOT_SET -1
/**********************************************************************************

	HAnimClass

	This is the base class for all animation formats used in W3D.  It
	contains the virtual interface that all animations must support.
	
**********************************************************************************/
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/hanim.h
// BFME 2 target: 23 primary slots at 007D5CB8. No extra data.
class HAnimClass : public RefCountClass, public HashableClass
{
public:
    enum { CLASSID_UNKNOWNANIM=0xFFFFFFFF, CLASSID_HRAWANIM=0, CLASSID_LASTANIM=0xFFFF };
    HAnimClass() {}
    virtual ~HAnimClass();
    virtual const char *Get_Name() const = 0; // 2
    virtual unsigned int _bfme_hanim_v3() const = 0;
    virtual const char *Get_HName() const = 0; // 4
    virtual const char *Get_Key() { return Get_Name(); } // Hashable interface
    virtual int Get_Num_Frames() = 0;
    virtual float Get_Frame_Rate() = 0;
    virtual float Get_Total_Time() = 0;
    virtual void Get_Translation(Vector3 &,int,float) const = 0;
    virtual bool Get_Orientation(Quaternion &,int,float) const = 0;
    virtual void Get_Transform(Matrix3D &,int,float) const = 0;
    virtual bool Get_Visibility(int,float) = 0;
    virtual float _bfme_hanim_fade(int,float) = 0; // 12
    virtual int Get_Num_Pivots() const = 0;
    virtual bool Is_Node_Motion_Present(int) = 0;
    virtual bool Has_X_Translation(int) { return true; }
    virtual bool Has_Y_Translation(int) { return true; }
    virtual bool Has_Z_Translation(int) { return true; }
    virtual bool Has_Rotation(int) { return true; }
    virtual bool Has_Visibility(int) { return true; }
    virtual bool _bfme_hanim_v21(int) { return true; } // native slot 20
    virtual int Class_ID() const { return CLASSID_UNKNOWNANIM; }
    virtual int rva0018FB70() = 0; // native slot 22; name/shape from derived row
};


/*
** The PivotMapClass is used by the HAnimComboDataClass (sometimes) to keep track of animation
** weights per-pivot point.
*/
class NamedPivotMapClass;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/hanim.h
class PivotMapClass : public DynamicVectorClass<float>, public RefCountClass
{
public:
	virtual NamedPivotMapClass * As_Named_Pivot_Map() { return 0; }
};


/*
**	The NamedPivotMapClass allows us to create HAnimComboDataClass objects with pivot maps without
**	having to have the HAnim available. Later, when an HAnim is retrieved from the asset manager,
** the pivot map can be updated to produce the correct map.
*/
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/hanim.h
class NamedPivotMapClass : public PivotMapClass
{
public:
	~NamedPivotMapClass(void);

	virtual NamedPivotMapClass * As_Named_Pivot_Map() { return this; }

	// add a name & weight to the arrays
	void Add(const char *Name, float Weight);

	// configure the base pivot map using the specified tree
	void Update_Pivot_Map(const HTreeClass *Tree);

private:

	// This info is packaged into a struct to minimize DynamicVectorClass overhead
	// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/hanim.h
	struct WeightInfoStruct {
		WeightInfoStruct() : Name(0) {}
		~WeightInfoStruct() { if(Name) delete [] Name; } 

		char *Name;
		float Weight;

		// operators required for the DynamicVectorClass
		WeightInfoStruct & operator = (WeightInfoStruct const &that);
		bool operator == (WeightInfoStruct const &that) const { return &that == this; }
		bool operator != (WeightInfoStruct const &that) const { return &that != this; }
	};

	DynamicVectorClass<WeightInfoStruct>	WeightInfo;
};


/*
**	The HAnimComboDataClass is used by the new HAnimComboClass to allow for a mix of shared/unshared data
**	which will allow us to have the anim combo refer to data whereever we wish to put it.
*/
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/hanim.h
class HAnimComboDataClass : public AutoPoolClass<HAnimComboDataClass,256> {
	public:
		HAnimComboDataClass(bool shared = false);
		HAnimComboDataClass(const HAnimComboDataClass &);
		~HAnimComboDataClass(void);

		void Copy(const HAnimComboDataClass *);

		void Clear(void);
		void Set_HAnim(HAnimClass *motion);
		void Give_HAnim(HAnimClass *motion) { if(HAnim) HAnim->Release_Ref(); HAnim = motion; }	// used for giving this object the reference

		// BFME's HAnimComboDataClass has no PrevFrame: retail exposes exactly two
		// float accessors on it, [ecx+4] and [ecx+8], and both Get_ and
		// Peek_Pivot_Weight_Map read [ecx+0xc], which leaves no room for a third.
		void Set_Frame(float frame)		{ Frame = frame; }		
		void Set_Weight(float weight)		{ Weight = weight; }
		void Set_Pivot_Map(PivotMapClass *map);
		

		HAnimClass * Peek_HAnim(void)				const { return HAnim; }	// note: does not add reference
		HAnimClass * Get_HAnim(void)				const { if(HAnim) HAnim->Add_Ref(); return HAnim; }	// note: does not add reference
		float Get_Frame(void)						const { return Frame; }
		float Get_Weight(void)						const { return Weight; }
		PivotMapClass * Peek_Pivot_Map(void)	const { return PivotMap; }
		PivotMapClass * Get_Pivot_Map(void)		const { if(PivotMap) PivotMap->Add_Ref(); return PivotMap; }
		bool Is_Shared(void)							const { return Shared; }

		void Build_Active_Pivot_Map(void);

	private:

		HAnimClass *HAnim;
		float Frame;
		float Weight;
		PivotMapClass * PivotMap;
		bool Shared;			// this is set to false when the HAnimCombo allocates it
};

/*
** defines a combination of animations for blending/mixing
*/
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/hanim.h
class HAnimComboClass {

public:

	HAnimComboClass(void);
	HAnimComboClass( int num_animations ); // allocates specified number of channels and sets then all to not-shared
	~HAnimComboClass(void);

	void	Clear( void );		// zeros all data

	void	Reset( void );		// empties the dynamic vector

 	bool	Normalize_Weights(void);	// Normalizes all weights (returns true if succeeded)
	int	Get_Num_Anims( void ) { return HAnimComboData.Count(); }

	void	Set_Motion( int indx, HAnimClass *motion );
	HAnimClass *Get_Motion( int indx );
	HAnimClass *Peek_Motion( int indx );

	void	Set_Frame( int indx, float frame );
	float	Get_Frame( int indx );

	void	Set_Weight( int indx, float weight );
	float	Get_Weight( int indx );

	void	Set_Pivot_Weight_Map( int indx, PivotMapClass * map );
	PivotMapClass	* Get_Pivot_Weight_Map( int indx );
	PivotMapClass	* Peek_Pivot_Weight_Map( int indx );


	// add an entry to the dynamic vector 
	void Append_Anim_Combo_Data(HAnimComboDataClass * AnimComboData);

	// remove an entry from the vector
	void Remove_Anim_Combo_Data(HAnimComboDataClass * AnimComboData);
	
	// retrieve a specific combo data
	HAnimComboDataClass * Peek_Anim_Combo_Data(int index) { return HAnimComboData[index]; }

protected:

	DynamicVectorClass<HAnimComboDataClass *> HAnimComboData;

};

#endif 
