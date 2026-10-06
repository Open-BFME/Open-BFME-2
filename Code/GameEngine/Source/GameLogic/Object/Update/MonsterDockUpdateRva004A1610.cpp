// cl: /DNDEBUG /MD
// Retail 0x004A1610 (73 bytes): ?rva004A1610@MonsterDockUpdate@@UAEXPAVObject@@@Z.
// Identity: slot 10 of the vtable 0x00C51D18 that the matched MonsterDockUpdate
// ctor 0x004A139A installs at +0x20, the DockUpdateInterface base (slot 3 of
// that table is the matched DockUpdate::isClearToEnter, as in the Zero Hour
// interface order, where slot 10 is onDockReached(Object *docker); the BFME2
// name is not asserted, hence the address name). Overrides of a non-primary
// base take the +0x20 subobject this ([edi-0x18] is the Object at +0x08).
// Body: set condition bit 9*32+17 on the docker; when both the docker and our
// Object have a Drawable, call the matched Drawable::rva00272A02(false) on the
// docker drawable.
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
class Object
{
public:
	void rva0028AE6D();
	Drawable *getDrawable() const;
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
	virtual void rva004A1610(Object *docker) = 0;
};
class DockUpdate : public UpdateModule, public DockUpdateInterface
{
};
class Drawable
{
public:
	void rva00272A02(bool on);
};
class MonsterDockUpdate : public DockUpdate
{
public:
	virtual void rva004A1610(Object *docker);
};
void MonsterDockUpdate::rva004A1610(Object *docker)
{
	setModelConditionBit(docker, 9 * 32 + 17);
	Drawable *mine = m_object->getDrawable();
	Drawable *theirs = docker->getDrawable();
	if (theirs && mine)
		theirs->rva00272A02(false);
}
