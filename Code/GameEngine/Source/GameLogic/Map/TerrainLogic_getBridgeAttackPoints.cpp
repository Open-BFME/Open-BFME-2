// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /ICode/Libraries/Include/Lib
//
// ?getBridgeAttackPoints@TerrainLogic@@QAEXPBVObject@@PAUTBridgeAttackInfo@@@Z
// retail 0x0027D483..0x0027D5AD (298B).
//
// Zero Hour reference TerrainLogic::getBridgeAttackPoints (GeneralsMD
// TerrainLogic.cpp): walk the bridges from getFirstBridge for the one whose
// BridgeInfo::bridgeObjectID is the bridge object's ID; on a hit place the
// two attack points half the bridge width in from `from` and `to` along the
// normalized from->to direction and return; otherwise both points are the
// object's position.
//
// Target facts: getFirstBridge is TerrainLogic vtable slot 40 (+0xA0); the
// Bridge list link is +0x04 and BridgeInfo starts at Bridge +0x0C (from +0x00
// to +0x0C fromLeft +0x1C fromRight +0x28 bridgeObjectID +0x54 as in ZH); the
// Object ID is +0x74 and the position +0x38; Coord3D::normalize 0x000035B6 and
// Coord3D::length 0x00003571 are rowed; 0.5f at 0x007C26F0 is the /2.0f.
// WorldBuilder twin 0x00C49B90 has the same `len = length(); len /= 2` and
// the same return inside the loop; the ZH body compiles to retail verbatim.
// Donor names and layout are carried from ZH; the vtable slot and offsets
// are from the retail body.
#include "Coord3D.h"

typedef float Real;
typedef int ObjectID;

class Object
{
public:
	const Coord3D *getPosition() const { return &m_pos; }
	ObjectID getID() const { return m_id; }

private:
	char m_pad00[0x38];
	Coord3D m_pos;		// +0x38
	char m_pad44[0x74 - 0x44];
	ObjectID m_id;		// +0x74
};

class BridgeInfo
{
public:
	Coord3D from;		// +0x00
	Coord3D to;		// +0x0C
	Real bridgeWidth;	// +0x18
	Coord3D fromLeft;	// +0x1C
	Coord3D fromRight;	// +0x28
	Coord3D toLeft;		// +0x34
	Coord3D toRight;	// +0x40
	int bridgeIndex;	// +0x4C
	int curDamageState;	// +0x50
	ObjectID bridgeObjectID;	// +0x54
};

class Bridge
{
public:
	Bridge *getNext() { return m_next; }
	const BridgeInfo *peekBridgeInfo() const { return &m_bridgeInfo; }

private:
	void *m_vtbl;		// MemoryPoolObject vptr
	Bridge *m_next;		// +0x04
	char m_templateName[4];	// +0x08 AsciiString
	BridgeInfo m_bridgeInfo;	// +0x0C
};

struct TBridgeAttackInfo
{
	Coord3D attackPoint1;
	Coord3D attackPoint2;
};

class TerrainLogic
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual void slot27();
	virtual void slot28();
	virtual void slot29();
	virtual void slot30();
	virtual void slot31();
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void slot35();
	virtual void slot36();
	virtual void slot37();
	virtual void slot38();
	virtual void slot39();
	virtual Bridge *getFirstBridge() const;	// slot 40 (+0xA0)

	void getBridgeAttackPoints(const Object *bridge, TBridgeAttackInfo *attackInfo);
};

void TerrainLogic::getBridgeAttackPoints(const Object *bridge, TBridgeAttackInfo *attackInfo)
{
	ObjectID id = bridge->getID();
	Bridge *pBridge = getFirstBridge();
	while (pBridge) {
		const BridgeInfo *info = pBridge->peekBridgeInfo();
		if (info->bridgeObjectID == id) {
			// found the right bridge.
			Coord3D delta;
			delta.x = info->to.x - info->from.x;
			delta.y = info->to.y - info->from.y;
			delta.z = info->to.z - info->from.z;
			delta.normalize();
			Coord3D width;
			width.x = info->fromRight.x - info->fromLeft.x;
			width.y = info->fromRight.y - info->fromLeft.y;
			width.z = info->fromRight.z - info->fromLeft.z;
			Real len = width.length();
			len /= 2.0f;
			attackInfo->attackPoint1.x = info->from.x + delta.x*len;
			attackInfo->attackPoint1.y = info->from.y + delta.y*len;
			attackInfo->attackPoint1.z = info->from.z + delta.z*len;

			attackInfo->attackPoint2.x = info->to.x - delta.x*len;
			attackInfo->attackPoint2.y = info->to.y - delta.y*len;
			attackInfo->attackPoint2.z = info->to.z - delta.z*len;

			return;
		}
		pBridge = pBridge->getNext();
	}
	attackInfo->attackPoint1 = *bridge->getPosition();
	attackInfo->attackPoint2 = *bridge->getPosition();
}
