// cl: /O1 /MD
//
// ?rva003FD1C5@Rva003FD1C5@@MAEXPAVXfer@@@Z, retail 0x003FD1C5, 38 bytes.
// Unlock: persists uint at +0x04 via Xfer slot 0x78 and bool at +0x08 via
// Xfer slot 0x90. Same minimal two-persist shape as Rva003FD789::xfer
// (no base/Version in retail). Owner unknown so honest address names.
// Callers at 0x003FD201/0x003FD222/0x003FD2CB/0x003FD32A/0x003FD383.

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

void Rva003FD1C5::rva003FD1C5(Xfer *xfer)
{
	*xfer == m_04;
	*xfer == m_08;
}

// ?rva003FD1C5@Rva003FD219@@MAEXPAVXfer@@@Z @0x003FD219 30B and
// ?rva003FD1C5@Rva003FD37A@@MAEXPAVXfer@@@Z @0x003FD37A 30B: derived
// overrides of the slot above that chain to it and then persist the word at
// +0x0C, an AsciiString (Xfer slot 0x6C) resp. an unsigned int (slot 0x78).
class Rva003FD219 : public Rva003FD1C5
{
protected:
	virtual void rva003FD1C5(Xfer *xfer);
private:
	void *m_0c; // AsciiString
};

void Rva003FD219::rva003FD1C5(Xfer *xfer)
{
	Rva003FD1C5::rva003FD1C5(xfer);
	*xfer == *reinterpret_cast<AsciiString *>(&m_0c);
}

class Rva003FD37A : public Rva003FD1C5
{
protected:
	virtual void rva003FD1C5(Xfer *xfer);
private:
	unsigned int m_0c;
};

void Rva003FD37A::rva003FD1C5(Xfer *xfer)
{
	Rva003FD1C5::rva003FD1C5(xfer);
	*xfer == m_0c;
}
