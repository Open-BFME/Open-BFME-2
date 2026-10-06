// cl: /MD
//
// ?rva0055BB5C@Rva0055BB5C@@UAEXPAVXfer@@@Z, retail 0x0055BB5C, 82 bytes.
// Evidence: calls inner ?rva0055B96D rowed 0x0055B96D at +0x0C plus Version1
// rowed 0x000053EE plus IsLightCRC slot 0x10 plus RGB slots 0x3C at +0x94
// and +0xA0 plus string slot 0x7C at +0xAC; caller jmp 0x003AC9AA.
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

class RGBColorFull
{
public:
	float r;
	float g;
	float b;
};

class AsciiStringFull
{
public:
	AsciiStringFull() { m_text = 0; }
private:
	char *m_text;
};

class RGBColorKey
{
public:
	int m_color;
};

struct InnerElem
{
	RGBColorKey m_a;
	char m_pad[8];
	unsigned int m_b;
};

class Rva0055BC8B
{
	InnerElem m_elems[8];
	float m_trailing;
public:
	virtual void rva0055B96D(Xfer *xfer);
};

class Rva0055BB5C
{
	char m_pad[8];
	Rva0055BC8B m_inner;
	RGBColorFull m_c0;
	RGBColorFull m_c1;
	int m_val;
public:
	virtual void rva0055BB5C(Xfer *xfer);
};

void Rva0055BB5C::rva0055BB5C(Xfer *xfer)
{
	if (xfer->IsLightCRC())
		return;
	xfer->Version1();
	m_inner.Rva0055BC8B::rva0055B96D(xfer);
	*xfer == (RGBColor &)m_c0;
	*xfer == (RGBColor &)m_c1;
	*xfer == m_val;
}
