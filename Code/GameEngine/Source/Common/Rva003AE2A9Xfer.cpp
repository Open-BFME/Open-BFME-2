// cl: /MD
// ?xfer@Rva003AE2A9@@MAEXPAVXfer@@@Z @0x0056454F 79B.
// Slot 3 (offset 0xC) of vtable 0x0081CAA4, the class of the rowed copy
// ctor ??0Rva003AE2A9@@QAE@ABV0@@Z: its xfer. Version(1,2) local via Xfer
// slot 0x28 (==(Version&)), subobject tail at this+0x10 through the rowed
// 0x00564522, bool at +0xC via slot 0x90 (==(bool&)), and the
// version-minimum-gated bool at +0x20 via slot 0x90. Caller at 0x003ACB6A.
// Xfer declaration copied verbatim from PoisonedBehaviorXfer.cpp (its
// reversed ==-overload layout is what puts Version at 0x28 and bool at
// 0x90); Xfer::Version 2-byte idiom from StancesBehaviorXfer.cpp.

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

class Rva00564522
{
public:
	void rva00564522(Xfer *xfer);
};

class Rva003AE2A9
{
protected:
	virtual void xfer(Xfer *xfer);
private:
	char m_pad4[8];
	bool m_boolC;
	char m_padD[0x13];
	bool m_bool20;
};

void Rva003AE2A9::xfer(Xfer *xfer)
{
	Xfer::Version version(1, 2);
	*xfer == version;
	((Rva00564522 *)((char *)this + 0x10))->rva00564522(xfer);
	*xfer == m_boolC;
	if (version.m_minimum >= 2)
		*xfer == m_bool20;
}
