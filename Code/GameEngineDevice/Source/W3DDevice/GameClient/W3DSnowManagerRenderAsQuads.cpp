// cl: /I. /Ireference/shims/sweep /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil
// stlport
/*
** Copyright 2025 Electronic Arts Inc.
** SPDX-License-Identifier: GPL-3.0-or-later
*/
// BFME1 W3DSnowManagerRenderAsQuads.cpp at cee35b7d8ca077d7255f1c39cb69e9fd9627aa85
// is the semantic donor. Retail 00093CC3..00094626 proves the 2403-byte body,
// target member offsets, wind drift, floor-based wrapping and D3D9 buffer ABI.
// WB 008B06C0 callgraph/algorithm supports the identity; its Vector3 assert label
// is not a function name. The rowed render caller supplies the existing name.
// The copied camera matrix is visible in WB. Full target Set_Transform semantics
// come from the verified Matrix3D overload at 0006A553, including projection.
// Keep wind together and the other locals in their natural scopes: MSVC 7.1
// then reproduces retail's stack homes. The box reference fixes SSE scheduling.
// Keep math.h's inline floorf local: retail's object exposes no _floorf.
extern "C" { static float __cdecl floorf(float); }
#include "reference/shims/bfme_matrix3d_sse_link/vector4.h"
#include "matrix3d.h"
#include "reference/shims/bfme_matrix4_rows_link/matrix4_bfme1_rows_link.h"
#include "vector2.h"
#include "vector3.h"
#include "wwmath.h"
#include <math.h>
#include "winbase_shim.h"
#include <d3d8.h>

#define MAXIMUM_CAMERA_DISTANCE 100000
#define MODPOW2(x,y) ((x) & (y-1))
enum { SNOW_NOISE_X = 64, SNOW_NOISE_Y = 64 };
#define SNOW_BATCH_SIZE 2048

#include "../../../../Libraries/Source/WWVegas/WW3D2/rendobj.h"

#include "../../../../Libraries/Source/WWVegas/WW3D2/CameraClass.h"

#define __PLACEMENT_VEC_NEW_INLINE  // always.h defines array placement-new itself
#include "../../../../Libraries/Source/WWVegas/WW3D2/RenderInfoClass.h"

class BaseHeightMapRenderObjClass;
extern BaseHeightMapRenderObjClass *TheTerrainRenderObject;

class IndexBufferClass;
class FVFInfoClass;
class VertexBufferClass;

struct VertexFormatXYZNDUV2
{
	float x;
	float y;
	float z;
	float nx;
	float ny;
	float nz;
	unsigned int diffuse;
	float u1;
	float v1;
	float u2;
	float v2;
};

class DynamicVBAccessClass
{
public:
	DynamicVBAccessClass(unsigned int type, unsigned int fvf, unsigned short vertex_count, unsigned int buffer);
	~DynamicVBAccessClass(void);

	struct WriteLock
	{
		DynamicVBAccessClass *DynamicVBAccess;
		VertexFormatXYZNDUV2 *Vertices;
		void *DeviceGuard;

		WriteLock(DynamicVBAccessClass *vb_access);
		~WriteLock(void);
		VertexFormatXYZNDUV2 *Get_Formatted_Vertex_Array(void) { return Vertices; }
	};

private:
	const FVFInfoClass *FVFInfo;
	unsigned int Type;
	unsigned int FormatIndex;
	unsigned int Declaration;
	unsigned short VertexCount;
	unsigned short VertexBufferOffset;
	VertexBufferClass *VertexBuffer;
};

extern unsigned number_of_DX8_calls;
#include "../../../../Libraries/Source/WWVegas/WW3D2/RenderStateStruct.h"
class DX8Wrapper
{
protected:
	static RenderStateStruct render_state;
	static unsigned render_state_changed;

public:
	enum {
		WORLD_CHANGED = 1 << 0,
		WORLD_IDENTITY = 1 << 18
	};

	static void Set_Index_Buffer(const IndexBufferClass *ib, unsigned short index_base_offset);
	static void Set_Vertex_Buffer(const DynamicVBAccessClass &vba);
	static void Draw_Triangles(unsigned int start_index, unsigned int polygon_count,
		unsigned int min_vertex_index, unsigned int vertex_count);

	protected:
	static IDirect3DDevice8 *D3DDevice;
	static unsigned matrix_changes;
	static float ZNear, ZFar;
	static Matrix4 ProjectionMatrix, DeviceProjectionMatrix;

