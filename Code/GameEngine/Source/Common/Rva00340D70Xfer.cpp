// cl: /MD
// ?xfer@Rva00340D70@@MAEXPAVXfer@@@Z @ 0x00340D70 201B: slot 3 xfer of vtable 0x008121E8.
// True class per vtable is Rva00340D1F but that name is taken by misnamed 111B row at
// 0x00340CB0 (no vtable proof); honest address name keeps bytes and links. Fix that
// row in its own commit to free the real name.
// Version(1,3) via Xfer slot 0x28 then base AIInternalMoveToState xfer via rowed 0x0033FF76,
// IsLightCRC via slot 0x10, int at +0x4C via slot 0x7C, bools at +0x54/+0x55/+0x56
// via slot 0x90, version>1 int at +0x50 via slot 0x7C plus CommandSource at +0x58
// via rowed XferCommandSourceType 0x00305C02 plus Snapshot ptr at +0x5C via slot
// 0x30 plus float at +0x60 via slot 0x70 plus bool at +0x64 via slot 0x90,
// version>2 bool at +0x57 via slot 0x90. Evidence: vtable 0x008121E8 slot 3.
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

#include "../../Include/Common/BfmeXfer.h"

class Xfer::Version
{
public:
	Version(unsigned char current, unsigned char minimum)
		: m_current(current), m_minimum(minimum) {}

	unsigned char m_current;
	unsigned char m_minimum;
};

void XferCommandSourceType(Xfer *xfer, int *value);

class Rva0049B47C
{
public:
	virtual ~Rva0049B47C();

private:
	char m_pad04[8];
};

class AIInternalMoveToState : public Rva0049B47C
{
public:
	virtual ~AIInternalMoveToState();

protected:
	virtual void xfer(Xfer *xfer);

private:
	char m_pad0C[0x40 - 0x0C];
	unsigned int m_handle40;
};

class Rva00340D70 : public AIInternalMoveToState
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	char m_pad44[0x4C - 0x44];
	int m_4C;
	int m_50;
	bool m_54;
	bool m_55;
	bool m_56;
	bool m_57;
	int m_58;
	Snapshot *m_snapshot;
	float m_60;
	bool m_64;
};

void Rva00340D70::xfer(Xfer *xfer)
{
	Xfer::Version version(1, 3);
	*xfer == version;
	AIInternalMoveToState::xfer(xfer);
	if (xfer->IsLightCRC())
		return;
	*xfer == m_4C;
	*xfer == m_54;
	*xfer == m_55;
	*xfer == m_56;
	if (version.m_minimum > 1) {
		*xfer == m_50;
		XferCommandSourceType(xfer, &m_58);
		if (m_snapshot != 0)
			*xfer == *m_snapshot;
		*xfer == m_60;
		*xfer == m_64;
	}
	if (version.m_minimum > 2)
		*xfer == m_57;
}
