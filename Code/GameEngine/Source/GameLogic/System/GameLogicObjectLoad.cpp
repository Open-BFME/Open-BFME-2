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
#include "../../Common/Thing/thing.h"
#include "../../../../../reference/shims/moduledata/Common/Snapshot.h"

enum NameKeyType { NAMEKEY_INVALID = 0 };
enum ObjectStatusTypes { OBJECT_STATUS_0x37 = 0x37 };
class Module;
class Drawable;
class Player;

class ThingTemplate
{
public:
	__forceinline bool isKindOf(int t) const { return (m_kindOf[t >> 3] & (1 << (t & 7))) != 0; }
	void GetAssetList(int a, int b);

	char m_pad[0x108];
	unsigned char m_kindOf[0x20]; // +0x108
	char m_pad128[0x4D0 - 0x128];
	float m_orient4D0; // +0x4D0
};

class Object : public Thing, public Snapshot
{
public:
	void rva0028ACEE(int a, int b);
protected: Module *findModule(NameKeyType) const;
public: Module *lookupModule(NameKeyType key) const {return findModule(key);}
	bool isMassSelectable() const;
	Drawable *getDrawable() const;
	Player *getControllingPlayer() const;
	void *rva0028BD3A() const;
	void rva0029041B(Player *player);
	void rva00290496(Player *player);
	void friend_bindToDrawable( Drawable *draw );
	void rva0028B31A(int val);
	bool testStatus(ObjectStatusTypes status) const;
	const ThingTemplate *getTemplate() const { return m_template; }
	ObjectID getID() const { return m_id; }
	Object *getNextObject() const { return m_next; }

	char m_pad64[0x74 - 0x64];
	ObjectID m_id; // +0x74
	char m_pad78[0x8C - 0x78];
	Object *m_next; // +0x8C
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
	virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5();
	virtual float getGroundHeight(float,float,Coord3D*); // slot 6
	virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12();
	virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18();
	virtual void v19(); virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24();
	virtual void v25(); virtual void v26(); virtual void v27(); virtual void v28(); virtual void v29(); virtual void v30();
	virtual void v31(); virtual void v32(); virtual void v33(); virtual void v34(); virtual void v35(); virtual void v36();
	virtual void v37(); virtual void v38(); virtual void v39(); virtual void v40();
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
		if (obj->getTemplate()->isKindOf(0x16)) {
			Bridge *bridge = TheTerrainLogic->findBridgeAt(obj->getPosition());
			const BridgeInfo *info = bridge->peekBridgeInfo();
			Object *bridgeObj = findObjectByID(info->bridgeObjectID);
			for (int i = 0; i < BRIDGE_MAX_TOWERS; ++i) {
				Object *tower = findObjectByID(info->towerObjectID[i]);
				if (tower)
					destroyObject(tower);
			}
			destroyObject(bridgeObj);
		} else if (obj->getTemplate()->isKindOf(0x3C)) {
			destroyObject(obj);
		}
	}
	processDestroyList();
}
