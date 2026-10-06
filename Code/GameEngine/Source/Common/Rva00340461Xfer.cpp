// cl: /MD
// ?xfer@Rva00340461@@MAEXPAVXfer@@@Z, retail 0x00340461, 42 bytes.
// Chain xfer: Version1 via 0x000053EE, bool at +0x54 via Xfer slot 0x90,
// then base Rva00340123 xfer via 0x00340123. Evidence: callees rowed,
// base size 0x54 from Rva00340123Xfer.cpp, no callers.
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

class Rva00340461 : public Rva00340123
{
protected:
	virtual void xfer(Xfer *xfer);
private:
	bool m_54;
};

class Rva00340411 : public Rva00340123
{
protected:
	virtual void xfer(Xfer *xfer);
};

void Rva00340461::xfer(Xfer *xfer)
{
	xfer->Version1();
	*xfer == m_54;
	Rva00340123::xfer(xfer);
}

void Rva00340411::xfer(Xfer *xfer)
{
	xfer->Version1();
	Rva00340123::xfer(xfer);
}
