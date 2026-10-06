// cl: /MD
//
// ?xfer@ObjectCreationUpgrade@@MAEXPAVXfer@@@Z @0x004B421D (62B).
// Slot 3 (offset 0x0C) of vtable 0x0085762C (class of ??1ObjectCreationUpgrade
// rowed at 0x004B3F90 in ObjectCreationUpgradeDtor.cpp).
//
// ObjectCreationUpgrade xfer: Version1 via rowed 0x53EE, then bool at +0x2C
// via Xfer slot 0x90, then uint at +0x28 via Xfer slot 0x78, then base
// UpdateModule xfer via rowed 0x44DF9F, then UpgradeMux base at +0 via rowed
// upgradeMuxXfer 0x4CE397 (this-8). No IsLightCRC early-out. Layout is the
// rowed ctor class (UpgradeMux base 8 plus UpdateModule base 0x20 plus uint
// at +0x28 plus bool at +0x2C) from ObjectCreationUpgradeCtor.cpp. Donor is ZH
// ObjectCreationUpgrade.cpp:117 version-plus-base; BFME2 adds the two members
// and the UpgradeMux split. Recipe is the slot-3 xfer pattern.

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

class UpdateModule
{
public:
	virtual ~UpdateModule();
	virtual void xfer(Xfer *xfer);

private:
	unsigned char m_pad[0x1C];
};

class UpgradeMux
{
protected:
	virtual void upgradeMuxXfer(Xfer *xfer);

private:
	bool m_upgradeExecuted;
};

class ObjectCreationUpgrade : public UpgradeMux, public UpdateModule
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	unsigned int m_status;
	bool m_flag;
};

void ObjectCreationUpgrade::xfer(Xfer *xfer)
{
	xfer->Version1();
	*xfer == m_flag;
	*xfer == m_status;
	UpdateModule::xfer(xfer);
	UpgradeMux::upgradeMuxXfer(xfer);
}
