// Header shim: BFME2's raw-animation node carries a ninth motion channel
// (per-pivot fade) ahead of Vis, where Zero Hour's NodeMotionStruct holds
// eight pointers. Retail Get_Orientation at 0x0018DD60 indexes the array
// with a stride of 36 bytes (lea eax,[eax+eax*8]; mov eax,[ecx+eax*4+0x18])
// while the Zero Hour header compiles to 32 (shl eax,5), and BFME1's
// hrawanim.h documents the same ninth channel (Fade ahead of Vis, value 15
// ANIM_CHANNEL_FADE). The quaternion-blend helper selection is unchanged
// here; Get_Orientation keeps Zero Hour's void signature because retail's
// decorated name (?Get_Orientation@HRawAnimClass@@UBEXAAVQuaternion@@HM@Z)
// returns void, unlike BFME1's bool revision.
// Scoped by -Ireference/shims/bfmehrawanim on the unit's `// cl:` line.
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

#if defined(_MSC_VER)
#pragma once
#endif

#ifndef HRAWANIM_H
#define HRAWANIM_H

#include "always.h"
#include "hanim.h"

class MotionChannelClass;
class BitChannelClass;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/hrawanim.h
struct NodeMotionStruct
{
	NodeMotionStruct();
	~NodeMotionStruct();

	MotionChannelClass *		X;
	MotionChannelClass *		Y;
	MotionChannelClass *		Z;
	MotionChannelClass *		XR;
	MotionChannelClass *		YR;
	MotionChannelClass *		ZR;
	MotionChannelClass *		Q;

	// BFME addition: ninth channel carrying a per-pivot fade. Declared ahead
	// of Vis (not appended) so Q stays at +0x18 and Vis moves to +0x20, which
	// is what the retail stride of 36 bytes requires. Matches BFME1's Fade.
	MotionChannelClass *		Fade;

	BitChannelClass *			Vis;
};

/**********************************************************************************

	HRawAnimClass

	Stores motion data to be applied to a HierarchyTree.  Each frame
	of the motion contains deltas from the HierarchyTree's base position
	to the desired position.

**********************************************************************************/

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/hrawanim.h
class HRawAnimClass : public HAnimClass
{

public:

	enum
	{
		OK,
		LOAD_ERROR
	};

	HRawAnimClass(void);
	~HRawAnimClass(void);

	int							Load_W3D(ChunkLoadClass & cload);

	const char *				Get_Name(void) const { return Name; }
	const char *				Get_HName(void) const { return HierarchyName; }
	int							Get_Num_Frames(void) { return NumFrames; }
	float							Get_Frame_Rate() { return FrameRate; }
	float							Get_Total_Time() { return (float)NumFrames / FrameRate; }

//	Vector3						Get_Translation(int pividx,float frame);
//	Quaternion					Get_Orientation(int pividx,float frame);
	void							Get_Translation(Vector3& translation, int pividx,float frame) const;
	// BFME returns success here where Zero Hour is void (retail 0x0018DD60
	// sets al=1 on every return path); same revision as BFME1's bool form.
	bool							Get_Orientation(Quaternion& orientation, int pividx,float frame) const;
	void							Get_Transform(Matrix3D& transform, int pividx,float frame) const;
	bool							Get_Visibility(int pividx,float frame);
	// BFME: per-pivot fade blend, vtable slot 11 after Get_Visibility (retail
	// 0x0018D540); BFME1's hrawanim.h declares the same virtual.
	virtual float				_bfme_hanim_fade(int pividx,float frame);

	bool							Is_Node_Motion_Present(int pividx);
	int							Get_Num_Pivots(void) const { return NumNodes; }

	// Methods that test the presence of a certain motion channel.
	bool							Has_X_Translation (int pividx);
	bool							Has_Y_Translation (int pividx);
	bool							Has_Z_Translation (int pividx);
	bool							Has_Rotation (int pividx);
	bool							Has_Visibility (int pividx);
	NodeMotionStruct				*Get_Node_Motion_Array(void) {return NodeMotion;}
	virtual int					Class_ID(void)	const															{ return CLASSID_HRAWANIM; }

private:

	char							Name[2*W3D_NAME_LEN];
	char							HierarchyName[W3D_NAME_LEN];

	int							NumFrames;
	int							NumNodes;
	float							FrameRate;

	NodeMotionStruct *		NodeMotion;

	void Free(void);
	bool read_channel(ChunkLoadClass & cload,MotionChannelClass * * newchan,bool pre30);
	void add_channel(MotionChannelClass * newchan);

	bool read_bit_channel(ChunkLoadClass & cload,BitChannelClass * * newchan,bool pre30);
	void add_bit_channel(BitChannelClass * newchan);

};

#endif
