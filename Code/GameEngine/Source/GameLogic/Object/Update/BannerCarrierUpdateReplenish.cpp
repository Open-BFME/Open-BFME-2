// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /ICode/Libraries/Include /Ireference/shims/iniexception /Ireference/shims/bfmealloc /Ireference/shims/moduledata
// stlport
//
// BannerCarrierUpdate's replenish scan (0x004973CF; REL32 from 0x00497524).
// Field names are the module data's INI table (UnitSpawnFX +0x34,
// ReplenishNearbyHorde +0x38, ReplenishAllNearbyHordes +0x39,
// ScanHordeDistance +0x3C; BannerCarrierUpdateModuleDataCtor.cpp). Every
// kind-109 object the controlling player's relationship flag 2 accepts
// within ScanHordeDistance (BFME2's partition filter chain, the view
// AIStructureCreepTactic.cpp documents), unless status 2, whose horde
// contain (Object::rva0028C197) has room (slot 98 below slot 95) spawns one
// through slot 99 (partition refresh and UnitSpawnFX), stopping after the
// first unless ReplenishAllNearbyHordes; a full one above 1 gets slot 93(1).
#include "ascii_string.h"
#include "Lib/Coord3D.h"
#include "Common/Snapshot.h"
#include <vector>

class Object;

class Player;

class Module;

class UpgradeTemplate;

class Gen_0028EF10;

class BannerContain;

class AIUpdateInterface;

struct ObjectInner04;

struct BfmeMorphCondition;

struct BfmeExpLevelDraw;

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

// vftable 0x00C004D8, allow 0x00261409: the player's relationship to the
// object's team against the +0x10 flags, +0x0C whether a hit allows.
class Rva00261409Filter : public Rva000421C8
{
public:
	Rva00261409Filter(Player *player, bool match, int flags)
		: m_player(player), m_match(match), m_flags(flags) {}
	virtual bool allow(Object *obj);
	virtual int getPlayerMask();
	Player *m_player;
	bool m_match;
	int m_flags;
};

// A KindOfMaskType as the mask filters copy it (0x0004543D).
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

struct Rva00045411BitSet
{
	Rva00045411BitSet(int unused, int bit) throw();	// 0x00045411
	unsigned int m_bits[7];
};
template <int N> class BitFlags;
extern BitFlags<116> KINDOFMASK_NONE;



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

enum UpdateSleepTime { UPDATE_SLEEP_NONE=1 };

enum KindOfType { KINDOF_DUMMY=0 };

enum ObjectStatusTypes { STATUS_DUMMY=0 };

enum NameKeyType
{
	NK_UNKNOWN = 0
};

class FXList
{
public:
	static void doFXObj(const FXList *,const Object *,const Object *); // 0x000B2235
};

template <int N> class Rva004973CFSlots : public Rva004973CFSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class Rva004973CFSlots<0>
{
};

// The horde contain interface Object::rva0028C197 returns.
class Rva004973CFContain : public Rva004973CFSlots<93>
{
public:
	virtual void rva004973CFSlot93(int arg) = 0;
	virtual unsigned rva004973CFSlot94() = 0;
	virtual unsigned rva004973CFSlot95() = 0;
	virtual void slot96() = 0;
	virtual void slot97() = 0;
	virtual unsigned rva004973CFSlot98() = 0;
	virtual Object *rva004973CFSlot99(void *what) = 0;
};

