// cl: /Ireference/shims/bfme2_ascii /MD
//
// ?xfer@GeometryUpgrade@@MAEXPAVXfer@@@Z, retail 0x004B6C02, 55 bytes.
// Virtual slot 3 (offset 0x0C) of vtable 0x008589C0 (class of rowed ctor
// ??0GeometryUpgrade@@QAE@PAVThing@@PBVModuleData@@@Z in
// GeometryUpgradeCtor.cpp): Version(1,1) via Xfer slot 0x28 then AsciiString
// upgrade-name at +0x1C via Xfer slot 0x6C then base UpgradeModule xfer via
// rowed 0x004CE3F9. Layout is the rowed 0x20-byte class (UpgradeModule base
// 0x1C plus string at +0x1C, cf. rowed dtor 0x004B6C55 and rowed
// friend_newModuleInstance 0x0025060A size 0x20). Identity is slot 3 plus the
// UpgradeModule base call; donor is BFME1 StatusBitsUpgrade/ModelCondition
// xfer shape (Version plus base) plus the string before base that retail
// shows here.

#include "ascii_string.h"
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

class UpgradeModule
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	unsigned char m_pad[0x1C - 4];
};

class GeometryUpgrade : public UpgradeModule
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	AsciiString m_upgradeName; // +0x1C
};

void GeometryUpgrade::xfer(Xfer *xfer)
{
	Xfer::Version version(1, 1);
	*xfer == version;
	*xfer == m_upgradeName;
	UpgradeModule::xfer(xfer);
}
