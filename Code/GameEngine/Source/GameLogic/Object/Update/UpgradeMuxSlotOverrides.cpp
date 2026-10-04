// cl: /O1 /DNDEBUG /MD
//
// UpgradeMux overrides of four BFME update/upgrade modules that carry their
// UpgradeMux at +0x20 (each class's ctor installs the UpgradeMux vtable there:
// AttributeModifierAuraUpdate 0x00C50CD8, RadiateFearUpdate 0x00C50F68,
// BroadcastStealthUpdate 0x00C52310, AudioLoopUpgrade 0x00C58C70; slots 1 and
// 5 are the rowed UpgradeMux members). Compiled with the +0x20 this (the
// ModuleData at [this-0x1C], the Object at [this-0x18]). As in
// DetachableRiderBodyUpgradeSlots.cpp: slot 11 copies the two 0x80-byte masks
// at the head of the module data's UpgradeMuxData block out
// (getUpgradeActivationMasks shape), slots 12 and 15 (one folded body) run the
// pinned UpgradeMuxData::performUpgradeFX on that block (named as the rowed
// AutoHealBehavior slot 12); AudioLoopUpgrade's slot 13 reads a module-data
// flag (address name). The UpgradeMuxData block sits at module data +0x28,
// +0x20, +0x30 and +0x14 respectively.

class Object;
class ModuleData;

struct UpgradeMaskType
{
	unsigned int m_bits[32];
};

class UpgradeMuxData
{
public:
	void performUpgradeFX(Object *obj) const;
	UpgradeMaskType m_activation; // +0x00
	UpgradeMaskType m_conflicting; // +0x80
};

template <int N> class UpgradeMuxSlots : public UpgradeMuxSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class UpgradeMuxSlots<1>
{
public:
	virtual void gap(char (*)[1]) = 0;
};

class UpgradeMux : public UpgradeMuxSlots<11>
{
protected:
	virtual void getUpgradeActivationMasks(UpgradeMaskType &activation, UpgradeMaskType &conflicting) const = 0;
	virtual void performUpgradeFX() = 0;
	virtual bool rva004B7E19() const = 0;
};

class UpdateModuleView
{
public:
	virtual ~UpdateModuleView();
protected:
	const ModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
	unsigned char m_pad0C[0x20 - 0x0C];
};

struct AttributeModifierAuraUpdateModuleData
{
	unsigned char m_pad000[0x28];
	UpgradeMuxData m_upgradeMuxData; // +0x28
};

class AttributeModifierAuraUpdate : public UpdateModuleView, public UpgradeMux
{
protected:
	virtual void getUpgradeActivationMasks(UpgradeMaskType &activation, UpgradeMaskType &conflicting) const;
	virtual void performUpgradeFX();
private:
	const AttributeModifierAuraUpdateModuleData *data() const { return (const AttributeModifierAuraUpdateModuleData *)m_moduleData; }
};

// ?getUpgradeActivationMasks@AttributeModifierAuraUpdate@@MBEXAAUUpgradeMaskType@@0@Z @0x0049B621
void AttributeModifierAuraUpdate::getUpgradeActivationMasks(UpgradeMaskType &activation, UpgradeMaskType &conflicting) const
{
	const UpgradeMuxData &mux = data()->m_upgradeMuxData;
	activation = mux.m_activation;
	conflicting = mux.m_conflicting;
}

// ?performUpgradeFX@AttributeModifierAuraUpdate@@MAEXXZ @0x0049B648
void AttributeModifierAuraUpdate::performUpgradeFX()
{
	data()->m_upgradeMuxData.performUpgradeFX(m_object);
}

struct RadiateFearUpdateModuleData
{
	unsigned char m_pad000[0x20];
	UpgradeMuxData m_upgradeMuxData; // +0x20
};

class RadiateFearUpdate : public UpdateModuleView, public UpgradeMux
{
protected:
	virtual void getUpgradeActivationMasks(UpgradeMaskType &activation, UpgradeMaskType &conflicting) const;
	virtual void performUpgradeFX();
private:
	const RadiateFearUpdateModuleData *data() const { return (const RadiateFearUpdateModuleData *)m_moduleData; }
};

// ?getUpgradeActivationMasks@RadiateFearUpdate@@MBEXAAUUpgradeMaskType@@0@Z @0x0049C022
void RadiateFearUpdate::getUpgradeActivationMasks(UpgradeMaskType &activation, UpgradeMaskType &conflicting) const
{
	const UpgradeMuxData &mux = data()->m_upgradeMuxData;
	activation = mux.m_activation;
	conflicting = mux.m_conflicting;
}

// ?performUpgradeFX@RadiateFearUpdate@@MAEXXZ @0x0049C049
void RadiateFearUpdate::performUpgradeFX()
{
	data()->m_upgradeMuxData.performUpgradeFX(m_object);
}

struct BroadcastStealthUpdateModuleData
{
	unsigned char m_pad000[0x30];
	UpgradeMuxData m_upgradeMuxData; // +0x30
};

class BroadcastStealthUpdate : public UpdateModuleView, public UpgradeMux
{
protected:
	virtual void getUpgradeActivationMasks(UpgradeMaskType &activation, UpgradeMaskType &conflicting) const;
	virtual void performUpgradeFX();
private:
	const BroadcastStealthUpdateModuleData *data() const { return (const BroadcastStealthUpdateModuleData *)m_moduleData; }
};

// ?getUpgradeActivationMasks@BroadcastStealthUpdate@@MBEXAAUUpgradeMaskType@@0@Z @0x004A350B
void BroadcastStealthUpdate::getUpgradeActivationMasks(UpgradeMaskType &activation, UpgradeMaskType &conflicting) const
{
	const UpgradeMuxData &mux = data()->m_upgradeMuxData;
	activation = mux.m_activation;
	conflicting = mux.m_conflicting;
}

// ?performUpgradeFX@BroadcastStealthUpdate@@MAEXXZ @0x004A3532
void BroadcastStealthUpdate::performUpgradeFX()
{
	data()->m_upgradeMuxData.performUpgradeFX(m_object);
}

struct AudioLoopUpgradeModuleData
{
	unsigned char m_pad000[0x14];
	UpgradeMuxData m_upgradeMuxData; // +0x14
	unsigned char m_pad114[0x120 - 0x114];
	bool m_120; // +0x120
};

class AudioLoopUpgrade : public UpdateModuleView, public UpgradeMux
{
protected:
	virtual bool rva004B7E19() const;
	virtual void performUpgradeFX();
private:
	const AudioLoopUpgradeModuleData *data() const { return (const AudioLoopUpgradeModuleData *)m_moduleData; }
};

// ?rva004B7E19@AudioLoopUpgrade@@MBE_NXZ @0x004B7E19
bool AudioLoopUpgrade::rva004B7E19() const
{
	return ((const AudioLoopUpgradeModuleData *)m_moduleData)->m_120;
}

// ?performUpgradeFX@AudioLoopUpgrade@@MAEXXZ @0x004B7E2D
void AudioLoopUpgrade::performUpgradeFX()
{
	data()->m_upgradeMuxData.performUpgradeFX(m_object);
}

