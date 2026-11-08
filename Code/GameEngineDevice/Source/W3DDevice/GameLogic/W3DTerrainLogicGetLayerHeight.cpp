// cl: /D_OPERATOR_NEW_DEFINED_ /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /ICode/Libraries/Include/Lib /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// stlport
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

#include "../../../../GameEngine/Include/GameLogic/BridgeClass.h"

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

#include "../../../Include/W3DDevice/GameLogic/W3DTerrainLogicClass.h"

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
