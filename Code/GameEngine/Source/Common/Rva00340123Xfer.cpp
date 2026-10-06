// cl: /MD
//
// ?xfer@Rva00340123@@MAEXPAVXfer@@@Z retail 0x00340123 53B slot 3.
// Evidence: Version1 via rowed 0x000053EE; base Rva0033FF2B xfer via rowed
// 0x0033FF76; int at +0x4C via Xfer slot 0x7C; bool at +0x50 via slot 0x90;
// callers at 0x00340423 0x00340481.
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

class Rva0049B47C
{
public:
	virtual ~Rva0049B47C();
private:
	char m_pad04[8];
};

class Rva0033FF2B : public Rva0049B47C
{
protected:
	virtual void xfer(Xfer *xfer);
private:
	char m_pad0C[0x20 - 0x0C];
	float m_20[3];
	float m_2C;
	int m_30;
	float m_34[3];
	unsigned int m_40;
	unsigned int m_44;
	bool m_48;
	bool m_49;
	char m_pad4A;
	bool m_4B;
};

class Rva00340123 : public Rva0033FF2B
{
protected:
	virtual void xfer(Xfer *xfer);
private:
	int m_4C;
	bool m_50;
};

void Rva00340123::xfer(Xfer *xfer)
{
	xfer->Version1();
	Rva0033FF2B::xfer(xfer);
	*xfer == m_4C;
	*xfer == m_50;
}
