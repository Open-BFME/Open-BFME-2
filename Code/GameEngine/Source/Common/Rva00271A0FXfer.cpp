// cl: /Ireference/shims/bfme2_ascii /O1 /Ireference/shims/moduledata

// ?rva00271A0F@Rva00271A0F@@QAEXPAVXfer@@@Z, RVA 0x00271A0F, 113B.
// Chain lane: calls Rva0030612AXfer 0x0030612A (3-float helper, rowed).
// Light-CRC guard via slot 0x10, Version1, four triples at +0x04/+0x10/
// +0x1C/+0x28, int at +0x34 via slot 0x78, bool at +0x39 via slot 0x90,
// unsigned char at +0x38 via slot 0x8c. Xfer declaration is
// Rva000E5725Xfer.cpp's model verbatim so the operator== slots match.

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

void Rva0030612AXfer(Xfer *xfer, float *vals);

class Rva00271A0F
{
public:
	void rva00271A0F(Xfer *xfer);

private:
	char m_pad[0x04];
	float m_04[12];
	UnsignedInt m_34;
	char m_38;
	Bool m_39;
};

void Rva00271A0F::rva00271A0F(Xfer *xfer)
{
	if (xfer->IsLightCRC())
		return;
	xfer->Version1();
	Rva0030612AXfer(xfer, m_04);
	Rva0030612AXfer(xfer, m_04 + 3);
	Rva0030612AXfer(xfer, m_04 + 6);
	Rva0030612AXfer(xfer, m_04 + 9);
	*xfer == m_34;
	*xfer == m_39;
	*xfer == m_38;
}
