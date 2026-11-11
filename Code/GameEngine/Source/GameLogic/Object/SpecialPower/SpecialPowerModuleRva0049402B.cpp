// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /GX
//
// ?rva0049402B@SpecialPowerModule@@QAEXPAUBfmeWideResult@@@Z @0x0049402B 428B.
// Original name unknown. Sole caller: triggerSpecialPower (0x004941F3) at
// 0x0049456F, passing the partition range query it built, with ecx = the
// primary SpecialPowerModule this (+4 module data, +8 object). Shape from the
// WorldBuilder debug body (0x011E8C20, 872B, unnamed; callgraph lead): for a
// type-0x85 template on a KindOf 300 object, the object's SpecialDisguiseUpdate
// (NAMEKEY "SpecialDisguiseUpdate", rowed findModule 0x0028B6D6) gets
// 0x004B05F5(false). The expiry frame is the current frame plus the named
// attribute modifier's duration (rowed rva00214713/getDuration), or 999999
// when the duration is not positive, and stays 0 when the data's +0x34
// BitFlags<11> (rowed any 0x0023C58B) is empty. Each queried object that is
// not KindOf 47, not the source unless data+0x20, passes the data+0x5E/+0x5F
// player-flag filters and (unless data+0x60) shares the source's controlling
// player, goes to primary virtual slot 13 (0x00493EA7) with that frame and the
// mask. Field offsets are target evidence; field meanings are inferred.
//
// ?ApplyPowerToObject@SpecialPowerModule@@UAEXPAVObject@@HPBV?$BitFlags@$0L@@@@Z
// @0x00493EA7 388B, that slot-13 virtual. Original name unknown; callers are
// 0x0049402B above and the slot-13 entries of the special-power vtables. Retail
// shape: the target's ExperienceTracker (+0x264) gains up to data+0x58 levels
// through the rowed 0x0039ABFF/0x0039B4EC pair, the data's attribute modifier
// name goes to the rowed Object::addAttributeModifierToPool with -1 (built as a
// temporary from its text), and for a non-zero frame and a non-empty mask the
// object's attribute modifier pool update (rowed private
// findAttributeModifierPoolUpdate) gets 0x00403415(mask, frame), or the current
// frame when data+0x42 is set and the +0x5E/+0x5F player-flag tests or (when
// neither is set) an owner relationship of 2 say so; FXLists at data+0x4C and
// (unless the target template has KindOf 109) data+0x28 play on the target.
// Codegen levers: the player flag must come from the same inline getter as
// above (mov al / xor al / test al), and the pool call must be written as two
// calls in an if/else rather than one call with a ternary argument.
#include "ascii_string.h"
#include "../../../Common/PartitionRangeQueryCallView.h"

enum NameKeyType { NAMEKEY_INVALID = 0 };
enum KindOfType { KINDOF_47 = 47, KINDOF_109 = 109, KINDOF_300 = 300 };

template <int N>
class BitFlags
{
public:
	bool any() const;
	unsigned int m_words[(N + 31) / 32];
};

#include "../../../../Include/Common/NameKeyGenerator.h"
extern NameKeyGenerator *TheNameKeyGenerator;

#include "../../../../Include/GameLogic/AttributeModifierStore.h"
extern AttributeModifierStore *TheAttributeModifierStore;

class GameLogic;
extern GameLogic *TheGameLogic;
struct Rva0049402BFrameView { char pad[0x40]; unsigned frame; };

#include "../../../../Include/Common/Overridable.h"

#include "../../../../Include/Common/SpecialPower.h"

#include "../../../../Include/Common/ThingTemplate.h"

class Rva0049402BPlayerFlags { public: char m_pad[0x1BC]; bool m_flag; };

class Player
{
public:
	bool rva0049402BFlag() const { return m_34 ? m_34->m_flag : false; }
	char m_pad[0x34];
	Rva0049402BPlayerFlags *m_34;
};

class Module;
class SpecialPowerModule;
#include "../../../../Include/GameLogic/Module/AttributeModifierPoolUpdate.h"

#include "../../../../Include/GameLogic/ExperienceTracker.h"
// Retail .CRT$XCU 0x007B16AD is this unit's Drawable.h copy (static 0x00E03A10).
#include "../../../../Include/GameClient/Drawable.h"

enum Relationship { REL_ENEMIES = 0, REL_NEUTRAL = 1, REL_ALLIES = 2 };

class FXList
{
public:
	static void doFXObj(const FXList *fx, const Object *primary, const Object *secondary);
};

class Object
{
	friend class SpecialPowerModule;
public:
	const ThingTemplate *getTemplate() const { return m_template; }
	bool isKindOf(KindOfType t) const;
	Player *getControllingPlayer() const;
	bool addAttributeModifierToPool(const AsciiString &name, int frame);
	Relationship getRelationship(const Object *that) const;
	ExperienceTracker *getExperienceTracker() const { return m_experienceTracker; }
protected:
	Module *findModule(NameKeyType key) const;
private:
	AttributeModifierPoolUpdate *findAttributeModifierPoolUpdate() const;
	void *m_vptr;
	const ThingTemplate *m_template;
	char m_pad08[0x264 - 0x08];
	ExperienceTracker *m_experienceTracker;
};

