// cl: /Ireference/shims/bfme2_ascii /MD
//
// ?Rva0055AED6@Rva0055B0CC@@UAEXPAVXfer@@PAX@Z, retail 0x0055AED6, 205 bytes.
// Virtual slot 12 (offset 0x30) of vtable 0x00870A98 (RVA, VA 0x00C70A98,
// class of ??1Rva00596B05@@UAE@XZ in Rva0055B0CCDerived.cpp, string
// AIMoneyLender immediately after vtable, base vtable 0x0086B900 shares
// slot 12). Called directly by 0x00573A35 (same this plus Xfer and second
// param) and by 0x005974F8 and 0x005DAAE5. Layout from base ctor 0x0055B048
// (float +0x04, ObjectID +0x08, AsciiString +0x0C, uint +0x10, list +0x14,
// float +0x18, list +0x1C, bool +0x20, bool +0x21, ObjectID +0x24,
// bool +0x28) and base dtor 0x0055B0CC (lists at +0x14/+0x1C, string at +0x0C).
// Xfer slots from proven siblings (GateOpenAndCloseBehaviorXfer): 0x28
// Version, 0x70 float, 0x78 uint, 0x90 bool, 0x6C AsciiString, 0x04 IsLoading.
// Version(1,3) with >=2 and >=3 gates, ObjectIDs via rowed 0x003060B2,
// uint +0x10 via local, tail IsLoading plus m_10==1 plus arg2 calling own
// slot 6 (0x18) with (arg2,1).

class AsciiString;
class UnicodeString;
class PooledString;
struct XferUnknown11;
struct Coord3DBase;
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

enum ObjectID
{
	INVALID_ID = 0
};

void XferObjectID(Xfer *xfer, ObjectID *objectID);

#include "ascii_string.h"

struct Coord3DBase
{
	float x;
	float y;
	float z;
};

class Rva0055B0CC
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
	virtual void slot5();
	virtual void Slot6(void *arg1, bool arg2);
	virtual void slot7();
	virtual void slot8();
	virtual void slot9();
	virtual void slot10();
	virtual void slot11();
	virtual void Rva0055AED6(Xfer *xfer, void *arg2);

private:
	float m_04;
	ObjectID m_08;
	AsciiString m_0C;
	unsigned int m_10;
	int m_pad14;
	float m_18;
	int m_pad1C;
	bool m_20;
	bool m_21;
	ObjectID m_24;
	bool m_28;
};

void Rva0055B0CC::Rva0055AED6(Xfer *xfer, void *arg2)
{
	Xfer::Version version(1, 3);
	*xfer == version;
	*xfer == m_04;
	XferObjectID(xfer, &m_08);
	*xfer == m_0C;
	unsigned int tmp = m_10;
	*xfer == tmp;
	m_10 = tmp;
	*xfer == m_18;
	*xfer == m_20;
	*xfer == m_21;
	if (version.m_minimum >= 2) {
		XferObjectID(xfer, &m_24);
	}
	if (version.m_minimum >= 3) {
		*xfer == m_28;
	}
	if (xfer->IsLoading() && m_10 == 1 && arg2 != 0) {
		Slot6(arg2, true);
	}
}

class Rva005DAAB6 : public Rva0055B0CC
{
public:
	virtual void dslot0();
	virtual void dslot1();
	virtual void dslot2();
	virtual void dslot3();
	virtual void dslot4();
	virtual void dslot5();
	virtual void dslot6();
	virtual void dslot7();
	virtual void dslot8();
	virtual void dslot9();
	virtual void dslot10();
	virtual void dslot11();
	virtual void Rva005DAAC1(Xfer *xfer, void *arg2);

private:
	bool m_2C;
	Coord3DBase m_30;
	float m_3C;
};

void Rva005DAAB6::Rva005DAAC1(Xfer *xfer, void *arg2)
{
	Xfer::Version version(1, 1);
	*xfer == version;
	((Rva0055B0CC *)this)->Rva0055B0CC::Rva0055AED6(xfer, arg2);
	*xfer == m_2C;
	*xfer == m_30;
	*xfer == m_3C;
}
