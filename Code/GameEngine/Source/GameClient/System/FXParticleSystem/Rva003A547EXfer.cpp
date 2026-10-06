// cl: /MD
//
// ?rva003A547E@Rva003A547E@@QAEXPAVXfer@@@Z, retail 0x003A547E, 226 bytes.
// Slot 7 (offset 0x1C) of vtable 0x0081BF84 (class of
// ??0?$ConcreteModuleTemplate@V?$DefaultModuleTag@$01@FXParticleSystem@@@FXParticleSystem@@QAE@ABV01@@Z
// in Code/GameEngine/Source/GameClient/FXParticleSystemModules.cpp).
// Ghidra labels DoXfer. Evidence: IsLightCRC early-out via Xfer slot 0x10,
// Version1 via rowed 0x000053EE, int at +0x04 via rowed XferWindMotion
// 0x0030606A, floats at +0x08-0x38 and +0x40-0x44 via Xfer slot 0x70, char at
// +0x3C via Xfer slot 0x8C. Layout is wind-motion plus float block.
// Recipe is PoisonedBehaviorXfer slot pattern with Xfer decl copied verbatim.

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

void XferWindMotion(Xfer *xfer, int *value);

class Rva003A547E
{
public:
	virtual void anchor();
	void rva003A547E(Xfer *xfer);
	int m_04;
	float m_08;
	float m_0c;
	float m_10;
	float m_14;
	float m_18;
	float m_1c;
	float m_20;
	float m_24;
	float m_28;
	float m_2c;
	float m_30;
	float m_34;
	float m_38;
	char m_3c;
	float m_40;
	float m_44;
};

void Rva003A547E::rva003A547E(Xfer *xfer)
{
	if (xfer->IsLightCRC())
		return;
	xfer->Version1();
	XferWindMotion(xfer, &m_04);
	*xfer == m_08;
	*xfer == m_0c;
	*xfer == m_10;
	*xfer == m_14;
	*xfer == m_18;
	*xfer == m_1c;
	*xfer == m_20;
	*xfer == m_24;
	*xfer == m_28;
	*xfer == m_2c;
	*xfer == m_30;
	*xfer == m_34;
	*xfer == m_38;
	*xfer == m_3c;
	*xfer == m_40;
	*xfer == m_44;
}

// ?rva003A5757@Rva003A5757@@QAEXPAVXfer@@@Z, retail 0x003A5757, 28 bytes.
// Slot 3 (offset 0x0C) of vtable 0x0081C60C (class of ??0Rva003AED3E@@QAE@ABV0@@Z
// in ConcreteModuleTemplateCopyCtors.cpp). Chain from 0x003A547E: Version1 via
// rowed 0x000053EE, then inner wind-motion block at +0x1C via rowed 0x003A547E.

class Rva003A5757
{
public:
	virtual void anchor();
	void rva003A5757(Xfer *xfer);
	char _pad04[0x18];
	Rva003A547E m_1c;
};

void Rva003A5757::rva003A5757(Xfer *xfer)
{
	xfer->Version1();
	m_1c.rva003A547E(xfer);
}

struct FieldParse;
class INI
{
public:
	void initFromINI(void *what, const struct FieldParse *table);
};
extern const struct FieldParse g_00C1B420[];
class Rva003A5560
{
public:
	void rva003A5560(INI *ini);
};

void Rva003A5560::rva003A5560(INI *ini)
{
	ini->initFromINI(this, g_00C1B420);
}