	static IDirect3DDevice8 *_Get_D3D_Device8() { return D3DDevice; }
public:
	// Inline-only view: do not emit a competing shared transform/assignment body.
	static __declspec(dllimport) __forceinline void Set_Transform(D3DTRANSFORMSTATETYPE transform, const Matrix3D &m)
	{
		Matrix4 m2(m);
		switch ((int)transform) {
		case D3DTS_WORLD:
			render_state.world = m2.Transpose();
			render_state_changed |= (unsigned)WORLD_CHANGED;
			render_state_changed &= ~(unsigned)WORLD_IDENTITY;
			break;
		case D3DTS_VIEW:
			render_state.view = m2.Transpose();
			render_state_changed |= (unsigned)2;
			render_state_changed &= ~(unsigned)(1 << 19);
			break;
		case D3DTS_PROJECTION:
			ProjectionMatrix = m2.Transpose();
			DeviceProjectionMatrix = ProjectionMatrix;
			ZFar = 0.0f;
			ZNear = 0.0f;
			D3DDevice->SetTransform(D3DTS_PROJECTION, (D3DMATRIX *)&DeviceProjectionMatrix);
			number_of_DX8_calls++;
			break;
		default:
			matrix_changes++;
			m2 = m2.Transpose();
			_Get_D3D_Device8()->SetTransform(transform, (D3DMATRIX *)&m2);
			number_of_DX8_calls++;
			break;
		}
	}
};

class W3DSnowManager
{
public:
	void renderAsQuads(RenderInfoClass &rinfo, int cubeOriginX, int cubeOriginY, int cubeDimX, int cubeDimY);
	float rva000932E1(void);	// the weather float helper 0x000932E1

private:
	char m_pad00[0x0C];
	float *m_startingHeights;	// +0x0C
	float m_time;	// +0x10
	float m_velocity;	// +0x14
	float m_fullTimePeriod;	// +0x18
	float m_frequencyScaleX;	// +0x1C
	float m_frequencyScaleY;	// +0x20
	float m_amplitude;	// +0x24
	float m_pointSize;	// +0x28
	float m_maxPointSize;	// +0x2C
	float m_minPointSize;	// +0x30
	float m_quadSize;	// +0x34
	float m_boxDimensions;	// +0x38
	float m_emitterSpacing;	// +0x3C
	unsigned char m_isVisible;	// +0x40
	unsigned char m_flag3D;	// +0x41
	char m_pad42[0x44 - 0x42];
	int m_tiles;	// +0x44
	float m_windX;	// +0x48
	float m_windY;	// +0x4C
	char m_pad50[0x74 - 0x50];
	IndexBufferClass *m_indexBuffer;	// +0x74
	char m_pad78[0x90 - 0x78];
	float m_snowCeiling;	// +0x90
	float m_heightTraveled;	// +0x94
	float m_originX;	// +0x98
	float m_originY;	// +0x9C
	int m_totalRendered;	// +0xA0
	float m_cullOverscan;	// +0xA4
	int m_A8;	// +0xA8
	int m_randomGray;	// +0xAC
};

