// cl: /O1 /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// Three SpellRechargeModifierUpgrade overrides on the vtables its matched ctor
// 0x004B5D7D installs: the upgrade mux 0x00C58368 at +0x10 and the 4-slot
// interface 0x00C58358 at +0x1C (the ctor also sets the bool at +0x20). Each
// is compiled with its subobject this. The controlling player's counter and
// recharge-modifier float are the rowed one-field Player members 0x002AA0BF
// (inc), 0x002AA0C6 (dec), 0x002AA0B8 (get) and 0x002AA0CD (set); the
// modifiers come from the module data's float vector at +0x118, indexed by
// the counter minus one, clamped to the vector. Names are by address.
//
// ?rva004B5F9F@SpellRechargeModifierUpgrade@@UAEXXZ, retail 0x004B5F9F, 114
// bytes: mux slot 10; counts one more upgrade and applies its modifier.
// ?rva004B5E46@SpellRechargeModifierUpgrade@@UAEXXZ, retail 0x004B5E46, 126
// bytes: mux slot 8; when mux slot 0 holds, counts one fewer and reapplies.
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

// The clamps compare as (a < b) ? a : b and (a > b) ? a : b, the operand
// order retail tests (STLport's min and max test b < a and a < b), and the
// index lives in one variable throughout: that is what puts it in the first
// of the two stack temporaries both clamps share, as retail does.
template <class T> inline const T &lowerOf(const T &a, const T &b)
{
	return (a < b) ? a : b;
}
template <class T> inline const T &higherOf(const T &a, const T &b)
{
	return (a > b) ? a : b;
}

static __forceinline void applyModifier(Player *player, const SpellRechargeModifierUpgradeModuleData *data)
{
	int index = ((Rva002AA0B8DwordField *)player)->get() - 1;
	index = higherOf(index, 0);
	int last = (int)data->m_modifiers.size() - 1;
	index = lowerOf(index, last);
	((Rva002AA0CDFloatField *)player)->set(data->m_modifiers[index]);
}

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
	virtual void rva004B5F9F();
	virtual void rva004B5E46();
	virtual void rva004B5DDC();
private:
	bool m_20; // +0x20
};

// ?rva004B5F9F@SpellRechargeModifierUpgrade@@UAEXXZ @0x004B5F9F
void SpellRechargeModifierUpgrade::rva004B5F9F()
{
	Player *player = m_object->getControllingPlayer();
	const SpellRechargeModifierUpgradeModuleData *data = m_moduleData;
	((Rva002AA0BFDwordCounter *)player)->inc();
	applyModifier(player, data);
}

// ?rva004B5E46@SpellRechargeModifierUpgrade@@UAEXXZ @0x004B5E46
void SpellRechargeModifierUpgrade::rva004B5E46()
{
	if (!slot0())
		return;
	const SpellRechargeModifierUpgradeModuleData *data = m_moduleData;
	Player *player = m_object->getControllingPlayer();
	if (!player)
		return;
	((Rva002AA0C6DwordCounter *)player)->dec();
	applyModifier(player, data);
}

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
