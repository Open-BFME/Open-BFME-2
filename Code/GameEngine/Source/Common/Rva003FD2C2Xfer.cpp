// cl: /MD
//
// ?rva003FD2C2@Rva003FD2C2@@MAEXPAVXfer@@@Z, retail 0x003FD2C2, 52 bytes.
// Chain: calls 0x003FD1C5 which just landed (base Rva003FD1C5 handling
// +0x04/+0x08). Then persists Coord at +0x0C via Xfer slot 0x60, float at
// +0x18 via Xfer slot 0x70, uint at +0x1C via Xfer slot 0x78. Same minimal
// shape as the base plus three members (Coord ends where float starts).

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

struct Coord3DBase
{
	float x;
	float y;
	float z;
};

class Rva003FD1C5
{
public:
	virtual ~Rva003FD1C5();
protected:
	virtual void rva003FD1C5(Xfer *xfer);
private:
	unsigned int m_04;
	bool m_08;
};

class Rva003FD2C2 : public Rva003FD1C5
{
protected:
	virtual void rva003FD2C2(Xfer *xfer);
private:
	Coord3DBase m_0c;
	float m_18;
	unsigned int m_1c;
};

void Rva003FD2C2::rva003FD2C2(Xfer *xfer)
{
	Rva003FD1C5::rva003FD1C5(xfer);
	*xfer == m_0c;
	*xfer == m_18;
	*xfer == m_1c;
}
