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
	void rva0028B4CE(PathfindLayerEnum layer);
	const Coord3D *getPosition() const { return &m_pos; }

private:
	char m_pad00[0x38];
	Coord3D m_pos;
};

class TerrainLogic
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0C();
	virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1C();
	virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2C();
	virtual void slot30(); virtual void slot34(); virtual void slot38(); virtual void slot3C();
	virtual void slot40(); virtual void slot44(); virtual void slot48(); virtual void slot4C();
	virtual void slot50(); virtual void slot54(); virtual void slot58(); virtual void slot5C();
	virtual void slot60(); virtual void slot64(); virtual void slot68(); virtual void slot6C();
	virtual void slot70(); virtual void slot74(); virtual void slot78(); virtual void slot7C();
	virtual void slot80(); virtual void slot84(); virtual void slot88(); virtual void slot8C();
	virtual void slot90(); virtual void slot94(); virtual void slot98(); virtual void slot9C();
	virtual void slotA0(); virtual void slotA4(); virtual void slotA8();
	virtual Bool objectInteractsWithBridgeLayer(Object *obj, Int layer, Bool considerBridgeHealth) const;
};
extern TerrainLogic *TheTerrainLogic;

struct Rva002ED236Pos
{
	Real x;
	Real y;
	Real z;
	Rva002ED236Pos(const Coord3D &c) { x = c.x; y = c.y; z = c.z; }
	~Rva002ED236Pos() {}
};

struct PathfindLayerView
{
	char m_pad00[0x38];
	Int m_38;
	char m_pad3C[0x40 - 0x3C];
};

class Pathfinder
{
public:
	Real GetWallHeight(PathfindLayerEnum layer, const Coord3D *pos, Coord3D *normal);
	bool IsPointOnRamp(const Coord3D *pos);
	PathfindLayerEnum rva002ED236(Object *obj, Rva002ED236Pos pos);
	void rva002EF2A6(Object *obj);
	void UpdateLayer(Object *obj, PathfindLayerEnum layer);

private:
	char m_pad00[0x60];
	PathfindLayerView m_layers[1];
};

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
		if (m_layers[layer].m_38 != 0)
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
	obj->rva0028B4CE(newLayer);
	rva002EF2A6(obj);
}
