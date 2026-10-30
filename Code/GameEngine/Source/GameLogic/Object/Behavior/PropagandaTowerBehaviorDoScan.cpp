// cl: /MD /GX /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata
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

typedef unsigned int UnsignedInt;
#include "Common/Snapshot.h"
#include "ascii_string.h"

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
struct Rva00045411BitSet
{
	unsigned m_bits[7];
	Rva00045411BitSet(int unused, int bit);	// 0x00045411
};

class BfmeFixedStorage0004543D
{
public:
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
template <int N> class BitFlags;
extern BitFlags<116> KINDOFMASK_NONE;


#include "../../../../../Libraries/Include/Lib/Coord3D.h"

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

#include "../../../Common/GameLogicObjectLookupView.h"

class UpgradeTemplate
{
public:
	char m_pad00[0x4];
	int m_type; // +0x04 (0 player, 1 object)
	char m_pad08[0x30];
	int m_bitIndex; // +0x38
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

class BodyModule
{
public:
	virtual void f0();
	virtual void f1();
	virtual void f2();
	virtual void f3();
	virtual void f4();
	virtual void f5();
	virtual float f6();
};

class Object
{
public:
	Player *getControllingPlayer() const;
	bool hasUpgrade(const UpgradeTemplate *upgrade) const;
	const Coord3D *getPosition() const { return &m_pos; }
	ObjectID getID() const { return m_id; }
	bool attemptHealingFromSoleBenefactor(float amount, const Object *source, UnsignedInt extra);
	// Retail keeps the whole 32-bit flag word live in eax across the test and the
	// set: `mov eax,[esi+0x380]` / `mov ecx,eax` / `shr ecx,8` / `test cl,1` /
	// `jne skip` / `or ah,0x1` / `mov [esi+0x380],eax`. Two facts pin the source:
	// the read-modify-write is on the WORD (a byte-view accessor collapses the
	// block to 195-216B because it drops the shared reload), and the OR is a 2-byte
	// in-place or on `ah` (an `int` shift of the word materialises
	// `or eax,0x100`, 5B, twice in this body).
	bool testWeaponBonusCondition(int bit) const
	{
		return (m_flags380 & (1 << (bit + 8))) != 0;
	}
	void setWeaponBonusCondition(int bit)
	{
		m_flags380 |= (1 << (bit + 8));
	}

	char m_pad00[0x38];
	Coord3D m_pos; // +0x38
	char m_pad044[0x74 - 0x44];
	ObjectID m_id; // +0x74
	char m_pad078[0x254 - 0x78];
	BodyModule *m_body; // +0x254
	char m_pad258[0x380 - 0x258];
	UnsignedInt m_flags380; // +0x380
	char m_pad384[0x100];
};

extern GameLogic *TheGameLogic;

// vftable 0x00C49174.
class ObjectTracker
{
public:
	ObjectTracker() : objectID(INVALID_OBJECT_ID), next(0) {}
	virtual ~ObjectTracker() {}
	ObjectID objectID; // +0x04
	ObjectTracker *next; // +0x08
};

class MultiIniFieldParse;

class __declspec(novtable) PropagandaTowerBehaviorModuleData : public Snapshot
{
public:
	virtual ~PropagandaTowerBehaviorModuleData();
	int m_unused04;
	float m_radius;
	int m_delayBetweenUpdates;
	float m_healPercentEachSecond;
	const FXList *m_pulseFX;
	AsciiString m_upgradeRequired;
	float m_upgradedHealPercentEachSecond;
	const FXList *m_upgradedPulseFX;
	static void buildFieldParse(MultiIniFieldParse &parse);
};

enum NameKeyType
{
	NK_UNKNOWN = 0
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
public:
	virtual NameKeyType getModuleNameKey() const;
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
			upgradePresent = us->hasUpgrade(m_upgradeRequired);
			break;
		}
	}
	if (upgradePresent == true)
		FXList::doFXObj(modData->m_upgradedPulseFX, us, 0);
	else
		FXList::doFXObj(modData->m_pulseFX, us, 0);

	BfmeWideResult hits = ThePartitionManager->iterateObjectsInRange(us->getPosition(), modData->m_radius, 0,
		Rva00260EB1Filter(us, 4, false).link(Rva0026119DFilter().link(Rva002611BFFilter(us).link(
			&Rva0004584D(*(const BfmeFixedStorage0004543D *)&KINDOFMASK_NONE,
				(const BfmeFixedStorage0004543D &)Rva00045411BitSet(0, 7))))), 0);
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
		ObjectTracker *objectTracker;
		for (objectTracker = newInsideList; objectTracker; objectTracker = objectTracker->next)
			if (objectTracker->objectID == curr->objectID)
				break;
		if (objectTracker == 0) {
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
