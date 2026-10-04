// cl: /O1 /MD /GX /arch:SSE
//
// ?doScan@PropagandaTowerBehavior@@MAEXXZ, retail 0x00481DA4: slot 14 (+0x38)
// of PropagandaTowerBehavior's vftable 0x00C49248 (removeAllInfluence
// 0x00481D4C is slot 13, effectLogic 0x00481A9E slot 15). BFME1's
// PropagandaTowerBehavior::doScan (reference/open-bfme-1) without its
// overlord/stealth FX gating and self rule: play the (upgraded) pulse FX,
// collect every ally (0x00260EB1 with 4) alive, not this object and not a
// structure (KindOf bit 7) in the module data's scan radius through BFME2's
// partition filter chain into a new ObjectTracker list, take the effect off
// every old entry that is not in it, then replace the old list.
// Layout: ModuleData +4 (scan radius +0x08, pulse FX +0x14, upgraded pulse
// FX +0x20), object +8, m_insideList +0x28, m_upgradeRequired +0x2C.

class Object;
class Player;

class Rva000421C8
{
public:
	Rva000421C8() : m_next(0) {}
	virtual ~Rva000421C8() {}
	virtual bool allow(Object *obj) = 0;
	virtual int getPlayerMask();
	Rva000421C8 *link(Rva000421C8 *next);	// 0x00625790
	Rva000421C8 *m_next;
};

// vftable 0x00BFAD10, allow 0x0026119D: not effectively dead.
class Rva0026119DFilter : public Rva000421C8
{
public:
	virtual bool allow(Object *obj);
};

// vftable 0x00BF91BC, allow 0x002611BF.
class Rva002611BFFilter : public Rva000421C8
{
public:
	Rva002611BFFilter(const Object *obj) : m_obj(obj) {}
	virtual bool allow(Object *obj);
	const Object *m_obj;
};

// vftable 0x00BFBC90, allow 0x00260EB1: +0x08 the object, +0x0C flags,
// +0x10 whether a hit allows.
class Rva00260EB1Filter : public Rva000421C8
{
public:
	Rva00260EB1Filter(const Object *obj, int flags, bool match)
		: m_obj(obj), m_flags(flags), m_match(match) {}
	virtual bool allow(Object *obj);
	virtual int getPlayerMask();
	const Object *m_obj;
	int m_flags;
	bool m_match;
};

// The 224-bit KindOf mask; the (unused, bit) constructor is 0x00045411.
class BfmeFixedStorage0004543D
{
public:
	BfmeFixedStorage0004543D(int unused, int bit);	// 0x00045411
	BfmeFixedStorage0004543D(const BfmeFixedStorage0004543D &other) throw();
private:
	unsigned char m_bytes[28];
};

// vftable 0x00BC2908, allow 0x002610DE: accept what has every kind of the
// first mask and none of the second.
class Rva0004584D : public Rva000421C8
{
public:
	Rva0004584D(const BfmeFixedStorage0004543D &a, const BfmeFixedStorage0004543D &b) throw();
	virtual bool allow(Object *obj);
	BfmeFixedStorage0004543D m_08;
	BfmeFixedStorage0004543D m_24;
};
extern unsigned char g_00DFEFA4StoragePrototype[28];

#pragma comment(linker, "/alternatename:?getPlayerMask@Rva000421C8@@UAEHXZ=?Get_File_Handle@FileClass@@UAEPAXXZ")

struct Coord3D
{
	float x;
	float y;
	float z;
};

struct BfmeWideResult
{
	Object *next() throw();	// 0x00045623
	~BfmeWideResult();	// 0x0004AA28
	void *m_value;
};

class PartitionManager
{
public:
	BfmeWideResult iterateObjectsInRange(const Coord3D *pos, float radius, int distCalc,
		Rva000421C8 *filters, int order);	// 0x00625610
};
extern PartitionManager *ThePartitionManager;

enum ObjectID
{
	INVALID_ID = 0
};

class UpgradeTemplate
{
public:
	char m_pad00[0x04];
	int m_type;	// +0x04 (0 player, 1 object)
};

class Player
{
public:
	bool rva002AB87D(const UpgradeTemplate *upgrade) const;	// 0x002AB87D
};

