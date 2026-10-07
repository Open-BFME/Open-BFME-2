// cl: /Ireference/shims/bfmerendobj /Ireference/shims/bfmehcanim /Ob2 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
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
#define Matrix4x4 Matrix4
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

/* $Header: /Commando/Code/ww3d2/hcanim.cpp 3     6/29/01 6:41p Jani_p $ */
/*********************************************************************************************** 
 ***                            Confidential - Westwood Studios                              *** 
 *********************************************************************************************** 
 *                                                                                             * 
 *                 Project Name : Commando / G 3D Library                                      * 
 *                                                                                             * 
 *                     $Archive:: /Commando/Code/ww3d2/hcanim.cpp                             $* 
 *                                                                                             * 
 *                       Author:: Greg_h                                                       * 
 *                                                                                             * 
 *                     $Modtime:: 6/27/01 7:50p                                               $* 
 *                                                                                             * 
 *                    $Revision:: 3                                                           $* 
 *                                                                                             * 
 *---------------------------------------------------------------------------------------------* 
 * Functions:                                                                                  * 
 *   NodeMotionStruct::NodeMotionStruct -- constructor                                         *
 *   NodeMotionStruct::~NodeMotionStruct -- destructor                                         *
 *   HCompressedAnimClass::HCompressedAnimClass -- constructor                                 * 
 *   HCompressedAnimClass::~HCompressedAnimClass -- Destructor                                 * 
 *   HCompressedAnimClass::Free -- De-allocates all memory in use                              * 
 *   HCompressedAnimClass::Load -- Loads hierarchy animation from a file                       * 
 *   HCompressedAnimClass::read_channel -- Reads in a single channel of motion                 * 
 *   HCompressedAnimClass::add_channel -- Adds a motion channel to the animation               * 
 *   HCompressedAnimClass::Get_Translation -- returns the translation vector for the given fram* 
 *   HCompressedAnimClass::Get_Orientation -- returns a quaternion for the orientation of the p* 
 *   HCompressedAnimClass::read_bit_channel -- read a bit channel from the file                *
 *   HCompressedAnimClass::add_bit_channel -- install a bit channel into the animation         *
 *   HCompressedAnimClass::Get_Visibility -- return visibility state for given pivot/frame     *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */


#include "hcanim.h"
#include "assetmgr.h"

// BFME reaches the hierarchy through a free function, as HRawAnimClass::Load_W3D
// does -- cdecl, one argument, caller cleans -- rather than through the asset
// manager singleton. The body lives in another translation unit.
HTreeClass *Get_HTree(const char *name);

// The compressed-animation constructor and loader both ask the retail name
// key singleton to assign a key to the fully-qualified animation name.  The
// complete NameKeyGenerator header is intentionally not pulled into this
// WW3D2 unit: this small declaration preserves the proven ABI and keeps the
// animation include boundary local.
enum NameKeyType
{
	NAMEKEY_INVALID = 0,
	FORCE_NAMEKEYTYPE_LONG = 0x7fffffff
};
class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};
extern NameKeyGenerator *TheNameKeyGenerator;

#include "htree.h"
// BFME2's TimeCodedMotionChannelClass is stateless: the search cache moved out
// to the caller, which passes it by reference (retail 0x0018EC60 reads and
// writes it through its second argument), and +0x14 is the last packet index
// that the binary search falls back to. motchan.h still describes BFME1's
// cached class, so it is renamed out of the way and redeclared below. The
// adaptive-delta channel lost its cache the same way.
#define TimeCodedMotionChannelClass BfmeOneTimeCodedMotionChannelClass
#define AdaptiveDeltaMotionChannelClass BfmeOneAdaptiveDeltaMotionChannelClass
#include "motchan.h"
#undef AdaptiveDeltaMotionChannelClass
#undef TimeCodedMotionChannelClass
#include "chunkio.h"
#include "w3d_file.h"
#include "wwdebug.h"
#include <string.h>
#include "nstrdup.h"


// The normalized quaternion lerp at 0x00717550 (ledger
// ?BFME2_Nlerp@@YAXAAVQuaternion@@ABV1@1M@Z) that BFME2 blends with where Zero
// Hour calls Fast_Slerp.
void BFME2_Nlerp(Quaternion &result, const Quaternion &p, const Quaternion &q, float alpha);

class TimeCodedMotionChannelClass : public W3DMPO
{
public:

	TimeCodedMotionChannelClass(void);
	~TimeCodedMotionChannelClass(void);

	bool	Load_W3D(ChunkLoadClass & cload);
	int	Get_Type(void) { return Type; }
	int	Get_Pivot(void) { return PivotIdx; }
	void	Get_Vector(float32 frame, float * setvec);
	Quaternion Get_QuatVector(float32 frame);
	void	Get_Vector(float32 frame, float * setvec, uint32 & cachedIdx);
	void	Get_QuatVector(float32 frame, Quaternion & q, uint32 & cachedIdx);

	int		Get_Channel_Memory_Usage(void);

private:

	uint32	PivotIdx;			// what pivot is this channel applied to
	uint32	Type;					// what type of channel is this
	int		VectorLen;			// size of each individual vector
	uint32	PacketSize;			// size of each packet
	uint32	NumTimeCodes;		// Number of packets
	uint32	LastTimeCodeIdx;	// absolute index to last time code
	uint32 *	Data;					// pointer to packet data

	void 		Free(void);
	uint32	get_index(uint32 timecode, uint32 & cachedIdx);

	friend class HCompressedAnimClass;
};

