// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /GX /ICode/Libraries/Include /Ireference/shims/bfme2_ascii
//
// AttributeModifierAuraUpdate::update (0x0049BCA3, slot 0 of the
// UpdateModuleInterface vftable 0x00C50D20 that the rowed ctor 0x0049B560
// installs at +0x10) and the per-object callback 0x0049B98A it hands every
// hit (and, for AffectContainedOnly, the contain module's iterateContained).
// BFME 1's AttributeModifierAuraUpdate::update (0x002803F0) is the same
// algorithm with the per-object work inline; BFME 2 moved it into the
// callback so contained objects can share it.
//
// Module data (field table 0x00C50DC8): BonusName +0x08, RefreshDelay +0x18,
// Range +0x1C, AllowPowerWhenAttacking +0x20, TargetEnemy +0x21,
// ObjectFilter +0x24, RequiredConditions +0x13C, AntiCategory +0x140, AntiFX
// +0x144, AffectGood +0x148, AffectEvil +0x149, RunWhileDead +0x14A,
// AllowSelf +0x14B, AffectContainedOnly +0x14C, MaxActiveRank +0x150.
// The filter chain is BFME 2's partition filter set (the views of
// AIClosestObjectQueries.cpp and RousingSpeechUpdateUpdate.cpp). The hit
// list's append at 0x00626630 takes the object and a float distance (the
// ledger row spells it with two ints), so it is reached through a placeholder
// pin.
#include "ascii_string.h"
#include "Lib/Coord3D.h"

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;

#define NULL 0

class Object;
class Player;
class FXList;
class ModuleData;

enum UpdateSleepTime
{
	UPDATE_SLEEP_FOREVER = 0x3FFFFFFF
};

enum KindOfType
{
	KINDOF_0x25 = 0x25,
	KINDOF_0xD6 = 0xD6
};

enum ObjectID
{
	INVALID_ID = -1
};

enum Relationship
{
	ENEMIES = 0
};

struct BfmePointFC;

template <int N> class BitFlags
{
public:
	bool any() const;
	unsigned m_words[7];
};

// 0x0006EE7A: a KindOf mask with two bits set.
struct Rva0006EE7A : public BitFlags<69>
{
	Rva0006EE7A(int unused, int b1, int b2);
};

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

// vftable 0x00C07190, allow 0x002614DF.
class Rva002614DFFilter : public Rva000421C8
{
public:
	Rva002614DFFilter(const Object *obj) : m_obj(obj) {}
	virtual bool allow(Object *obj);
	const Object *m_obj;
};

// vftable 0x00BF91BC, allow 0x002611BF.
class Rva002611BFFilter : public Rva000421C8
{
public:
	Rva002611BFFilter(const Object *obj) : m_obj(obj) {}
	virtual bool allow(Object *obj);
	const Object *m_obj;
};

// vftable 0x00BFBC90, allow 0x00260EB1, getPlayerMask 0x00260E6A: the object,
// relationship flags and whether a hit allows.
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

// vftable 0x00BCECF0, allow 0x002614EC: +0x08 what to compare, +0x0C a
// player, +0x10 whether a hit allows.
class Rva002614ECFilter : public Rva000421C8
{
public:
	Rva002614ECFilter(const void *what, Player *player, bool match)
		: m_what(what), m_player(player), m_match(match) {}
	virtual bool allow(Object *obj);
	const void *m_what;
	Player *m_player;
	bool m_match;
};

#pragma comment(linker, "/alternatename:?getPlayerMask@Rva000421C8@@UAEHXZ=?Get_File_Handle@FileClass@@UAEPAXXZ")

struct BfmeWideResult
{
	Object *next() throw();	// 0x00045623
	~BfmeWideResult();	// 0x0004AA28
	void rva00626630(Object *obj, Real distance);	// 0x00626630
	void *m_value;
};

class PartitionManager
{
public:
	BfmeWideResult iterateObjectsInRange(const Coord3D *pos, Real radius, int distCalc,
		Rva000421C8 *filters, int order);	// 0x00625610
};
extern PartitionManager *ThePartitionManager;

