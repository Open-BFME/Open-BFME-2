// cl: /DNDEBUG /MD /GX
//
// ModelConditionSpecialAbilityUpdate's slot-22 override (vftable whose
// slot-2 name getter returns "ModelConditionSpecialAbilityUpdate"; rowed
// pool key 0x00490D96). It runs the base SpecialAbilityUpdate slot 22
// (pinned rva004508B7) and carries that slot's address name, which cl 7.1
// needs to place the override; the method identity is not established.
//
// ?rva004508B7@ModelConditionSpecialAbilityUpdate@@UAEXXZ, retail 0x00490ECF, 102 bytes.
// While the ability state at +0x24 is 0, sets one model-condition bit on the
// owner chosen by module data +0xC8 (0: bit 10*32+10; 1 to 3: bits 6*32+19
// to 6*32+21) and, when it was clear, runs the pinned notifier
// Object::rva0028AE6D (the HordeSiegeEngineContainRiders bit helper).
//
// ?onExit@ModelConditionSpecialAbilityUpdate@@MAEX_N0@Z, retail 0x00490F35, 121 bytes.
// Slot 13, where the SpecialAbilityUpdate vftable holds the rowed onExit
// 0x004502CE: runs it, then clears the bit slot 22 set (same choice by module
// data +0xC8) and notifies when it was set.
//
// ?triggerAbilityEffect@ModelConditionSpecialAbilityUpdate@@UAEXXZ, retail 0x00490FAE, 313 bytes.
// Slot 17 (vftable 0x0084D7C8): after SpecialAbilityUpdate's slot 17, when
// the module data's +0xCC or +0xCD flag is set, hand every object within its
// +0xD0 radius that the player's relationship flag 4 accepts, other than the
// owner, and that passes the 0x002614EC filter over the data's +0xD4 and the
// owner's player, to 0x0028EC68 (6 for +0xCC, 5 for +0xCD; the owner; 1).
// The filters are BFME2's partition filter chain (the view
// AIStructureCreepTactic.cpp documents).

class ModuleData;
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

// vftable 0x00BF91BC, allow 0x002611BF.
class Rva002611BFFilter : public Rva000421C8
{
public:
	Rva002611BFFilter(const Object *obj) : m_obj(obj) {}
	virtual bool allow(Object *obj);
	const Object *m_obj;
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

#pragma comment(linker, "/alternatename:?getPlayerMask@Rva000421C8@@UAEHXZ=?Get_File_Handle@FileClass@@UAEPAXXZ")

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

class Rva0010CBits
{
public:
	unsigned int test(int bit) const
	{
		return m_words[bit >> 5] & (1U << (bit & 0x1f));
	}
	void set(int bit)
	{
		m_words[bit >> 5] |= 1U << (bit & 0x1f);
	}
	void clear(int bit)
	{
		m_words[bit >> 5] &= ~(1U << (bit & 0x1f));
	}
private:
	unsigned int m_words[20];
};

class Object
{
public:
	void rva0028AE6D();
	Player *getControllingPlayer() const;	// 0x0028AFA9
	void rva0028EC68(int a, void *b, int c);	// 0x0028EC68
	void applyFrom(int a, Object *source) { rva0028EC68(a, source, 1); }
	const Coord3D *getPosition() const { return &m_pos; }
	unsigned char m_pad000[0x38];
	Coord3D m_pos;	// +0x38
	unsigned char m_pad044[0x10C - 0x44];
	Rva0010CBits m_conditionBits; // +0x10C
};

static __forceinline void setModelConditionBit(Object *object, int bit)
{
	if (object->m_conditionBits.test(bit) == 0)
	{
		object->m_conditionBits.set(bit);
		object->rva0028AE6D();
	}
}

static __forceinline void clearModelConditionBit(Object *object, int bit)
{
	if (object->m_conditionBits.test(bit) != 0)
	{
		object->m_conditionBits.clear(bit);
		object->rva0028AE6D();
	}
}

struct ModelConditionSpecialAbilityUpdateModuleData
{
	unsigned char m_pad00[0xC8];
	int m_C8;
	bool m_CC;
	bool m_CD;
	float m_D0;	// +0xD0 the radius
	char m_D4[4];	// +0xD4 what the 0x002614EC filter compares
};

class ModelConditionSpecialAbilityUpdate;

class SpecialAbilityUpdate
{
	friend class ModelConditionSpecialAbilityUpdate;
public:
	virtual void triggerAbilityEffect();
	virtual void rva004508B7();
private:
	void onExit(bool a, bool b);
protected:
	Object *getObject() const { return m_object; }
	const ModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
	unsigned char m_pad0C[0x24 - 0x0C];
	int m_24; // +0x24
};

class ModelConditionSpecialAbilityUpdate : public SpecialAbilityUpdate
{
public:
	virtual void triggerAbilityEffect();
	virtual void rva004508B7();
protected:
	virtual void onExit(bool a, bool b);
};

// ?rva004508B7@ModelConditionSpecialAbilityUpdate@@UAEXXZ @0x00490ECF
void ModelConditionSpecialAbilityUpdate::rva004508B7()
{
	SpecialAbilityUpdate::rva004508B7();
	if (m_24 != 0)
		return;

	const ModelConditionSpecialAbilityUpdateModuleData *data =
		(const ModelConditionSpecialAbilityUpdateModuleData *)m_moduleData;
	Object *object = m_object;
	switch (data->m_C8)
	{
	case 0:
		setModelConditionBit(object, 10 * 32 + 10);
		break;
	case 1:
		setModelConditionBit(object, 6 * 32 + 19);
		break;
	case 2:
		setModelConditionBit(object, 6 * 32 + 20);
		break;
	case 3:
		setModelConditionBit(object, 6 * 32 + 21);
		break;
	}
}

// ?onExit@ModelConditionSpecialAbilityUpdate@@MAEX_N0@Z @0x00490F35
void ModelConditionSpecialAbilityUpdate::onExit(bool a, bool b)
{
	SpecialAbilityUpdate::onExit(a, b);

	const ModelConditionSpecialAbilityUpdateModuleData *data =
		(const ModelConditionSpecialAbilityUpdateModuleData *)m_moduleData;
	Object *object = m_object;
	switch (data->m_C8)
	{
	case 0:
		clearModelConditionBit(object, 10 * 32 + 10);
		break;
	case 1:
		clearModelConditionBit(object, 6 * 32 + 19);
		break;
	case 2:
		clearModelConditionBit(object, 6 * 32 + 20);
		break;
	case 3:
		clearModelConditionBit(object, 6 * 32 + 21);
		break;
	}
}

void ModelConditionSpecialAbilityUpdate::triggerAbilityEffect()
{
	SpecialAbilityUpdate::triggerAbilityEffect();
	const ModelConditionSpecialAbilityUpdateModuleData *data =
		(const ModelConditionSpecialAbilityUpdateModuleData *)m_moduleData;
	if (data && (data->m_CC || data->m_CD)) {
	BfmeWideResult hits = ThePartitionManager->iterateObjectsInRange(getObject()->getPosition(), data->m_D0, 0,
		Rva00261409Filter(m_object->getControllingPlayer(), true, 4).link(Rva002611BFFilter(m_object)
			.link(&Rva002614ECFilter(data->m_D4, m_object->getControllingPlayer(), true))), 0);
	Object *other;
	while ((other = hits.next()) != 0) {
		if (data->m_CC)
			other->applyFrom(6, m_object);
		if (data->m_CD)
			other->applyFrom(5, m_object);
	}
}
}
