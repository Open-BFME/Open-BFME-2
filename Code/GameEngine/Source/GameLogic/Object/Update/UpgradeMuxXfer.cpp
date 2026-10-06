// cl: /MD
//
// ?upgradeMuxXfer@UpgradeMux@@MAEXPAVXfer@@@Z, retail 0x004CE397, 34 bytes.
// Virtual slot 16 (offset 0x40) of UpgradeMux member vtable 0x0083FC88 (class
// of rowed AutoHealBehavior ctor 0x00452592, member at +0x20) and same body
// at slot 16 of ReplenishUnits/AttributeModifierAura/RadiateFear/
// ObjectCreation/AudioLoop/DetachableRider member vtables plus slot 28/32 of
// UpgradeModule-primary vtables (StealthUpgrade etc). Version1 via rowed
// 0x000053EE then bool at +0x4 via Xfer slot 0x90. Called this+0x20 by 12
// derived xfers (0x0045242B etc). Donor ZH UpgradeModule.h protected virtual
// UpgradeMux::upgradeMuxXfer plus BFME1 FireWeaponWhenDamagedBehaviorXfer.

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

class UpgradeMux
{
protected:
	virtual void upgradeMuxXfer(Xfer *xfer);

private:
	bool m_upgradeExecuted; // +4 (vptr at +0)
};

void UpgradeMux::upgradeMuxXfer(Xfer *xfer)
{
	xfer->Version1();
	*xfer == m_upgradeExecuted;
}