/***********************************************************************************************
 * TimeCodedMotionChannelClass::get_index -- returns packet index                             *
 *                                                                                             *
 * BFME2 (retail 0x0018EC60): the caller owns the cache. The look-ahead only runs while two   *
 * more packets fit before the last one, and the binary search is folded in.                  *
 *=============================================================================================*/
WWINLINE uint32 TimeCodedMotionChannelClass::get_index(uint32 timecode, uint32 & cachedIdx)
{
	uint32 idx = cachedIdx;

	if (idx + PacketSize * 2 <= LastTimeCodeIdx) {
		uint32 * packet = &Data[idx];
		if (timecode >= (packet[0] & ~W3D_TIMECODED_BINARY_MOVEMENT_FLAG)) {
			if (timecode < (packet[PacketSize] & ~W3D_TIMECODED_BINARY_MOVEMENT_FLAG)) {
				return idx;
			}
			if (timecode < (packet[PacketSize * 2] & ~W3D_TIMECODED_BINARY_MOVEMENT_FLAG)) {
				cachedIdx = idx + PacketSize;
				return cachedIdx;
			}
		}
	}

	// special case last packet
	if (timecode >= (Data[LastTimeCodeIdx] & ~W3D_TIMECODED_BINARY_MOVEMENT_FLAG)) {
		cachedIdx = LastTimeCodeIdx;
		return LastTimeCodeIdx;
	}

	int leftIdx = 0;
	int rightIdx = NumTimeCodes - 2;

	for (;;) {
		int dx = (leftIdx + rightIdx) / 2;
		uint32 * packet = &Data[dx * PacketSize];

		if (timecode < (packet[0] & ~W3D_TIMECODED_BINARY_MOVEMENT_FLAG)) {
			rightIdx = dx;
			continue;
		}

		if (timecode < (packet[PacketSize] & ~W3D_TIMECODED_BINARY_MOVEMENT_FLAG)) {
			cachedIdx = packet - Data;
			return cachedIdx;
		}

		if (leftIdx ^ dx) {
			leftIdx = dx;
			continue;
		}

		leftIdx++;
	}
}

/***********************************************************************************************
 * TimeCodedMotionChannelClass::Get_Vector -- returns the value for the specified frame #     *
 *                                                                                             *
 * BFME2 (retail 0x0018ED50): one float per packet, and the search cache comes from the      *
 * caller. Retail inlines it into every caller (nothing calls the copy at 0x0018ED50).         *
 *=============================================================================================*/
WWINLINE void	TimeCodedMotionChannelClass::Get_Vector(float32 frame, float * setvec, uint32 & cachedIdx)
{
	uint32 tc0 = frame;

	uint32 pidx = get_index(tc0, cachedIdx);
	uint32 p2idx;

	if (pidx == ((NumTimeCodes - 1) * PacketSize)) {
		*setvec = *(float32 *)&Data[pidx+1];
		return;
	} else {
		p2idx = pidx + PacketSize;
	}

	uint32 time = Data[p2idx];

	if (time & W3D_TIMECODED_BINARY_MOVEMENT_FLAG) {
		*setvec = *(float32 *)&Data[pidx+1];
		return;
	}

	float32 time1 = (Data[pidx] & ~W3D_TIMECODED_BINARY_MOVEMENT_FLAG);
	float32 time2 = (time & ~W3D_TIMECODED_BINARY_MOVEMENT_FLAG);

	float32 ratio = (frame - time1) / (time2 - time1);

	float32 *frame1 = (float32 *) &Data[pidx+1];
	float32 *frame2 = (float32 *) &Data[p2idx+1];

	*setvec = WWMath::Lerp(frame1[0],frame2[0],ratio);
}

/***********************************************************************************************
 * TimeCodedMotionChannelClass::Get_QuatVector -- returns the orientation for the frame #     *
 *                                                                                             *
 * BFME2 (retail 0x0018EEF0): writes through the caller's quaternion and blends with the      *
 * normalized lerp at 0x00717550 instead of returning a Fast_Slerp result.                    *
 *=============================================================================================*/
void TimeCodedMotionChannelClass::Get_QuatVector(float32 frame, Quaternion & q, uint32 & cachedIdx)
{
	float32 * packets = (float32 *) Data;
	uint32 tc0 = frame;

	uint32 pidx = get_index(tc0, cachedIdx);
	uint32 p2idx;

	if (pidx == LastTimeCodeIdx) {
		float32 *vec = &packets[pidx+1];
		q.Set(vec[0], vec[1], vec[2], vec[3]);
		return;
	} else {
		p2idx = pidx + PacketSize;
	}

	uint32 time = Data[p2idx];

	if (time & W3D_TIMECODED_BINARY_MOVEMENT_FLAG) {
		// its a binary movement!
		float32 *vec = &packets[pidx+1];
		q.Set(vec[0], vec[1], vec[2], vec[3]);
		return;
	}

	// The next timecode never carries the flag here, so retail converts it unmasked.
	float32 time1 = (Data[pidx] & ~W3D_TIMECODED_BINARY_MOVEMENT_FLAG);
	float32 ratio = (frame - time1) / ((float32)time - time1);

	BFME2_Nlerp(q, *(Quaternion *)&packets[pidx+1], *(Quaternion *)&packets[p2idx+1], ratio);
}

// The adaptive-delta filter table, owned by AdaptiveDeltaMotionChannelFinish.cpp
// (retail 0x00DB67D8).
extern float filtertable[256];

// Decoded values for two consecutive frames of an N-float adaptive-delta
// channel. The caller owns it and starts Frame at 0x0FFFFFFF, an index no
// channel reaches. Descriptive name: retail only shows the 4 + 2*N*4 byte layout.
template <int N> struct AdaptiveDeltaCacheStruct
{
	uint32	Frame;
	float		Value[2 * N];
};

