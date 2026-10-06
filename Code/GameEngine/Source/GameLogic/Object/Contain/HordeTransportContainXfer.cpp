// cl: /DNDEBUG /MD /GX
// ?xfer@HordeTransportContain@@MAEXPAVXfer@@@Z, retail 0x0047714A, 59 bytes.
// Slot 3 (offset 0x0C) of vtable 0x00845EB8 (class of
// ??0HordeTransportContain@@QAE@PAVThing@@PBVModuleData@@@Z in
// HordeTransportContainCtor.cpp). Version1 via rowed 0x000053EE then
// rowed TransportContain::xfer 0x00466DBC then int at +0x120 via Xfer
// slot 0x7c and bool at +0x124 via Xfer slot 0x90 (same slots as
// TransportContain::xfer uses for int at +0x100 and bool at +0x10C).
// Layout from HordeTransportContainCtor (int -1000 at +0x120 and zero
// byte at +0x124); Xfer declaration copied verbatim from
// TransportContainXfer.cpp per xfer recipe.
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

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;

class OpenContain
{
protected:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void xfer( Xfer *xfer );
	char m_unrecovered04[ 0x100 - 0x04 ];
};

class TransportContain : public OpenContain
{
protected:
	virtual void xfer( Xfer *xfer );
private:
	Int m_extraSlotsInUse;
	UnsignedInt m_frameExitNotBusy;
	char m_unrecovered108[ 0x10C - 0x108 ];
	Bool m_payloadCreated;
};

class HordeTransportContain : public TransportContain
{
protected:
	virtual void xfer( Xfer *xfer );
private:
	char m_pad110[ 0x120 - 0x110 ];
	Int m_int120;
	Bool m_bool124;
};

void HordeTransportContain::xfer( Xfer *xfer )
{
	xfer->Version1();
	TransportContain::xfer( xfer );
	*xfer == m_int120;
	*xfer == m_bool124;
}
