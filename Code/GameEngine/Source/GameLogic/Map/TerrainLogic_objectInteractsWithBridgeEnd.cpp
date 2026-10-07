// cl: /O1 /DNDEBUG /MD /arch:SSE /ICode/Libraries/Include/Lib
//
// TerrainLogic::objectInteractsWithBridgeLayer and objectInteractsWithBridgeEnd,
// slots 43 and 44 of the TerrainLogic vftable (0x007FB2C8; slots 65 and 66 of
// W3DTerrainLogic's at 0x007C5838). Both are Zero Hour's
// (GameLogic/Map/TerrainLogic.cpp): the bridge on the object's layer, the point
// test (layer only), a pathfind-cell-padded box around the object tested
// against the bridge ends, the deck height within LAYER_Z_CLOSE_ENOUGH_F and
// (layer only) the rubble check. BFME 2 drops the LAYER_WALL case of the layer
// test.
//
// Target facts: getFirstBridge is slot 40 (+0xA0); the bridge list links at
// Bridge+0x04, the layer sits at Bridge+0xC4 and the end corners at
// Bridge+0x28..0x58 (as Bridge::isPointOnBridge 0x0027EEAD lays them out), so
// Zero Hour's BridgeInfo starts at +0x0C and its damage state lands at +0x5C,
// compared with 3 (BODY_RUBBLE). The object's position is Object+0x38 and the
// radius it pads is Object+0xB8, which Zero Hour reads as the geometry's minor
// radius. The callees are the Bridge methods Zero Hour calls in this order:
// isPointOnBridge (rowed), isCellOnEnd (0x0027C79C) and getBridgeHeight
// (0x0027FD2A).
#include "Coord2D.h"
#include "Coord3D.h"

typedef bool Bool;
typedef int Int;
typedef float Real;

#include <math.h>
#include <stddef.h>

enum PathfindLayerEnum
{
	LAYER_INVALID = 0,
	LAYER_GROUND = 1
};

enum BodyDamageType
{
	BODY_PRISTINE = 0,
	BODY_DAMAGED = 1,
	BODY_REALLYDAMAGED = 2,
	BODY_RUBBLE = 3
};

#define PATHFIND_CELL_SIZE_F 10.0f
#define LAYER_Z_CLOSE_ENOUGH_F 10.0f

struct Region2D
{
	Coord2D lo;
	Coord2D hi;
};

class GeometryInfo
{
public:
	Real getMinorRadius() const { return m_minorRadius; }
private:
	char m_pad00[0x10];
	Real m_minorRadius; // +0x10
};

class Object
{
public:
	const Coord3D *getPosition() const { return &m_pos; }
	const GeometryInfo &getGeometryInfo() const { return m_geometryInfo; }
private:
	char m_pad00[0x38];
	Coord3D m_pos; // +0x38
	char m_pad44[0xA8 - 0x44];
	GeometryInfo m_geometryInfo; // +0xA8
};

// Zero Hour's BridgeInfo; Bridge holds it at +0x0C.
struct BridgeInfo
{
	Coord3D from; // +0x00
	Coord3D to; // +0x0C
	Real bridgeWidth; // +0x18
	Coord3D fromLeft; // +0x1C
	Coord3D fromRight; // +0x28
	Coord3D toLeft; // +0x34
	Coord3D toRight; // +0x40
	Int bridgeIndex; // +0x4C
	BodyDamageType curDamageState; // +0x50
};

class Bridge
{
public:
	Bridge *getNext() { return m_next; }
	const BridgeInfo *peekBridgeInfo() const { return &m_bridgeInfo; }
	Bool isPointOnBridge(const Coord3D *loc);
	Int getLayer() const { return m_layer; }
	Bool isCellOnEnd(const Region2D *cell);
	Real getBridgeHeight(const Coord3D *loc, Coord3D *normal);
private:
	void *m_pad00;
	Bridge *m_next; // +0x04
	char m_pad08[0x0C - 0x08];
	BridgeInfo m_bridgeInfo; // +0x0C
	char m_pad60[0xC4 - 0x60];
	Int m_layer; // +0xC4
};

