// cl: /MD
//
// ?xfer@ClearanceTestingSlowDeathBehavior@@MAEXPAVXfer@@@Z, retail 0x00483E0A, 27 bytes. Virtual
// slot 3 (offset 0x0C) of vtable 0x00849E4C (class of rowed dtor
// ??1ClearanceTestingSlowDeathBehavior@@UAE@XZ in Rva0045D39EDerived.cpp): Xfer Version1 via rowed
// 0x53EE then SlowDeathBehavior base xfer via rowed 0x45D3CB. No members
// (cf. Rva00499F45Xfer minimal shape). Identity is slot 3 plus the base
// SlowDeathBehavior xfer call; class name stays honest Rva address name.

enum NameKeyType
{
	NK_UNKNOWN = 0
};

class Snapshot;
class AsciiString;
class UnicodeString;
class PooledString;
class Coord3DBase;
struct ICoord3D;
struct Region3D;
struct IRegion3D;
class Coord2D;
struct ICoord2D;
struct Region2D;
struct IRegion2D;
class RealRange;
struct RGBColor;
class RGBAColorReal;
class RGBAColorInt;
struct XferUnknown11;
#include "../../Include/Common/BfmeXfer.h"
#include "../../../Libraries/Include/Lib/Coord3D.h"

class Thing
{
public:
	void transformPoint(const Coord3D *in, Coord3D *out);
};

struct Rva00483C35ModuleData
{
	unsigned char m_pad000[0x1EC];
	Coord3D m_clearanceGeometryOffset;
};

// The primary base subobject spans +0x00..+0x50 (vptrs at +0, +0xC, +0x10,
// +0x20 and +0x24 in the dtor's stores, not modelled here); the interface
// whose slot 1 is getClearanceTestGeometryCenter sits at +0x50.
class SlowDeathBehavior
{
public:
	virtual ~SlowDeathBehavior();
protected:
	virtual void xfer(Xfer *xfer);
	const Rva00483C35ModuleData *m_moduleData; // +0x04
	Thing *m_object; // +0x08
private:
	unsigned char m_pad0C[0x50 - 0x0C];
};

class Rva00483C69Interface
{
public:
	virtual void s00();
	virtual void getClearanceTestGeometryCenter(Coord3D *out) = 0;
};

class ClearanceTestingSlowDeathBehavior : public SlowDeathBehavior, public Rva00483C69Interface
{
public:
	virtual NameKeyType getModuleNameKey() const;
	virtual Rva00483C69Interface *rva00483C69();
	virtual void getClearanceTestGeometryCenter(Coord3D *out);
protected:
	virtual void xfer(Xfer *xfer);
};

void ClearanceTestingSlowDeathBehavior::xfer(Xfer *xfer)
{
	xfer->Version1();
	SlowDeathBehavior::xfer(xfer);
}
