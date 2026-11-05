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
// retail's [ebp+8], while Version lands at the slot base. The canonical DrawModule
// layout is 12 bytes, placing the bone-index list at +0x0C.
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

#include "../../../../../../GameEngine/Include/GameLogic/Module/DrawModule.h"

struct Coord3D;
class RadiusDecal
{
public:
	~RadiusDecal();
	void setPosition(const Coord3D &pos);
	void update();
	void rva00330F7D(Xfer *xfer);
};

class W3DTornadoDraw : public DrawModule
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