class GameLogic
{
public:
	UnsignedInt getFrame() const { return m_frame; }
	Object *findObjectByID(ObjectID id);

private:
	char m_unknown00[0x40];
	UnsignedInt m_frame; // +0x40
};
extern GameLogic *TheGameLogic;

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};
extern NameKeyGenerator *TheNameKeyGenerator;

class AttributeModifierStore
{
public:
	int rva00214713(int key);
	void *getDuration(int index);
};
extern AttributeModifierStore *TheAttributeModifierStore;

class BfmeTaintManager
{
public:
	int rva006C0850(const BfmePointFC *pos, int *owner);
};
extern BfmeTaintManager *TheTaintManager;

class FXList
{
public:
	static void doFXObj(const FXList *fx, const Object *primary, const Object *secondary);
};

class AttributeModifierPoolUpdate
{
public:
	void rva00403415(int *categories, int endFrame);
};

typedef void (*ContainIterateFunc)(Object *obj, void *userData);
template <int N> class Rva0049B98ASlots : public Rva0049B98ASlots<N - 1>
{
public:
	virtual void gap(char (*)[N + 1]) = 0;
};
template <> class Rva0049B98ASlots<0>
{
public:
	virtual void gap(char (*)[1]) = 0;
};
// Object +0x250: slot 68 walks the contained Objects.
class ContainModuleInterface : public Rva0049B98ASlots<67>
{
public:
	virtual void iterateContained(ContainIterateFunc func, void *userData, bool reverse) = 0;
};

class ThingTemplate
{
public:
	__forceinline UnsignedInt isKindOf(int k) const { return m_kindOf[k >> 5] & (1U << (k & 31)); }

private:
	char m_unknown000[0x10C];
	UnsignedInt m_kindOf[4]; // +0x10C
};

class Rva0028B511Side
{
public:
	char m_unknown000[0x1BC];
	Bool m_isGood; // +0x1BC
};

class Player
{
public:
	Bool isGood() const { return m_side ? m_side->m_isGood : false; }

private:
	char m_unknown00[0x34];
	Rva0028B511Side *m_side; // +0x34
};

class ExperienceTracker
{
public:
	char m_unknown00[0x24];
	Int m_rank; // +0x24
};

class Thing
{
public:
	const ThingTemplate *getTemplate() const { return m_template; }
	bool isAnyKindOf(const BitFlags<69> &mask) const;

private:
	void *m_vtable;
	const ThingTemplate *m_template; // +0x04
};

class Object : public Thing
{
public:
	Player *getControllingPlayer() const;	// 0x0028AFA9
	Bool isKindOf(KindOfType t) const;	// 0x0006F039
	int rva0028B511() const;
	Relationship getRelationship(const Object *that) const;
	bool addAttributeModifierToPool(const AsciiString &name, int duration);
	const Coord3D *getPosition() const { return &m_pos; }
	ObjectID getID() const { return m_id; }
	Real getBoundingRadius() const { return m_boundingRadius; }
	Bool testStatus(int bit) const { return (m_status >> bit) & 1; }
	Bool isEffectivelyDead() const { return (m_438 & 1) != 0; }
	ContainModuleInterface *getContain() const { return m_contain; }
	ExperienceTracker *getExperienceTracker() const { return m_experience; }

private:
	friend void Rva0049B98A(Object *obj, void *userData);
	AttributeModifierPoolUpdate *findAttributeModifierPoolUpdate() const;

	char m_pad008[0x38 - 0x8];
	Coord3D m_pos;		// +0x38
	char m_pad044[0x74 - 0x44];
	ObjectID m_id;		// +0x74
	char m_pad078[0xB8 - 0x78];
	Real m_boundingRadius;	// +0xB8
	char m_pad0BC[0x11C - 0xBC];
	UnsignedInt m_status;	// +0x11C
	char m_pad120[0x250 - 0x120];
	ContainModuleInterface *m_contain;	// +0x250
	char m_pad254[0x264 - 0x254];
	ExperienceTracker *m_experience;	// +0x264
	char m_pad268[0x438 - 0x268];
	unsigned char m_438;	// +0x438
};

