// cl: /DNDEBUG /MD
// Retail 0x004C6D0F (38 bytes): ?rva004C6D0F@FellBeastSwoopPower@@UAEX_N0@Z.
// Identity: slot 13 of the primary vtable 0x00C5DF80 installed by the matched
// FellBeastSwoopPower ctor 0x004C6C1E (slots 3/4 are the matched
// FellBeastSwoopPower xfer and pool key). The class derives from
// SpecialAbilityUpdate (slots 14/15 inherit 0x00450AE9/0x00450D9A); its own
// slot 13 is 0x004502CE, pinned as SpecialAbilityUpdate::onExit (bool, bool)
// from the BFME1 donor, so this is the FellBeastSwoopPower override of that
// slot (ret 8, both args unused). Name by address: the override's exact
// signature and access are not established.
// Body: clear condition bit 7*32+20 on the owning Object (+0x08), then clear
// the bool at +0x88 (zeroed by the matched ctor).
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
static __forceinline void clearModelConditionBit(Object *object, int bit)
{
	if (object->m_conditionBits.test(bit) != 0)
	{
		object->m_conditionBits.clear(bit);
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
class SpecialAbilityUpdate : public UpdateModule
{
};
class FellBeastSwoopPower : public SpecialAbilityUpdate
{
public:
	virtual void rva004C6D0F(bool a, bool b);
private:
	unsigned char m_pad20[0x88 - 0x20];
	bool m_88;
};
void FellBeastSwoopPower::rva004C6D0F(bool, bool)
{
	clearModelConditionBit(m_object, 7 * 32 + 20);
	m_88 = false;
}
