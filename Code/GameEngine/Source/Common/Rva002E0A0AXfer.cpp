// cl: /Ireference/shims/bfme2_ascii /MD
// ?xfer@Rva002E0A0A@@MAEXPAVXfer@@@Z @0x0052BA0A 161B slot 3 xfer via Version plus IsLightCRC plus strings plus ints.
// Evidence: vslot slot 3 of 0x00804948; donor CopyCtor 0x002E0A0A same members; callers vtable.
#include "ascii_string.h"
#include "unicode_string.h"
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
	unsigned char m_major;
	unsigned char m_minor;
	Version(unsigned char a, unsigned char b) : m_major(a), m_minor(b) {}
};
class EmptyBase
{
public:
	EmptyBase() {}
	~EmptyBase();
};
class Rva002E0A0A : EmptyBase
{
protected:
	virtual void xfer(Xfer *xfer);
private:
	UnicodeString m_04;
	AsciiString m_08;
	AsciiString m_0c;
	AsciiString m_10;
	AsciiString m_14;
	int m_18;
	int m_1c;
	int m_20;
	bool m_24;
};
void Rva002E0A0A::xfer(Xfer *xfer)
{
	Xfer::Version v(1, 2);
	*xfer == v;
	if (!xfer->IsCRC())
		*xfer == m_04;
	*xfer == m_08;
	*xfer == m_0c;
	*xfer == m_14;
	*xfer == m_1c;
	*xfer == m_10;
	*xfer == m_18;
	*xfer == m_24;
	if (v.m_minor >= 2)
		*xfer == m_20;
	else
		m_20 = 0;
}
