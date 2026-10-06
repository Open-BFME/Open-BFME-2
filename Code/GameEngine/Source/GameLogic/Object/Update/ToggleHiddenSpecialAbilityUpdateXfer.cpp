// cl: /DNDEBUG /MD
// ?xfer@ToggleHiddenSpecialAbilityUpdate@@MAEXPAVXfer@@@Z @0x004AE25C 42B slot 3.
// Retail runs Xfer::Version1, xfers uint at +0x88 via Xfer reverse-overload
// slot 0x78, then base SpecialAbilityUpdate::xfer. Evidence: vslot lane
// slot 3 of 0x008552D8; donor ToggleHiddenSpecialAbilityUpdate.cpp m_hidden;
// base size 0x88 from SpecialAbilityUpdateXfer TU and ctor TU m_88.

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

class SpecialAbilityUpdate
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	unsigned char m_pad[0x88 - 4];
};

class ToggleHiddenSpecialAbilityUpdate : public SpecialAbilityUpdate
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	unsigned int m_88;
};

void ToggleHiddenSpecialAbilityUpdate::xfer(Xfer *xfer)
{
	xfer->Version1();
	*xfer == m_88;
	SpecialAbilityUpdate::xfer(xfer);
}
