// cl: /DNDEBUG /MD
//
// ??0ModelConditionSoundSelectorClientBehavior@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x00254B82, 42 bytes. The rowed Rva00252B68 base, the
// interface base's own table (retail's folded 0x00BE2B78, three pure slots), then the compiler's two table
// installs: 0x00BF3220 at +0 and 0x00BF3210 at +0x0C. The instance factory 0x00255C26 is its sole raw caller.

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

class Rva00BF3210Iface
{
public:
	virtual bool rva004CAC2F(int idx, Rva002C99FB *dest) = 0;
	virtual bool rva004CAC9C(const AsciiString &key, Rva002C99FB *dest) = 0;
	virtual bool rva004CABCD(int *dest) = 0;
};

// Retail's tables: 0x00BF3220 (19 slots) and 0x00BF3210 at +0x0C.
class ModelConditionSoundSelectorClientBehavior : public Rva00252B68, public Rva00BF3210Iface
{
public:
	ModelConditionSoundSelectorClientBehavior(Thing *thing, const ModuleData *moduleData);
	virtual NameKeyType getModuleNameKey() const;
	virtual void *vslot13() { return static_cast<Rva00BF3210Iface *>(this); }
	virtual void *vslot14() { return static_cast<Rva00BF3210Iface *>(this); }
	virtual bool rva004CAC2F(int idx, Rva002C99FB *dest);
	virtual bool rva004CAC9C(const AsciiString &key, Rva002C99FB *dest);
	virtual bool rva004CABCD(int *dest);
protected:
	virtual void xfer(Xfer *xfer);
};

// ??0ModelConditionSoundSelectorClientBehavior@@QAE@PAVThing@@PBVModuleData@@@Z @0x00254B82
ModelConditionSoundSelectorClientBehavior::ModelConditionSoundSelectorClientBehavior(Thing *thing, const ModuleData *moduleData) :
	Rva00252B68(thing, moduleData)
{
}

// ?xfer@ModelConditionSoundSelectorClientBehavior@@MAEXPAVXfer@@@Z @0x004CBF58: slot 3, the base then Version1, folded with DrawModule's.
void ModelConditionSoundSelectorClientBehavior::xfer(Xfer *xfer)
{
	Rva00252B68::xfer(xfer);
	xfer->Version1();
}
