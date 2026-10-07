// cl: /Ireference/shims/bfme2_ascii /GX- /O1
// ?rva00380200@Rva00380200@@QAEPAVAsciiString@@XZ @ 0x00380200 (13B): getter returning +4 or AsciiString::TheEmptyString. Callers 0x00380230 0x00380265 push result. Twin of EmptyString fallback pattern.
// ?rva0038020D@Rva00380200@@QAEXXZ @ 0x0038020D (110B): caches at +0x20 the
// value the store (0x00DFE0EC, pinned get 0x002000D7) config for level
// m_14 + 1 reports for this name (0x7FFFFFFF when absent), and at +0x24 the
// one for level m_14 (0 when absent), through the config method 0x00200157
// (pinned from these call sites: thiscall ret 4 taking the name by reference,
// returning a dword field). Retail keeps the config in edx across the
// rva00380200 call, which cl only does when that getter was compiled earlier
// in the same TU; the TU is /O1 so the getter is called rather than inlined.
#include "ascii_string.h"

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


// Matched DIR32 references place this static object at VA 0x00DE0878. Its
// four retail bytes are zero, the null StringBase buffer of an empty string.
const AsciiString AsciiString::TheEmptyString;

struct Rva002000D7Config
{
	int rva00200157(const AsciiString &name);
};
class Rva002000D7Store
{
public:
	Rva002000D7Config *get(int);
};
extern Rva002000D7Store *Va00DFE0ECStore;

class Rva00380200
{
	int m_00;
	AsciiString *m_ptr;
	char m_pad08[4];
	float m_0C;
	float m_10;
	int m_14;
	int m_18;
	int m_1C;
	int m_20;
	int m_24;
	int m_28;
public:
	AsciiString *rva00380200();
	void rva0038020D();
	void rva00380499(Xfer *xfer);
};

AsciiString *Rva00380200::rva00380200()
{
	if (m_ptr)
		return m_ptr;
	return const_cast<AsciiString *>(&AsciiString::TheEmptyString);
}

void Rva00380200::rva0038020D()
{
	Rva002000D7Config *config = Va00DFE0ECStore ? Va00DFE0ECStore->get(m_14 + 1) : 0;
	m_20 = config ? config->rva00200157(*rva00380200()) : 0x7fffffff;
	config = Va00DFE0ECStore ? Va00DFE0ECStore->get(m_14) : 0;
	m_24 = config ? config->rva00200157(*rva00380200()) : 0;
}

// Retail 0x00380499 is a complete 126-byte RET4 body on the same receiver
// as 0x0038020D. Virtual Xfer slots prove floats at +0x0C/+0x10, ints at
// +0x14/+0x18/+0x1C/+0x28, Version {1,2}, and the load-only cache refresh.
// The original class and member names remain unidentified.
void Rva00380200::rva00380499(Xfer *xfer)
{
    Xfer::Version version(1, 2);
    *xfer == version;
    *xfer == m_0C;
    *xfer == m_10;
    *xfer == m_14;
    *xfer == m_18;
    *xfer == m_1C;
    if (version.m_minor >= 2)
        *xfer == m_28;
    if (xfer->IsLoading())
        rva0038020D();
}
