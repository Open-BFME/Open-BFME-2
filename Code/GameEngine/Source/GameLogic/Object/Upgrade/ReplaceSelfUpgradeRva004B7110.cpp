// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /ICode/Libraries/Include/Lib
//
// ?rva004CE2B0@ReplaceSelfUpgrade@@UAE_NPAVRva00406F9C@@@Z, retail
// 0x004B7110..0x004B74CB (955B), thiscall ret 4; slot 2 of the UpgradeMux
// vtable 0x00858AC8 that the rowed ReplaceSelfUpgrade ctor 0x004B7045 installs
// at +0x10 (so `this` is that subobject: module data at -0x0C, object at -0x08).
//
// ReplaceSelfUpgrade's override of the UpgradeMux check (pinned base
// 0x004CE2B0, called first): with the base satisfied and the object not in
// status 2 unless also in status 0x14, every template named by the module
// data's list (+0x118) must exist; the replacements are laid out in a line
// along the perpendicular of the object's facing, starting their summed +0xC8
// lengths out from the object. For each one, objects found within three
// times the template's +0xB0 radius through the template-geometry filter
// (0x0027C2C9) linked to the kind-of 0x96/0x9C filter (0x003959FA) are
// tolerated only when the template is kind-of 28 and they are not, and every
// geometry shape's footprint point must lie within TheGlobalData +0xA70 of
// the object's height.
//
// Evidence (target): WorldBuilder twin 0x0123F700 (ThingFactory::
// findTemplateInternal, Thing::getUnitDirectionVector2D, Coord3D::scale/add,
// PartitionFilter::And, GeometryInfo::getGeometryShape, fabs); callees are
// rowed or pinned under the spellings used here (several are still
// address-derived views: Rva00406F9C, Rva000421C8, BfmeWideResult,
// BfmeObjE15, Rva0087E900Shape).
//
// Codegen (from the bytes): retail stores no EH state between the two filter
// temporaries, so the geometry filter's constructor is nothrow here; the
// facing is copied and swapped in place (WB's -y / x idiom); the shape is
// fetched before the footprint query's arguments; the position add goes
// through an owner local, and the kind-of tests are plain word tests.

#include "ascii_string.h"
#include "Coord3D.h"
#include <math.h>
#include "../../../Common/PartitionRangeQueryCallView.h"

typedef int Int;
typedef bool Bool;
typedef float Real;

namespace _STL
{
template <class T> class allocator
{
};
template <class T, class A> class vector
{
public:
	vector(const vector &other);
	~vector();
	unsigned int size() const { return _M_finish - _M_start; }
	T &operator[](unsigned int n) { return *(_M_start + n); }
	T *_M_start;
	T *_M_finish;
	T *_M_end_of_storage;
};
}
typedef _STL::vector<AsciiString, _STL::allocator<AsciiString> > AsciiStringVector;

enum ObjectStatusTypes
{
	OBJECT_STATUS_NONE = 0
};

class ThingTemplate
{
public:
	int isKindOf28() const { return m_kindOf[0] & 0x10000000; }
	const class GeometryInfo &getTemplateGeometryInfo() const { return *(const GeometryInfo *)m_geometry; }
	Real getB0() const { return m_b0; }
	Real getC8() const { return m_c8; }
private:
	unsigned char m_pad000[0xA0];
	unsigned char m_geometry[0x10];			// +0xA0 GeometryInfo
	Real m_b0;					// +0xB0
	unsigned char m_padB4[0xC8 - 0xB4];
	Real m_c8;					// +0xC8
	unsigned char m_padCC[0x118 - 0xCC];
	unsigned int m_kindOf[7];			// +0x118
};

class Thing
{
public:
	const Coord3D *getUnitDirectionVector2D() const;
};

