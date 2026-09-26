// cl: /O1 /MD
// ?rva004B23C5@Rva004B237B@@QAEXPAVXfer@@@Z, retail 0x004B23C5, 147 bytes.
// Virtual slot 3 (offset 0xC) of vtable 0x00856948 (VA 0x00C56948), class of
// ??1Rva004B237B@@UAE@XZ in Rva0024A797Derived.cpp. UpdateModule xfer via
// rowed 0x0044DF9F with Version(1,1) via Xfer slot 0x28 then uint fields at
// +0x20/+0x24/+0x28 via slot 0x78 and bool fields at +0x2C/+0x2D/+0x2E/+0x2F/
// +0x30 via slot 0x90. Xfer spelling copied from FoundationAIUpdateXfer.cpp.

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
	void xfer( Xfer *xfer );

private:
	unsigned char m_pad[ 0x20 ];
};

class Rva004B237B : public UpdateModule
{
public:
	void rva004B23C5( Xfer *xfer );

private:
	unsigned int m_20;
	unsigned int m_24;
	unsigned int m_28;
	bool m_2C;
	bool m_2D;
	bool m_2E;
	bool m_2F;
	bool m_30;
};

void Rva004B237B::rva004B23C5( Xfer *xfer )
{
	Xfer::Version version( 1, 1 );
	*xfer == version;
	UpdateModule::xfer( xfer );
	*xfer == m_20;
	*xfer == m_2C;
	*xfer == m_24;
	*xfer == m_2F;
	*xfer == m_2D;
	*xfer == m_30;
	*xfer == m_28;
	*xfer == m_2E;
}