void W3DSnowManager::renderAsQuads(RenderInfoClass &rinfo, int cubeOriginX, int cubeOriginY, int cubeDimX, int cubeDimY)
{
	Matrix3D view;
	Vector3 snowCenter;

	CameraClass &camera = rinfo.Camera;
	camera.Get_View_Matrix(&view);

	Matrix3D ctm = camera.Get_Transform();
	Vector3 right;
	right.X = ctm[0][0];
	right.Y = ctm[1][0];
	right.Z = ctm[2][0];
	Vector3 up(0.0f, 0.0f, 1.0f);
	Vector3 vertex_offsets[4] = {
		-right + up,
		-right - up,
		right - up,
		right + up
	};
	Vector2 quad_uvs[4] = {
		Vector2(0.0f, 0.0f),
		Vector2(0.0f, 1.0f),
		Vector2(1.0f, 1.0f),
		Vector2(1.0f, 0.0f)
	};

	int i = 0;
	do {
		vertex_offsets[i] *= m_quadSize * 0.707f;
	} while (++i < 4);

	Matrix3D terrainTm = ((RenderObjClass *)TheTerrainRenderObject)->Get_Transform();
	DX8Wrapper::Set_Transform(D3DTS_WORLD, terrainTm);
	DX8Wrapper::Set_Index_Buffer(m_indexBuffer, 0);

	Vector2 wind;
	int tiles = m_tiles;
	if (tiles < 1)
		tiles = 1;
	int stepX = (cubeDimX - cubeOriginX) / tiles;
	int stepY = (cubeDimY - cubeOriginY) / tiles;
	int y = cubeOriginY;
	int cubeOriginXRemainder = cubeOriginX;
	int endY = cubeOriginY + stepY;
	int endX = cubeOriginX + stepX;
	int totalPart = stepY * stepX;
	int spacing = (int)m_emitterSpacing;
	if (spacing < 1)
		spacing = 1;
	totalPart /= spacing * spacing;
	m_totalRendered += totalPart;

	int gray;
	if (m_randomGray)
		gray = (int)(rva000932E1() * 255.0f);
	else
		gray = 255;
	unsigned int color = gray * 0x10101 + 0xFF000000;

	float windScale = m_boxDimensions / m_velocity;
	wind.X = m_windX * windScale;
	wind.Y = m_windY * windScale;

	while (totalPart)
	{
		int batchSize = totalPart;
		if (batchSize > SNOW_BATCH_SIZE)
			batchSize = SNOW_BATCH_SIZE;

		int numberInBatch = 0;
/* visibility sweep: declaration removed */

		DynamicVBAccessClass vb_access(2, 5, batchSize * 4, 0);
		{
			DynamicVBAccessClass::WriteLock lock(&vb_access);
			VertexFormatXYZNDUV2 *verts = lock.Get_Formatted_Vertex_Array();

			for (; y < endY; y += spacing)
			{
				for (int x = cubeOriginXRemainder; x < endX; x += spacing)
				{
					if (numberInBatch >= batchSize)
					{
						cubeOriginXRemainder = x;
						goto flush_particles;
					}
					int noiseOffset = MODPOW2(x + MAXIMUM_CAMERA_DISTANCE, SNOW_NOISE_X) +
						MODPOW2(y + MAXIMUM_CAMERA_DISTANCE, SNOW_NOISE_Y) * SNOW_NOISE_X;
					if (noiseOffset > SNOW_NOISE_X * SNOW_NOISE_Y)
						noiseOffset = 0;
					float height = m_startingHeights[noiseOffset] + m_heightTraveled;
					float cycles = floorf(height / m_boxDimensions);
					// Preserve the member reference across the wrap calculation.
					const float &box = m_boxDimensions;
					float h0 = m_snowCeiling - (height - box * cycles);
					snowCenter = Vector3((float)x, (float)y, h0);
					if (m_amplitude > 0.0f)
					{
						snowCenter.X += m_amplitude * WWMath::Fast_Sin(h0 * m_frequencyScaleX + (float)x);
						snowCenter.Y += m_amplitude * WWMath::Fast_Sin(h0 * m_frequencyScaleY + (float)y);
					}
					snowCenter.X = m_originX - cycles * wind.X + snowCenter.X;
					snowCenter.Y = m_originY - cycles * wind.Y + snowCenter.Y;
					i = 0;
					do
					{
						*(Vector3 *)verts = snowCenter + vertex_offsets[i];
						verts->nx = 0;
						verts->ny = 0;
						verts->nz = 0;
						verts->diffuse = color;
						verts->u1 = quad_uvs[i].X;
						verts->v1 = quad_uvs[i].Y;
						verts->u2 = 0;
						verts->v2 = 0;
						verts++;
					} while (++i < 4);
					numberInBatch++;
				}
				cubeOriginXRemainder = cubeOriginX;
			}
flush_particles:
			;
		}

		if (numberInBatch)
		{
			DX8Wrapper::Set_Vertex_Buffer(vb_access);
			Matrix3D tm = terrainTm;
			for (i = 0; i < tiles; i++)
			{
				for (int j = 0; j < tiles; j++)
				{
					Vector3 pos = terrainTm.Get_Translation();
					pos += Vector3((float)(j * stepX), (float)(i * stepY), 0.0f);
					tm.Set_Translation(pos);
					DX8Wrapper::Set_Transform(D3DTS_WORLD, tm);
					DX8Wrapper::Draw_Triangles(0, numberInBatch * 2, 0, numberInBatch * 4);
				}
			}
			totalPart -= numberInBatch;
		}
	}
}
