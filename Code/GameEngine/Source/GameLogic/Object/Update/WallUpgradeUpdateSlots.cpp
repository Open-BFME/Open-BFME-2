// cl: /DNDEBUG /MD
//
// Two WallUpgradeUpdate overrides on the interface vtables its matched ctor
// 0x004AB317 installs over UpdateModule: 0x00C54768 at +0x20 and 0x00C54764 at
// +0x24, each compiled with its subobject this. Names are by address.
//
// ?rva004AB3AE@WallUpgradeUpdate@@UAE_NXZ, retail 0x004AB3AE, 61 bytes: +0x24
// slot 0; whether our Object is of KindOf 0x109, 0x108 or 0x107.
// ?rva004AB3EB@WallUpgradeUpdate@@UAEXHHH@Z, retail 0x004AB3EB, 42 bytes:
// +0x20 slot 2; when the third argument rises above the second to 3, arms
// +0x2C with eight times the constant g_009BA4E4 and wakes the module
// (UpdateModule::setWakeFrame, UPDATE_SLEEP_NONE).
// ?update@WallUpgradeUpdate@@UAE?AW4UpdateSleepTime@@XZ, retail 0x004AB4D8,
// 166 bytes: +0x10 slot 0 (vtable 0x00C54774), the update. A raised +0x30
// runs the matched scan 0x004AB415 once; the +0x2C countdown (armed by the
// +0x20 slot 2 above) raises +0x31 when it runs out and keeps the module
// awake meanwhile. With +0x31 up and the matched 0x004AB4AB check passing,
// the Object gets 0x0028DA28, its +0x254 body slot 9 with 0, condition bit
// 1*32+30 cleared (notifying through 0x0028AE6D) and statuses 0x13, 3, 0x56
// and 4 cleared through 0x0028CDEB with an Rva00346BC0 mask; otherwise it
// sleeps g_009BA4E4 frames.

enum KindOfType
{
	KINDOF_107 = 0x107,
	KINDOF_108 = 0x108,
	KINDOF_109 = 0x109
};

// ObjectStatusMask-shaped: four status bits set (first argument ignored).
class Rva00346BC0
{
public:
	Rva00346BC0(unsigned int a1, unsigned int a2, unsigned int a3, unsigned int a4, unsigned int a5);
private:
	unsigned int m_bits[4];
};

// Object +0x254: slot 9 takes an int.
class Rva004AB4D8Body
{
public:
	virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
	virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8();
	virtual void rva004AB4D8Slot9(int value);
};

class Rva004AB4D8Bits
{
public:
	unsigned int test(int bit) const { return m_words[bit >> 5] & (1U << (bit & 0x1f)); }
	void clear(int bit) { m_words[bit >> 5] &= ~(1U << (bit & 0x1f)); }
private:
	unsigned int m_words[19];
};

class Object
{
public:
	bool isKindOf(KindOfType kind) const;
	void rva0028DA28();
	void rva0028AE6D();
	void rva0028CDEB(const Rva00346BC0 &mask, bool set);
	unsigned char m_pad000[0x10C];
	Rva004AB4D8Bits m_conditionBits; // +0x10C
	unsigned char m_pad158[0x254 - 0x158];
	Rva004AB4D8Body *m_254; // +0x254
};

extern const int g_009BA4E4;

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3FFFFFFF
};

class ModuleData;

class BehaviorModule
{
public:
	virtual ~BehaviorModule();
protected:
	const ModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
};
struct BehaviorModuleInterface { virtual void f0C(); };
struct UpdateModuleInterface { virtual UpdateSleepTime update() = 0; };

class UpdateModule : public BehaviorModule, public BehaviorModuleInterface, public UpdateModuleInterface
{
protected:
	void setWakeFrame(Object *obj, UpdateSleepTime wakeDelay);
	unsigned int m_14;
	int m_18;
	int m_1C;
};

class Rva004AB3EBIface
{
public:
	virtual void gap0() = 0;
	virtual void gap1() = 0;
	virtual void rva004AB3EB(int a1, int previous, int current) = 0;
};

class Rva004AB3AEIface
{
public:
	virtual bool rva004AB3AE() = 0;
};

// The native update calls 0x004AB4AB with the complete module this pointer.
// Its verified provider reads the same +0x28 object ID; use that existing
// const thiscall bool() identity without emitting a second implementation.
class Rva004AB4AB
{
public:
    bool rva004AB4AB() const;
};

class WallUpgradeUpdate : public UpdateModule, public Rva004AB3EBIface, public Rva004AB3AEIface
{
public:
	virtual void rva004AB3EB(int a1, int previous, int current);
	virtual bool rva004AB3AE();
	virtual UpdateSleepTime update();
	void scanForBuildingAndPossess();
private:
	int m_28;
	int m_2C; // +0x2C
	bool m_30;
	bool m_31;
};

// ?rva004AB3AE@WallUpgradeUpdate@@UAE_NXZ @0x004AB3AE
bool WallUpgradeUpdate::rva004AB3AE()
{
	Object *obj = m_object;
	return obj->isKindOf(KINDOF_109) || obj->isKindOf(KINDOF_108) || obj->isKindOf(KINDOF_107);
}

// ?rva004AB3EB@WallUpgradeUpdate@@UAEXHHH@Z @0x004AB3EB
void WallUpgradeUpdate::rva004AB3EB(int, int previous, int current)
{
	if (current > previous && current == 3)
	{
		m_2C = g_009BA4E4 * 8;
		setWakeFrame(m_object, UPDATE_SLEEP_NONE);
	}
}

// ?update@WallUpgradeUpdate@@UAE?AW4UpdateSleepTime@@XZ @0x004AB4D8
UpdateSleepTime WallUpgradeUpdate::update()
{
	UpdateSleepTime ret = UPDATE_SLEEP_FOREVER;
	if (m_30)
	{
		m_30 = false;
		scanForBuildingAndPossess();
	}
	if (m_2C > 0)
	{
		if (--m_2C == 0)
			m_31 = true;
		else
			ret = UPDATE_SLEEP_NONE;
	}
	if (m_31)
	{
		if (reinterpret_cast<const Rva004AB4AB *>(this)->rva004AB4AB())
		{
			Object *obj = m_object;
			obj->rva0028DA28();
			obj->m_254->rva004AB4D8Slot9(0);
			if (obj->m_conditionBits.test(1 * 32 + 30))
			{
				obj->m_conditionBits.clear(1 * 32 + 30);
				obj->rva0028AE6D();
			}
			obj->rva0028CDEB(Rva00346BC0(0, 0x13, 3, 0x56, 4), false);
			m_31 = false;
		}
		else
			ret = (UpdateSleepTime)g_009BA4E4;
	}
	return ret;
}