class Object : public Thing
{
public:
	Bool testStatus(ObjectStatusTypes bit) const;
	const ThingTemplate *getTemplate() const { return m_template; }
	const Coord3D *getPosition() const { return &m_pos; }
	Real getOrientation() const { return m_orientation; }
private:
	unsigned char m_pad00[0x04];
	const ThingTemplate *m_template;		// +0x04
	unsigned char m_pad08[0x38 - 0x08];
	Coord3D m_pos;					// +0x38
	Real m_orientation;				// +0x44
};

class ThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
};
extern ThingFactory *TheThingFactory;

class TerrainLogic
{
public:
	virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4(); virtual void s5();
	virtual Real getGroundHeight(Real x, Real y, Coord3D *normal);	// slot 6
};
extern TerrainLogic *TheTerrainLogic;

class GlobalData
{
public:
	unsigned char m_pad000[0xA70];
	Real m_a70;					// +0xA70
};
extern GlobalData *TheWritableGlobalData;

// Footprint shapes of a GeometryInfo (0x24-byte records at +0x2C..+0x30).
struct Rva0087E900Coord
{
	Real x;
	Real y;
	Real z;
};
class Rva0087E900Shape
{
public:
	void rva006BE220(const Rva0087E900Coord *pos, Real angle, Rva0087E900Coord *result);
};
struct BfmeShapeE15;
class BfmeObjE15
{
public:
	BfmeShapeE15 *bfmeAtE15(Int index);
};
class GeometryInfo
{
public:
	Int getShapeCount() const { return (m_shapesLast - m_shapesFirst) / 0x24; }
	BfmeShapeE15 *getShape(Int index) const { return ((BfmeObjE15 *)this)->bfmeAtE15(index); }
private:
	unsigned char m_pad00[0x2C];
	const char *m_shapesFirst;			// +0x2C
	const char *m_shapesLast;			// +0x30
};

class BfmeFixedStorage0004543D			// KindOfMaskType
{
public:
	BfmeFixedStorage0004543D(Int init, Int bit1, Int bit2);
private:
	unsigned int m_bits[7];
};

// The (init, bit1, bit2) ctor 0x0006EE7A is rowed as Rva0006EE7A; a no-member
// view of the mask type so the temporary is built through that row.
struct Rva0006EE7A : BfmeFixedStorage0004543D { Rva0006EE7A(Int init, Int bit1, Int bit2); };

// The partition filter base (ctor 0x000421C8, vtable 0x007C26E0).
class Rva000421C8
{
public:
	Rva000421C8() : m_next(0) {}
	virtual ~Rva000421C8() {}
	virtual bool allow(Object *obj) = 0;
	virtual int getPlayerMask();
	Rva000421C8 *link(Rva000421C8 *next);	// 0x00625790
	Rva000421C8 *m_next;
};

class Rva003959FA : public Rva000421C8
{
public:
	Rva003959FA(const BfmeFixedStorage0004543D &kindOf);
	virtual bool allow(Object *obj);
private:
	unsigned int m_kindOf[7];
};

class Rva00261603Filter : public Rva000421C8
{
public:
	Rva00261603Filter(const Coord3D &pos, const GeometryInfo &geom, Real angle, Bool flag) throw();
	virtual bool allow(Object *obj);
private:
	Coord3D m_pos;
	const GeometryInfo *m_geom;
	Real m_angle;
	Bool m_flag;
};

extern PartitionManager *ThePartitionManager;

class Rva00406F9C;

class ReplaceSelfUpgradeModuleData
{
public:
	unsigned char m_pad000[0x118];
	AsciiStringVector m_replaceWith;		// +0x118
};

class Rva004B7110ModuleBase
{
public:
	virtual void b0();
protected:
	const ReplaceSelfUpgradeModuleData *m_moduleData;	// +0x04
	Object *m_object;				// +0x08
};

class Rva004B7110UpgradeInterface
{
public:
	virtual void u0();
};

class UpgradeMux
{
public:
	virtual void m0();
	virtual void m1();
	virtual Bool rva004CE2B0(Rva00406F9C *mask);	// slot 2
};

