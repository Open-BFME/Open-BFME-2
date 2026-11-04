// cl: /DNDEBUG /MD /Ireference/shims/moduledata
// AODCrushCollide destructor pair: retail RVAs 0x004BBEDD (32B), 0x004BC050 (28B).
// Shared UpdateModule supplies the primary/+0x0C/+0x10 bases; CrushCollide
// contributes the collide interface at +0x20, as the matched constructor proves.
enum NameKeyType
{
	NK_UNKNOWN = 0
};
enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3fffffff
};
enum ObjectID;
class Thing;
class ModuleData;
class Xfer;
class Object;
struct Coord3D;
#include "../../../../Include/GameLogic/Module/BehaviorModule.h"
#include "../../../../Include/GameLogic/Module/UpdateModule.h"
class __declspec(novtable) CollideModuleInterface
{
public:
	virtual void onCollide(Object *, const Coord3D *, const Coord3D *) = 0;
};
class __declspec(novtable) CrushCollide : public UpdateModule, public CollideModuleInterface
{
public:
	virtual ~CrushCollide() {}

protected:
	unsigned int m_24;
	ObjectID m_28;
	bool m_2C;
};
class AODCrushCollide : public CrushCollide
{
public:
	AODCrushCollide(Thing *thing, const ModuleData *moduleData);
	virtual ~AODCrushCollide();
	virtual NameKeyType getModuleNameKey() const;
	virtual CollideModuleInterface *getCollide() { return this; }
	virtual UpdateSleepTime update();
	virtual void onCollide(Object *, const Coord3D *, const Coord3D *);

protected:
	virtual void xfer(Xfer *xfer);
};

AODCrushCollide::~AODCrushCollide()
{
}
