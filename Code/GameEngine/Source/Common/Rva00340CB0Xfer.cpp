// cl: /MD
// ?xfer@Rva00340D1F@@MAEXPAVXfer@@@Z @ 0x00340CB0 111B: slot 3 xfer of vtable 0x00810E?? family.
// Version(1,2) via Xfer slot 0x28 then base Rva0033FF2B xfer via rowed 0x0033FF76,
// IsLightCRC via slot 0x10, int at +0x4C via slot 0x7C, bools at +0x50/+0x51 via
// slot 0x90, version>=2 int at +0x54 via slot 0x7C. Evidence: rowed base xfer
// 0x0033FF76 plus Xfer slots 0x28/0x10/0x7C/0x90 plus caller 0x0034253E.
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

typedef unsigned int AudioHandle;

struct Coord3DBase
{
	float x;
	float y;
	float z;
};

class Rva0049B47C
{
public:
	virtual ~Rva0049B47C();

private:
	char m_pad04[8];
};

class Rva0033FF2B : public Rva0049B47C
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	char m_pad0C[0x20 - 0x0C];
	Coord3DBase m_20;
	float m_2C;
	int m_30;
	Coord3DBase m_34;
	AudioHandle m_40;
	unsigned int m_44;
	bool m_48;
	bool m_49;
	char m_pad4A;
	bool m_4B;
};

class Rva00340D1F : public Rva0033FF2B
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	int m_4C;
	bool m_50;
	bool m_51;
	char m_pad52[2];
	int m_54;
};

void Rva00340D1F::xfer(Xfer *xfer)
{
	Xfer::Version version(1, 2);
	*xfer == version;
	Rva0033FF2B::xfer(xfer);
	if (xfer->IsLightCRC())
		return;
	*xfer == m_4C;
	*xfer == m_50;
	*xfer == m_51;
	if (version.m_minimum >= 2)
		*xfer == m_54;
}
