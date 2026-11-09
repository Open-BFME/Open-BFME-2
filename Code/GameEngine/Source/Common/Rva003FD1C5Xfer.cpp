// cl: /MD
//
// ?xfer@Rva002B3092@@MAEXPAVXfer@@@Z, retail 0x003FD1C5, 38 bytes.
// Unlock: persists uint at +0x04 via Xfer slot 0x78 and bool at +0x08 via
// Xfer slot 0x90. Same minimal two-persist shape as Rva003FD789::xfer
// (no base/Version in retail). Owner unknown so honest address names.
// Callers at 0x003FD201/0x003FD222/0x003FD2CB/0x003FD32A/0x003FD383.

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

#include "../../Include/Common/BfmeXfer.h"

class Rva002B3092
{
public:
	virtual ~Rva002B3092();
protected:
	virtual void xfer(Xfer *xfer);
private:
	unsigned int m_04;
	bool m_08;
};

void Rva002B3092::xfer(Xfer *xfer)
{
	*xfer == m_04;
	*xfer == m_08;
}

// ?rva003FD1C5@Rva003FD219@@MAEXPAVXfer@@@Z @0x003FD219 30B and
// ?rva003FD1C5@Rva003FD37A@@MAEXPAVXfer@@@Z @0x003FD37A 30B: derived
// overrides of the slot above that chain to it and then persist the word at
// +0x0C, an AsciiString (Xfer slot 0x6C) resp. an unsigned int (slot 0x78).
class Rva003FD219 : public Rva002B3092
{
protected:
	virtual void rva003FD1C5(Xfer *xfer);
private:
	void *m_0c; // AsciiString
};

void Rva003FD219::rva003FD1C5(Xfer *xfer)
{
	Rva002B3092::xfer(xfer);
	*xfer == *reinterpret_cast<AsciiString *>(&m_0c);
}

class Rva003FD37A : public Rva002B3092
{
protected:
	virtual void rva003FD1C5(Xfer *xfer);
private:
	unsigned int m_0c;
};

void Rva003FD37A::rva003FD1C5(Xfer *xfer)
{
	Rva002B3092::xfer(xfer);
	*xfer == m_0c;
}
