// ?updateScorches@BaseHeightMapRenderObjClass@@QAEXXZ
// partial score=0.8 date=2026-10-10
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
// stlport
// ?updateScorches@BaseHeightMapRenderObjClass@@QAEXXZ, retail 0x000678BB..
// 0x00067E8E (1491 bytes). Zero Hour's BaseHeightMapRenderObjClass::updateScorches
// (BaseHeightMap.cpp) with the BFME changes the retail body shows; the skeleton
// is the BFME 1 port (Open-BFME-1 575ba2b04 BaseHeightMapUpdateScorches.cpp:
// skipped scorches via the flag byte, border read once before the locks,
// 16-bit heights, a vertex-budget rollback). BFME 2 target evidence: the
// shade is ambient + diffuse-times-scale / 2 scaled by 2 under shader
// overbright and clamped to 1, UVs span the scorch's own quad grid in 1/3
// atlas cells, heights are ushort * 0.0390625 + 1.
// Entry stride 0x1C at +0xE0 (as addScorch), counts at +0x3790/+0x3794.

typedef int Int;
typedef float Real;
typedef bool Bool;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;
typedef unsigned int UnsignedInt;

#include <math.h>
#include "wwmath.h"

struct VertexFormatXYZDUV1
{
	Real x, y, z;
	UnsignedInt diffuse;
	Real u1, v1;
};

struct RGBColor
{
	Real red, green, blue;
};

class GlobalData
{
public:
	unsigned char m_pad000[0x8D8];
	RGBColor m_terrainAmbient[3];		// +0x8D8
	RGBColor m_terrainDiffuse[3];		// +0x8FC
	unsigned char m_pad920[0x944 - 0x920];
	RGBColor m_scale944;			// +0x944
};
extern GlobalData *TheWritableGlobalData;
extern bool ShaderOverbrightEnabled;

class VertexBufferClass
{
public:
	class WriteLockClass
	{
	public:
		WriteLockClass(VertexBufferClass *vertex_buffer, int flags);
		~WriteLockClass();
		void *Get_Vertex_Array() { return Vertices; }
	private:
		VertexBufferClass *VertexBuffer;
		void *Vertices;
		int m_08;
	};
};

class IndexBufferClass
{
public:
	class WriteLockClass
	{
	public:
		WriteLockClass(IndexBufferClass *index_buffer, int flags);
		~WriteLockClass();
		UnsignedShort *Get_Index_Array() { return Indices; }
	private:
		IndexBufferClass *IndexBuffer;
		UnsignedShort *Indices;
		int m_08;
	};
};

// The world height map view retail reads: border at +0x10, extents at +8/+0xC;
// 0x0006653B is its clamped 16-bit height lookup, 0x004ADF41 the flip-state query.
class Rva0006653B
{
public:
	UnsignedShort rva0006653B(Int x, Int y);
	char m_pad00[8];
	Int m_xExtent;
	Int m_yExtent;
	Int m_border;
};

class Gen_0074B410
{
public:
	bool bfmeBitA(int x, int y) const;
};

class Vector3
{
public:
	Real X, Y, Z;
	Vector3() {}
	__forceinline Vector3(const Vector3 &v) : X(v.X), Y(v.Y), Z(v.Z) {}
};

struct BFMEScorchEntry
{
	char m_pad00[4];
	Vector3 location;
	Real radius;
	Int scorchType;
	UnsignedByte flag;
	char m_pad19[3];
};

#define SCORCH_MARKS_IN_TEXTURE 9
#define SCORCH_PER_ROW 3
#define MAX_SCORCH_VERTEX 8194
#define MAX_SCORCH_INDEX 49164
#define BFME_MAP_XY_FACTOR 10.0f

static inline Real bfmeFloorD(Real f) { double d = floor(f); return (Real)d; }
static inline Real bfmeCeilD(Real f) { double d = ceil(f); return (Real)d; }

