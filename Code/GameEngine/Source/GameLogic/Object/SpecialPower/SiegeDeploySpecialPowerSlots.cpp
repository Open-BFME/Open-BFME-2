// cl: /O1 /DNDEBUG /MD
//
// Three SiegeDeploySpecialPower overrides on the interface vtables its matched
// ctor 0x004C56BA installs over WeaponModeSpecialPowerUpdateBase: 0x00C5DCCC
// at +0x20 and 0x00C5DC68 at +0x24. Each is compiled with its subobject this.
// The deploy state int sits at +0x38 (the matched xfer saves it first; the
// unrowed setter 0x004C5BE3 compares its argument with it), the bool at +0x70.
// Names are by address.
//
// ?rva004C575F@SiegeDeploySpecialPower@@UAE_NXZ, retail 0x004C575F, 19 bytes:
// +0x20 slot 2; true unless the state is 0 or 1.
// ?rva004C5751@SiegeDeploySpecialPower@@UAE_NXZ, retail 0x004C5751, 14 bytes:
// +0x24 slot 1; the negation of +0x20 slot 2, called virtually.
// ?rva004C5E41@SiegeDeploySpecialPower@@UAEXXZ, retail 0x004C5E41, 33 bytes:
// +0x24 slot 17; states 0/1 call the setter with 0, states 2/3 set +0x70.

class Object;
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
struct UpdateModuleInterface { virtual void f10(); };

class UpdateModule : public BehaviorModule, public BehaviorModuleInterface, public UpdateModuleInterface
{
protected:
	unsigned int m_14;
	int m_18;
	int m_1C;
};

class Rva004C575FIface
{
public:
	virtual void gap0() = 0;
	virtual void gap1() = 0;
	virtual bool rva004C575F() = 0;
};

class Rva004C5751Iface
{
public:
	virtual void gap0() = 0;
	virtual bool rva004C5751() = 0;
	virtual void gap2() = 0;
	virtual void gap3() = 0;
	virtual void gap4() = 0;
	virtual void gap5() = 0;
	virtual void gap6() = 0;
	virtual void gap7() = 0;
	virtual void gap8() = 0;
	virtual void gap9() = 0;
	virtual void gap10() = 0;
	virtual void gap11() = 0;
	virtual void gap12() = 0;
	virtual void gap13() = 0;
	virtual void gap14() = 0;
	virtual void gap15() = 0;
	virtual void gap16() = 0;
	virtual void rva004C5E41() = 0;
};

class WeaponModeSpecialPowerUpdateBase : public UpdateModule, public Rva004C575FIface, public Rva004C5751Iface
{
protected:
	unsigned int m_28;
	int m_2C;
	unsigned int m_30;
	float m_34;
};

class SiegeDeploySpecialPower : public WeaponModeSpecialPowerUpdateBase
{
public:
	virtual bool rva004C575F();
	virtual bool rva004C5751();
	virtual void rva004C5E41();
private:
	void rva004C5BE3(int state);
	int m_38; // +0x38
	unsigned char m_pad3C[0x70 - 0x3C];
	bool m_70; // +0x70
};

// ?rva004C575F@SiegeDeploySpecialPower@@UAE_NXZ @0x004C575F
bool SiegeDeploySpecialPower::rva004C575F()
{
	return !(m_38 == 0 || m_38 == 1);
}

// ?rva004C5751@SiegeDeploySpecialPower@@UAE_NXZ @0x004C5751
bool SiegeDeploySpecialPower::rva004C5751()
{
	return !rva004C575F();
}

// ?rva004C5E41@SiegeDeploySpecialPower@@UAEXXZ @0x004C5E41
void SiegeDeploySpecialPower::rva004C5E41()
{
	switch (m_38)
	{
	case 0:
	case 1:
		rva004C5BE3(0);
		break;
	case 2:
	case 3:
		m_70 = true;
		break;
	}
}
