// cl: /MD
// ?xfer@Rva003AE0AF@@MAEXPAVXfer@@@Z @0x00563F88 89B
// Slot 3 (offset 0xC) of vtable 0x0081CA04 (class of ??0Rva003AE0AF copy 0x003AE0AF).
// Chain after landing 0x003B0E38. IsLightCRC early-out via Xfer slot 0x10,
// Version(1,2) via Xfer slot 0x28, subobject at +0x10 via rowed 0x003B0E38,
// bool at +0xC and version-gated bool at +0x1C via Xfer slot 0x90.
// Layout from retail offsets; Xfer decl verbatim from PoisonedBehaviorXfer.cpp.
// Precedent: Rva00563ED1Xfer.cpp (/O1 /MD) and PoisonedBehaviorXfer.cpp slot-3 recipe.
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
class DamageInfo;

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
	Version(unsigned char major, unsigned char minor) : m_major(major), m_minor(minor) {}
	unsigned char m_major;
	unsigned char m_minor;
};

class Rva003B0E38
{
public:
	void rva003B0E38(Xfer *xfer);
private:
	int m_pad;
	unsigned int m_val;
};

class Rva003AE0AF
{
public:
	virtual ~Rva003AE0AF();
	virtual void crc(Xfer *xfer);
	virtual void loadPostProcess();
protected:
	virtual void xfer(Xfer *xfer);
private:
	char m_pad4[8];
	bool m_0c;
	char m_padD[3];
	Rva003B0E38 m_10;
	char m_pad18[4];
	bool m_1c;
};

void Rva003AE0AF::xfer(Xfer *xfer)
{
	if (xfer->IsLightCRC())
		return;
	Xfer::Version version(1, 2);
	*xfer == version;
	m_10.rva003B0E38(xfer);
	*xfer == m_0c;
	if (version.m_minor >= 2)
		*xfer == m_1c;
}
