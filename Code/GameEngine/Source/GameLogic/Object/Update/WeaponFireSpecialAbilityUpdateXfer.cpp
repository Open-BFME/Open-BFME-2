// cl: /MD
// ?xfer@WeaponFireSpecialAbilityUpdate@@MAEXPAVXfer@@@Z @ 0x004925E5 160B: slot 3.
// BFME1 donor WeaponFireSpecialAbilityUpdate_xfer.cpp reuse: Version(1,2) via
// slot 0x28 then base SpecialAbilityUpdate xfer via rowed 0x0044F996 then IsCRC
// via slot 0x0C then version>=2 bool weaponPresent at +0x88 via slot 0x90 then
// IsStoring via slot 0x08 then WeaponFireSpecialWeapon block via slots
// 0x14/0x30/0x18 else skip via 0x1C. Evidence: donor plus vtable 0x0084E090
// slot 3 plus string plus rowed base.
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

	virtual int beginBlock(const char *name);
	virtual void endBlock();
	virtual void skipBlock(const char *name);

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

class SpecialAbilityUpdate
{
public:
	virtual ~SpecialAbilityUpdate();

protected:
	virtual void xfer(Xfer *xfer);

private:
	char m_pad04[0x88 - 0x04];
};

class WeaponFireSpecialAbilityUpdate : public SpecialAbilityUpdate
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	Snapshot *m_weapon88;
};

void WeaponFireSpecialAbilityUpdate::xfer(Xfer *xfer)
{
	Xfer::Version version(1, 2);
	*xfer == version;
	SpecialAbilityUpdate::xfer(xfer);
	if (xfer->IsCRC())
		return;
	if (version.m_minimum < 2)
		return;
	bool weaponPresent = m_weapon88 != 0;
	*xfer == weaponPresent;
	if (!weaponPresent)
		return;
	if (xfer->IsStoring() || m_weapon88 != 0) {
		xfer->beginBlock("WeaponFireSpecialWeapon");
		*xfer == *m_weapon88;
		xfer->endBlock();
	} else {
		xfer->skipBlock("WeaponFireSpecialWeapon");
	}
}
