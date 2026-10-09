// ?getStaticDiffuse@BaseHeightMapRenderObjClass@@QAEHHHH@Z
// partial score=0.92 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// Native [0006B4CC,0006B76C),672B, RET12. BaseHeightMapRenderObjClass::
// getStaticDiffuse (Zero Hour BaseHeightMap.cpp is the guide): clamp the
// cell to the map (+0x37C0), light the cell vertex with the global terrain
// lights through doTheLight (0x000694A3, six arguments in BFME 2, the
// caller's flag last) using the scene's light iterator (+0x78) when there is
// a scene. BFME 2 takes the normal from the map's normal query (0x0006AA45)
// instead of the ZH cross product, and tints the result under water: the
// area found by 0x0007FA2B on the W3DGCData00DE2000 object, when 0x003081FB
// accepts it, compares its integer level (+0x60) with getHeightMapHeight
// (vtable +0x244) and scales the RGB channels by the colour 0x00308A12
// returns for depth / max(level, 1). Offsets and helper roles are target
// evidence; helper names are address-derived.

typedef int Int;
typedef float Real;
typedef unsigned int UnsignedInt;
typedef unsigned char UnsignedByte;

#define MAP_XY_FACTOR 10.0f
#define MAP_HEIGHT_SCALE (10.0f / 256.0f)
#define MAX_GLOBAL_LIGHTS 3

class Vector3
{
public:
	void Set(Real x, Real y, Real z) { X = x; Y = y; Z = z; }
	Real X;
	Real Y;
	Real Z;
};

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

struct VertexFormatXYZDUV2
{
	Real x;
	Real y;
	Real z;
	UnsignedInt diffuse;
	Real u1;
	Real v1;
	Real u2;
	Real v2;
};

class RenderObjClass;
template <class T> class RefMultiListIterator;

class RTS3DScene
{
public:
	RefMultiListIterator<RenderObjClass> *createLightsIterator(void);
};

class Rva0006ED29
{
public:
	void rva0006ED29(void *it);
};

class GlobalLightView
{
public:
	unsigned char m_pad000[0x920];
	Coord3D m_terrainLightPos[MAX_GLOBAL_LIGHTS];
	unsigned char m_pad944[0x988 - 0x944];
	Int m_numGlobalLights;
};

extern GlobalLightView *TheGlobalData;

class BoundedShortGrid
{
public:
	short rva00062A58(Int x, Int y);
};

class Rva0006653B
{
public:
	void rva0006AA45(Int x, Int y, Vector3 *normal);
};

class WorldHeightMap
{
public:
	Int getXExtent() { return m_width; }
	Int getYExtent() { return m_height; }
	Int getBorderSize() { return m_borderSize; }
	unsigned short getHeight(Int x, Int y) { return ((BoundedShortGrid *)this)->rva00062A58(x, y); }
	void getTerrainNormal(Int x, Int y, Vector3 *normal) { ((Rva0006653B *)this)->rva0006AA45(x, y, normal); }

private:
	unsigned char m_pad00[0x08];
	Int m_width;
	Int m_height;
	Int m_borderSize;
};

class Rva003081FB
{
public:
	UnsignedByte rva003081FB(void);
};

class Rva00308A12
{
public:
	void rva00308A12(Real ratio, Int *r, Int *g, Int *b);
};

class Rva0007FA2B
{
public:
	void *rva0007FA2B(Real x, Real y);
};

extern void *W3DGCData00DE2000;

