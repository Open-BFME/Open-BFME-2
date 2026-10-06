// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?Rva004DD619Footprint@@YAPAVXfer@@PAV1@PAH@Z @ 0x004DD619 (30B).
// Free XferEnum helper moving 4 bytes through slot-37 XferEnum with the
// "PathfinderFootprintAngle" label, returning the Xfer for chaining.
// Evidence: string literal in .rdata; slot 0x94 proven by XferEnumHelpers;
// callers at 0x004DD67B plus 0x004DD69E use the return for the next Xfer call.

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

#include "../../../../Libraries/Include/Lib/Coord2D.h"

struct ICoord2D
{
	int x;
	int y;
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
	unsigned int red;
	unsigned int green;
	unsigned int blue;
	unsigned int alpha;
};

class Xfer;

class Snapshot
{
public:
	virtual ~Snapshot();
	virtual void crc(Xfer *xfer) = 0;
	virtual void loadPostProcess() = 0;
	virtual void xfer(Xfer *xfer) = 0;
};

class AsciiString;
class UnicodeString;
class PooledString;
struct XferUnknown11;

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

Xfer * __cdecl Rva004DD619Footprint(Xfer *xfer, int *value)
{
	xfer->XferEnum("PathfinderFootprintAngle", value, 4);
	return xfer;
}
