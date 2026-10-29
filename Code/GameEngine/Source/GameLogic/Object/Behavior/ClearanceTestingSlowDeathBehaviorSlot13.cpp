// cl: /DNDEBUG /MD
//
// ClearanceTestingSlowDeathBehavior::rva00483C69, retail 0x00483C69, 12
// bytes: slot 13 of the primary vtable 0x00C49E4C that
// ClearanceTestingSlowDeathBehavior's ctors (0x00483C35, 0x00483D50) install,
// the slot after UpdateModule::getUpdatePhase: hands out the interface the
// class carries at +0x50 (null-safe base conversion, neg/sbb/and). Which
// interface it is is not established; names by address.
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
#include "../../../../Include/Common/BfmeXfer.h"
#include "../../../../../Libraries/Include/Lib/Coord3D.h"

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

Rva00483C69Interface *ClearanceTestingSlowDeathBehavior::rva00483C69()
{
	return this;
}
