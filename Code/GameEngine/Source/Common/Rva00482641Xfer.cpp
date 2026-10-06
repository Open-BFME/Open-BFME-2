// cl: /DNDEBUG /MD /GX
//
// ?xfer@Rva00482641@@MAEXPAVXfer@@@Z, retail 0x00482641, 361 bytes.
// Virtual slot 3 of vtable 0x0084965C (primary of FireWeaponWhenDamagedBehavior
// ctor 0x00482803 and dtor 0x00482551); true FireWeaponWhenDamagedBehavior xfer
// with eight Weapon slots at +0x2C..0x48 via base UpdateModule xfer 0x0044DF9F
// plus UpgradeMux 0x004CE397 plus Version1 plus IsLightCRC early-out. Donor:
// BFME1 FireWeaponWhenDamagedBehaviorXfer.cpp (same eight-weapon order).
// Honest Rva name: real name ?xfer@FireWeaponWhenDamagedBehavior@@MAEXPAVXfer@@@Z
// already rowed at 0x004A4EE9 for vtable 0x00852868 (Rva004A4C19 class diverging
// from donor); this body matches the donor and the rowed ctor/dtor layout.

class AsciiString;
class UnicodeString;
class PooledString;
struct XferUnknown11;
class Coord3DBase;
class ICoord3D;
class Region3D;
class IRegion3D;
class Coord2D;
class ICoord2D;
class Region2D;
class IRegion2D;
class RealRange;
class RGBColor;
class RGBAColorReal;
class RGBAColorInt;
class Snapshot;
class Thing;
class ModuleData;
class Object;

class Xfer
{
public:
	class Version;

	Xfer();
	virtual ~Xfer();

	void Version1();

	virtual bool IsLoading() const;
	virtual bool IsStoring() const;
	virtual bool IsCRC() const;
	virtual bool IsLightCRC() const;

	virtual void v5() = 0;
	virtual void v6() = 0;
	virtual void v7() = 0;

	virtual void SkipBadBlock(Snapshot &snapshot, unsigned int size);
	virtual Xfer &XferRawBytes(void *data, unsigned int size);
	virtual Xfer &operator==(bool &value);
	virtual Xfer &operator==(char &value);
	virtual Xfer &operator==(unsigned char &value);
	virtual Xfer &operator==(short &value);
	virtual Xfer &operator==(unsigned short &value);
	virtual Xfer &operator==(int &value);
	virtual Xfer &operator==(unsigned int &value);
	virtual Xfer &operator==(__int64 &value);
	virtual Xfer &operator==(float &value);
	virtual Xfer &operator==(AsciiString &value);
	virtual Xfer &operator==(UnicodeString &value);
	virtual Xfer &operator==(PooledString &value);
	virtual Xfer &operator==(Coord3DBase &value);
	virtual Xfer &operator==(ICoord3D &value);
	virtual Xfer &operator==(Region3D &value);
	virtual Xfer &operator==(IRegion3D &value);
	virtual Xfer &operator==(Coord2D &value);
	virtual Xfer &operator==(ICoord2D &value);
	virtual Xfer &operator==(Region2D &value);
	virtual Xfer &operator==(IRegion2D &value);
	virtual Xfer &operator==(RealRange &value);
	virtual Xfer &operator==(RGBColor &value);
	virtual Xfer &operator==(RGBAColorReal &value);
	virtual Xfer &operator==(RGBAColorInt &value);
	virtual Xfer &operator==(Snapshot &value);
	virtual Xfer &operator==(XferUnknown11 &value) = 0;
	virtual Xfer &operator==(Version &value);

	virtual Xfer &XferEnum(const char *name, void *data, unsigned int size);

protected:
	virtual void XferData(unsigned int type, void *data, unsigned int size) = 0;
};

class Snapshot
{
public:
	virtual void snapshotSlot();
};

class Weapon : public Snapshot
{
};

class Thing;
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
public:
	BehaviorModule(Thing *thing, const ModuleData *moduleData);
};

class UpdateModuleInterface
{
public:
	virtual void update();
};

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);
	virtual ~UpdateModule();
	void xfer(Xfer *xfer);

private:
	unsigned m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_bfmeReserved;
};

class UpgradeMux
{
public:
	UpgradeMux();
	void giveSelfUpgrade();

protected:
	virtual bool isUpgradeActive() = 0;
	virtual void upgradeMuxXfer(Xfer *xfer);

private:
	bool m_upgradeExecuted;
};

class DamageModuleInterface
{
public:
	virtual void damageSlot();
};

class Rva00482641 : public UpdateModule, public UpgradeMux, public DamageModuleInterface
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	Weapon *m_reactionWeaponPristine; // +0x2C
	Weapon *m_reactionWeaponDamaged; // +0x30
	Weapon *m_reactionWeaponReallyDamaged; // +0x34
	Weapon *m_reactionWeaponRubble; // +0x38
	Weapon *m_continuousWeaponPristine; // +0x3C
	Weapon *m_continuousWeaponDamaged; // +0x40
	Weapon *m_continuousWeaponReallyDamaged; // +0x44
	Weapon *m_continuousWeaponRubble; // +0x48
};

typedef bool Bool;

void Rva00482641::xfer(Xfer *xfer)
{
	UpdateModule::xfer(xfer);
	UpgradeMux::upgradeMuxXfer(xfer);
	if (xfer->IsLightCRC())
		return;

	xfer->Version1();

	Bool weaponPresent = m_reactionWeaponPristine != 0;
	*xfer == weaponPresent;
	if (weaponPresent)
		*xfer == *m_reactionWeaponPristine;

	weaponPresent = m_reactionWeaponDamaged != 0;
	*xfer == weaponPresent;
	if (weaponPresent)
		*xfer == *m_reactionWeaponDamaged;

	weaponPresent = m_reactionWeaponReallyDamaged != 0;
	*xfer == weaponPresent;
	if (weaponPresent)
		*xfer == *m_reactionWeaponReallyDamaged;

	weaponPresent = m_reactionWeaponRubble != 0;
	*xfer == weaponPresent;
	if (weaponPresent)
		*xfer == *m_reactionWeaponRubble;

	weaponPresent = m_continuousWeaponPristine != 0;
	*xfer == weaponPresent;
	if (weaponPresent)
		*xfer == *m_continuousWeaponPristine;

	weaponPresent = m_continuousWeaponDamaged != 0;
	*xfer == weaponPresent;
	if (weaponPresent)
		*xfer == *m_continuousWeaponDamaged;

	weaponPresent = m_continuousWeaponReallyDamaged != 0;
	*xfer == weaponPresent;
	if (weaponPresent)
		*xfer == *m_continuousWeaponReallyDamaged;

	weaponPresent = m_continuousWeaponRubble != 0;
	*xfer == weaponPresent;
	if (weaponPresent)
		*xfer == *m_continuousWeaponRubble;
}