template <int N> class TerrainLogicSlots : public TerrainLogicSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]);
};
template <> class TerrainLogicSlots<1>
{
public:
	virtual void gap(char (*)[1]);
};

class TerrainLogic : public TerrainLogicSlots<40>
{
public:
	virtual Bridge *getFirstBridge() const; // +0xA0
	virtual void slot41();
	virtual void slot42();
	virtual Bool objectInteractsWithBridgeLayer(Object *obj, Int layer, Bool considerBridgeHealth = true) const; // +0xAC
	virtual Bool objectInteractsWithBridgeEnd(Object *obj, Int layer) const; // +0xB0
};

// ?objectInteractsWithBridgeLayer@TerrainLogic@@UBE_NPAVObject@@H_N@Z @0x002804B2
// Zero Hour's test less its LAYER_WALL case.
Bool TerrainLogic::objectInteractsWithBridgeLayer(Object *obj, Int layer, Bool considerBridgeHealth) const
{
	if (layer == LAYER_GROUND) return false;
	Bridge *pBridge = getFirstBridge();

	while (pBridge ) {
		if (pBridge->getLayer() == layer) {
			Bool match = false;
			if (pBridge->isPointOnBridge(obj->getPosition()) ) {
				match = true;
			}

			Real radius = obj->getGeometryInfo().getMinorRadius();
			radius += PATHFIND_CELL_SIZE_F/2.0f;
			Region2D bounds;
			bounds.lo.x = obj->getPosition()->x;
			bounds.lo.y = obj->getPosition()->y;
			bounds.hi = bounds.lo;
			bounds.lo.x -= radius;
			bounds.lo.y -= radius;
			bounds.hi.x += radius;
			bounds.hi.y += radius;
			if (pBridge->isCellOnEnd(&bounds)) {
				match = true;
			}

			if (match) {
				Real bridgeHeight = pBridge->getBridgeHeight(obj->getPosition(), NULL);
				Real delta = fabs(obj->getPosition()->z-bridgeHeight);
				if (delta>LAYER_Z_CLOSE_ENOUGH_F) {
					return false;
				}

				// make sure it's not destroyed. can't interact with dead bridges.
				if (considerBridgeHealth && pBridge->peekBridgeInfo()->curDamageState == BODY_RUBBLE)
				{
					return false;
				}

				return true;
			}
			return false;
		}

		pBridge = pBridge->getNext();
	}
	return(false);
}

// ?objectInteractsWithBridgeEnd@TerrainLogic@@UBE_NPAVObject@@H@Z @0x002805C1
Bool TerrainLogic::objectInteractsWithBridgeEnd(Object *obj, Int layer) const
{
	if (layer == LAYER_GROUND) return false;
	Bridge *pBridge = getFirstBridge();

	while (pBridge ) {
		if (pBridge->getLayer() == layer) {
			Bool match = false;

			Real radius = obj->getGeometryInfo().getMinorRadius();
			radius += PATHFIND_CELL_SIZE_F/2.0f;
			Region2D bounds;
			bounds.lo.x = obj->getPosition()->x;
			bounds.lo.y = obj->getPosition()->y;
			bounds.hi = bounds.lo;
			bounds.lo.x -= radius;
			bounds.lo.y -= radius;
			bounds.hi.x += radius;
			bounds.hi.y += radius;
			if (pBridge->isCellOnEnd(&bounds)) {
				match = true;
			}

			if (match) {
				Real bridgeHeight = pBridge->getBridgeHeight(obj->getPosition(), NULL);
				Real delta = fabs(obj->getPosition()->z-bridgeHeight);
				if (delta>LAYER_Z_CLOSE_ENOUGH_F)
				{
					return false;
				}
				return true;
			}
			return false;
		}

		pBridge = pBridge->getNext();
	}
	return(false);
}
