// cl: /Ireference/shims/bfmestages /DBFME_WWSTRING_NATIVE_CSTR_ASSIGN /Ireference/shims/wwstring_teardown/zhmd /arch:SSE /G7 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
// platformsdk
// dxsdk
// The compiler-generated vector constructor iterator (??_H) takes the
// optimization state of the first function that needs it; retail links the
// /O1 body at 0x00001423. Instantiate it first in an unemitted anchor (the
// lookuptable.cpp pattern) so this unit's copy is that body.
struct BfmeVciAnchorElem { BfmeVciAnchorElem(); };
#pragma optimize("gsy", on)
static void bfmeVciAnchor() { BfmeVciAnchorElem anchor[2]; (void)anchor; }
// RefCountClass's inline members and deleting destructor are retail's
// size-optimised bodies: compile them for size, as hlod.cpp does.
#include "refcount.h"
#pragma optimize("", on)
#include <math.h>
// Link view first: Vector3 Length/Normalize/ctor and the scalar operator* stay inline without emitting
// /O2 copies that compete with retail's owners (0x000692B3, 0x0006924F, 0x006CD510, 0x00066382, 0x0007DFB3).
#include "../../../../../reference/shims/bfme_vector3_full_link/vector3_full_link.h"
// Link view first: Matrix3D(), Matrix3D(bool) and Matrix3D(const Matrix3D&) stay inline without
// emitting /O2 copies that compete with retail's owners (0x000423C5, 0x0004C91A, 0x0006645C).
#include "../../../../../reference/shims/bfme_matrix3d_full_link/matrix3d_full_link.h"
// Link view first: Vector4(x,y,z,w) stays inline without emitting an SSE
// copy that competes with retail's integer-move owner (0x006D8A30).
#include "../../../../../reference/shims/bfme_matrix3d_sse_link/vector4.h"
// stlport
#define Matrix4x4 Matrix4  // BFME renamed it
// Link view: Matrix4(Vector4 x4), Transpose and the Matrix3D overloads stay inline without emitting
// non-/O1 copies that lose to retail's owners (0x0006A34E, 0x0006A3D1).
#include "../../../../../reference/shims/bfme_matrix4_rows_link/matrix4_zh_rows_link.h"
// Retail deallocation cannot throw; keep member cleanup outside an EH frame.
void operator delete[](void*) throw();
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

/***********************************************************************************************
 ***              EA PACIFIC CONFIDENTIAL              ***
 ***********************************************************************************************
 *                                                                                             *
 *              Original Author:: Mark Lorenzen                                                *
 *                                                                                             *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */


#include "../../../../../reference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2/texture.h"
#include "../../../../../reference/shims/bfmestreak/streakrender.h"
#include "ww3d.h"
#include "rinfo.h"
#include "dx8wrapper.h"
#include "sortingrenderer.h"
#include "vp.h"
#include "vector3i.h"
#include "random.h"
#include "../../../../../reference/shims/bfme_randomizer_dtor/v3_rnd.h"

#ifdef _INTERNAL
// for occasional debugging...
// #pragma optimize("", off)
// #pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif

/* We have chunking logic which handles N segments at a time. To simplify the subdivision logic,
** we will ensure that N is a power of two and that N >= 2^MAX_STREAK_SUBDIV_LEVELS, so that the
** subdivision logic can be inside the chunking loop.
*/

#if MAX_STREAK_SUBDIV_LEVELS > 7
#define STREAK_CHUNK_SIZE (1 << MAX_STREAK_SUBDIV_LEVELS)
#else
#define STREAK_CHUNK_SIZE (128)
#endif

#define MAX_STREAK_POINT_BUFFER_SIZE (1 + STREAK_CHUNK_SIZE)
// This macro depends on the assumption that each line segment is two polys.
#define MAX_STREAK_POLY_BUFFER_SIZE (STREAK_CHUNK_SIZE * 2)




StreakRendererClass::StreakRendererClass(void) :
		Texture(NULL),
		Shader(ShaderClass::_PresetAdditiveSpriteShader),
		Width(0.0f),
		Color(Vector3(1,1,1)),
		Opacity(1.0f),
		SubdivisionLevel(0),
		NoiseAmplitude(0.0f),
		MergeAbortFactor(1.5f),
		TextureTileFactor(1.0f),
		LastUsedSyncTime(WW3D::Get_Sync_Time()),
		CurrentUVOffset(0.0f,0.0f),
		UVOffsetDeltaPerMS(0.0f, 0.0f),
		Bits(DEFAULT_BITS),
		m_vertexBufferSize(0),
		m_vertexBuffer(NULL)
{
  // EMPTY
}

