// cl: /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmelist /Ireference/shims/bfmealloc
// stlport
// ??0AssaultTransportAIUpdate@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x0048F5A3.

// The base constructor is 0x0026E9BD. Retail installs vptrs at +0/+0x0C/+0x10/+0x20/+0x24,
// and replaces the +0x3E4 interface table 0x00C1C780 with 0x00C4CC88.
// The instance factory at 0x0024D263 is the single raw caller.
#include "../../../../Common/GameLogicObjectLookupView.h"
enum NameKeyType;
enum UpdateSleepTime { UPDATE_SLEEP_NONE = 1 };
enum CommandSourceType { CMD_FROM_PLAYER = 0 };

#include "../../../../../Include/GameLogic/Module/UpdateModule.h"

struct AICommandParms;
struct Coord3D;
class Coord3DBase
{
public:
    float x;
    float y;
    float z;
};

enum AssaultStateTypes
{
    IDLE
};

class AICommandInterface
{
public:
    virtual void aiDoCommand(const AICommandParms *parms) = 0;
    void rva0026C347(Object *target, CommandSourceType source);
    void rva0026C2D9(Object *target, int range, CommandSourceType source);
};

class Rva0026E836_M4
{
public:
    virtual void onCollide(Object *other, const Coord3D *loc, const Coord3D *normal);
};

class AIUpdateInterface : public UpdateModule, public AICommandInterface, public Rva0026E836_M4
{
public:
    AIUpdateInterface(Thing *thing, const ModuleData *moduleData);
    virtual void xfer(Xfer *xfer);
    virtual void aiDoCommand(const AICommandParms *parms);
    virtual UpdateSleepTime update();
    virtual void onCollide(Object *other, const Coord3D *loc, const Coord3D *normal);
    unsigned char m_pad28[0x3C1 - 0x28];
    unsigned char m_byte3C1;
    unsigned char m_pad3C2[0x3E4 - 0x3C2];
protected:
    virtual ~AIUpdateInterface();
    void wakeUpNow();
};

class AssaultTransportAIInterface
{
public:
    virtual void beginAssault(const Object *designatedTarget) const = 0;
};

class AssaultTransportAIUpdate : public AIUpdateInterface, public AssaultTransportAIInterface
{
public:
    AssaultTransportAIUpdate(Thing *thing, const ModuleData *moduleData);
    virtual ~AssaultTransportAIUpdate();
    virtual NameKeyType getModuleNameKey() const;
    virtual void beginAssault(const Object *designatedTarget) const;
    virtual void aiDoCommand(const AICommandParms *parms);
    virtual UpdateSleepTime update();
    void Rva0048F365Helper() throw();
    bool isAttackPointless() const;
    bool rva0048F64E(void *arg);
    void Rva0048F690Helper();
    void Rva0048F6EEHelper();
protected:
    virtual void xfer(Xfer *xfer);
private:
    ObjectID m_memberIDs[10]; // +0x3E8
    bool m_memberHealing[10]; // +0x410
    unsigned char m_array41A[10]; // +0x41A
    Coord3DBase m_attackMoveGoalPos; // +0x424
    mutable ObjectID m_designatedTarget; // +0x430
    AssaultStateTypes m_state; // +0x434
    unsigned int m_framesRemaining; // +0x438
    int m_currentMembers; // +0x43C
    bool m_isAttackMove; // +0x440
    bool m_isAttackObject; // +0x441
    bool m_bfmeFlag442; // +0x442
};

// ??0AssaultTransportAIUpdate@@QAE@PAVThing@@PBVModuleData@@@Z @0x0048F5A3
AssaultTransportAIUpdate::AssaultTransportAIUpdate(Thing *thing, const ModuleData *moduleData)
    : AIUpdateInterface(thing, moduleData)
{
    m_currentMembers = 0xA;
    Rva0048F365Helper();
}
