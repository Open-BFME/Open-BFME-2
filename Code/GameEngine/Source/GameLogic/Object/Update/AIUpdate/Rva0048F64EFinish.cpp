// ?rva0048F64E@AssaultTransportAIUpdate@@QAE_NPAX@Z
// cl: /DNDEBUG /MD
//
// ?rva0048F64E@AssaultTransportAIUpdate@@QAE_NPAX@Z @0x0048F64E 66B
// __thiscall predicate on AssaultTransportAIUpdate: arg+0x254 slave provides
// two float virtuals at +0x10 and +0x18 (ratio a/b); this+4 master provides
// float at +0x64 threshold; returns threshold > ratio, false on null slave.
// Neighbours AssaultTransportAIUpdateCheck/ PassengerHelper share // cl and
// class; callers at 0x0048F9A7 0x0048FAA6 in 0x0048F828. /arch:SSE is what
// selects retail's fcomip float guard: plain /O1 emits the fnstsw/parity form
// three bytes shorter (63B). The Helper sibling TU carries the same flag.
#include "../../../../Common/GameLogicObjectLookupView.h"
enum NameKeyType;
enum CommandSourceType;
enum CommandSourceType { CMD_FROM_PLAYER = 0 };
enum UpdateSleepTime { UPDATE_SLEEP_NONE = 1 };

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

class Rva0048F64ESlave
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual float GetA();
	virtual void v05();
	virtual float GetB();
};
struct Rva0048F64EMaster
{
	unsigned char m_pad[0x64];
	float m64;
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
};bool AssaultTransportAIUpdate::rva0048F64E(void *arg)
{
	Rva0048F64ESlave *slave = *(Rva0048F64ESlave **)((char *)arg + 0x254);
	Rva0048F64EMaster *master = (Rva0048F64EMaster *)m_moduleData;
	if (slave != 0) {
		float a = slave->GetA();
		float b = slave->GetB();
		float ratio = a / b;
		if (ratio < master->m64)
			return true;
	}
	return false;
}
