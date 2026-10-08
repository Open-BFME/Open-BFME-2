// cl: /Ireference/shims/bfme2_ascii /O1 /MD /Ireference/shims/moduledata

// ?rva000E5725@Rva000E5725@@QAEXPAVXfer@@@Z, RVA 0x000E5725, 218B.
// Chain lane: every callee is rowed (XferDrawableID 0x003060CA,
// Rva003062FEXfer 0x003062FE). Callers at 0x000E6215/0x000E6333 in
// 0x000E6186. Xfer slot evidence from the retail calls: Version at 0x28
// with {1,1}, AsciiString at 0x6c (+0x8c), float at 0x70 (+0x84/+0x88),
// bool at 0x90 (+0x80/+0x81/+0x82/+0x9c/+0x9d), raw-4 at 0x24
// (+0x94/+0x98), DrawableID helper at +0x4c, 12-float triple at +0x50.
// Xfer declaration is SkirmishGameInfoXfer.cpp's model verbatim so the
// operator== slots land on the shipped layout.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned char UnsignedByte;
typedef bool Bool;

class Xfer;
class AsciiString;
class UnicodeString;
class PooledString;
struct XferUnknown11;

struct Coord3DBase
{
	float x;
	float y;
	float z;
};

struct ICoord3D
{
	int x;
	int y;
	int z;
};

struct Region3D
{
	Coord3DBase lo;
	Coord3DBase hi;
};

struct IRegion3D
{
	ICoord3D lo;
	ICoord3D hi;
};

#include "../../../Libraries/Include/Lib/Coord2D.h"

struct ICoord2D
{
	int x;
	int y;
};

struct Region2D
{
	Coord2D lo;
	Coord2D hi;
};

struct IRegion2D
{
	ICoord2D lo;
	ICoord2D hi;
};

struct RealRange
{
	float lo;
	float hi;
};

struct RGBColor
{
	float red;
	float green;
	float blue;
};

struct RGBAColorReal
{
	float red;
	float green;
	float blue;
	float alpha;
};

struct RGBAColorInt
{
	int red;
	int green;
	int blue;
	int alpha;
};

#include "ascii_string.h"

#include "Common/Snapshot.h"

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

	void xferAsciiString(AsciiString *value) { *this == *value; }

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

void XferDrawableID(Xfer *xfer, int *value);
void Rva003062FEXfer(Xfer *xfer, float *vals);

class Rva000E5725
{
public:
	void rva000E5725(Xfer *xfer);

private:
	char m_pad[0x4C];
	Int m_4c;
	float m_50[12];
	Bool m_80;
	Bool m_81;
	Bool m_82;
	char m_pad83;
	float m_84;
	float m_88;
	AsciiString m_8c;
	char m_pad90[0x94 - 0x90];
	Int m_94;
	Int m_98;
	Bool m_9c;
	Bool m_9d;
};

void Rva000E5725::rva000E5725(Xfer *xfer)
{
	Xfer::Version version(1, 1);
	*xfer == version;
	*xfer == m_8c;
	XferDrawableID(xfer, &m_4c);
	Rva003062FEXfer(xfer, m_50);
	*xfer == m_80;
	*xfer == m_81;
	*xfer == m_82;
	*xfer == m_84;
	*xfer == m_88;
	xfer->XferRawBytes(&m_94, 4);
	xfer->XferRawBytes(&m_98, 4);
	*xfer == m_9c;
	*xfer == m_9d;
}
