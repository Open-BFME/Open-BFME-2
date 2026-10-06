// cl: /MD
//
// ?xfer@UpgradeModule@@MAEXPAVXfer@@@Z, retail 0x004CE3F9, 37 bytes.
// Slot 3 (offset 0x0C) of vtable 0x00842768 (class of rowed UpgradeModule
// ctor 0x00460AEC). Version1 via rowed 0x000053EE then base BehaviorModule
// xfer via rowed 0x004C9C7D then UpgradeMux member at +0x10 via just-rowed
// 0x004CE397. Donor ZH UpgradeModule.cpp xfer verbatim (version plus base
// plus upgradeMuxXfer). Called by 6 derived xfers.

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

class UpgradeModule;

class BehaviorModule
{
public:
	virtual ~BehaviorModule();
	void xfer(Xfer *xfer);

private:
	unsigned char m_pad[0xC];
};

class UpgradeMux
{
	friend class UpgradeModule;
protected:
	virtual void upgradeMuxXfer(Xfer *xfer);

private:
	bool m_upgradeExecuted;
};

class UpgradeModule : public BehaviorModule
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	UpgradeMux m_mux10;
};

void UpgradeModule::xfer(Xfer *xfer)
{
	xfer->Version1();
	BehaviorModule::xfer(xfer);
	m_mux10.UpgradeMux::upgradeMuxXfer(xfer);
}