/*
** BFME2's AdaptiveDeltaMotionChannelClass (0x1C bytes, see the matched
** constructor at 0x00195F60). Retail compiles each sampler once per vector
** length: the scalar copies have no vector loop and 9-byte packet strides, the
** quaternion copies count four vectors over 36-byte strides. That is a
** compile-time length, so the bodies below are templates on it.
*/
class AdaptiveDeltaMotionChannelClass : public W3DMPO
{
public:

	AdaptiveDeltaMotionChannelClass(void);
	~AdaptiveDeltaMotionChannelClass(void);

	bool	Load_W3D(ChunkLoadClass & cload);
	int	Get_Type(void) { return Type; }
	int	Get_Pivot(void) { return PivotIdx; }
	void	Get_Vector(float32 frame, float * setvec);
	Quaternion Get_QuatVector(float32 frame);
	void	Get_Vector(float32 frame, float * setvec, AdaptiveDeltaCacheStruct<1> & cache);
	void	Get_QuatVector(float32 frame, Quaternion & q, AdaptiveDeltaCacheStruct<4> & cache);

	int		Get_Channel_Memory_Usage(void);

private:

	enum { PACKET_SIZE = 9 };

	uint32	PivotIdx;			// what pivot is this channel applied to
	uint32	Type;					// what type of channel is this
	int		VectorLen;			// size of each individual vector
	uint32	NumFrames;			// Number of frames
	uint32	DataByteCount;
	float		Scale;				// Scale Filter, this much
	uint32  *Data;				 	// pointer to packet data

	void 		Free(void);

	template <int N> void getframe(uint32 frame_idx, AdaptiveDeltaCacheStruct<N> & cache);
	template <int N> void decompress(uint32 src_idx, float *srcdata, uint32 frame_idx, float *outdata);

	friend class HCompressedAnimClass;
};

/***********************************************************************************************
 * AdaptiveDeltaMotionChannelClass::decompress -- decode N floats up to frame_idx             *
 *                                                                                             *
 * BFME2 (retail 0x0018F910 for one float, 0x0018F9C0 for four): continues from src_idx and   *
 * srcdata, or from the uncompressed header when srcdata is NULL. Nothing is decoded for a     *
 * frame past the end, so the source values are passed through.                               *
 *=============================================================================================*/
// ??$decompress@$00@AdaptiveDeltaMotionChannelClass@@AAEXKPAMK0@Z
template <int N>
void AdaptiveDeltaMotionChannelClass::decompress(uint32 src_idx, float *srcdata, uint32 frame_idx, float *outdata)
{
	unsigned char *base = (unsigned char *) Data;

	if (srcdata == NULL) {
		src_idx = 0;
		srcdata = (float *) base;
	}

	if (frame_idx >= NumFrames) {
		src_idx = frame_idx;
	}

	base += sizeof(float) * N;										// skip non-compressed header information
	base += (PACKET_SIZE * N) * (src_idx >> 4);				// skip out to current packet

	for (int vi = 0; vi < N; vi++) {
		unsigned char *pPacket = base + PACKET_SIZE * vi;
		float last_value = srcdata[vi];
		if (src_idx < frame_idx) {
			int fi = src_idx & 0xF;
			uint32 frame = src_idx;
			do {
			float filter = filtertable[*pPacket] * Scale;	// decompression filter
			pPacket++;

			// data is grouped in sets of 16 nybbles
			do {
				int factor = pPacket[fi >> 1] << 24;
				if ((fi & 1) == 0) {
					factor <<= 4;
				}
				factor >>= 28;									// sign-extended nybble, -8 to +7

				last_value += factor * filter;

				frame++;
				if (frame >= frame_idx) break;
				fi++;
			} while (fi < 16);

			fi = 0;
			pPacket += (PACKET_SIZE * N) - 1;					// skip to next packet
			} while (frame < frame_idx);
		}

		outdata[vi] = last_value;
	}
}

/***********************************************************************************************
 * AdaptiveDeltaMotionChannelClass::getframe -- fill the caller's cache for frame_idx          *
 *                                                                                             *
 * BFME2 (retail 0x0018FC20 for one float, 0x0018FCC0 for four): the cache holds frame_idx    *
 * and frame_idx+1. A channel of another length reads as zero.                                 *
 *=============================================================================================*/
// ??$getframe@$03@AdaptiveDeltaMotionChannelClass@@AAEXKAAU?$AdaptiveDeltaCacheStruct@$03@@@Z
template <int N>
void AdaptiveDeltaMotionChannelClass::getframe(uint32 frame_idx, AdaptiveDeltaCacheStruct<N> & cache)
{
	if (VectorLen != N) {
		memset(cache.Value, 0, sizeof(cache.Value));
		return;
	}

	if (frame_idx >= NumFrames) frame_idx = NumFrames - 1;

	if (cache.Frame + 1 == frame_idx) {
		// Sliding window
		cache.Frame++;
		memcpy(&cache.Value[0], &cache.Value[N], N * sizeof(float));
		decompress<N>(frame_idx, &cache.Value[0], frame_idx + 1, &cache.Value[N]);
		return;
	}

	if (frame_idx == cache.Frame) return;

	if (frame_idx < cache.Frame) {
		cache.Frame = frame_idx;
		decompress<N>(0, NULL, frame_idx, &cache.Value[0]);
	} else {
		decompress<N>(cache.Frame + 1, &cache.Value[N], frame_idx, &cache.Value[0]);
		cache.Frame = frame_idx;
	}

	decompress<N>(frame_idx, &cache.Value[0], frame_idx + 1, &cache.Value[N]);
}

