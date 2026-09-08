// ?Load_W3D@HCompressedAnimClass@@QAEHAAVChunkLoadClass@@@Z
// partial score=0.301488 date=2026-09-08
// ?Load_W3D@HCompressedAnimClass@@QAEHAAVChunkLoadClass@@@Z
// partial score=0.3 date=2026-09-08
// cl: /Ireference/shims/bfmerendobj /Ireference/shims/bfmehcanim /Ob2 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
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
#include "motchan.h"
#include "chunkio.h"
#include "w3d_file.h"
#include "wwdebug.h"
#include <string.h>
#include "nstrdup.h"
extern "C" int __cdecl toupper(int);


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

// BFME2's new compressed-channel records have no recovered public source name.
// This descriptive interface is limited to the loader's proven fields and
// virtual ABI: Load_W3D is slot 0, the scalar deleting destructor is slot 1,
// Type is at +4 and Pivot is at +8.
class BFME2CompressedMotionChannel {
public:
	virtual bool Load_W3D(ChunkLoadClass & cload);
	virtual ~BFME2CompressedMotionChannel();

	int Type;
	int Pivot;

	int Get_Type() const { return Type; }
	int Get_Pivot() const { return Pivot; }
};

// The factory's original owner and spelling remain unresolved.  Its full retail
// body is independently bounded at RVA 0x001A46B4..0x001A47BB; keep this call
// descriptive until that dependency is reconstructed.
extern BFME2CompressedMotionChannel *BFME2_Read_CompressedMotionChannel(ChunkLoadClass & cload);

struct BFME2CompressedMotionChannels {
	BFME2CompressedMotionChannel *Channels[5];
	TimeCodedBitChannelClass *Visibility;
	BFME2CompressedMotionChannels();
	~BFME2CompressedMotionChannels();
};

// Scratch-only model of the retail debug stream used for missing-bone reports.
// The slot names are descriptive and preserve only the independently proven ABI.
class BFMEAnimationDebugStream {
public:
	virtual void Slot00(); virtual void Slot04(); virtual void Slot08(); virtual void Slot0C();
	virtual void Slot10(); virtual void Slot14(); virtual void Slot18(); virtual void Slot1C();
	virtual void Slot20(); virtual void Slot24(); virtual void Slot28(); virtual void Slot2C();
	virtual void Slot30(); virtual void Slot34();
	virtual BFMEAnimationDebugStream *Put_String(const char *text);
	virtual void Slot3C(); virtual void Slot40(); virtual void Slot44(); virtual void Slot48();
	virtual BFMEAnimationDebugStream *Finish(int report);
};
class BFMEAnimationDebugClass {
public:
	virtual void Slot00(); virtual void Slot04(); virtual void Slot08(); virtual void Slot0C();
	virtual void Slot10(); virtual void Slot14(); virtual void Slot18(); virtual void Slot1C();
	virtual void Slot20(); virtual void Slot24(); virtual void Slot28(); virtual void Slot2C();
	virtual void Slot30(); virtual void Slot34(); virtual void Slot38(); virtual void Slot3C();
	virtual void Slot40(); virtual void Slot44(); virtual void Slot48(); virtual void Slot4C();
	virtual void Slot50(); virtual void Slot54(); virtual void Slot58(); virtual void Slot5C();
	virtual void Begin_Report();
	virtual void Slot64(); virtual void Slot68();
	virtual BFMEAnimationDebugStream *Get_Stream(void *owner, void *context, void *extra);
};
extern BFMEAnimationDebugClass *volatile g_BFMEAnimationDebug;
extern "C" bool __cdecl BFMEAnimation_DebugIsEnabled();
extern "C" bool __cdecl BFMEAnimation_DebugSkipNext(bool set);