// The base check 0x004CE2B0 is rowed as Rva004CE2B0::rva004CE2B0 (non-virtual spelling).
class Rva004CE2B0
{
public:
	Bool rva004CE2B0(Rva00406F9C *mask);
};

class ReplaceSelfUpgrade : public Rva004B7110ModuleBase, public Rva004B7110UpgradeInterface, public UpgradeMux
{
public:
	virtual Bool rva004CE2B0(Rva00406F9C *mask);
};

static __forceinline void copyCoord(Coord3D &c, const Coord3D *a)
{
	c.x = a->x;
	c.y = a->y;
	c.z = a->z;
}

static __forceinline void scaleCoord(Coord3D &c, Real scale)
{
	c.x *= scale;
	c.y *= scale;
	c.z *= scale;
}

static __forceinline void addCoord(Coord3D &c, const Coord3D *a)
{
	c.x += a->x;
	c.y += a->y;
	c.z += a->z;
}

Bool ReplaceSelfUpgrade::rva004CE2B0(Rva00406F9C *mask)
{
	if (!((Rva004CE2B0 *)((char *)this + 0x10))->rva004CE2B0(mask)) // the UpgradeMux base at +0x10, no null check
		return false;

	Object *obj = m_object;
	if (obj->testStatus((ObjectStatusTypes)2) && !obj->testStatus((ObjectStatusTypes)0x14))
		return false;

	const ReplaceSelfUpgradeModuleData *data = m_moduleData;
	if (!data)
		return false;

	AsciiStringVector names = data->m_replaceWith;
	Int count = names.size();
	if (count == 0)
		return false;

	Coord3D pos;
	copyCoord(pos, m_object->getPosition());
	Real angle = m_object->getOrientation();

	Real totalLength = 0.0f;
	for (Int i = 0; i < count; i++)
	{
		const ThingTemplate *tmpl = ((ThingFactory *)TheThingFactory)->findTemplate(names[i]);
		if (!tmpl)
			return false;
		totalLength += tmpl->getC8();
	}

	Coord3D perp;
	copyCoord(perp, m_object->getUnitDirectionVector2D());
	Real t = -perp.y;
	perp.y = perp.x;
	perp.x = t;

	Coord3D cur;
	copyCoord(cur, &perp);
	scaleCoord(cur, totalLength);
	const Object *owner = m_object;
	addCoord(cur, owner->getPosition());
	Real height = pos.z;

	for (Int j = 0; j < count; j++)
	{
		const ThingTemplate *tmpl = ((ThingFactory *)TheThingFactory)->findTemplate(names[j]);

		Coord3D step;
		copyCoord(step, &perp);
		scaleCoord(step, -tmpl->getC8());
		addCoord(cur, &step);

		const GeometryInfo &geom = tmpl->getTemplateGeometryInfo();
		BfmeWideResult iter = ThePartitionManager->iterateObjectsInRange(&pos, tmpl->getB0() * 3.0f, 3,
			Rva00261603Filter(pos, geom, angle, true).link(&Rva003959FA(Rva0006EE7A(0, 0x96, 0x9C))), 0);

		for (Object *other = iter.next(); other; other = iter.next())
		{
			if (!tmpl->isKindOf28() || other->getTemplate()->isKindOf28())
				return false;
		}

		Int shapes = geom.getShapeCount();
		if (shapes > 0)
		{
			for (Int k = 0; k < shapes; k++)
			{
				Rva0087E900Shape *shape = (Rva0087E900Shape *)geom.getShape(k);
				shape->rva006BE220((const Rva0087E900Coord *)&cur, angle, (Rva0087E900Coord *)&step);
				if (fabs(TheTerrainLogic->getGroundHeight(step.x, step.y, 0) - height) > TheWritableGlobalData->m_a70)
					return false;
			}
		}

		addCoord(cur, &step);
	}
	return true;
}
