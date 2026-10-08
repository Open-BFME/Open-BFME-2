// cl: /DNDEBUG /MD
//
// Small vtable-slot bodies with no ledger owner and no Ghidra entry (sized
// from their bytes), batch U: overrides reached through a secondary base, so
// each body reads the complete object at a negative displacement from the
// interface's this. Each class models only the base offset and the members
// the body touches (the module data at +0x04, the object at +0x08); class
// names are address-derived, method names are the slot's where the ledger
// names the slot in a sibling table. Meanings are not recovered.

typedef int Int;
typedef unsigned int UnsignedInt;

class Object;
class AsciiString;

// A primary base of the given size: vtable, module data, object.
template <int SIZE>
class Rva00452EDDPrimary
{
public:
	virtual void primarySlot();
protected:
	const void *m_moduleData; // +0x04
	Object *m_object; // +0x08
	char m_pad0C[SIZE - 0x0C];
};

// 0x00452EDD, 0x00452EF5, 0x00452F0D (interface at +0x20): the template the
// registry at VA 0x00DFF000 finds for the module data's name at +0x14, +0x18
// resp. +0x1C, NULL without module data.
class Rva002D06CA
{
public:
	void *rva002D06CA(const AsciiString *name);
};
extern class ThingFactory *TheThingFactory;
struct Rva00452EDDData
{
	char m_pad00[0x14];
	void *m_14; // AsciiString
	void *m_18; // AsciiString
	void *m_1C; // AsciiString
};
class Rva00452EDDIface
{
public:
	virtual void *rva00452EDD() = 0;
	virtual void *rva00452EF5() = 0;
	virtual void *rva00452F0D() = 0;
};
class Rva00452EDD : public Rva00452EDDPrimary<0x20>, public Rva00452EDDIface
{
public:
	void *rva00452EDD();
	void *rva00452EF5();
	void *rva00452F0D();
};
void *Rva00452EDD::rva00452EDD()
{
	const Rva00452EDDData *d = (const Rva00452EDDData *)m_moduleData;
	if (!d)
		return 0;
	return ((Rva002D06CA *)TheThingFactory)->rva002D06CA((const AsciiString *)&d->m_14);
}
void *Rva00452EDD::rva00452EF5()
{
	const Rva00452EDDData *d = (const Rva00452EDDData *)m_moduleData;
	if (!d)
		return 0;
	return ((Rva002D06CA *)TheThingFactory)->rva002D06CA((const AsciiString *)&d->m_18);
}
void *Rva00452EDD::rva00452F0D()
{
	const Rva00452EDDData *d = (const Rva00452EDDData *)m_moduleData;
	if (!d)
		return 0;
	return ((Rva002D06CA *)TheThingFactory)->rva002D06CA((const AsciiString *)&d->m_1C);
}

// 0x0044F09F (interface at +0x20, beside WeaponFireSpecialAbilityUpdate's
// slots): whether the module data's +0x38 equals the argument.
struct Rva0044F09FData
{
	char m_pad00[0x38];
	Int m_38;
};
class Rva0044F09FIface
{
public:
	virtual bool rva0044F09F(Int value) = 0;
};
class Rva0044F09F : public Rva00452EDDPrimary<0x20>, public Rva0044F09FIface
{
public:
	bool rva0044F09F(Int value);
};
bool Rva0044F09F::rva0044F09F(Int value)
{
	return value == ((const Rva0044F09FData *)m_moduleData)->m_38;
}

// UpgradeMux slots: the activation and conflicting masks (0x80 bytes each)
// at the module data's mux data, and the pinned UpgradeMuxData FX call with
// the object. Interface at +0x20 (0x00452460, beside the rowed
// AutoHealBehavior::performUpgradeFX), +0x10 (0x00460AAC, 0x00460AD3) and
// +0x30 (0x0045F46A, mux data at +0x5C).
struct UpgradeMaskType
{
	UnsignedInt m_words[0x20];
};
class UpgradeMuxData
{
public:
	void performUpgradeFX(Object *obj) const;
	__forceinline void getUpgradeActivationMasks(UpgradeMaskType &activation, UpgradeMaskType &conflicting) const
	{
		activation = m_activationUpgradeNames;
		conflicting = m_conflictingUpgradeNames;
	}
	UpgradeMaskType m_activationUpgradeNames;
	UpgradeMaskType m_conflictingUpgradeNames;
};
struct Rva00452460Data
{
	char m_pad00[0x08];
	UpgradeMuxData m_upgradeMuxData; // +0x08
};
struct Rva0045F46AData
{
	char m_pad00[0x5C];
	UpgradeMuxData m_upgradeMuxData; // +0x5C
};
class Rva00452460Iface
{
public:
	virtual void getUpgradeActivationMasks(UpgradeMaskType &activation, UpgradeMaskType &conflicting) const = 0;
	virtual void performUpgradeFX() = 0;
};
class Rva00452460 : public Rva00452EDDPrimary<0x20>, public Rva00452460Iface
{
public:
	void getUpgradeActivationMasks(UpgradeMaskType &activation, UpgradeMaskType &conflicting) const;
	void performUpgradeFX();
};
void Rva00452460::getUpgradeActivationMasks(UpgradeMaskType &activation, UpgradeMaskType &conflicting) const
{
	((const Rva00452460Data *)m_moduleData)->m_upgradeMuxData.getUpgradeActivationMasks(activation, conflicting);
}
class Rva00460AAC : public Rva00452EDDPrimary<0x10>, public Rva00452460Iface
{
public:
	void getUpgradeActivationMasks(UpgradeMaskType &activation, UpgradeMaskType &conflicting) const;
	void performUpgradeFX();
};
void Rva00460AAC::getUpgradeActivationMasks(UpgradeMaskType &activation, UpgradeMaskType &conflicting) const
{
	((const Rva00452460Data *)m_moduleData)->m_upgradeMuxData.getUpgradeActivationMasks(activation, conflicting);
}
void Rva00460AAC::performUpgradeFX()
{
	((const Rva00452460Data *)m_moduleData)->m_upgradeMuxData.performUpgradeFX(m_object);
}
class Rva0045F46A : public Rva00452EDDPrimary<0x30>, public Rva00452460Iface
{
public:
	void getUpgradeActivationMasks(UpgradeMaskType &activation, UpgradeMaskType &conflicting) const;
	void performUpgradeFX();
};
void Rva0045F46A::performUpgradeFX()
{
	((const Rva0045F46AData *)m_moduleData)->m_upgradeMuxData.performUpgradeFX(m_object);
}

