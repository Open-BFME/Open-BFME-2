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
class BfmeObjF9
{
public:
    void setFlag(const BfmeStrF9 &name, char flag);
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
class Object
{
public:
    void rva0028AB75(bool flag);
    char pad[0xA8];
    BfmeObjF9 geometry;
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
    virtual void rva004B6C8A() = 0;
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
    // The apply override is reconstructed separately after removal verifies.
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