StreakRendererClass::StreakRendererClass(const StreakRendererClass & that) :
		Texture(NULL),
		Shader(ShaderClass::_PresetAdditiveSpriteShader),
		Width(0.0f),
		Color(Vector3(1,1,1)),
		Opacity(1.0f),
		SubdivisionLevel(0),
		NoiseAmplitude(0.0f),
		MergeAbortFactor(1.5f),
		TextureTileFactor(1.0f),
		LastUsedSyncTime(that.LastUsedSyncTime),
		CurrentUVOffset(0.0f,0.0f),
		UVOffsetDeltaPerMS(0.0f, 0.0f),
		Bits(DEFAULT_BITS),
		m_vertexBufferSize(0),
		m_vertexBuffer(NULL)
{
	*this = that;
}

StreakRendererClass & StreakRendererClass::operator = (const StreakRendererClass & that)
{
	if (this != &that) {
		Texture = that.Texture;
		Shader = that.Shader;
		Width = that.Width;
		Color = that.Color;
		Opacity = that.Opacity;
		SubdivisionLevel = that.SubdivisionLevel;
		NoiseAmplitude = that.NoiseAmplitude;
		MergeAbortFactor = that.MergeAbortFactor;
		TextureTileFactor = that.TextureTileFactor;
		LastUsedSyncTime = that.LastUsedSyncTime;
		CurrentUVOffset = that.CurrentUVOffset;
		UVOffsetDeltaPerMS = that.UVOffsetDeltaPerMS;
		Bits = that.Bits;
		// Don't modify m_vertexBufferSize and m_vertexBuffer.
	}
	return *this;
}

StreakRendererClass::~StreakRendererClass(void)
{
	delete [] m_vertexBuffer;
}

// StreakRendererClass::Init: defined with its retail body in StreakRendererInit.cpp (its row's unit).
// Anchor only: the retail Init body lives in StreakRendererInit.cpp; this keeps
// the rowed out-of-line setters below emitted from this unit. Not retail code.
// ?_bfmeStreakRenderSetterAnchor absent-from-retail
void _bfmeStreakRenderSetterAnchor(StreakRendererClass &streakRenderer, const W3dEmitterLinePropertiesStruct & props)
{
	// translate the flags
	streakRenderer.Set_Merge_Intersections(props.Flags & W3D_ELINE_MERGE_INTERSECTIONS);
	streakRenderer.Set_Freeze_Random(props.Flags & W3D_ELINE_FREEZE_RANDOM);
	streakRenderer.Set_Disable_Sorting(props.Flags & W3D_ELINE_DISABLE_SORTING);
	streakRenderer.Set_End_Caps(props.Flags & W3D_ELINE_END_CAPS);

	int texture_mode = ((props.Flags & W3D_ELINE_TEXTURE_MAP_MODE_MASK) >> W3D_ELINE_TEXTURE_MAP_MODE_OFFSET);
	switch (texture_mode) 
	{
	case W3D_ELINE_UNIFORM_WIDTH_TEXTURE_MAP:
		streakRenderer.Set_Texture_Mapping_Mode(StreakRendererClass::UNIFORM_WIDTH_TEXTURE_MAP);
		break;
	case W3D_ELINE_UNIFORM_LENGTH_TEXTURE_MAP:
		streakRenderer.Set_Texture_Mapping_Mode(StreakRendererClass::UNIFORM_LENGTH_TEXTURE_MAP);		
		break;
	case W3D_ELINE_TILED_TEXTURE_MAP:
		streakRenderer.Set_Texture_Mapping_Mode(StreakRendererClass::TILED_TEXTURE_MAP);		
		break;
	};

	// install all other settings
	streakRenderer.Set_Current_Subdivision_Level(props.SubdivisionLevel);
	streakRenderer.Set_Noise_Amplitude(props.NoiseAmplitude);
	streakRenderer.Set_Merge_Abort_Factor(props.MergeAbortFactor);
	// Set_Texture_Tile_Factor(props.TextureTileFactor);
	// Set_UV_Offset_Rate(Vector2(props.UPerSec,props.VPerSec));
}


// StreakRendererClass::Set_Texture: defined in StreakRendererSetTextureBFME1.cpp (its row's unit).

// ?Get_Texture@StreakRendererClass@@QBEPAVTextureClass@@XZ present-unmatched
TextureClass * StreakRendererClass::Get_Texture(void) const
{
	if (Texture != NULL) {
		Texture->Add_Ref();
	}
	return Texture.Peek();
}