class BehaviorModule
{
public:
	virtual ~BehaviorModule();
	Object *getObject() const { return m_object; }
protected:
	const ModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
};
class BehaviorModuleInterface
{
public:
	virtual void behaviorModuleInterfaceAnchor();
};
class UpdateModuleInterface
{
public:
	virtual UpdateSleepTime update() = 0;
};
class UpdateModule : public BehaviorModule, public BehaviorModuleInterface, public UpdateModuleInterface
{
protected:
	char m_pad14[0x20 - 0x14];
};
class UpgradeMux
{
public:
	virtual bool rvaUpgradeMuxSlot0() const = 0;
private:
	unsigned int m_executed;
};

class AttributeModifierAuraUpdateModuleData
{
public:
	char m_unknown00[8];
	AsciiString m_bonusName;		// +0x08
	char m_unknown0C[0x18 - 0xC];
	Int m_refreshDelay;			// +0x18
	Real m_range;				// +0x1C
	Bool m_allowPowerWhenAttacking;		// +0x20
	Bool m_targetEnemy;			// +0x21
	char m_unknown22[2];
	char m_objectFilter[0x13C - 0x24];	// +0x24
	UnsignedInt m_requiredConditions;	// +0x13C
	Int m_antiCategory;			// +0x140
	const FXList *m_antiFX;			// +0x144
	Bool m_affectGood;			// +0x148
	Bool m_affectEvil;			// +0x149
	Bool m_runWhileDead;			// +0x14A
	Bool m_allowSelf;			// +0x14B
	Bool m_affectContainedOnly;		// +0x14C
	char m_unknown14D[3];
	Int m_maxActiveRank;			// +0x150
};

// What update hands the callback for each object.
struct AttributeModifierAuraInfo
{
	UnsignedInt m_endFrame;		// +0x00 when the anti-category modifiers expire (0: none)
	Object *m_source;		// +0x04
	const AttributeModifierAuraUpdateModuleData *m_data;	// +0x08
	Bool m_special;			// +0x0C
	Bool m_contained;		// +0x0D
};

class AttributeModifierAuraUpdate : public UpdateModule, public UpgradeMux
{
public:
	virtual UpdateSleepTime update();
private:
	const AttributeModifierAuraUpdateModuleData *getAttributeModifierAuraUpdateModuleData() const
	{
		return (const AttributeModifierAuraUpdateModuleData *)m_moduleData;
	}
};

void Rva0049B98A(Object *obj, void *userData);

// ?Rva0049B98A@@YAXPAVObject@@PAX@Z @0x0049B98A 537B
void Rva0049B98A(Object *obj, void *userData)
{
	if (obj->isAnyKindOf(Rva0006EE7A(0, 0x2F, 0x97)))
		return;
	AttributeModifierAuraInfo *info = (AttributeModifierAuraInfo *)userData;
	if (!info->m_data->m_allowSelf && obj == info->m_source)
		return;
	Player *player = obj->getControllingPlayer();
	if (info->m_data->m_affectGood && player->isGood())
		return;
	if (info->m_data->m_affectEvil && !player->isGood())
		return;
	ExperienceTracker *experience = obj->getExperienceTracker();
	if (experience)
	{
		Int maxRank = info->m_data->m_maxActiveRank;
		Int rank = experience->m_rank;
		if (maxRank && rank > maxRank)
			return;
	}
	if (obj->testStatus(1))
		return;
	if (info->m_special)
	{
		if (obj->rva0028B511() < 0x11 || obj->rva0028B511() > 0x40)
			return;
	}
	UnsignedInt conditions = info->m_data->m_requiredConditions;
	if (conditions & 2)
	{
		int owner = -1;
		if (TheTaintManager->rva006C0850((const BfmePointFC *)obj->getPosition(), &owner) != 2)
			return;
		if (owner != -1)
		{
			Object *ownerObj = TheGameLogic->findObjectByID((ObjectID)owner);
			if (!ownerObj || ownerObj->getRelationship(obj) == ENEMIES)
				return;
		}
	}
	else if (conditions & 4)
	{
		int owner = -1;
		if (TheTaintManager->rva006C0850((const BfmePointFC *)obj->getPosition(), &owner) != 1)
			return;
		if (owner != -1)
		{
			Object *ownerObj = TheGameLogic->findObjectByID((ObjectID)owner);
			if (!ownerObj || ownerObj->getRelationship(obj) == ENEMIES)
				return;
		}
	}
	if (info->m_contained && obj->getTemplate()->isKindOf(77))
		obj->getContain()->iterateContained(Rva0049B98A, info, true);
	if (info->m_endFrame)
	{
		AttributeModifierPoolUpdate *pool = obj->findAttributeModifierPoolUpdate();
		if (pool)
			pool->rva00403415((int *)&info->m_data->m_antiCategory, info->m_endFrame);
		if (info->m_data->m_antiFX)
			FXList::doFXObj(info->m_data->m_antiFX, obj, NULL);
	}
	const AsciiString &bonusName = info->m_data->m_bonusName;
	if (!((const StringBase<char> *)&bonusName)->isEmpty())
	{
		AsciiString name(bonusName.str());
		obj->addAttributeModifierToPool(name, -1);
	}
}

