// cl: /DNDEBUG /MD /EHs
//
// FellBeastSwoopPower::update, retail 0x004C6E49 (254 bytes): slot 0 of the
// vtable 0x00C5DF74 that the matched FellBeastSwoopPower ctor 0x004C6C1E
// installs at +0x10 (UpdateModuleInterface), compiled with that subobject this.
// First frame: call primary slot 17 and raise the +0x88 flag (the one the matched
// slot-13 override 0x004C6D0F clears). Afterwards: when the Object +0x258
// interface answers slot 110 or slot 116, end the swoop through primary slot 13
// (false, false) and sleep forever; otherwise compare the height above ground
// (TheTerrainLogic slot 6, getGroundHeight(x, y, NULL), stored to a float local
// before the SSE subtraction as retail does) with the +0x14 field of a copy of
// the Object GeometryInfo at +0xA8 (matched copy ctor 0x000929E8 and virtual
// dtor 0x00050B2A, hence the EH frame) and set or clear condition bit 7*32+20.
// One NONE exit for both paths. Slot names are not established.
// Condition word array at Object+0x10C with masked-word accessors.

struct Coord3D;
class GeometryInfo
{
public:
	GeometryInfo(const GeometryInfo &other);
	virtual ~GeometryInfo();
	float m_04;
	float m_08;
	float m_0C;
	float m_10;
	float m_14; // +0x14
	unsigned char m_pad18[0x5C - 0x18];
};
class TerrainLogic
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual float getGroundHeight(float x, float y, Coord3D *normal) const;
};
extern TerrainLogic *TheTerrainLogic;
template <int N> class Rva004C6E49Slots : public Rva004C6E49Slots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class Rva004C6E49Slots<0>
{
};
// The Object +0x258 interface (AI): slots 110 and 116 are bool queries.
class Rva004C6E49AI110 : public Rva004C6E49Slots<110>
{
public:
	virtual bool rva004C6E49Slot110() = 0;
	virtual void gap111() = 0;
	virtual void gap112() = 0;
	virtual void gap113() = 0;
	virtual void gap114() = 0;
	virtual void gap115() = 0;
	virtual bool rva004C6E49Slot116() = 0;
};
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
	unsigned int m_words[19];
};
class Object
{
public:
	void rva0028AE6D();
	unsigned char m_pad000[0x38];
	float m_x; // +0x38
	float m_y; // +0x3C
	float m_z; // +0x40
	unsigned char m_pad044[0xA8 - 0x44];
	GeometryInfo m_geometryInfo; // +0xA8
	unsigned char m_pad104[0x10C - 0x104];
	Rva0010CBits m_conditionBits; // +0x10C
	unsigned char m_pad158[0x258 - 0x158];
	Rva004C6E49AI110 *m_ai; // +0x258
};
enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3fffffff
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
	unsigned int m_14;
	int m_18;
	int m_1C;
};
class SpecialPowerUpdateInterface
{
public:
	virtual void specialPowerUpdateAnchor();
};
class SpecialAbilityUpdate : public UpdateModule, public SpecialPowerUpdateInterface
{
public:
	virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06();
	virtual void slot07(); virtual void slot08(); virtual void slot09();
	virtual void slot10(); virtual void slot11(); virtual void slot12();
	virtual void slot13(bool a, bool b); // FellBeastSwoopPower 0x004C6D0F
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
private:
	unsigned char m_pad24[0x88 - 0x24];
};
class FellBeastSwoopPower : public SpecialAbilityUpdate
{
public:
	virtual UpdateSleepTime update();
private:
	bool m_88; // +0x88
};
UpdateSleepTime FellBeastSwoopPower::update()
{
	if (!m_88)
	{
		slot17();
		m_88 = true;
	}
	else
	{
		Object *object = m_object;
		Rva004C6E49AI110 *ai = object->m_ai;
		if (ai && (ai->rva004C6E49Slot110() || ai->rva004C6E49Slot116()))
		{
			slot13(false, false);
			return UPDATE_SLEEP_FOREVER;
		}
		float ground = TheTerrainLogic->getGroundHeight(object->m_x, object->m_y, 0);
		float height = object->m_z - ground;
		GeometryInfo geometry(object->m_geometryInfo);
		if (geometry.m_14 > height)
		{
			if (object->m_conditionBits.test(7 * 32 + 20) == 0)
			{
				object->m_conditionBits.set(7 * 32 + 20);
				object->rva0028AE6D();
			}
		}
		else
		{
			if (object->m_conditionBits.test(7 * 32 + 20) != 0)
			{
				object->m_conditionBits.clear(7 * 32 + 20);
				object->rva0028AE6D();
			}
		}
	}
	return UPDATE_SLEEP_NONE;
}
