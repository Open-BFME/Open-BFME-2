// cl: /Ireference/shims/bfme2_ascii /MD /DNDEBUG /DWIN32 /D_WINDOWS
// ??0Rva003ECD60Object@@QAE@ABVAsciiString@@E@Z @0x003ECD60 (87B): heap
// object ctor that constructs the 20-element 0x44 array via ??_H with the
// rowed element ctor 0x003ECA4B copies the +0x550 name via the pinned
// StringBase copy 0x000365F0 zeroes four floats at +0x554/+0x558/+0x55C/
// +0x560 zeroes +0x564 via AND-imm and stores the flag byte at +0x568.
// Called from Xfer 0x003ECED5 plus two 0x002C5xxx sites. No donor name.
class Rva003ECD60Object;

#include "../../../../../../reference/shims/bfme2_ascii/ascii_string.h"


class Rva003ECA4BElement
{
public:
 Rva003ECA4BElement();
 Rva003ECA4BElement *rva003ECA81(const Rva003ECA4BElement *other);
private:
 float m_values[17];
};

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

#include "../../../../Include/Common/BfmeXfer.h"

class Xfer::Version
{
public:
	Version(unsigned char current, unsigned char minimum)
		: m_current(current), m_minimum(minimum) {}

	unsigned char m_current;
	unsigned char m_minimum;
};

struct Rva003ECB52Arg;
class Rva003ECA69Element : public Rva003ECA4BElement
{
public:
	Rva003ECA69Element *rva003ECB52(Rva003ECB52Arg *);
	void rva003ECAE0(Xfer *xfer);
};

class Rva003ECD60Object
{
	friend class ThreatFinderUpdate;
public:
	Rva003ECD60Object(const StringBase<char> &name, bool flag);
	void xfer(Xfer *xfer);

private:
	Rva003ECA4BElement m_elems[20];
	AsciiString m_name;
	float m_f554;
	float m_f558;
	float m_f55C;
	float m_f560;
	int m_564;
	bool m_568;
};

Rva003ECD60Object::Rva003ECD60Object(const StringBase<char> &name, bool flag)
	: m_name(reinterpret_cast<const AsciiString &>(name))
{
	float *p = &m_f554;
	p[0] = 0.0f;
	p[1] = 0.0f;
	p[2] = 0.0f;
	m_564 = 0;
	m_568 = flag;
	m_f560 = 0.0f;
}

// ?xfer@Rva003ECD60Object@@QAEXPAVXfer@@@Z, retail 0x003ECBF8 (136B). Xfers
// the heap object as Version(1,1) via slot 0x28 then the 20-element 0x44
// array through the rowed 0x003ECAE0 helper then AsciiString at +0x550 via
// slot 0x6c then Coord (3 floats) at +0x554 via slot 0x60 then float at
// +0x560 via slot 0x70 then uint at +0x564 via slot 0x78 then bool at +0x568
// via slot 0x90. Evidence: caller ThreatFinderUpdate::xfer at 0x003ECED5
// passes its heap at +0x20 here; allocation 0x56C matches 0x550+4+12+4+4+1;
// Xfer/Version decls copied verbatim from PoisonedBehaviorXfer.cpp and
// Rva00491DD3Xfer.cpp so float/uint/bool/Version sit at 0x70/0x78/0x90/0x28.
void Rva003ECD60Object::xfer(Xfer *xfer)
{
	Xfer::Version version(1, 1);
	*xfer == version;
	Rva003ECA4BElement *p = m_elems;
	for (int i = 20; i != 0; --i, ++p)
		reinterpret_cast<Rva003ECA69Element *>(p)->rva003ECAE0(xfer);
	*xfer == reinterpret_cast<AsciiString &>(m_name);
	*xfer == reinterpret_cast<Coord3DBase &>(m_f554);
	*xfer == m_f560;
	*xfer == reinterpret_cast<unsigned int &>(m_564);
	*xfer == m_568;
}
