// cl: /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
// stlport
// ?xfer@ThreatFinderUpdate@@MAEXPAVXfer@@@Z @0x003ECED5 (143B): ThreatFinderUpdate
// xfer (vslot 3) that versions via slot 0x28 calls UpdateModule::xfer allocates
// the 0x56C heap via 0x003ECD60 when not storing registers it then xfers it.
// Evidence: vtable 0x008360CC slot 3 plus ctor 0x003ECCA2 plus dtor heap +0x20
// plus callers of 0x003ECD60 and 0x003ECBF8; Xfer decl verbatim from
// PoisonedBehaviorXfer.cpp so Version sits at 0x28 and IsStoring at 0x08.
// The canonical frozen StringBase replaces the private copy; the member is
// only passed by reference, so its copy ctor stays declared.
#include "string_base.h"

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

struct OwnerWithName
{
	char m_pad[0x88];
	StringBase<char> m_name;
};

class UpdateModule
{
public:
	void xfer(Xfer *xfer);

protected:
	virtual void dummy() = 0;

	char m_pad04[4];
	OwnerWithName *m_owner;
	char m_pad0C[0x14];
};

class Rva003ECDB7Object
{
public:
	void registerName();
};

class Rva003ECD60Object : public Rva003ECDB7Object
{
public:
	Rva003ECD60Object(const StringBase<char> &name, bool flag);
	void xfer(Xfer *xfer);

private:
	char m_pad[0x56C];
};

class ThreatFinderUpdate : public UpdateModule
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	Rva003ECD60Object *m_heap;
};

void ThreatFinderUpdate::xfer(Xfer *xfer)
{
	Xfer::Version version(1, 1);
	*xfer == version;
	UpdateModule::xfer(xfer);
	if (!xfer->IsStoring()) {
		Rva003ECD60Object *obj = new Rva003ECD60Object(m_owner->m_name, false);
		m_heap = obj;
		obj->registerName();
	}
	if (m_heap != 0)
		m_heap->xfer(xfer);
}
