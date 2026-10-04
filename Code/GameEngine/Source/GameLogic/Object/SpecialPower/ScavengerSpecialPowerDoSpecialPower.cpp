// cl: /O1 /MD /GX /arch:SSE
//
// ScavengerSpecialPower::doSpecialPower, retail 0x004C4401, 47 bytes: slot
// 10 of the class's +0x10 special-power interface vftable 0x00C5D2A0 (slots
// 11/12 there are the SpecialPowerModule bases), so `this` is that subobject
// (module data at -0x0C, Object at -0x08). Stores the module data's +0x7C
// float into the controlling Player's +0x314 (0x002A9E25, pinned for Player
// by address on this call site), runs the SpecialPowerModule base
// doSpecialPower 0x0049490F, then raises the byte at +0x34.
class Player
{
public:
	void rva002A9E25(float value);	// sets +0x314
};

class Object
{
public:
	Player *getControllingPlayer() const;	// 0x0028AFA9
};

struct ScavengerSpecialPowerModuleData
{
	unsigned char m_pad00[0x7C];
	float m_7C;			// +0x7C
};

class ModuleData;
class ModuleBase
{
public:
	virtual ~ModuleBase();
protected:
	const ModuleData *m_moduleData;	// +0x04
	Object *m_object;		// +0x08
};

class BehaviorModuleInterface
{
public:
	virtual void b00() = 0;
};

class SpecialPowerModuleInterface
{
public:
	virtual void s00() = 0;
	virtual void s01() = 0;
	virtual void s02() = 0;
	virtual void s03() = 0;
	virtual void s04() = 0;
	virtual void s05() = 0;
	virtual void s06() = 0;
	virtual void s07() = 0;
	virtual void s08() = 0;
	virtual void s09() = 0;
	virtual void doSpecialPower(unsigned int options) = 0;
};

class SpecialPowerModule : public ModuleBase, public BehaviorModuleInterface,
	public SpecialPowerModuleInterface
{
public:
	virtual void doSpecialPower(unsigned int options);	// 0x0049490F
protected:
	unsigned char m_pad14[0x34 - 0x14];
};

class ScavengerSpecialPower : public SpecialPowerModule
{
public:
	virtual void doSpecialPower(unsigned int options);
	const ScavengerSpecialPowerModuleData *getData() const
	{
		return (const ScavengerSpecialPowerModuleData *)m_moduleData;
	}
private:
	bool m_34;			// +0x34
};

void ScavengerSpecialPower::doSpecialPower(unsigned int options)
{
	const ScavengerSpecialPowerModuleData *data = getData();
	Object *object = m_object;
	object->getControllingPlayer()->rva002A9E25(data->m_7C);
	SpecialPowerModule::doSpecialPower(options);
	m_34 = true;
}
