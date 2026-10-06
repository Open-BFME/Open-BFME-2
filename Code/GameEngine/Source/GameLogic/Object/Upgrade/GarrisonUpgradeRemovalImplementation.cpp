// cl: /O1 /DNDEBUG /MD
//
// GarrisonUpgrade::upgradeRemovalImplementation, retail 0x004B58FF (131 bytes):
// slot 8 of the +0x10 UpgradeMux vtable 0x00C58040 installed by the matched
// GarrisonUpgrade ctor 0x004B5839 (slot 9 is the rowed bool setter
// UpgradeMux::rva00452354, setUpgradeExecuted).
// Donor: BFME1 game/GameEngine/Source/GameLogic/Object/Upgrade/
// GarrisonUpgradeRemovalImplementation.cpp (open-bfme-1 068db38bb4), same
// body: for every behavior module whose contain is garrisonable, clear the
// upgrade-garrison model condition and notify the contain; then poke the
// related interface when the object has an AI; then setUpgradeExecuted(false).
// BFME2 deltas (target evidence): behavior array at Object+0x244, AI at +0x258,
// the condition is bit 8*32+7 of the Object+0x10C words (byte +0x12C mask
// 0x80) with notifier 0x0028AE6D, the contain calls are vslots 4 and 64, and
// the related interface comes from the rowed Object::rva0028BCF4.
// GarrisonUpgrade::upgradeImplementation, retail 0x004B5886 (121 bytes), slot
// 10 (the slot ArmorUpgrade's BFME1-donor upgradeImplementation occupies): the
// mirror image, setting the condition, passing true to contain vslot 63 and
// the object id (+0x74) to the related interface, without the executed reset.
typedef bool Bool;
class ProjectileUpdateInterface
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02(int value);
};
enum ObjectID
{
	INVALID_ID = 0
};
class ContainModuleInterface
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual Bool isGarrisonable() const = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void slot17() = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual void slot20() = 0;
	virtual void slot21() = 0;
	virtual void slot22() = 0;
	virtual void slot23() = 0;
	virtual void slot24() = 0;
	virtual void slot25() = 0;
	virtual void slot26() = 0;
	virtual void slot27() = 0;
	virtual void slot28() = 0;
	virtual void slot29() = 0;
	virtual void slot30() = 0;
	virtual void slot31() = 0;
	virtual void slot32() = 0;
	virtual void slot33() = 0;
	virtual void slot34() = 0;
	virtual void slot35() = 0;
	virtual void slot36() = 0;
	virtual void slot37() = 0;
	virtual void slot38() = 0;
	virtual void slot39() = 0;
	virtual void slot40() = 0;
	virtual void slot41() = 0;
	virtual void slot42() = 0;
	virtual void slot43() = 0;
	virtual void slot44() = 0;
	virtual void slot45() = 0;
	virtual void slot46() = 0;
	virtual void slot47() = 0;
	virtual void slot48() = 0;
	virtual void slot49() = 0;
	virtual void slot50() = 0;
	virtual void slot51() = 0;
	virtual void slot52() = 0;
	virtual void slot53() = 0;
	virtual void slot54() = 0;
	virtual void slot55() = 0;
	virtual void slot56() = 0;
	virtual void slot57() = 0;
	virtual void slot58() = 0;
	virtual void slot59() = 0;
	virtual void slot60() = 0;
	virtual void slot61() = 0;
	virtual void slot62() = 0;
	virtual void slot63(Bool value) = 0;
	virtual void slot64() = 0;
};
class BehaviorModuleInterface
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual ContainModuleInterface *getContain();
};
class BehaviorModule
{
public:
	virtual ~BehaviorModule();
	BehaviorModuleInterface *getBehaviorModuleInterface() { return &m_interface; }
private:
	unsigned char m_pad04[0x0C - 0x04];
	BehaviorModuleInterface m_interface; // +0x0C
};
class ModelConditionFlags
{
public:
	unsigned int test(unsigned int bit) const
	{
		return m_words[bit >> 5] & (1U << (bit & 0x1f));
	}
	void set(unsigned int bit)
	{
		m_words[bit >> 5] |= 1U << (bit & 0x1f);
	}
	void clear(unsigned int bit)
	{
		m_words[bit >> 5] &= ~(1U << (bit & 0x1f));
	}
private:
	unsigned int m_words[19];
};
class AIUpdateInterface;
class Object
{
public:
	void rva0028AE6D();
	void *rva0028BCF4() const;
	BehaviorModule **getBehaviorModules() const { return m_behaviors; }
	AIUpdateInterface *getAI() const { return m_ai; }
	ObjectID getID() const { return m_id; }
	__forceinline void setModelConditionState(unsigned int mc)
	{
		if (m_modelConditionFlags.test(mc) == 0)
		{
			m_modelConditionFlags.set(mc);
			rva0028AE6D();
		}
	}
	__forceinline void clearModelConditionState(unsigned int mc)
	{
		if (m_modelConditionFlags.test(mc) != 0)
		{
			m_modelConditionFlags.clear(mc);
			rva0028AE6D();
		}
	}
private:
	unsigned char m_pad000[0x74];
	ObjectID m_id; // +0x74
	unsigned char m_pad078[0x10C - 0x78];
	ModelConditionFlags m_modelConditionFlags; // +0x10C
	unsigned char m_pad158[0x244 - 0x158];
	BehaviorModule **m_behaviors; // +0x244
	unsigned char m_pad248[0x258 - 0x248];
	AIUpdateInterface *m_ai; // +0x258
};
enum
{
	MODELCONDITION_UPGRADE_GARRISON = 8 * 32 + 7
};
class ModuleData;
class ObjectModuleBase
{
public:
	virtual ~ObjectModuleBase();
protected:
	const ModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
};
class UpgradeModuleInterface
{
public:
	virtual void upgradeModuleInterfaceAnchor();
};
template <int N> class GarrisonUpgradeMuxSlots : public GarrisonUpgradeMuxSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class GarrisonUpgradeMuxSlots<0>
{
};
// UpgradeMux interface at +0x10: slot 8 upgradeRemovalImplementation, slot 9
// setUpgradeExecuted (the rowed bool setter UpgradeMux::rva00452354), slot 10
// upgradeImplementation.
class UpgradeMuxIface : public GarrisonUpgradeMuxSlots<8>
{
protected:
	virtual void upgradeRemovalImplementation() = 0;
	virtual void setUpgradeExecuted(Bool executed) = 0;
	virtual void upgradeImplementation() = 0;
};
class UpgradeModule : public ObjectModuleBase, public UpgradeModuleInterface, public UpgradeMuxIface
{
};
class GarrisonUpgrade : public UpgradeModule
{
protected:
	virtual void upgradeRemovalImplementation();
	virtual void upgradeImplementation();
};
void GarrisonUpgrade::upgradeRemovalImplementation()
{
	Object *object = m_object;
	for (BehaviorModule **module = object->getBehaviorModules(); *module != 0; ++module)
	{
		ContainModuleInterface *contain = (*module)->getBehaviorModuleInterface()->getContain();
		if (contain != 0 && contain->isGarrisonable())
		{
			object->clearModelConditionState(MODELCONDITION_UPGRADE_GARRISON);
			contain->slot64();
		}
	}
	if (object->getAI() != 0)
	{
		ProjectileUpdateInterface *related = (ProjectileUpdateInterface *)object->rva0028BCF4();
		if (related != 0)
			related->slot02(0);
	}
	setUpgradeExecuted(false);
}
void GarrisonUpgrade::upgradeImplementation()
{
	Object *object = m_object;
	for (BehaviorModule **module = object->getBehaviorModules(); *module != 0; ++module)
	{
		ContainModuleInterface *contain = (*module)->getBehaviorModuleInterface()->getContain();
		if (contain != 0 && contain->isGarrisonable())
		{
			object->setModelConditionState(MODELCONDITION_UPGRADE_GARRISON);
			contain->slot63(true);
		}
	}
	if (object->getAI() != 0)
	{
		ProjectileUpdateInterface *related = (ProjectileUpdateInterface *)object->rva0028BCF4();
		if (related != 0)
			related->slot02(object->getID());
	}
}
