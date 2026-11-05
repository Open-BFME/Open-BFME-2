// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc
// Retail 0x00457577, 448B: BridgeBehavior::handleObjectsOnBridgeOnDie.
// Target evidence: the only caller is BridgeBehavior::onDie (0x004581FD, via
// its die interface at this+0x28), which runs it between the tower kills and
// the death-frame store exactly as Zero Hour's BridgeBehavior::onDie does.
// The body is Zero Hour's handleObjectsOnBridgeOnDie (GeneralsMD
// GameEngine/Source/GameLogic/Object/Behavior/BridgeBehavior.cpp) with BFME 2
// deltas: Bridge::getBridgeInfo is the inline copy of the BridgeInfo held at
// Bridge+0x0C (ctor 0x0027C36A, operator= 0x00085420), the layer is read from
// Bridge+0xC4, the range query is the native by-value result (0x006255D0),
// and every surviving object is killed with (8, 0) - the physics fall-over
// branch is gone. BridgeInfo's fromLeft/fromRight/toLeft/toRight sit at
// +0x1C/+0x28/+0x34/+0x40 as in ZH. The kind-of tests read the template's
// bitset bytes +0x10A bit 6 and +0x10B bit 0 (ZH KINDOF_BRIDGE and
// KINDOF_BRIDGE_TOWER); the BFME bit names are not recovered here.


// Coord3D: shared derived view (Coord3DBase base); no private copy.
#define COORD3D_DV_CTOR_EXTERN
#define COORD3D_DV_DTOR_EXTERN
#include "../../../../../Libraries/Include/Lib/Coord3DDerivedView.h"


#include "../../../../../Libraries/Include/Lib/Coord2D.h"

#include "../../../../../Libraries/Include/Lib/Region3D.h"

// The 12-byte BridgeInfo entries use the opaque ctor already owned by
// Rva0027C36ACtor.cpp. Their retail identity is still unknown; Region3D is 24 bytes.
class Rva0027C36ATwelve
{
public:
	Rva0027C36ATwelve();
	char m_d[12];
};

class Rva0027C36ASix
{
public:
	Rva0027C36ASix();
	char m_d[6];
};

// BridgeInfo (address-derived class name, as rowed at 0x0027C36A).
class Rva0027C36A
{
public:
	Rva0027C36A();
	Rva0027C36A &operator=(const Rva0027C36A &that);
	Coord3DBase m_from;
	Coord3DBase m_to;
	float m_bridgeWidth;
	Coord3DBase m_fromLeft;
	Coord3DBase m_fromRight;
	Coord3DBase m_toLeft;
	Coord3DBase m_toRight;
	int m_4c;
	int m_50;
	int m_54;
	int m_58[4];
	unsigned char m_68;
	char m_pad69[3];
	Rva0027C36ATwelve m_6c[4];
	Rva0027C36ASix m_9c[2];
};

enum PathfindLayerEnum
{
	LAYER_GROUND = 1
};

enum DamageType
{
	BridgeDieDamageType8 = 8
};

enum DeathType
{
	BridgeDieDeathType0 = 0
};

#include "../../../../Include/Common/ThingTemplate.h"

#include "../../../Common/Thing/thing.h"

class Object : public Thing
{
public:
	int rva0028B511() const;
	void setLayer(PathfindLayerEnum layer);
	void kill(DamageType damageType, DeathType deathType);
};

class Bridge
{
public:
	unsigned char m_pad00[0x0C];
	Rva0027C36A m_bridgeInfo;
	unsigned char m_padB4[0xC4 - 0xB4];
	int m_layer;
};

#include "../../../../Include/GameLogic/TerrainLogic.h"

extern TerrainLogic *TheTerrainLogic;

bool PointInsideArea2D(const Coord3D *ptToTest, const Coord3D *area, int numPointsInArea);

#include "../../../Common/PartitionRangeQueryCallView.h"
extern PartitionManager *ThePartitionManager;

class BridgeBehavior
{
protected:
	void handleObjectsOnBridgeOnDie();

public:
	void *m_vtable;
	const void *m_moduleData;
	Object *m_object;
};

void BridgeBehavior::handleObjectsOnBridgeOnDie()
{
	const Object *bridge = m_object;
	const Coord3D *bridgePos = &bridge->m_cachedPos;

	Bridge *terrainBridge = TheTerrainLogic->findBridgeAt(&m_object->m_cachedPos);
	if (terrainBridge)
	{
		int bridgeLayer = terrainBridge->m_layer;

		Rva0027C36A bridgeInfo;
		bridgeInfo = terrainBridge->m_bridgeInfo;

		Coord3D bridgePolygon[4];
		static_cast<Coord3DBase &>(bridgePolygon[0]) = bridgeInfo.m_fromLeft;
		static_cast<Coord3DBase &>(bridgePolygon[1]) = bridgeInfo.m_fromRight;
		static_cast<Coord3DBase &>(bridgePolygon[2]) = bridgeInfo.m_toRight;
		static_cast<Coord3DBase &>(bridgePolygon[3]) = bridgeInfo.m_toLeft;

		float lowBridgeZ = bridgePolygon[0].z;
		for (int i = 0; i < 4; ++i)
			if (bridgePolygon[i].z < lowBridgeZ)
				lowBridgeZ = bridgePolygon[i].z;

		Coord2D v;
		v.x = bridgeInfo.m_toLeft.x - bridgePos->x;
		v.y = bridgeInfo.m_toLeft.y - bridgePos->y;
		float radius = v.length();

		BfmeWideResult iter = ThePartitionManager->rva006255D0(bridgePos, radius, 0, 0);
		Object *other;
		while ((other = iter.next()) != 0)
		{
			if ((((const unsigned char *)other->m_template->m_kindof)[2] & 0x40) || (((const unsigned char *)other->m_template->m_kindof)[3] & 1))
				continue;
			if (other->isAboveTerrain())
				continue;
			if (other->m_cachedPos.z < lowBridgeZ)
				continue;
			if (!PointInsideArea2D(&other->m_cachedPos, bridgePolygon, 4))
				continue;
			if (bridgeLayer != other->rva0028B511())
				continue;
			if (other->rva0028B511() == bridgeLayer)
				other->setLayer(LAYER_GROUND);
			other->kill(BridgeDieDamageType8, BridgeDieDeathType0);
		}
	}
}
