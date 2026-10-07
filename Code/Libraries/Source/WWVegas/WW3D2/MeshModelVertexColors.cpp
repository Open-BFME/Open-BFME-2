// cl: /G7 /arch:SSE /Ireference/shims/bfmecamera /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep /Ireference/open-bfme-1/build/toolchains/dx81/include /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2
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
** This program is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
** GNU General Public License for more details.
** You should have received a copy of the GNU General Public License
** along with this program. If not, see <http://www.gnu.org/licenses/>.
*/
// BFME MeshModelClass::read_vertex_colors, RVA 0x0096D140, 373 bytes.
// read_chunks maps W3D_CHUNK_VERTEX_COLORS (0x0D) through selector byte
// 0x0097013F and table slot 0x0097011C to the arm at 0x0097001C;
// its call at 0x00970020 reaches this body. The dispatcher consumes AL
// and tests it against 1, matching the Boolean ABI of the sibling loaders.
// The final RET 8 at 0x0096D2B2 ends immediately before INT3 padding.
// read_dcg: RVA 0x0096D500, complete 773-byte body. Chunk 0x3B selects
// arm 0x0096FBB5; the call at 0x0096FBB9 reaches this body. It returns
// a Boolean in AL and ends with RET 8 at 0x0096D802, then INT3 padding.
// The matched MeshModel constructor establishes DefMatDesc at +0x94,
// AlternateMatDesc at +0x98, and CurMatDesc at +0x9C. Legacy vertex colors
// use CurMatDesc; the DCG reader starts with DefMatDesc.
// read_dig: RVA 0x0096D810, complete 809-byte body. Chunk 0x3C selects
// arm 0x0096FBC0, whose call at 0x0096FBC4 reaches this body. It ends
// with RET 8 at 0x0096DB36 and INT3 padding at 0x0096DB39.
// LoadedDIG at context+0x20C selects the alternate descriptor on repeat chunks.
// read_stage_texcoords: RVA 0x0096E690, complete 178-byte body. Texture-stage
// chunks 0x05 and 0x4A select the arm at 0x0096EDCB; its call at 0x0096EDCF
// reaches this loader. RET 8 at 0x0096E73F ends before INT3 at 0x0096E742.
// The original SimpleVecClass<Vector2> at context+0x200 provides the temporary
// array; its data pointer is at +0x204. The V conversion reads float 1.0f.
// read_texture_stage: RVA 0x0096ED60, full 247-byte compiler span. Material
// pass chunk 0x48 selects arm 0x0096FBCB, whose call at 0x0096FBCF reaches
// this body and checks AL against 1. RET 8 at +0x9A ends the executable code;
// the jump table (+0xA0..+0xAF) and selectors (+0xB0..+0xF6) belong to this
// function. INT3 padding starts at +0xF7. Per-face UV indices are skipped by
// the original inline length check and Seek; no separate body is claimed.
// Original semantic bodies: meshmdlio.cpp; BFME field views are local here.
#include "dx8wrapper.h"
#include "w3d_file.h"
#include "simplevec.h"
#include "vector2.h"
#include "vector3i.h"

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

class MeshMatDescClass
{
	int PassCount;
	int VertexCount;
	int PolyCount;
	void *UV[8];
	int UVSource[4][2];
	void *ColorArray[2];
	VertexMaterialClass::ColorSourceType DCGSource[4];
	VertexMaterialClass::ColorSourceType DIGSource[4];

public:
	bool Has_UV(int pass,int stage) { return UVSource[pass][stage] != -1; }
	void Install_UV_Array(int pass,int stage,Vector2 *uvs,int count);
	VertexMaterialClass::ColorSourceType Get_DCG_Source(int pass) { return DCGSource[pass]; }
	bool Has_Color_Array(int array) { return ColorArray[array] != 0; }
	unsigned *Get_Color_Array(int array,bool create = true);
	void Set_DCG_Source(int pass,VertexMaterialClass::ColorSourceType source)
	{
		DCGSource[pass] = source;
	}
};

class MeshLoadContextClass
{
	unsigned char prelit_padding[0x88];
public:
	unsigned long PrelitChunkID;
	int CurPass;
	int CurTexStage;
	unsigned char alternate_padding[0x10c - 0x94];
	MeshMatDescClass AlternateMatDesc;
	unsigned char temporary_uv_padding[0x200 - 0x10c - sizeof(MeshMatDescClass)];
	SimpleVecClass<Vector2> TempUVArray;
	bool LoadedDIG;

	Vector2 *Get_Temporary_UV_Array(int elementcount)
	{
		TempUVArray.Uninitialised_Grow(elementcount);
		return &TempUVArray[0];
	}

	bool Already_Loaded_DIG() { return LoadedDIG; }
	void Notify_Loaded_DIG_Chunk(bool loaded) { LoadedDIG = loaded; }
};

class MeshModelClass
{
	unsigned char geometry_padding[0x24];
	int PolyCount;
	int VertexCount;
	unsigned char material_padding[0x94 - 0x2c];
public:
	MeshMatDescClass *DefMatDesc;
	MeshMatDescClass *AlternateMatDesc;
	MeshMatDescClass *CurMatDesc;

	unsigned *Get_Color_Array(int array,bool create = true)
	{
		return CurMatDesc->Get_Color_Array(array,create);
	}

protected:
    bool read_texture_ids(ChunkLoadClass &cload,MeshLoadContextClass *context);
    bool read_per_face_texcoord_ids(ChunkLoadClass &cload,MeshLoadContextClass *context);
    bool read_texture_stage(ChunkLoadClass &cload,MeshLoadContextClass *context);
	bool read_stage_texcoords(ChunkLoadClass &cload,MeshLoadContextClass *context);
	bool read_dig(ChunkLoadClass &cload,MeshLoadContextClass *context);
	bool read_dcg(ChunkLoadClass &cload,MeshLoadContextClass *context);
	bool read_vertex_colors(ChunkLoadClass &cload,MeshLoadContextClass *context);
};

bool MeshModelClass::read_per_face_texcoord_ids(ChunkLoadClass &cload,MeshLoadContextClass *context)
{
    unsigned size = sizeof(Vector3i) * PolyCount;
    if (cload.Cur_Chunk_Length() == size) {
        cload.Seek(size);
        return true;
    }
    return false;
}

// MeshModelClass::read_vertex_colors is defined with its retail-matched body in Code/Libraries/Source/WWVegas/WW3D2/MeshModelReadVertexColors.cpp (0x00188760).
