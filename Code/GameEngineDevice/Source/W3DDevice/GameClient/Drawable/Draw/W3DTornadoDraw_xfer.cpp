// ?xfer@W3DTornadoDraw@@MAEXPAVXfer@@@Z
// cl: /MD
// stlport
//
// ?xfer@W3DTornadoDraw@@MAEXPAVXfer@@@Z @0x000D1776 68B
// Slot 3 (offset 0x0C) of the W3DTornadoDraw vtable (class of rowed
// ??1W3DTornadoDraw@@UAE@XZ 0x000D18AB). Body: base DrawModule::xfer via rowed
// 0x004CBF58, then Xfer::Version(1,1) through the Version operator== slot
// 0x28, then the +0x0C bone-index list drained through the 0x00330F7D decal
// xfer. The 2-byte Version temp must be a real Version object: a struct of two
// bools places it at [ebp+0x0A] (tail of the dead argument slot) instead of
// retail's [ebp+8], while Version lands at the slot base. Layout from the
// matched dtor TU: Rva000B19A1 intermediate carries the 8-byte pad that puts
// the list at +0x0C.
#include <list>

class Thing;
class ModuleData;
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
#include "../../../../../../GameEngine/Include/Common/BfmeXfer.h"

#include "../../../../../../GameEngine/Include/Common/XferVersion.h"

class DrawModule
{
protected:
	virtual void xfer(Xfer *xfer);
};

class RadiusDecal
{
public:
	void rva00330F7D(Xfer *xfer);
};

class Rva000B19A1 : public DrawModule
{
public:
	Rva000B19A1(Thing *thing, const ModuleData *moduleData);
	virtual ~Rva000B19A1();

private:
	unsigned char m_pad04[8];
};

class W3DTornadoDraw : public Rva000B19A1
{
public:
	W3DTornadoDraw(Thing *thing, const ModuleData *moduleData);

protected:
	virtual void xfer(Xfer *xfer);

private:
	_STL::list<int> m_boneIndices;
};

void W3DTornadoDraw::xfer(Xfer *xfer)
{
	DrawModule::xfer(xfer);
	Xfer::Version version(1, 1);
	*xfer == version;
	for (_STL::list<int>::iterator it = m_boneIndices.begin(); it._M_node != m_boneIndices.end()._M_node; ++it) {
		RadiusDecal *decal = reinterpret_cast<RadiusDecal *>(*it);
		decal->rva00330F7D(xfer);
	}
}
