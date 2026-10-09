// ?renderAsQuads@W3DSnowManager@@QAEXAAVRenderInfoClass@@HHHH@Z
// partial score=0.9 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas
//
// ?renderAsQuads@W3DSnowManager@@QAEXAAVRenderInfoClass@@HHHH@Z, retail
// 0x00093CC3 (2403 bytes, RET 0x14 with an EH frame).  Ported from
// Open-BFME-1's W3DSnowManagerRenderAsQuads.cpp (BFME 1 retail 0x00724A20):
// world-space quads from the camera's X axis and world up scaled by
// m_quadSize*0.707f, the terrain transform as world transform, noise-table
// heights, inlined WWMath::Fast_Sin sway, a grey diffuse from the random
// gate, one filled tile redrawn once per tile of the m_tiles x m_tiles grid.
// BFME 2 differences read from retail: the members sit 4 bytes further
// (vtable), the tile count is +0x44, the index buffer +0x74, the snow
// ceiling/height traveled +0x90/+0x94, m_totalRendered +0xA0 and the random
// gate +0xAC; the height wrap is open-coded with floorf instead of fmod and
// the wrap count drifts every flake by the +0x98/+0x9C origin minus the
// +0x48/+0x4C wind scaled by m_boxDimensions/m_velocity.
// NEAR (banked, not landed): 2407 of 2403 bytes, score ~0.95.  Every branch,
// call, constant and frame object matches retail (frame 0x16C, view -0x178,
// vb_access -0x148, the loop Matrix4 of the inlined DX8Wrapper::Set_Transform
// at -0x130 with its rotation stores hoisted ahead of the tile loops, exactly as
// retail).  Remaining differences are allocation only:
//  - tile loop: retail folds the terrain X translation into
//    `cvtsi2ss xmm1,[ebp+0x10]; addss xmm1,[ebp-0x54]` and loads tz early;
//    this body loads tx into xmm1 and adds the converted offset later (+4 bytes);
//  - spill-slot permutation: retail -0x18/-0x1C and -0x2C/-0x30 are swapped
//    here (Fast_Sin temps vs verts/batchSize), and stepY/stepX/Fast_Sin
//    spills/color/wind sit in a different order at -0x68..-0x84.
// Shapes tried without gain: tm inside/outside the loops, Adjust_Translation,
// Set_X/Y_Translation, Get_Translation(&pos), the real BFME 1 dx8wrapper.h
// header (identical result), wind as Vector2/Vector3, decl-order changes.
// Dead code inside the inlined Set_Transform switch changes the tie-breaks, so
// keep it exactly as written here.
#include "matrix3d.h"
#include "matrix4.h"
#include "vector2.h"
#include "vector3.h"
#include "wwmath.h"
#include <math.h>

#define MAXIMUM_CAMERA_DISTANCE 100000
#define MODPOW2(x,y) ((x) & (y-1))
enum { SNOW_NOISE_X = 64, SNOW_NOISE_Y = 64 };
#define SNOW_BATCH_SIZE 2048

class RenderObjClass
{
public:
	virtual void slot00(void);
	virtual void slot04(void);
	virtual void slot08(void);
	virtual void slot0C(void);
	virtual void slot10(void);
	virtual void slot14(void);
	virtual void slot18(void);
	virtual void slot1C(void);
	virtual void slot20(void);
	virtual void slot24(void);
	virtual void slot28(void);
	virtual void slot2C(void);
	virtual void slot30(void);
	virtual void slot34(void);
	virtual void slot38(void);
	virtual void slot3C(void);
	virtual void slot40(void);
	virtual void slot44(void);
	virtual void slot48(void);
	virtual void slot4C(void);
	virtual void Validate_Transform(void) const;	// slot 0x50

	const Matrix3D &Get_Transform(void) const
	{
		Validate_Transform();
		return Transform;
	}

private:
	char m_pad04[0x18 - 4];
	Matrix3D Transform;	// +0x18
};

class CameraClass : public RenderObjClass
{
public:
	void Get_View_Matrix(Matrix3D *set_tm);
};

class RenderInfoClass
{
public:
	CameraClass &Camera;
};

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
class DX8Wrapper
{
	static Matrix4 render_state_world;
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

	struct Dev { virtual long __stdcall SetTransform(int, const Matrix4 *) = 0; };
	static Dev *D3DDevice;
	static unsigned matrix_changes;
	static Matrix4 render_state_view;
	static Dev *_Get_D3D_Device8() { return D3DDevice; }
	static __forceinline void Set_Transform(int transform, const Matrix3D &m)
	{
		Matrix4 m2(m);
		switch (transform) {
		case 256:
			render_state_world = m2.Transpose();
			render_state_changed |= (unsigned)WORLD_CHANGED;
			render_state_changed &= ~(unsigned)WORLD_IDENTITY;
			break;
		case 2:
			render_state_view = m2.Transpose();
			render_state_changed |= (unsigned)2;
			render_state_changed &= ~(unsigned)(1 << 19);
			break;
		default:
			matrix_changes++;
			m2 = m2.Transpose();
			_Get_D3D_Device8()->SetTransform(transform, &m2);
			number_of_DX8_calls++;
			break;
		}
	}
};

// The random helper 0x000932E1 on this W3DSnowManager, rowed under its address.
class Rva000932E1
{
public:
	float rva000932E1(void);
};

class W3DSnowManager
{
public:
	void renderAsQuads(RenderInfoClass &rinfo, int cubeOriginX, int cubeOriginY, int cubeDimX, int cubeDimY);

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

	const Matrix3D &ctm = camera.Get_Transform();
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
	DX8Wrapper::Set_Transform(256, terrainTm);
	DX8Wrapper::Set_Index_Buffer(m_indexBuffer, 0);

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
		gray = (int)(((Rva000932E1 *)this)->rva000932E1() * 255.0f);
	else
		gray = 255;
	unsigned int color = gray * 0x10101 + 0xFF000000;

	float windScale = m_boxDimensions / m_velocity;
	float windX = m_windX * windScale;
	float windY = m_windY * windScale;

	while (totalPart)
	{
		int batchSize = totalPart;
		if (batchSize > SNOW_BATCH_SIZE)
			batchSize = SNOW_BATCH_SIZE;

		int numberInBatch = 0;
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
					float h0 = m_snowCeiling - (height - m_boxDimensions * cycles);
					snowCenter = Vector3((float)x, (float)y, h0);
					if (m_amplitude > 0.0f)
					{
						snowCenter.X += m_amplitude * WWMath::Fast_Sin(h0 * m_frequencyScaleX + (float)x);
						snowCenter.Y += m_amplitude * WWMath::Fast_Sin(h0 * m_frequencyScaleY + (float)y);
					}
					snowCenter.X = m_originX - cycles * windX + snowCenter.X;
					snowCenter.Y = m_originY - cycles * windY + snowCenter.Y;
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
					DX8Wrapper::Set_Transform(256, tm);
					DX8Wrapper::Draw_Triangles(0, numberInBatch * 2, 0, numberInBatch * 4);
				}
			}
			totalPart -= numberInBatch;
		}
	}
}