// 0x004839F9 (interface at +0x20): virtual slot 14 of the complete object
// when the third argument is 2, else slot 15 when the second is 2.
class Rva004839F9Primary
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void v14();
	virtual void v15();
	virtual void v16();
	virtual void v17();
private:
	char m_pad04[0x1C];
};
class Rva004839F9Iface
{
public:
	virtual void rva004839F9(Int a, Int b, Int c) = 0;
};
class Rva004839F9 : public Rva004839F9Primary, public Rva004839F9Iface
{
public:
	void rva004839F9(Int a, Int b, Int c);
};
void Rva004839F9::rva004839F9(Int, Int b, Int c)
{
	if (c == 2)
		v14();
	else if (b == 2)
		v15();
}

// 0x004ADBD7 (interface at +0x88): virtual slot 17 of the complete object
// while the module data's +0xCC flag is set.
struct Rva004ADBD7Data
{
	char m_pad00[0xCC];
	bool m_CC;
};
class Rva004ADBD7Iface
{
public:
	virtual void rva004ADBD7() = 0;
};
class Rva004ADBD7 : public Rva00452EDDPrimary<0x88>, public Rva004ADBD7Iface
{
public:
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void v14();
	virtual void v15();
	virtual void v16();
	virtual void v17();
	void rva004ADBD7();
};
void Rva004ADBD7::rva004ADBD7()
{
	if (((const Rva004ADBD7Data *)m_moduleData)->m_CC)
		v17();
}

// 0x004DF897 (UpdateModuleInterface at +0x10, slot 0 beside the rowed
// UpdateModule getDisabledTypesToProcess and wake slots): clears object
// status 8 through the rowed Object::setStatus and sleeps forever.
enum ObjectStatusTypes
{
	OBJECT_STATUS_8 = 8
};
enum UpdateSleepTime
{
	UPDATE_SLEEP_FOREVER = 0x3fffffff
};
class Object
{
public:
	void setStatus(ObjectStatusTypes status, bool set);
};
class Rva004DF897Iface
{
public:
	virtual UpdateSleepTime update() = 0;
};
class Rva004DF897 : public Rva00452EDDPrimary<0x10>, public Rva004DF897Iface
{
public:
	UpdateSleepTime update();
};
UpdateSleepTime Rva004DF897::update()
{
	m_object->setStatus(OBJECT_STATUS_8, false);
	return UPDATE_SLEEP_FOREVER;
}

// 0x005E1CF8 (interface at +0x08): the rowed 0x005E1C6F of the +0x10 object
// with the complete object (the argument is unused).
class Rva005E1C6F
{
public:
	void rva005E1C6F(void *owner);
};
class Rva005E1CF8Primary
{
public:
	virtual void primarySlot();
private:
	Int m_04;
};
class Rva005E1CF8Iface
{
public:
	virtual void rva005E1CF8(Int unused) = 0;
private:
	Int m_0C;
};
class Rva005E1CF8 : public Rva005E1CF8Primary, public Rva005E1CF8Iface
{
public:
	void rva005E1CF8(Int unused);
private:
	Rva005E1C6F *m_10;
};
void Rva005E1CF8::rva005E1CF8(Int)
{
	m_10->rva005E1C6F(this);
}

// 0x00497805: a module's loadPostProcess that only chains to the rowed
// UpdateModule::loadPostProcess (the slot after the scalar destructor in
// many module tables).
class UpdateModule
{
protected:
	virtual void loadPostProcess();
};
class Rva00497805 : public UpdateModule
{
protected:
	virtual void loadPostProcess();
};
void Rva00497805::loadPostProcess()
{
	UpdateModule::loadPostProcess();
}
