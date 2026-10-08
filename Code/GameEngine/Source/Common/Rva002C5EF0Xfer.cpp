// cl: /MD
// ?rva002C5EF0@Rva002C5EF0@@QAEXPAVXfer@@@Z @0x002C5EF0 117B. Xfer-style persist with Version(1 3) then uint at +0 m_0, Coord at +4, uint at +0x10, float at +0x14, global g_00DFEFC8, float at +0x18, version-gated uint at +0x1c. Evidence: unlock lane, slots 0x28 Version 0x78 uint 0x60 Coord 0x70 float match reversed-overload layout, callers 0x002C6429 0x002C64A4 in 0x002C63A1, neighbours DispDwordLeaFieldGetters/Disp8NullAdjustGetters.
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
	unsigned char m_current;
	unsigned char m_minimum;
};

class Coord3DBase
{
public:
	float x;
	float y;
	float z;
};

extern unsigned int g_00DFEFC8;
// g_00DFEFC8: matched references place it at VA 0xdfefc8 (zero-filled .bss).
unsigned int g_00DFEFC8;

class Rva002C5EF0
{
public:
	void rva002C5EF0(Xfer *xfer);
private:
	unsigned int m_0;
	Coord3DBase m_4;
	unsigned int m_10;
	float m_14;
	float m_18;
	unsigned int m_1c;
};

void Rva002C5EF0::rva002C5EF0(Xfer *xfer)
{
	Xfer::Version version;
	version.m_current = 1;
	version.m_minimum = 3;
	*xfer == version;
	*xfer == m_0;
	*xfer == m_4;
	*xfer == m_10;
	*xfer == m_14;
	*xfer == g_00DFEFC8;
	*xfer == m_18;
	if (version.m_minimum >= 3)
		*xfer == m_1c;
}

// Complete native2A8808..2A8810 follows RET2A8807 and clears the same
// existing unsigned global used by the verified serializer above. The
// original function spelling and higher-level reset role remain unknown.
void Rva002A8808Clear()
{
    g_00DFEFC8=0;
}
