// cl: /DNDEBUG /MD
//
// ?getClearanceTestGeometryCenter@ClearanceTestingSlowDeathBehavior@@UAEXPAUCoord3D@@@Z @0x00483DA4 84B.
// Target evidence: the only reference to this body is slot 1 of the vtable
// 0x00C49D70 that the matched ClearanceTestingSlowDeathBehavior dtor 0x00483C35 installs at +0x50,
// the last interface base of this behavior class (vptrs at +0, +0xC, +0x10,
// +0x20, +0x24, +0x50 as the dtor stores them); the slot's name is not
// established, hence the address name. cl 7.1 compiles an override of a
// non-primary base's virtual with the base subobject's this and folds the
// adjustment into the member accesses: module data (+4) and object (+8) are
// read as [ecx-0x4C] and [ecx-0x48]. Body: without an object the out
// coordinate is zeroed; otherwise the module data's Coord3D at +0x1EC is
// transformed by the object (Thing::transformPoint 0x0030A812, pinned from
// this call site) into a temporary copied field by field into out (retail
// shares the z store between the two paths).
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
void ClearanceTestingSlowDeathBehavior::getClearanceTestGeometryCenter(Coord3D *out)
{
	const Rva00483C35ModuleData *md = m_moduleData;
	Thing *obj = m_object;
	if (obj == 0)
	{
		out->x = 0.0f;
		out->y = 0.0f;
		out->z = 0.0f;
	}
	else
	{
		Coord3D tmp;
		obj->transformPoint(&md->m_clearanceGeometryOffset, &tmp);
		out->x = tmp.x;
		out->y = tmp.y;
		out->z = tmp.z;
	}
}