class BaseHeightMapRenderObjClass
{
public:
	void updateScorches();

private:
	UnsignedByte m_pad00[0xCC];
	VertexBufferClass *m_vertexScorch;	// +0xCC
	IndexBufferClass *m_indexScorch;	// +0xD0
	void *m_scorchTexture;			// +0xD4
	Int m_curNumScorchVertices;		// +0xD8
	Int m_curNumScorchIndices;		// +0xDC
	BFMEScorchEntry m_scorches[500];	// +0xE0
	Int m_numScorches;			// +0x3790
	Int m_scorchesInBuffer;			// +0x3794
	Int m_nextScorch;			// +0x3798
	UnsignedByte m_pad379C[0x37C0 - 0x379C];
	Rva0006653B *m_map;			// +0x37C0
};

void BaseHeightMapRenderObjClass::updateScorches()
{
	if (m_scorchesInBuffer > 1) {
		return;
	}
	if (m_numScorches == 0) {
		return;
	}
	if (!m_indexScorch || !m_vertexScorch) {
		return;
	}
	m_scorchesInBuffer = 0;
	m_curNumScorchVertices = 0;
	m_curNumScorchIndices = 0;

	Real shadeR, shadeG, shadeB;
	shadeR = TheWritableGlobalData->m_scale944.red * TheWritableGlobalData->m_terrainDiffuse[0].red;
	shadeG = TheWritableGlobalData->m_scale944.green * TheWritableGlobalData->m_terrainDiffuse[0].green;
	shadeB = TheWritableGlobalData->m_scale944.blue * TheWritableGlobalData->m_terrainDiffuse[0].blue;
	shadeR = shadeR * 0.5f + TheWritableGlobalData->m_terrainAmbient[0].red;
	shadeG = shadeG * 0.5f + TheWritableGlobalData->m_terrainAmbient[0].green;
	shadeB = shadeB * 0.5f + TheWritableGlobalData->m_terrainAmbient[0].blue;
	Real scale = 1.0f;
	if (ShaderOverbrightEnabled) scale = 2.0f;
	shadeR = scale * shadeR;
	if (shadeR > 1.0f) shadeR = 1.0f;
	shadeG = scale * shadeG;
	if (shadeG > 1.0f) shadeG = 1.0f;
	shadeB = scale * shadeB;
	if (shadeB > 1.0f) shadeB = 1.0f;
	shadeR *= 255.0f;
	shadeG *= 255.0f;
	shadeB *= 255.0f;
	Int diffuse = (Int)shadeR;
	diffuse |= 0xffffff00;
	diffuse <<= 8;
	diffuse |= (Int)shadeG;
	diffuse <<= 8;
	diffuse |= (Int)shadeB;
	Int borderSize = m_map->m_border;

	IndexBufferClass::WriteLockClass lockIdxBuffer(m_indexScorch, 0);
	UnsignedShort *curIb = lockIdxBuffer.Get_Index_Array();

	VertexBufferClass::WriteLockClass lockVtxBuffer(m_vertexScorch, 0);
	VertexFormatXYZDUV1 *curVb = (VertexFormatXYZDUV1 *)lockVtxBuffer.Get_Vertex_Array();

	Int curScorch;
	for (curScorch = m_numScorches - 1; curScorch >= 0; curScorch--) {
		UnsignedByte flag = m_scorches[curScorch].flag;
		if (flag) {
			continue;
		}
		m_scorchesInBuffer++;
		Int type = m_scorches[curScorch].scorchType;
		if (type < 0 || type >= SCORCH_MARKS_IN_TEXTURE) {
			type = 0;
		}
		Real uOffset = (type % SCORCH_PER_ROW) * (1.0f / (SCORCH_PER_ROW));
		Real vOffset = (type / SCORCH_PER_ROW) * (1.0f / (SCORCH_PER_ROW));
		Real radius = m_scorches[curScorch].radius;
		Vector3 loc = m_scorches[curScorch].location;

		Int minX = WWMath::Float_To_Long(bfmeFloorD((loc.X - radius) * (1.0f / BFME_MAP_XY_FACTOR)));
		minX--;
		Int minY = WWMath::Float_To_Long(bfmeFloorD((loc.Y - radius) * (1.0f / BFME_MAP_XY_FACTOR)));
		minY--;
		if (minX < -borderSize) minX = -borderSize;
		if (minY < -borderSize) minY = -borderSize;
		Int maxX = WWMath::Float_To_Long(bfmeCeilD((loc.X + radius) * (1.0f / BFME_MAP_XY_FACTOR)));
		maxX++;
		Int maxY = WWMath::Float_To_Long(bfmeCeilD((loc.Y + radius) * (1.0f / BFME_MAP_XY_FACTOR)));
		maxY++;
		Int xExtent = m_map->m_xExtent;
		if (maxX > xExtent - borderSize) {
			maxX = xExtent - borderSize;
		}
		Int yExtent = m_map->m_yExtent;
		if (maxY > yExtent - borderSize) {
			maxY = yExtent - borderSize;
		}
		Int startVertex = m_curNumScorchVertices;
		Int yOffset = maxX - minX;
		Real left = minX * BFME_MAP_XY_FACTOR;
		Real width = (yOffset - 1) * BFME_MAP_XY_FACTOR;
		Real top = minY * BFME_MAP_XY_FACTOR;
		Real height = (maxY - minY - 1) * BFME_MAP_XY_FACTOR;
		Int i, j;
		for (j = minY; j < maxY; j++) {
			Real Y = j * BFME_MAP_XY_FACTOR;
			for (i = minX; i < maxX; i++) {
				if (m_curNumScorchVertices >= MAX_SCORCH_VERTEX) {
					m_curNumScorchVertices = startVertex;
					return;
				}
				curVb->diffuse = diffuse;
				Real X = i * BFME_MAP_XY_FACTOR;
				curVb->u1 = (X - left) / width * (1.0f / (SCORCH_PER_ROW)) + uOffset;
				curVb->v1 = (Y - top) / height * (1.0f / (SCORCH_PER_ROW)) + vOffset;
				curVb->x = X;
				curVb->y = Y;
				curVb->z = m_map->rva0006653B(i + borderSize, j + borderSize) * 0.0390625f + 1.0f;
				curVb++;
				m_curNumScorchVertices++;
			}
		}
		for (j = 0; j < maxY - minY - 1; j++) {
			Int yNdx = j + minY + borderSize;
			for (i = 0; i < maxX - minX - 1; i++) {
				if (m_curNumScorchIndices + 6 > MAX_SCORCH_INDEX) return;
				Int xNdx = i + minX + borderSize;
				Bool flipForBlend = reinterpret_cast<const Gen_0074B410 *>(m_map)->bfmeBitA(xNdx, yNdx);
				if (flipForBlend) {
					*curIb++ = startVertex + j * yOffset + i + 1;
					*curIb++ = startVertex + j * yOffset + i + yOffset;
					*curIb++ = startVertex + j * yOffset + i;
					*curIb++ = startVertex + j * yOffset + i + 1;
					*curIb++ = startVertex + j * yOffset + i + 1 + yOffset;
					*curIb++ = startVertex + j * yOffset + i + yOffset;
				} else {
					*curIb++ = startVertex + j * yOffset + i;
					*curIb++ = startVertex + j * yOffset + i + 1 + yOffset;
					*curIb++ = startVertex + j * yOffset + i + yOffset;
					*curIb++ = startVertex + j * yOffset + i;
					*curIb++ = startVertex + j * yOffset + i + 1;
					*curIb++ = startVertex + j * yOffset + i + 1 + yOffset;
				}
				m_curNumScorchIndices += 6;
			}
		}
	}
}
