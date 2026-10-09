// ?doPartialUpdate@W3DTerrainBackground@@QAEXABUIRegion2D@@PAVWorldHeightMap@@_N2@Z
// partial score=0.85 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// Native [00115044,00115791),1869B, RET16. W3DTerrainBackground::
// doPartialUpdate (WorldBuilder name). BFME 2 rewrite of the ZH update: after
// the tesselated terrain update it builds a second mesh of textured quads for
// the map's flagged (cliff) cells: four vertices per cell (+0x68, size +0x6C,
// count +0x78; FVF 0x152) with per-corner alpha in the diffuse high byte and
// the cell's UV quad, six indices per cell (+0x70, size +0x74, count +0x7C)
// split along the cell's flip diagonal. Offsets are target evidence; rowed
// helper receivers keep their ledger names.

#include <string.h>

typedef int Int;
typedef float Real;
typedef bool Bool;
typedef unsigned short UnsignedShort;

#define MAP_XY_FACTOR 10.0f
#define MAP_HEIGHT_SCALE (10.0f / 256.0f)

void *__cdecl operator new[](unsigned int size);
void __cdecl operator delete[](void *p);

extern void BFME_DX8_Thread_Lock(void);
extern void BFME_DX8_Thread_Assert(void);

class BFMEDX8DeviceLock
{
public:
	BFMEDX8DeviceLock() { BFME_DX8_Thread_Lock(); }
	~BFMEDX8DeviceLock() { BFME_DX8_Thread_Assert(); }
};

void bfmeReleaseQueuedDeviceInterfaces();

class Vector3
{
public:
	Vector3() {}
	Vector3(Real x, Real y, Real z) { X = x; Y = y; Z = z; }
	Vector3(const Vector3 &v) { X = v.X; Y = v.Y; Z = v.Z; }
	Vector3 &operator=(const Vector3 &v) { X = v.X; Y = v.Y; Z = v.Z; return *this; }
	Real X;
	Real Y;
	Real Z;
};

inline Vector3 operator+(const Vector3 &a, const Vector3 &b)
{
	return Vector3(a.X + b.X, a.Y + b.Y, a.Z + b.Z);
}

inline Vector3 operator-(const Vector3 &a, const Vector3 &b)
{
	return Vector3(a.X - b.X, a.Y - b.Y, a.Z - b.Z);
}

inline Vector3 operator*(const Vector3 &a, Real k)
{
	return Vector3(a.X * k, a.Y * k, a.Z * k);
}

class MinMaxAABoxClass
{
public:
	void Init_Empty(void);
	__forceinline void Add_Point(const Vector3 &point)
	{
		if (point.X < MinCorner.X) MinCorner.X = point.X;
		if (point.Y < MinCorner.Y) MinCorner.Y = point.Y;
		if (point.Z < MinCorner.Z) MinCorner.Z = point.Z;
		if (point.X > MaxCorner.X) MaxCorner.X = point.X;
		if (point.Y > MaxCorner.Y) MaxCorner.Y = point.Y;
		if (point.Z > MaxCorner.Z) MaxCorner.Z = point.Z;
	}

	Vector3 MinCorner;
	Vector3 MaxCorner;
};

class AABoxClass
{
public:
	__forceinline void Init(const MinMaxAABoxClass &mmbox)
	{
		Center = (mmbox.MaxCorner + mmbox.MinCorner) * 0.5f;
		Extent = (mmbox.MaxCorner - mmbox.MinCorner) * 0.5f;
	}

	Vector3 Center;
	Vector3 Extent;
};

class RefCountClass
{
public:
	virtual void Delete_This();
	void Add_Ref() { m_numRefs++; }
	void Release_Ref()
	{
		if (--m_numRefs == 0)
			Delete_This();
	}

private:
	Int m_numRefs;
};

class VertexBufferClass : public RefCountClass
{
public:
	class WriteLockClass
	{
	public:
		WriteLockClass(VertexBufferClass *buffer, int flags);
		~WriteLockClass();
		void *Get_Vertex_Array() { return m_vertices; }

	private:
		VertexBufferClass *m_buffer;
		void *m_vertices;
		int m_flags;
	};
};

class BfmeDynamicNativeVB : public VertexBufferClass
{
public:
	BfmeDynamicNativeVB(unsigned int fvf, unsigned short count, unsigned int a, unsigned int b);

private:
	unsigned char m_storage[0x20 - 0x08];
};

class IndexBufferClass : public RefCountClass
{
public:
	class WriteLockClass
	{
	public:
		WriteLockClass(IndexBufferClass *buffer, int flags);
		~WriteLockClass();
		UnsignedShort *Get_Index_Array() { return m_indices; }

