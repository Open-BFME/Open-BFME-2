// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?Rva00573F9F@Rva00573F03@@UAEXPAVXfer@@PAX@Z @0x00573F9F 116B
// Xfer slot 12 (0x30) of Rva00573F03 (vtable 0x0086E2C8, derived of Rva00573B23):
// Version(1,1), Coord +0x40 via 0x60, float +0x4c via 0x70, int +0x50 via 0x7c,
// bool +0x54 via 0x90, uint +0x58 via 0x78, uint +0x5c via 0x78, then base
// Rva00573B23::Rva00573A35 last. Base Rva00573B23 ends 0x40. Chain from 0x00573A35.
// Evidence: call [eax+28] with bytes 1,1; six Xfer virtuals 0x60 0x70 0x7c 0x90
// 0x78 0x78; push [ebp+C] push esi call 0x573A35 ret 8. Unblocks 0x0059702D.
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
#include "ascii_string.h"
struct Coord3DBase
{
	float x;
	float y;
	float z;
};
enum ObjectID
{
	INVALID_ID = 0
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
class Rva00573B23 : public Rva0055B0CC
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
	virtual void Rva00573A35(Xfer *xfer, void *arg2);
private:
	AsciiString m_2c;
	Coord3DBase m_30;
	float m_3c;
};
class Rva00573F03 : public Rva00573B23
{
public:
	virtual void eslot0();
	virtual void eslot1();
	virtual void eslot2();
	virtual void eslot3();
	virtual void eslot4();
	virtual void eslot5();
	virtual void eslot6();
	virtual void eslot7();
	virtual void eslot8();
	virtual void eslot9();
	virtual void eslot10();
	virtual void eslot11();
	virtual void Rva00573F9F(Xfer *xfer, void *arg2);
private:
	Coord3DBase m_40;
	float m_4c;
	int m_50;
	bool m_54;
	char m_pad55[3];
	unsigned int m_58;
	unsigned int m_5c;
};
void Rva00573F03::Rva00573F9F(Xfer *xfer, void *arg2)
{
	Xfer::Version version(1, 1);
	*xfer == version;
	*xfer == m_40;
	*xfer == m_4c;
	*xfer == m_50;
	*xfer == m_54;
	*xfer == m_58;
	*xfer == m_5c;
	((Rva00573B23 *)this)->Rva00573B23::Rva00573A35(xfer, arg2);
}
