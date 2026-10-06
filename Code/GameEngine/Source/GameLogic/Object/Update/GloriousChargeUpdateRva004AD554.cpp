// cl: /DNDEBUG /MD
// Retail 0x004AD554 (56 bytes): ?rva004AD554@GloriousChargeUpdate@@UAEXXZ.
// Identity: slot 15 of the primary vtable 0x00C55118 that the matched
// GloriousChargeUpdate dtor 0x004AD58C installs (slot 0 is the matched
// ??_GGloriousChargeUpdate, slot 4 its pool key). Its base is
// SpecialAbilityUpdate: the base vtable 0x00C3FBA8 has the matched
// ??_GSpecialAbilityUpdate, xfer and pool key in slots 0/3/4 and holds
// 0x00450D9A in slot 15, which this override calls first as the base
// implementation (pinned here as ?rva00450D9A@SpecialAbilityUpdate@@UAEXXZ).
// Names by address: the slot name is not established.
// Body: base call, set condition bit 6*32+15 on the Object, then OR 0x10 into
// the +0x118 word of its Drawable (pinned getDrawable 0x005508E2).
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
class Drawable
{
public:
	unsigned char m_pad[0x118];
	unsigned int m_118;
};
class SpecialAbilityUpdate : public UpdateModule
{
public:
	virtual void rva00450D9A();
};
class GloriousChargeUpdate : public SpecialAbilityUpdate
{
public:
	virtual void rva004AD554();
};
void GloriousChargeUpdate::rva004AD554()
{
	SpecialAbilityUpdate::rva00450D9A();
	setModelConditionBit(m_object, 6 * 32 + 15);
	Drawable *draw = m_object->getDrawable();
	if (draw)
		draw->m_118 |= 0x10;
}