	private:
		IndexBufferClass *m_buffer;
		UnsignedShort *m_indices;
		int m_flags;
	};
};

class DX8IndexBufferClass : public IndexBufferClass
{
public:
	enum UsageType { USAGE_DEFAULT = 0 };
	DX8IndexBufferClass(unsigned int index_count, UsageType usage);

private:
	unsigned char m_storage[0x18 - 0x08];
};

struct VertexFormatXYZNDUV1
{
	Real x;
	Real y;
	Real z;
	Real nx;
	Real ny;
	Real nz;
	unsigned int diffuse;
	Real u1;
	Real v1;
};

class TextureClass
{
public:
	void Release_Ref();
};

template <class T> class RefCountPtr
{
public:
	~RefCountPtr()
	{
		if (m_referent)
			m_referent->Release_Ref();
	}
	const RefCountPtr<T> &operator=(const RefCountPtr<T> &rhs);
	bool isNull() const { return m_referent == 0; }

private:
	T *m_referent;
};

struct BfmeResetTextureRef
{
	void clear();
};

class ShroudFilter
{
public:
	int m_pad00[3];
	int m_uAddressMode;
	int m_vAddressMode;
};

class ShroudTexture
{
public:
	ShroudFilter *getFilter(void);
};

class Rva0006B4CC
{
public:
	int call(int x, int y, int flag);
};

class BaseHeightMapRenderObjClass;
extern BaseHeightMapRenderObjClass *TheTerrainRenderObject;

class GameClient;
extern GameClient *TheGameClient;

class GlobalData
{
public:
	unsigned char m_pad00[0x49];
	bool m_secondTerrainTexture;
};

extern GlobalData *TheGlobalData;

struct ICoord2D
{
	Int x;
	Int y;
};

struct IRegion2D
{
	ICoord2D lo;
	ICoord2D hi;
};

class BoundedShortGrid
{
public:
	short rva00062A58(Int x, Int y);
};

class Rva00729300BitPlane
{
public:
	bool test(Int x, Int y) const;
};

class Rva0006653B
{
public:
	void rva0006AA45(Int x, Int y, Vector3 *normal);
};

// ZH TCliffInfo shape (WorldHeightMap.h): four corner UVs, flip, mutant, tile.
class Rva000ABD19
{
public:
	bool rva000ABD19(int a, int b);
};

struct TCliffInfo
{
	TCliffInfo()
	{
		u0 = 0.0f;
		v0 = 0.0f;
		u1 = 0.0f;
		v1 = 0.0f;
		u2 = 0.0f;
		v2 = 0.0f;
		u3 = 0.0f;
		v3 = 0.0f;
		flip = false;
		mutant = false;
		tileIndex = 0;
	}
	Real u0, v0;
	Real u1, v1;
	Real u2, v2;
	Real u3, v3;
	Bool flip;
	Bool mutant;
	short tileIndex;
};

class WorldHeightMap : public RefCountClass
{
public:
	Int getXExtent() { return m_width; }
	Int getYExtent() { return m_height; }
	Int getBorderSize() { return m_borderSize; }
	UnsignedShort getHeight(Int x, Int y) { return ((BoundedShortGrid *)this)->rva00062A58(x, y); }
	bool isCliffCell(Int x, Int y) { return ((Rva000ABD19 *)this)->rva000ABD19(x, y); }
	void getTerrainNormal(Int x, Int y, Vector3 *normal) { ((Rva0006653B *)this)->rva0006AA45(x, y, normal); }
	void rva000AE44B(Int x, Int y, TCliffInfo *info);
	bool rva000AE37E(Int x, Int y);
	bool rva000AF841(Int x, Int y);

private:
	Int m_width;
	Int m_height;
	Int m_borderSize;
};

class Rva000AE84A
{
public:
	void rva000AE84A(int x, int y, unsigned char *out, int unused);
};

class Gen_0074B410
{
public:
	bool bfmeBitA(Int x, Int y) const;
};

