// ?upgradeImplementation@GeometryUpgrade@@UAEXXZ
// partial score=0.94 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /MD /DNDEBUG /EHsc
// BFME1 donor874e38488 game/.../GeometryUpgradeRemoveUpgrade.cpp supplies
// removal semantics and the module/drawable loop. BFME2 ctor4B6A5E proves
// base footprint1C and its four vptrs0/C/10/18, with string at1C. Native
// module-data ctor4B6EE2 proves show/hide vectors118/124 and strings130/134/138.
// Native callers retain primary ECX for flag-helper4B6B04 even though that
// helper does not read this. Target calls and offsets, not donor bytes,
// establish the adaptations here. Original override names remain neutral.
#include "ascii_string.h"
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
class BfmeObjE15 { public: BfmeShapeE15 *bfmeAtE15(int index); };
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
struct GeometryNameVector
{
    BfmeStrF9 *begin, *end, *endStorage;
    int size() const { return end - begin; }
};
struct GeometryUpgradeModuleData
{
    char pad[0x118];
    GeometryNameVector show, hide;
    AsciiString wall, ramp, name;
};
class BehaviorModule
{
public:
    virtual ~BehaviorModule();
protected:
    Object *getObject() const { return m_object; }
    const ModuleData *m_moduleData;
    Object *m_object;
};
struct BehaviorModuleInterface { virtual void iface(); };
class UpgradeMux
{
public:
    virtual bool executed() const = 0;
    virtual void f1() = 0; virtual void f2() = 0; virtual void f3() = 0;
    virtual void f4() = 0; virtual void f5() = 0; virtual void f6() = 0;
    virtual void f7() = 0;
    virtual void rva004B6B29() = 0;
    virtual void setExecuted(bool flag) = 0;
    virtual void upgradeImplementation() = 0;
    virtual void masks(GeometryUpgradeMask &set, GeometryUpgradeMask &clear) = 0;
    int state;
};
struct UpgradeTail { virtual void iface(); };
class UpgradeModule : public BehaviorModule, public BehaviorModuleInterface, public UpgradeMux, public UpgradeTail
{
public:
    void rva004CE4A0();
    void rva004CE4A8();
};
class GeometryUpgrade : public UpgradeModule
{
public:
    virtual void rva004B6B29();
    virtual void upgradeImplementation();
    const GeometryUpgradeModuleData *getData() const { return (const GeometryUpgradeModuleData *)m_moduleData; }
    void rva004B6B04(BfmeObjF9 *, void *vector, char flag);
private:
    AsciiString m_upgradeName;
};
void GeometryUpgrade::rva004B6B29()
{
    if (!executed())
        return;
    rva004CE4A8();
    Object *object = m_object;
    TheAI->pathfinder->RemoveObjectFromPathfindMap(object);
    GeometryDrawModule **modules = (GeometryDrawModule **)((const Thing *)object)->getDrawable()->getDrawModules();
    for (; modules[0]; ++modules)
    {
        modules[0]->reset(0);
        modules[0]->mesh(0, false);
        modules[0]->mesh(0, true);
    }
    const GeometryUpgradeModuleData *data = (const GeometryUpgradeModuleData *)m_moduleData;
    rva004B6B04(&object->geometry, (void *)&data->hide, 0);
    rva004B6B04(&object->geometry, (void *)&data->show, 0);
    if (!m_upgradeName.isEmpty())
        object->geometry.setFlag((const BfmeStrF9 &)m_upgradeName, 1);
    TheAI->pathfinder->AddObjectToPathfindMap(object);
    object->rva0028AB75(false);
    setExecuted(false);
}

class Module;
class WallUpgradeUpdate
{
public:
    static Module *rva004AB1F5(Object *);
    void rva004AB57E();
};
// Retail 4B6C8A..4B6EE2. Target applies the mux's two 128-byte masks only
// after rejecting clear-mask overlaps in Object+284 and Player+13C. Three
// optional module-data strings address draw-module slots D4/D8; geometry
// records36 at Object+A8 begin2C/end30 contribute an active name at+1C.
// Donor removal establishes the inverse operation; the extended mask checks,
// three strings, geometry records and WallUpgradeUpdate route are target facts.
// ?upgradeImplementation@GeometryUpgrade@@UAEXXZ present-unmatched
void GeometryUpgrade::upgradeImplementation()
{
    GeometryUpgradeMask setMask;
    GeometryUpgradeMask clearMask;
    masks(setMask, clearMask);
    Object *object = getObject();
    if (object->upgrades.rva00406F9C(&clearMask))
        return;
    Player *player = object->getControllingPlayer();
    if (player->upgrades.rva00406F9C(&clearMask))
        return;
    rva004CE4A0();
    const GeometryUpgradeModuleData *data = getData();
    struct PredicateBytes { char unused; bool wall, name, ramp; } predicates;
    predicates.wall = data->wall.getLength() > 0;
    predicates.ramp = data->ramp.getLength() > 0;
    predicates.name = data->name.getLength() > 0;
    if (predicates.wall || predicates.ramp || predicates.name)
    {
        const char *wall = predicates.wall ? data->wall.str() : 0;
        const char *ramp = predicates.ramp ? data->ramp.str() : 0;
        const char *name = predicates.name ? data->name.str() : 0;
        GeometryDrawModule **modules = (GeometryDrawModule **)((const Thing *)object)->getDrawable()->getDrawModules();
        for (; modules[0]; ++modules)
        {
            if (wall)
                modules[0]->reset(wall);
            if (ramp)
                modules[0]->mesh(ramp, false);
            if (name)
                modules[0]->mesh(name, true);
        }
    }
    if (predicates.wall || predicates.ramp || predicates.name || data->hide.size() != 0 || data->show.size() != 0)
    {
        BfmeObjF9 *geometry = &object->geometry;
        int count = geometry->end - geometry->begin;
        for (int i = 0; i < count; ++i)
        {
            BfmeShapeE15 *shape = ((BfmeObjE15 *)geometry)->bfmeAtE15(i);
            if (shape->active)
                m_upgradeName = shape->name;
        }
        rva004B6B04(geometry, (void *)&data->hide, 0);
        rva004B6B04(geometry, (void *)&data->show, 1);
        object->rva0028AB75(true);
        WallUpgradeUpdate *wallUpgrade = (WallUpgradeUpdate *)WallUpgradeUpdate::rva004AB1F5(object);
        if (wallUpgrade)
            wallUpgrade->rva004AB57E();
    }
}