/***********************************************************************************************
 * AdaptiveDeltaMotionChannelClass::Get_Vector -- returns the value for the specified frame #  *
 *                                                                                             *
 * BFME2 (retail 0x0018FD90).                                                                  *
 *=============================================================================================*/
void	AdaptiveDeltaMotionChannelClass::Get_Vector(float32 frame, float * setvec, AdaptiveDeltaCacheStruct<1> & cache)
{
	int frame1 = frame;

	getframe(frame1, cache);

	*setvec = WWMath::Lerp(cache.Value[0], cache.Value[1], frame - frame1);
}

/***********************************************************************************************
 * AdaptiveDeltaMotionChannelClass::Get_QuatVector -- returns the orientation for the frame # *
 *                                                                                             *
 * BFME2 (retail 0x0018FDE0): blends with the normalized lerp at 0x00717550.                  *
 *=============================================================================================*/
void AdaptiveDeltaMotionChannelClass::Get_QuatVector(float32 frame, Quaternion & q, AdaptiveDeltaCacheStruct<4> & cache)
{
	int frame1 = frame;

	getframe(frame1, cache);

	BFME2_Nlerp(q, *(Quaternion *)&cache.Value[0], *(Quaternion *)&cache.Value[4], frame - frame1);
}

/*
** BFME2's newer per-pivot channels (VectorMotion). The type names are the
** descriptive ones of BFME2MotionChannelFactory.cpp; slot 3 samples one float.
*/
class BFME2MotionChannel
{
public:
	virtual bool Load(ChunkLoadClass &);
	virtual ~BFME2MotionChannel();
	virtual int UnknownSlot2();
	virtual void UnknownSlot3(float frame, float *value, unsigned char **cursor);
	virtual void UnknownSlot4(float frame, Vector3 *value, unsigned char **cursor);
	virtual void UnknownSlot5(float frame, Quaternion *value, unsigned char **cursor);
	virtual int UnknownSlot6();
};

struct BFME2CompressedMotionChannels
{
	BFME2MotionChannel *			Channels[5];		// X, Y, Z, Q, fade
	TimeCodedBitChannelClass *	Visibility;
};

struct NodeCompressedMotionStruct
{
	NodeCompressedMotionStruct();
	~NodeCompressedMotionStruct();

	void SetFlavor(int flavor)  {Flavor = flavor;}

	int Flavor;

	union {
		struct {
			TimeCodedMotionChannelClass *		X;
			TimeCodedMotionChannelClass *		Y;
			TimeCodedMotionChannelClass *		Z;
			TimeCodedMotionChannelClass *		Q;
			TimeCodedMotionChannelClass *		Fade;
		} tc;

		struct {
			AdaptiveDeltaMotionChannelClass *		X;
			AdaptiveDeltaMotionChannelClass *		Y;
			AdaptiveDeltaMotionChannelClass *		Z;
			AdaptiveDeltaMotionChannelClass *		Q;
			AdaptiveDeltaMotionChannelClass *		Fade;

		} ad;

		struct {
			 void * X;
			 void * Y;
			 void * Z;
			 void * Q;
			 void * Fade;
		} vd;
	};


	// BFME: Vis sits at +0x18 and the struct strides 0x1c (imul ...,0x1c at
	// 0x0095BA3B and 0x0095B2D7), which is one dword more than Zero Hour's. The
	// extra one is a fade channel inside the union at +0x14 -- the slot-13 getter
	// at 0x0095B260 switches on Flavor and reads [eax+0x14] in both arms.
	TimeCodedBitChannelClass *			Vis;

	int Get_Channel_Memory_Usage(void);
};

/***********************************************************************************************
 * NodeCompressedMotionStruct::NodeCompressedMotionStruct -- constructor                       *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *=============================================================================================*/
// ?NodeCompressedMotionStruct::NodeCompressedMotionStruct present-unmatched
NodeCompressedMotionStruct::NodeCompressedMotionStruct() : 
	Vis(NULL)
{
		vd.X = NULL;
		vd.Y = NULL;
		vd.Z = NULL;
		vd.Q = NULL;
		vd.Fade = NULL;
}


/***********************************************************************************************
 * NodeCompressedMotionStruct::~NodeCompressedMotionStruct -- destructor                       *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   10/23/98   GTH : Created.                                                                 *
 *   02/02/00   JGA : Compressed                                                               *
 *=============================================================================================*/
// ?NodeCompressedMotionStruct::~NodeCompressedMotionStruct present-unmatched
NodeCompressedMotionStruct::~NodeCompressedMotionStruct()
{
	// Needs to be changed to call the correct destructors

	switch (Flavor) {
		case ANIM_FLAVOR_TIMECODED:
			if (tc.X) delete tc.X;
			if (tc.Y) delete tc.Y;
			if (tc.Z) delete tc.Z;
			if (tc.Q) delete tc.Q;
			if (tc.Fade) delete tc.Fade;
			break;
		case ANIM_FLAVOR_ADAPTIVE_DELTA:
			if (ad.X) delete ad.X;
			if (ad.Y) delete ad.Y;
			if (ad.Z) delete ad.Z;
			if (ad.Q) delete ad.Q;
			if (ad.Fade) delete ad.Fade;
			break;
		default:
			WWASSERT(0);	// unknown flavor
			break;
	}

	if (Vis) delete Vis;

}  // ~NodeCompressedMotionStruct


