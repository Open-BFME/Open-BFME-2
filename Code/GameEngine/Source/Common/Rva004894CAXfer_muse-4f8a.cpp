// cl: /MD
// ?xfer@Rva004894CA@@MAEXPAVXfer@@@Z @0x004894CA 43B
// Honest State-area xfer: Version1 via rowed 0x000053EE then raw 4B at +0x20
// via Xfer slot 0x24 (XferRawBytes) then Snapshot via slot 0x30
// (operator==(Snapshot&) under MSVC71 reverse-overload layout: slot 12 is the
// third-from-last operator==). Retail pushes the dword at +0x24 (a Snapshot*
// whose pointee is passed as Snapshot&), hence a pointer field. Sibling of
// 0x0048947D/0x004894A9. Xfer declaration copied from RainOfFireUpdateXfer.cpp.

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

class __declspec(novtable) Rva004894CA
{
public:
	Rva004894CA();
	virtual ~Rva004894CA();

protected:
	virtual void xfer(Xfer *xfer);

private:
	unsigned char m_pad[0x1C];
	int m_20;
	Snapshot *m_24;
};

void Rva004894CA::xfer(Xfer *xfer)
{
	xfer->Version1();
	xfer->XferRawBytes(&m_20, 4);
	*xfer == *m_24;
}