#include "../../../../Include/GameLogic/Module/SpecialDisguiseUpdate.h"

#include "../../../../Include/GameLogic/Module/SpecialPowerModuleData.h"

// +0x34 holds the BitFlags<11> AntiCategory mask the canonical header keeps as neutral storage.
static inline const BitFlags<11> &antiCategoryMask(const SpecialPowerModuleData *data)
{
	return *(const BitFlags<11> *)&data->field34;
}

class SpecialPowerModule
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12();
	virtual void ApplyPowerToObject(Object *obj, int frame, const BitFlags<11> *mask);
	void rva0049402B(BfmeWideResult *iter);
protected:
	const ModuleData *m_moduleData;
	Object *m_object;
};

void SpecialPowerModule::rva0049402B(BfmeWideResult *iter)
{
	const SpecialPowerModuleData *modData = (const SpecialPowerModuleData *)m_moduleData;
	Object *source = m_object;
	if (((const SpecialPowerTemplate *)modData->m_specialPowerTemplate->friend_getFinalOverride())->m_type == 0x85
		&& source->isKindOf(KINDOF_300))
	{
		static NameKeyType key = TheNameKeyGenerator->nameToKey("SpecialDisguiseUpdate");
		SpecialDisguiseUpdate *disguise = (SpecialDisguiseUpdate *)source->findModule(key);
		if (disguise)
			disguise->rva004B05F5(false);
	}

	unsigned frame = 0;
	if (antiCategoryMask(modData).any())
	{
		frame = ((Rva0049402BFrameView *)TheGameLogic)->frame;
		if (!((const StringBase<char> *)&modData->field18)->isEmpty())
		{
			int duration = (int)TheAttributeModifierStore->getDuration(
				TheAttributeModifierStore->rva00214713(TheNameKeyGenerator->nameToKey(modData->field18.str())));
			if (duration > 0)
				frame += duration;
			else
				frame += 999999;
		}
	}

	Object *obj;
	while ((obj = iter->next()) != 0)
	{
		if (((obj->getTemplate()->m_kindof[KINDOF_47 >> 5] & (1U << (KINDOF_47 & 31))) != 0))
			continue;
		if (!modData->field20 && obj == source)
			continue;
		if (modData->field5E && obj->getControllingPlayer()->rva0049402BFlag())
			continue;
		if (modData->field5F && !obj->getControllingPlayer()->rva0049402BFlag())
			continue;
		if (!modData->field60 && obj->getControllingPlayer() != source->getControllingPlayer())
			continue;
		ApplyPowerToObject(obj, frame, &antiCategoryMask(modData));
	}
}

// WorldBuilder SpecialPowerModule::ApplyPowerToObject, WB VA 0x011E88A0 (callgraph lead, score 3).
void SpecialPowerModule::ApplyPowerToObject(Object *obj, int frame, const BitFlags<11> *mask)
{
	const SpecialPowerModuleData *modData = (const SpecialPowerModuleData *)m_moduleData;
	ExperienceTracker *tracker = obj->getExperienceTracker();
	if (tracker)
	{
		int levels = modData->field58;
		while (levels > 0)
		{
			if (tracker->rva0039ABFF())
			{
				tracker->rva0039B4EC(1, true, false);
				--levels;
			}
			else
				levels = 0;
		}
	}

	if (!((const StringBase<char> *)&modData->field18)->isEmpty())
		obj->addAttributeModifierToPool(modData->field18.str(), -1);

	if (frame != 0 && mask->any())
	{
		AttributeModifierPoolUpdate *pool = obj->findAttributeModifierPoolUpdate();
		bool useNow = false;
		if (modData->field42)
		{
			if (modData->field5F && obj->getControllingPlayer()->rva0049402BFlag())
				useNow = true;
			if (modData->field5E && !obj->getControllingPlayer()->rva0049402BFlag())
				useNow = true;
			if (!modData->field5F && !modData->field5E
				&& m_object->getRelationship(obj) == REL_ALLIES)
				useNow = true;
		}
		if (useNow)
			pool->rva00403415((int *)mask, ((Rva0049402BFrameView *)TheGameLogic)->frame);
		else
			pool->rva00403415((int *)mask, frame);
		if (modData->field4C)
			FXList::doFXObj(modData->field4C, obj, 0);
	}

	if (modData->field28 && !((obj->getTemplate()->m_kindof[KINDOF_109 >> 5] & (1U << (KINDOF_109 & 31))) != 0))
		FXList::doFXObj(modData->field28, obj, 0);
}