class Object { public:
 bool isKindOf(KindOfType) const;
 bool testStatus(ObjectStatusTypes) const; // 0x0004E536
 bool hasUpgrade(const UpgradeTemplate *) const;
 Object *rva002931F5(bool);
 int rva0028AF76() const;
 Player *getControllingPlayer() const; // 0x0028AFA9
 void *rva0028C197() const; // 0x0028C197
 void rva0028CFB2(const int *clearFlags, const int *setFlags);
 void updateShroudNow(); // 0x0028C11A
 const Coord3D *getPosition() const { return &m_position; }
 AIUpdateInterface *getAI() const { return m_ai; }
 char pad00[4]; ObjectInner04 *m_04; // +0x04
 char matrix[0x30]; // +0x08
 Coord3D m_position; // +0x38
 char pad44[0x24C-0x44]; Gen_0028EF10 *m_stats; BannerContain *m_contain; // +0x24C, +0x250
 char pad254[4]; AIUpdateInterface *m_ai; // +0x258
 char pad25C[0x274-0x25C]; Object *m_containedBy; // +0x274
protected:
 Module *findModule(NameKeyType key) const;
};

// Field identity is retail's own INI table at 0x00C4F9E8; the +0x18/+0x24 element
// classes keep the names the ledger's vector destructor rows carry.
class BannerCarrierUpdateModuleData : public Snapshot
{
public:
	BannerCarrierUpdateModuleData();
	virtual ~BannerCarrierUpdateModuleData();
	AsciiString rva00496DA3(const AsciiString &name) const;
	const FXList *getFX() const { return m_bannerMorphFX; }
	int m_unused04; // +0x04
	unsigned m_idleSpawnRate; // +0x08
	unsigned m_meleeFreeUnitSpawnTime; // +0x0C
	int m_diedRespawnTime; // +0x10
	int m_meleeFreeBannerReSpawnTime; // +0x14
	_STL::vector<BfmeMorphCondition *> m_morphConditions; // +0x18
	_STL::vector<BfmeExpLevelDraw *> m_expLevelDraws; // +0x24
	const FXList *m_bannerMorphFX; // +0x30
	const FXList *m_unitSpawnFX; // +0x34
	bool m_replenishNearbyHorde; // +0x38
	bool m_replenishAllNearbyHordes; // +0x39
	unsigned char m_pad3A[2]; // +0x3A
	float m_scanHordeDistance; // +0x3C
	AsciiString m_upgradeRequired; // +0x40
};

class BannerBase { public: virtual void slot0();
 Object *getObject() const { return object; }
 const BannerCarrierUpdateModuleData *data; Object *object;
};

class BannerOther { public: virtual void slot0(); };

class UpdateModuleInterface { public: virtual UpdateSleepTime update()=0; };

class BannerCarrierUpdate : public BannerBase, public BannerOther, public UpdateModuleInterface {
public:
 virtual UpdateSleepTime update();
 void rva004973CF(); bool rva00496BD2(Object *); void rva00496E05(void *entry, bool playFX);
public:
	virtual NameKeyType getModuleNameKey() const;
};

void BannerCarrierUpdate::rva004973CF()
{
	Player *player = object->getControllingPlayer();
	if (!player)
		return;
	const BannerCarrierUpdateModuleData *data = this->data;
	BfmeWideResult hits = ThePartitionManager->iterateObjectsInRange(getObject()->getPosition(), data->m_scanHordeDistance, 0,
		Rva0004584D(*(BfmeFixedStorage0004543D *)&Rva00045411BitSet(0, 109),
			*(BfmeFixedStorage0004543D *)&KINDOFMASK_NONE).link(&Rva00261409Filter(player, true, 2)), 1);
	Object *other;
	while ((other = hits.next()) != 0) {
		if (!other->testStatus((ObjectStatusTypes)2)) {
			Rva004973CFContain *contain = (Rva004973CFContain *)other->rva0028C197();
			if (contain) {
				unsigned maxCount = contain->rva004973CFSlot95();
				if (contain->rva004973CFSlot98() < maxCount) {
					Object *spawned = contain->rva004973CFSlot99(other->matrix);
					if (spawned) {
						spawned->updateShroudNow();
						if (data->m_unitSpawnFX)
							FXList::doFXObj(data->m_unitSpawnFX, spawned, 0);
					}
					if (!data->m_replenishAllNearbyHordes)
						break;
				} else if (contain->rva004973CFSlot94() > 1) {
					contain->rva004973CFSlot93(1);
				}
			}
		}
	}
}