class W3DTerrainBackground
{
public:
	void doTesselatedUpdate(const IRegion2D &partialRange, WorldHeightMap *htMap, Bool doTextures);
	void doPartialUpdate(const IRegion2D &partialRange, WorldHeightMap *htMap, Bool doTextures, Bool flag);

private:
	Int m_cullStatus[3];
	AABoxClass m_bounds;
	VertexBufferClass *m_vertexTerrain;
	Int m_vertexTerrainSize;
	IndexBufferClass *m_indexTerrain;
	Int m_indexTerrainSize;
	RefCountPtr<TextureClass> m_terrainTexture;
	RefCountPtr<TextureClass> m_terrainTexture2X;
	RefCountPtr<TextureClass> m_normalTexture;
	RefCountPtr<TextureClass> m_normalTexture2X;
	Int m_texMultiplier;
	Int m_curNumTerrainVertices;
	Int m_curNumTerrainIndices;
	Int m_xOrigin;
	Int m_yOrigin;
	Int m_width;
	WorldHeightMap *m_map;
	Bool m_initialized;
	Bool m_flag61;
	Bool m_needUpdate;
	unsigned char m_pad63[0x68 - 0x63];
	VertexBufferClass *m_vertexCliff;
	Int m_vertexCliffSize;
	IndexBufferClass *m_indexCliff;
	Int m_indexCliffSize;
	Int m_curNumCliffVertices;
	Int m_curNumCliffIndices;
};

