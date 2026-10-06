// cl: /MD
// ?rva004ECDC8@Rva004ECDC8@@QAEXPAVXfer@@@Z @ 0x004ECDC8, 66 bytes.
// Xfer helper for a 0x14-byte element (uint at +0, Coord3DBase at +4, int at
// +0x10) with Version(1,1) via slot 0x28 then uint/Coord/int via
// 0x78/0x60/0x7C. Evidence: callers at 0x004EDB95 and 0x004EDBC7 in 0x004EDA8C
// (Xfer with IsLoading at +0x4 IsStoring at +0x8 Version 0,2 via +0x28 bool via
// +0x90 uint via +0x78 int via +0x7C Coord via +0x60 Ascii via +0x6C); Xfer
// vtable with reversed operator== group copied verbatim from
// Code/GameEngine/Source/GameLogic/Object/Behavior/PoisonedBehaviorXfer.cpp;
// Coord3DBase 12B from game/Libraries/Source/WWVegas/WWMath/coord3d.h;
// Xfer::Version 2B from game/GameEngine/Source/Common/System/xfer.h;
// Rva honest-address name since caller class is UNCLAIMED.
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

class Coord3DBase
{
public:
	float x;
	float y;
	float z;
};

class Xfer::Version
{
public:
	unsigned char data[2];
};

class Rva004ECDC8
{
public:
	unsigned int m_unk0;
	Coord3DBase m_unk4;
	int m_unk10;
	void rva004ECDC8(Xfer *xfer);
};

void Rva004ECDC8::rva004ECDC8(Xfer *xfer)
{
	Xfer::Version v;
	v.data[0] = 1;
	v.data[1] = 1;
	*xfer == v;
	*xfer == m_unk0;
	*xfer == m_unk4;
	*xfer == m_unk10;
}
