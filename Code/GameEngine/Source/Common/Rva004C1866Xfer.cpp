// cl: /MD
//
// ?xfer@Rva004C1866@@MAEXPAVXfer@@@Z, retail 0x004C1974, 104 bytes.
// Slot 3 (offset 0x0C) of vtable 0x0085BE38 (class of ??1Rva004C1866@@UAE@XZ
// rowed at 0x004C1866 in Rva004C131BDerived.cpp).
//
// Retail: Version1 via rowed 0x000053EE, then bool at +0x100 via Xfer slot
// 0x90, float at +0x104 via slot 0x70, bool at +0x108 via slot 0x90,
// uint at +0x10C and uint at +0x110 via slot 0x78, then base
// ImmortalBody::xfer via rowed 0x004C20BA. No IsLightCRC in retail.
// Layout is ImmortalBody base 0x100 plus 5 members (bool/float/bool/uint/uint).
// Shape follows Rva004B4CDFXfer/BodyModuleXfer slot-3 pattern.

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

class ImmortalBody
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	char m_pad04[0x100 - 4];
};

class Rva004C1866 : public ImmortalBody
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	bool m_b100; // +0x100
	float m_f104; // +0x104
	bool m_b108; // +0x108
	unsigned int m_u10C; // +0x10C
	unsigned int m_u110; // +0x110
};

void Rva004C1866::xfer(Xfer *xfer)
{
	xfer->Version1();
	*xfer == m_b100;
	*xfer == m_f104;
	*xfer == m_b108;
	*xfer == m_u10C;
	*xfer == m_u110;
	ImmortalBody::xfer(xfer);
}
