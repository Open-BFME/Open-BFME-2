// cl: /DNDEBUG /MD
//
// ?xfer@HordeGarrisonContain@@MAEXPAVXfer@@@Z, retail 0x00479D28, 64 bytes.
// Slot 3 of ??_7HordeGarrisonContain 0x00C46570 (installed by the rowed ctor
// 0x0047A040; slot 0 the rowed ??_G 0x0047A12B, slot 4 the rowed pool-name
// key 0x0047A0E6). Version(1,2) through Xfer slot 0x28, the rowed
// GarrisonContain::xfer 0x00478260, then from version 2 the int at +0x9E0
// that the ctor clears (Xfer slot 0x78). Member name not recovered.

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

class GarrisonContain
{
protected:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void xfer(Xfer *xfer);
	char m_unrecovered04[0x9E0 - 0x04];
};

class HordeGarrisonContain : public GarrisonContain
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	unsigned int m_9E0;
};

// ?xfer@HordeGarrisonContain@@MAEXPAVXfer@@@Z @0x00479D28
void HordeGarrisonContain::xfer(Xfer *xfer)
{
	Xfer::Version version(1, 2);
	*xfer == version;

	GarrisonContain::xfer(xfer);

	if (version.m_minimum >= 2)
		*xfer == m_9E0;
}

// Native 00479D68..00479D6D forwards the unchanged full-object receiver to
// 004783D7, whose existing ABI spelling is used by Rva004697E1Gate.cpp.
// WB 011A1210 confirms a no-argument member call, also used by the independently
// named HordeSiegeEngineContain::LoadPostProcess. The folded class name is unknown.
class Rva004697E1Contain { public: void rva004783D7(); };
class Rva00479D68 { public: void rva00479D68(); };
void Rva00479D68::rva00479D68()
{
    reinterpret_cast<Rva004697E1Contain *>(this)->rva004783D7();
}
