// cl: /O1 /DNDEBUG /MD /EHsc
// Destructor and scalar deleting destructor of an unidentified class with
// vtable 0x00C61DC4: one string member at +4, then an empty base whose vtable
// is 0x00BBB554. These bodies were first claimed as AttackNugget's, but the
// real AttackNugget (built by AttackNugget::parse) uses vtable 0x00BE0FF4 and
// a different member, so the class stays address-named until identified.
//
// ?DoXfer@Rva004E1B72@@UAEXAAVXfer@@@Z retail 0x004E1355 61B: virtual slot 3
// (offset 0x0C) of vtable 0x00C61DC4 (class of rowed ??1Rva004E1B72@@UAE@XZ).
// Snapshot order is dtor plus LoadPostProcess plus GetSnapshotName plus DoXfer
// per LivingWorldRegionConnectionDtor; slot 1 is the shared empty ret at
// 0x000B3FD0 and slot 2 is the rowed string getter at 0x004E1392 returning
// SetPlayerControlOfArmy. Body is Version 1 1 via Xfer slot 0x28 then
// AsciiString at +0x04 via Xfer slot 0x6C then bool at +0x08 via Xfer slot
// 0x90. Xfer declaration mirrors GpuDrawModuleInfoDoXfer for retail vtable
// 0x00BBB910. Layout is AsciiString at +4 plus bool at +8.

// Fold-shared string member teardown (never defined; resolves through the
// symbols.csv pin at 0x00036410).
class AsciiString
{
public:
	~AsciiString();

private:
	void *m_data;
};

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

class Xfer::Version
{
public:
	Version(unsigned char current, unsigned char minimum)
		: m_current(current), m_minimum(minimum) {}

	unsigned char m_current;
	unsigned char m_minimum;
};

class Rva004E1B72Base
{
public:
	virtual ~Rva004E1B72Base() {}
};

class Rva004E1B72 : public Rva004E1B72Base
{
public:
	virtual ~Rva004E1B72();
	virtual void DoXfer(Xfer &xfer);

	AsciiString m_member04;
	bool m_bool08;
};

Rva004E1B72::~Rva004E1B72()
{
}

void Rva004E1B72::DoXfer(Xfer &xfer)
{
	Xfer::Version version(1, 1);
	xfer == version;
	xfer == m_member04;
	xfer == m_bool08;
}
