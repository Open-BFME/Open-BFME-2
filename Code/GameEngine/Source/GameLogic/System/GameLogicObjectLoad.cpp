// cl: /O1 /DNDEBUG /MD /EHsc
//
// GameLogic::prepareLogicForObjectLoad, retail 0x00242C86 (151B), from a
// WorldBuilder lead with Zero Hour's GameLogic.cpp as the donor: before
// loading a save, destroy each bridge's object and towers (bridge info inline
// at Bridge +0x0C) and every KindOf-0x3C object, then process the destroy
// list.
//
// Kind-of bits 0x16 (bridge) and 0x3C are tested inline on the template's
// +0x108 bit set; Object +0x74 id, +0x38 position, +0x8C next; the object list
// head is GameLogic +0xAC, read inline.

#include "../../../../Libraries/Include/Lib/Coord3D.h"
#include "../../Common/GameLogicObjectLookupView.h"

class ThingTemplate
{
public:
	__forceinline bool isKindOf(int t) const { return (m_kindOf[t >> 3] & (1 << (t & 7))) != 0; }

private:
	unsigned char m_pad[0x108];
	unsigned char m_kindOf[0x20];
};

class Object
{
public:
	ObjectID getID() const { return m_id; }
	const Coord3D *getPosition() const { return &m_position; }
	Object *getNextObject() const { return m_next; }
	__forceinline bool isKindOf(int t) const { return m_template->isKindOf(t); }

private:
	unsigned char m_pad00[4];
	const ThingTemplate *m_template;
	unsigned char m_pad08[0x38 - 0x08];
	Coord3D m_position;
	unsigned char m_pad44[0x74 - 0x44];
	ObjectID m_id;
	unsigned char m_pad78[0x8C - 0x78];
	Object *m_next;
};

enum { BRIDGE_MAX_TOWERS = 4 };

struct BridgeInfo
{
	unsigned char m_pad00[0x54];
	ObjectID bridgeObjectID;
	ObjectID towerObjectID[BRIDGE_MAX_TOWERS];
};

class Bridge
{
public:
	const BridgeInfo *peekBridgeInfo() const { return &m_bridgeInfo; }

private:
	unsigned char m_pad00[0x0C];
	BridgeInfo m_bridgeInfo;
};

class TerrainLogic
{
public:
#define TERRAIN_SLOT(n) virtual void slot##n();
	TERRAIN_SLOT(0) TERRAIN_SLOT(1) TERRAIN_SLOT(2) TERRAIN_SLOT(3) TERRAIN_SLOT(4)
	TERRAIN_SLOT(5) TERRAIN_SLOT(6) TERRAIN_SLOT(7) TERRAIN_SLOT(8) TERRAIN_SLOT(9)
	TERRAIN_SLOT(10) TERRAIN_SLOT(11) TERRAIN_SLOT(12) TERRAIN_SLOT(13) TERRAIN_SLOT(14)
	TERRAIN_SLOT(15) TERRAIN_SLOT(16) TERRAIN_SLOT(17) TERRAIN_SLOT(18) TERRAIN_SLOT(19)
	TERRAIN_SLOT(20) TERRAIN_SLOT(21) TERRAIN_SLOT(22) TERRAIN_SLOT(23) TERRAIN_SLOT(24)
	TERRAIN_SLOT(25) TERRAIN_SLOT(26) TERRAIN_SLOT(27) TERRAIN_SLOT(28) TERRAIN_SLOT(29)
	TERRAIN_SLOT(30) TERRAIN_SLOT(31) TERRAIN_SLOT(32) TERRAIN_SLOT(33) TERRAIN_SLOT(34)
	TERRAIN_SLOT(35) TERRAIN_SLOT(36) TERRAIN_SLOT(37) TERRAIN_SLOT(38) TERRAIN_SLOT(39)
	TERRAIN_SLOT(40)
#undef TERRAIN_SLOT
	virtual Bridge *findBridgeAt(const Coord3D *pLoc) const; // 0xA4
};
extern TerrainLogic *TheTerrainLogic;

extern GameLogic *TheGameLogic;

void GameLogic::prepareLogicForObjectLoad()
{
	Object *obj;
	Object *next;
	for (obj = m_firstObject; obj; obj = next) {
		next = obj->getNextObject();
		if (obj->isKindOf(0x16)) {
			Bridge *bridge = TheTerrainLogic->findBridgeAt(obj->getPosition());
			const BridgeInfo *info = bridge->peekBridgeInfo();
			Object *bridgeObj = findObjectByID(info->bridgeObjectID);
			for (int i = 0; i < BRIDGE_MAX_TOWERS; ++i) {
				Object *tower = findObjectByID(info->towerObjectID[i]);
				if (tower)
					destroyObject(tower);
			}
			destroyObject(bridgeObj);
		} else if (obj->isKindOf(0x3C)) {
			destroyObject(obj);
		}
	}
	processDestroyList();
}