// void StreakRendererClass::Set_Current_UV_Offset(const Vector2 & offset)
// {
// 	CurrentUVOffset = offset;
// }

// void StreakRendererClass::Set_Texture_Tile_Factor(float factor)
// {
// 	if (factor > 8.0f) {
//		factor = 8.0f;
//		WWDEBUG_SAY(("Texture Tile Factor too large in StreakRendererClass!\r\n"));
//	} else {
//		factor = MAX(factor, 0.0f);
//	}
//	TextureTileFactor = factor;
//}

// void StreakRendererClass::Reset_Line(void)
// {
	// LastUsedSyncTime = WW3D::Get_Sync_Time();
	// CurrentUVOffset.Set(0.0f,0.0f);
// }

///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
void StreakRendererClass::Render
(	
	RenderInfoClass & rinfo,
	const Matrix3D & transform,
	unsigned int num_points,
	Vector3 * points,
	const SphereClass & obj_sphere
)
{
	//NOTHING!
	return;
}

///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////




__declspec(noinline) inline void StreakRendererClass::subdivision_util(unsigned int point_cnt, const Vector3 *xformed_pts,
	const float *base_tex_v, unsigned int *p_sub_point_cnt, Vector3 *xformed_subdiv_pts,
	float *subdiv_tex_v)
{
	// CAUTION: freezing the random offsets will make it more readily apparent that the offsets
	// are in camera space rather than worldspace.
	struct StreakRendererRetailLayout {
		TextureClass *Texture;
		ShaderClass Shader;
		float Width;
		Vector3 Color;
		float Opacity;
		unsigned int SubdivisionLevel;
		float NoiseAmplitude;
		float MergeAbortFactor;
		float TextureTileFactor;
		unsigned int LastUsedSyncTime;
		Vector2 CurrentUVOffset;
		Vector2 UVOffsetDeltaPerMS;
		unsigned int Bits;
	};
	const StreakRendererRetailLayout *retail_this =
		reinterpret_cast<const StreakRendererRetailLayout *>(this);
	int freeze_random = retail_this->Bits & FREEZE_RANDOM;
	Random3Class randomize;
	const float oo_int_max = 1.0f / (float)INT_MAX;
	Vector3SolidBoxRandomizer randomizer(Vector3(1,1,1));
	Vector3 randvec(0,0,0);
	unsigned int sub_pointIndex = 0;

	struct StreakSubdivision {
		Vector3			StartPos;
		Vector3			EndPos;
		float				StartTexV;	// V texture coordinate of start point
		float				EndTexV;		// V texture coordinate of end point
		float				Rand;
		unsigned int	Level;		// Subdivision level
	};

	StreakSubdivision stack[2 * MAX_STREAK_SUBDIV_LEVELS];	// Maximum number needed
	int tos = 0;

	for (unsigned int pointIndex = 0; pointIndex < point_cnt - 1; pointIndex++) {

		// Subdivide the (pointIndex, pointIndex + 1) segment. Produce pointIndex and all subdivided points up to
		// (not including) pointIndex + 1.
		tos = 0;
		stack[0].StartPos = xformed_pts[pointIndex];
		stack[0].EndPos = xformed_pts[pointIndex + 1];
		stack[0].StartTexV = base_tex_v[pointIndex];
		stack[0].EndTexV = base_tex_v[pointIndex + 1];
		stack[0].Rand = NoiseAmplitude;
		stack[0].Level = 0;

		for (; tos >= 0;) {
			if (stack[tos].Level == SubdivisionLevel) {
				// Generate point location and texture V coordinate
				xformed_subdiv_pts[sub_pointIndex] = stack[tos].StartPos;
				subdiv_tex_v[sub_pointIndex++] = stack[tos].StartTexV;

				// Pop
				tos--;
			} else {
				// Recurse down: pop existing entry and push two subdivided ones.
				if (freeze_random) {
					randvec.Set(randomize * oo_int_max, randomize * oo_int_max, randomize * oo_int_max);
				} else {
					randomizer.Get_Vector(randvec);
				}
				stack[tos + 1].StartPos = stack[tos].StartPos;
				stack[tos + 1].EndPos = (stack[tos].StartPos + stack[tos].EndPos) * 0.5f + randvec * stack[tos].Rand;
				stack[tos + 1].StartTexV = stack[tos].StartTexV;
				stack[tos + 1].EndTexV = (stack[tos].StartTexV + stack[tos].EndTexV) * 0.5f;
				stack[tos + 1].Rand = stack[tos].Rand * 0.5f;
				stack[tos + 1].Level = stack[tos].Level + 1;
				stack[tos].StartPos = stack[tos + 1].EndPos;
				// stack[tos].EndPos already has the right value
				stack[tos].StartTexV = stack[tos + 1].EndTexV;
				// stack[tos].EndTexV already has the right value
				stack[tos].Rand = stack[tos + 1].Rand;
				stack[tos].Level = stack[tos + 1].Level;
				tos++;
			}
		}
	}
	// Last point
	xformed_subdiv_pts[sub_pointIndex] = xformed_pts[point_cnt - 1];
	subdiv_tex_v[sub_pointIndex++] = base_tex_v[point_cnt - 1];

	// Output:
	*p_sub_point_cnt = sub_pointIndex;
}