void W3DTerrainBackground::doPartialUpdate(const IRegion2D &partialRange, WorldHeightMap *htMap, Bool doTextures, Bool flag)
{
	if (m_map == 0)
		return;
	m_flag61 = flag;
	if (htMap) {
		htMap->Add_Ref();
		if (m_map)
			m_map->Release_Ref();
		m_map = htMap;
	}
	if (!m_initialized)
		return;
	doTesselatedUpdate(partialRange, htMap, doTextures);

	Int minX = m_xOrigin;
	Int minY = m_yOrigin;
	Int maxX = m_xOrigin + m_width;
	Int maxY = m_yOrigin + m_width;
	WorldHeightMap *map = m_map;
	Int limitX = map->getXExtent() - 1;
	Int limitY = map->getYExtent() - 1;
	if (maxX > limitX)
		maxX = limitX;
	if (maxY > limitY)
		maxY = limitY;
	if (partialRange.lo.x > maxX || partialRange.lo.y > maxY
		|| partialRange.hi.x < minX || partialRange.hi.y < minY)
		return;

	Bool anyCliff = false;
	Int numCliff = 0;
	for (Int j = minY; j <= maxY; j++) {
		for (Int i = minX; i <= maxX; i++) {
			if (map->isCliffCell(i, j)) {
				anyCliff = true;
				numCliff++;
			}
		}
	}
	m_curNumCliffVertices = 0;
	m_curNumCliffIndices = 0;
	if (!anyCliff)
		return;

	BFMEDX8DeviceLock lock;
	Int requiredVertex = numCliff * 4 + 6;
	if (m_vertexCliffSize < requiredVertex || m_vertexCliff == 0) {
		m_vertexCliffSize = requiredVertex;
		if (m_vertexCliff) {
			m_vertexCliff->Release_Ref();
			m_vertexCliff = 0;
		}
		m_vertexCliff = new BfmeDynamicNativeVB(0x152, (unsigned short)(m_vertexCliffSize + 4), 0, 0);
	}
	Int requiredIndex = numCliff * 6 + 6;
	if (m_indexCliffSize < requiredIndex || m_indexCliff == 0) {
		m_indexCliffSize = requiredIndex;
		if (m_indexCliff) {
			m_indexCliff->Release_Ref();
			m_indexCliff = 0;
		}
		m_indexCliff = new DX8IndexBufferClass(m_indexCliffSize + 4, DX8IndexBufferClass::USAGE_DEFAULT);
	}

	VertexBufferClass::WriteLockClass lockVtxBuffer(m_vertexCliff, 0);
	VertexFormatXYZNDUV1 *curVb = (VertexFormatXYZNDUV1 *)lockVtxBuffer.Get_Vertex_Array();
	MinMaxAABoxClass bounds;
	bounds.Init_Empty();
	IndexBufferClass::WriteLockClass lockIdxBuffer(m_indexCliff, 0);
	UnsignedShort *curIb = lockIdxBuffer.Get_Index_Array();
	m_curNumCliffIndices = 0;
	for (Int j = minY; j <= maxY; j++) {
		for (Int i = minX; i <= maxX; i++) {
			if (!m_map->isCliffCell(i, j))
				continue;
			TCliffInfo info;
			m_map->rva000AE44B(i, j, &info);
			Int base = m_curNumCliffVertices;
			if (base + 4 >= m_vertexCliffSize)
				return;
			bool flip = false;
			unsigned char alpha[4];
			alpha[0] = 0xFF;
			alpha[1] = 0xFF;
			alpha[2] = 0xFF;
			alpha[3] = 0xFF;
			if (m_map->rva000AE37E(i, j)) {
				flip = ((Gen_0074B410 *)m_map)->bfmeBitA(i, j);
				((Rva000AE84A *)m_map)->rva000AE84A(i, j, alpha, (int)&flip);
			}

			Vector3 pos;
			Vector3 normal;
			curVb->diffuse = (alpha[0] << 24) | ((Rva0006B4CC *)TheTerrainRenderObject)->call(i, j, 1);
			pos.Z = ((Real)m_map->getHeight(i, j) * MAP_HEIGHT_SCALE);
			pos.X = i * MAP_XY_FACTOR - m_map->getBorderSize() * MAP_XY_FACTOR;
			pos.Y = j * MAP_XY_FACTOR - m_map->getBorderSize() * MAP_XY_FACTOR;
			m_map->getTerrainNormal(i, j, &normal);
			curVb->u1 = info.u0;
			curVb->v1 = info.v0;
			curVb->x = pos.X;
			curVb->y = pos.Y;
			curVb->z = pos.Z;
			curVb->nx = normal.X;
			curVb->ny = normal.Y;
			curVb->nz = normal.Z;
			curVb++;
			m_curNumCliffVertices++;

			curVb->diffuse = (alpha[1] << 24) | ((Rva0006B4CC *)TheTerrainRenderObject)->call(i + 1, j, 1);
			pos.Z = ((Real)m_map->getHeight(i + 1, j) * MAP_HEIGHT_SCALE);
			pos.X = (i + 1) * MAP_XY_FACTOR - m_map->getBorderSize() * MAP_XY_FACTOR;
			pos.Y = j * MAP_XY_FACTOR - m_map->getBorderSize() * MAP_XY_FACTOR;
			m_map->getTerrainNormal(i + 1, j, &normal);
			curVb->u1 = info.u1;
			curVb->v1 = info.v1;
			curVb->x = pos.X;
			curVb->y = pos.Y;
			curVb->z = pos.Z;
			curVb->nx = normal.X;
			curVb->ny = normal.Y;
			curVb->nz = normal.Z;
			curVb++;
			m_curNumCliffVertices++;

			curVb->diffuse = (alpha[3] << 24) | ((Rva0006B4CC *)TheTerrainRenderObject)->call(i, j + 1, 1);
			pos.Z = ((Real)m_map->getHeight(i, j + 1) * MAP_HEIGHT_SCALE);
			pos.X = i * MAP_XY_FACTOR - m_map->getBorderSize() * MAP_XY_FACTOR;
			pos.Y = (j + 1) * MAP_XY_FACTOR - m_map->getBorderSize() * MAP_XY_FACTOR;
			m_map->getTerrainNormal(i, j + 1, &normal);
			curVb->u1 = info.u3;
			curVb->v1 = info.v3;
			curVb->x = pos.X;
			curVb->y = pos.Y;
			curVb->z = pos.Z;
			curVb->nx = normal.X;
			curVb->ny = normal.Y;
			curVb->nz = normal.Z;
			curVb++;
			m_curNumCliffVertices++;

			curVb->diffuse = (alpha[2] << 24) | ((Rva0006B4CC *)TheTerrainRenderObject)->call(i + 1, j + 1, 1);
			pos.Z = ((Real)m_map->getHeight(i + 1, j + 1) * MAP_HEIGHT_SCALE);
			pos.X = (i + 1) * MAP_XY_FACTOR - m_map->getBorderSize() * MAP_XY_FACTOR;
			pos.Y = (j + 1) * MAP_XY_FACTOR - m_map->getBorderSize() * MAP_XY_FACTOR;
			m_map->getTerrainNormal(i + 1, j + 1, &normal);
			curVb->u1 = info.u2;
			curVb->v1 = info.v2;
			curVb->x = pos.X;
			curVb->y = pos.Y;
			curVb->z = pos.Z;
			curVb->nx = normal.X;
			curVb->ny = normal.Y;
			curVb->nz = normal.Z;
			curVb++;
			m_curNumCliffVertices++;

			*curIb++ = base;
			if (!m_map->rva000AF841(i, j)) {
				*curIb++ = base + 3;
				*curIb++ = base + 2;
				*curIb++ = base;
				*curIb++ = base + 1;
				*curIb++ = base + 3;
			} else {
				*curIb++ = base + 1;
				*curIb++ = base + 2;
				*curIb++ = base + 1;
				*curIb++ = base + 3;
				*curIb++ = base + 2;
			}
			m_curNumCliffIndices += 6;
		}
	}
}
