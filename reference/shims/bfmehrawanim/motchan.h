// Header shim: BFME2's MotionChannelClass has no CompressedData member and no
// Do_Data_Compression, matching BFME1's motchan.h. Retail Get_Orientation at
// 0x0018DD60 reads the channel Data pointer at +0x14 with FirstFrame/LastFrame
// at +0x18/+0x1C (mov ecx,[eax+0x14]; mov ecx,[eax+0x18] bounds), while Zero
// Hour's header compiles to +0x18/+0x1c/+0x20 because of the extra
// `unsigned short *CompressedData` dword. HRawAnimClass::read_channel
// allocates eight dwords (push 0x20), which is exactly PivotIdx, Type,
// VectorLen, ValueOffset, ValueScale, Data, FirstFrame and LastFrame with
// nothing left over. The W3DMPO base itself is empty so nothing moves; only
// the pooling glue (plain operator delete in ~NodeMotionStruct) and the two
// compression members go.
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

/* $Header: /Commando/Code/ww3d2/motchan.h 5     11/29/01 1:07p Jani_p $ */
/***********************************************************************************************
 ***                            Confidential - Westwood Studios                              ***
 ***********************************************************************************************
 *                                                                                             *
 *                 Project Name : Commando / G 3D Library                                      *
 *                                                                                             *
 *                     $Archive:: /Commando/Code/ww3d2/motchan.h                              $*
 *                                                                                             *
 *                      $Author:: Jani_p                                                      $*
 *                                                                                             *
 *                     $Modtime:: 11/28/01 5:43p                                              $*
 *                                                                                             *
 *                    $Revision:: 5                                                           $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */


#if defined(_MSC_VER)
#pragma once
#endif

#ifndef MOTCHAN_H
#define MOTCHAN_H

#include "always.h"
#include "bittype.h"
#include "w3d_file.h"
#include "quat.h"

class ChunkLoadClass;
class Quaternion;

/******************************************************************************

	MotionChannelClass is used to store motion.  Motion data
	is broken into separate channels for X, Y, Z, and orientation.
	Then if any of the channels are empty, they don't have to be stored.
	The X,Y,Z channels all contain one-dimensional vectors and the
	orientation channel contains four-dimensional vectors (quaternions).

******************************************************************************/

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/motchan.h
class MotionChannelClass : public W3DMPO
{
	// BFME does not pool these: ~NodeMotionStruct deletes every channel
	// through plain operator delete, where the glue would route through
	// getClassMemoryPool. W3DMPO itself is empty, so the base stays and
	// nothing moves.

public:
	void Get_Vector(int frame,float * setvec) const;

	MotionChannelClass(void);
	~MotionChannelClass(void);

	bool	Load_W3D(ChunkLoadClass & cload);
	WWINLINE int Get_Type(void) const { return Type; }
	WWINLINE int Get_Pivot(void) const { return PivotIdx; }
	WWINLINE void Set_Pivot(int idx) { PivotIdx=idx; }

#define SPECIAL_GETVEC_AS_QUAT
#ifdef SPECIAL_GETVEC_AS_QUAT
	WWINLINE void Get_Vector_As_Quat(int frame, Quaternion& quat) const;
#endif

private:

	uint32	PivotIdx;			// what pivot is this channel applied to
	uint32	Type;					// what type of channel is this
	int		VectorLen;			// size of each individual vector

	float		ValueOffset;
	float		ValueScale;

	float	*	Data;					// pointer to the raw floating point data
	int		FirstFrame;			// first frame which was non-identity
	int		LastFrame;			// last frame which was non-identity
	void Free(void);
	WWINLINE void set_identity(float * setvec) const;

//	friend class HRawAnimClass;

};

WWINLINE void MotionChannelClass::set_identity(float * setvec) const
{
	// BFME: the fade channel (type 15, BFME1 ANIM_CHANNEL_FADE) rests at 1.0;
	// retail tests it ahead of the quaternion arm (0x0018DFEC, 0x0018D647).
	if (Type == 15) {

		setvec[0] = 1.0f;

	} else {

		setvec[0] = 0.0f;
		if (Type == ANIM_CHANNEL_Q) {
			setvec[1] = 0.0f;
			setvec[2] = 0.0f;
			setvec[3] = 1.0f;
		}

	}
}

WWINLINE void	MotionChannelClass::Get_Vector(int frame,float * setvec) const
{
	if ((frame < FirstFrame) || (frame > LastFrame)) {

		set_identity(setvec);

	} else {

		int vframe = frame - FirstFrame;

		for (int i=0; i<VectorLen; i++) {
			setvec[i] = Data[vframe * VectorLen + i];
		}
	}
}

#ifdef SPECIAL_GETVEC_AS_QUAT
WWINLINE void MotionChannelClass::Get_Vector_As_Quat(int frame, Quaternion& quat) const
{
	if ((frame < FirstFrame) || (frame > LastFrame)) {

		quat.Set(0.0f, 0.0f, 0.0f, 1.0f);

	} else {

		const float* d = &Data[(frame - FirstFrame) * VectorLen];
		quat.Set(d[0], d[1], d[2], d[3]);

	}
}
#endif


