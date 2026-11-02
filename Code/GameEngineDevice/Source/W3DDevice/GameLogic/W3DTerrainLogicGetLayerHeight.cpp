// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /ICode/Libraries/Include/Lib C:/Program Files/Git/ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
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

#include "../../../../GameEngine/Include/GameLogic/AIPathfind.h"

#include "../../../../GameEngine/Include/GameLogic/AI.h"
extern AI *TheAI;

#include "../../../Include/W3DDevice/GameClient/BaseHeightMap.h"
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
			height = TheAI->pathfinder()->GetWallHeight(layer, &loc, normal);
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
