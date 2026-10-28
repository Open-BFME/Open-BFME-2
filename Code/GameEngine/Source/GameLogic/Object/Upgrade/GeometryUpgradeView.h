// GeometryUpgradeView.h: the one view of GeometryUpgrade, its UpgradeModule
// bases and the engine classes its bodies touch, shared by GeometryUpgrade.cpp
// and the donors that merge into it. Layout: BehaviorModule +0 (vptr,
// m_moduleData +4, m_object +8), BehaviorModuleInterface +0xC, UpgradeMux
// +0x10 (state +0x14), UpgradeTail +0x18, upgrade name +0x1C (size 0x20 per
// the rowed friend_newModuleInstance 0x0025060A); retail ctor 0x004B6A5E
// stores the four vptrs at +0/+0xC/+0x10/+0x18.
#ifndef GEOMETRYUPGRADEVIEW_H
#define GEOMETRYUPGRADEVIEW_H

#include "Common/Snapshot.h"

#include <vector>

#include "ascii_string.h"

// A declaration-only specialization stops the unit emitting its own
// vector<AsciiString> dtor COMDAT, so the call binds the kept copy.
namespace _STL {
template <> vector<AsciiString, allocator<AsciiString> >::~vector();
template <> _Vector_base<AsciiString, allocator<AsciiString> >::~_Vector_base();
template <> void _STLP_alloc_proxy<AsciiString*, AsciiString, allocator<AsciiString> >::deallocate(AsciiString*, size_t);
template <> void allocator<AsciiString>::deallocate(AsciiString*, size_t) const;
}
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
#include "../../../../Include/Common/BfmeXfer.h"

class Thing;

class ModuleData;

class BfmeStrF9 { void *data; };

class Rva00406F9C
{
public:
    bool rva00406F9C(const void *other);
private:
    unsigned words[32];
};

class Rva001EAE6FHelper { public: Rva001EAE6FHelper *clear80(); };

class GeometryUpgradeMask : public Rva00406F9C
{
public:
    GeometryUpgradeMask() { ((Rva001EAE6FHelper *)this)->clear80(); }
};

struct BfmeShapeE15
{
    char pad[0x1C];
    AsciiString name;
    bool active;
    char tail[3];
};

class BfmeObjE15 { public: BfmeShapeE15 *getGeometryShape(int index); };

class BfmeObjF9
{
public:
    void setFlag(const BfmeStrF9 &name, char flag);
    char pad[0x2C];
    BfmeShapeE15 *begin, *end;
};

template <int N> class GeometrySlots : public GeometrySlots<N - 1>
{
public:
    virtual void gap(char (*)[N]) = 0;
};

template <> class GeometrySlots<0> {};

class GeometryDrawModule : public GeometrySlots<53>
{
public:
    virtual void reset(const char *text) = 0;
    virtual void mesh(const char *text, bool flag) = 0;
};

class DrawModule;

class Drawable
{
public:
    DrawModule **getDrawModules();
};

class Rva002B224BDwordField
{
public:
    int get() const;
};

class Thing
{
public:
    Drawable *getDrawable() const;
};

class Player
{
public:
    char pad[0x13C];
    Rva00406F9C upgrades;
};

class Object
{
public:
    Player *getControllingPlayer() const;
    void rva0028AB75(bool flag);
    char pad[0xA8];
    BfmeObjF9 geometry;
    char padDC[0x284 - 0xDC];
    Rva00406F9C upgrades;
};

class Pathfinder
{
public:
    void RemoveObjectFromPathfindMap(Object *);
    void AddObjectToPathfindMap(Object *);
};

class AI
{
public:
    char pad[0x10];
    Pathfinder *pathfinder;
};

extern AI *TheAI;

// The upgrade's ModuleData (size 0x13C via factory 0x00250642): the
// ShowGeometry/HideGeometry name lists at +0x118/+0x124 and the
// WallBoundsMesh, RampMesh1 and RampMesh2 strings at +0x130/+0x134/+0x138
// (field table 0x00858918). Retail dtor 0x004B6F81 stores no derived vptr,
// so the class is novtable over the canonical Snapshot.
class __declspec(novtable) GeometryUpgradeModuleData : public Snapshot
{
public:
	virtual ~GeometryUpgradeModuleData();

	// The inherited ModuleData state is opaque here; members still start at +0x118.
	unsigned char m_moduleDataState[0x118 - sizeof(Snapshot)];
	_STL::vector<AsciiString> m_showGeometry; // +0x118
	_STL::vector<AsciiString> m_hideGeometry; // +0x124
	AsciiString m_wallBoundsMesh; // +0x130
	AsciiString m_rampMesh1; // +0x134
	AsciiString m_rampMesh2; // +0x138
};

enum NameKeyType
{
	NK_UNKNOWN = 0
};

class Xfer;

class BehaviorModule
{
protected:
	Object *getObject() const { return m_object; }
public:
	BehaviorModule(Thing *thing, const ModuleData *moduleData);
	virtual ~BehaviorModule();
protected:
	const ModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
};

struct BehaviorModuleInterface { virtual void iface() {} };

class UpgradeMux
{
public:
	UpgradeMux();
	virtual bool executed() const = 0;
	virtual void f1() = 0; virtual void f2() = 0; virtual void f3() = 0;
	virtual void f4() = 0; virtual void f5() = 0; virtual void f6() = 0;
	virtual void f7() = 0;
	virtual void upgradeRemovalImplementation() = 0;
	virtual void setExecuted(bool flag) = 0;
	virtual void upgradeImplementation() = 0;
	virtual void masks(GeometryUpgradeMask &set, GeometryUpgradeMask &clear) = 0;
	int state;
};

struct UpgradeTail { virtual void iface() {} };

class UpgradeModule : public BehaviorModule, public BehaviorModuleInterface, public UpgradeMux, public UpgradeTail
{
public:
	UpgradeModule(Thing *thing, const ModuleData *moduleData);
	void rva004CE4A0();
	void rva004CE4A8();
protected:
	virtual ~UpgradeModule(); // retail ??1UpgradeModule@@MAE@XZ, 0x0046089D
	virtual void xfer(Xfer *xfer);
};

class GeometryUpgrade : public UpgradeModule
{
public:
	GeometryUpgrade(Thing *thing, const ModuleData *moduleData);
	virtual ~GeometryUpgrade();
	virtual NameKeyType getModuleNameKey() const;
	virtual void upgradeRemovalImplementation();
	virtual void upgradeImplementation();
	const GeometryUpgradeModuleData *getData() const { return (const GeometryUpgradeModuleData *)m_moduleData; }
	void rva004B6B04(BfmeObjF9 *, void *vector, char flag);
protected:
	virtual void xfer(Xfer *xfer);
private:
	AsciiString m_upgradeName; // +0x1C
};

#endif
