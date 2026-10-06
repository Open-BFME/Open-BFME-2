// cl: /DNDEBUG /MD
//
// ?xfer@DetachableRiderBody@@MAEXPAVXfer@@@Z, retail 0x004C1D0B, 62 bytes.
// Slot 3 of the vftable 0x00C5C0B8 whose slot-2 name getter returns
// "DetachableRiderBody" (the rowed dtor 0x004C1BAB installs it).
// Version(1,2), the rowed ActiveBody::xfer 0x004BF1E8, then from version 2
// the upgrade mux on the +0x100 subobject (rowed upgradeMuxXfer 0x004CE397).

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

class Xfer::Version
{
public:
	Version(unsigned char current, unsigned char minimum)
		: m_current(current), m_minimum(minimum) {}

	unsigned char m_current;
	unsigned char m_minimum;
};

class ActiveBody
{
protected:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void xfer(Xfer *xfer);
	char m_unrecovered04[0x100 - 0x04];
};

class DetachableRiderBody;

class UpgradeMux
{
	friend class DetachableRiderBody;
protected:
	virtual void upgradeMuxXfer(Xfer *xfer);
private:
	bool m_upgradeExecuted;
};

class DetachableRiderBody : public ActiveBody
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	UpgradeMux m_100;
};

// ?xfer@DetachableRiderBody@@MAEXPAVXfer@@@Z @0x004C1D0B
void DetachableRiderBody::xfer(Xfer *xfer)
{
	Xfer::Version version(1, 2);
	*xfer == version;

	ActiveBody::xfer(xfer);

	if (version.m_minimum >= 2)
		m_100.UpgradeMux::upgradeMuxXfer(xfer);
}
