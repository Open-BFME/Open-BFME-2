// cl: /MD
// ?xfer@Rva003429B9@@MAEXPAVXfer@@@Z @0x003406A5 117B: slot 3 xfer of vtable 0x008126C0 (class of Rva003429B9 ctor 0x003429B9). Version(1 3) then base Rva0033FF2B xfer then IsLightCRC early-out then Coord at +0x4C via slot 0x60 plus uint at +0x58 via slot 0x78 plus bool at +0x5C if min>=2 plus bool at +0x5D if min>=3. Evidence: callees rowed (base 0x0033FF76) layout from Rva003429B9Ctor floats 0x4C 0x50 0x54 as Coord plus int 0x58 plus bools 0x5C 0x5D.
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
	unsigned int m_40;
	unsigned int m_44;
	bool m_48;
	bool m_49;
	char m_pad4A;
	bool m_4B;
};

class Rva003429B9 : public Rva0033FF2B
{
protected:
	virtual void xfer(Xfer *xfer);
private:
	Coord3DBase m_4C;
	unsigned int m_58;
	bool m_5C;
	bool m_5D;
};

void Rva003429B9::xfer(Xfer *xfer)
{
	Xfer::Version version(1, 3);
	*xfer == version;
	Rva0033FF2B::xfer(xfer);
	if (xfer->IsLightCRC())
		return;
	*xfer == m_4C;
	*xfer == m_58;
	if (version.m_minimum >= 2) {
		*xfer == m_5C;
	}
	if (version.m_minimum >= 3) {
		*xfer == m_5D;
	}
}
