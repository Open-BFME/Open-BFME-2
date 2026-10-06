// cl: /DNDEBUG /MD
// Retail 0x004A1119 (87 bytes): ?update@SupplyCenterDockUpdate@@UAE?AW4UpdateSleepTime@@XZ.
// Identity: slot 0 of the vtable 0x00C51B10 that the matched
// SupplyCenterDockUpdate ctor 0x004A0DC7 installs at +0x10 (the
// UpdateModuleInterface base), and Zero Hour SupplyCenterDockUpdate.cpp, whose
// update() extends DockUpdate::update() and returns its result. The base call
// target 0x00589F09 is slot 0 of the same interface in the docks that do not
// override update (RepairDockUpdate 0x00C51D68, MonsterDockUpdate), pinned
// as DockUpdate::update (?update@DockUpdate@@UAE?AW4UpdateSleepTime@@XZ).
// BFME2 extension after the base call: unless bit 0x14C (= 10*32+12) is
// already set, when the controlling player has the science at module data
// +0x14, set condition bit 10*32+12. The test is the matched 0x0006F039, which
// the ledger names Object::isKindOf; called on the Object it tests the same
// +0x10C word array (the name is presumably an ICF fold with a template
// kind-of test, whose mask also sits at +0x10C).
//
// Model-condition bits: the word array of the Object starts at +0x10C (the
// variable-index set/test in 0x00293A05 addresses [obj + word*4 + 0x10C]); a
// bit index is word*32 + bit. The accessors return the masked word rather
// than a bool and the update is a free __forceinline helper that calls the
// pinned condition-changed notifier 0x0028AE6D (?rva0028AE6D@Object@@QAEXXZ)
// only when the bit changed; this is the BFME1 HordeGarrisonContainCtor.cpp
// recipe (mask in a register and test/or on the member for a set, byte-narrowed
// test/and for a clear). With the array based at +0x110 instead, a word-0 access
// keeps the array address in a register (lea), which retail never does.

class Drawable;
class Rva0010CConditionBits
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
enum KindOfType { KINDOF_FIRST = 0 };
enum ScienceType { SCIENCE_INVALID = -1 };
class Player
{
public:
	bool hasScience(ScienceType t) const;
};
class Object
{
public:
	void rva0028AE6D();
	Drawable *getDrawable() const;
	bool isKindOf(KindOfType t) const;
	Player *getControllingPlayer() const;
	unsigned char m_pad000[0x10C];
	Rva0010CConditionBits m_conditionBits; // +0x10C
};
static __forceinline void setModelConditionBit(Object *object, int bit)
{
	if (object->m_conditionBits.test(bit) == 0)
	{
		object->m_conditionBits.set(bit);
		object->rva0028AE6D();
	}
}
class Thing;
class ModuleData;
class BehaviorModule
{
public:
	virtual ~BehaviorModule();
protected:
	const ModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
};
class BehaviorModuleInterface
{
public:
	virtual void behaviorModuleInterfaceAnchor();
};
enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3fffffff
};
class UpdateModuleInterface
{
public:
	virtual UpdateSleepTime update() = 0;
};
class UpdateModule : public BehaviorModule, public BehaviorModuleInterface, public UpdateModuleInterface
{
protected:
	unsigned int m_14;
	int m_18;
	int m_1C;
};
class DockUpdateInterface
{
public:
	virtual void dockAnchor();
};
class DockUpdate : public UpdateModule, public DockUpdateInterface
{
public:
	virtual UpdateSleepTime update();
};
class SupplyCenterDockUpdateModuleData
{
public:
	unsigned char m_pad[0x14];
	ScienceType m_14;
};
class SupplyCenterDockUpdate : public DockUpdate
{
public:
	virtual UpdateSleepTime update();
};
UpdateSleepTime SupplyCenterDockUpdate::update()
{
	UpdateSleepTime result = DockUpdate::update();
	Object *object = m_object;
	if (!object->isKindOf((KindOfType)0x14c))
	{
		const SupplyCenterDockUpdateModuleData *data = (const SupplyCenterDockUpdateModuleData *)m_moduleData;
		if (object->getControllingPlayer()->hasScience(data->m_14))
			setModelConditionBit(object, 10 * 32 + 12);
	}
	return result;
}
