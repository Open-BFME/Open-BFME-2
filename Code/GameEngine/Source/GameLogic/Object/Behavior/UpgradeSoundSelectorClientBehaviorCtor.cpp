// cl: /DNDEBUG /MD
//
// ??0UpgradeSoundSelectorClientBehavior@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x00252CB5, 42 bytes. The rowed Rva00252B68 base, the
// interface base's own table (retail's folded 0x00BE2B78, three pure slots), then the compiler's two table
// installs: 0x00BEFEB0 at +0 and 0x00BEFEA4 at +0x0C. The instance factory 0x00254BF7 is its sole raw caller.

class Thing;
class ModuleData;
class Object;
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
struct Rva002C99FB;
#include "../../../../Include/Common/BfmeXfer.h"
#include "../../../../Include/Common/Rva00252B68.h"

class Rva004CB51CInterface
{
public:
	virtual bool rva004CB3F8(int index, Rva002C99FB *out) = 0;
	virtual bool rva004CB48A(const AsciiString &name, Rva002C99FB *out) = 0;
	virtual bool rva004CB51C(int *out) = 0;
};

// Retail's tables: 0x00BEFEB0 (19 slots) and 0x00BEFEA4 at +0x0C.
class UpgradeSoundSelectorClientBehavior : public Rva00252B68, public Rva004CB51CInterface
{
public:
	UpgradeSoundSelectorClientBehavior(Thing *thing, const ModuleData *moduleData);
	virtual NameKeyType getModuleNameKey() const;
	virtual void *vslot13() { return static_cast<Rva004CB51CInterface *>(this); }
	virtual void *vslot14() { return static_cast<Rva004CB51CInterface *>(this); }
	virtual bool rva004CB3F8(int index, Rva002C99FB *out);
	virtual bool rva004CB48A(const AsciiString &name, Rva002C99FB *out);
	virtual bool rva004CB51C(int *out);
protected:
	virtual void xfer(Xfer *xfer);
};

// ??0UpgradeSoundSelectorClientBehavior@@QAE@PAVThing@@PBVModuleData@@@Z @0x00252CB5
UpgradeSoundSelectorClientBehavior::UpgradeSoundSelectorClientBehavior(Thing *thing, const ModuleData *moduleData) :
	Rva00252B68(thing, moduleData)
{
}

// ?xfer@UpgradeSoundSelectorClientBehavior@@MAEXPAVXfer@@@Z @0x004CBF58: slot 3, the base then Version1, folded with DrawModule's.
void UpgradeSoundSelectorClientBehavior::xfer(Xfer *xfer)
{
	Rva00252B68::xfer(xfer);
	xfer->Version1();
}
