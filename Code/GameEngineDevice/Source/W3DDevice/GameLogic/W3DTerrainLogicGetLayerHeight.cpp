// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /ICode/Libraries/Include/Lib
//
// W3DTerrainLogic::getLayerHeight, BFME 2's rework of Zero Hour's body. The
// normal is preset before the terrain check, the ground layer returns the
// height map height directly, wall layers (>= 0x10) ask the pathfinder at
// 0x002EF68C, a missing bridge falls back to the pathfinder's per-layer height
// (the ledger's Rva002E7482), and a bridge wins only when above the ground.

#include "Coord3D.h"

enum PathfindLayerEnum
{
	LAYER_INVALID = 0,
	LAYER_GROUND = 1,
	LAYER_WALL = 0x10
};

class Bridge
{
public:
	float getBridgeHeight(const Coord3D *loc, Coord3D *normal);
};

class Rva002E7482
{
public:
	float rva002E7482(int layer);
};

class Pathfinder
{
public:
	float rva002EF68C(PathfindLayerEnum layer, const Coord3D *loc, Coord3D *normal);
};

class AI
{
public:
	Pathfinder *pathfinder() { return m_pathfinder; }
private:
	char m_pad00[0x10];
	Pathfinder *m_pathfinder; // +0x10
};
extern AI *TheAI;

class BaseHeightMapRenderObjClass
{
public:
#define G(n) virtual void gap##n();
	G(00) G(01) G(02) G(03) G(04) G(05) G(06) G(07) G(08) G(09) G(0A) G(0B) G(0C) G(0D) G(0E) G(0F)
	G(10) G(11) G(12) G(13) G(14) G(15) G(16) G(17) G(18) G(19) G(1A) G(1B) G(1C) G(1D) G(1E) G(1F)
	G(20) G(21) G(22) G(23) G(24) G(25) G(26) G(27) G(28) G(29) G(2A) G(2B) G(2C) G(2D) G(2E) G(2F)
	G(30) G(31) G(32) G(33) G(34) G(35) G(36) G(37) G(38) G(39) G(3A) G(3B) G(3C) G(3D) G(3E) G(3F)
	G(40) G(41) G(42) G(43) G(44) G(45) G(46) G(47) G(48) G(49) G(4A) G(4B) G(4C) G(4D) G(4E) G(4F)
	G(50) G(51) G(52) G(53) G(54) G(55) G(56) G(57) G(58) G(59) G(5A) G(5B) G(5C) G(5D) G(5E) G(5F)
	G(60) G(61) G(62) G(63) G(64) G(65) G(66) G(67) G(68) G(69) G(6A) G(6B) G(6C) G(6D) G(6E) G(6F)
	G(70) G(71) G(72) G(73) G(74) G(75) G(76) G(77) G(78) G(79) G(7A) G(7B) G(7C) G(7D) G(7E) G(7F)
	G(80) G(81) G(82) G(83) G(84) G(85) G(86) G(87) G(88) G(89) G(8A) G(8B) G(8C) G(8D) G(8E) G(8F)
	G(90)
#undef G
	virtual float getHeightMapHeight(float x, float y, Coord3D *normal); // +0x244
};
extern BaseHeightMapRenderObjClass *TheTerrainRenderObject;

class W3DTerrainLogic
{
public:
#define G(n) virtual void gap##n();
	G(00) G(01) G(02) G(03) G(04) G(05) G(06) G(07) G(08) G(09) G(0A) G(0B) G(0C) G(0D) G(0E) G(0F)
	G(10) G(11) G(12) G(13) G(14) G(15) G(16) G(17) G(18) G(19) G(1A) G(1B) G(1C) G(1D) G(1E) G(1F)
	G(20) G(21) G(22) G(23) G(24) G(25) G(26) G(27) G(28) G(29)
#undef G
	virtual Bridge *findBridgeLayerAt(const Coord3D *pLoc, PathfindLayerEnum layer, bool clip = false) const; // +0xA8
	virtual float getLayerHeight(float x, float y, PathfindLayerEnum layer, Coord3D *normal = 0, bool clip = true) const;
};

// ?getLayerHeight@W3DTerrainLogic@@UBEMMMW4PathfindLayerEnum@@PAUCoord3D@@_N@Z @0x00062C95
float W3DTerrainLogic::getLayerHeight(float x, float y, PathfindLayerEnum layer, Coord3D *normal, bool clip) const
{
	if (normal) {
		normal->x = 0.0f;
		normal->y = 0.0f;
		normal->z = 1.0f;
	}
	if (!TheTerrainRenderObject)
		return 0;

	if (layer != LAYER_GROUND) {
		Coord3D loc;
		loc.x = x;
		loc.y = y;
		loc.z = 0.0f;
		float height;
		if (layer >= LAYER_WALL) {
			height = TheAI->pathfinder()->rva002EF68C(layer, &loc, normal);
			return height;
		}
		Bridge *pBridge = findBridgeLayerAt(&loc, layer, clip);
		if (pBridge) {
			float bridgeHeight = pBridge->getBridgeHeight(&loc, normal);
			if (bridgeHeight > TheTerrainRenderObject->getHeightMapHeight(x, y, normal))
				return bridgeHeight;
		} else {
			height = ((Rva002E7482 *)TheAI->pathfinder())->rva002E7482(layer);
			return height;
		}
	}
	return TheTerrainRenderObject->getHeightMapHeight(x, y, normal);
}