#define BFME_PAD_VIRTUAL(n) virtual void pad##n();
#define BFME_PAD_VIRTUAL8(n) BFME_PAD_VIRTUAL(n##0) BFME_PAD_VIRTUAL(n##1) \
	BFME_PAD_VIRTUAL(n##2) BFME_PAD_VIRTUAL(n##3) BFME_PAD_VIRTUAL(n##4) \
	BFME_PAD_VIRTUAL(n##5) BFME_PAD_VIRTUAL(n##6) BFME_PAD_VIRTUAL(n##7)
#define BFME_PAD_VIRTUAL64(n) BFME_PAD_VIRTUAL8(n##0) BFME_PAD_VIRTUAL8(n##1) \
	BFME_PAD_VIRTUAL8(n##2) BFME_PAD_VIRTUAL8(n##3) BFME_PAD_VIRTUAL8(n##4) \
	BFME_PAD_VIRTUAL8(n##5) BFME_PAD_VIRTUAL8(n##6) BFME_PAD_VIRTUAL8(n##7)

class BaseHeightMapRenderObjClass
{
public:
	BFME_PAD_VIRTUAL64(a) BFME_PAD_VIRTUAL64(b) BFME_PAD_VIRTUAL8(c0) BFME_PAD_VIRTUAL8(c1)
	BFME_PAD_VIRTUAL(d0)
	virtual Real getHeightMapHeight(Real x, Real y, Coord3D *normal);	// slot 145 (+0x244)

	Int getStaticDiffuse(Int x, Int y, Int flag);
	void doTheLight(VertexFormatXYZDUV2 *vb, Vector3 *light, Vector3 *normal,
		RefMultiListIterator<RenderObjClass> *pLightsIterator, UnsignedByte alpha, Int flag);

private:
	unsigned char m_pad04[0x78 - 0x04];
	RTS3DScene *m_scene;
	unsigned char m_pad7C[0x37C0 - 0x7C];
	WorldHeightMap *m_map;
};

// ?getStaticDiffuse@BaseHeightMapRenderObjClass@@QAEHHHH@Z
Int BaseHeightMapRenderObjClass::getStaticDiffuse(Int x, Int y, Int flag)
{
	if (x < 0)
		x = 0;
	if (y < 0)
		y = 0;
	if (x >= m_map->getXExtent())
		x = m_map->getXExtent() - 1;
	if (y >= m_map->getYExtent())
		y = m_map->getYExtent() - 1;

	if (m_map == 0)
		return 0;

	Vector3 normalAtTexel;
	Vector3 lightRay[MAX_GLOBAL_LIGHTS];
	const Coord3D *lightPos;
	Int numLights = TheGlobalData->m_numGlobalLights;
	for (Int lightIndex = 0; lightIndex < numLights; lightIndex++) {
		lightPos = &TheGlobalData->m_terrainLightPos[lightIndex];
		Vector3 &ray = lightRay[lightIndex];
		ray.X = -lightPos->x;
		ray.Y = -lightPos->y;
		ray.Z = -lightPos->z;
	}

	m_map->getTerrainNormal(x, y, &normalAtTexel);

	VertexFormatXYZDUV2 vertex;
	Int border = m_map->getBorderSize();
	vertex.x = (x - border) * MAP_XY_FACTOR;
	vertex.y = (y - border) * MAP_XY_FACTOR;
	vertex.z = ((Real)m_map->getHeight(x, y)) * MAP_HEIGHT_SCALE;
	vertex.u1 = 0;
	vertex.v1 = 0;
	vertex.u2 = 1;
	vertex.v2 = 1;

	RTS3DScene *pMyScene = m_scene;
	if (pMyScene) {
		RefMultiListIterator<RenderObjClass> *it = pMyScene->createLightsIterator();
		doTheLight(&vertex, lightRay, &normalAtTexel, it, 1, flag);
		if (it)
			((Rva0006ED29 *)pMyScene)->rva0006ED29(it);
	} else {
		doTheLight(&vertex, lightRay, &normalAtTexel, 0, 1, flag);
	}

	Real worldX = x * MAP_XY_FACTOR - m_map->getBorderSize() * MAP_XY_FACTOR;
	Real worldY = y * MAP_XY_FACTOR - m_map->getBorderSize() * MAP_XY_FACTOR;
	if (W3DGCData00DE2000) {
		void *water = ((Rva0007FA2B *)W3DGCData00DE2000)->rva0007FA2B(worldX, worldY);
		if (water && ((Rva003081FB *)water)->rva003081FB()) {
			Real level = *(Int *)((char *)water + 0x60);
			Real ground = getHeightMapHeight(worldX, worldY, 0);
			if (level > ground) {
				Real depth = level - ground;
				Real range = level;
				if (range <= 1.0f)
					range = 1.0f;
				Int b = 255;
				Int g = 255;
				Int r = 255;
				((Rva00308A12 *)water)->rva00308A12(depth / range, &r, &g, &b);
				UnsignedInt alpha = vertex.diffuse >> 24;
				UnsignedInt red = (((vertex.diffuse >> 16) & 0xFF) * r) >> 8;
				UnsignedInt green = (((vertex.diffuse >> 8) & 0xFF) * g) >> 8;
				UnsignedInt blue = ((vertex.diffuse & 0xFF) * b) >> 8;
				if (red > 255)
					red = 255;
				if (green > 255)
					green = 255;
				if (blue > 255)
					blue = 255;
				vertex.diffuse = (alpha << 24) | (red << 16) | (green << 8) | blue;
			}
		}
	}
	return vertex.diffuse;
}
