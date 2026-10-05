// cl: /O1 /MD
//
// ?xfer@Rva0055B3D9@@UAEXPAVXfer@@@Z @0x0055B3D9 (62B).
// Slot-3 xfer: Version1 plus Rva0055B367 at +0xC plus two floats at +0x50
// +0x54 via slot 0x70 plus int at +0x58 via slot 0x7C. Abuts 0x0055B39C.
// Evidence: vtable slot 3 of 0x0081C904/0x0081D11C, rowed callees 0x53EE
// 0x0055B367, caller 0x003AC939. Xfer decl verbatim from Rva0055B367Xfer.
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
	virtual void SkipBadBlock(class Snapshot &snapshot, unsigned int size);
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

struct Rva0055B367Pair
{
	float f;
	unsigned int u;
};

class Rva0055B367
{
public:
	void rva0055B367(Xfer *xfer);
private:
	char m_pad[4];
	Rva0055B367Pair m_pairs[8];
};

class Rva0055B3D9
{
public:
	virtual void xfer(Xfer *xfer);
private:
	char m_pad0[0xC - 4];
	Rva0055B367 m_0C;
	float m_50;
	float m_54;
	int m_58;
};

void Rva0055B3D9::xfer(Xfer *xfer)
{
	xfer->Version1();
	m_0C.rva0055B367(xfer);
	*xfer == m_50;
	*xfer == m_54;
	*xfer == m_58;
}