int NodeCompressedMotionStruct::Get_Channel_Memory_Usage(void)
{
	int size = sizeof(NodeCompressedMotionStruct);

	switch (Flavor) {
		case ANIM_FLAVOR_TIMECODED:
			if (tc.X) size += tc.X->Get_Channel_Memory_Usage();
			if (tc.Y) size += tc.Y->Get_Channel_Memory_Usage();
			if (tc.Z) size += tc.Z->Get_Channel_Memory_Usage();
			if (tc.Q) size += tc.Q->Get_Channel_Memory_Usage();
			break;
		case ANIM_FLAVOR_ADAPTIVE_DELTA:
			if (ad.X) size += ad.X->Get_Channel_Memory_Usage();
			if (ad.Y) size += ad.Y->Get_Channel_Memory_Usage();
			if (ad.Z) size += ad.Z->Get_Channel_Memory_Usage();
			if (ad.Q) size += ad.Q->Get_Channel_Memory_Usage();
			break;
	}

	if (Vis) size += Vis->Get_Channel_Memory_Usage();

	return size;
}


/*********************************************************************************************** 
 * HCompressedAnimClass::HCompressedAnimClass -- constructor                                   * 
 *                                                                                             * 
 * INPUT:                                                                                      * 
 *                                                                                             * 
 * OUTPUT:                                                                                     * 
 *                                                                                             * 
 * WARNINGS:                                                                                   * 
 *                                                                                             * 
 * HISTORY:                                                                                    * 
 *   08/11/1997 GH  : Created.                                                                 * 
 *=============================================================================================*/
// ?HCompressedAnimClass::HCompressedAnimClass present-unmatched
HCompressedAnimClass::HCompressedAnimClass(void) :
	NumFrames(0),
	NumNodes(0),
	Flavor(ANIM_FLAVOR_VALID),
	FrameRate(0),
	NodeMotion(NULL),
	VectorMotion(NULL)
{
	memset(Name,0,W3D_NAME_LEN);
	_bfme_unk_hcanim_key = TheNameKeyGenerator->nameToKey(Name);
	memset(HierarchyName,0,W3D_NAME_LEN);
}


/*********************************************************************************************** 
 * HCompressedAnimClass::~HCompressedAnimClass -- Destructor                                   * 
 *                                                                                             * 
 * INPUT:                                                                                      * 
 *                                                                                             * 
 * OUTPUT:                                                                                     * 
 *                                                                                             * 
 * WARNINGS:                                                                                   * 
 *                                                                                             * 
 * HISTORY:                                                                                    * 
 *   08/11/1997 GH  : Created.                                                                 * 
 *=============================================================================================*/
// ?HCompressedAnimClass::~HCompressedAnimClass present-unmatched
HCompressedAnimClass::~HCompressedAnimClass(void)
{
	Free();
}


/*********************************************************************************************** 
 * HCompressedAnimClass::Free -- De-allocates all memory in use                                * 
 *                                                                                             * 
 * INPUT:                                                                                      * 
 *                                                                                             * 
 * OUTPUT:                                                                                     * 
 *                                                                                             * 
 * WARNINGS:                                                                                   * 
 *                                                                                             * 
 * HISTORY:                                                                                    * 
 *   08/11/1997 GH  : Created.                                                                 * 
 *=============================================================================================*/
/*********************************************************************************************** 
 * HCompressedAnimClass::Load -- Loads hierarchy animation from a file                         * 
 *                                                                                             * 
 * INPUT:                                                                                      * 
 *                                                                                             * 
 * OUTPUT:                                                                                     * 
 *                                                                                             * 
 * WARNINGS:                                                                                   * 
 *                                                                                             * 
 * HISTORY:                                                                                    * 
 *   08/11/1997 GH  : Created.                                                                 * 
 *=============================================================================================*/
