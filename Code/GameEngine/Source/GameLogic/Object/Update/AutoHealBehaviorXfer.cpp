// cl: /MD
//
// ?xfer@AutoHealBehavior@@MAEXPAVXfer@@@Z, retail 0x00452401, 95 bytes.
// Slot 3 (offset 0x0C) of vtable 0x0083FCDC (class of rowed AutoHealBehavior
// ctor 0x00452592). Version(1,2) via Xfer slot 0x28 then base UpdateModule
// xfer via rowed 0x0044DF9F then UpgradeMux member at +0x20 via rowed
// 0x004CE397 then uint at +0x2C via Xfer slot 0x78 plus bool at +0x30 via
// Xfer slot 0x90 plus version-gated uint at +0x34 via Xfer slot 0x78.
// Layout is UpdateModule base 0x20 plus UpgradeMux member plus neutral
// members (retail diverges from the BFME1 donor which xfers user/uint/bool).
// Recipe is the FireWeaponWhenDamagedBehaviorXfer version-gated slot-3 pattern.

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

class Xfer::Version
{
public:
	Version(unsigned char current, unsigned char minimum)
		: m_current(current), m_minimum(minimum) {}

	unsigned char m_current;
	unsigned char m_minimum;
};

class UpdateModule
{
public:
	virtual ~UpdateModule();
	void xfer(Xfer *xfer);

private:
	unsigned char m_pad[0x1C];
};

class AutoHealBehavior;

class UpgradeMux
{
	friend class AutoHealBehavior;
protected:
	virtual void upgradeMuxXfer(Xfer *xfer);

private:
	bool m_upgradeExecuted;
};

class AutoHealBehavior : public UpdateModule
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	UpgradeMux m_mux20;
	unsigned int m_28;
	unsigned int m_2C;
	bool m_stopped30;
	unsigned char m_pad31[3];
	unsigned int m_34;
};

void AutoHealBehavior::xfer(Xfer *xfer)
{
	Xfer::Version version(1, 2);
	*xfer == version;
	UpdateModule::xfer(xfer);
	m_mux20.UpgradeMux::upgradeMuxXfer(xfer);
	*xfer == m_2C;
	*xfer == m_stopped30;
	if (version.m_minimum >= 2) {
		*xfer == m_34;
	}
}
