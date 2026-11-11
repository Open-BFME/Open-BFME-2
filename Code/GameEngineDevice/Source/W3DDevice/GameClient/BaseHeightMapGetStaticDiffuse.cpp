// cl: /O1 /G7 /arch:SSE /Op /DNDEBUG /MD /EHsc /ICode/Libraries/Include /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
//
// ?getStaticDiffuse@BaseHeightMapRenderObjClass@@QAEHHH_N@Z, retail
// 0x0006B4CC..0x0006B76C (672B), thiscall ret 0xC.
//
// Zero Hour's BaseHeightMapRenderObjClass::getStaticDiffuse in its BFME 2
// form: the cell is clamped to the map, the normal comes from the map's
// terrain-normal sampler (0x0006AA45) instead of an inline cross product, the
// height from the 16-bit grid (0x00062A58, * 10/256), and the six-argument
// doTheLight (0x000694A3) receives the caller's flag that leaves the sun to
// the normal-mapped terrain shader. Under a standing-water area with a depth
// colouring texture (0x0007FA2B, 0x003081FB) the colour is multiplied by the
// area's depth LUT sampled at (waterZ - groundZ) / max(waterZ, 1)
// (0x00308A12); waterZ is the area polygon's elevation (+0x60).
//
// Evidence (target): WorldBuilder twin 0x75CA90 has the same statements; it
// reads the third argument as a byte and computes the tint position as
// x*10 - border*10. The road lighting caller (loadLit4PtSection) passes
// (x, y, 1). /Op is what keeps retail's load/store order in the light-ray
// loop. Map, scene and water-area class names are the ledger's
// address-derived owners.

typedef int Int;
typedef bool Bool;
typedef float Real;
typedef unsigned char UnsignedByte;
typedef unsigned int UnsignedInt;

#include "../../../../Libraries/Source/WWVegas/WWMath/Vector3Data.h"

struct VertexFormatXYZDUV2
{
public:
	Real x; // +0x00
	Real y; // +0x04
	Real z; // +0x08
	unsigned int diffuse; // +0x0C
	Real u1; // +0x10
	Real v1; // +0x14
	Real u2; // +0x18
	Real v2; // +0x1C
};

#include "Lib/Coord3D.h"

#include "../../../../GameEngine/Include/Common/GlobalData.h"
extern GlobalData *TheWritableGlobalData;

class Rva0006653B
{
public:
	unsigned short rva0006653B(int x, int y);
	void rva0006AA45(int x, int y, Vector3 *normal);
	char m_pad00[8];
	Int m_xExtent;
	Int m_yExtent;
	Int m_border;
};

class BoundedShortGrid
{
public:
	short load(int x, int y);
};

template <class T> class RefMultiListIterator;
class RenderObjClass;

#include "../../../Include/W3DDevice/GameClient/RTS3DScene.h"
#include "../../../Include/W3DDevice/GameClient/Rva0006ED29.h"

#include "../../../Include/W3DDevice/GameClient/Rva0007F944Host.h"
class Rva003081FB { public: unsigned char rva003081FB(); };
#include "../../../../GameEngine/Include/GameLogic/StandingWaterArea.h"
extern void *W3DGCData00DE2000;

class BaseHeightMapRenderObjClass
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual void v5();
	virtual void v6();
	virtual void v7();
	virtual void v8();
	virtual void v9();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void v14();
	virtual void v15();
	virtual void v16();
	virtual void v17();
	virtual void v18();
	virtual void v19();
	virtual void v20();
	virtual void v21();
	virtual void v22();
	virtual void v23();
	virtual void v24();
	virtual void v25();
	virtual void v26();
	virtual void v27();
	virtual void v28();
	virtual void v29();
	virtual void v30();
	virtual void v31();
	virtual void v32();
	virtual void v33();
	virtual void v34();
	virtual void v35();
	virtual void v36();
	virtual void v37();
	virtual void v38();
	virtual void v39();
	virtual void v40();
	virtual void v41();
	virtual void v42();
	virtual void v43();
	virtual void v44();
	virtual void v45();
	virtual void v46();
	virtual void v47();
	virtual void v48();
	virtual void v49();
	virtual void v50();
	virtual void v51();
	virtual void v52();
	virtual void v53();
	virtual void v54();
	virtual void v55();
	virtual void v56();
	virtual void v57();
	virtual void v58();
	virtual void v59();
	virtual void v60();
	virtual void v61();
	virtual void v62();
	virtual void v63();
	virtual void v64();
	virtual void v65();
	virtual void v66();
	virtual void v67();
	virtual void v68();
	virtual void v69();
	virtual void v70();
	virtual void v71();
	virtual void v72();
	virtual void v73();
	virtual void v74();
	virtual void v75();
	virtual void v76();
	virtual void v77();
	virtual void v78();
	virtual void v79();
	virtual void v80();
	virtual void v81();
	virtual void v82();
	virtual void v83();
	virtual void v84();
	virtual void v85();
	virtual void v86();
	virtual void v87();
	virtual void v88();
	virtual void v89();
	virtual void v90();
	virtual void v91();
	virtual void v92();
	virtual void v93();
	virtual void v94();
	virtual void v95();
	virtual void v96();
	virtual void v97();
	virtual void v98();
	virtual void v99();
	virtual void v100();
	virtual void v101();
	virtual void v102();
	virtual void v103();
	virtual void v104();
	virtual void v105();
	virtual void v106();
	virtual void v107();
	virtual void v108();
	virtual void v109();
	virtual void v110();
	virtual void v111();
	virtual void v112();
	virtual void v113();
	virtual void v114();
	virtual void v115();
	virtual void v116();
	virtual void v117();
	virtual void v118();
	virtual void v119();
	virtual void v120();
	virtual void v121();
	virtual void v122();
	virtual void v123();
	virtual void v124();
	virtual void v125();
	virtual void v126();
	virtual void v127();
	virtual void v128();
	virtual void v129();
	virtual void v130();
	virtual void v131();
	virtual void v132();
	virtual void v133();
	virtual void v134();
	virtual void v135();
	virtual void v136();
	virtual void v137();
	virtual void v138();
	virtual void v139();
	virtual void v140();
	virtual void v141();
	virtual void v142();
	virtual void v143();
	virtual void v144();
	virtual Real getHeightMapHeight(Real x, Real y, Coord3D *normal) const;
	Int getStaticDiffuse(Int x, Int y, Bool skipFirstLight);
	void doTheLight(VertexFormatXYZDUV2 *vb, Vector3 *light, Vector3 *normal, RefMultiListIterator<RenderObjClass> *pLightsIterator, UnsignedByte alpha, Bool skipFirstLight);