// ?HCompressedAnimClass::Load_W3D present-unmatched
int HCompressedAnimClass::Load_W3D(ChunkLoadClass & cload)
{
	int i = 0;
	/* 
	** First make sure we release any memory in use
	*/
	Free();

	/*
	**	Open the first chunk, it should be the animation header
	*/
	if (!cload.Open_Chunk()) return LOAD_ERROR;

	if (cload.Cur_Chunk_ID() != W3D_CHUNK_COMPRESSED_ANIMATION_HEADER) {
		// ERROR: Expected Animation Header!
		return LOAD_ERROR;
	}

	W3dCompressedAnimHeaderStruct aheader;
	if (cload.Read(&aheader,sizeof(W3dAnimHeaderStruct)) != sizeof(W3dAnimHeaderStruct)) {
		return LOAD_ERROR;
	}

	cload.Close_Chunk();

	strcpy(Name,aheader.HierarchyName);
	strcat(Name,".");
	strcat(Name,aheader.Name);

	// TSS chasing crash bug 05/26/99
   WWASSERT(HierarchyName != NULL);
   WWASSERT(aheader.HierarchyName != NULL);
   WWASSERT(sizeof(HierarchyName) >= W3D_NAME_LEN);
   strncpy(HierarchyName,aheader.HierarchyName,W3D_NAME_LEN);

	HTreeClass * base_pose = Get_HTree(HierarchyName);
	if (base_pose == NULL) {
		goto Error;
	}
	NumNodes = base_pose->Num_Pivots();

	NumFrames = aheader.NumFrames;
	FrameRate = aheader.FrameRate;
	Flavor    = aheader.Flavor;
  																					
	// Just for now                                          
	WWASSERT((Flavor == ANIM_FLAVOR_TIMECODED)||(Flavor == ANIM_FLAVOR_ADAPTIVE_DELTA));

	NodeMotion = W3DNEWARRAY NodeCompressedMotionStruct[ NumNodes ];
	if (NodeMotion == NULL) {
		goto Error;
	}

	// Initialize Flavor
	for (i=0; i<NumNodes; i++) {
		NodeMotion[i].SetFlavor(Flavor);
	}

	/*
	** Now, read in all of the other chunks (motion channels).
	*/
	TimeCodedMotionChannelClass * tc_chan;
	AdaptiveDeltaMotionChannelClass * ad_chan;
	TimeCodedBitChannelClass * newbitchan;

	while (cload.Open_Chunk()) {

		switch (cload.Cur_Chunk_ID()) {

			case W3D_CHUNK_COMPRESSED_ANIMATION_CHANNEL:

				switch ( Flavor ) {

					case ANIM_FLAVOR_TIMECODED:
						
						if (!read_channel(cload,&tc_chan)) {
							goto Error;
						}			
						if (tc_chan->Get_Pivot() < NumNodes) {
							add_channel(tc_chan);
						} else {
							// PWG 12-14-98: we have only allocated space for NumNode pivots.  
							// If we have an index thats equal or higher than NumNode we are
							// gonna trash memory.  Boy will we trash memory.
							// GTH 09-25-2000: print a warning and survive this error
							delete tc_chan;
							WWDEBUG_SAY(("ERROR! animation %s indexes a bone not present in the model. Please re-export!\r\n",Name));
						}

						break;

					case ANIM_FLAVOR_ADAPTIVE_DELTA:
						if (!read_channel(cload,&ad_chan)) {
							goto Error;
						}			
						if (ad_chan->Get_Pivot() < NumNodes) {
							add_channel(ad_chan);
						} else {
							// PWG 12-14-98: we have only allocated space for NumNode pivots.  
							// If we have an index thats equal or higher than NumNode we are
							// gonna trash memory.  Boy will we trash memory.
							// GTH 09-25-2000: print a warning and survive this error
							delete ad_chan;
							WWDEBUG_SAY(("ERROR! animation %s indexes a bone not present in the model. Please re-export!\r\n",Name));
						}
						break;
				}
				break;
	
			case W3D_CHUNK_COMPRESSED_BIT_CHANNEL:
				if (!read_bit_channel(cload,&newbitchan)) {
					goto Error;
				}
				if (newbitchan->Get_Pivot() < NumNodes) {
					add_bit_channel(newbitchan);
				} else {
					// PWG 12-14-98: we have only allocated space for NumNode pivots.  
					// If we have an index thats equal or higher than NumNode we are
					// gonna trash memory.  Boy will we trash memory.
					// GTH 09-25-2000: print a warning and survive this error
					delete newbitchan;
					WWDEBUG_SAY(("ERROR! animation %s indexes a bone not present in the model. Please re-export!\r\n",Name));
				}

				break;

			default:
				break;
		}
		cload.Close_Chunk();
	}

	return OK;

Error:

	Free();
	return LOAD_ERROR;

}	 // Load_W3D

/*********************************************************************************************** 
 * HCompressedAnimClass::read_channel -- Reads in a single channel of motion                   * 
 *                                                                                             * 
 * INPUT:                                                                                      * 
 *                                                                                             * 
 * OUTPUT:                                                                                     * 
 *                                                                                             * 
 * WARNINGS:                                                                                   * 
 *                                                                                             * 
 * HISTORY:                                                                                    * 
 *   08/11/1997 GH  : Created.                                                                 * 
 *=============================================================================================*/
// ?HCompressedAnimClass::read_channel present-unmatched
bool HCompressedAnimClass::read_channel(ChunkLoadClass & cload,TimeCodedMotionChannelClass * * newchan)
{
	*newchan = W3DNEW TimeCodedMotionChannelClass;
	bool result = (*newchan)->Load_W3D(cload);	
	
	return result;
  
}	// read_channel

// ?HCompressedAnimClass::read_channel present-unmatched
bool HCompressedAnimClass::read_channel(ChunkLoadClass & cload,AdaptiveDeltaMotionChannelClass * * newchan)
{
	*newchan = W3DNEW AdaptiveDeltaMotionChannelClass;
	bool result = (*newchan)->Load_W3D(cload);	
	
	return result;
  
}	// read_channel


/*********************************************************************************************** 
 * HCompressedAnimClass::add_channel -- Adds a motion channel to the animation                 * 
 *                                                                                             * 
 * INPUT:                                                                                      * 
 *                                                                                             * 
 * OUTPUT:                                                                                     * 
 *                                                                                             * 
 * WARNINGS:                                                                                   * 
 *                                                                                             * 
 * HISTORY:                                                                                    * 
 *   08/11/1997 GH  : Created.                                                                 * 
 *=============================================================================================*/
// ?HCompressedAnimClass::add_channel present-unmatched
void HCompressedAnimClass::add_channel(TimeCodedMotionChannelClass * newchan)
{
	int idx = newchan->Get_Pivot();

	switch (newchan->Get_Type())
	{
		case ANIM_CHANNEL_X:
			NodeMotion[idx].tc.X = newchan;
			break;

		case ANIM_CHANNEL_Y:
			NodeMotion[idx].tc.Y = newchan;
			break;

		case ANIM_CHANNEL_Z:
			NodeMotion[idx].tc.Z = newchan;
			break;

		case ANIM_CHANNEL_Q:
			NodeMotion[idx].tc.Q = newchan;
			break;

		case ANIM_CHANNEL_FADE:
			NodeMotion[idx].tc.Fade = newchan;
			break;
	}

}	// add_channel

