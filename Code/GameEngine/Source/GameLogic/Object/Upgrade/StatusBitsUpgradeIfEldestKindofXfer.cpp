// cl: /DNDEBUG /MD
//
// ?xfer@StatusBitsUpgradeIfEldestKindof@@MAEXPAVXfer@@@Z, retail 0x004B4B7C, 37 bytes.
// Slot 3 of the vftable 0x00C57ADC whose slot-2 name getter returns
// "StatusBitsUpgradeIfEldestKindof" (installed by 0x004B49E2). Version1, the
// StatusBitsUpgrade::xfer (pinned at the ICF-shared upgrade xfer 0x004B8710),
// then the frame cache at +0x1C through the rowed Rva00485BB8::xfer.

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

class Rva00485BB8
{
public:
	void xfer(Xfer *xfer);

private:
	unsigned int m_00;
};

class StatusBitsUpgrade
{
protected:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void xfer(Xfer *xfer);
	char m_unrecovered04[0x1C - 0x04];
};

class StatusBitsUpgradeIfEldestKindof : public StatusBitsUpgrade
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	Rva00485BB8 m_1C;
};

// ?xfer@StatusBitsUpgradeIfEldestKindof@@MAEXPAVXfer@@@Z @0x004B4B7C
void StatusBitsUpgradeIfEldestKindof::xfer(Xfer *xfer)
{
	xfer->Version1();
	StatusBitsUpgrade::xfer(xfer);
	m_1C.xfer(xfer);
}
