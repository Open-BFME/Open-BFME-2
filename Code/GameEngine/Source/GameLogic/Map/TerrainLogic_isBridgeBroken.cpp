// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// ZH donor: GeneralsMD TerrainLogic.cpp isBridgeRepaired and isBridgeBroken.
// ?isBridgeRepaired@TerrainLogic@@QAE_NPBVObject@@@Z @0x0027D40B 60B and
// ?isBridgeBroken@TerrainLogic@@QAE_NPBVObject@@@Z @0x0027D447 60B.
// Target evidence: the matched BRIDGE_REPAIRED and BRIDGE_BROKEN evaluators
// (0x003E3DC6, 0x003E3D95) call them on TheTerrainLogic with the named
// bridge; both walk the bridge list from vslot +0xA0 (getFirstBridge),
// match the bridge object ID (Object +0x74) and differ only in testing the
// changed damage state against BODY_RUBBLE (3) with == or !=. Donor-carried
// layout: Bridge {vptr, m_next, m_templateName, BridgeInfo}, which puts curDamageState,
// bridgeObjectID and damageStateChanged at the retail +0x5C, +0x60, +0x74.

#include "ascii_string.h"

typedef int ObjectID;
enum BodyDamageType { BODY_PRISTINE, BODY_DAMAGED, BODY_REALLYDAMAGED, BODY_RUBBLE };

#include "../../../../Libraries/Include/Lib/Coord3D.h"
// Retail 0x0027D3D9: placement manager slot 20 takes template and position
// plus Matrix3D::Get_Z_Rotation() and template scale. ElvenWood calls this
// for non-tree, non-shrub terrain templates. The manager uses its ledger global.
class ThingTemplate;
class Matrix3D {public: float Get_Z_Rotation() const;};

struct BridgeInfo
{
	Coord3D from;
	Coord3D to;
	float bridgeWidth;
	Coord3D fromLeft;
	Coord3D fromRight;
	Coord3D toLeft;
	Coord3D toRight;
	int bridgeIndex;
	BodyDamageType curDamageState;
	ObjectID bridgeObjectID;
	ObjectID towerObjectID[4];
	bool damageStateChanged;
};

class Bridge
{
public:
	virtual ~Bridge();
	Bridge *getNext() { return m_next; }
	const BridgeInfo *peekBridgeInfo() const { return &m_bridgeInfo; }

protected:
	Bridge *m_next;
	AsciiString m_templateName;
	BridgeInfo m_bridgeInfo;
};

class Object
{
public:
	ObjectID getID() const { return m_id; }
	unsigned char m_pad00[0x74];
	ObjectID m_id;
};

class TerrainLogic
{
public:
	virtual void s00();
	virtual void s01();
	virtual void s02();
	virtual void s03();
	virtual void s04();
	virtual void s05();
	virtual void s06();
	virtual void s07();
	virtual void s08();
	virtual void s09();
	virtual void s10();
	virtual void s11();
	virtual void s12();
	virtual void s13();
	virtual void s14();
	virtual void s15();
	virtual void s16();
	virtual void s17();
	virtual void s18();
	virtual void s19();
	virtual void s20();
	virtual void s21();
	virtual void s22();
	virtual void s23();
	virtual void s24();
	virtual void s25();
	virtual void s26();
	virtual void s27();
	virtual void s28();
	virtual void s29();
	virtual void s30();
	virtual void s31();
	virtual void s32();
	virtual void s33();
	virtual void s34();
	virtual void s35();
	virtual void s36();
	virtual void s37();
	virtual void s38();
	virtual void s39();
	virtual Bridge *getFirstBridge() const; // +0xA0
	void rva0027D3D9(const ThingTemplate*,const Coord3D*,const Matrix3D*,float);
	bool isBridgeRepaired(const Object *bridge);
	bool isBridgeBroken(const Object *bridge);
};

bool TerrainLogic::isBridgeRepaired(const Object *bridge)
{
	if (!bridge) return false;
	ObjectID id = bridge->getID();
	Bridge *pBridge = getFirstBridge();
	while (pBridge) {
		const BridgeInfo *info = pBridge->peekBridgeInfo();
		if (info->bridgeObjectID == id) {
			if (info->damageStateChanged) {
				if (info->curDamageState != BODY_RUBBLE) {
					return true;
				}
			}
			return false;
		}
		pBridge = pBridge->getNext();
	}
	return false;
}

bool TerrainLogic::isBridgeBroken(const Object *bridge)
{
	if (!bridge) return false;
	ObjectID id = bridge->getID();
	Bridge *pBridge = getFirstBridge();
	while (pBridge) {
		const BridgeInfo *info = pBridge->peekBridgeInfo();
		if (info->bridgeObjectID == id) {
			if (info->damageStateChanged) {
				if (info->curDamageState == BODY_RUBBLE) {
					return true;
				}
			}
			return false;
		}
		pBridge = pBridge->getNext();
	}
	return false;
}

class G00DFF080Obj;
extern G00DFF080Obj *g_00DFF080;
class TerrainPlacementManagerView {public:
 virtual void p0();
 virtual void p1();
 virtual void p2();
 virtual void p3();
 virtual void p4();
 virtual void p5();
 virtual void p6();
 virtual void p7();
 virtual void p8();
 virtual void p9();
 virtual void p10();
 virtual void p11();
 virtual void p12();
 virtual void p13();
 virtual void p14();
 virtual void p15();
 virtual void p16();
 virtual void p17();
 virtual void p18();
 virtual void p19();
 virtual void p20(const ThingTemplate*,const Coord3D*,float,float);
};
void TerrainLogic::rva0027D3D9(const ThingTemplate *templ,const Coord3D *position,const Matrix3D *matrix,float scale)
{
 reinterpret_cast<TerrainPlacementManagerView*>(g_00DFF080)->p20(templ,position,matrix->Get_Z_Rotation(),scale);
}