private:
	char m_pad04[0x78 - 4 - 0];
	RTS3DScene *m_scene;			// +0x78
	char m_pad7C[0x37C0 - 0x7C];
	Rva0006653B *m_map;			// +0x37C0
};

Int BaseHeightMapRenderObjClass::getStaticDiffuse(Int x, Int y, Bool skipFirstLight)
{
	RefMultiListIterator<RenderObjClass> *it = 0;
	if (x < 0) x = 0;
	if (y < 0) y = 0;
	if (x >= m_map->m_xExtent)
		x = m_map->m_xExtent - 1;
	if (y >= m_map->m_yExtent)
		y = m_map->m_yExtent - 1;

	if (m_map == 0) {
		return 0;
	}

	Vector3 lightRay[3];
	Int numLights = TheWritableGlobalData->m_numberGlobalLights;
	for (Int lightIndex = 0; lightIndex < numLights; lightIndex++)
	{
		const Coord3D *lightPos = &TheWritableGlobalData->m_terrainLightPos[lightIndex];
		lightRay[lightIndex].X = -lightPos->x;
		Vector3 &ray = lightRay[lightIndex];
		Real ny = -lightPos->y;
		Real nz = -lightPos->z;
		ray.Y = ny;
		ray.Z = nz;
	}

	Vector3 normalAtTexel;
	m_map->rva0006AA45(x, y, &normalAtTexel);

	VertexFormatXYZDUV2 vertex;
	Int border = m_map->m_border;
	vertex.x = (x - border) * 10.0f;
	vertex.y = (y - border) * 10.0f;
	vertex.z = (unsigned short)((BoundedShortGrid *)m_map)->load(x, y) * 0.0390625f;
	vertex.u1 = 0;
	vertex.v1 = 0;
	vertex.u2 = 1;
	vertex.v2 = 1;

	RTS3DScene *pMyScene = m_scene;
	if (pMyScene) {
		it = pMyScene->createLightsIterator();
		doTheLight(&vertex, lightRay, &normalAtTexel, it, 1, skipFirstLight);
		if (it) {
			((Rva0006ED29 *)pMyScene)->rva0006ED29(it);
			it = 0;
		}
	} else {
		doTheLight(&vertex, lightRay, &normalAtTexel, it, 1, skipFirstLight);
	}

	Real px = x * 10.0f - m_map->m_border * 10.0f;
	Real py = y * 10.0f - m_map->m_border * 10.0f;
	if (W3DGCData00DE2000) {
		Rva003081FB *area = (Rva003081FB *)((Rva0007F944Host *)W3DGCData00DE2000)->rva0007FA2B(px, py);
		if (area && area->rva003081FB()) {
			Real waterHeight = (Real)*(Int *)((char *)area + 0x60);
			Real terrainHeight = getHeightMapHeight(px, py, 0);
			if (waterHeight > terrainHeight) {
				Real depth = waterHeight - terrainHeight;
				Real range = waterHeight;
				if (1.0f >= range)
					range = 1.0f;
				Int r = 0xff, g = 0xff, b = 0xff;
				((StandingWaterArea *)area)->rva00308A12(depth / range, &r, &g, &b);
				UnsignedInt color = vertex.diffuse;
				UnsignedInt blue = color & 0xff;
				UnsignedInt green = (color >> 8) & 0xff;
				UnsignedInt red = (color >> 16) & 0xff;
				UnsignedInt alpha = (color >> 24) & 0xff;
				blue = (blue * b) >> 8;
				green = (green * g) >> 8;
				red = (red * r) >> 8;
				if (red > 0xff) red = 0xff;
				if (green > 0xff) green = 0xff;
				if (blue > 0xff) blue = 0xff;
				vertex.diffuse = blue | (green << 8) | (red << 16) | (alpha << 24);
			}
		}
	}
	return vertex.diffuse;
}
