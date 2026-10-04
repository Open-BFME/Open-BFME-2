// cl: /O1 /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// SpellRechargeModifierUpgrade overrides on the vtables its matched ctor
// 0x004B5D7D installs: the upgrade mux 0x00C58368 at +0x10 and the 4-slot
// interface 0x00C58358 at +0x1C (the ctor also sets the bool at +0x20). Each
// is compiled with its subobject this. The controlling player's counter and
// recharge-modifier float are the rowed one-field Player members 0x002AA0BF
// (inc), 0x002AA0C6 (dec), 0x002AA0B8 (get) and 0x002AA0CD (set); the
// modifiers come from the module data's float vector at +0x118, indexed by
// the counter minus one, clamped to the vector. Names are by address.
//
// Mux slots 10 (0x004B5F9F) and 8 (0x004B5E46) are banked near-misses.
// ?rva004B5DDC@SpellRechargeModifierUpgrade@@UAEXXZ, retail 0x004B5DDC, 42
// bytes: +0x1C slot 1; with the module data's +0x124 flag runs mux slots 10
// and 9 (1), then sets +0x20.

#include <algorithm>
#include <vector>

class Player;

class Rva002AA0BFDwordCounter { public: void inc(); };
class Rva002AA0C6DwordCounter { public: void dec(); };
class Rva002AA0B8DwordField { public: int get() const; };
class Rva002AA0CDFloatField { public: void set(float value); };

class Object
{
public:
	Player *getControllingPlayer() const;
};

struct SpellRechargeModifierUpgradeModuleData
{
	unsigned char m_pad000[0x118];
	_STL::vector<float> m_modifiers; // +0x118
	bool m_124; // +0x124
};

class BehaviorModule
{
public:
	virtual ~BehaviorModule();
protected:
	const SpellRechargeModifierUpgradeModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
};
struct BehaviorModuleInterface { virtual void f0C(); };

class UpgradeMux
{
public:
	virtual bool slot0() = 0;
	virtual void gap1() = 0; virtual void gap2() = 0; virtual void gap3() = 0; virtual void gap4() = 0;
	virtual void gap5() = 0; virtual void gap6() = 0; virtual void gap7() = 0;
	virtual void rva004B5E46() = 0;
	virtual void slot9(int a1) = 0;
	virtual void rva004B5F9F() = 0;
};

struct UpgradeIface18 { virtual void f18(); };

class UpgradeModule : public BehaviorModule, public BehaviorModuleInterface, public UpgradeMux
{
protected:
	int m_14;
};

class Rva004B5DDCIface
{
public:
	virtual void gap0() = 0;
	virtual void rva004B5DDC() = 0;
};

class SpellRechargeModifierUpgrade : public UpgradeModule, public UpgradeIface18, public Rva004B5DDCIface
{
public:
	virtual void rva004B5DDC();
private:
	bool m_20; // +0x20
};

// ?rva004B5DDC@SpellRechargeModifierUpgrade@@UAEXXZ @0x004B5DDC
void SpellRechargeModifierUpgrade::rva004B5DDC()
{
	if (m_moduleData->m_124)
	{
		rva004B5F9F();
		slot9(1);
	}
	m_20 = true;
}