// byte-exact reconstruction: Code/Libraries/Source/WWVegas/WW3D2/StreakRendererClass_getVertexBuffer_Thunk.cpp
// ?getVertexBuffer@StreakRendererClass@@AAEPAUVertexFormatXYZUV1@@I@Z
__declspec(noinline) inline VertexFormatXYZUV1 *StreakRendererClass::getVertexBuffer(unsigned int number)
{
	// TODO: use a stl vector instead of our own array.
	if (number > m_vertexBufferSize)
	{
		unsigned int numberToAlloc = number + (number >> 1);
	  delete [] m_vertexBuffer;
		m_vertexBuffer = W3DNEWARRAY VertexFormatXYZUV1[numberToAlloc];		
		m_vertexBufferSize = numberToAlloc;
	}

#ifdef _INTERNAL
	for (unsigned i = 0; i < number; ++i)
	{
	  m_vertexBuffer[i].x = m_vertexBuffer[i].y = m_vertexBuffer[i].z = m_vertexBuffer[i].u1 = m_vertexBuffer[i].v1 = (float)0xdeadbeef;
	}
#endif

	return m_vertexBuffer;
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:??1MaterialPassStage@@QAE@XZ=??1?$RefCountPtr@VTextureClass@@@@QAE@XZ")
#pragma comment(linker, "/alternatename:??1TextureClassPtr@@QAE@XZ=??1?$RefCountPtr@VTextureClass@@@@QAE@XZ")
#pragma comment(linker, "/alternatename:??1BfmeElemVVE@@QAE@XZ=??1?$RefCountPtr@VTextureClass@@@@QAE@XZ")
#pragma comment(linker, "/alternatename:??1BfmeElementA@@QAE@XZ=??1?$RefCountPtr@VTextureClass@@@@QAE@XZ")
#pragma comment(linker, "/alternatename:?bfmeElem936B@@YGXPAX@Z=??1?$RefCountPtr@VTextureClass@@@@QAE@XZ")

// Keep the rowed matrix and property inlines emitted.
// ?bfmeStreakMathAnchor absent-from-retail
void bfmeStreakMathAnchor(Matrix3D &out, const Matrix3D &a, const Matrix3D &b,
    const StreakRendererClass &streak, int &merge, int &sorting,
    StreakRendererClass::TextureMapMode &mode)
{
    out.mul(a, b);
    merge = streak.Is_Merge_Intersections();
    sorting = streak.Is_Sorting_Disabled();
    mode = streak.Get_Texture_Mapping_Mode();
}

// Keep the rowed private helper definitions emitted from their owner.
// ?bfmeStreakVertexBufferAnchor absent-from-retail
template <VertexFormatXYZUV1 *(StreakRendererClass::*Member)(unsigned)>
VertexFormatXYZUV1 *bfmeStreakVertexBufferAnchor(StreakRendererClass &streak, unsigned count)
{
    return (streak.*Member)(count);
}
template VertexFormatXYZUV1 *bfmeStreakVertexBufferAnchor<&StreakRendererClass::getVertexBuffer>(StreakRendererClass &, unsigned);

// ?bfmeStreakSubdivisionAnchor absent-from-retail
template <void (StreakRendererClass::*Member)(unsigned, const Vector3 *, const float *, unsigned *, Vector3 *, float *)>
void bfmeStreakSubdivisionAnchor(StreakRendererClass &streak, unsigned count,
    const Vector3 *points, const float *tex, unsigned *sub_count, Vector3 *sub_points, float *sub_tex)
{
    (streak.*Member)(count, points, tex, sub_count, sub_points, sub_tex);
}
template void bfmeStreakSubdivisionAnchor<&StreakRendererClass::subdivision_util>(StreakRendererClass &, unsigned,
    const Vector3 *, const float *, unsigned *, Vector3 *, float *);
