// cl: /DNDEBUG /MD
// Retail 0x004BC2E6 (63 bytes): ?update@AODCrushCollide@@UAE?AW4UpdateSleepTime@@XZ.
// Identity: slot 0 of the vtable 0x00C5A254 that the matched AODCrushCollide
// dtor 0x004BBEDD installs at +0x10, the UpdateModuleInterface base of an
// UpdateModule (slots 1/2 are the shared UpdateModule defaults 0x00253376 /
// 0x0044DF8D seen in every update vtable), i.e. update(); it returns 1
// (UPDATE_SLEEP_NONE) or 0x3FFFFFFF (UPDATE_SLEEP_FOREVER). cl 7.1 compiles
// the override with the +0x10 subobject this, hence [esi-8] for the Object.
// Body: while the +0x2C flag is set and the +0x24 frame is behind
// TheGameLogic frame (+0x40), clear condition bit 1*32+9 and the flag.
// Members +0x24/+0x28/+0x2C as the matched ctor 0x004BC00D initialises them.
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
class GameLogic
{
public:
	unsigned int getFrame() const { return m_frame; }
private:
	unsigned char m_pad[0x40];
	unsigned int m_frame;
};
extern GameLogic *TheGameLogic;
class AODCrushCollideIface20
{
public:
	virtual void iface20Anchor();
};
class AODCrushCollide : public UpdateModule, public AODCrushCollideIface20
{
public:
	virtual UpdateSleepTime update();
private:
	unsigned int m_24;
	int m_28;
	bool m_2C;
};
UpdateSleepTime AODCrushCollide::update()
{
	if (m_2C)
	{
		if (m_24 < TheGameLogic->getFrame())
		{
			clearModelConditionBit(m_object, 1 * 32 + 9);
			m_2C = false;
		}
		return UPDATE_SLEEP_NONE;
	}
	return UPDATE_SLEEP_FOREVER;
}