// ?HCompressedAnimClass::add_channel present-unmatched
void HCompressedAnimClass::add_channel(AdaptiveDeltaMotionChannelClass * newchan)
{
	int idx = newchan->Get_Pivot();

	switch (newchan->Get_Type())
	{
		case ANIM_CHANNEL_X:
			NodeMotion[idx].ad.X = newchan;
			break;

		case ANIM_CHANNEL_Y:
			NodeMotion[idx].ad.Y = newchan;
			break;

		case ANIM_CHANNEL_Z:
			NodeMotion[idx].ad.Z = newchan;
			break;

		case ANIM_CHANNEL_Q:
			NodeMotion[idx].ad.Q = newchan;
			break;

		case ANIM_CHANNEL_FADE:
			NodeMotion[idx].ad.Fade = newchan;
			break;
	}

}	// add_channel




/***********************************************************************************************
 * HCompressedAnimClass::read_bit_channel -- read a bit channel from the file                  *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   1/19/98    GTH : Created.                                                                 *
 *=============================================================================================*/
// ?HCompressedAnimClass::read_bit_channel present-unmatched
bool HCompressedAnimClass::read_bit_channel(ChunkLoadClass & cload,TimeCodedBitChannelClass * * newchan)
{
	*newchan = W3DNEW TimeCodedBitChannelClass;
	bool result = (*newchan)->Load_W3D(cload);	

	return result;		 
  
}	// read_bit_channel


/***********************************************************************************************
 * HCompressedAnimClass::add_bit_channel -- install a bit channel into the animation           *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   1/19/98    GTH : Created.                                                                 *
 *=============================================================================================*/
// ?HCompressedAnimClass::add_bit_channel present-unmatched
void HCompressedAnimClass::add_bit_channel(TimeCodedBitChannelClass * newchan)
{
	int idx = newchan->Get_Pivot();

	switch (newchan->Get_Type())
	{
		case BIT_CHANNEL_VIS:
			NodeMotion[idx].Vis = newchan;
			break;
	}
}

/***********************************************************************************************
 * HCompressedAnimClass::_bfme_hanim_fade -- returns the fade of a pivot at a frame            *
 *                                                                                             *
 * BFME2 (retail 0x001903C0). Pivots without a fade channel are fully opaque. Every call       *
 * starts with a cold search cache.                                                            *
 *=============================================================================================*/
float HCompressedAnimClass::_bfme_hanim_fade(int pividx,float frame)
{
	float fade = 1.0f;

	if (VectorMotion) {
		BFME2MotionChannel * chan = VectorMotion[pividx].Channels[4];
		if (chan) chan->UnknownSlot3(frame, &fade, NULL);
		return fade;
	}

	struct NodeCompressedMotionStruct * motion = &NodeMotion[pividx];

	switch(Flavor) {
		case ANIM_FLAVOR_TIMECODED:
			if (motion->tc.Fade) {
				uint32 cache = 0x0FFFFFFF;
				motion->tc.Fade->Get_Vector(frame, &fade, cache);
			}
			break;
		case ANIM_FLAVOR_ADAPTIVE_DELTA:
			if (motion->ad.Fade) {
				// Not Get_Vector: retail takes the frame fraction before the delta.
				AdaptiveDeltaCacheStruct<1> cache;
				cache.Frame = 0x0FFFFFFF;
				int frame1 = frame;
				motion->ad.Fade->getframe(frame1, cache);
				float t = frame - frame1;
				fade = WWMath::Lerp(cache.Value[0], cache.Value[1], t);
			}
			break;
	}

	return fade;
}

/*********************************************************************************************** 
 * HCompressedAnimClass::Get_Translation -- returns the translation vector for the given frame * 
 *                                                                                             * 
 * INPUT:                                                                                      * 
 *                                                                                             * 
 * OUTPUT:                                                                                     * 
 *                                                                                             * 
 * WARNINGS:                                                                                   * 
 *                                                                                             * 
 * HISTORY:                                                                                    * 
 *   08/11/1997 GH  : Created.                                                                 * 
 *=============================================================================================*/
void HCompressedAnimClass::Get_Translation( Vector3& trans, int pividx, float frame ) const
{
	if (VectorMotion) {
		BFME2MotionChannel * chan = VectorMotion[pividx].Channels[0];
		if (chan) chan->UnknownSlot3(frame, &(trans[0]), NULL);
		else trans[0] = 0.0f;
		chan = VectorMotion[pividx].Channels[1];
		if (chan) chan->UnknownSlot3(frame, &(trans[1]), NULL);
		else trans[1] = 0.0f;
		chan = VectorMotion[pividx].Channels[2];
		if (chan) chan->UnknownSlot3(frame, &(trans[2]), NULL);
		else trans[2] = 0.0f;
		return;
	}

	struct NodeCompressedMotionStruct * motion = &NodeMotion[pividx];
	  
	trans=Vector3(0,0,0);

	switch(Flavor) {
		case ANIM_FLAVOR_TIMECODED:
			if (motion->tc.X) {
				uint32 cache = 0x0FFFFFFF;
				motion->tc.X->Get_Vector(frame, &(trans[0]), cache);
			}
			if (motion->tc.Y) {
				uint32 cache = 0x0FFFFFFF;
				motion->tc.Y->Get_Vector(frame, &(trans[1]), cache);
			}
			if (motion->tc.Z) {
				uint32 cache = 0x0FFFFFFF;
				motion->tc.Z->Get_Vector(frame, &(trans[2]), cache);
			}
			break;
		case ANIM_FLAVOR_ADAPTIVE_DELTA:
			if (motion->ad.X) {
				AdaptiveDeltaCacheStruct<1> cache;
				cache.Frame = 0x0FFFFFFF;
				int frame1 = frame;
				motion->ad.X->getframe(frame1, cache);
				float t = frame - frame1;
				trans[0] = WWMath::Lerp(cache.Value[0], cache.Value[1], t);
			}
			if (motion->ad.Y) {
				AdaptiveDeltaCacheStruct<1> cache;
				cache.Frame = 0x0FFFFFFF;
				int frame1 = frame;
				motion->ad.Y->getframe(frame1, cache);
				float t = frame - frame1;
				trans[1] = WWMath::Lerp(cache.Value[0], cache.Value[1], t);
			}
			if (motion->ad.Z) {
				AdaptiveDeltaCacheStruct<1> cache;
				cache.Frame = 0x0FFFFFFF;
				int frame1 = frame;
				motion->ad.Z->getframe(frame1, cache);
				float t = frame - frame1;
				trans[2] = WWMath::Lerp(cache.Value[0], cache.Value[1], t);
			}
			break;
	}
}

