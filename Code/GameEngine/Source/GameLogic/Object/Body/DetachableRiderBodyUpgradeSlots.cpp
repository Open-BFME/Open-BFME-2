// cl: /O1 /DNDEBUG /MD
//
// DetachableRiderBody's UpgradeMux overrides. Its matched ctor 0x004C1C82
// builds an UpgradeMux at +0x100 (rowed ctor 0x004CE2A3) and installs that
// subobject's vtable 0x00C5BF00, whose slots 1, 5, 9 and 16 are the rowed
// UpgradeMux members; the overrides below are compiled with the +0x100 this
// (the ModuleData at [this-0xFC], the Object at [this-0xF8]).
//
// ?getUpgradeActivationMasks@DetachableRiderBody@@MBEXAAUUpgradeMaskType@@0@Z,
// retail 0x004C1C29, 42 bytes: slot 11, copies the two 0x80-byte masks at
// module data's +0x64 block (+0x64 and +0xE4) out (ZH UpgradeMux's two-mask
// out query).
//
// ?performUpgradeFX@DetachableRiderBody@@MAEXXZ, retail 0x004C1C53, 21 bytes:
// slots 12 and 15 (one folded body), the pinned UpgradeMuxData member
// 0x0047A69C on the module data's +0x64 block with the Object, named as the
// rowed AutoHealBehavior slot 12 is.
//
// ?rva004C1C68@DetachableRiderBody@@MBE_NXZ, retail 0x004C1C68, 13 bytes, and
// ?rva004C1C75@DetachableRiderBody@@MBE_NXZ, retail 0x004C1C75, 13 bytes: slots
// 13 and 14, the module data's +0x170 and +0x171 flags. Address names.
//
// ?rva004C1BD4@DetachableRiderBody@@UAEPAVUpgradeMux@@XZ, retail 0x004C1BD4, 16
// bytes: slot 10 of the +0x0C vtable 0x00C5BFF8, this object's UpgradeMux,
// null-checked as cl converts. Address name.

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

struct DetachableRiderBodyModuleData
{
	unsigned char m_pad000[0x64];
	UpgradeMuxData m_upgradeMuxData; // +0x64
	unsigned char m_pad164[0x170 - 0x164];
	bool m_170; // +0x170
	bool m_171; // +0x171
};

template <int N> class Rva004C1C29Slots : public Rva004C1C29Slots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class Rva004C1C29Slots<1>
{
public:
	virtual void gap(char (*)[1]) = 0;
};

class UpgradeMux : public Rva004C1C29Slots<11>
{
protected:
	virtual void getUpgradeActivationMasks(UpgradeMaskType &activation, UpgradeMaskType &conflicting) const = 0;
	virtual void performUpgradeFX() = 0;
	virtual bool rva004C1C68() const = 0;
	virtual bool rva004C1C75() const = 0;
};

class BehaviorModuleInterface : public Rva004C1C29Slots<10>
{
public:
	virtual UpgradeMux *rva004C1BD4() = 0;
};

class BodyModule : public Rva004C1C29Slots<1>
{
protected:
	const ModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
};

class BodyModuleInterface
{
public:
	virtual void bodyModuleInterfaceAnchor();
};

class ActiveBody : public BodyModule, public BehaviorModuleInterface, public BodyModuleInterface
{
protected:
	unsigned char m_pad014[0x100 - 0x14];
};

class DetachableRiderBody : public ActiveBody, public UpgradeMux
{
public:
	virtual UpgradeMux *rva004C1BD4();
protected:
	virtual void getUpgradeActivationMasks(UpgradeMaskType &activation, UpgradeMaskType &conflicting) const;
	virtual void performUpgradeFX();
	virtual bool rva004C1C68() const;
	virtual bool rva004C1C75() const;
private:
	const DetachableRiderBodyModuleData *data() const { return (const DetachableRiderBodyModuleData *)m_moduleData; }
};

// ?getUpgradeActivationMasks@DetachableRiderBody@@MBEXAAUUpgradeMaskType@@0@Z @0x004C1C29
void DetachableRiderBody::getUpgradeActivationMasks(UpgradeMaskType &activation, UpgradeMaskType &conflicting) const
{
	const UpgradeMuxData &mux = data()->m_upgradeMuxData;
	activation = mux.m_activation;
	conflicting = mux.m_conflicting;
}

// ?performUpgradeFX@DetachableRiderBody@@MAEXXZ @0x004C1C53
void DetachableRiderBody::performUpgradeFX()
{
	data()->m_upgradeMuxData.performUpgradeFX(m_object);
}

// ?rva004C1C68@DetachableRiderBody@@MBE_NXZ @0x004C1C68
bool DetachableRiderBody::rva004C1C68() const
{
	return data()->m_170;
}

// ?rva004C1C75@DetachableRiderBody@@MBE_NXZ @0x004C1C75
bool DetachableRiderBody::rva004C1C75() const
{
	return data()->m_171;
}

// ?rva004C1BD4@DetachableRiderBody@@UAEPAVUpgradeMux@@XZ @0x004C1BD4
UpgradeMux *DetachableRiderBody::rva004C1BD4()
{
	return this;
}
