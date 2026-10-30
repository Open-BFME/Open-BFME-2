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
#include "ascii_string.h"

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
public:
	char m_pad00[0x88];
	StringBase<char> m_name; // +0x88
};

enum NameKeyType { NK_UNKNOWN = 0 };

class Thing;
class ModuleData;
class Rva003ECD60Object;
class Xfer;

#include "../../../../Include/GameLogic/Module/BehaviorModule.h"

class UpdateModuleInterface
{
public:
    virtual void f2() = 0;
};

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
public:
    UpdateModule(Thing *thing, const ModuleData *moduleData);
    virtual ~UpdateModule();
    void xfer(Xfer *xfer);

private:
    unsigned int m_nextCallFrameAndPhase;
    int m_indexInLogic;
    int m_updateState;
};

class ThreatFinderUpdate : public UpdateModule
{
public:
    ThreatFinderUpdate(Thing *thing, const ModuleData *moduleData);
    virtual ~ThreatFinderUpdate();
    virtual NameKeyType getModuleNameKey() const;

protected:
    virtual void xfer(Xfer *xfer);

private:
    Rva003ECD60Object *m_heap;
};

class Rva003ECDB7Object
{
public:
	~Rva003ECDB7Object();
	void registerName();

private:
	char m_pad[0x550];
	AsciiString m_name;
};

class Rva003ECA4BElement
{
public:
 Rva003ECA4BElement();
 Rva003ECA4BElement *rva003ECA81(const Rva003ECA4BElement *other);
private:
 float m_values[17];
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



void ThreatFinderUpdate::xfer(Xfer *xfer)
{
	Xfer::Version version(1, 1);
	*xfer == version;
	UpdateModule::xfer(xfer);
	if (!xfer->IsStoring()) {
		Rva003ECD60Object *obj = new Rva003ECD60Object(reinterpret_cast<OwnerWithName *>(m_object)->m_name, false);
		m_heap = obj;
		reinterpret_cast<Rva003ECDB7Object *>(obj)->registerName();
	}
	if (m_heap != 0)
		m_heap->xfer(xfer);
}
