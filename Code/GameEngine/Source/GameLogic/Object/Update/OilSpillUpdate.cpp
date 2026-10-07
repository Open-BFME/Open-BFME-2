// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /GX /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc
// stlport
//
// OilSpillUpdate (BFME 2): the update.
//
// Target facts. OilSpillUpdate derives from FireWeaponUpdate (its update
// 0x0048BEE8 is slot 0 of the +0x10 vftable 0x00C4C18C the base ctor row
// 0x0048C0C5 stores, and is called first) and adds a vector<Coord3D> of
// breadcrumb positions at +0x2C (ctor row 0x0048C1F7, size 0x38 from the
// rowed factory). Its module data (ctor row 0x0048C16C, table 0x00C4C2A8)
// holds BreadcrumbName at +0x10, IgnitionWeaponName at +0x14,
// IgnitionWeaponSpacing at +0x18 and OilSpillFX at +0x1C. update is slot 0
// of the +0x10 UpdateModuleInterface vftable 0x00C4C374 the ctor stores.
// 0x00E027B8 is TheBuildAssistant (slot 14 takes the builder, template,
// position, angle and owning player, as Zero Hour's buildObjectNow).
//
// Codegen notes. The breadcrumb test is a positive condition on a flag
// (fcomi with the length on top and jb past the drop) and the drop is one
// block, which lets MSVC push esi only around it. pos lives at function
// scope so its copy stores follow each load. The distance is
// GetLength2D on the temporary operator- returns: all three subtractions
// precede the stores, which a named delta (address taken) cannot give.
// The two null checks are separate statements; joined with || the return
// block moves to the end.
// Retail keeps one unsigned max, RVA 0x00013740 (the vendored STLport row). This unit's
// flags compile a different copy, and retail kept another unit's. This unit-local
// overload keeps the inlined code and offers the link no second copy.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <vector>
#include "ascii_string.h"

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;

class Thing;
class ModuleData;
class Object;
class Player;
class ThingTemplate;
class Matrix3D;
class FXList;

// class-gate: allow Coord3D the canonical data-only header cannot declare the out-of-line GetLength2D (rowed 0x0000599F) or the copy constructor push_back instantiates with; same three floats
struct Coord3D
{
	Real x;
	Real y;
	Real z;

	Coord3D() {}
	Coord3D(Real ax, Real ay, Real az) : x(ax), y(ay), z(az) {}
	Coord3D(const Coord3D &that) throw();
	Real GetLength2D() const;
	void set(const Coord3D *a) { x = a->x; y = a->y; z = a->z; }
	void set(Real ax, Real ay, Real az) { x = ax; y = ay; z = az; }
};

inline Coord3D operator-(const Coord3D &a, const Coord3D &b)
{
	return Coord3D(a.x - b.x, a.y - b.y, a.z - b.z);
}

namespace _STL {
template <> void _Construct<Coord3D, Coord3D>(Coord3D *, const Coord3D &);
}

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3FFFFFFF
};

class Object
{
public:
	const Coord3D *getPosition() const { return &m_position; }
	Player *getControllingPlayer() const;

private:
	char m_unknown00[0x38];
	Coord3D m_position; // +0x38
};

class ThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
};

extern ThingFactory *TheThingFactory;

// TheBuildAssistant.
class Rva00A027B8
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13();
	virtual Object *buildObjectNow(Object *constructorObject, const ThingTemplate *what,
		const Coord3D *pos, Real angle, Player *owningPlayer); // +0x38
};

extern Rva00A027B8 *g_00A027B8;

class FXList
{
public:
	static void doFXPos(const FXList *fx, const Coord3D *primary, const Matrix3D *primaryMtx,
		Real primarySpeed, const Coord3D *secondary);
};

class FireWeaponUpdateModuleData
{
	char m_unknown00[0x10];
};

class OilSpillUpdateModuleData : public FireWeaponUpdateModuleData
{
public:
	AsciiString m_breadcrumbName; // +0x10
	AsciiString m_ignitionWeaponName; // +0x14
	Real m_ignitionWeaponSpacing; // +0x18
	const FXList *m_oilSpillFX; // +0x1C
};

class BehaviorModuleBase
{
public:
	virtual void behaviorModuleBaseAnchor();
	const ModuleData *m_moduleData;
	Object *m_object;
};

class BehaviorModuleOther
{
public:
	virtual void behaviorModuleOtherAnchor();
};

class BehaviorModule : public BehaviorModuleBase, public BehaviorModuleOther
{
public:
	Object *getObject() const { return m_object; }
};

class UpdateModuleInterface
{
public:
	virtual UpdateSleepTime update();
};

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
protected:
	unsigned m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_bfmeReserved;
};

class FireWeaponUpdate : public UpdateModule
{
public:
	virtual UpdateSleepTime update();

private:
	char m_unknown20[0x0C];
};

class OilSpillUpdate : public FireWeaponUpdate
{
public:
	virtual UpdateSleepTime update();

protected:
	const OilSpillUpdateModuleData *getOilSpillUpdateModuleData() const
	{
		return (const OilSpillUpdateModuleData *)m_moduleData;
	}

private:
	_STL::vector<Coord3D> m_breadcrumbs; // +0x2C
};

// ?update@OilSpillUpdate@@UAE?AW4UpdateSleepTime@@XZ @0x0048C30E 263B
// (Ghidra boundary; slot 0 of vftable 0x00C4C374). Runs the base update,
// then drops a breadcrumb object where the object stands once it is at least
// IgnitionWeaponSpacing (2D) from the last one, plays OilSpillFX there and
// records the position.
UpdateSleepTime OilSpillUpdate::update()
{
	FireWeaponUpdate::update();
	const OilSpillUpdateModuleData *data = getOilSpillUpdateModuleData();
	if (data == NULL)
		return UPDATE_SLEEP_FOREVER;
	if (getObject() == NULL)
		return UPDATE_SLEEP_FOREVER;
	Coord3D pos;
	const Coord3D *p = getObject()->getPosition();
	if (p != NULL)
	{
		pos.set(p);
		Int count = m_breadcrumbs.size();
		Bool drop = true;
		if (count > 0)
		{
			const Coord3D &last = m_breadcrumbs[count - 1];
			drop = (pos - last).GetLength2D() >= data->m_ignitionWeaponSpacing;
		}
		if (drop)
		{
			const ThingTemplate *tmpl = TheThingFactory->findTemplate(data->m_breadcrumbName);
			if (tmpl)
			{
				Object *obj = getObject();
				g_00A027B8->buildObjectNow(obj, tmpl, &pos, 0.0f, obj->getControllingPlayer());
				FXList::doFXPos(data->m_oilSpillFX, &pos, NULL, 0.0f, NULL);
			}
			m_breadcrumbs.push_back(pos);
		}
	}
	return UPDATE_SLEEP_NONE;
}
