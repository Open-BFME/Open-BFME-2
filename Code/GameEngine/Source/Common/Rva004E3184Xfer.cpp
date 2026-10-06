// cl: /Ireference/shims/bfme2_ascii /O1 /MD /EHsc /DNDEBUG /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/moduledata
// stlport
// ?DoXfer@Rva004E3184@@UAEXAAVXfer@@@Z @0x004E3991 221B
// Slot 3 of vtable 0x00861F28 (Rva004E3184 ModuleData). Layout from
// Rva004E3184CopyCtor. Version 1 3 via Xfer slot 0x28 then members via
// 0x6C/0x50/0x70/0x90 plus 0x4C via Rva004E12D7Parse plus vector via
// xferAsciiStringVector plus version-gated +0x18/+0x28/+0x1C.
#include <memory>
#include <vector>

#include "ascii_string.h"
#include "Common/Snapshot.h"


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

#include "../../../Libraries/Include/Lib/Coord2D.h"

class Rva004E3184 : public Snapshot {
public:
    virtual ~Rva004E3184();
    virtual void DoXfer(Xfer &xfer);
private:
    AsciiString m_04;
    AsciiString m_08;
    AsciiString m_0c;
    AsciiString m_10;
    AsciiString m_14;
    AsciiString m_18;
    AsciiString m_1c;
    Coord2D m_20;
    AsciiString m_28;
    AsciiString m_2c;
    AsciiString m_30;
    AsciiString m_34;
    _STL::vector<AsciiString> m_vec38;
    float m_44;
    unsigned int m_48;
    unsigned int m_4c;
    AsciiString m_50;
    bool m_54;
    bool m_55;
};

void Rva004E12D7Parse(void *a, void *b);
Xfer *xferAsciiStringVector(Xfer *xfer, _STL::vector<AsciiString> *vec);

void Rva004E3184::DoXfer(Xfer &xfer)
{
	Xfer::Version version(1, 3);
	xfer == version;
	Rva004E12D7Parse(&xfer, &m_4c);
	xfer == m_04;
	xfer == m_08;
	xfer == m_20;
	xfer == m_2c;
	xfer == m_30;
	xfer == m_34;
	xferAsciiStringVector(&xfer, &m_vec38);
	xfer == m_54;
	xfer == m_50;
	xfer == m_44;
	xfer == m_55;
	if (version.m_minimum >= 2) {
		xfer == m_18;
	}
	if (version.m_minimum >= 3) {
		xfer == m_28;
		xfer == m_1c;
	}
}
