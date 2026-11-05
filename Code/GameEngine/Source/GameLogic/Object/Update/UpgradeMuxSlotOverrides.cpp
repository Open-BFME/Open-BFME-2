// cl: /DNDEBUG /MD
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
// +0x20, +0x30 and +0x14 respectively. AudioLoopUpgrade's slot 11 does not copy
// the masks inline: it tail-jumps to the shared out-of-line copy 0x0045F2D5
// (SpawnBehavior_getUpgradeActivationMasks.cpp), as SpawnBehavior's does.

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
	void rva0045F2D5(UpgradeMaskType &activation, UpgradeMaskType &conflicting) const;
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

#include "../../../../Include/GameLogic/Module/UpgradeMux.h"

class UpdateModuleView
{
public:
	virtual ~UpdateModuleView();
protected:
	const ModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
	unsigned char m_pad0C[0x20 - 0x0C];
};

#include "../../../../Include/GameLogic/Module/AttributeModifierAuraUpdateModuleData.h"

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
	const UpgradeMuxData &mux = reinterpret_cast<const UpgradeMuxData &>(data()->m_28);
	activation = mux.m_activation;
	conflicting = mux.m_conflicting;
}

// ?performUpgradeFX@AttributeModifierAuraUpdate@@MAEXXZ @0x0049B648
void AttributeModifierAuraUpdate::performUpgradeFX()
{
	reinterpret_cast<const UpgradeMuxData &>(data()->m_28).performUpgradeFX(m_object);
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
	virtual void getUpgradeActivationMasks(UpgradeMaskType &activation, UpgradeMaskType &conflicting) const;
	virtual bool requiresAllActivationUpgrades() const;
	virtual void performUpgradeFX();
private:
	const AudioLoopUpgradeModuleData *data() const { return (const AudioLoopUpgradeModuleData *)m_moduleData; }
};

// ?getUpgradeActivationMasks@AudioLoopUpgrade@@MBEXAAUUpgradeMaskType@@0@Z @0x004B7E0E
void AudioLoopUpgrade::getUpgradeActivationMasks(UpgradeMaskType &activation, UpgradeMaskType &conflicting) const
{
	data()->m_upgradeMuxData.rva0045F2D5(activation, conflicting);
}

// ?requiresAllActivationUpgrades@AudioLoopUpgrade@@MBE_NXZ @0x004B7E19
bool AudioLoopUpgrade::requiresAllActivationUpgrades() const
{
	return ((const AudioLoopUpgradeModuleData *)m_moduleData)->m_120;
}

// ?performUpgradeFX@AudioLoopUpgrade@@MAEXXZ @0x004B7E2D
void AudioLoopUpgrade::performUpgradeFX()
{
	data()->m_upgradeMuxData.performUpgradeFX(m_object);
}


// ObjectCreationUpgrade (vtable entries 0x00857688/0x0085768C/0x00857690/0x0085769C):
// slots 10, 11, 12 and 15 of the primary UpgradeMux vtable 0x00857660, compiled with
// a this whose UpdateModule subobject sits at +0x08 (ModuleData at +0x0C, Object at
// +0x10). The UpgradeMuxData block sits at module data +0x10.
enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1
};

class GameLogic;
extern GameLogic *TheGameLogic;
struct GameLogicFrameView
{
	unsigned char m_pad00[0x40];
	unsigned int m_frame;
};

#include "../../../../Include/GameLogic/Module/UpdateModule.h"

class ObjectCreationUpgradeModuleData
{
public:
	unsigned char m_pad000[0x0C];
	unsigned int m_delay; // +0x0C
	UpgradeMuxData m_upgradeMuxData; // +0x10
};

class ObjectCreationUpgrade : public UpgradeMux, public UpdateModule
{
protected:
	virtual void upgradeImplementation();
	virtual void getUpgradeActivationMasks(UpgradeMaskType &activation, UpgradeMaskType &conflicting) const;
	virtual void performUpgradeFX();
private:
	unsigned int m_28; // +0x28
	bool m_2C; // +0x2C
	const ObjectCreationUpgradeModuleData *data() const { return (const ObjectCreationUpgradeModuleData *)m_moduleData; }
};

// ?getUpgradeActivationMasks@ObjectCreationUpgrade@@MBEXAAUUpgradeMaskType@@0@Z @0x004B403A
void ObjectCreationUpgrade::getUpgradeActivationMasks(UpgradeMaskType &activation, UpgradeMaskType &conflicting) const
{
	const UpgradeMuxData &mux = data()->m_upgradeMuxData;
	activation = mux.m_activation;
	conflicting = mux.m_conflicting;
}

// ?performUpgradeFX@ObjectCreationUpgrade@@MAEXXZ @0x004B4075
void ObjectCreationUpgrade::performUpgradeFX()
{
	data()->m_upgradeMuxData.performUpgradeFX(m_object);
}

// ?upgradeImplementation@ObjectCreationUpgrade@@MAEXXZ @0x004B4106
void ObjectCreationUpgrade::upgradeImplementation()
{
	if (!m_2C)
	{
		m_28 = data()->m_delay + ((const GameLogicFrameView *)TheGameLogic)->m_frame;
		m_2C = true;
		setWakeFrame(m_object, UPDATE_SLEEP_NONE);
	}
}
