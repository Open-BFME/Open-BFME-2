// cl: /MD
// ?xfer@Rva00340D70@@MAEXPAVXfer@@@Z @ 0x00340D70 201B: slot 3 xfer of vtable 0x008121E8.
// True class per vtable is Rva00340D1F but that name is taken by misnamed 111B row at
// 0x00340CB0 (no vtable proof); honest address name keeps bytes and links. Fix that
// row in its own commit to free the real name.
// Version(1,3) via Xfer slot 0x28 then base Rva0033FF2B xfer via rowed 0x0033FF76,
// IsLightCRC via slot 0x10, int at +0x4C via slot 0x7C, bools at +0x54/+0x55/+0x56
// via slot 0x90, version>1 int at +0x50 via slot 0x7C plus CommandSource at +0x58
// via rowed XferCommandSourceType 0x00305C02 plus Snapshot ptr at +0x5C via slot
// 0x30 plus float at +0x60 via slot 0x70 plus bool at +0x64 via slot 0x90,
// version>2 bool at +0x57 via slot 0x90. Evidence: vtable 0x008121E8 slot 3.
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

void XferCommandSourceType(Xfer *xfer, int *value);

class Rva0049B47C
{
public:
	virtual ~Rva0049B47C();

private:
	char m_pad04[8];
};

class Rva0033FF2B : public Rva0049B47C
{
public:
	virtual ~Rva0033FF2B();

protected:
	virtual void xfer(Xfer *xfer);

private:
	char m_pad0C[0x40 - 0x0C];
	unsigned int m_handle40;
};

class Rva00340D70 : public Rva0033FF2B
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	char m_pad44[0x4C - 0x44];
	int m_4C;
	int m_50;
	bool m_54;
	bool m_55;
	bool m_56;
	bool m_57;
	int m_58;
	Snapshot *m_ptr5C;
	float m_60;
	bool m_64;
};

void Rva00340D70::xfer(Xfer *xfer)
{
	Xfer::Version version(1, 3);
	*xfer == version;
	Rva0033FF2B::xfer(xfer);
	if (xfer->IsLightCRC())
		return;
	*xfer == m_4C;
	*xfer == m_54;
	*xfer == m_55;
	*xfer == m_56;
	if (version.m_minimum > 1) {
		*xfer == m_50;
		XferCommandSourceType(xfer, &m_58);
		if (m_ptr5C != 0)
			*xfer == *m_ptr5C;
		*xfer == m_60;
		*xfer == m_64;
	}
	if (version.m_minimum > 2)
		*xfer == m_57;
}