class FXList
{
public:
	static void doFXObj(const FXList *fx, const Object *primary, const Object *secondary);	// 0x000B2235
};

class Object
{
public:
	Player *getControllingPlayer() const;	// 0x0028AFA9
	bool rva00290D2B(const UpgradeTemplate *upgrade) const;	// 0x00290D2B
	const Coord3D *getPosition() const { return &m_pos; }
	ObjectID getID() const { return m_id; }
	char m_pad000[0x38];
	Coord3D m_pos;		// +0x38
	char m_pad044[0x74 - 0x44];
	ObjectID m_id;		// +0x74
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);	// 0x00049DC5
};
extern GameLogic *TheGameLogic;

// vftable 0x00C49174.
class ObjectTracker
{
public:
	ObjectTracker() : objectID(INVALID_ID), next(0) {}
	virtual ~ObjectTracker();
	ObjectID objectID;
	ObjectTracker *next;
};

struct PropagandaTowerBehaviorModuleData
{
	char m_pad00[0x08];
	float m_scanRadius;		// +0x08
	char m_pad0C[0x14 - 0x0C];
	const FXList *m_pulseFX;	// +0x14
	char m_pad18[0x20 - 0x18];
	const FXList *m_upgradedPulseFX;	// +0x20
};

class PropagandaTowerBehavior
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
protected:
	virtual void removeAllInfluence();
	virtual void doScan();
	virtual void effectLogic(Object *obj, bool giving, const PropagandaTowerBehaviorModuleData *modData);
private:
	const PropagandaTowerBehaviorModuleData *getPropagandaTowerBehaviorModuleData() const
	{
		return m_moduleData;
	}
	const PropagandaTowerBehaviorModuleData *m_moduleData;	// +0x04
	Object *m_object;		// +0x08
	unsigned char m_pad0C[0x28 - 0x0C];
	ObjectTracker *m_insideList;	// +0x28
	const UpgradeTemplate *m_upgradeRequired;	// +0x2C
};

void PropagandaTowerBehavior::doScan()
{
	const PropagandaTowerBehaviorModuleData *modData = getPropagandaTowerBehaviorModuleData();
	Object *us = m_object;
	ObjectTracker *newInsideList = 0;
	bool upgradePresent = false;
	if (m_upgradeRequired) {
		switch (m_upgradeRequired->m_type) {
		case 0: {
			Player *player = us->getControllingPlayer();
			upgradePresent = player->rva002AB87D(m_upgradeRequired);
			break;
		}
		case 1:
			upgradePresent = us->rva00290D2B(m_upgradeRequired);
			break;
		}
	}
	if (upgradePresent == true)
		FXList::doFXObj(modData->m_upgradedPulseFX, us, 0);
	else
		FXList::doFXObj(modData->m_pulseFX, us, 0);

	BfmeWideResult hits = ThePartitionManager->iterateObjectsInRange(us->getPosition(), modData->m_scanRadius, 0,
		Rva00260EB1Filter(us, 4, false).link(Rva0026119DFilter().link(Rva002611BFFilter(us).link(
			&Rva0004584D(*(const BfmeFixedStorage0004543D *)g_00DFEFA4StoragePrototype,
				BfmeFixedStorage0004543D(0, 7))))), 0);
	Object *obj;
	while ((obj = hits.next()) != 0) {
		if (obj == us)
			continue;
		ObjectTracker *newEntry = new ObjectTracker;
		newEntry->objectID = obj->getID();
		newEntry->next = newInsideList;
		newInsideList = newEntry;
	}

	for (ObjectTracker *curr = m_insideList; curr; curr = curr->next) {
		ObjectTracker *o;
		for (o = newInsideList; o; o = o->next)
			if (o->objectID == curr->objectID)
				break;
		if (o == 0) {
			obj = TheGameLogic->findObjectByID(curr->objectID);
			if (obj)
				effectLogic(obj, false, modData);
		}
	}

	while (m_insideList) {
		ObjectTracker *next = m_insideList->next;
		::delete m_insideList;
		m_insideList = next;
	}
	m_insideList = newInsideList;
}
