// cl: /MD
//
// ?xfer@Rva004AD9B0@@MAEXPAVXfer@@@Z, retail 0x004ADA2D, 67 bytes.
// Slot 3 (offset 0x0C) of vtable 0x008551C0 (class of ??1Rva004AD9B0 in
// ModuleUpdateDtors.cpp). Version(1,2) via Xfer slot 0x28, base
// SpecialAbilityUpdate::xfer rowed at 0x0044F996, then version-gated bool
// at +0x8C via Xfer slot 0x90. Xfer declaration verbatim from
// SpecialAbilityUpdateXfer.cpp (reverse overload order puts Version at
// 0x28 and bool at 0x90). No IsLightCRC (base handles). Callers: none
// rowed; vtable slot proves identity.
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

class Xfer::Version
{
public:
	Version(unsigned char current, unsigned char minimum)
		: m_current(current), m_minimum(minimum) {}

	unsigned char m_current;
	unsigned char m_minimum;
};

class Thing;
class ModuleData;

class Rva0044EF5E
{
public:
	Rva0044EF5E(Thing *thing, const ModuleData *moduleData);
	virtual ~Rva0044EF5E();
protected:
	unsigned char m_pad[0x88 - 4];
};

class SpecialAbilityUpdate : public Rva0044EF5E
{
protected:
	virtual void xfer(Xfer *xfer);
};

class Rva004AD9B0 : public SpecialAbilityUpdate
{
protected:
	virtual void xfer(Xfer *xfer);
private:
	unsigned char m_pad8C[0x8C - 0x88];
	bool m_8C;
};

void Rva004AD9B0::xfer(Xfer *xfer)
{
	Xfer::Version version(1, 2);
	*xfer == version;
	SpecialAbilityUpdate::xfer(xfer);
	if (version.m_minimum >= 2)
		*xfer == m_8C;
}
