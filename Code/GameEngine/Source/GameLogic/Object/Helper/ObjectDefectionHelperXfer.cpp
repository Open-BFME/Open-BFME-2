// cl: /DNDEBUG /MD
// ?xfer@ObjectDefectionHelper@@MAEXPAVXfer@@@Z, RVA 0x004DF76E, 84 bytes.
// Slot 3 of vtable 0x007FBD40 (class of ObjectDefectionHelper ctor 0x0028C955).
// Base Rva004DF81B xfer via rowed 0x004DF81B then IsLightCRC early-out via Xfer slot 0x10
// then Version1 via rowed 0x000053EE then uint at +0x20 plus uint at +0x24 via Xfer slot 0x78
// plus float at +0x28 via Xfer slot 0x70 plus bool at +0x2C via Xfer slot 0x90.
// Layout is the rowed 0x30-byte class from ObjectDefectionHelperCtor.cpp
// (ObjectHelper base 0x20 plus uint uint float bool). Recipe is the
// OneRingPenaltyUpdateXfer slot-3 pattern.
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

class Rva004DF81B
{
public:
	void xfer(Xfer *xfer);
};

class ObjectDefectionHelper
{
protected:
	virtual void xfer(Xfer *xfer);
private:
	char m_pad[0x20 - 4];
	unsigned int m_20;
	unsigned int m_24;
	float m_28;
	bool m_2C;
};

void ObjectDefectionHelper::xfer(Xfer *xfer)
{
	((Rva004DF81B *)this)->xfer(xfer);
	if (xfer->IsLightCRC())
		return;
	xfer->Version1();
	*xfer == m_20;
	*xfer == m_24;
	*xfer == m_28;
	*xfer == m_2C;
}
