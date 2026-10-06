// cl: /DNDEBUG /MD
//
// ?rva004B5765@WeaponSetUpgradeSecondary@@QAEXXZ @0x004B5765 30B
// Chain after 0x0028D86F: UpgradeModule apply plus Object WeaponSet bitset OR.
// Retail: lea ecx [esi-0x10] call UpgradeModule::rva004CE4A0, then
// mov eax [esi-0xC] mov ecx [esi-0x8] add eax 0x118 push eax
// call Rva0028D86F::rva0028D86F. Layout from UpgradeModuleConditionState
// (ModuleData at +4 Object at +8 Mux at +0x10) plus AllowBanner precedent.
// ModuleData bitset at +0x118 (16B _Base_bitset<4>), Object at +8 is the
// Rva0028D86F receiver (WeaponSet at +0x330 bitset at +0x370 per its TU).
// Evidence: vtable 0x00857F68 slot 22 class Rva004B55C8, prev 0x004B5749
// next 0x004B57AA WeaponSetUpgradeModuleData, callees rowed 0x004CE4A0
// plus 0x0028D86F, LINK none.

namespace _STL
{
template<unsigned N> struct _Base_bitset;
template<> struct _Base_bitset<4>
{
	unsigned long _M_w[4];
};
}

class Object;
class ModuleData;

class BehaviorModuleBase
{
public:
	virtual void behaviorModuleBaseAnchor();
	const ModuleData *m_moduleData;
	Object *m_object;
};

class BehaviorModuleOther
{
public:
	virtual void behaviorModuleOtherAnchor();
};

class BehaviorModule : public BehaviorModuleBase, public BehaviorModuleOther
{
};

class UpgradeModuleInterface
{
public:
	virtual void upgradeModuleInterfaceAnchor();
};

template<int N> class UpgradeMuxSlots : public UpgradeMuxSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template<> class UpgradeMuxSlots<0>
{
};

class UpgradeMuxIface : public UpgradeMuxSlots<8>
{
protected:
	virtual void upgradeRemovalImplementation() = 0;
	virtual void slot09() = 0;
	virtual void upgradeImplementation() = 0;
};

class UpgradeModule : public BehaviorModule, public UpgradeModuleInterface, public UpgradeMuxIface
{
public:
	void rva004CE4A0();
};

class Rva0028D86F
{
public:
	void rva0028D86F(const _STL::_Base_bitset<4> &other);
};

class WeaponSetUpgradeSecondary
{
public:
	void rva004B5765();
};

void WeaponSetUpgradeSecondary::rva004B5765()
{
	((UpgradeModule *)((char *)this - 0x10))->rva004CE4A0();
	const ModuleData *data = *(const ModuleData * const *)((const char *)this - 0xC);
	Object *obj = *(Object * const *)((const char *)this - 0x8);
	const _STL::_Base_bitset<4> *bits = (const _STL::_Base_bitset<4> *)((const char *)data + 0x118);
	((Rva0028D86F *)obj)->rva0028D86F(*bits);
}