/******************************************************************************

	BitChannelClass is used to store a boolean "on/off" value for each frame
	in an animation.

******************************************************************************/

class BitChannelClass : public W3DMPO
{
	W3DMPO_GLUE(BitChannelClass)

public:

	BitChannelClass(void);
	~BitChannelClass(void);

	bool	Load_W3D(ChunkLoadClass & cload);
	WWINLINE int	Get_Type(void) const { return Type; }
	WWINLINE int	Get_Pivot(void) const { return PivotIdx; }
	WWINLINE int	Get_Bit(int frame) const;

private:

	uint32	PivotIdx;
	uint32	Type;
	int		DefaultVal;
	int		FirstFrame;
	int		LastFrame;

	uint8 *	Bits;

	void Free(void);

	friend class HRawAnimClass;
};


WWINLINE int BitChannelClass::Get_Bit(int frame) const
{
	if ((frame < FirstFrame) || (frame > LastFrame)) {

		return DefaultVal;

	} else {

		int bit = frame - FirstFrame;

		uint8 mask = (uint8)(1 << (bit % 8));
		return ((*(Bits + (bit/8)) & mask) != 0);

	}
}

/******************************************************************************

	TimeCodedMotionChannelClass is used to store motion.  Motion data
	is broken into separate channels for X, Y, Z, and orientation.
	Then if any of the channels are empty, they don't have to be stored.
	The X,Y,Z channels all contain one-dimensional vectors and the
	orientation channel contains four-dimensional vectors (quaternions).

******************************************************************************/

class TimeCodedMotionChannelClass : public W3DMPO
{
	W3DMPO_GLUE(TimeCodedMotionChannelClass)

public:

	TimeCodedMotionChannelClass(void);
	~TimeCodedMotionChannelClass(void);

	bool	Load_W3D(ChunkLoadClass & cload);
	int	Get_Type(void) { return Type; }
	int	Get_Pivot(void) { return PivotIdx; }
	void	Get_Vector(float32 frame, float * setvec);

	Quaternion Get_QuatVector(float32 frame);

private:

	uint32	PivotIdx;			// what pivot is this channel applied to
	uint32	Type;					// what type of channel is this
	int		VectorLen;			// size of each individual vector
	uint32	PacketSize;			// size of each packet

	uint32	NumTimeCodes;		// Number of packets

	uint32	LastTimeCodeIdx;	// absolute index to last time code
	uint32	CachedIdx;			// Last Index Used

	uint32	*	Data;			 	// pointer to packet data

	void 		Free(void);
	void 		set_identity(float * setvec);
	uint32	get_index(uint32 timecode);
	uint32	binary_search_index(uint32 timecode);

	friend class HCompressedAnimClass;
};

class AdaptiveDeltaMotionChannelClass : public W3DMPO
{
	W3DMPO_GLUE(AdaptiveDeltaMotionChannelClass)

public:

	AdaptiveDeltaMotionChannelClass(void);
	~AdaptiveDeltaMotionChannelClass(void);

	bool	Load_W3D(ChunkLoadClass & cload);
	int	Get_Type(void) { return Type; }
	int	Get_Pivot(void) { return PivotIdx; }
	void	Get_Vector(float32 frame, float * setvec);

	Quaternion Get_QuatVector(float32 frame);

private:

	uint32	PivotIdx;			// what pivot is this channel applied to
	uint32	Type;					// what type of channel is this
	int		VectorLen;			// size of each individual vector

	uint32	NumFrames;			// Number of frames

	float		Scale;				// Scale Filter, this much

	uint32  *Data;				 	// pointer to packet data

	uint32	CacheFrame;
	float	  *CacheData;			// the data for CachedFrame, and CachedFrame+1, x VectorLen

	void 		Free(void);

	float		getframe(uint32 frame_idx, uint32 vector_idx=0);
   void		decompress(uint32 frame_idx, float *outdata);
   void		decompress(uint32 src_idx, float *srcdata, uint32 frame_idx, float *outdata);

	friend class HCompressedAnimClass;
};



/******************************************************************************

	TimeCodedBitChannelClass is used to store a boolean "on/off" value for each frame
	in an animation.

******************************************************************************/

class TimeCodedBitChannelClass : public W3DMPO
{
	W3DMPO_GLUE(TimeCodedBitChannelClass)

public:

	TimeCodedBitChannelClass(void);
	~TimeCodedBitChannelClass(void);

	bool	Load_W3D(ChunkLoadClass & cload);
	int	Get_Type(void) { return Type; }
	int	Get_Pivot(void) { return PivotIdx; }
	int	Get_Bit(int frame);

private:

	uint32	PivotIdx;
	uint32	Type;
	int		DefaultVal;

	uint32	NumTimeCodes;
	uint32	CachedIdx;

	uint32	*Bits;

	void Free(void);

	friend class HCompressedAnimClass;
};


#endif
