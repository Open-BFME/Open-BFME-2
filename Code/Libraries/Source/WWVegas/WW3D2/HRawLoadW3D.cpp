// cl: /Ireference/shims/bfmehrawanim /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
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
** Copyright 2025 Electronic Arts Inc.
** SPDX-License-Identifier: GPL-3.0-or-later
** BFME1 raw animation loader and local type declarations adapted to BFME2.
*/
// Target names/offsets follow header parsing and the matched channel family.
// Name10, HierarchyName30, NameKey40, NumFrames44, NumNodes48, FrameRate4C, NodeMotion50.
// Target imports toupper at BBA5B4 and passes signed chars before nameToKey.
// Array callbacks are ctor18D1E0 and dtor18E750; the latter independently
// reproduces the nine channel releases with the shared 24-byte cleanup body.
// Keep the channel helper definitions visible: MSVC uses them when compiling
// the loader, while the target still calls the matched read helpers.

// stlport
#define Matrix4x4 Matrix4  // BFME renamed it
#define __PLACEMENT_VEC_NEW_INLINE  // always.h/GameMemory.h define array placement-new themselves
// stlport

#define ANIM_CHANNEL_FADE 15
// Scoped by -Ireference/shims/bfmehrawanim on the unit's `// cl:` line.

// RefCountClass's inline members and deleting destructor are retail's
// size-optimised bodies: compile them for size, as hlod.cpp does.
#pragma optimize("s", on)
#include "refcount.h"
#pragma optimize("", on)
// BFME 2 does not pool the animation channels (see the motchan.h shim).
#include "always.h"
#undef W3DMPO_GLUE
#define W3DMPO_GLUE(ARGCLASS)
#include "hrawanim.h"
#include "motchan.h"

#include "chunkio.h"
#include "assetmgr.h"

HTreeClass *Get_HTree(const char *name);
#include "htree.h"
#include <ctype.h>
enum NameKeyType { NAMEKEY_INVALID = 0, FORCE_NAMEKEYTYPE_LONG = 0x7fffffff };
class NameKeyGenerator { public: NameKeyType nameToKey(const char *name); };
extern NameKeyGenerator *TheNameKeyGenerator;

inline void HRawAnimClass::Free(void)
{
	if (NodeMotion != NULL) {
		delete[] NodeMotion;
		NodeMotion = NULL;
	}
}

int HRawAnimClass::Load_W3D(ChunkLoadClass & cload)
{
	bool pre30 = false;

	Free();

	if (!cload.Open_Chunk()) return LOAD_ERROR;

	if (cload.Cur_Chunk_ID() != W3D_CHUNK_ANIMATION_HEADER) {
		return LOAD_ERROR;
	}

	W3dAnimHeaderStruct aheader;
	if (cload.Read(&aheader,sizeof(W3dAnimHeaderStruct)) != sizeof(W3dAnimHeaderStruct)) {
		return LOAD_ERROR;
	}

	cload.Close_Chunk();

	if (aheader.Version < W3D_MAKE_VERSION(3,0)) {
		pre30 = true;
	}

	strcpy(Name,aheader.HierarchyName);
	strcat(Name,".");
	strcat(Name,aheader.Name);

   WWASSERT(HierarchyName != NULL);
   WWASSERT(aheader.HierarchyName != NULL);
   WWASSERT(sizeof(HierarchyName) >= W3D_NAME_LEN);

	for (char *name = Name; *name != 0; ++name) *name = (char)toupper((int)*name);
	NameKey = TheNameKeyGenerator->nameToKey(Name);
	strncpy(HierarchyName,aheader.HierarchyName,W3D_NAME_LEN);

	HTreeClass * base_pose = Get_HTree(HierarchyName);
	if (base_pose == NULL) {
		goto Error;
	}
	NumNodes = base_pose->Num_Pivots();

	NumFrames = aheader.NumFrames;
	FrameRate = aheader.FrameRate;

	NodeMotion = W3DNEWARRAY NodeMotionStruct[ NumNodes ];
	if (NodeMotion == NULL) {
		goto Error;
	}

	MotionChannelClass * newchan;
	BitChannelClass * newbitchan;

	while (cload.Open_Chunk()) {

		switch (cload.Cur_Chunk_ID()) {

			case W3D_CHUNK_ANIMATION_CHANNEL:
				if (!read_channel(cload,&newchan,pre30)) {
					goto Error;
				}

				if (newchan->Get_Pivot() < NumNodes) {
					add_channel(newchan);
				} else {
					WWDEBUG_SAY(("Animation %s referring to missing Bone! Please re-export.\n",Name));
					newchan->Free();
					::operator delete(newchan);
				}
				break;

			case W3D_CHUNK_BIT_CHANNEL:
				if (!read_bit_channel(cload,&newbitchan,pre30)) {
					goto Error;
				}

				if (newbitchan->Get_Pivot() < NumNodes) {
					add_bit_channel(newbitchan);
				} else {
					WWDEBUG_SAY(("Animation %s referring to missing Bone! Please re-export.\n",Name));
					newbitchan->Free();
					::operator delete(newbitchan);
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

}

inline bool HRawAnimClass::read_channel(ChunkLoadClass & cload,MotionChannelClass * * newchan,bool pre30)
{
	*newchan = W3DNEW MotionChannelClass;
	bool result = (*newchan)->Load_W3D(cload);

	if (result && pre30) {
		(*newchan)->Set_Pivot((*newchan)->Get_Pivot()+1);
	}

	return result;
}

inline void HRawAnimClass::add_channel(MotionChannelClass * newchan)
{
	int idx = newchan->Get_Pivot();

	switch (newchan->Get_Type())
	{
		case ANIM_CHANNEL_X:
			NodeMotion[idx].X = newchan;
			break;

		case ANIM_CHANNEL_Y:
			NodeMotion[idx].Y = newchan;
			break;

		case ANIM_CHANNEL_Z:
			NodeMotion[idx].Z = newchan;
			break;

		case ANIM_CHANNEL_XR:
			NodeMotion[idx].XR = newchan;
			break;

		case ANIM_CHANNEL_YR:
			NodeMotion[idx].YR = newchan;
			break;

		case ANIM_CHANNEL_ZR:
			NodeMotion[idx].ZR = newchan;
			break;

		case ANIM_CHANNEL_Q:
			NodeMotion[idx].Q = newchan;
			break;

		case ANIM_CHANNEL_FADE:
			NodeMotion[idx].Fade = newchan;
			break;
	}

}

bool HRawAnimClass::read_bit_channel(ChunkLoadClass & cload,BitChannelClass * * newchan,bool pre30)
{
	*newchan = W3DNEW BitChannelClass;
	bool result = (*newchan)->Load_W3D(cload);

	if (result && pre30) {
		(*newchan)->PivotIdx += 1;
	}

	return result;
}

inline void HRawAnimClass::add_bit_channel(BitChannelClass * newchan)
{
	int idx = newchan->Get_Pivot();

	switch (newchan->Get_Type())
	{
		case BIT_CHANNEL_VIS:
			NodeMotion[idx].Vis = newchan;
			break;
	}
}