/*********************************************************************************************** 
 * HCompressedAnimClass::Get_Orientation -- returns a quaternion for the orientation of the    * 
 *                                                                                             * 
 * INPUT:                                                                                      * 
 *                                                                                             * 
 * OUTPUT:                                                                                     * 
 *                                                                                             * 
 * WARNINGS:                                                                                   * 
 *                                                                                             * 
 * HISTORY:                                                                                    * 
 *   08/11/1997 GH  : Created.                                                                 * 
 *=============================================================================================*/
// ?HCompressedAnimClass::Get_Orientation present-unmatched
bool HCompressedAnimClass::Get_Orientation(Quaternion& q, int pividx,float frame) const
{		
	switch(Flavor) {
		case ANIM_FLAVOR_TIMECODED:
			if (NodeMotion[pividx].tc.Q) q = NodeMotion[pividx].tc.Q->Get_QuatVector(frame);
			else q.Make_Identity();
			break;
		case ANIM_FLAVOR_ADAPTIVE_DELTA:
			if (NodeMotion[pividx].ad.Q) q = NodeMotion[pividx].ad.Q->Get_QuatVector(frame);
			else q.Make_Identity();
			break;
		default:
			WWASSERT(0); // unknown flavor
			break;
	}
	// BFME reports whether the pivot actually has rotation; these bodies are not
	// matched yet, so true is a placeholder that preserves Zero Hour behaviour.
	return true;
} // Get_Orientation

/*********************************************************************************************** 
 * HCompressedAnimClass::Get_Transform -- returns the transform matrix for the given frame	  * 
 *                                                                                             * 
 * INPUT:                                                                                      * 
 *                                                                                             * 
 * OUTPUT:                                                                                     * 
 *                                                                                             * 
 * WARNINGS:                                                                                   * 
 *                                                                                             * 
 * HISTORY:                                                                                    * 
 *   08/11/1997 GH  : Created.                                                                 * 
 *=============================================================================================*/
// ?HCompressedAnimClass::Get_Transform present-unmatched
void HCompressedAnimClass::Get_Transform( Matrix3D& mtx, int pividx, float frame ) const
{
	struct NodeCompressedMotionStruct * motion = &NodeMotion[pividx];
	  
	switch(Flavor) {
		case ANIM_FLAVOR_TIMECODED:
			if (NodeMotion[pividx].tc.Q) {
				Quaternion q;
				q = NodeMotion[pividx].tc.Q->Get_QuatVector(frame);
				::Build_Matrix3D(q,mtx);
			}
			else mtx.Make_Identity();
			if (motion->tc.X) motion->tc.X->Get_Vector(frame, &(mtx[0][3]));
			if (motion->tc.Y) motion->tc.Y->Get_Vector(frame, &(mtx[1][3]));
			if (motion->tc.Z) motion->tc.Z->Get_Vector(frame, &(mtx[2][3]));
			break;
		case ANIM_FLAVOR_ADAPTIVE_DELTA:
			if (NodeMotion[pividx].ad.Q) {
				Quaternion q;
				q = NodeMotion[pividx].ad.Q->Get_QuatVector(frame);
				::Build_Matrix3D(q,mtx);
			}
			else mtx.Make_Identity();

			if (motion->ad.X) motion->ad.X->Get_Vector(frame, &(mtx[0][3]));
			if (motion->ad.Y) motion->ad.Y->Get_Vector(frame, &(mtx[1][3]));
			if (motion->ad.Z) motion->ad.Z->Get_Vector(frame, &(mtx[2][3]));
			break;
		default:
			WWASSERT(0);	// unknown flavor
			break;
	}
}

/***********************************************************************************************
 * HCompressedAnimClass::Get_Visibility -- return visibility state for given pivot/frame       *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   1/19/98    GTH : Created.                                                                 *
 *=============================================================================================*/
// HCompressedAnimClass::Get_Visibility is recovered in HCompressedAnimGetters.cpp.



/***********************************************************************************************
 * HAnimClass::Is_Node_Motion_Present -- return true if there is motion defined for this frame *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   3/23/99    EHC : Created.                                                                 *
 *=============================================================================================*/
// HCompressedAnimClass::Is_Node_Motion_Present is recovered in HCompressedAnimGetters.cpp.

// HCompressedAnimClass::Has_X_Translation is recovered in HCompressedAnimGetters.cpp.

// HCompressedAnimClass::Has_Y_Translation is recovered in HCompressedAnimGetters.cpp.

// HCompressedAnimClass::Has_Z_Translation is recovered in HCompressedAnimGetters.cpp.

// HCompressedAnimClass::Has_Rotation is recovered in HCompressedAnimGetters.cpp.

// HCompressedAnimClass::Has_Visibility is recovered in HCompressedAnimGetters.cpp.


// eof - hcanim.cpp