// Keep this expression in Load_W3D's member scope so the compiler retains the
// retail object/name register roles while merging the common stream suffix.
#define BFME_ANIMATION_REPORT_MISSING_BONE() do { \
	if (BFMEAnimation_DebugIsEnabled()) { \
		BFMEAnimation_DebugSkipNext(true); \
		g_BFMEAnimationDebug->Begin_Report(); \
		(g_BFMEAnimationDebug->Get_Stream(NULL, NULL, NULL) \
			->Put_String("ERROR! animation ") \
			->Put_String(Name) \
			->Put_String(" indexes a bone not present in the model. Please re-export!\r\n") \
			->Finish(2)); \
	} \
} while (0)

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
	bool old_format;
	TimeCodedMotionChannelClass * tc_chan;
	AdaptiveDeltaMotionChannelClass * ad_chan;
	TimeCodedBitChannelClass * newbitchan;
	BFME2CompressedMotionChannel * newchan;
	/*
	** First make sure we release any memory in use
	*/
	Free();

	/*
	** Open the first chunk, it should be the animation header
	*/
	if (!cload.Open_Chunk()) return LOAD_ERROR;

	if (cload.Cur_Chunk_ID() != W3D_CHUNK_COMPRESSED_ANIMATION_HEADER) {
		return LOAD_ERROR;
	}

	W3dCompressedAnimHeaderStruct aheader;
	if (cload.Read(&aheader,sizeof(W3dAnimHeaderStruct)) != sizeof(W3dAnimHeaderStruct)) {
		return LOAD_ERROR;
	}

	cload.Close_Chunk();

	old_format = (aheader.Version == 1);
	if (!old_format && aheader.Version != 0x10000) {
		return LOAD_ERROR;
	}

	strcpy(Name,aheader.HierarchyName);
	strcat(Name,".");
	strcat(Name,aheader.Name);
	for (char *name = Name; *name != 0; name++) {
		*name = (char)toupper(*name);
	}

	_bfme_unk_hcanim_key = TheNameKeyGenerator->nameToKey(Name);

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

	if (old_format) {
		int i;
		Flavor = aheader.Flavor;
		NodeMotion = W3DNEWARRAY NodeCompressedMotionStruct[ NumNodes ];
		if (NodeMotion == NULL) {
			goto Error;
		}

		for (i=0; i<NumNodes; i++) {
			NodeMotion[i].SetFlavor(Flavor);
		}


		while (cload.Open_Chunk()) {
			switch (cload.Cur_Chunk_ID()) {
				case W3D_CHUNK_COMPRESSED_ANIMATION_CHANNEL:
					switch ( Flavor ) {
						case ANIM_FLAVOR_TIMECODED:
							if (!read_channel(cload,&tc_chan)) goto Error;
							if (tc_chan->Get_Pivot() < NumNodes) {
								add_channel(tc_chan);
							} else {
								delete tc_chan;
							}
							break;
						case ANIM_FLAVOR_ADAPTIVE_DELTA:
							if (!read_channel(cload,&ad_chan)) goto Error;
							if (ad_chan->Get_Pivot() < NumNodes) {
								add_channel(ad_chan);
							} else {
								delete ad_chan;
							}
							break;
					}
					break;

				case W3D_CHUNK_COMPRESSED_BIT_CHANNEL:
					if (!read_bit_channel(cload,&newbitchan)) goto Error;
					if (newbitchan->Get_Pivot() < NumNodes && newbitchan->Get_Type() == BIT_CHANNEL_VIS) {
						add_bit_channel(newbitchan);
					} else {
						delete newbitchan;
					}
					break;
				default:
					break;
			}
			cload.Close_Chunk();
		}
		return OK;
	}

	VectorMotion = W3DNEWARRAY BFME2CompressedMotionChannels[ NumNodes ];
	if (VectorMotion == NULL) {
		goto Error;
	}

	while (cload.Open_Chunk()) {
		switch (cload.Cur_Chunk_ID()) {
			case W3D_CHUNK_COMPRESSED_ANIMATION_CHANNEL + 1: {
				BFME2CompressedMotionChannel * newchan = BFME2_Read_CompressedMotionChannel(cload);
				if (newchan == NULL) break;
				int slot;
				if (newchan->Get_Pivot() < NumNodes) {
					switch (newchan->Get_Type()) {
						case ANIM_CHANNEL_X: slot = 0; break;
						case ANIM_CHANNEL_Y: slot = 1; break;
						case ANIM_CHANNEL_Z: slot = 2; break;
						case ANIM_CHANNEL_Q: slot = 3; break;
						case ANIM_CHANNEL_FADE: slot = 4; break;
						default: slot = 5; break;
					}
					if (slot < 5) {
						BFME2CompressedMotionChannel ** dest = &VectorMotion[newchan->Get_Pivot()].Channels[slot];
						if (*dest == NULL) *dest = newchan;
						else { ::delete newchan; BFME_ANIMATION_REPORT_MISSING_BONE(); }
					} else {
						::delete newchan;
						BFME_ANIMATION_REPORT_MISSING_BONE();
					}
				} else {
					::delete newchan;
					BFME_ANIMATION_REPORT_MISSING_BONE();
				}
				break;
			}

			case W3D_CHUNK_COMPRESSED_BIT_CHANNEL + 1:
				if (!read_bit_channel(cload,&newbitchan)) goto Error;
				if (newbitchan->Get_Pivot() < NumNodes) {
					VectorMotion[newbitchan->Get_Pivot()].Visibility = newbitchan;
				} else {
					delete newbitchan;
					BFME_ANIMATION_REPORT_MISSING_BONE();
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

} // Load_W3D

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
// ?HCompressedAnimClass::Get_Translation present-unmatched
void HCompressedAnimClass::Get_Translation( Vector3& trans, int pividx, float frame ) const
{
	struct NodeCompressedMotionStruct * motion = &NodeMotion[pividx];
	  
	trans=Vector3(0,0,0);

	switch(Flavor) {
		case ANIM_FLAVOR_TIMECODED:
			if (motion->tc.X) motion->tc.X->Get_Vector(frame, &(trans[0]));
			if (motion->tc.Y) motion->tc.Y->Get_Vector(frame, &(trans[1]));
			if (motion->tc.Z) motion->tc.Z->Get_Vector(frame, &(trans[2]));
			break;
		case ANIM_FLAVOR_ADAPTIVE_DELTA:
			if (motion->ad.X) motion->ad.X->Get_Vector(frame, &(trans[0]));
			if (motion->ad.Y) motion->ad.Y->Get_Vector(frame, &(trans[1]));
			if (motion->ad.Z) motion->ad.Z->Get_Vector(frame, &(trans[2]));
			break;
		default:
			WWASSERT(0);	// unknown flavor
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
// ?HCompressedAnimClass::Get_Visibility present-unmatched
bool HCompressedAnimClass::Get_Visibility(int pividx,float frame)
{		

	if (NodeMotion[pividx].Vis != NULL) {
		return (NodeMotion[pividx].Vis->Get_Bit((int)frame) == 1);
	}


	// default to always visible...
	return 1;
}



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
// ?HCompressedAnimClass::Is_Node_Motion_Present present-unmatched
bool HCompressedAnimClass::Is_Node_Motion_Present(int pividx) 
{
	WWASSERT((pividx >= 0) && (pividx < NumNodes));

	if (NodeMotion[pividx].vd.X != NULL)	return true;
	if (NodeMotion[pividx].vd.Y != NULL)	return true;
	if (NodeMotion[pividx].vd.Z != NULL)	return true;
	if (NodeMotion[pividx].vd.Q  != NULL)	return true;
	if (NodeMotion[pividx].Vis != NULL)		return true;

	return false;
}

// ?HCompressedAnimClass::Has_X_Translation present-unmatched
bool HCompressedAnimClass::Has_X_Translation (int pividx)
{
	WWASSERT((pividx >= 0) && (pividx < NumNodes));
	return NodeMotion[pividx].vd.X != NULL;
}

// ?HCompressedAnimClass::Has_Y_Translation present-unmatched
bool HCompressedAnimClass::Has_Y_Translation (int pividx)
{
	WWASSERT((pividx >= 0) && (pividx < NumNodes));
	return NodeMotion[pividx].vd.Y != NULL;
}

// ?HCompressedAnimClass::Has_Z_Translation present-unmatched
bool HCompressedAnimClass::Has_Z_Translation (int pividx)
{
	WWASSERT((pividx >= 0) && (pividx < NumNodes));
	return NodeMotion[pividx].vd.Z != NULL;
}

// ?HCompressedAnimClass::Has_Rotation present-unmatched
bool HCompressedAnimClass::Has_Rotation (int pividx)
{
	WWASSERT((pividx >= 0) && (pividx < NumNodes));
	return NodeMotion[pividx].vd.Q != NULL;
}

// ?HCompressedAnimClass::Has_Visibility present-unmatched
bool HCompressedAnimClass::Has_Visibility (int pividx)
{
	WWASSERT((pividx >= 0) && (pividx < NumNodes));
	return NodeMotion[pividx].Vis != NULL;
}


// eof - hcanim.cpp
