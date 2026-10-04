// cl: /O1 /DNDEBUG /MD
// ?xfer@Rva0040C351@@MAEXPAVXfer@@@Z @0x0040C4FE 136B
// Slot 3 of vtable 0x0083944C (class of ctor 0x0040C351). Version 1 1 via
// Xfer slot 0x28 then base CarryoverUnit xfer 0x0037DE79 then bool at +0xC5
// via slot 0x90 plus int at +0xB4 via Get 0x004E075F plus int at +0xB8 via
// LivingWorldArmyID 0x00318D1E plus bool at +0xC4 via slot 0x90 plus int at
// +0xBC via Get plus int at +0xC0 via Parse 0x004E12D7. Layout from ctor TU.
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
class CarryoverUnit
{
protected:
	virtual void xfer(Xfer *xfer);
private:
	char m_pad[0xAC - 4];
};
class Rva004E075FObj;
int Rva004E075FGet(Rva004E075FObj *o, int a);
void XferLivingWorldArmyID(Xfer *xfer, int *value);
void __cdecl Rva004E12D7Parse(void *ini, void *dest);
class Rva0040C351 : public CarryoverUnit
{
protected:
	virtual void xfer(Xfer *xfer);
private:
	char m_ac[8];
	int m_b4;
	int m_b8;
	int m_bc;
	int m_c0;
	bool m_c4;
	bool m_c5;
};
void Rva0040C351::xfer(Xfer *xfer)
{
	Xfer::Version version(1, 1);
	*xfer == version;
	CarryoverUnit::xfer(xfer);
	*xfer == m_c5;
	Rva004E075FGet((Rva004E075FObj *)xfer, (int)&m_b4);
	XferLivingWorldArmyID(xfer, &m_b8);
	*xfer == m_c4;
	Rva004E075FGet((Rva004E075FObj *)xfer, (int)&m_bc);
	Rva004E12D7Parse(xfer, &m_c0);
}
