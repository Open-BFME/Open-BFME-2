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

struct Coord3DBase
{
	float x;
	float y;
	float z;
};

// class-gate: allow Coord3D the bridge polygon is built and torn down through BFME 2's out-of-line empty Coord3D constructor and destructor (the eh vector iterators push 0x0047A6A9 and 0x000B3FD0); the canonical data-only header cannot declare them; same three floats
// The polygon array is built by the EH vector constructor with the shared
// out-of-line Coord3D ctor (0x0047A6A9) and dtor (0x000B3FD0); BridgeInfo's
// own points carry neither, since its constructor opens no unwind state.
struct Coord3D : public Coord3DBase
{
	Coord3D();
	~Coord3D();
};

#include "../../../../../Libraries/Include/Lib/Coord2D.h"

class Region3D
{
public:
	Region3D();
	float m_x;
	float m_y;
	float m_z;
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
	Region3D m_6c[4];
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

class ThingTemplate
{
public:
	unsigned char m_pad00[0x10A];
	unsigned char m_kindOf10A;
	unsigned char m_kindOf10B;
};

class Thing
{
public:
	bool isAboveTerrain() const;
	void *m_vtable;
	const ThingTemplate *m_template;
	unsigned char m_pad08[0x38 - 0x08];
	Coord3D m_pos;
};

class Object : public Thing
{
public:
	int rva0028B511() const;
	void rva0028B4CE(PathfindLayerEnum layer);
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

class TerrainLogic
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v0a();
	virtual void v0b();
	virtual void v0c();
	virtual void v0d();
	virtual void v0e();
	virtual void v0f();
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
	virtual void v1a();
	virtual void v1b();
	virtual void v1c();
	virtual void v1d();
	virtual void v1e();
	virtual void v1f();
	virtual void v20();
	virtual void v21();
	virtual void v22();
	virtual void v23();
	virtual void v24();
	virtual void v25();
	virtual void v26();
	virtual void v27();
	virtual void v28();
	virtual Bridge *findBridgeAt(const Coord3D *loc) const;
};

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
	const Coord3D *bridgePos = &bridge->m_pos;

	Bridge *terrainBridge = TheTerrainLogic->findBridgeAt(&m_object->m_pos);
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
			if ((other->m_template->m_kindOf10A & 0x40) || (other->m_template->m_kindOf10B & 1))
				continue;
			if (other->isAboveTerrain())
				continue;
			if (other->m_pos.z < lowBridgeZ)
				continue;
			if (!PointInsideArea2D(&other->m_pos, bridgePolygon, 4))
				continue;
			if (bridgeLayer != other->rva0028B511())
				continue;
			if (other->rva0028B511() == bridgeLayer)
				other->rva0028B4CE(LAYER_GROUND);
			other->kill(BridgeDieDamageType8, BridgeDieDeathType0);
		}
	}
}
