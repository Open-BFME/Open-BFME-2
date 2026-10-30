// cl: /MD
// stlport
#include <list>
//
// ?xfer@EvacuateDamage@@MAEXPAVXfer@@@Z, retail 0x004BAC83, 44 bytes.
// Virtual slot 3 (offset 0x0C) of vtable 0x00859E2C (VA 0x00C59E2C, class of
// rowed ctor ??0EvacuateDamage@@QAE@PAVThing@@PBVModuleData@@@Z in
// EvacuateDamageCtorModuleFactoryBody.cpp): Version(1,2) via Xfer slot 0x28
// then base DamageModule xfer via rowed 0x004CE56D. No members and no
// IsLightCRC early-out in retail. Recipe is the WallHubBehaviorXfer and
// ReplaceSelfUpgradeXfer 44B Version-plus-base pattern with protected xfer.

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

#include "../../../../Include/Common/BfmeXfer.h"

class Xfer::Version
{
public:
	Version(unsigned char current, unsigned char minimum)
		: m_current(current), m_minimum(minimum) {}

	unsigned char m_current;
	unsigned char m_minimum;
};

enum NameKeyType
{
	NK_UNKNOWN = 0
};

#include "../../../../Include/Common/ObjectModule.h"

class PB_Iface1 { public: virtual void slot(); };

class EvacuateDamageInterface { public: virtual void slot() = 0; };

// The target's three-vptr base is only address-identified at 0x004B96CC.
class Rva004B96CC : public ObjectModule,
                     public PB_Iface1,
                     public EvacuateDamageInterface
{
public:
	virtual ~Rva004B96CC();
};

typedef Rva004B96CC DamageModule;

class Rva004CE56D
{
public:
	virtual void baseAnchor();
	void xfer(Xfer *xfer);
};

class EvacuateDamage : public DamageModule
{
public:
	virtual NameKeyType getModuleNameKey() const;

protected:
	virtual void xfer(Xfer *xfer);
	virtual ~EvacuateDamage();

private:
	// Retail calls the ICF-canonical List_base<int> destructor at 0x004EC395.
	// EvacuationRecord is two POD dwords; the list object and teardown are
	// storage-identical here, and the typed pin for this dtor points elsewhere.
	std::list<int> m_pendingEvacuations;
};

void EvacuateDamage::xfer(Xfer *xfer)
{
	Xfer::Version version(1, 2);
	*xfer == version;
	reinterpret_cast<Rva004CE56D *>(this)->Rva004CE56D::xfer(xfer);
}
