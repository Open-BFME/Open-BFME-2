// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
// ?UpdateLayer@Pathfinder@@QAEXPAVObject@@W4PathfindLayerEnum@@@Z retail
// 0x002F11A1..0x002F133C (411 bytes). WorldBuilder twin 0x00D388B0 is
// Pathfinder::UpdateLayer in pathfinder.cpp (asserts 1910..2004; callgraph
// score 4.0): a BFME 2 rewrite of Zero Hour's Pathfinder::updateLayer. It
// reads the old layer (rowed Object 0x0028B511) and grades the request:
// bridge layers 2..15 (rowed predicate 0x001E3679) try the bridge; ramps
// (0x10) and ground (1) leaving a wall layer fall back to ramp/ground; wall
// layers 0x11..0x40 (rowed predicate 0x002E6E8A whose callers test al) stay
// unless the object's z is more than 10 from the rowed GetWallHeight
// 0x002EF68C. Bridges consult the pinned layer query 0x002ED236 when the
// layer record at +0x60 + layer*0x40 has its +0x38 word set and TheTerrainLogic
// slot +0xAC (objectInteractsWithBridgeLayer) otherwise. Ramp tests use the
// rowed IsPointOnRamp 0x002E757D. The result goes through the rowed setter
// 0x0028B4CE and then the pinned 0x002EF2A6 (WB Pathfinder::AdjustLayer).
#include <math.h>
#include "../../../../Libraries/Include/Lib/Coord3D.h"

typedef bool Bool;
typedef int Int;
typedef float Real;

enum PathfindLayerEnum
{
	LAYER_INVALID = 0,
	LAYER_GROUND = 1,
	LAYER_RAMPS = 0x10
};

bool Rva001E3679(int layer);
int Rva002E6E8AGet(int layer);

class Object
{
public:
	int rva0028B511() const;
	void setLayer(PathfindLayerEnum layer);
	const Coord3D *getPosition() const { return &m_pos; }

private:
	char m_pad00[0x38];
	Coord3D m_pos;
};

#include "../../../Include/GameLogic/TerrainLogic.h"
extern TerrainLogic *TheTerrainLogic;

struct Rva002ED236Pos
{
	Real x;
	Real y;
	Real z;
	Rva002ED236Pos(const Coord3D &c) { x = c.x; y = c.y; z = c.z; }
	~Rva002ED236Pos() {}
};

#include "../../../Include/GameLogic/AIPathfind.h"

void Pathfinder::UpdateLayer(Object *obj, PathfindLayerEnum layer)
{
	PathfindLayerEnum oldLayer = (PathfindLayerEnum)obj->rva0028B511();
	PathfindLayerEnum newLayer = oldLayer;
	const Real MAX_Z_TO_WALL = 10.0f;
	Int mode = 3;
	if (Rva001E3679(layer))
		mode = 0;
	if (layer == LAYER_RAMPS)
		mode = 1;
	if (layer == LAYER_GROUND)
	{
		mode = 3;
		if ((unsigned char)Rva002E6E8AGet(oldLayer))
			mode = 1;
	}
	if ((unsigned char)Rva002E6E8AGet(layer))
	{
		mode = 2;
		if (fabs(obj->getPosition()->z - GetWallHeight(layer, obj->getPosition(), 0)) > MAX_Z_TO_WALL)
			mode = 1;
		if (oldLayer == LAYER_GROUND)
			mode = 1;
	}

	if (mode == 3)
	{
		if (oldLayer == LAYER_RAMPS && IsPointOnRamp(obj->getPosition()))
			return;
		newLayer = LAYER_GROUND;
	}
	else if (mode == 0)
	{
		if (oldLayer == LAYER_RAMPS && IsPointOnRamp(obj->getPosition()))
			return;
		Bool onLayer;
		if (m_layers[layer].m_triggers != 0)
			onLayer = rva002ED236(obj, *obj->getPosition()) == layer;
		else
			onLayer = TheTerrainLogic->objectInteractsWithBridgeLayer(obj, layer, true);
		if (onLayer)
			newLayer = layer;
		else
			newLayer = oldLayer;
	}
	else if (mode == 1)
	{
		newLayer = oldLayer;
		if (IsPointOnRamp(obj->getPosition()))
			newLayer = LAYER_RAMPS;
		else if (oldLayer == LAYER_RAMPS)
			newLayer = LAYER_GROUND;
	}
	else if (mode == 2)
	{
		if (IsPointOnRamp(obj->getPosition()))
			newLayer = LAYER_RAMPS;
		else
			newLayer = layer;
	}
	obj->setLayer(newLayer);
	AdjustLayer(obj);
}
