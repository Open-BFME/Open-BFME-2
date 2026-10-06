// cl: /DNDEBUG /MD
//
// ?xfer@DamageFilteredCreateObjectDie@@MAEXPAVXfer@@@Z, retail 0x00485FE3, 50 bytes.
// Slot 3 (offset 0x0C) of vtable 0x0084AB54 (class of ??0DamageFilteredCreateObjectDie
// rowed at 0x00485F87 in DamageFilteredCreateObjectDieCtor.cpp).
//
// Version1 via rowed 0x000053EE, base DieModule xfer via rowed 0x004CE56D
// (?xfer@Rva004CE56D@@QAEXPAVXfer@@@Z), then uint at +0x18 via Xfer slot
// 0x78 plus int at +0x1C via Xfer slot 0x7C. Layout is the rowed ctor class
// (DieModule base 0x14 plus +0x14 member giving +0x18 start; ctor zeroes
// +0x18 and sets +0x1C to -1). Recipe is the ClickReactionBehaviorXfer
// slot-3 pattern.

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

class Rva004CE56D
{
public:
	virtual void baseAnchor();
	void xfer(Xfer *xfer);

private:
	unsigned char m_pad[0x14 - 4];
};

class DamageFilteredCreateObjectDie : public Rva004CE56D
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	int m_14;
	unsigned int m_18;
	int m_1C;
};

void DamageFilteredCreateObjectDie::xfer(Xfer *xfer)
{
	xfer->Version1();
	Rva004CE56D::xfer(xfer);
	*xfer == m_18;
	*xfer == m_1C;
}
