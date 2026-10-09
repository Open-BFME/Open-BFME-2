// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// Native [001149EB,00115044),1625B, RET12. W3DTerrainBackground::
// doTesselatedUpdate (WorldBuilder name). BFME 2 rewrite of the ZH tile
// update: swap in the height map, bail when uninitialized (+0x60) or when
// the partial range misses the clamped tile; number the in-mesh cells of the
// map bit plane, (re)allocate the dynamic vertex buffer (+0x24, size +0x28,
// FVF 0x152 XYZ|NORMAL|DIFFUSE|TEX1, 0x24-byte vertices) and fill one vertex
// per in-mesh cell (height * MAP_HEIGHT_SCALE, normal 0x0006AA45, diffuse
// from TheTerrainRenderObject 0x0006B4CC, tile UVs); let the recursive
// filler 0x00113DE0 count and then write the indices (+0x2C, size +0x30,
// count +0x4C); rebuild the bounds (+0x0C) from a MinMaxAABox; rebuild the
// 1x textures +0x34/+0x3C (DXT1 when TheGameClient exists) through the map
// builder 0x000AE989. All under the DX8 thread lock. Offsets are target
// evidence; rowed helper receivers keep their ledger names.

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

class WorldHeightMap : public RefCountClass
{
public:
	Int getXExtent() { return m_width; }
	Int getYExtent() { return m_height; }
	Int getBorderSize() { return m_borderSize; }
	UnsignedShort getHeight(Int x, Int y) { return ((BoundedShortGrid *)this)->rva00062A58(x, y); }
	bool isInMesh(Int x, Int y) { return ((const Rva00729300BitPlane *)this)->test(x, y); }
	void getTerrainNormal(Int x, Int y, Vector3 *normal) { ((Rva0006653B *)this)->rva0006AA45(x, y, normal); }
	RefCountPtr<TextureClass> rva000AE989(int xCell, int yCell, int cellWidth,
		int pixelsPerCell, int format, bool second);

private:
	Int m_width;
	Int m_height;
	Int m_borderSize;
};

class W3DTerrainBackground
{
public:
	void doTesselatedUpdate(const IRegion2D &partialRange, WorldHeightMap *htMap, Bool doTextures);
	void rva00113DE0(UnsignedShort *ib, Vector3 *heights, Int xOffset, Int yOffset, Int width,
		UnsignedShort *ndx, Int &curIndex);

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
	unsigned char m_pad61;
	Bool m_needUpdate;
};

