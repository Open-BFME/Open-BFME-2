// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// ?xfer@Rva003FD789@@MAEXPAVXfer@@@Z, retail 0x003FD6BD, 35 bytes.
// Slot 3 (offset 0x0C) of vtable 0x00837D78 (class of ??0Rva003FD789
// rowed at 0x003FD716 in Rva003FD789Ctor.cpp). Persists AsciiString at
// +0x1C via Xfer slot 0x6C and Coord at +0x20 via Xfer slot 0x60. No base
// call (EmptyBase has no xfer) and no IsLightCRC/Version in retail.
// Layout is the rowed Rva003FD789 class from Rva003FD789Ctor.cpp (EmptyBase
// plus m_04/m_08/m_0C/m_10/m_11/m_14/m_18 plus m_1C plus Coord at +0x20).
// Caller at 0x00212208.

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

#include "ascii_string.h"

struct Coord3DBase
{
	float x;
	float y;
	float z;
};


class EmptyBase
{
public:
	EmptyBase() {}
	~EmptyBase();
};

class Rva003FD789 : public EmptyBase
{
public:
	virtual ~Rva003FD789();
protected:
	virtual void xfer(Xfer *xfer);
private:
	int volatile m_04;
	float volatile m_08;
	StringBase<char> m_0c;
	bool m_10;
	bool m_11;
	float m_14;
	short m_18;
	AsciiString m_1c;
	Coord3DBase m_20;
};

void Rva003FD789::xfer(Xfer *xfer)
{
	*xfer == m_1c;
	*xfer == m_20;
}
