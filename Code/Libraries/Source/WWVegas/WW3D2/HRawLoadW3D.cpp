// cl: /Ireference/shims/bfmehrawanim /arch:SSE /G7 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
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

#ifndef HRAWANIM_H
#define HRAWANIM_H

#include "always.h"
// Scoped by -Ireference/shims/bfmehrawanim on the unit's `// cl:` line.

#ifndef HANIM_H
#define HANIM_H

#include "always.h"
#include "quat.h"
#include "refcount.h"
#include "w3d_file.h"
#include "hash.h"
#include "mempool.h"
#include <refcount.h>
#include <slist.h>
#include <vector.h>

struct NodeMotionStruct;
class MotionChannelClass;
class BitChannelClass;
class HTreeClass;
class ChunkLoadClass;
class ChunkSaveClass;
class HTreeClass;

#define EMBEDDED_SOUND_BONE_INDEX_NOT_SET -1

class HAnimClass : public RefCountClass, public	HashableClass
{
public:
	enum
	{
		CLASSID_UNKNOWNANIM	= 0xFFFFFFFF,
		CLASSID_HRAWANIM		= 0,
		CLASSID_LASTANIM		= 0x0000FFFF
	};

	HAnimClass(void)	{ }
	virtual ~HAnimClass(void);

	virtual const char *		Get_Name(void) const = 0;
	virtual const char *		Get_HName(void) const = 0;

	virtual const char *		Get_Key( void )						{ return Get_Name(); }

	virtual int					Get_Num_Frames(void) = 0;
	virtual float				Get_Frame_Rate() = 0;
	virtual float				Get_Total_Time() = 0;

	virtual void				Get_Translation(int pividx,float frame) {}
	virtual void				Get_Orientation(int pividx,float frame) {}
	virtual void				Get_Translation(Vector3& translation, int pividx,float frame) const = 0;
	virtual bool				Get_Orientation(Quaternion& orientation, int pividx,float frame) const = 0;
	virtual void				Get_Transform(Matrix3D&, int pividx, float frame) const = 0;
	virtual bool				Get_Visibility(int pividx,float frame) = 0;

	virtual int					Get_Num_Pivots(void) const = 0;
	virtual bool				Is_Node_Motion_Present(int pividx) = 0;

	virtual bool				Has_X_Translation (int pividx)	{ return true; }
	virtual bool				Has_Y_Translation (int pividx)	{ return true; }
	virtual bool				Has_Z_Translation (int pividx)	{ return true; }
	virtual bool				Has_Rotation (int pividx)			{ return true; }
	virtual bool				Has_Visibility (int pividx)		{ return true; }
	virtual int					Class_ID(void)	const															{ return CLASSID_UNKNOWNANIM; }

};

#endif

class MotionChannelClass;
class BitChannelClass;

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

	MotionChannelClass *		Fade;

	BitChannelClass *			Vis;
};

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

	void							Get_Translation(Vector3& translation, int pividx,float frame) const;
	bool							Get_Orientation(Quaternion& orientation, int pividx,float frame) const;
	void							Get_Transform(Matrix3D& transform, int pividx,float frame) const;
	bool							Get_Visibility(int pividx,float frame);

	bool							Is_Node_Motion_Present(int pividx);
	int							Get_Num_Pivots(void) const { return NumNodes; }

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
	unsigned int				NameKey;

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

#ifndef MOTCHAN_H
#define MOTCHAN_H

#include "always.h"
#include "bittype.h"
#include "w3d_file.h"
#include "quat.h"

class ChunkLoadClass;
class Quaternion;

class MotionChannelClass : public W3DMPO
{

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

friend class HRawAnimClass;

};

class BitChannelClass : public W3DMPO
{

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

#endif

#include "chunkio.h"
#include "assetmgr.h"

HTreeClass *Get_HTree(const char *name);
#include "htree.h"
extern "C" __declspec(dllimport) int __cdecl toupper(int);
enum NameKeyType { NAMEKEY_INVALID = 0, FORCE_NAMEKEYTYPE_LONG = 0x7fffffff };
class NameKeyGenerator { public: NameKeyType nameToKey(const char *name); };
extern NameKeyGenerator *TheNameKeyGenerator;

void HRawAnimClass::Free(void)
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

bool HRawAnimClass::read_channel(ChunkLoadClass & cload,MotionChannelClass * * newchan,bool pre30)
{
	*newchan = W3DNEW MotionChannelClass;
	bool result = (*newchan)->Load_W3D(cload);

	if (result && pre30) {
		(*newchan)->Set_Pivot((*newchan)->Get_Pivot()+1);
	}

	return result;
}

void HRawAnimClass::add_channel(MotionChannelClass * newchan)
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

void HRawAnimClass::add_bit_channel(BitChannelClass * newchan)
{
	int idx = newchan->Get_Pivot();

	switch (newchan->Get_Type())
	{
		case BIT_CHANNEL_VIS:
			NodeMotion[idx].Vis = newchan;
			break;
	}
}