void W3DTerrainBackground::doTesselatedUpdate(const IRegion2D &partialRange, WorldHeightMap *htMap, Bool doTextures)
{
	if (m_map == 0)
		return;
	if (htMap) {
		htMap->Add_Ref();
		if (m_map)
			m_map->Release_Ref();
		m_map = htMap;
	}
	if (!m_initialized)
		return;

	Int minX = m_xOrigin;
	Int minY = m_yOrigin;
	Int maxX = m_xOrigin + m_width;
	Int maxY = m_yOrigin + m_width;
	m_needUpdate = false;
	Int limitX = m_map->getXExtent() - 1;
	Int limitY = m_map->getYExtent() - 1;
	if (maxX > limitX)
		maxX = limitX;
	if (maxY > limitY)
		maxY = limitY;
	if (partialRange.lo.x > maxX || partialRange.lo.y > maxY
		|| partialRange.hi.x < minX || partialRange.hi.y < minY)
		return;

	Int count = (m_width + 1) * (m_width + 1);
	UnsignedShort *ndx = new UnsignedShort[count];
	memset(ndx, 0, count * sizeof(UnsignedShort));

	Int requiredVertex = 0;
	Int i, j;
	for (j = minY; j <= maxY; j++) {
		for (i = minX; i <= maxX; i++) {
			if (m_map->isInMesh(i, j))
				requiredVertex++;
		}
	}

	BFMEDX8DeviceLock lock;
	if (m_vertexTerrainSize < requiredVertex || m_vertexTerrain == 0) {
		m_vertexTerrainSize = requiredVertex;
		if (m_vertexTerrain) {
			m_vertexTerrain->Release_Ref();
			m_vertexTerrain = 0;
		}
		m_vertexTerrain = new BfmeDynamicNativeVB(0x152, (unsigned short)(m_vertexTerrainSize + 4), 0, 0);
	}

	m_curNumTerrainVertices = 0;
	VertexBufferClass::WriteLockClass lockVtxBuffer(m_vertexTerrain, 0);
	VertexFormatXYZNDUV1 *curVb = (VertexFormatXYZNDUV1 *)lockVtxBuffer.Get_Vertex_Array();
	for (j = minY; j <= maxY; j++) {
		for (i = minX; i <= maxX; i++) {
			if (m_map->isInMesh(i, j)) {
				Int diffuse = ((Rva0006B4CC *)TheTerrainRenderObject)->call(i, j, 1);
				Vector3 pos;
				Int k = i < limitX ? i : limitX;
				Int l = j < limitY ? j : limitY;
				WorldHeightMap *map = m_map;
				pos.Z = ((Real)map->getHeight(k, l) * MAP_HEIGHT_SCALE);
				pos.X = i * MAP_XY_FACTOR - map->getBorderSize() * MAP_XY_FACTOR;
				pos.Y = j * MAP_XY_FACTOR - map->getBorderSize() * MAP_XY_FACTOR;
				Vector3 normal;
				map->getTerrainNormal(i, j, &normal);
				curVb->x = pos.X;
				curVb->y = pos.Y;
				curVb->z = pos.Z;
				curVb->nx = normal.X;
				curVb->ny = normal.Y;
				curVb->nz = normal.Z;
				curVb->diffuse = diffuse;
				curVb->u1 = (Real)(i - minX) / (Real)(m_width);
				curVb->v1 = 1.0f - (Real)(j - minY) / (Real)(m_width);
				curVb++;
				ndx[i - minX + (m_width + 1) * (j - minY)] = m_curNumTerrainVertices;
				m_curNumTerrainVertices++;
			}
		}
	}

	Int curIndex = 0;
	rva00113DE0(0, 0, 0, 0, m_width, ndx, curIndex);
	if (m_indexTerrainSize < curIndex || m_indexTerrain == 0) {
		m_indexTerrainSize = curIndex;
		if (m_indexTerrain) {
			m_indexTerrain->Release_Ref();
			m_indexTerrain = 0;
		}
		m_indexTerrain = new DX8IndexBufferClass(m_indexTerrainSize + 4, DX8IndexBufferClass::USAGE_DEFAULT);
	}
	m_curNumTerrainIndices = 0;
	IndexBufferClass::WriteLockClass lockIdxBuffer(m_indexTerrain, 0);
	rva00113DE0(lockIdxBuffer.Get_Index_Array(), 0, 0, 0, m_width, ndx, m_curNumTerrainIndices);
	delete[] ndx;

	MinMaxAABoxClass bounds;
	bounds.Init_Empty();
	for (j = minY; j <= maxY; j += 1) {
		i = minX;
		if (i <= maxX) {
			WorldHeightMap *map = m_map;
			do {
				Vector3 pos;
				Int k = i < limitX ? i : limitX;
				Int l = j < limitY ? j : limitY;
				pos.Z = ((Real)map->getHeight(k, l) * MAP_HEIGHT_SCALE);
				pos.X = i * MAP_XY_FACTOR - map->getBorderSize() * MAP_XY_FACTOR;
				pos.Y = j * MAP_XY_FACTOR - map->getBorderSize() * MAP_XY_FACTOR;
				bounds.Add_Point(pos);
			} while (++i <= maxX);
		}
	}
	m_bounds.Init(bounds);

	if (m_terrainTexture.isNull() || doTextures) {
		((BfmeResetTextureRef *)&m_terrainTexture2X)->clear();
		if (TheGameClient)
			m_terrainTexture = m_map->rva000AE989(m_xOrigin, m_yOrigin, m_width, 0x10, 0x31545844, false);
		else
			m_terrainTexture = m_map->rva000AE989(m_xOrigin, m_yOrigin, m_width, 0x10, 0x19, false);
		((ShroudTexture *)&m_terrainTexture)->getFilter()->m_uAddressMode = 1;
		((ShroudTexture *)&m_terrainTexture)->getFilter()->m_vAddressMode = 1;
	}
	if (TheGlobalData->m_secondTerrainTexture) {
		if (m_normalTexture.isNull() || doTextures) {
			((BfmeResetTextureRef *)&m_normalTexture2X)->clear();
			m_normalTexture = m_map->rva000AE989(m_xOrigin, m_yOrigin, m_width, 0x10, 0x19, true);
			((ShroudTexture *)&m_normalTexture)->getFilter()->m_uAddressMode = 1;
			((ShroudTexture *)&m_normalTexture)->getFilter()->m_vAddressMode = 1;
		}
	}
	if (!TheGameClient)
		bfmeReleaseQueuedDeviceInterfaces();
}