// ?update@AttributeModifierAuraUpdate@@UAE?AW4UpdateSleepTime@@XZ @0x0049BCA3 685B
UpdateSleepTime AttributeModifierAuraUpdate::update()
{
	Object *object = getObject();
	const AttributeModifierAuraUpdateModuleData *data = getAttributeModifierAuraUpdateModuleData();
	if (object->isEffectivelyDead() && !data->m_runWhileDead)
		return UPDATE_SLEEP_FOREVER;
	if (object->testStatus(1))
		return (UpdateSleepTime)(object->getID() % 5 + data->m_refreshDelay);
	if (!rvaUpgradeMuxSlot0())
		return UPDATE_SLEEP_FOREVER;
	if (data->m_requiredConditions & 1)
	{
		if (!object->isKindOf(KINDOF_0xD6))
			return (UpdateSleepTime)(object->getID() % 5 + data->m_refreshDelay);
	}
	if (!data->m_allowPowerWhenAttacking && getObject()->isKindOf(KINDOF_0x25))
		return (UpdateSleepTime)(object->getID() % 5 + data->m_refreshDelay);

	AttributeModifierAuraInfo info;
	info.m_source = object;
	info.m_endFrame = 0;
	info.m_data = data;
	info.m_contained = false;
	info.m_special = getObject()->getTemplate()->isKindOf(28);
	if (((const BitFlags<11> *)&data->m_antiCategory)->any() && !((const StringBase<char> *)&data->m_bonusName)->isEmpty())
	{
		info.m_endFrame = TheGameLogic->getFrame();
		UnsignedInt duration = (UnsignedInt)TheAttributeModifierStore->getDuration(
			TheAttributeModifierStore->rva00214713(TheNameKeyGenerator->nameToKey(data->m_bonusName.str())));
		if (duration > 0)
			info.m_endFrame += duration;
		else
			info.m_endFrame += 999999;
	}

	if (data->m_affectContainedOnly)
	{
		ContainModuleInterface *contain = object->getContain();
		if (contain)
		{
			info.m_contained = true;
			contain->iterateContained(Rva0049B98A, &info, true);
		}
	}
	else
	{
		Rva002614DFFilter filter1(object);
		Rva002611BFFilter filter2(object);
		Rva00260EB1Filter relationship1(object, 1, false);
		Rva00260EB1Filter relationship4(object, 4, false);
		Rva002614ECFilter objectFilter(data->m_objectFilter, object->getControllingPlayer(), true);
		Rva0026119DFilter root;
		root.link(&filter1);
		root.link(&filter2);
		if (!data->m_affectGood && !data->m_affectEvil)
		{
			if (data->m_targetEnemy)
				root.link(&relationship1);
			else if (!info.m_special)
				root.link(&relationship4);
		}
		root.link(&objectFilter);
		Real radius = info.m_special ? getObject()->getBoundingRadius() : data->m_range;
		BfmeWideResult hits = ThePartitionManager->iterateObjectsInRange(object->getPosition(), radius, 0, &root, 1);
		if (data->m_allowSelf)
			hits.rva00626630(object, 0.0f);
		Object *other;
		while ((other = hits.next()) != NULL)
			Rva0049B98A(other, &info);
	}
	return (UpdateSleepTime)(object->getID() % 5 + data->m_refreshDelay);
}
